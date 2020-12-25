#include "nsmb.h"

// FLAG POLE SHIFT ==================================

/* REPLACES.X

@ FLAG POLE SOLID COLLISION SIZE CHANGE
021320AC_ov_0C: 0xFFFF8000		@LEFT
021320B4_ov_0C: 0x8000			@RIGHT

*/

// Shift flag 8 pixels to the right
void hook_0212FDCC_ov_0C(EnemyActor* pole)
{
	pole->actor.position.x += 0x8000;
}

// Move the flag model
NAKED void nsub_0212FE28_ov_0C()
{
asm(R"(
	ADD     R0, R0, #0x2000
	B       0x0212FE2C
)");
}

// Rotate the flag model
NAKED void nsub_0212FF30_ov_0C()
{
asm(R"(
	@ X Rotation
	MOV     R0, #0x8000    @ 90°
	STRH    R0, [R4,#0xA0]

	@ Y Rotation
	MOV     R0, #0x4000    @ -0xC000 (-180°)
	STRH    R0, [R4,#0xA2]

	B       0x0212FF3C     @ Jump back to code
)");
}

// BAHP ==================================

NAKED void nsub_02012584() { asm("B 0x0201258C"); } //Disable baphs

// NO SOFT RESET ==================================

NAKED void nsub_0201364C() { asm("B 0x201368C"); }

// MEGA GOOMBA ===================================

//Instant growth
/*NAKED void nsub_02131468_ov_0E()
{
asm(R"(
	MOV     R1, #1
	STRH    R1, [R0,#0xA8]
	B       0x213146C
)");
}*/

//Custom boss battle end
void nsub_0214560C_ov_28(EnemyActor* bossKey)
{
	u16& frame = *(u16*)((u8*)bossKey + 0x530);

	if(frame == 0xB0)
		ExitLevel(true);

	frame++;
}

//Skip boss controller check
NAKED void nsub_021453D4_ov_28() { asm("B 0x02145420"); }

//Replace key spawn
NAKED void repl_02130014_ov_0E() { asm("MOV R3, R4\nBX LR"); }
void repl_02130020_ov_0E(int classID, int spriteData, Vec3 *pos, EnemyActor* mGoomba)
{
	fx32 mGoomba_xStartPos = *(fx32*)((u8*)mGoomba + 0x748);

	//Calculate where to place the key
	Vec3 keyDestPos = *pos;
	keyDestPos.x -= 0x7800 * 16;
	keyDestPos.y -= 0x2C000;

	//Prevent the key from getting out of bounds
	fx32 minPos = mGoomba_xStartPos - 0xC0000;
	if (keyDestPos.x < minPos)
		keyDestPos.x = minPos;

	CreateActor(266, 0, &keyDestPos, 0, 0, 0); //Spawn "Boss Key Location"
	CreateActor(classID, spriteData, pos, 0, 0, 0); //Spawn "Boss Key"
}

void hook_021315C4_ov_0E()
{
	if (!isEventActive(48))
		return;

	for (int i = 0; i < GetPlayerCount(); i++)
	{
		PlayerActor* player = GetPtrToPlayerActorByID(i);
		player->P.miscActionsBitfield |= 0x80;
		player->actor.collisionBitfield = 0;
	}
}
void hook_02131604_ov_0E()
{
	for (int i = 0; i < GetPlayerCount(); i++)
	{
		PlayerActor_freeze(GetPtrToPlayerActorByID(i), true);
	}
}

// MULTIPLAYER ===================================

NAKED void repl_021578F0_ov_34() { asm("MOVEQ R1, #0\nBX LR"); } //Force MvsLMode = 0
void nsub_021535A0_ov_34() { SetPlayerCount(2); } //Change mvsl setup crap

int repl_02157A40_ov_34()
{
	asm("MOV R1, #0");
	return MAIN_MENU_SCENE;
}

NAKED void repl_020AECA4_ov_00() { asm("MOV R1, #1\nBX LR"); } //Disable background HDMA parallax

int repl_020BD820_ov_00() { return GetPlayerCount(); } //Bottom screen background draw
int repl_020BDA90_ov_00() { return GetPlayerCount(); } //Bottom screen background execute
int repl_020BDC1C_ov_00() { return GetPlayerCount(); } //Bottom screen background load

void nsub_020FBF60_ov_0A() {} //Fix end of level for player that "lost the race"

void nsub_0209AAD0_ov_00() {} //Disable MvsL coin score
void repl_020D3350_ov_0A() {} //Disable MvsL coin score for coin actor

int repl_0209AC1C_ov_00() { return 1; } //Allow score incrementation
int repl_0209ABA8_ov_00() { return 1; } //Allow score incrementation from actors

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

void repl_020D13B4_ov_0A() {} //Powerups don't despawn

void nsub_0200E874() {} //No wireless strenght icon bitmap
void nsub_0200E944() {} //No wireless strenght icon palette

//Fix desyncs on pause menu
u16* repl_020A20E8_ov_00(u8* stageScene) { asm("MOV R0, R5"); return &((u16*)0x2087648)[stageScene[25640]]; }
u8 repl_020A21A4_ov_00(u8* stageScene) { asm("MOV R0, R5"); return stageScene[25640]; }
u8 repl_020A22D8_ov_00(u8* stageScene) { return repl_020A21A4_ov_00(stageScene); }
//Disable options on pause menu
void repl_020A2230_ov_00() {
	if (GetPlayerCount() == 1)
		asm("BL 0x20C1F14");
}

// MISC ===================================

//Disable goomba/coin drop on Mega Mario ground-pound
void nsub_0209E038_ov_00() {}

//Do not spawn Mega Mario destruction counter
void repl_0215ED54_ov_36() {}

//Enemies don't drop coins when burned
void repl_0209D86C_ov_00() {}

//Mario doesn't look at enemies
NAKED void nsub_020FD544_ov_0A() { asm("B 0x020FD568"); }

//Coins keep incrementing until 999
NAKED void repl_020203D0()
{
asm(R"(
	LDR     R1, =999
	CMP     R0, R1
	LDR     R1, =0x0208B37C @ Restore R1
	BX      LR
)");
}
NAKED void nsub_020203E4() { asm("B 0x020203FC"); }

void repl_0215E850_ov_36() {} //Do not load doors
int repl_021002F0_ov_0A() { return 1; } //Door doesn't play animation

//Disable shoulder buttons
NAKED void nsub_020BA038_ov_00() { asm("LDMFD SP!, {R4-R8,PC}"); }