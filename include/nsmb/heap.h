#pragma once

#include "nitro/types.h"

#define CURRENT_HEAP ((void*)0x0208B72C)
#define TEMPFILE_HEAP ((void*)0x0208B730)

#ifdef __cplusplus
extern "C" {
#endif

	// Allocates block from heap and returns block
	void* NSMB_AllocFromHeap(void* heap, u32 block_szByte, s32 word_align);

	// Frees block to heap
	void NSMB_FreeToHeap(void* heap, void* block);



	// Allocates block from current heap and returns block (NOT FOUND YET)
	//void NSMB_AllocFromCurrentHeap(u32 size);

	// Frees specified heap from current heap handler
	void NSMB_FreeToCurrentHeapIfNotNull(void* block);



	// Allocates block from game heap and returns block
	void* NSMB_AllocFromGameHeap(u32 size);

	// Frees block to game heap
	void NSMB_FreeToGameHeap(void* heap);

	// Loads an overlay or crashes
	void NSMB_LoadOverlayOrPanic(int ovNo);

	// Unloads an overlay
	void NSMB_UnloadOverlay(int ovNo);

	// Creates overlay 53 heap
	void NSMB_CreateOv53Heap();

	// Gets the pointer to overlay 53 heap
	void* NSMB_GetPtrToOv53Heap();

	// Loads a spriteset overlay
	void NSMB_LoadOrUnloadSpriteSetOverlays(u8* overlays, bool load);

#ifdef __cplusplus
}

#endif