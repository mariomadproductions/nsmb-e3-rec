#pragma once

#include "nitro/types.h"
#include "nitro/fx/fx.h"
#include "nsmb/filesystem/cache.h"
#include "nsmb/ui/bnbl.h"
#include "nsmb/stage/player/player.h"

// Contains declarations and symbols from the game that
// have not yet been added to the NSMB-Code-Reference

asm(R"(
BNXX_InitSub = 0x02004564
MvsLDrawBottomScreenProgressPathIcons = 0x020BE674
UpdateInventoryPowerup = 0x020BFFDC
SetSpriteAtPosUsed = 0x020CDB80
GetSpriteAtPosUsed = 0x020CDC4C
GetConsoleCount = 0x02046C34
UpdatePenTouchPositions = 0x02021808
_ZN5Stage9exitLevelEm = 0x020A189C
_ZN4BNBL7currentE = 0x02085888
_ZN4BNCL7currentE = 0x0208588C
_ZN4BNBL10currentSubE = 0x02085890
Player_checkGroundPound = 0x02113E2C
ActiveColliderDestroyBlocks = 0x020A70A0
GetStartEntranceID = 0x0201F518
)");

extern "C" {

void BNXX_InitSub(void* bncd, void* bncl, void* bnbl);
void MvsLDrawBottomScreenProgressPathIcons(void* stageScene, int xShift, int yShift);
void UpdateInventoryPowerup(int playerNo, u8 powerup);
u16 GetSpriteAtPosUsed(fx32 x, fx32 y); // Gets the sprite respawn argument
void SetSpriteAtPosUsed(fx32 x, fx32 y, u16 used); // Sets the sprite respawn argument
int GetConsoleCount();
void UpdatePenTouchPositions();
bool Player_checkGroundPound(Player* player);
void ActiveColliderDestroyBlocks(ActiveCollider* collider, u32 unk1, u32 direction, u32 playerID, u32 unk2);
u32 GetStartEntranceID(u32 playerID);

}

namespace Multiplayer
{
	void init();
	void endConnection();
}

namespace Stage
{
	void exitLevel(u32 flags = 0);
}

namespace BNBL
{
	extern File* current;
}

namespace BNCL
{
	struct FileObj
	{
		u16 xpos;
		u16 ypos;
		u32 id;
	};

	struct File
	{
		char magic[4];
		u16 padding;
		u16 objCount;
		FileObj objs[];
	};

	extern File* current;
	extern File* currentSub;
}
