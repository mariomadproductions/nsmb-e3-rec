#include "nsmb.h"

void nsub_020A3568_ov_00() {} //Do not update top screen OAM
void nsub_020A3710_ov_00() {} //Do not draw top screen OAM

//Top screen OAM doesn't load extra bottom screen palette
void repl_0215E860_ov_36(int fileID) { nFS_LoadFileByIDToDestWithSize(fileID, (void*)HW_OBJ_PLTT, 0x200); }

void repl_0215F1D8_ov_36() {} //Do not load a sub OAM palette into cache
void repl_020C0530_ov_00() {} //Do not write a cached sub OAM palette into VRAM

//Bottom Background Setup
void nsub_020BDAFC_ov_00()
{
	GX_SetBankForSubBG(GX_VRAM_SUB_BG_32_H);
	GX_SetBankForSubOBJ(GX_VRAM_SUB_OBJ_16_I);
	GXS_SetGraphicsMode(GX_BGMODE_0);

	G2S_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_256, GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000);
	G2S_SetBG3ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_256, GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000);

	nFS_LoadLZ77FileByIDToDest(2005 - 131, (void*)HW_DB_BG_VRAM);
	nFS_LoadLZ77FileByIDToDest(2006 - 131, (void*)HW_DB_BG_PLTT);
	nFS_LoadLZ77FileByIDToDest(2007 - 131, G2S_GetBG2ScrPtr());
	nFS_LoadLZ77FileByIDToDest(2008 - 131, G2S_GetBG3ScrPtr());

	nFS_LoadLZ77FileByIDToDest(2057 - 131, (void*)HW_DB_OBJ_VRAM);
	void* objPltt = nFS_LoadFileByID(2058 - 131);
	GXS_LoadOBJPltt((u8*)objPltt + 0x200, 0, 0x200);
	NSMB_FreeToCurrentHeapIfNotNull(objPltt);

	G2S_SetBG0Priority(0);
	G2S_SetBG1Priority(1);
	G2S_SetBG2Priority(2);
	G2S_SetBG3Priority(3);
	G2S_SetBG0Offset(0, 0);
	G2S_SetBG1Offset(0, 0);
	G2S_SetBG2Offset(0, 0);
	G2S_SetBG3Offset(0, 0);
	G2S_BG0Mosaic(FALSE);
	G2S_BG1Mosaic(FALSE);
	G2S_BG2Mosaic(FALSE);
	G2S_BG3Mosaic(FALSE);

	GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);

	GXS_SetVisiblePlane(GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ);

	void* bnbl = nFS_LoadFileByIDToCache(2055 - 131, false);
	void* bncl = nFS_LoadFileByIDToCache(2056 - 131, false);
	BNXX_InitSub(NULL, bncl, bnbl);
}

//Sub OAM Update (simply skip part of it xD)
NAKED void nsub_020C03F8_ov_00() { asm("B 0x020C0448"); }

extern "C" {
	u8 GetInventoryPowerupForPlayerSlot(int playerNo, int slot);
	u8 GetDroppingSlot(int playerNo);
}

//OAM entries based on 0x020CA150
static OAMEntry oam_noItem[] = {
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(0) | ATTR1_SIZE_16,
		(0x63 * 2)
	},
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(32) | ATTR1_SIZE_8,
		(0x67 * 2)
	},
	{
		OBJ_Y(0) | ATTR0_SQUARE | ATTR0_COLOR_256,
		OBJ_X(48) | ATTR1_SIZE_8,
		(0x69 * 2) | ATTR2_DATA_END
	}
};

static OAMEntry oam_mushroomItem = {
	0xE0 | ATTR0_COLOR_256,
	0xC1E0,
	0x9000 | (0x80 * 2) | ATTR2_DATA_END
};

static OAMEntry oam_fireflowerItem = {
	0xE0 | ATTR0_COLOR_256,
	0xC1E0,
	0x9000 | (0xC0 * 2) | ATTR2_DATA_END
};

static OAMEntry* oam_invItems[] = {
	oam_noItem, &oam_mushroomItem, &oam_fireflowerItem
};

static OAMEntry oam_touchI[] = {
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(0) | ATTR1_SIZE_32,
		(0x4E * 2)
	},
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(32) | ATTR1_SIZE_32,
		(0x56 * 2)
	},
	{
		OBJ_Y(0) | ATTR0_SQUARE | ATTR0_COLOR_256,
		OBJ_X(64) | ATTR1_SIZE_16,
		(0x5E * 2)
	},
	{
		OBJ_Y(16) | ATTR0_SQUARE | ATTR0_COLOR_256,
		OBJ_X(36) | ATTR1_SIZE_8,
		(0x62 * 2) | ATTR2_DATA_END
	}
};

static OAMEntry oam_LevelName_FIELD[] = {
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(0) | ATTR1_SIZE_16,
		(0x6A * 2)
	},
	{
		OBJ_Y(0) | ATTR0_SQUARE | ATTR0_COLOR_256,
		OBJ_X(32) | ATTR1_SIZE_8,
		(0x6E * 2) | ATTR2_DATA_END
	}
};

