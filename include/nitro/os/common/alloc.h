/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     alloc.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: alloc.h,v $
  Revision 1.17  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.16  2005/10/07 06:10:39  yada
  add OS_GetTotalOccupiedSize()

  Revision 1.15  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.14  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.13  2004/11/05 12:33:36  yada
  OS_GetAllocatedSize() -> OS_GetTotalAllocSize()

  Revision 1.12  2004/11/05 10:39:08  yada
  add OS_FreeAllToHeap. and add inlines concerned to that

  Revision 1.11  2004/11/05 06:31:34  yada
  Change type of OS_CheckHeap(): long -> s32 .
  Add OS_GetAllocatedSize(), OS_GetTotalFreeSize(),
  OS_GetMaxFreeSize(), OS_ClearHeap()

  Revision 1.10  2004/11/02 10:23:23  yada
  just fix comment

  Revision 1.9  2004/08/31 01:03:27  yada
  add functions to get/set initial setting in specified arena

  Revision 1.8  2004/07/01 10:45:16  yada
  only add function descriptions

  Revision 1.7  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.6  2004/02/13 10:38:26  yada
  Changed from 6 to 9 arenas.

  Revision 1.5  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.4  2004/01/17 06:21:15  yada
  OSFree 'define' was wrong

  Revision 1.3  2004/01/17 04:35:33  yada
  Corrected definition for the arena specification 'inline'

  Revision 1.2  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.1  2004/01/07 00:22:19  yada
  Initial release.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_ALLOC_H_
#define NITRO_OS_ALLOC_H_

#include "nitro/misc.h"
#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------
// type definition

typedef int OSHeapHandle;
typedef void (*OSAllocVisitor) (void *obj, u32 size);

#define  OS_CURRENT_HEAP_HANDLE       ((OSHeapHandle)-1)

//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_InitAlloc

  Description:  Initializes the arena in which all heaps will reside.
                Reserves some small amount of memory for array of heap
                descriptors.

  Arguments:    id         : arena ID
                arenaStart : beginning addr of arena
                arenaEnd   : ending addr of arena
                maxHeaps   : Maximum number of active heaps that will be
                           : used in lifetime of program

  Returns:      start of real arena, aligned with 32 bytes boundaries, after
                heap array has been allocated
 *---------------------------------------------------------------------------*/
extern void *OS_InitAlloc(OSArenaId id, void *arenaStart, void *arenaEnd, int maxHeaps);

/*---------------------------------------------------------------------------*
  Name:         OS_ClearAlloc

  Description:  Clear heap pointer system remember.
                After calling this, you can call OS_InitAlloc() again.

  Arguments:    id  : arena ID

  Returns:      None
 *---------------------------------------------------------------------------*/
extern void OS_ClearAlloc(OSArenaId id);

/*---------------------------------------------------------------------------*
  Name:         OS_CreateHeap

  Description:  Reserves area of memory from /start/ to /end/ for use as a
                heap.  Initializes heap descriptor and free list.
                Will consume one entry in heap array.

  Arguments:    id    : arena ID
                start : starting addr of heap
                end   : ending addr of heap

  Returns:      If the function succeeds, it returns a new handle to heap
                for use in OS_AllocFromHeap(), OS_FreeToHeap(), etc.
                If the function fails, the return value is -1.
 *---------------------------------------------------------------------------*/
extern OSHeapHandle OS_CreateHeap(OSArenaId id, void *start, void *end);

