#include "BackgroundSwapper.h"

static u8 LastBG = 0;
static u8 LastFG = 0;
static u8 LastTS = 0;

void hook_020BCFCC_ov_00()
{
	u8* PointerToBlock1 = *(u8**)0x0208B168;
	LastBG = PointerToBlock1[6];
	LastFG = PointerToBlock1[18];
	LastTS = PointerToBlock1[12];
}

void BackgroundSwapper_LoadBG(BackgroundSwapper* bgSwapper)
{
	if (bgSwapper->BG_ID != 0xFF)
	{
		u32* BG_NCG_TBL = (u32*)0x020C9454;
		u32* BG_NCL_TBL = (u32*)0x020C9A44;
		u32* BG_NSC_TBL = (u32*)0x020C9914;

		// ==== NCG ====

		nFS_LoadLZ77FileByIDToDest(BG_NCG_TBL[bgSwapper->BG_ID], (u16*)0x6011000);

		// ==== NCL ====

		GX_BeginLoadBGExtPltt();
		nFS_LoadLZ77FileByIDToDest(BG_NCL_TBL[bgSwapper->BG_ID], (void*)(*(int*)0x2094274 + 0x7400 - *(int*)0x2094270));
		GX_EndLoadBGExtPltt();

		// ==== NSC ====

		u16* transferHeap = (u16*)NSMB_AllocFromGameHeap(0x2000);
		nFS_LoadLZ77FileByIDToDest(BG_NSC_TBL[bgSwapper->BG_ID], transferHeap);
		u16* index_ptr = (u16*)G2_GetBG1ScrPtr();
		for (u16 index = 0; index < 32; index++)
		{
			MIi_CpuCopy16(&transferHeap[0x40 * index], index_ptr, 0x40);
			MIi_CpuCopy16(&transferHeap[(index << 6) + 0x20], index_ptr + 0x400, 0x40);
			MIi_CpuCopy16(&transferHeap[(index << 6) + 0x800], index_ptr + 0x800, 0x40);
			MIi_CpuCopy16(&transferHeap[(index << 6) + 0x820], index_ptr + 0xC00, 0x40);
			index_ptr += 32;
		}
		NSMB_FreeToGameHeap(transferHeap);
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

void BackgroundSwapper_LoadFG(BackgroundSwapper* bgSwapper)
{
	if (bgSwapper->FG_ID != 0xFF)
	{
		u32* FG_NCG_TBL = (u32*)0x020C96B4;
		u32* FG_NCL_TBL = (u32*)0x020C9CA4;
		u32* FG_NSC_TBL = (u32*)0x020C97E4;

		// ==== NCG ====

		nFS_LoadLZ77FileByIDToDest(FG_NCG_TBL[bgSwapper->FG_ID], (u16*)0x600C000);

		// ==== NCL ====

		GX_BeginLoadBGExtPltt();
		nFS_LoadLZ77FileByIDToDest(FG_NCL_TBL[bgSwapper->FG_ID], (void*)(*(int*)0x2094274 + 0x7000 - *(int*)0x2094270));
		GX_EndLoadBGExtPltt();

		// ==== NSC ====

		nFS_LoadLZ77FileByIDToDest(FG_NSC_TBL[bgSwapper->FG_ID], G2_GetBG3ScrPtr());
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

void BackgroundSwapper_LoadTS(BackgroundSwapper* bgSwapper)
{
	if (bgSwapper->TS_ID != 0xFF)
	{
		u32* TS_NCG_TBL = (u32*)0x020C9584;
		u32* TS_NCL_TBL = (u32*)0x020C9B74;

		// ==== NCG ====

		nFS_LoadLZ77FileByIDToDest(TS_NCG_TBL[bgSwapper->TS_ID], (u16*)0x6003000);

		// ==== NCL ====

		GX_BeginLoadBGExtPltt();
		nFS_LoadLZ77FileByIDToDest(TS_NCL_TBL[bgSwapper->TS_ID], (void*)(*(int*)0x2094274 + 0x4400 - *(int*)0x2094270));
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

void BackgroundSwapper_DoSwapping(BackgroundSwapper* bgSwapper)
{
	bool swapBG = LastBG != bgSwapper->BG_ID;
	bool swapFG = LastFG != bgSwapper->FG_ID;
	bool swapTS = LastTS != bgSwapper->TS_ID;
	if (!swapBG && !swapFG && !swapTS)
		return;

	int visiblePlane = GX_GetVisiblePlane();
	GX_SetVisiblePlane(
		(visiblePlane & ~(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2)) &
		((GX_PLANEMASK_BG0 * swapTS) | (GX_PLANEMASK_BG1 * swapBG) | (GX_PLANEMASK_BG2 * swapFG))
	);

	if (swapBG)
	{
		BackgroundSwapper_LoadBG(bgSwapper);
		LastBG = bgSwapper->BG_ID;
	}

	if (swapFG)
	{
		BackgroundSwapper_LoadFG(bgSwapper);
		LastFG = bgSwapper->FG_ID;
	}

	if (swapTS)
	{
		BackgroundSwapper_LoadTS(bgSwapper);
		LastTS = bgSwapper->TS_ID;
	}

	GX_SetVisiblePlane(visiblePlane);
}

void BackgroundSwapper_CheckIfClose(BackgroundSwapper* bgSwapper)
{
	PlayerActor* player = GetPtrToPlayerActor();
	int XDistToSprite = MATH_ABS(bgSwapper->actor.position.x - player->actor.position.x);
	int YDistToSprite = MATH_ABS(bgSwapper->actor.position.y - player->actor.position.y);

	XDistToSprite /= 0x1000;
	YDistToSprite /= 0x1000;

	if (XDistToSprite < 128 &&
		YDistToSprite < 96)
	{
		BackgroundSwapper_DoSwapping(bgSwapper);
	}
}

//MAIN ACTOR START ---------------------------------------------

extern "C"
{
	extern const u32 BackgroundSwapper_ActorSize = sizeof(BackgroundSwapper);

	int BackgroundSwapper_OnCreate(BackgroundSwapper* bgSwapper)
	{
		u32 spriteData = bgSwapper->actor.base.spriteData;

		bgSwapper->BG_ID = (spriteData) & 0xFF;
		bgSwapper->FG_ID = (spriteData >> 8) & 0xFF;
		bgSwapper->TS_ID = (spriteData >> 16) & 0xFF;

		BackgroundSwapper_CheckIfClose(bgSwapper);
		return 1;
	}

	int BackgroundSwapper_OnExecute(BackgroundSwapper* bgSwapper)
	{
		if (enemyActor_deleteIfOutOfRange(bgSwapper, 0))
			return 1;

		BackgroundSwapper_CheckIfClose(bgSwapper);
		return 1;
	}

	int BackgroundSwapper_OnDraw(BackgroundSwapper* bgSwapper)
	{
		return 1;
	}

	int BackgroundSwapper_OnDelete(BackgroundSwapper* bgSwapper)
	{
		return 1;
	}
}