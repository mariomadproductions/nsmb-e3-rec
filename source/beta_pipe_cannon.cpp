#include "nsmb.h"

// =================== PROPERTY CONTROL ===================

void repl_020F8704_ov_0A(PlayerActor* player, EnemyActor* pipe, fx32 force, fx32 angle, fx32 direction, int cannon_mode)
{
	u16 spriteData = pipe->actor.base.spriteData;
	force = ((spriteData >> 8) & 0xFF) * 0x400;
	player->actor.base.vtable->virt37(player, pipe, force, angle, direction, cannon_mode);
}

// =================== PARTICLES ===================

void nsub_0210C8DC_ov_0A()
{
	asm("MOV R0, R4");
	asm("BL  PlayerActor_SpawnStarmanParticles");
	asm("B   0x0210C92C");
}
void nsub_020F87A0_ov_0A() { asm("B 0x020F87B4"); } //Do not spawn pipe cannon particles

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

void nsub_02098B08_ov_00()
{
	asm("MOV     R0, R7");
	asm("MOV     R2, R4");
	asm("BL      EnemyInvecibility_check");
	asm("CMP     R0, #0");
	asm("BEQ     0x2098B38");
	asm("B       0x2098B1C");
}

// Fix pipe cannon desync
void nsub_020F8230_ov_0A() { asm("B 0x020F823C"); }