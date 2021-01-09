#include "nsmb.h"

//Set zoom when growing to Mega form
void repl_0212027C_ov_0A(int item, int playerNo)
{
	SetLevelZoom(0x1400, 16, playerNo, 0);
	GiveScoreItemForPlayer(item, playerNo); //Keep replaced instruction
}
//Fancier but less accurate alternative:
//void hook_02120344_ov_0A() { SetLevelZoom(0x1400, 64, 0, 0); }

//Set zoom when un-growing from Mega form
void hook_02120528_ov_0A(PlayerActor* player)
{
	int playerNo = player->actor.playerNumber;
	SetLevelZoom(0x1000, 16, playerNo, 0);
}

void repl_02120288_ov_0A() { asm("MOV R1, #0x4B0\nBX LR"); }

void repl_02011A7C() {} //Do not load Mega Mario music
void repl_02120298_ov_0A() {} //Do not play Mega Mario music

//Mega Mushroom doesn't move around
NAKED void nsub_020D37E0_ov_0A() { asm("B 0x020D3818"); }
NAKED void nsub_020D368C_ov_0A() { asm("B 0x020D3694"); }

// MEGA KICK ===================================

void PlayerActor_doKickDestruction(PlayerActor* player)
{
    if(player->P.powerupStateOld != 3)
        return;

    int d = player->info.direction ? -1 : 1;

    int xS = FX_Whole(player->actor.position.x) + ((16 * 1) * d);
    int yS = -FX_Whole(player->actor.position.y) - (16 * 4);
    for(int yy = 0; yy < (16 * 4); yy += 16) {
        for(int xx = 0; xx < (16 * 4); xx += 16)
        {
            int x = xS + (xx * d);
            int y = yS + yy;
            if(GetTileBehaviorAtPos(x, y) & 0x1C0000)
            {
                ChangeTile(*(void**)0x020CAD40, x, y, 0);
            }
        }
    }
}

bool PlayerActor_megaKickState(PlayerActor *player, int arg)
{
    if (player->P.movementStateStep == -1) //dtor
    {
        //nothing to destroy
    }
    else if (!player->P.movementStateStep) //ctor
    {
        PlayerActor_setAnimation(player, 83, 0, 0, 0x800, 0);
        player->P.movementStateStep++;
    }
    else //update
    {
        bool animEnded = PlayerActor_animationEnded(player);
        if(animEnded || player->collider.isOnGround)
        {
            PlayerActor_setMovementState(player, 0x021135B8, false, 0);
        }
        else
        {
            if(player->P.movementStateStep == 0xA)
                PlayerActor_doKickDestruction(player);
            else if(player->P.movementStateStep == 0x17)
                PlayerActor_setAnimationSpeed(player, 0x100); //Kick retraction speed
            PlayerActor_updateAnimation(player);
            player->P.movementStateStep++;
        }
    }
    return true;
}

bool PlayerActor_checkMegaKick(PlayerActor* player)
{
    bool rButtonDown = player->P.ButtonsPressed & PAD_BUTTON_R;
    if(rButtonDown)
    {
        PlayerActor_setMovementState(player, (int)PlayerActor_megaKickState, false, 0);
        return true;
    }
    return false;
}

bool repl_021136E0_ov_0A(PlayerActor* player)
{
	if(PlayerActor_checkMegaKick(player))
		return true;
	return PlayerActor_checkGroundPound(player);
}