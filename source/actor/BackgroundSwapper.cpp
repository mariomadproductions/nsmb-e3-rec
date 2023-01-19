#include "BackgroundSwapper.hpp"

#include "nitro/gx.h"
#include "nitro/mi/memory.h"
#include "nsmb/filesystem/file.h"

static u8 LastBG = 0;
static u8 LastFG = 0;
static u8 LastTS = 0;

ncp_hook(0x020BCFCC, 0)
void hook_020BCFCC_ov_00()
{
	u8* PointerToBlock1 = *(u8**)0x0208B168;
	LastBG = PointerToBlock1[6];
	LastFG = PointerToBlock1[18];
	LastTS = PointerToBlock1[12];
}

ActorProfile BackgroundSwapper::profile = {
	&constructObject<BackgroundSwapper>,
	0xFB, 0x69,
	nullptr
};

s32 BackgroundSwapper::onCreate()
{
	BG_ID = settings & 0xFF;
	FG_ID = (settings >> 8) & 0xFF;
	TS_ID = (settings >> 16) & 0xFF;

	checkIfClose();
	return 1;
}

s32 BackgroundSwapper::onUpdate()
{
	if (destroyInactive(0))
		return 1;

	checkIfClose();
	return 1;
}

void BackgroundSwapper::loadBG()
{
	if (BG_ID != 0xFF)
	{
		u32* BG_NCG_TBL = (u32*)0x020C9454;
		u32* BG_NCL_TBL = (u32*)0x020C9A44;
		u32* BG_NSC_TBL = (u32*)0x020C9914;

		// ==== NCG ====

		FS::loadFileLZ77(BG_NCG_TBL[BG_ID], (u16*)0x6011000);

		// ==== NCL ====

		GX_BeginLoadBGExtPltt();
		FS::loadFileLZ77(BG_NCL_TBL[BG_ID], (void*)(*(int*)0x2094274 + 0x7400 - *(int*)0x2094270));
		GX_EndLoadBGExtPltt();

		// ==== NSC ====

		u16* transferHeap = new u16[0x2000 / sizeof(u16)];
		FS::loadFileLZ77(BG_NSC_TBL[BG_ID], transferHeap);
		u16* index_ptr = (u16*)G2_GetBG1ScrPtr();
		for (u16 index = 0; index < 32; index++)
		{
			MIi_CpuCopy16(&transferHeap[0x40 * index], index_ptr, 0x40);
			MIi_CpuCopy16(&transferHeap[(index << 6) + 0x20], index_ptr + 0x400, 0x40);
			MIi_CpuCopy16(&transferHeap[(index << 6) + 0x800], index_ptr + 0x800, 0x40);
			MIi_CpuCopy16(&transferHeap[(index << 6) + 0x820], index_ptr + 0xC00, 0x40);
			index_ptr += 32;
		}
		delete[] transferHeap;
	}
	else
	{
		MIi_CpuClearFast(0, (u8*)0x6011000, 0x5000); //Clear NCG

		//Clear NCL
		GX_BeginLoadBGExtPltt();
		MIi_CpuClearFast(0, (void*)(*(int*)0x2094274 + 0x7400 - *(int*)0x2094270), 0x400);
		GX_EndLoadBGExtPltt();

		MIi_CpuClearFast(0xA240A240, G2_GetBG1ScrPtr(), 0x2000); //Clear NSC
	}
}

void BackgroundSwapper::loadFG()
{
	if (FG_ID != 0xFF)
	{
		u32* FG_NCG_TBL = (u32*)0x020C96B4;
		u32* FG_NCL_TBL = (u32*)0x020C9CA4;
		u32* FG_NSC_TBL = (u32*)0x020C97E4;

		// ==== NCG ====

		FS::loadFileLZ77(FG_NCG_TBL[FG_ID], (u16*)0x600C000);

		// ==== NCL ====

		GX_BeginLoadBGExtPltt();
		FS::loadFileLZ77(FG_NCL_TBL[FG_ID], (void*)(*(int*)0x2094274 + 0x7000 - *(int*)0x2094270));
		GX_EndLoadBGExtPltt();

		// ==== NSC ====

		FS::loadFileLZ77(FG_NSC_TBL[FG_ID], G2_GetBG3ScrPtr());
	}
	else
	{
		MIi_CpuClearFast(0, (u8*)0x600C000, 0x5000); //Clear NCG

		//Clear NCL
		GX_BeginLoadBGExtPltt();
		MIi_CpuClearFast(0, (void*)(*(int*)0x2094274 + 0x7000 - *(int*)0x2094270), 0x400);
		GX_EndLoadBGExtPltt();

		MIi_CpuClearFast(0x81008100, G2_GetBG3ScrPtr(), 0x2000); //Clear NSC
	}
}

void BackgroundSwapper::loadTS()
{
	if (TS_ID != 0xFF)
	{
		u32* TS_NCG_TBL = (u32*)0x020C9584;
		u32* TS_NCL_TBL = (u32*)0x020C9B74;

		// ==== NCG ====

		FS::loadFileLZ77(TS_NCG_TBL[TS_ID], (u16*)0x6003000);

		// ==== NCL ====

		GX_BeginLoadBGExtPltt();
		FS::loadFileLZ77(TS_NCL_TBL[TS_ID], (void*)(*(int*)0x2094274 + 0x4400 - *(int*)0x2094270));
		GX_EndLoadBGExtPltt();
	}
	else
	{
		MIi_CpuClearFast(0, (u8*)0x6003000, 0x7000); //Clear NCG

		//Clear NCL
		GX_BeginLoadBGExtPltt();
		MIi_CpuClearFast(0, (void*)(*(int*)0x2094274 + 0x4400 - *(int*)0x2094270), 0x800);
		GX_EndLoadBGExtPltt();
	}
}

void BackgroundSwapper::doSwapping()
{
	bool swapBG = LastBG != BG_ID;
	bool swapFG = LastFG != FG_ID;
	bool swapTS = LastTS != TS_ID;
	if (!swapBG && !swapFG && !swapTS)
		return;

	int visiblePlane = GX_GetVisiblePlane();
	GX_SetVisiblePlane(
		(visiblePlane & ~(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2)) |
		((GX_PLANEMASK_BG0 * swapTS) | (GX_PLANEMASK_BG1 * swapBG) | (GX_PLANEMASK_BG2 * swapFG))
	);

	if (swapBG)
	{
		loadBG();
		LastBG = BG_ID;
	}

	if (swapFG)
	{
		loadFG();
		LastFG = FG_ID;
	}

	if (swapTS)
	{
		loadTS();
		LastTS = TS_ID;
	}

	GX_SetVisiblePlane(visiblePlane);
}

void BackgroundSwapper::checkIfClose()
{
	Player* player = Game::getLocalPlayer();
	int XDistToSprite = MATH_ABS(position.x - player->position.x);
	int YDistToSprite = MATH_ABS(position.y - player->position.y);

	XDistToSprite /= 0x1000;
	YDistToSprite /= 0x1000;

	if (XDistToSprite < 128 && YDistToSprite < 96)
		doSwapping();
}
