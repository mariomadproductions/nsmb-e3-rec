#include "e3rec/MainMenu.hpp"

#include <nsmb/core/filesystem/file.hpp>

#include "e3rec/files.hpp"

constexpr u32 TitleLogo_NCG = "e3rec/UE_title_ncg.bin"fid;
constexpr u32 TitleLogo_NCL = "e3rec/UE_title_ncl.bin"fid;
constexpr u32 TitleLogo_NSC = "e3rec/UE_title_nsc.bin"fid;

void MainMenu::initTopScreen()
{
	GX_ResetBankForSubBG();
	GX_ResetBankForSubOBJ();
	GX_ResetBankForSubBGExtPltt();
	GX_ResetBankForSubOBJExtPltt();

	GXS_SetGraphicsMode(GX_BGMODE_0);
	GX_SetBankForSubBG(GX_VRAM_SUB_BG_128_C);

	G2S_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_256, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x00000);

	E3Rec::withGameFileIDs([] {
		FS::loadFileLZ77(TitleLogo_NCG, rcast<u8*>(G2S_GetBG2CharPtr()) + 0x4000);
		FS::loadFileLZ77(TitleLogo_NSC, G2S_GetBG2ScrPtr());
		void* pal = FS::loadExtFile(TitleLogo_NCL);
		GXS_LoadBGPltt(pal, 0, 0x200);
		FS::unloadFile(pal);
	});

	G2S_SetBG1Priority(1);
	G2S_SetBG2Priority(2);
	G2S_SetBG1Offset(0, 0);
	G2S_SetBG2Offset(0, 0);
	G2S_BG1Mosaic(false);
	G2S_BG2Mosaic(false);

	GXS_SetVisiblePlane(GX_PLANEMASK_BG2);
}
