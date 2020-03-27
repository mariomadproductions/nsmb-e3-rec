#include "nsmb.h"

// FLAG POLE SHIFT ==================================

/* REPLACES.X

@ POLE BOTTOM SOLID COLLISION CHANGE
021320AC_ov_0C: 0xFFFF8000		@LEFT
021320B4_ov_0C: 0x8000			@RIGHT

*/

void hook_0212FDCC_ov_0C(EnemyActor* pole)
{
	pole->actor.position.x += 0x8000;
}

// BAHP ==================================

void nsub_02012584() { asm("B 0x0201258C"); } //Disable baphs

// MULTIPLAYER ===================================

void repl_021578F0_ov_34() { asm("MOVEQ R1, #0"); } //Force MvsLMode = 0
void nsub_021535A0_ov_34() { SetPlayerCount(2); } //Change mvsl setup crap

int repl_02157A40_ov_34()
{
	asm("MOV R1, #0");
	return MAIN_MENU_SCENE;
}

void repl_020AECA4_ov_00() { asm("MOV R1, #1"); } //Disable background HDMA parallax

int repl_020BD820_ov_00() { return GetPlayerCount(); } //Bottom screen background draw
int repl_020BDA90_ov_00() { return GetPlayerCount(); } //Bottom screen background execute
int repl_020BDC1C_ov_00() { return GetPlayerCount(); } //Bottom screen background load

void nsub_020FBF60_ov_0A() {} //Fix end of level for player that "lost the race"

void nsub_0209AAD0_ov_00() {} //Disable MvsL coin score
void repl_020D3350_ov_0A() {} //Disable MvsL coin score for coin actor

void nsub_0200E944() {} //No wireless strenght icon palette