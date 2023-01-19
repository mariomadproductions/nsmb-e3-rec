#include "nitro/gx.h"
#include "nitro/fx/fx.h"
#include "nsmb/player.h"
#include "nsmb/system/misc.h"
#include "nsmb/filesystem/file.h"
#include "nsmb/filesystem/cache.h"
#include "extra/fx.h"
#include "extra/undocumented.hpp"
#include "CustomInventory.hpp"

ncp_repl(0x020A3568, 0, "BX LR") //Do not update top screen OAM
ncp_repl(0x020A3710, 0, "BX LR") //Do not draw top screen OAM

//Top screen OAM doesn't load extra bottom screen palette
ncp_call(0x0215E860, 54)
void repl_0215E860_ov_36(int fileID) { FS::loadExtFile(fileID, (void*)HW_OBJ_PLTT, 0x200); }

ncp_repl(0x0215F1D8, 54, "NOP") //Do not load a sub OAM palette into cache
ncp_repl(0x020C0530, 0, "NOP") //Do not write a cached sub OAM palette into VRAM

//Bottom Background Setup
ncp_jump(0x020BDAFC, 0)
void nsub_020BDAFC_ov_00()
{
	GX_SetBankForSubBG(GX_VRAM_SUB_BG_32_H);
	GX_SetBankForSubOBJ(GX_VRAM_SUB_OBJ_16_I);
	GXS_SetGraphicsMode(GX_BGMODE_0);

	G2S_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_256, GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000);
	G2S_SetBG3ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_256, GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000);

	FS::loadFileLZ77(2005 - 131, (void*)HW_DB_BG_VRAM);
	FS::loadFileLZ77(2006 - 131, (void*)HW_DB_BG_PLTT);
	FS::loadFileLZ77(2007 - 131, G2S_GetBG2ScrPtr());
	FS::loadFileLZ77(2008 - 131, G2S_GetBG3ScrPtr());

	FS::loadFileLZ77(2057 - 131, (void*)HW_DB_OBJ_VRAM);
	void* objPltt = FS::loadExtFile(2058 - 131);
	GXS_LoadOBJPltt((u8*)objPltt + 0x200, 0, 0x200);
	FS::unloadFile(objPltt);

	G2S_SetBG0Priority(0);
	G2S_SetBG1Priority(1);
	G2S_SetBG2Priority(2);
	G2S_SetBG3Priority(3);
	G2S_SetBG0Offset(0, 0);
	G2S_SetBG1Offset(0, 0);
	G2S_SetBG2Offset(0, 0);
	G2S_SetBG3Offset(0, 0);
	G2S_BG0Mosaic(false);
	G2S_BG1Mosaic(false);
	G2S_BG2Mosaic(false);
	G2S_BG3Mosaic(false);

	GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);

	GXS_SetVisiblePlane(GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ);

	void* bnbl = FS::Cache::loadFile(2055 - 131, false);
	void* bncl = FS::Cache::loadFile(2056 - 131, false);
	BNXX_InitSub(NULL, bncl, bnbl);
}

//Sub OAM Update (simply skip part of it xD)
ncp_repl(0x020C03F4, 0, "B 0x020C04E4")

//OAM entries based on 0x020CA150
static GXOamAttr oam_noItem[] = {
	OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x8, GX_OAM_COLOR_256, 0x63 * 2, 0, 0, 0),
	OAM::getOBJAttr(32, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x8, GX_OAM_COLOR_256, 0x67 * 2, 0, 0, 0),
	OAM::getOBJAttr(48, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x8, GX_OAM_COLOR_256, 0x69 * 2, 0, 0, 0xFFFF)
};

static GXOamAttr oam_mushroomItem[] = {
	OAM::getOBJAttr(480, 224, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_64x64, GX_OAM_COLOR_256, 0x80 * 2, 9, 0, 0xFFFF),
};

static GXOamAttr oam_fireflowerItem[] = {
	OAM::getOBJAttr(480, 224, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_64x64, GX_OAM_COLOR_256, 0xC0 * 2, 9, 0, 0xFFFF),
};

static GXOamAttr* oam_invItems[] = {
	oam_noItem, oam_mushroomItem, oam_fireflowerItem
};

