/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     card.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: card.h,v $
  Revision 1.10  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.9  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.8  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.7  2004/12/08 08:53:18  yosizaki
  delete CARDi_ReadRomID()

  Revision 1.6  2004/07/19 13:17:18  yosizaki
  change MI_ReadCard.

  Revision 1.5  2004/06/28 02:04:25  yosizaki
  change internal implement.
  (SDK recommends using CARD-API instead of this module)

  Revision 1.4  2004/06/22 01:46:32  yosizaki
  change to use OS_GetConsoleType().

  Revision 1.3  2004/06/03 13:32:24  yosizaki
  add MI_ReadCardID.

  Revision 1.2  2004/05/10 06:23:42  yosizaki
  add MIi_ReadCardAsync() callback param.

  Revision 1.1  2004/04/26 11:04:42  yosizaki
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_CARD_H_
#define NITRO_MI_CARD_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "nitro/os.h"
#include "nitro/card.h"


/******************************************************************************
 * CARD access
 *
 *	These are simple CARD API wrappers for internal Lock/Unlock operations.
 *	Future plan calls for elimination of them in accordance with the shift to the CARD API.
 *
 ******************************************************************************/


// Use the LockID for the MI-CARD function to allocate/release CARD.
void    MIi_LockCard(void);
void    MIi_UnlockCard(void);

// Read the card ID. (Sync)
static inline u32 MI_ReadCardID(void)
{
    u32     ret;
    MIi_LockCard();
    ret = CARDi_ReadRomID();
    MIi_UnlockCard();
    return ret;
}

// Read card. (Sync)
static inline void MIi_ReadCard(u32 dmaNo, const void *src, void *dst, u32 size)
{
    MIi_LockCard();
    /*
     * Changed to use interrupts regardless of whether synchronous or asynchronous in order to guarantee performance as much as possible in the low-level CARD_ReadRom.
     * However, because there are places using this function with interrupts prohibited, a change was made so that CPU transfer is used unconditionally for the synchronous version of MI.
     * (If not multithreaded, the efficiency would be similar)
     */
    (void)dmaNo;
    CARD_ReadRom((MI_DMA_MAX_NUM + 1), src, dst, size);
    MIi_UnlockCard();
}

// Read card data. (Async)
void    MIi_ReadCardAsync(u32 dmaNo, const void *srcp, void *dstp, u32 size,
                          MIDmaCallback callback, void *arg);

// Confirm completion of card data async read.
static inline BOOL MIi_TryWaitCard(void)
{
    return CARD_TryWaitRomAsync();
}

// Wait for card data async read to complete.
static inline void MIi_WaitCard(void)
{
    CARD_WaitRomAsync();
}


#ifdef __cplusplus
} /* extern "C" */
#endif


/* NITRO_MI_CARD_H_ */
#endif
