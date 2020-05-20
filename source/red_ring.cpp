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

extern "C" {
	void* findNextTreeNode(void* node);
	void BGActor_animateBrickBlocks(void* level);
	void BGActor_animateQuestionBlocks(void* level);
	void BGActor_animateCoins(void* level, int frame);
}
void DeleteStageSprites()
{
	void* node = *(void**)0x0208FB0C;
	while (true)
	{
		node = findNextTreeNode(node);
		if (!node)
		{
			break;
		}
		Actor* node_actor = (Actor*)((u32*)node)[4];
		if (node_actor->actorType == T_SPRITE)
		{
			Base_deleteIt(node_actor);
		}
	}
}
void repl_021188C4_ov_0A(PlayerActor* player)
{
	player->info.direction = D_Right;
	if (GetPlayerCount() == 1)
	{
		u16* block1ptr = *(u16**)0x0208B168;
		int* timeLeft = (int*)0x020CA8B4;
		*timeLeft = block1ptr[2] << 12;

		DeleteStageSprites();

		u16* spawnedSprite1 = (u16*)0x020CA3CC;
		u16* spawnedSprite2 = (u16*)0x020CA64C;
		u16* spriteRespData = (u16*)0x02129220;
		MI_CpuClearFast(spawnedSprite1, 0x100);
		MI_CpuClearFast(spawnedSprite2, 0x200);
		MI_CpuFillFast(spriteRespData, 0xFFFFFFFF, 0x100);

		u64* activatorBitmask = (u64*)0x0208AF3C;
		*activatorBitmask = 0;

		void* pLevelActor = *(void**)0x020CAD40;
		u8* brickBlockFrame = (u8*)0x0212943C;
		u8* questionBlockFrame = (u8*)0x0212944C;
		u8* coinFrame = (u8*)0x0212944C;
		*brickBlockFrame = 0;
		*questionBlockFrame = 0;
		*coinFrame = 0;
		BGActor_animateBrickBlocks(pLevelActor);
		BGActor_animateQuestionBlocks(pLevelActor);
		BGActor_animateCoins(pLevelActor, 0);

		//Freeze
		int* frozenBitmask = (int*)0x020CA850;
		*frozenBitmask |= 4;

		//Change fading transition
		((u8*)SCENE_INFO)[1474] = 0;
	}
}
//Hook stage tile reset
void nsub_02118888_ov_0A()
{
	asm("BL      GetPlayerCount"); //Get the player count
	asm("CMP     R0, #1"); //Compare if it is 1
	asm("LDRNE   R0, =0x2089506"); //(If not) keep replaced instruction
	asm("BNE     0x0211888C"); //(If not) return to code

	asm("LDRSH   R0, [R0,#0x68]"); //Player->IsRespawning
	asm("CMP     R0, #0"); //Compare if it is 0
	asm("MOVNE   R0, #1"); //(If not) R0 = 1
	asm("LDRNE   R1, =0x020CAC98"); //(If not) R1 = &Level->resetStage
	asm("STRNEB  R0, [R1]"); //(If not) *R1 = R0

	asm("LDR     R0, =0x2089506"); //Keep replaced instruction
	asm("B       0x0211888C"); //Return to code
}

//Restore fading head transition on single player respawn
void hook_02118DBC_ov_0A()
{
	if (GetPlayerCount() == 1)
	{
		((u8*)SCENE_INFO)[1474] = 2;
	}
}

void repl_02118974_ov_0A() {} //Player doesn't blink on respawn
void repl_021189B8_ov_0A() {} //Player visible during respawn fade

void hook_0211C580_ov_0A()
{
	if (GetPlayerCount() == 1)
	{
		int* frozenBitmask = (int*)0x020CA850;
		*frozenBitmask &= ~4;
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

		RedCoinRing_updateColor(ring);

		int* respawnEntrance = (int*)0x0208B0B8;
		respawnEntrance[playerNo] = entranceId;
	}
}
void nsub_0201E558() { asm("B 0x0201E580"); }
int repl_0201E584(int playerNo)
{
	int* respawnEntrance = (int*)0x0208B0B8;
	int dest = respawnEntrance[playerNo];
	if (dest == 0)
	{
		dest = GetStartEntranceIDForPlayer(playerNo);
	}
	return dest;
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