#include "nsmb/game.h"
#include "nsmb/player.h"
#include "nsmb/graphics/2d/oam.h"
#include "nsmb/filesystem/file.h"

namespace PlayerStartFX {

// Set the animation properties
constexpr int animDuration = 60; // Duration in frames (60 = 1 second)
constexpr int animScaleSpeed = 256; // Speed of the scaling IN animation
constexpr int animStartScale = 0xA00; // OAM scale on first frame
constexpr int animMidScaleExtra = 0x200; // Extra scale before transitioning to end scale (pop out effect intensity)
constexpr int animEndScale = 0x1000; // OAM scale for the rest of the duration after the scale IN animation

int animState = 0;

// Prepare the animation sequence
ncp_hook(0x0215E630, 54)
void loadHook()
{
	u8 isLevelStart = *(u8*)0x02085A5C;
	if (isLevelStart)
	{
		int playerChar = Game::getPlayerCharacter(Game::localPlayerID);
		int fileID = playerChar ? 1811 - 131 : 1816 - 131;
		FS::loadFileLZ77(fileID, (u16*)HW_OBJ_VRAM); // Overwrite VRAM StageBigOAM slot
		animState = 1; // Set animation as loaded
	}
	else
	{
		animState = 0; // Set animation as not loaded
	}
}

// Increment when player is about to move (if function above had set it to 1 then the animation will start)
ncp_jump(0x020FC3B8, 10)
NTR_NAKED void startHook() {asm(R"(
	LDR     R3, =_ZN13PlayerStartFX9animStateE
	LDR     R2, [R3]
	ADD     R2, R2, #1
	STR     R2, [R3]
	MOV     R2, #1
	B       0x020FC3BC
)");}

// Play animation
void update()
{
	if (animState >= 2) //Only start animation if start conditions are met
	{
		GXOamAttr* oam = (GXOamAttr*)0x0216F6C8;

		Vec2 oamScale;
		int oamPalette;

		int animFrame = animState - 2;
		int speededScale = ((animFrame * animScaleSpeed) + animStartScale);
		if (speededScale < (animEndScale + animMidScaleExtra))
		{
			oamScale.x = speededScale;
			oamScale.y = speededScale;
			oamPalette = (animFrame < 2) ? 14 : 15;
		}
		else
		{
			oamScale.x = animEndScale;
			oamScale.y = animEndScale;

			int playerChar = Game::getPlayerCharacter(Game::localPlayerID);
			oamPalette = playerChar ? 3 : 1;
		}

		OAM::draw(oam, 128, 96, OAM::Flags::None, oamPalette, 0, &oamScale, 0, nullptr, OAM::Settings::None);

		if (animState > animDuration)
			animState = -1;

		animState++;
	}
}

ncp_jump(0x020A2E50, 0)
NTR_NAKED void updateHook() {asm(R"(
	MOV   R4, R0
	BL    _ZN13PlayerStartFX6updateEv
	B     0x020A2E54
)");}

}
