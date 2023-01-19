#include "MainMenu.hpp"

#include "nsmb/filesystem/archive.h"

void MainMenu::initTopScreen()
{
	GX_ResetBankForSubBG();
	GX_ResetBankForSubOBJ();
	GX_ResetBankForSubBGExtPltt();
	GX_ResetBankForSubOBJExtPltt();

	GXS_SetGraphicsMode(GX_BGMODE_0);
	GX_SetBankForSubBG(GX_VRAM_SUB_BG_128_C);

	G2S_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_256, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x00000);

	FS::Archive::mountBack(9, nullptr);
	FS::loadFileLZ77(0xC900, (u8*)G2S_GetBG2CharPtr() + 0x4000);
	FS::loadFileLZ77(0xC902, G2S_GetBG2ScrPtr());
	void* pal = FS::loadExtFile(0xC901);
	GXS_LoadBGPltt(pal, 0, 0x200);
	FS::unloadFile(pal);
	FS::Archive::unmount(9);

	G2S_SetBG1Priority(1);
	G2S_SetBG2Priority(2);
	G2S_SetBG1Offset(0, 0);
	G2S_SetBG2Offset(0, 0);
	G2S_BG1Mosaic(false);
	G2S_BG2Mosaic(false);

	GXS_SetVisiblePlane(GX_PLANEMASK_BG2);
}

// Level exits to titlescreen
ncp_repl(0x020A19D8, 0, R"(
	MOV R0, #4
	MOV R1, #0
)")

// Do not draw level intro in the only frame that it shows up
ncp_repl(0x02152884, 54, R"(
	MOV R0, #1
	BX  LR
)")

// Make level intro have a duration of 0
ncp_repl(0x02152840, 54, R"(
	PUSH {LR}
	LDR  R1, [R0,#8]
	MOV  R0, #3
	BL   _ZN5Scene11switchSceneEtm
	MOV  R0, #1
	POP  {PC}
)")
