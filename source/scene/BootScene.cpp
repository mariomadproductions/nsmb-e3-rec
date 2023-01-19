#include "nitro/gx.h"
#include "nsmb/entity/scene.h"
#include "nsmb/graphics/fader.h"
#include "nsmb/filesystem/file.h"
#include "nsmb/system/input.h"
#include "nsmb/system/misc.h"
#include "extra/undocumented.hpp"
#include "MainMenu.hpp"

ncp_repl(0x020CC730, 1, "B 0x020CCAD4") // Boot scene fades out to white

ncp_call(0x020CCBF0, 1)
void repl_020CCBF0_ov_01()
{
	Multiplayer::init();

	GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
	MainMenu::initTopScreen();

	G2_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000);
	FS::loadFileLZ77(1209, (u8*)G2_GetBG2CharPtr());
	FS::loadFileLZ77(1210, (u16*)HW_BG_PLTT);
	FS::loadFileLZ77(1211, G2_GetBG2ScrPtr());

	// Visibility
	G2_SetBG1Priority(1);
	G2_SetBG2Priority(2);
	G2_SetBG1Offset(0, 0);
	G2_SetBG2Offset(0, 0);
	G2_BG1Mosaic(false);
	G2_BG2Mosaic(false);

	Game::setVisiblePlane(GX_PLANEMASK_BG2);
}

ncp_repl(0x020CCBF4, 1, "B 0x020CCD90")

ncp_call(0x020CC5A8, 1)
u16 repl_020CC5A8_ov_01(u16* timer)
{
	if (*timer)
		--*timer;
	if (*timer == 0x56)
		*timer = 0;
	return *timer;
}

ncp_call(0x020CC720, 1)
void repl_020CC720_ov_01()
{
	u32 keysPressed = Input::getPressedKeys(0);
	if (keysPressed & Keys::A || penDown)
	{
		Game::fader.fadingTarget[0] = 1;
		Scene::switchScene(SceneID::TitleScreen, 0);
	}
	else if (keysPressed & Keys::B)
	{
		Scene::switchScene(SceneID::MvsLMainMenu, 0);
	}
}

//void nsub_020CCD40_ov_01() { ((u16*)HW_DB_BG_PLTT)[0] = 0x7FFF; asm("B 0x020CCD70"); } // White bottom background
ncp_repl(0x020CCDDC, 1, "NOP") // No coin sound
