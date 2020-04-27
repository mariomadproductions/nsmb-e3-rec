#include "nsmb.h"

int repl_0215395C_ov_36() { return 0x4EE; } //Increase ring allocation size

// ============================================= CORE RESPAWN =============================================

int repl_0212B2DC_ov_0B() { return 1; } //Do not decrement player lives
void repl_02119CB8_ov_0A() {} //Do not freeze timer on player death
void nsub_0212B314_ov_0B() //Take total control of death/respawn check system and set arguments
{
	asm("MOV R0, R6");
	asm("MOV R1, R4");
	asm("B 0x0212B338");
}
bool repl_0212B338_ov_0B(int playerNo, int lives) //Implement new system
{
	fx32 fx32_timeLeft = *(fx32*)0x020CA8B4;
	if (fx32_timeLeft == 0)
	{
		ExitLevel(false);
		return false; //Do not respawn
	}
	else
	{
		return true; //Respawn
	}
}

void nsub_0211C470_ov_0A() { asm("B 0x0211C580"); } //No pipe entrance on respawn

// ============================================= RING RESPAWN =============================================

static u32 ringCollected[2];

extern "C"
bool GetRingCollectedForPlayer(EnemyActor * ring, int playerNo)
{
	u32 ringData = ring->actor.base.spriteData;
	u8 ringId = ringData & 0xF;
	return (ringCollected[playerNo] >> ringId) & 1;
}

void RedCoinRing_updateColor(EnemyActor* ring)
{
	u8& ring_color = ((u8*)ring)[0x4ED];

	bool collected_m = GetRingCollectedForPlayer(ring, 0);
	bool collected_l = GetRingCollectedForPlayer(ring, 1);

	ring_color = 1 + (collected_m | (collected_l << 1));
}

extern "C"
{
	void RedCoinRing_setExecuteState(void* ring, int func, int thumb);
	void RedCoinRing_slowDownRotation(void* ring, s16* rotX_inc, s16 rotX_max, s16 rotX_dec);
	void RedCoinRing_checkAgainstPosition(void* ring, int playerNo);
	bool RedCoinRing_checkIfTouched(void* ring, int playerNo);

	void RedRing_OnCollided(EnemyActor* ring, int playerNo)
	{
		u32 ringData = ring->actor.base.spriteData;
		u8 ringId = ringData & 0xF;
		u32 entranceId = (ringData >> 8) & 0xFF;

		ringCollected[playerNo] |= (1 << ringId);
		Entrance* entrance = GetPtrToEntranceById(entranceId, entranceId);

		RedCoinRing_updateColor(ring);

		int x = (entrance->x + 8) << 12;
		int y = -(entrance->y + 16) << 12;
		SetRespawnPositionForPlayer(playerNo, x, y);
	}
}

void hook_0215E478_ov_36() { ringCollected[0] = 0; ringCollected[1] = 0; }

void nsub_0215365C_ov_36() //Do not allow player to hit ring if already collected
{
	asm("BEQ     0x21537CC"); //If player pointer is null then continue to check next player
	asm("PUSH    {R0}"); //Save player pointer to stack
	asm("MOV     R0, R6"); //Pass actor as first argument
	asm("MOV     R1, R5"); //Pass player number as second argument
	asm("BL      GetRingCollectedForPlayer"); //Execute the collect check function
	asm("CMP     R0, #1"); //Compare if ring is collected
	asm("POP     {R0}"); //Restore player pointer from stack
	asm("BEQ     0x21537CC"); //If ring is collected then continue to check next player
	asm("B       0x2153660"); //Return to code in case all matches
}

void nsub_021536A8_ov_36()
{
	asm("MOV     R0, R6"); //Pass actor as first argument
	asm("MOV     R1, R5"); //Pass player number as second argument
	asm("BL      RedRing_OnCollided"); //Execute my collision function
	asm("LDR     R0, [R6,#0x60]"); //Keep replaced instruction
	asm("B       0x021536AC"); //Return to code
}

void hook_02153198_ov_36(EnemyActor* ring) //Color on create
{
	RedCoinRing_updateColor(ring);
}

void repl_021536B4_ov_36() {} //Ring doesn't get set as not respawn between areas
void repl_021534E4_ov_36() //Set some ring variables on collected state enter
{
	asm("MOV     R1, #0");
	asm("STRB    R1, [R0,#0x4EC]"); //ring_frames = 0;
	asm("MOV     R1, #0"); //Ring doesn't get deleted permanently
}
void repl_021535B4_ov_36(EnemyActor* ring, s16* rotX_inc, s16 rotX_extreme, s16 rotX_dec) //Ring can stop rotation
{
	s8 direction = ((s8*)0x20C4EC4)[ring->info.direction ^ 1];
	u8& ring_frames = ((u8*)ring)[0x4EC];

	if (ring_frames == 0)
	{
		RedCoinRing_slowDownRotation(ring, rotX_inc, rotX_extreme, rotX_dec);
		ring_frames++;
	}
	else if (ring_frames == 0x40)
	{
		ring->actor.rotation.y = -0x2000 * direction;
		RedCoinRing_setExecuteState(ring, 0x2153604, 0);
	}
	else
	{
		u16& ring_rotY_inc = ((u16*)ring)[0x274];
		ring_rotY_inc -= (0x30 * direction);
		ring_frames++;
	}
}