static GXOamAttr oam_touchI[] = {
	OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x16, GX_OAM_COLOR_256, 0x4E * 2, 0, 0, 0),
	OAM::getOBJAttr(32, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x16, GX_OAM_COLOR_256, 0x56 * 2, 0, 0, 0),
	OAM::getOBJAttr(64, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x16, GX_OAM_COLOR_256, 0x5E * 2, 0, 0, 0),
	OAM::getOBJAttr(36, 16, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x8, GX_OAM_COLOR_256, 0x62 * 2, 0, 0, 0xFFFF)
};

static GXOamAttr oam_LevelName_FIELD[] = {
	OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x8, GX_OAM_COLOR_256, 0x6A * 2, 0, 0, 0),
	OAM::getOBJAttr(32, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x8, GX_OAM_COLOR_256, 0x6E * 2, 0, 0, 0xFFFF)
};

static GXOamAttr oam_LevelName_FORTRESS[] = {
	OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x8, GX_OAM_COLOR_256, 0x76 * 2, 0, 0, 0),
	OAM::getOBJAttr(32, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x8, GX_OAM_COLOR_256, 0x7A * 2, 0, 0, 0),
	OAM::getOBJAttr(64, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x8, GX_OAM_COLOR_256, 0x7E * 2, 0, 0, 0xFFFF)
};

static GXOamAttr oam_LevelName_DESERT[] = {
	OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x8, GX_OAM_COLOR_256, 0x6F * 2, 0, 0, 0),
	OAM::getOBJAttr(32, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x8, GX_OAM_COLOR_256, 0x73 * 2, 0, 0, 0),
	OAM::getOBJAttr(48, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x8, GX_OAM_COLOR_256, 0x75 * 2, 0, 0, 0xFFFF)
};

static GXOamAttr* oam_LevelNames[] = {
	oam_LevelName_FIELD,
	oam_LevelName_FORTRESS,
	oam_LevelName_DESERT
};

static void MyDrawBottomScreenLevelName(int* stageScene)
{
	int levelID = *(int*)0x02085A14;
	Game::drawBNCLSpriteSub(11 + levelID, oam_LevelNames[levelID], OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, 0, 0);
}

static void MyDrawBottomScreenPowerups(int* stageScene, int playerNo)
{
	for (int i = 0; i < 3; i++)
	{
		int invItem = CustomInventory::getPowerupOnSlot(playerNo, i);

		int* stageSceneChild = &stageScene[3 * playerNo];
		int xOff = (stageSceneChild[31] >> 12) - *(int*)0x020CC2C4;
		int yOff = -(stageSceneChild[32] >> 12);

		Vec2* scale;
		s16 rotation;
		int yOffAnim;

		Vec2 scale2 = Vec2(0x1000);

		int dropState = ((int*)0x020CC0E0)[playerNo];
		bool somePlayerDropStateCondition = (dropState <= 3);
		if (invItem == 0 || (!somePlayerDropStateCondition && i != CustomInventory::getDroppingSlot(playerNo)))
		{
			scale = &scale2;
			rotation = 0;
			yOffAnim = 0;
		}
		else
		{
			bool showTouch = !(((u8*)0x0208B098)[playerNo] & 1);
			if (stageScene[playerNo + 8] && somePlayerDropStateCondition && showTouch)
				Game::drawBNCLSpriteSub(3 + i, oam_touchI, OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, xOff, yOff);

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
			Game::drawBNCLSpriteSub(
				i,
				oam_invItems[invItem],
				OAM::Flags::None,
				0,
				0,
				scale,
				rotation,
				nullptr,
				OAM::Settings::None,
				xOff,
				yOff + yOffAnim
			);
		}
	}
}

static GXOamAttr* OAM_GetNumber8px(int number)
{
	static GXOamAttr number_8px = OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x16, GX_OAM_COLOR_256, 0, 0, 0, 0xFFFF);
	number_8px.attr2 &= ~0x3FF;
	number_8px.attr2 |= (number * 4);
	return &number_8px;
}

static GXOamAttr* OAM_GetNumber16px(int number)
{
	static GXOamAttr number_16px = OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x16, GX_OAM_COLOR_256, 0, 0, 0, 0xFFFF);
	number_16px.attr2 &= ~0x3FF;
	number_16px.attr2 |= ((number * 8) + 0x28);
	return &number_16px;
}

