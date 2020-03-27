#include "nsmb.h"

void repl_02119CB8_ov_0A() {} //Do not freeze timer on player death
//Do not allow player to respawn so we can control it ourselves
int repl_0212B318_ov_0B() { return 1; }
void repl_0212B334_ov_0B() { asm("MOV R0, R6"); asm("MOV R1, R4"); }
bool repl_0212B338_ov_0B(int playerNo, int lives)
{
	if (GetPlayerCount() == 1)
	{
		fx32 fx32_timeLeft = *(fx32*)0x020CA8B4;
		if (lives == 0 || fx32_timeLeft == 0)
		{
			ExitLevel(false);
			return false; //Do not respawn
		}
		else
		{
			return true;
		}
	}
	else
	{
		if ((lives == 0 && GetLivesForPlayer(!playerNo) == 0) || GetPlayerDeathState(!playerNo))
		{
			ExitLevel(false);
			return false; //Do not respawn
		}
		else
		{
			return true;
		}
	}
}

void nsub_0211C470_ov_0A() { asm("B 0x0211C580"); } //No pipe entrance on respawn

extern "C" void SetRespawnEntranceForRing(EnemyActor* ring, int playerNo)
{
	u32 ringData = ring->actor.base.spriteData;
	u32 entranceId = (ringData >> 8) & 0xFF;

	Entrance* entrance = GetPtrToEntranceById(entranceId, entranceId);

	int x = (entrance->x + 8) << 12;
	int y = -(entrance->y + 16) << 12;
	SetRespawnPositionForPlayer(playerNo, x, y);
}

void nsub_021536A8_ov_36()
{
	asm("MOV R0, R4");
	asm("MOV R1, R5");
	asm("BL  SetRespawnEntranceForRing");
	asm("LDR R0, [R6,#0x60]"); //Keep replaced instruction
	asm("B   0x021536AC"); //Return to code
}

//Only freeze timer and pause menu on toad houses
void nsub_0212B908_ov_0B(u8* player)
{
	if (*(int*)0x02085A18 == 8 || GetPlayerCount() == 1)
	{
		*(int*)0x020CA898 |= 0x40;
		*(int*)0x020CA880 |= 0x10;
		player[1968] = 1;
		player[454] |= 1;
	}
}