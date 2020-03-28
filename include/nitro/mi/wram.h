/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     wram.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: wram.h,v $
  Revision 1.17  2006/01/18 02:12:29  kitase_hirotake
  do-indent

  Revision 1.16  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.15  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.14  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.13  2004/03/30 04:50:46  yada
  moved ASSERT from .h to .c

  Revision 1.12  2004/03/25 02:54:10  yada
  made MI_GetWramBank() public to ARM9 side as well.

  Revision 1.11  2004/02/19 08:44:41  yada
  only arrange tab

  Revision 1.10  2004/02/14 04:44:55  yasu
  if SDK_ARM9 -> ifdef SDK_ARM9

  Revision 1.9  2004/02/13 07:03:35  yada
  added MI_GetWramBank

  Revision 1.8  2004/02/13 01:10:39  yada
  added definition for ARM7

  Revision 1.7  2004/02/12 13:33:09  yasu
  include nitro/ioreg.h

  Revision 1.6  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.5  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.4  2003/12/26 05:52:45  yada
  Changes as per unified type rules

  Revision 1.3  2003/12/25 10:28:08  yada
  Changes as per unified type rules MI_WRAM changed to MIWram

  Revision 1.2  2003/12/24 08:08:56  yada
  corrected 'assert'

  Revision 1.1  2003/12/24 07:57:53  yada
  transferred control of WRAM relations from GX to MI


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_WRAM_H_
#define NITRO_MI_WRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/ioreg.h"

//----------------------------------------------------------------
//    enum definition
//
#ifdef SDK_ARM9
typedef enum
{
    MI_WRAM_ARM9_ALL = 0 << REG_GX_VRAMCNT_WRAM_BANK_SHIFT,
    MI_WRAM_1616_1 = 1 << REG_GX_VRAMCNT_WRAM_BANK_SHIFT,
    MI_WRAM_1616_2 = 2 << REG_GX_VRAMCNT_WRAM_BANK_SHIFT,
    MI_WRAM_ARM7_ALL = 3 << REG_GX_VRAMCNT_WRAM_BANK_SHIFT
}
MIWram;
#else  // SDK_ARM9
typedef enum
{
    MI_WRAM_ARM9_ALL = (REG_MI_WVRAMSTAT_WRAM_1_MASK | REG_MI_WVRAMSTAT_WRAM_0_MASK),
    MI_WRAM_1616_1 = (REG_MI_WVRAMSTAT_WRAM_0_MASK),
    MI_WRAM_1616_2 = (REG_MI_WVRAMSTAT_WRAM_1_MASK),
    MI_WRAM_ARM7_ALL = 0
}
MIWram;
#endif // SDK_ARM9


/*---------------------------------------------------------------------------*
  Name:         MI_SetWramBank

  Description:  set common-Wram bank status

  Arguments:    cnt      status of common-Wram.
                   MI_WRAM_ARM9_ALL :  allocate all blocks for ARM9
                   MI_WRAM_1616_1   :  allocate block1 for ARM9, block for ARM7
                   MI_WRAM_1616_2   :  allocate block0 for ARM9, block for ARM7
                   MI_WRAM_ARM7_ALL :  allocate all blocks for ARM7

  Returns:      None.

      *Notice: only ARM9 can set common-Wram status.
               ARM7 can read only.
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
void    MI_SetWramBank(MIWram cnt);
#endif

/*---------------------------------------------------------------------------*
  Name:         MI_GetWramBank

  Description:  get common-Wram bank status

  Arguments:    None.

  Returns:      status of common-Wram.
                   MI_WRAM_ARM9_ALL :  allocate all blocks for ARM9
                   MI_WRAM_1616_1   :  allocate block1 for ARM9, block for ARM7
                   MI_WRAM_1616_2   :  allocate block0 for ARM9, block for ARM7
                   MI_WRAM_ARM7_ALL :  allocate all blocks for ARM7
 *---------------------------------------------------------------------------*/
MIWram  MI_GetWramBank(void);



#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_WRAM_H_ */
#endif
