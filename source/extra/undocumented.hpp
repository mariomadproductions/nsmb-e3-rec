#pragma once

#include "nitro/types.h"
#include "nitro/fx/fx.h"
#include "nsmb/filesystem/cache.h"
#include "nsmb/ui/bnbl.h"

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
_ZN4BNBL7currentE = 0x02085888
_ZN4BNCL7currentE = 0x0208588C
_ZN4BNBL10currentSubE = 0x02085890
)");

extern "C" {

void BNXX_InitSub(void* bncd, void* bncl, void* bnbl);
void MvsLDrawBottomScreenProgressPathIcons(void* stageScene, int xShift, int yShift);
void UpdateInventoryPowerup(int playerNo, u8 powerup);
u16 GetSpriteAtPosUsed(fx32 x, fx32 y); // Gets the sprite respawn argument
void SetSpriteAtPosUsed(fx32 x, fx32 y, u16 used); // Sets the sprite respawn argument
int GetConsoleCount();
void UpdatePenTouchPositions();

}

namespace Multiplayer
{
	void init();
	void endConnection();
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