/*---------------------------------------------------------------------------*
  Name:         OS_DestroyHeap

  Description:  Frees up the descriptor for the /heap/.  Subsequent
                allocation requests from this heap will fail unless another
                heap is created with the same handle.

  Arguments:    id   : arena ID
                heap : handle to a live heap, previously created with OS_CreateHeap().

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void OS_DestroyHeap(OSArenaId id, OSHeapHandle heap);

/*---------------------------------------------------------------------------*
  Name:         OS_AddToHeap

  Description:  Adds an arbitrary block of memory to /heap/.  Used to free
                blocks previously allocated with OS_AllocFixed(), or to
                create non-contiguous heaps.

  Arguments:    id    : arena ID
                heap  : handle to live heap, previously created with OS_CreateHeap().
                start : starting addr of block to add to /heap/
                end   : ending addr of block to add to /heap/

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void OS_AddToHeap(OSArenaId id, OSHeapHandle heap, void *start, void *end);

/*---------------------------------------------------------------------------*
  Name:         OS_SetCurrentHeap

  Description:  Sets OSi_CurrentHeap to /heap/.  All subsequent calls to
                OS_Alloc() will be performed on this heap until another
                call to OS_SetCurrentHeap().

  Arguments:    id   : arena ID
                heap : handle to a heap that was returned from OS_CreateHeap()

  Returns:      previous heap handle.
 *---------------------------------------------------------------------------*/
extern OSHeapHandle OS_SetCurrentHeap(OSArenaId id, OSHeapHandle heap);

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromHeap

  Description:  Allocates /size/ bytes from /heap/. Some additional memory
                will also be consumed from /heap/.

  Arguments:    id   : arena ID
                heap : handle to a heap that was returned from OS_CreateHeap()
                size : size of object to be allocated

  Returns:      a null pointer or a pointer to the allocated space aligned
                with ALIGNMENT bytes boundaries
 *---------------------------------------------------------------------------*/
extern void *OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size);

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFixed

  Description:  Allocates the block of memory specified by /rstart/ and
                /rend/.  Will break up any heap.  Will not check for overlap
                with other fixed blocks.  May create a zero-length heap.

  Arguments:    id     : arena ID
                rstart : pointer to starting addr of block
                rend   : pointer to ending addr of block

  Returns:      a null pointer or a pointer to the allocated space aligned
                with ALIGNMENT bytes boundaries. /rstart/ and /rend/ might be
                adjusted to the boundaries of really allocated region.
 *---------------------------------------------------------------------------*/
extern void *OS_AllocFixed(OSArenaId id, void **rstart, void **rend);

/*---------------------------------------------------------------------------*
  Name:         OS_FreeToHeap

  Description:  Returns obj /ptr/ to /heap/.

  Arguments:    id       :  arena ID
                heap     :  handle to the heap that /ptr/ was allocated from
                ptr      :  pointer to object previously returned from
                            OS_Alloc() or OS_AllocFromHeap().

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void OS_FreeToHeap(OSArenaId id, OSHeapHandle heap, void *ptr);

/*---------------------------------------------------------------------------*
  Name:         OS_FreeAllToHeap

  Description:  free all allocated block in the specified heap

  Arguments:    id       : arena ID
                heap     : handle to the heap

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void OS_FreeAllToHeap(OSArenaId id, OSHeapHandle heap);

/*---------------------------------------------------------------------------*
  Name:         OS_CheckHeap

  Description:  Checks heap sanity for debugging

  Arguments:    id   : arena ID
                heap : handle to a live heap.

  Returns:      -1 if heap is not consistent. Otherwise, returns number
                of bytes available in free.
 *---------------------------------------------------------------------------*/
extern s32 OS_CheckHeap(OSArenaId id, OSHeapHandle heap);

/*---------------------------------------------------------------------------*
  Name:         OS_DumpHeap

  Description:  Dumps statistics and elements of a heap

  Arguments:    id   : arena ID
                heap : handle to a heap.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void OS_DumpHeap(OSArenaId id, OSHeapHandle heap);

/*---------------------------------------------------------------------------*
  Name:         OS_ReferentSize

  Description:  Returns size of payload

  Arguments:    id  : arena ID
                ptr : pointer to object previously returned from OS_Alloc()
                      or OSAllocFromHeap().

  Returns:      size of payload
 *---------------------------------------------------------------------------*/
extern u32 OS_ReferentSize(OSArenaId id, void *ptr);

