#include "nsmb.h"

//MENU VARIABLES (AUTO RESET ON SCENE RELOAD)
static u8& SelectedButton = *(u8*)0x020DBB84;
static u8& ButtonClicked = *(u8*)0x020DBB85;
static BOOL& isFirstExecute = *(BOOL*)0x020DBBA0;

void MainMenuScene_InitTopScreen()
{
	GX_ResetBankForSubBG();
	GX_ResetBankForSubOBJ();
	GX_ResetBankForSubBGExtPltt();
	GX_ResetBankForSubOBJExtPltt();

	GXS_SetGraphicsMode(GX_BGMODE_0);
	GX_SetBankForSubBG(GX_VRAM_SUB_BG_128_C);

	G2S_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_256, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x00000);

	nFS_MountArchiveByID(9, 0);
	nFS_LoadLZ77FileByIDToDest(0xC900, (u8*)G2S_GetBG2CharPtr() + 0x4000);
	nFS_LoadLZ77FileByIDToDest(0xC902, G2S_GetBG2ScrPtr());
	void* pal = nFS_LoadFileByID(0xC901);
	GXS_LoadBGPltt(pal, 0, 0x200);
	NSMB_FreeToCurrentHeapIfNotNull(pal);
	nFS_UnmountArchiveByID(9);

	G2S_SetBG1Priority(1);
	G2S_SetBG2Priority(2);
	G2S_SetBG1Offset(0, 0);
	G2S_SetBG2Offset(0, 0);
	G2S_BG1Mosaic(FALSE);
	G2S_BG2Mosaic(FALSE);

	GXS_SetVisiblePlane(GX_PLANEMASK_BG2);
}

void MainMenuScene_InitBottomScreen()
{
	GX_ResetBankForBG();
	GX_ResetBankForOBJ();
	GX_ResetBankForBGExtPltt();
	GX_ResetBankForOBJExtPltt();
	GX_ResetBankForTex();
	GX_ResetBankForTexPltt();
	GX_ResetBankForClearImage();

	//INIT
	GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_2D);
	GX_SetBankForBG(GX_VRAM_BG_128_D);
	GX_SetBankForOBJ(GX_VRAM_OBJ_128_A);
	GX_SetBankForOBJExtPltt(GX_VRAM_OBJEXTPLTT_0_F);

	//BACKGROUND
	G2_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x00000);

	MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
	MIi_CpuClearFast(0x11111111, G2_GetBG2CharPtr(), 0x20);

	*(u32*)HW_BG_PLTT = 0x7FFF << 16;

	//OAM
	nFS_LoadLZ77FileByIDToDest(2087 - 131, (void*)HW_OBJ_VRAM);
	nFS_LoadFileByIDToOBJExtPltt(2044 - 131, 0, true);

	//VISIBILITY
	G2_SetBG1Priority(1);
	G2_SetBG2Priority(2);
	G2_SetBG1Offset(0, 0);
	G2_SetBG2Offset(0, 0);
	G2_BG1Mosaic(FALSE);
	G2_BG2Mosaic(FALSE);

	GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);

	nGX_SetVisiblePlaneSceneStart(GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
}

//OnCreate
int nsub_020D3570_ov_09()
{
	int lastSceneId = *(int*)0x0203BD2C;
	SetSceneFadingArguments(SCENE_INFO, 0, lastSceneId == 0, 0);

	if (lastSceneId != 0)
	{
		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
		MainMenuScene_InitTopScreen();
	}
	else
	{
		u8* screensToFade = (u8*)SCENE_INFO + 1468;
		*screensToFade = 1;
	}

	MainMenuScene_InitBottomScreen();

	//Music_ClearAndLoadSeqWithSoundset(99, 0);
	//Music_PlaySeq(99, 0);

	//Load BNBL and BNCL to heap
	BNBLFilePtr = (BNBLFile*)nFS_LoadFileByIDToCache(2083 - 131, false);
	BNCLFilePtr = (BNCLFile*)nFS_LoadFileByIDToCache(2084 - 131, false);

	if (lastSceneId == 3)
		SelectedButton = *(int*)0x02085A14;

	return 1;
}

extern "C" void SetInventoryPowerupForPlayerSlot(int playerNo, int slot, u8 value);

void MainMenuScene_onButtonClicked()
{
	ButtonClicked = true;

	PlaySNDEffect(0xE9, 0);
	LoadSaveAndSetCounters(0, 0, &saveData);

	for (int i = 0; i < 2; i++)
	{
		SetInventoryPowerupForPlayerSlot(i, 0, 1);
		SetInventoryPowerupForPlayerSlot(i, 1, 0);
		SetInventoryPowerupForPlayerSlot(i, 2, 0);
	}

	int consoleCount = GetConsoleCount();
	int playerNumber = *(int*)0x020887F0;
	int spawnBitmask = consoleCount == 1 ? 1 : 3;
	ChangeSceneToLevel(
		STAGE_INTRO_SCENE,
		0,
		0,
		SelectedButton,
		0,
		playerNumber,
		spawnBitmask,
		0,
		1,
		0,
		0xFF,
		1,
		1,
		0xFF,
		1,
		0,
		0xFFFFFFFF);
}

