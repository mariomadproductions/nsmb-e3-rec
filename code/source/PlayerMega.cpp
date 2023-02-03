#include "nsmb/stage/misc.h"
#include "nsmb/stage/entity.h"
#include "nsmb/stage/player/player.h"

// Set zoom when growing to Mega form
ncp_call(0x0212027C, 10)
void megaGrowZoomHook(int item, int playerID)
{
	StageEntity::getCollectablePoints(item, playerID); // Keep replaced instruction
	Stage::setZoom(0x1400, 16, playerID, 0);
}
// Fancier but less accurate alternative:
// ncp_hook(0x02120344, 10) void megaMarioGrowZoomHook() { Stage::setZoom(0x1400, 64, 0, 0); }

// Set zoom when un-growing from Mega form
ncp_call(0x0212052C, 10)
void megaShrinkZoomHook(Player* player)
{
	player->megaShrunk(); // Keep replaced instruction
	Stage::setZoom(0x1000, 16, player->playerID, 0);
}

ncp_repl(0x02120288, 10, "MOV R1, #0x4B0") // Change Mega Mushroom duration

ncp_repl(0x02011A7C, "NOP") // Do not load Mega Mario music
ncp_repl(0x02120298, 10, "NOP") // Do not play Mega Mario music

// Mega Mushroom doesn't move around
ncp_repl(0x020D37E0, 10, "B 0x020D3818");
ncp_repl(0x020D368C, 10, "B 0x020D3694");