static void OAM_DrawInvCounterDigits(int rect, int value)
{
	GXOamAttr* digit;
	if (value < 10)
	{
		digit = OAM_GetNumber16px(value);
		Game::drawBNCLSpriteSub(rect, digit, OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, 14, 2);
	}
	else if (value < 100)
	{
		digit = OAM_GetNumber16px((value % 10));
		Game::drawBNCLSpriteSub(rect, digit, OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, 21, 1);
		digit = OAM_GetNumber16px((value / 10));
		Game::drawBNCLSpriteSub(rect, digit, OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, 7, 3);
	}
	else
	{
		digit = OAM_GetNumber16px((value % 10));
		Game::drawBNCLSpriteSub(rect, digit, OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, 28, 0);
		digit = OAM_GetNumber16px(((value / 10) % 10));
		Game::drawBNCLSpriteSub(rect, digit, OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, 14, 2);
		digit = OAM_GetNumber16px((value / 100));
		Game::drawBNCLSpriteSub(rect, digit, OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, 0, 4);
	}
}

static void MyDrawBottomScreenCounters(int playerNo)
{
	//Coins
	s32 coinCount = Game::getPlayerCoins(playerNo);
	OAM_DrawInvCounterDigits(6, coinCount);

	//Timer
	fx32 fx32_timeLeft = *(fx32*)0x020CA8B4;
	u32 timeLeft = FX_Whole(FX_Ceil(fx32_timeLeft));
	OAM_DrawInvCounterDigits(7, timeLeft);

	//Score
	s32 score = Game::getPlayerScore(playerNo);

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
		GXOamAttr* digit = OAM_GetNumber8px(modScore);
		Game::drawBNCLSpriteSub(8, digit, OAM::Flags::None, 0, 0, nullptr, 0, nullptr, OAM::Settings::None, x, i);

		x -= 8;
		divisior *= 10;
	}
}

static GXOamAttr oam_marioHead[] = {
	OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x16, GX_OAM_COLOR_256, 0x3C * 2, 0, 0, 0),
	OAM::getOBJAttr(16, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x16, GX_OAM_COLOR_256, 0x40 * 2, 0, 0, 0),
	OAM::getOBJAttr(0, 16, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x8, GX_OAM_COLOR_256, 0x42 * 2, 0, 0, 0),
	OAM::getOBJAttr(16, 16, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x8, GX_OAM_COLOR_256, 0x44 * 2, 0, 0, 0xFFFF)
};

static GXOamAttr oam_luigiHead[] = {
	OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x16, GX_OAM_COLOR_256, 0x45 * 2, 0, 0, 0),
	OAM::getOBJAttr(16, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x16, GX_OAM_COLOR_256, 0x49 * 2, 0, 0, 0),
	OAM::getOBJAttr(0, 16, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x8, GX_OAM_COLOR_256, 0x4B * 2, 0, 0, 0),
	OAM::getOBJAttr(16, 16, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_8x8, GX_OAM_COLOR_256, 0x4D * 2, 0, 0, 0xFFFF)
};

ncp_over(0x020CA104, 0)
static GXOamAttr* oam_headPtrs[] = { oam_marioHead, oam_luigiHead };

ncp_repl(0x020BE5E8, 0, "MOV R0, #(240-24)") // Progress bar pixel scale
ncp_repl(0x020BE658, 0, "MOV R0, #9") // MvsL progress bar uses my BNCL rectangle index

ncp_call(0x020BE64C, 0)
NTR_NAKED void repl_020BE64C_ov_00() { asm("LDR R1, =0x020CA104\nBX LR"); } // MvsL progress bar uses singleplayer OAM addresses (which are replaced with mine)

ncp_jump(0x020BE600, 0)
NTR_NAKED void nsub_020BE600_ov_00() // Shift progress bar OAM
{
asm(R"(
	BL      _ZN4Game14getPlayerCountEv
	CMP     R0, #1
	MOVNE   R0, R6
	BLNE    _ZN4Game18getPlayerCharacterEl
	BNE     0x020BE604
	MOV     R8, #0
	B       0x020BE610
)");
}

ncp_repl(0x020BE608, 0, "MOVEQ R8, #-2") // Mario head OAM shift
ncp_repl(0x020BE60C, 0, "MOVNE R8, #0") // Luigi head OAM shift

//Sub OAM Draw
ncp_jump(0x020BFE5C, 0)
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
