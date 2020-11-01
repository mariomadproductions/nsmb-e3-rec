#include "nsmb.h"

// =================== PROPERTY CONTROL ===================

// #include <cstddef>
// void repl_020F8704_ov_0A(PlayerActor* player, EnemyActor* pipe, fx32 force, fx32 angle, fx16 direction, BOOL cannon_mode, BOOL timed, u16 duration)
// {
// 	/*u16 spriteData = pipe->actor.base.spriteData;
// 	force = ((spriteData >> 8) & 0xFF) * 0x400;*/
// 
// 	/*force = 0x4200;
// 	angle = 0x2080;
// 	//direction = 0x4000;
// 	cannon_mode = 0;
// 	timed = 1;
// 	duration = 114;*/
// 
// 	/*cout << "Force     = " << (int)force << "\n";
// 	cout << "Angle     = " << (int)angle << "\n";
// 	cout << "Direction = " << (int)direction << "\n";
// 	cout << "Warp Can. = " << (int)cannon_mode << "\n";
// 	cout << "Timed     = " << (int)timed << "\n";
// 	cout << "Duration  = " << (int)duration << "\n";
// 
// 	player->P.powerupStateOld = 4;
// 	player->P.powerupStateCurrent = 4;*/
// 
// 	cout << ((int)player + offsetof(PlayerActor, actor.position.y)) << "\n";
// 
// 	player->actor.base.vtable->virt37(player, pipe, force, angle, direction, cannon_mode, timed, duration);
// }

//void repl_0210651C_ov_0A() {}

// =================== PARTICLES ===================

NAKED void nsub_0210C8DC_ov_0A()
{
asm(R"(
	MOV     R0, R4
	BL      PlayerActor_SpawnStarmanParticles
	B       0x0210C92C
)");
}
NAKED void nsub_020F87A0_ov_0A() { asm("B 0x020F87B4"); } //Do not spawn pipe cannon particles

// =================== INVENCIBILITY ===================

extern "C"
bool EnemyInvecibility_check(EnemyActor* enemy, int playerNo, PlayerActor* player)
{
	u16* StarmanTimeForPlayer = (u16*)0x0208B350;
	bool beingShoot = (player->P.miscActionsBitfield & BEING_SHOOT);
	if ((StarmanTimeForPlayer[playerNo] > 1) || beingShoot)
	{
		if (beingShoot)
		{
			enemyActor_dropCoin(enemy);
		}
		return true;
	}
	return false;
}

NAKED void nsub_02098B08_ov_00()
{
asm(R"(
	MOV     R0, R7
	MOV     R2, R4
	BL      EnemyInvecibility_check
	CMP     R0, #0
	BEQ     0x2098B38
	B       0x2098B1C
)");
}

// Fix pipe cannon desync
NAKED void nsub_020F8230_ov_0A() { asm("B 0x020F823C"); }

/*void hook_020FD1DC_ov_0A(PlayerActor* player)
{
	//cout << "player->P.movementStateFunc: " << player->P.movementStateFunc << "\n";
	//cout << "player->P.movementStateStep: " << player->P.movementStateStep << "\n";

	if (player->P.ButtonsPressed & PAD_BUTTON_B)
	{
		// *(int*)0x0208B334 = 60;
		player->P.powerupStateCurrent = 4;
		player->P.powerupStateOld = 4;
	}
}*/