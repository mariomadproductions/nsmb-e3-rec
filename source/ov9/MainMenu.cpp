#include "scene/MainMenu.hpp"

#include "nitro/gx.h"
#include "nsmb/game.h"
#include "nsmb/sound.h"
#include "nsmb/graphics/fader.h"
#include "nsmb/graphics/2d/oam.h"
#include "nsmb/system/input.h"
#include "nsmb/system/save.h"
#include "nsmb/system/misc.h"
#include "nsmb/filesystem/file.h"
#include "nsmb/filesystem/cache.h"
#include "nsmb/ui/bnbl.h"
#include "extra/undocumented.hpp"
#include "CustomInventory.hpp"

ObjectProfile MainMenu::profile = {
	&constructObject<MainMenu>,
	4, 12
};

s32 MainMenu::onCreate()
{
	Game::fader.setupSceneFading(Fader::FadingType::FadeOnly, Scene::previousSceneID == 0, false);

	if (Scene::previousSceneID != 0)
	{
		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
		initTopScreen();
	}
	else
	{
		Game::fader.fadingTarget[0] = 1;
	}

	initBottomScreen();

	// SND::loadSounds(99, 0);
	// SND::playBGM(0, false);

	//Load BNBL and BNCL to heap
	BNBL::current = (BNBL::File*)FS::Cache::loadFile(2083 - 131, false);
	BNCL::current = (BNCL::File*)FS::Cache::loadFile(2084 - 131, false);

	if (Scene::previousSceneID == 3)
		selectedButton = Game::stageID;

	return 1;
}

s32 MainMenu::onUpdate()
{
	//If fading do not run execution process
	if (!Game::fader.fadedIn())
		return 1;

	if (!isFirstExecute)
	{
		G2S_SetBlendBrightness(0x3F, 0); //Fix brightness bug where bottom screen is darker than top

		Game::fader.targetBrightness = -16; //Set fade color to black (forces black fade out)

		//Restore amount of screens to fade out
		Game::fader.fadingTarget[0] = 1 | 2;

		isFirstExecute = true;
	}

	int newSelectedLevel = selectedButton;
	u16 keysPressed = Input::getPressedKeys(0);
	if (keysPressed & Keys::Left)
	{
		if (selectedButton > 0)
			newSelectedLevel--;
	}
	else if (keysPressed & Keys::Right)
	{
		if (selectedButton < 2)
			newSelectedLevel++;
	}

	if (newSelectedLevel != selectedButton)
	{
		SND::playSFX(229);
		selectedButton = newSelectedLevel;
	}

	UpdatePenTouchPositions();
	int rect = BNBL::getTouchedRectangleID(BNBL::current);
	if (rect != -1)
	{
		selectedButton = rect;
		onButtonClicked();
	}

	if (keysPressed & Keys::A)
	{
		onButtonClicked();
	}
	if (keysPressed & Keys::B)
	{
		if (GetConsoleCount() == 1)
		{
			Scene::switchScene(SceneID::MvsLMainMenu, 0);
		}
		else
		{
			Multiplayer::endConnection();
			*(int*)0x02085200 = 1; //Reset console count
		}
	}

	return 1;
}

s32 MainMenu::onRender()
{
	for (int i = 0; i < 3; i++)
	{
		int objID = BNCL::current->objs[i].id;

		static GXOamAttr oamObj = OAM::getOBJAttr(0, 0, 0, GX_OAM_MODE_NORMAL, false, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_64x64, GX_OAM_COLOR_256, 0, 0, 0, 0xFFFF);

		oamObj.attr2 = objID * 0x80;
		Game::drawBNCLSprite(i, &oamObj, OAM::Flags::None, objID, 0, 0, 0, 0, OAM::Settings::None, 0, 0);

		int selPal = (i == selectedButton ? (buttonClicked ? 5 : 4) : 3);
		oamObj.attr2 = 3 * 0x80;
		Game::drawBNCLSprite(i, &oamObj, OAM::Flags::None, selPal, 0, 0, 0, 0, OAM::Settings::None, 0, 0);
	}
	return 1;
}

s32 MainMenu::onDestroy()
{
    return 1;
}

void MainMenu::initBottomScreen()
{
	GX_ResetBankForBG();
	GX_ResetBankForOBJ();
	GX_ResetBankForBGExtPltt();
	GX_ResetBankForOBJExtPltt();

	// Init
	GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_2D);
	GX_SetBankForBG(GX_VRAM_BG_128_D);
	GX_SetBankForOBJ(GX_VRAM_OBJ_128_A);
	GX_SetBankForOBJExtPltt(GX_VRAM_OBJEXTPLTT_0_F);

	// Background
	G2_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x00000);

	MIi_CpuClearFast(0, G2_GetBG2ScrPtr(), 0x800);
	MIi_CpuClearFast(0x11111111, G2_GetBG2CharPtr(), 0x20);

	*(u32*)HW_BG_PLTT = 0x7FFF << 16;

	// OAM
	FS::loadFileLZ77(2087 - 131, (void*)HW_OBJ_VRAM);
	FS::loadOBJExtPalette(2044 - 131, 0, true);

	// Visibility
	G2_SetBG1Priority(1);
	G2_SetBG2Priority(2);
	G2_SetBG1Offset(0, 0);
	G2_SetBG2Offset(0, 0);
	G2_BG1Mosaic(false);
	G2_BG2Mosaic(false);

	GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);

	Game::setVisiblePlane(GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
}

void MainMenu::onButtonClicked()
{
	buttonClicked = true;

	SND::playSFX(233);
	Save::loadMainSave(0, 0, &Save::mainSave);

	for (int i = 0; i < 2; i++)
	{
		CustomInventory::setPowerupOnSlot(i, 0, 1);
		CustomInventory::setPowerupOnSlot(i, 1, 0);
		CustomInventory::setPowerupOnSlot(i, 2, 0);
	}

	int consoleCount = GetConsoleCount();
	int playerNumber = *(int*)0x020887F0;
	int spawnBitmask = consoleCount == 1 ? 1 : 3;
	Game::loadLevel(
		SceneID::StageIntro,
		0,
		0,
		selectedButton,
		0,
		playerNumber,
		spawnBitmask,
		0,
		1,
		0,
		-1,
		1,
		1,
		-1,
		1,
		0,
		-1);
}
