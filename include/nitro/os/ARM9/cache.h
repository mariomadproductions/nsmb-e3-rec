/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     cache.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: cache.h,v $
  Revision 1.18  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.17  2005/10/14 06:37:35  yada
  let some arguments of functions be const

  Revision 1.16  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.15  2005/01/24 00:23:43  takano_makoto
  fix Copyright header.

  Revision 1.14  2005/01/21 10:40:39  takano_makoto
  Added DC_Unlockdown, DC_UnlockdownAll, IC_Unlockdown, IC_UnlockdownAll.

  Revision 1.13  2004/11/02 09:58:29  yada
  just fix comment

  Revision 1.12  2004/04/07 05:45:59  yada
  (none)

  Revision 1.11  2004/04/07 05:29:40  yada
  (1.10 comment was wrong)
  add explanation for function

  Revision 1.10  2004/04/07 05:05:02  yada
  axf->nef

  Revision 1.9  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.8  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.7  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.6  2004/01/14 08:41:52  yada
  Define different names of cache functions

  Revision 1.5  2003/12/18 01:53:12  yada
  Made corrections.

  Revision 1.4  2003/12/17 11:29:49  yada
  Coded data cache functions.

  Revision 1.3  2003/12/17 09:39:34  nishida_kenji
  small bug fix

  Revision 1.2  2003/12/17 09:28:20  yada
  defined data cache instructions (no contents yet)

  Revision 1.1  2003/12/08 12:22:34  yada
  Initial release.


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_CACHE_H_
#define NITRO_OS_CACHE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"

//===========================================================================
//              DATA CACHE CONTROL
//===========================================================================
/*---------------------------------------------------------------------------*
  Name:         DC_Enable

  Description:  enable data cache

  Arguments:    None

  Returns:      previous state
 *---------------------------------------------------------------------------*/
BOOL    DC_Enable();

/*---------------------------------------------------------------------------*
  Name:         DC_Disable

  Description:  disable data cache

  Arguments:    None

  Returns:      previous stats
 *---------------------------------------------------------------------------*/
BOOL    DC_Disable();

/*---------------------------------------------------------------------------*
  Name:         DC_Restore

  Description:  set state of data cache

  Arguments:    data cache state to be set

  Returns:      previous state
 *---------------------------------------------------------------------------*/
BOOL    DC_Restore(BOOL enable);


