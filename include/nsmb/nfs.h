#pragma once

#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

	// Loads a file by ID and returns it's heap
	void* nFS_LoadFileByID(u32 id);

	// Writes a file by ID to the destination
	void nFS_LoadFileByIDToDest(u32 id, void* dest);

	// Writes a file by ID to the destination (only writes the specified size)
	void nFS_LoadFileByIDToDestWithSize(u32 id, void* dest, u32 size);

	// Writes a file by path to the destination (only writes the specified size)
	void nFS_LoadFileByNameToDestWithSize(const char* path, void* dest, u32 size);

	// Loads a compressed file by ID and returns it's heap
	void* nFS_LoadLZ77FileByID(u32 id);

	// Writes a compressed file by ID to the destination
	void nFS_LoadLZ77FileByIDToDest(u32 id, void* dest);

	// Gets the file ID from path
	u32 nFS_GetFileIDFromPath(const char* path);

	// Gets pointer to cached file heap
	void* nFS_GetPtrToCachedFile(u32 id);

	// Gets pointer to cached file entry
	void* nFS_GetPtrToCachedFileEntry(u32 id);

	// Loads a file by ID into cache and returns the loaded file
	void* nFS_LoadFileByIDToCache(u32 id, BOOL isHeaderLessLZ77);

	// Loads a file by ID into cache to spriteset 16 var address (used by final boss)
	void nFS_LoadFileByIDToCache_IntoSpriteSet16VarAddress(u32 id, BOOL isHeaderLessLZ77);

	// Unloads a file by ID from cache
	void nFS_UnloadFileByIDFromCache(u32 id);

	// Loads an archive by ID
	void nFS_MountArchiveByID(u32 id, void* destHeap);

	// Unloads an archive by ID
	void nFS_UnmountArchiveByID(u32 id);

	// Loads an OBJ extended palette to it's destination
	void nFS_LoadFileByIDToOBJExtPltt(u32 id, u32 destSlotAddr, BOOL isHeaderLessLZ77);

	// Writes a cached OBJ to it's destination
	void nFS_WriteCachedFileByIDToOBJ(u32 id, u32 destSlotAddr);

	// Writes a cached OBJ extended palette to it's destination
	void nFS_WriteCachedFileByIDToOBJExtPltt(u32 id, u32 destSlotAddr);

#ifdef __cplusplus
}
#endif