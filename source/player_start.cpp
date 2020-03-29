#include "nsmb.h"

static int& playerNo = *(int*)0x2085A7C;

static int animState = 0;

//Prepare the animation sequence
void hook_0215E630_ov_36()
{
	u8 isLevelStart = *(u8*)0x02085A5C;
	if (isLevelStart)
	{
		int charForPlayer = GetCharacterForPlayer(playerNo);
		int fileId = charForPlayer ? 1811 - 131 : 1816 - 131;
		nFS_LoadLZ77FileByIDToDest(fileId, (u16*)HW_OBJ_VRAM); //Overwrite VRAM StageBigOAM slot
		animState = 1; //Set animation as loaded
	}
	else
	{
		animState = 0; //Set animation as not loaded
	}
}
//Increment when player is about to move (if function above had set it to 1 then the animation will start)
void hook_020FC3B8_ov_0A() { animState++; }

//Set the animation properties
const int animDuration = 60; //Duration in frames (60 = 1 second)
const int animScaleSpeed = 256; //Speed of the scaling IN animation
const int animStartScale = 0xA00; //OAM scale on first frame
const int animMidScaleExtra = 0x200; //Extra scale before transitioning to end scale (pop out effect intensity)
const int animEndScale = 0x1000; //OAM scale for the rest of the duration after the scale IN animation

//Play animation
void hook_020A2E50_ov_00()
{
	if (animState >= 2) //Only start animation if start conditions are met
	{
		OAMEntry* oam = (OAMEntry*)0x0216F6C8;

		Vec2 oam_scale;
		int oam_palette;

		int animFrame = animState - 2;
		int speededScale = ((animFrame * animScaleSpeed) + animStartScale);
		if (speededScale < (animEndScale + animMidScaleExtra))
		{
			oam_scale.x = speededScale;
			oam_scale.y = speededScale;
			oam_palette = (animFrame < 2) ? 14 : 15;
		}
		else
		{
			oam_scale.x = animEndScale;
			oam_scale.y = animEndScale;

			int charForPlayer = GetCharacterForPlayer(playerNo);
			oam_palette = charForPlayer ? 3 : 1;
		}

		OAM_DrawHUD(oam, 128, 96, 0, oam_palette, 0, &oam_scale, 0, 0, 0);

		if (animState > animDuration)
			animState = -1;

		animState++;
	}
}