/*---------------------------------------------------------------------------*
  Name:         OS_VisitAllocated

  Description:  Visits every element of every allocated block of memory,
                calling a routine on each one.

  Arguments:    id      : arena ID
                visitor : function to be called on each cell

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void OS_VisitAllocated(OSArenaId id, OSAllocVisitor visitor);

/*---------------------------------------------------------------------------*
  Name:         OS_GetTotalAllocSize

  Description:  Get sum of allocated block size,
                not including block header.

  Arguments:    id   :  arena ID
                heap :  handle to a heap.

  Returns:      sum of allocated block size
 *---------------------------------------------------------------------------*/
extern u32 OSi_GetTotalAllocSize(OSArenaId id, OSHeapHandle heap, BOOL isHeadInclude);
static inline u32 OS_GetTotalAllocSize(OSArenaId id, OSHeapHandle heap)
{
    return OSi_GetTotalAllocSize(id, heap, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_GetTotalOccupiedSize

  Description:  Get sum of allocated block size,
                including block header.

  Arguments:    id   :  arena ID
                heap :  handle to a heap.

  Returns:      sum of allocated block size
 *---------------------------------------------------------------------------*/
static inline u32 OS_GetTotalOccupiedSize(OSArenaId id, OSHeapHandle heap)
{
    return OSi_GetTotalAllocSize(id, heap, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_GetTotalFreeSize

  Description:  Get sum of free block size,
                not includeing of block header.

  Arguments:    id   :  arena ID
                heap :  handle to a heap.

  Returns:      sum of free block size
 *---------------------------------------------------------------------------*/
extern u32 OS_GetTotalFreeSize(OSArenaId id, OSHeapHandle heap);

/*---------------------------------------------------------------------------*
  Name:         OS_GetMaxFreeSize

  Description:  Get maximun free block size

  Arguments:    id   :  arena ID
                heap :  handle to a heap.

  Returns:      maximum free block size.
 *---------------------------------------------------------------------------*/
extern u32 OS_GetMaxFreeSize(OSArenaId id, OSHeapHandle heap);

/*---------------------------------------------------------------------------*
  Name:         OS_ClearHeap

  Description:  re-initialize heap.

  Arguments:    id   :  arena ID
                heap :  handle to a heap.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void OS_ClearHeap(OSArenaId id, OSHeapHandle heap, void *start, void *end);


//================================================================================
//         convenient functions
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromMain / OS_FreeToMain / OS_FreeAllToMain

  Description:  convenience Alloc/Free for access main memory,
                Main-Processor private
 *---------------------------------------------------------------------------*/
static inline void *OS_AllocFromMain(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_MAIN, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToMain(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_MAIN, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToMain(void)
{
    OS_FreeAllToHeap(OS_ARENA_MAIN, OS_CURRENT_HEAP_HANDLE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromSubPriv / OS_FreeToSubPriv / OS_FreeAllToSubPriv

  Description:  convenience Alloc/Free for access main memory,
                Sub-Processor private
 *---------------------------------------------------------------------------*/
static inline void *OS_AllocFromSubPriv(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_MAIN_SUBPRIV, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToSubPriv(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_MAIN_SUBPRIV, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToSubPriv(void)
{
    OS_FreeAllToHeap(OS_ARENA_MAIN_SUBPRIV, OS_CURRENT_HEAP_HANDLE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromMainEx / OS_FreeToMainEx / OS_FreeAllToMainEx

  Description:  convenience Alloc/Free for extended main memory
 *---------------------------------------------------------------------------*/
static inline void *OS_AllocFromMainEx(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_MAINEX, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToMainEx(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_MAINEX, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToMainEx(void)
{
    OS_FreeAllToHeap(OS_ARENA_MAINEX, OS_CURRENT_HEAP_HANDLE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromITCM / OS_FreeToITCM / OS_FreeAllToITCM

  Description:  convenience Alloc/Free for ITCM
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
static inline void *OS_AllocFromITCM(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_ITCM, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToITCM(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_ITCM, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToITCM(void)
{
    OS_FreeAllToHeap(OS_ARENA_ITCM, OS_CURRENT_HEAP_HANDLE);
}
#endif // SDK_ARM9

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromDTCM / OS_FreeToDTCM / OS_FreeAllToDTCM

  Description:  convenience Alloc/Free for DTCM
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
static inline void *OS_AllocFromDTCM(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_DTCM, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToDTCM(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_DTCM, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToDTCM(void)
{
    OS_FreeAllToHeap(OS_ARENA_DTCM, OS_CURRENT_HEAP_HANDLE);
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromShared / OS_FreeToShared / OS_FreeAllToShared

  Description:  convenience Alloc/Free for shared memory
 *---------------------------------------------------------------------------*/
static inline void *OS_AllocFromShared(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_SHARED, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToShared(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_SHARED, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToShared(void)
{
    OS_FreeAllToHeap(OS_ARENA_SHARED, OS_CURRENT_HEAP_HANDLE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromWramMain / OS_FreeToWramMain / OS_FreeAllToWramMain

  Description:  convenience Alloc/Free for common Work RAM,
                Main-Processor private
 *---------------------------------------------------------------------------*/
static inline void *OS_AllocFromWramMain(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_WRAM_MAIN, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToWramMain(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_WRAM_MAIN, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToWramMain(void)
{
    OS_FreeAllToHeap(OS_ARENA_WRAM_MAIN, OS_CURRENT_HEAP_HANDLE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromWramSub / OS_FreeToWramSub / OS_FreeAllToWramSub

  Description:  convenience Alloc/Free for common Work RAM,
                Sub-Processor private
 *---------------------------------------------------------------------------*/
static inline void *OS_AllocFromWramSub(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_WRAM_SUB, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToWramSub(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_WRAM_SUB, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToWramSub(void)
{
    OS_FreeAllToHeap(OS_ARENA_WRAM_SUB, OS_CURRENT_HEAP_HANDLE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_AllocFromSubPrivWram / OS_FreeToSubPrivWram / OS_FreeAllToSubPrivWram

  Description:  convenience Alloc/Free for Sub-Processor private Work RAM
 *---------------------------------------------------------------------------*/
static inline void *OS_AllocFromSubPrivWram(u32 size)
{
    return OS_AllocFromHeap(OS_ARENA_WRAM_SUBPRIV, OS_CURRENT_HEAP_HANDLE, size);
}
static inline void OS_FreeToSubPrivWram(void *ptr)
{
    OS_FreeToHeap(OS_ARENA_WRAM_SUBPRIV, OS_CURRENT_HEAP_HANDLE, ptr);
}
static inline void OS_FreeAllToSubPrivWram(void)
{
    OS_FreeAllToHeap(OS_ARENA_WRAM_SUBPRIV, OS_CURRENT_HEAP_HANDLE);
}

/*---------------------------------------------------------------------------*
  Name:         OS_Alloc

  Description:  same as OS_AllocFromMain()    (if ARM9)
                same as OS_AllocFromSubPriv() (if ARM7)
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
#  define OS_Alloc( size )   OS_AllocFromMain( (size) )
#else
#  define OS_Alloc( size )   OS_AllocFromSubPriv( (size) )
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_Free

  Description:  same as OS_FreeToMain()    (if ARM9)
                same as OS_FreeToSubPriv() (if ARM7)
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
#  define OS_Free( ptr )     OS_FreeToMain( (ptr) )
#else
#  define OS_Free( ptr )     OS_FreeToSubPriv( (ptr) )
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_FreeAll

  Description:  same as OS_FreeAllToMain()    (if ARM9)
                same as OS_FreeAllToSubPriv() (if ARM7)
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
#  define OS_FreeAll()     OS_FreeAllToMain()
#else
#  define OS_FreeAll()     OS_FreeAllToSubPriv()
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_ALLOC_H_ */
#endif
