#include "nitro_if.h"
#include "nsmb/stage/layout/stagelayout.h"

struct Chunk { u8 data[0x200]; };

constexpr u32 LevelChunkTableSize = 128;

static Chunk** sLevelChunkTable = rcast<Chunk**>(0x020CAFE0);
static Chunk** sLevelChunkTableBak = nullptr;

// Write backup
ncp_jump(0x020AE534, 0)
void writeLevelChunksBackupHook(u16* level)
{
	StageLayout::doLayoutReset = false;

	u16 chunkCount = level[0x232];
	for (u32 i = 0; i < chunkCount; i++)
		MI_CpuCopyFast(sLevelChunkTableBak[i], sLevelChunkTable[i], sizeof(Chunk));

	level[0x237] = level[0x236];
}

// Allocate backup
ncp_repl(0x020B0434, 0, "MOV R0, R7")
ncp_repl(0x020B043C, 0, "B 0x020B04A0")

ncp_call(0x020B0438, 0)
void allocLevelChunksBackupHook(u16* level)
{
	u16 chunkCount = level[0x232];
	if (chunkCount)
	{
		sLevelChunkTableBak = new Chunk*[128];
		for (u32 i = 0; i < chunkCount; i++)
		{
			Chunk* pNewChunk = new Chunk;
			sLevelChunkTableBak[i] = pNewChunk;
			MI_CpuCopyFast(sLevelChunkTable[i], pNewChunk, sizeof(Chunk));
		}
	}
}

// Free backup
ncp_call(0x020BB5E8, 0)
u32 freeLevelChunksBackupHook()
{
	if (sLevelChunkTableBak)
	{
		for (u32 i = 0; i < LevelChunkTableSize; i++)
		{
			delete sLevelChunkTableBak[i];
			sLevelChunkTableBak[i] = nullptr;
		}
		delete[] sLevelChunkTableBak;
		sLevelChunkTableBak = nullptr;
	}

	return 0x020CAD28; // Keep replaced instruction
}
