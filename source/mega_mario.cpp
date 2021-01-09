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

static u8 breakTextures[] = {
    5, 2, 1, 6
};

void PlayerActor_doKickDestruction(PlayerActor* player)
{
    if(player->P.powerup != 3)
        return;

    const int direction = player->info.direction ? -1 : 1;

    const int tileX =  FX_Whole(player->actor.position.x);
    const int tileY = -FX_Whole(player->actor.position.y);

    // 16 = 1 tile
    const int rectX = 1 * 16;
    const int rectY = 6 * 16;
    const int rectW = 3 * 16;
    const int rectH = 6 * 16;

    const int xOff = tileX + (rectX * direction);
    const int yOff = tileY - rectY;

    for(int w = 0; w < rectW; w += 16)
    {
        for(int h = 0; h < rectH; h += 16)
        {
            const int x = xOff + (w * direction);
            const int y = yOff + h;

            const int tileB = GetTileBehaviorAtPos(x, y);
            if(tileB & 0x1C0000)
            {
                ChangeTile(*(void**)0x020CAD40, x, y, 0);

                int breakTex;
                if (tileB & 0x40000)
                    breakTex = 3;
                else if (tileB & 0x100000)
                    breakTex = 0;
                else
                    breakTex = breakTextures[0x80003 - tileB];
                
                Vec3 pos;
                pos.x =  x << FX32_SHIFT;
                pos.y = -y << FX32_SHIFT;
                SpawnBrokenTileParticle(22, &pos, 0, 0, 3, (breakTex << 8) | 2);
            }
        }
    }
}

bool PlayerActor_kickState(PlayerActor *player, int arg)
{
    if (player->P.movementStateStep == -1) //dtor
    {
        //nothing to destroy
    }
    else if (!player->P.movementStateStep) //ctor
    {
        player->P.movementStateStep++;
        if ( player->P.powerup == 3 )
            player->P.miscActionsBitfield |= 0x40000000;
        PlayerActor_setAnimation(player, 83, 0, 0, 0x800, 0);
    }
    else //update
    {
        bool grounded = player->P.collBitfield & 1;
        if (PlayerActor_animationEnded(player) || grounded)
        {
            PlayerActor_setMovementState(player, 0x021135B8, false, 0);
        }
        else
        {
            if (player->P.movementStateStep == 0xA)
                PlayerActor_doKickDestruction(player);
            else if (player->P.movementStateStep == 0x17)
                PlayerActor_setAnimationSpeed(player, 0x100); //Kick retraction speed

            PlayerActor_updateAnimation(player);
            player->P.movementStateStep++;
        }
    }
    return true;
}

bool PlayerActor_checkKick(PlayerActor* player)
{
    bool rButtonDown = player->P.ButtonsPressed & PAD_BUTTON_R;
    bool notSmall = player->P.powerup != 0 && player->P.powerup != 4;
    bool nearGround = player->P.collBitfield & 0x8000001;
    bool goingDown = player->actor.velocity.y < 0;
    bool notJumping2 = player->P.consecutiveJumps != 2;

    if (rButtonDown && notSmall && notJumping2 && !(nearGround && goingDown))
    {
        PlayerActor_setMovementState(player, (int)PlayerActor_kickState, false, 0);
        return true;
    }

    return false;
}

bool repl_021136E0_ov_0A(PlayerActor* player)
{
	if (PlayerActor_checkKick(player))
		return true;
	return PlayerActor_checkGroundPound(player);
}