#include "nsmb.h"

//void repl_020AE540_ov_00() { asm("MOV R1, #1"); } //Enable stage resets
//int repl_020B0438_ov_00() { return 1; } //Load stage reset

typedef u16 Chunk[256];
static Chunk* (*pLevelChunks)[128] = (Chunk * (*)[128])0x020CAFE0;
static Chunk* (*pLevelChunksBak)[128] = nullptr;

// Write backup
void nsub_020AE534_ov_00(u16* level)
{
	u8* resetStage = (u8*)0x020CAC98;
	*resetStage = 0;

	u16 chunkCount = level[0x232];
	if (chunkCount)
	{
		for (int i = 0; i < chunkCount; i++)
		{
			MI_CpuCopyFast((*pLevelChunksBak)[i], (*pLevelChunks)[i], 0x200);
		}
	}
	level[0x237] = level[0x236];
}

// Allocate backup
void repl_020B0434_ov_00() { asm("MOV R0, R7"); }
void nsub_020B043C_ov_00() { asm("B 0x020B04A0"); }
void repl_020B0438_ov_00(u16* level)
{
	u16 chunkCount = level[0x232];
	if (chunkCount)
	{
		pLevelChunksBak = (Chunk * (*)[128])NSMB_AllocFromHeap(*CURRENT_HEAP, 0x200, 4);
		for (int i = 0; i < chunkCount; i++)
		{
			Chunk* pNewChunk = (Chunk*)NSMB_AllocFromHeap(*CURRENT_HEAP, 0x200, 4);
			(*pLevelChunksBak)[i] = pNewChunk;
			MI_CpuCopyFast((*pLevelChunks)[i], pNewChunk, 0x200);
		}
	}
}

// Free backup
int repl_020BB5E8_ov_00()
{
	if (pLevelChunksBak)
	{
		for (u16 i = 0; i < 128; i++)
		{
			Chunk* chunk = (*pLevelChunksBak)[i];
			if (chunk)
				NSMB_FreeToHeap(*CURRENT_HEAP, chunk);
			(*pLevelChunksBak)[i] = nullptr;
		}
		pLevelChunksBak = nullptr;
	}

	return 0x020CAD28; //Keep replaced instruction
}