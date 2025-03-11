#pragma once

#include <nsmb_nitro.hpp>
#include <nsmb/game/ui/bnbl.hpp>
#include <nsmb/game/ui/bncl.hpp>
#include <nsmb/game/stage/player/player.hpp>
#include <nsmb/core/filesystem/cache.hpp>

// Contains declarations and symbols from the game that
// have not yet been added to the NSMB-Code-Reference

asm(R"(
MvsLDrawBottomScreenProgressPathIcons = 0x020BE674
UpdateInventoryPowerup = 0x020BFFDC
SetSpriteAtPosUsed = 0x020CDB80
GetSpriteAtPosUsed = 0x020CDC4C
UpdatePenTouchPositions = 0x02021808
_ZN5Stage9exitLevelEm = 0x020A189C
Player_checkGroundPound = 0x02113E2C
ActiveColliderDestroyBlocks = 0x020A70A0
GetStartEntranceID = 0x0201F518
TouchedX = 0x0208B4E8
TouchedY = 0x0208B4F4
)");

extern "C" {

void MvsLDrawBottomScreenProgressPathIcons(void* stageScene, int xShift, int yShift);
void UpdateInventoryPowerup(int playerNo, u8 powerup);
u16 GetSpriteAtPosUsed(fx32 x, fx32 y); // Gets the sprite respawn argument
void SetSpriteAtPosUsed(fx32 x, fx32 y, u16 used); // Sets the sprite respawn argument
void UpdatePenTouchPositions();
bool Player_checkGroundPound(Player* player);
void ActiveColliderDestroyBlocks(ActiveCollider* collider, u32 unk1, u32 direction, u32 playerID, u32 unk2);
u32 GetStartEntranceID(u32 playerID);

}

extern u8 TouchedX[2];
extern u8 TouchedY[2];

namespace Stage
{
	void exitLevel(u32 flags = 0);
}