static OAMEntry oam_LevelName_FORTRESS[] = {
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(0) | ATTR1_SIZE_16,
		(0x76 * 2)
	},
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(32) | ATTR1_SIZE_16,
		(0x7A * 2)
	},
	{
		OBJ_Y(0) | ATTR0_SQUARE | ATTR0_COLOR_256,
		OBJ_X(64) | ATTR1_SIZE_8,
		(0x7E * 2) | ATTR2_DATA_END
	}
};

static OAMEntry oam_LevelName_DESERT[] = {
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(0) | ATTR1_SIZE_16,
		(0x6F * 2)
	},
	{
		OBJ_Y(0) | ATTR0_WIDE | ATTR0_COLOR_256,
		OBJ_X(32) | ATTR1_SIZE_8,
		(0x73 * 2)
	},
	{
		OBJ_Y(0) | ATTR0_SQUARE | ATTR0_COLOR_256,
		OBJ_X(48) | ATTR1_SIZE_8,
		(0x75 * 2) | ATTR2_DATA_END
	}
};

static OAMEntry* oam_LevelNames[] = {
	oam_LevelName_FIELD,
	oam_LevelName_FORTRESS,
	oam_LevelName_DESERT
};

static void MyDrawBottomScreenLevelName(int* stageScene)
{
	int levelID = *(int*)0x02085A14;
	OAM_DrawHUDSubFromLoadedBNCL(11 + levelID, oam_LevelNames[levelID], 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

static void MyDrawBottomScreenPowerups(int* stageScene, int playerNo)
{
	for (int i = 0; i < 3; i++)
	{
		int invItem = GetInventoryPowerupForPlayerSlot(playerNo, i);

		int* stageSceneChild = &stageScene[3 * playerNo];
		int xOff = (stageSceneChild[31] >> 12) - *(int*)0x020CC2C4;
		int yOff = -(stageSceneChild[32] >> 12);

		Vec2* scale;
		s16 rotation;
		int yOffAnim;

		Vec2 scale2 = Vec2(0x1000);

		int dropState = ((int*)0x020CC0E0)[playerNo];
		bool somePlayerDropStateCondition = (dropState <= 3);
		if (invItem == 0 || (!somePlayerDropStateCondition && i != GetDroppingSlot(playerNo)))
		{
			scale = &scale2;
			rotation = 0;
			yOffAnim = 0;
		}
		else
		{
			bool showTouch = !(((u8*)0x0208B098)[playerNo] & 1);
			if (stageScene[playerNo + 8] && somePlayerDropStateCondition && showTouch)
				OAM_DrawHUDSubFromLoadedBNCL(3 + i, oam_touchI, 0, 0, 0, 0, 0, 0, 0, xOff, yOff);

			scale = &((Vec2*)0x020CC14C)[playerNo];
			rotation = *((u16*)0x020CC0D0 + playerNo);
			yOffAnim = *((int*)0x020CC0D8 + playerNo);
		}

		if (invItem == 0)
		{
			xOff += 7;
			yOff += 19;
		}
		else
		{
			xOff += 32;
			yOff += 32;
		}

		if (yOffAnim > -192)
		{
			OAM_DrawHUDSubFromLoadedBNCL(
				i,
				oam_invItems[invItem],
				0,
				0,
				0,
				scale,
				rotation,
				0,
				0,
				xOff,
				yOff + yOffAnim
			);
		}
	}
}

static OAMEntry* OAM_GetNumber(bool small, int number)
{
	if (small)
	{
		static OAMEntry number_8px =
		{
			ATTR0_TALL | ATTR0_COLOR_256,
			ATTR1_SIZE_8,
			ATTR2_DATA_END
		};
		number_8px.attr2 &= ~0x3FF;
		number_8px.attr2 |= (number * 4);
		return &number_8px;
	}
	else
	{
		static OAMEntry number_16px =
		{
			ATTR0_SQUARE | ATTR0_COLOR_256,
			ATTR1_SIZE_16,
			ATTR2_DATA_END
		};
		number_16px.attr2 &= ~0x3FF;
		number_16px.attr2 |= ((number * 8) + 0x28);
		return &number_16px;
	}
}

static void OAM_DrawInvCounterDigits(int rect, int value)
{
	OAMEntry* digit;
	if (value < 10)
	{
		digit = OAM_GetNumber(false, value);
		OAM_DrawHUDSubFromLoadedBNCL(rect, digit, 0, 0, 0, 0, 0, 0, 0, 14, 2);
	}
	else if (value < 100)
	{
		digit = OAM_GetNumber(false, (value % 10));
		OAM_DrawHUDSubFromLoadedBNCL(rect, digit, 0, 0, 0, 0, 0, 0, 0, 21, 1);
		digit = OAM_GetNumber(false, (value / 10));
		OAM_DrawHUDSubFromLoadedBNCL(rect, digit, 0, 0, 0, 0, 0, 0, 0, 7, 3);
	}
	else
	{
		digit = OAM_GetNumber(false, (value % 10));
		OAM_DrawHUDSubFromLoadedBNCL(rect, digit, 0, 0, 0, 0, 0, 0, 0, 28, 0);
		digit = OAM_GetNumber(false, ((value / 10) % 10));
		OAM_DrawHUDSubFromLoadedBNCL(rect, digit, 0, 0, 0, 0, 0, 0, 0, 14, 2);
		digit = OAM_GetNumber(false, (value / 100));
		OAM_DrawHUDSubFromLoadedBNCL(rect, digit, 0, 0, 0, 0, 0, 0, 0, 0, 4);
	}
}

static void MyDrawBottomScreenCounters(int playerNo)
{
	//Coins
	s32 coinCount = GetCoinsForPlayer(playerNo);
	OAM_DrawInvCounterDigits(6, coinCount);

	//Timer
	fx32 fx32_timeLeft = *(fx32*)0x020CA8B4;
	u32 timeLeft = FX_Whole(FX_Ceil(fx32_timeLeft));
	OAM_DrawInvCounterDigits(7, timeLeft);

	//Score
	u32 score = GetScoreForPlayer(playerNo);

	int digitCount = 0;
	int n = score;
	while (n != 0) {
		n = n / 10;
		++digitCount;
	}
	if (digitCount == 0)
		digitCount++;

	int divisior = 1;
	int x = 48;
	for (int i = 0; i < digitCount; i++)
	{
		int modScore = (score / divisior) % 10;
		OAMEntry* digit = OAM_GetNumber(true, modScore);
		OAM_DrawHUDSubFromLoadedBNCL(8, digit, 0, 0, 0, 0, 0, 0, 0, x, i);

		x -= 8;
		divisior *= 10;
	}
}

extern "C"
{
	void MvsLDrawBottomScreenProgressPathIcons(void* stageScene, int x_shift, int y_shift);

	OAMEntry oam_marioHead[] = {
		{
			OBJ_Y(0) | ATTR0_SQUARE | ATTR0_COLOR_256,
			OBJ_X(0) | ATTR1_SIZE_16,
			(0x3C * 2)
		},
		{
			OBJ_Y(0) | ATTR0_TALL | ATTR0_COLOR_256,
			OBJ_X(16) | ATTR1_SIZE_8,
			(0x40 * 2)
		},
		{
			OBJ_Y(16) | ATTR0_WIDE | ATTR0_COLOR_256,
			OBJ_X(0) | ATTR1_SIZE_8,
			(0x42 * 2)
		},
		{
			OBJ_Y(16) | ATTR0_SQUARE | ATTR0_COLOR_256,
			OBJ_X(16) | ATTR1_SIZE_8,
			(0x44 * 2) | ATTR2_DATA_END
		}
	};

	OAMEntry oam_luigiHead[] = {
		{
			OBJ_Y(0) | ATTR0_SQUARE | ATTR0_COLOR_256,
			OBJ_X(0) | ATTR1_SIZE_16,
			(0x45 * 2)
		},
		{
			OBJ_Y(0) | ATTR0_TALL | ATTR0_COLOR_256,
			OBJ_X(16) | ATTR1_SIZE_8,
			(0x49 * 2)
		},
		{
			OBJ_Y(16) | ATTR0_WIDE | ATTR0_COLOR_256,
			OBJ_X(0) | ATTR1_SIZE_8,
			(0x4B * 2)
		},
		{
			OBJ_Y(16) | ATTR0_SQUARE | ATTR0_COLOR_256,
			OBJ_X(16) | ATTR1_SIZE_8,
			(0x4D * 2) | ATTR2_DATA_END
		}
	};
}

int repl_020BE5E8_ov_00() { return 240-24; } //Progress bar pixel scale
NAKED void repl_020BE64C_ov_00() { asm("LDR R1, =0x020CA104\nBX LR"); } //MvsL progress bar uses singleplayer OAM addresses (which are replaced with mine)
NAKED void repl_020BE658_ov_00() { asm("MOV R0, #9\nBX LR"); } //MvsL progress bar uses my BNCL rectangle index
NAKED void nsub_020BE600_ov_00() //Shift progress bar OAM
{
asm(R"(
	BL      GetPlayerCount
	CMP     R0, #1
	MOVNE   R0, R6
	BLNE    GetCharacterForPlayer
	BNE     0x020BE604
	MOV     R8, #0
	B       0x020BE610
)");
}
NAKED void repl_020BE608_ov_00() { asm("MOVEQ R8, #-2\nBX LR"); } //Mario head OAM shift
NAKED void repl_020BE60C_ov_00() { asm("MOVNE R8, #0\nBX LR"); } //Luigi head OAM shift

//Sub OAM Draw
void nsub_020BFE5C_ov_00(int* stageScene, int playerNo)
{
	MyDrawBottomScreenLevelName(stageScene);
	MyDrawBottomScreenPowerups(stageScene, playerNo);
	MyDrawBottomScreenCounters(playerNo);
	MvsLDrawBottomScreenProgressPathIcons(
		stageScene,
		stageScene[3 * playerNo + 31] >> 12,
		-(stageScene[3 * playerNo + 32] >> 12)
	);
}