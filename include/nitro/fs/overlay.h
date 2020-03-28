/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FS - include
  File:     overlay.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: overlay.h,v $
  Revision 1.12  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.11  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.10  2005/01/24 06:34:45  yosizaki
  Revised copyright year notation

  Revision 1.9  2005/01/19 11:36:09  yosizaki
  delete pragma `pack'.

  Revision 1.8  2004/11/17 06:05:09  yosizaki
  delete implement of FS_RegisterOverlayToDebugger.

  Revision 1.7  2004/11/16 06:04:54  yosizaki
  add FS_LoadOverlayImageAsync.

  Revision 1.6  2004/10/18 13:51:28  yosizaki
  add FS_RegisterOverlayToDebugger.

  Revision 1.5  2004/09/17 06:49:32  yosizaki
  fix around commpressed overlay.

  Revision 1.4  2004/09/07 06:36:59  yosizaki
  add umcomp-routine.
  add FS_ClearOverlayImage.

  Revision 1.3  2004/09/04 13:20:06  yosizaki
  add FS_AttachOverlayTable().
  change FSOverlayInfo.

  Revision 1.2  2004/07/13 08:00:35  yosizaki
  add new member to FSOverlayInfo.

  Revision 1.1  2004/07/08 13:46:36  yosizaki
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/


#if	!defined(NITRO_FS_OVERLAY_H_)
#define NITRO_FS_OVERLAY_H_

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/mi.h"


#ifdef __cplusplus
extern "C" {
#endif


/* for FS_LoadOverlay(), FS_UnloadOverlay(), ... */
typedef u32 FSOverlayID;

/* Overlay macro which declares ID of overlay module in *.lcf */
#define	FS_EXTERN_OVERLAY(name)	extern u32 SDK_OVERLAY_ ## name ## _ID[1]

/* Overlay macro which refers ID of overlay module in *.lcf */
#define	FS_OVERLAY_ID(name)	((u32)&(SDK_OVERLAY_ ## name ## _ID))

/* overlay static initializer function */
typedef void (*FSOverlayInitFunc) (void);


/*
 * overlay module information structure.
 * (NitroROM-formatted OVT element)
 */
typedef struct
{
/* protected: */
    u32     id;                        /* own overlay ID (equal to index of OVT element) */
    u8     *ram_address;               /* start-address of overlay */
    u32     ram_size;                  /* size of [text+data] section */
    u32     bss_size;                  /* size of bss section */
    /* static initializer function table */
    FSOverlayInitFunc *sinit_init;
    FSOverlayInitFunc *sinit_init_end;
    u32     file_id;                   /* index as FAT of "rom" archive */
    u32     compressed:24;             /* size of commpressed 'ram_size' */
    u32     flag:8;                    /* multi-purpose flag */
}
FSOverlayInfoHeader;

/*
 * overlay module information structure.
 * (FSOverlayInfoHeader and some extensions)
 */
typedef struct
{
/* private: */
    FSOverlayInfoHeader header;
    MIProcessor target;                /* target processor */
    CARDRomRegion file_pos;            /* region in CARD-ROM */
}
FSOverlayInfo;


/* overlay function **********************************************************/

/*---------------------------------------------------------------------------*
  Name:         FS_LoadOverlayInfo

  Description:  load the information of specified overlay module

  Arguments:    p_ovi       pointer to destination FSOverlayInfo
                target      ARM9 or ARM7
                id          overlay-id (FS_OVERLAY_ID(overlay-name))

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_LoadOverlayInfo(FSOverlayInfo *p_ovi, MIProcessor target, FSOverlayID id);

/*---------------------------------------------------------------------------*
  Name:         FS_GetOverlayTotalSize

  Description:  get total size of overlay module from FSOverlayInfo
                (text section + data section + bss section)

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      total size of overlay module.
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetOverlayTotalSize(const FSOverlayInfo *p_ovi)
{
    return (u32)(p_ovi->header.ram_size + p_ovi->header.bss_size);
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetOverlayImageSize

  Description:  get image size of overlay module from FSOverlayInfo
                (text section + data section)

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      image size of overlay module.
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetOverlayImageSize(const FSOverlayInfo *p_ovi)
{
    return (u32)(p_ovi->header.ram_size);
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetOverlayAddress

  Description:  get start-address of overlay module from FSOverlayInfo.

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      start-address of overlay module.
 *---------------------------------------------------------------------------*/
static inline void *FS_GetOverlayAddress(const FSOverlayInfo *p_ovi)
{
    return p_ovi->header.ram_address;
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetOverlayFileID

  Description:  get file-id which contains an image of overlay module

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      file-id od overlay.
 *---------------------------------------------------------------------------*/
FSFileID FS_GetOverlayFileID(const FSOverlayInfo *p_ovi);

/*---------------------------------------------------------------------------*
  Name:         FS_ClearOverlayImage

  Description:  0-clear the memory where FS_GetOverlayAddress() points,
                and invalidate its region of cache.
                this function is called in FS_LoadOverlayImage().

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_ClearOverlayImage(FSOverlayInfo *p_ovi);

/*---------------------------------------------------------------------------*
  Name:         FS_LoadOverlayImage

  Description:  load the image of overlay module without 'static initializer'.
                by this call, the memory where FS_GetOverlayAddress() points
                is set to rare initial status.

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_LoadOverlayImage(FSOverlayInfo *p_ovi);

/*---------------------------------------------------------------------------*
  Name:         FS_LoadOverlayImageAsync

  Description:  load the image of overlay module without 'static initializer'.
                by this call, the memory where FS_GetOverlayAddress() points
                is set to rare initial status.

  Arguments:    p_ovi       pointer to FSOverlayInfo
                p_file      pointer to FSFile for asynchronous reading

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_LoadOverlayImageAsync(FSOverlayInfo *p_ovi, FSFile *p_file);

/*---------------------------------------------------------------------------*
  Name:         FS_StartOverlay

  Description:  execute 'static initializer'.
                this function needs:
                    the memory where FS_GetOverlayAddress() points is
                    set by data which FS_LoadOverlayImage() makes.

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_StartOverlay(FSOverlayInfo *p_ovi);

/*---------------------------------------------------------------------------*
  Name:         FS_EndOverlay

  Description:  execute 'static unintinalizer'.
                by this function:
                    all the destructors in specified overlay module
                    are removed from global destructor chain and executed.

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_EndOverlay(FSOverlayInfo *p_ovi);

/*---------------------------------------------------------------------------*
  Name:         FS_UnloadOverlayImage

  Description:  unload overlay module

  Arguments:    p_ovi       pointer to FSOverlayInfo

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_UnloadOverlayImage(FSOverlayInfo *p_ovi);

/*---------------------------------------------------------------------------*
  Name:         FS_LoadOverlay

  Description:  load overlay module and initialize

  Arguments:    target      ARM9 or ARM7
                id          overlay-id (FS_OVERLAY_ID(overlay-name))

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_LoadOverlay(MIProcessor target, FSOverlayID id);

/*---------------------------------------------------------------------------*
  Name:         FS_UnloadOverlay

  Description:  unload overlay module and clean up

  Arguments:    target      ARM9 or ARM7
                id          overlay-id (FS_OVERLAY_ID(overlay-name))

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_UnloadOverlay(MIProcessor target, FSOverlayID id);

/*---------------------------------------------------------------------------*
  Name:         FS_AttachOverlayTable

  Description:  attach the overlayinfo-table (OVT) to file-system.
                after setting, FS_LoadOverlayInfo()
                loads overlay-info from specified memory.

  Arguments:    target      ARM9 or ARM7
                ptr         pointer to buffer which contains OVT.
                            if ptr is NULL, reset to default(from CARD).
                len         length of OVT.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_AttachOverlayTable(MIProcessor target, const void *ptr, u32 len);

/*---------------------------------------------------------------------------*
  Name:         FS_RegisterOverlayToDebugger

  Description:  register specified overlay to debugger so that debugger trace
                its runtime information.
                (obsolete)

  Arguments:    p_ovi       ignored
                p_file      ignored

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void FS_RegisterOverlayToDebugger(const FSOverlayInfo *p_ovi, const FSFile *p_file)
{
    (void)p_ovi;
    (void)p_file;
}


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* NITRO_FS_OVERLAY_H_ */