//===========================================================================
//              DATA CACHE (for all range)
//===========================================================================
/*---------------------------------------------------------------------------*
  Name:         DC_InvalidateAll

  Description:  invalidate all data cache

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_InvalidateAll(void);

/*---------------------------------------------------------------------------*
  Name:         DC_StoreAll

  Description:  clean all data cache
                (write cache data to memory)

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_StoreAll(void);

/*---------------------------------------------------------------------------*
  Name:         DC_FlushAll

  Description:  clean and invalidate all data cache
                (write cache data to memory, and invalidate cache)

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_FlushAll(void);


//===========================================================================
//              DATA CACHE (for specified range)
//===========================================================================
/*---------------------------------------------------------------------------*
  Name:         DC_InvalidateRange

  Description:  invalidate data cache in specified range

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_InvalidateRange(void *startAddr, u32 nBytes);

/*---------------------------------------------------------------------------*
  Name:         DC_StoreRange

  Description:  clean data cache in specified range
                (write cache data to memory)

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_StoreRange(const void *startAddr, u32 nBytes);

/*---------------------------------------------------------------------------*
  Name:         DC_FlushRange

  Description:  clean and invalidate data cache in specified range
                (write cache data to memory, and invalidate cache)

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_FlushRange(const void *startAddr, u32 nBytes);


//===========================================================================
//              DATA CACHE (for specified range)
//===========================================================================
/*---------------------------------------------------------------------------*
  Name:         DC_TouchRange

  Description:  include specified area to data cache in advance

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_TouchRange(const void *startAddr, u32 nBytes);

/*---------------------------------------------------------------------------*
  Name:         DC_LockdownRange

  Description:  lock specified area to prevent not to release data cache

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_LockdownRange(const void *startAddr, u32 nBytes);

/*---------------------------------------------------------------------------*
  Name:         DC_UnlockdownAll

  Description:  unlock all data cache to enable to release

  Arguments:    none.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_UnlockdownAll(void);

/*---------------------------------------------------------------------------*
  Name:         DC_Unlockdown

  Description:  unlock any data cache to enable to release

  Arguments:    num  - specify number of datablock to unlock.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_Unlockdown(u32 num);

/*---------------------------------------------------------------------------*
  Name:         DC_WaitWriteBufferEmpty

  Description:  wait till write buffer becomes to be empty

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    DC_WaitWriteBufferEmpty(void);


//===========================================================================
//              ALIAS OF DC function
//===========================================================================
/*---------------------------------------------------------------------------*
  Name:         DC_CleanAll

  Description:  alias for DC_StoreAll

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void DC_CleanAll(void)
{
    DC_StoreAll();
}

/*---------------------------------------------------------------------------*
  Name:         DC_CleanAndInvalidateAll

  Description:  alias for DC_FlushAll

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void DC_CleanAndInvalidateAll(void)
{
    DC_FlushAll();
}

/*---------------------------------------------------------------------------*
  Name:         DC_CleanRange

  Description:  alias for DC_StoreRange

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void DC_CleanRange(const void *startAddr, u32 nBytes)
{
    DC_StoreRange(startAddr, nBytes);
}

/*---------------------------------------------------------------------------*
  Name:         DC_CleanAndInvalidateRange

  Description:  alias for DC_FlushRange

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void DC_CleanAndInvalidateRange(const void *startAddr, u32 nBytes)
{
    DC_FlushRange(startAddr, nBytes);
}

//===========================================================================
//              INSTRUCTION CACHE CONTROL
//===========================================================================
/*---------------------------------------------------------------------------*
  Name:         IC_Enable

  Description:  enable instruction cache

  Arguments:    None

  Returns:      previous state
 *---------------------------------------------------------------------------*/
BOOL    IC_Enable();

/*---------------------------------------------------------------------------*
  Name:         IC_Disable

  Description:  disable instruction cache

  Arguments:    None

  Returns:      previous stats
 *---------------------------------------------------------------------------*/
BOOL    IC_Disable();

/*---------------------------------------------------------------------------*
  Name:         IC_Restore

  Description:  set state of instruction cache

  Arguments:    instruction cache state to be set

  Returns:      previous stats
 *---------------------------------------------------------------------------*/
BOOL    IC_Restore(BOOL enable);


//===========================================================================
//              INSTRUCTION CACHE
//===========================================================================
/*---------------------------------------------------------------------------*
  Name:         IC_InvalidateAll

  Description:  invalidate all instruction cache

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    IC_InvalidateAll(void);

/*---------------------------------------------------------------------------*
  Name:         IC_InvalidateRange

  Description:  invalidate instruction cache in specified range

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    IC_InvalidateRange(void *startAddr, u32 nBytes);

/*---------------------------------------------------------------------------*
  Name:         IC_PrefetchRange

  Description:  include specified area to instruction cache in advance

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    IC_PrefetchRange(const void *startAddr, u32 nBytes);

/*---------------------------------------------------------------------------*
  Name:         IC_LockdownRange

  Description:  lock specified area to prevent not to release instruction cache

  Arguments:    startAddr     start address
                nBytes        size (in byte)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    IC_LockdownRange(const void *startAddr, u32 nBytes);

/*---------------------------------------------------------------------------*
  Name:         IC_Unlockdown

  Description:  unlock any instruction cache to enable to release

  Arguments:    num  - specify number of datablock to unlock.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    IC_Unlockdown(u32 num);

/*---------------------------------------------------------------------------*
  Name:         IC_UnlockdownAll

  Description:  unlock all instruction cache to enable to release

  Arguments:    None.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    IC_UnlockdownAll(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_CACHE_H_ */
#endif
