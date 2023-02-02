#include "nsmb/player.h"
#include "nsmb/game.h"
#include "nsmb/stage/entity.h"
#include "nsmb/stage/actors/ov14/megagoomba.h"
#include "nsmb/entity/scene.h"
#include "nsmb/system/function.h"
#include "nsmb/sound.h"
#include "extra/events.hpp"
#include "extra/undocumented.hpp"

// FLAG POLE SHIFT ==================================

// Flag Pole collider size change
ncp_repl(0x021320AC, 12, ".int -0x8000") // Left
ncp_repl(0x021320B4, 12, ".int 0x8000") // Right

// Shift flag 8 pixels to the right
ncp_jump(0x0212FDCC, 12)
NTR_NAKED void flagPoleShiftHook() {asm(R"(
	MOV     R4, R0
	LDR     R3, [R0,#0x60]
	ADD     R3, R3, #0x8000 // pole->position.x += 0x8000;
	STR     R3, [R0,#0x60]
	B       0x0212FDD0
)");}

ncp_repl(0x0212FE28, 12, "ADD R0, R0, #0x2000") // Move the flag model

// Rotate the flag model
ncp_jump(0x0212FF30, 12)
NTR_NAKED void flagPoleRotateHook() {asm(R"(
	// X Rotation
	MOV     R0, #0x8000    // 90°
	STRH    R0, [R4,#0xA0]
	// Y Rotation
	MOV     R0, #0x4000    // -0xC000 (-180°)
	STRH    R0, [R4,#0xA2]
	B       0x0212FF3C     // Jump back to code
)");}

// FLAG POLE ANIMATION ==================================

ncp_repl(0x0211B9A4, 10, "MOV R1, #0x2000") // Player jumps further in the flag pole
ncp_repl(0x0211BA84, 10, "MOV R0, #0x600") // Change flag animation zoom
ncp_repl(0x0211BC20, 10, "NOP") // Do not zoom back when Mario starts walking

ncp_repl(0x0211BA68, 10, "SUB R1, R1, #0x10000") // Shift initial animation camera location X

// Shift initial animation camera location Y
asm(R"(
ncp_jump_ov 0x0211BA7C, 10
	SUB     R1, R1, #0x10000
	STR     R1, [R0]
	B       0x0211BA80
)");

ncp_repl(0x0211BBF8, 10, "MOV R1, #0x2000") // Player walks faster

// Walk animation speed
ncp_repl(0x02117938, 10, R"(
	MOV     R12, #0x1800
	B       0x02117980
)")

ncp_call(0x0211BC48, 10)
bool goalMoveCameraHook(Player* player)
{
	bool finished = player->transitStepCompleted(); // Keep replaced instruction
	*rcast<fx32*>(0x020CAD14) += 0x1800; // Camera move speed
	if (finished)
		*rcast<u32*>(0x020CA8C0) |= 0x10; // End level
	return finished;
}

ncp_repl(0x0211BB50, 10, "NOP") // Disable timer countdown

// Disable toad house special on flag pole
ncp_repl(0x0211C0A8, 10, R"(
	PUSH    {LR}
	MOV     R0, #4
	BL      _ZN4Game19playTransitionMusicEl
	MOV     R0, #0
	POP     {PC}
)")

ncp_repl(0x0213065C, 12, "B 0x02130698") // No goal score

// CEILING ROPE ==================================

ncp_repl(0x0210C1D0, 10, "MOV R1, #0x800") // Walk speed
ncp_repl(0x0210C1E8, 10, "MOV R1, #0x800") // Animation speed
ncp_repl(0x0210C18C, 10, "B   0x0210C1C8") // No running

// BAHP ==================================

ncp_repl(0x02012584, "B 0x0201258C") // Disable baphs

// NO SOFT RESET ==================================

ncp_repl(0x0201364C, "B 0x0201368C")

// MEGA GOOMBA ===================================

asm("_Z22MegaGoomba_switchStatePvmm = 0x02132D68");
void MegaGoomba_switchState(void*, u32, u32);

// Instant growth
/*NAKED void nsub_02131468_ov_0E()
{
asm(R"(
	MOV     R1, #1
	STRH    R1, [R0,#0xA8]
	B       0x213146C
)");
}*/

// Replace key spawn
ncp_repl(0x02130014, 14, "MOV R3, R4")

ncp_call(0x02130020, 14)
void MegaGoomba_spawnBossKeyHook(u16 classID, u32 settings, Vec3* pos, MegaGoomba* megaGoomba)
{
	// Calculate where to place the key
	Vec3 keyDestPos = *pos;
	keyDestPos.x -= 0x7800 * 16;
	keyDestPos.y -= 0x2C000;

	// Prevent the key from getting out of bounds
	fx32 minPos = megaGoomba->spawnPosX - 0xC0000;
	if (keyDestPos.x < minPos)
		keyDestPos.x = minPos;

	Actor::spawnActor(266, 0, &keyDestPos, nullptr, nullptr, nullptr); // Spawn "Boss Key Location"
	Actor::spawnActor(classID, settings, pos, nullptr, nullptr, nullptr); // Spawn "Boss Key"
}

// Fix some desyncs
ncp_repl(0x02132108, 14, "MOV R1, #0")
ncp_repl(0x0212FCCC, 14, "MOV R0, #0")

ncp_hook(0x021315C4, 14)
void MegaGoomba_freezeBarrierHook()
{
	if (!Event::isActive(48))
		return;

	for (int i = 0; i < Game::getPlayerCount(); i++)
	{
		Player* player = Game::getPlayer(i);
		player->velH = 0;
		player->direction = 0;
		player->subActionFlag.releaseKeys = true;
	}
}

ncp_call(0x0213160C, 14)
void MegaGoomba_beginCutsceneHook(MegaGoomba* self, u32 a, u32 b)
{
	MegaGoomba_switchState(self, a, b); // Keep replaced instruction

	for (int i = 0; i < Game::getPlayerCount(); i++)
	{
		Player* player = Game::getPlayer(i);
		if (self->viewID == player->viewID)
		{
			player->beginCutscene(true);
		}
	}
}

ncp_call(0x0213137C, 14)
void MegaGoomba_endCutsceneHook()
{
	for (int i = 0; i < Game::getPlayerCount(); i++)
	{
		Player* player = Game::getPlayer(i);
		player->endCutscene();
	}
}

// BOSS KEY ===================================

// Victory freeze
ncp_call(0x0214619C, 40)
void bossVictoryFreezeHook()
{
	u32 playerID = Game::localPlayerID;
	Game::getPlayer(playerID)->physicsFlag.bossDefeated = true;

	if (Game::getPlayerCount() == 2)
		Game::getPlayer(!playerID)->actionFlag.bowserJrBeaten = true;
}

// Custom boss battle end
ncp_jump(0x0214560C, 40)
void bossVictoryCutsceneHook(StageActor* bossKey)
{
	u16& frame = *rcast<u16*>(rcast<u8*>(bossKey) + 0x530);

	if (frame == 0xB0)
		Stage::exitLevel();

	frame++;
}

// Skip boss controller check
ncp_repl(0x021453D4, 40, "B 0x02145420")

// REMOVE DOWNLOAD PLAY ===================================

ncp_call(0x021592DC, 52)
int mvslMenuCreationHook()
{
	register int* mvslMenu asm("r4");

	mvslMenu[0x15C / 4] = 0x0215CA6C; // Sub-menu updater
	mvslMenu[0x160 / 4] = 0x00000001; // Sub-menu swap timer

	return 1;
}

ncp_hook(0x021587F8, 52)
void mvslMenuReturnButtonHook(int* mvslMenu)
{
	// Variable that happens to not be 0 during connection menu
	if (mvslMenu[0x134 / 4])
	{
		Scene::switchScene(SceneID::TitleScreen);
		Sound::stopBGM(30);
	}
}

// MULTIPLAYER ===================================

ncp_repl(0x021578F0, 52, "MOVEQ R1, #0") // Force MvsLMode = 0

// Replace MvsL load function
ncp_repl(0x021535A0, 52, R"(
	MOV R0, #2
	B _ZN4Game14setPlayerCountEl
)")

ncp_repl(0x02157A3C, 52, R"(
	MOV R0, #4 // SceneID::TitleScreen
	MOV R1, #0
)")

ncp_repl(0x020AECA4, 0, "MOV R1, #1") // Disable background HDMA parallax

ncp_repl(0x020BD820, 0, "BL _ZN4Game14getPlayerCountEv") // Bottom screen background draw
ncp_repl(0x020BDA90, 0, "BL _ZN4Game14getPlayerCountEv") // Bottom screen background execute
ncp_repl(0x020BDC1C, 0, "BL _ZN4Game14getPlayerCountEv") // Bottom screen background load

ncp_repl(0x020FBF60, 10, "BX LR") // Fix end of level for player that "lost the race"

ncp_repl(0x0209AAD0, 0, "BX LR") // Disable MvsL coin score
ncp_repl(0x020D3350, 10, "NOP") // Disable MvsL coin score for coin actor

ncp_repl(0x0209AC1C, 0, "MOV R0, #1") // Allow score incrementation
ncp_repl(0x0209ABA8, 0, "MOV R0, #1") // Allow score incrementation from actors

// Only freeze timer and pause menu on toad houses
ncp_jump(0x0212B908, 11)
void coopTimerFreezeHook(Player* player)
{
	if (Game::stageGroup == 8 || Game::getPlayerCount() == 1)
	{
		*rcast<u8*>(0x020CA898) |= 0x40;
		*rcast<u8*>(0x020CA880) |= 0x10;
		player->transitioningFlag = 1;
		player->activeCollider.collisionResult |= 1;
	}
}

ncp_repl(0x020D13B4, 10, "NOP") // Powerups don't despawn

ncp_repl(0x0200E874, "BX LR") // No wireless strenght icon bitmap
ncp_repl(0x0200E944, "BX LR") // No wireless strenght icon palette

ncp_repl(0x020A1590, 0, "MOV R0, #1") // Force MvsL pause menu settings
ncp_repl(0x020A1E10, 0, "MOV R0, #1") // Force MvsL pause menu behaviour
ncp_repl(0x0215F1BC, 54, "MOV R0, #4") // Force MvsL pause menu text
ncp_repl(0x020A2004, 0, "B 0x020A2034") // Do not end connection on pause menu quit

// MISC ===================================

// Level exits to titlescreen
ncp_repl(0x020A19D8, 0, R"(
	MOV R0, #4
	MOV R1, #0
)")

// Do not draw level intro in the only frame that it shows up
ncp_repl(0x02152884, 54, R"(
	MOV R0, #1
	BX  LR
)")

// Make level intro have a duration of 0
ncp_repl(0x02152840, 54, R"(
	PUSH {LR}
	LDR  R1, [R0,#8]
	MOV  R0, #3
	BL   _ZN5Scene11switchSceneEtm
	MOV  R0, #1
	POP  {PC}
)")

ncp_repl(0x020C93B9, 0, ".int 0"); // Castle level jyotyu palette
ncp_repl(0x0209E038, 0, "BX LR") // Disable goomba/coin drop on Mega Mario ground-pound
ncp_repl(0x0215ED54, 54, "NOP") // Do not spawn Mega Mario destruction counter
ncp_repl(0x0209D86C, 0, "NOP") // Enemies don't drop coins when burned
ncp_repl(0x020FD544, 10, "B 0x020FD568") // Mario doesn't look at enemies

// Coins keep incrementing until 999
ncp_jump(0x020203D0)
NTR_NAKED void coinIncrementHook() {asm(R"(
	LDR     R3, =999
	CMP     R0, R3
	B       0x020203D4
)");}

ncp_repl(0x020203E4, "B 0x020203FC") // Coins don't award powerup

ncp_repl(0x0215E850, 54, "NOP") // Do not load doors
ncp_repl(0x021002F0, 10, "MOV R0, #1") // Door doesn't play animation

ncp_repl(0x020BA038, 0, "POP {R4-R8,PC}") // Disable shoulder buttons

ncp_repl(0x02006E00, "MOV R6, #0") // Clear freezing flag
ncp_repl(0x02006AE8, "NOP") // Prevent freezing flag being set on level load