//OnExecute
int nsub_020D339C_ov_09()
{
	//If fading do not run execution process
	if (!GetSceneFadingFinished(SCENE_INFO))
		return 1;

	if (!isFirstExecute)
	{
		G2S_SetBlendBrightness(0x3F, 0); //Fix brightness bug where bottom screen is darker than top

		s32* fadeColor = &SCENE_INFO[361];
		*fadeColor = -16; //Set fade color to black (forces black fade out)

		//Restore amount of screens to fade out
		u8* screensToFade = (u8*)SCENE_INFO + 1468;
		*screensToFade = 1 | 2;

		isFirstExecute = true;
	}

	int newSelectedLevel = SelectedButton;
	if (*nkeysDown & PAD_KEY_LEFT)
	{
		if (SelectedButton > 0)
			newSelectedLevel--;
	}
	else if (*nkeysDown & PAD_KEY_RIGHT)
	{
		if (SelectedButton < 2)
			newSelectedLevel++;
	}

	if (newSelectedLevel != SelectedButton)
	{
		PlaySNDEffect(0xE5, 0);
		SelectedButton = newSelectedLevel;
	}

	UpdatePenTouchPositions();
	int rect = BNBL().GetRectangleAtPosition(penXDown[0], penYDown[0]);
	if (rect != -1)
	{
		SelectedButton = rect;
		MainMenuScene_onButtonClicked();
	}

	if (nkeysDown[0] & PAD_BUTTON_A)
	{
		MainMenuScene_onButtonClicked();
	}
	if (nkeysDown[0] & PAD_BUTTON_B)
	{
		if(GetConsoleCount() == 1)
			ChangeToScene(MvsL_MAIN_MENU_SCENE, 0);
	}

	return 1;
}

NAKED void nsub_020A19D8_ov_00() { asm("MOV R0, #4\nMOV R1, #0\nB 0x020A19E0"); } //Level exits to titlescreen
int nsub_02152884_ov_36() { return 1; } //Do not draw level intro in the only frame that it shows up
int repl_0215285C_ov_36() { return 0; } //Make level intro have a duration of 0

//OnDraw
int nsub_020CF7BC_ov_09()
{
	for (int i = 0; i < 3; i++)
	{
		int objId = BNCLFilePtr->objs[i].id;

		OAMEntry OAM_OBJ;
		OAM_OBJ.attr0 = ATTR0_SQUARE | ATTR0_COLOR_256;
		OAM_OBJ.attr1 = ATTR1_SIZE_64;
		OAM_OBJ.attr2 = (objId * 0x80) | ATTR2_DATA_END;
		OAM_DrawHUDFromLoadedBNCL(i, &OAM_OBJ, false, objId, 0, 0, 0, 0, 0, 0, 0);

		int sel_pal = (i == SelectedButton ? (ButtonClicked ? 5 : 4) : 3);
		OAM_OBJ.attr2 = (3 * 0x80) | ATTR2_DATA_END;
		OAM_DrawHUDFromLoadedBNCL(i, &OAM_OBJ, false, sel_pal, 0, 0, 0, 0, 0, 0, 0);
	}
	return 1;
}


// BOOT SCENE

NAKED void nsub_020CC730_ov_01() { asm("B 0x020CC738"); } //Boot scene fades out to white
NAKED void nsub_020CCBF0_ov_01() { asm("B 0x020CCD8C"); }
void repl_020CCD8C_ov_01()
{
	WiFi_Init();

	GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
	MainMenuScene_InitTopScreen();

	G2_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000);
	nFS_LoadLZ77FileByIDToDest(1209, (u8*)G2_GetBG2CharPtr());
	nFS_LoadLZ77FileByIDToDest(1210, (u16*)HW_BG_PLTT);
	nFS_LoadLZ77FileByIDToDest(1211, G2_GetBG2ScrPtr());

	//VISIBILITY
	G2_SetBG1Priority(1);
	G2_SetBG2Priority(2);
	G2_SetBG1Offset(0, 0);
	G2_SetBG2Offset(0, 0);
	G2_BG1Mosaic(FALSE);
	G2_BG2Mosaic(FALSE);

	nGX_SetVisiblePlaneSceneStart(GX_PLANEMASK_BG2);
}

u16 repl_020CC5A8_ov_01(u16* timer)
{
	if (*timer)
		--*timer;
	if (*timer == 0x56)
		*timer = 0;
	return *timer;
}

void repl_020CC720_ov_01()
{
	if (*nkeysDown & PAD_BUTTON_A || *penHeld)
	{
		u8* screensToFade = (u8*)SCENE_INFO + 1468;
		*screensToFade = 1;
		ChangeToScene(MAIN_MENU_SCENE, 0);
	}
	else if (*nkeysDown & PAD_BUTTON_B)
	{
		ChangeToScene(MvsL_MAIN_MENU_SCENE, 0);
	}
}

//void nsub_020CCD40_ov_01() { ((u16*)HW_DB_BG_PLTT)[0] = 0x7FFF; asm("B 0x020CCD70"); } //White bottom background
void repl_020CCDDC_ov_01() {} //No coin sound

// THANK YOU FOR PLAYING