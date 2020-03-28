/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PAD - include
  File:     pad.h

  Copyright 2003-2005,2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: pad.h,v $
  Revision 1.11  2007/08/24 04:34:49  okubata_ryoma
  Fix related to headerfiles.

  Revision 1.10  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.9  2005/02/28 05:26:29  yosizaki
  do-indent.

  Revision 1.8  2004/08/06 12:43:20  yada
  Changed key interrupt logic enum

  Revision 1.7  2004/08/06 05:13:20  yada
  Changed PAD_SetIrq to PADi_SetIrq, PAD_ClearIrq to PADi_ClearIrq

  Revision 1.6  2004/06/11 11:21:57  terui
  Reversed bit logic of open/close detection function.

  Revision 1.5  2004/06/11 11:04:59  terui
  Added definition and function regarding open/close determination.

  Revision 1.4  2004/04/13 07:45:56  yada
  Corrected mask value in interrupt key setting

  Revision 1.3  2004/04/07 02:03:17  yada
  Fixed header comment

  Revision 1.2  2004/03/16 13:03:42  takano_makoto
  Added DEBUG button.

  Revision 1.1  2004/02/18 01:23:28  yada
  Moved the pad region to the region shared by ARM7/9

  Revision 1.16  2004/02/17 09:22:03  yada
  Support for ARM7

  Revision 1.15  2004/02/12 10:56:04  yasu
  New location of include files ARM9/ARM7

  Revision 1.14  2004/02/05 07:09:03  yasu
  Changed SDK prefix iris -> nitro

  Revision 1.13  2004/01/17 02:28:38  nishida_kenji
  Converted 'inline' to 'static inline' in header files

  Revision 1.12  2004/01/08 12:03:21  yada
  Revised key interrupt definition.

  Revision 1.11  2003/12/26 05:52:02  yada
  Changes as per unified type rules

  Revision 1.10  2003/12/25 10:55:08  yada
  Changes as per unified type rules

  Revision 1.9  2003/12/25 00:19:29  nishida_kenji
  Converted INLINE to inline

  Revision 1.8  2003/12/11 08:00:31  yada
  Revised enum definition. Made enable flag BOOL type.

  Revision 1.7  2003/12/01 10:39:04  yada
  Changed PAD_SetInterrupt() to PAD_SetIRQ(), and changed PAD_ClearInterrupt() to PAD_ClearIRQ().

  Revision 1.6  2003/11/14 04:56:01  yada
  Changed the register access macro from REG_XXX to reg_XXX.

  Revision 1.5  2003/11/12 12:02:09  yada
  Comment revision. Revised included files.

  Revision 1.4  2003/11/10 07:59:47  yada
  Inverted input from the pad.

  Revision 1.3  2003/11/05 01:03:31  yada
  Made the cast more strict. For now made it so at least no warnings appear.

  Revision 1.2  2003/10/30 11:42:57  yada
  Decided to use REGTypexx in the register type.

  Revision 1.1  2003/10/30 07:41:13  yada
  Initial version created

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PAD_PAD_H_
#define NITRO_PAD_PAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/hw/common/mmap_shared.h"
#ifdef SDK_ARM9
#include "nitro/hw/ARM9/ioreg_PAD.h"
#else  // SDK_ARM9
#include "nitro/hw/ARM7/ioreg_PAD.h"
#endif // SDK_ARM9

//================================================================================
//    BUTTONS

//---- masked value
#define PAD_PLUS_KEY_MASK       0x00f0 // mask: +Control Pad keys
#define PAD_BUTTON_MASK         0x2f0f // mask: buttons
#define PAD_DEBUG_BUTTON_MASK   0x2000 // mask: debug button
#define PAD_ALL_MASK            0x2fff // mask: all buttons
#define PAD_RCNTPORT_MASK       0x2c00 // mask: factors ARM7 can read from RCNT register
#define PAD_KEYPORT_MASK        0x03ff // mask: factors ARM7/9 can read from KEY register

#define PAD_DETECT_FOLD_MASK    0x8000 // mask: folding

//---- buttons and keys
#define PAD_BUTTON_A            0x0001 // A
#define PAD_BUTTON_B            0x0002 // B
#define PAD_BUTTON_SELECT       0x0004 // SELECT
#define PAD_BUTTON_START        0x0008 // START
#define PAD_KEY_RIGHT           0x0010 // +Control Pad Right
#define PAD_KEY_LEFT            0x0020 // +Control Pad Left
#define PAD_KEY_UP              0x0040 // +Control Pad Up
#define PAD_KEY_DOWN            0x0080 // +Control Pad Down
#define PAD_BUTTON_R            0x0100 // R
#define PAD_BUTTON_L            0x0200 // L
#define PAD_BUTTON_X            0x0400 // X
#define PAD_BUTTON_Y            0x0800 // Y
#define PAD_BUTTON_DEBUG        0x2000 // Debug button

/*---------------------------------------------------------------------------*
  Name:         PAD_Read

  Description:  read pad data.
                X and Y button data from ARM7 are added.

  Arguments:    None.

  Returns:      pad data.
                See above defines to know the meaning of each bit.
 *---------------------------------------------------------------------------*/
static inline u16 PAD_Read(void)
{
    return (u16)(((reg_PAD_KEYINPUT | *(vu16 *)HW_BUTTON_XY_BUF) ^
                  (PAD_PLUS_KEY_MASK | PAD_BUTTON_MASK)) & (PAD_PLUS_KEY_MASK | PAD_BUTTON_MASK));
}

/*---------------------------------------------------------------------------*
  Name:         PAD_DetectFold

  Description:  Detect closing of Nitro console.

  Arguments:    None.

  Returns:      TRUE if closed, FALSE if not.
 *---------------------------------------------------------------------------*/
static inline BOOL PAD_DetectFold(void)
{
    return (BOOL)((*(vu16 *)HW_BUTTON_XY_BUF & PAD_DETECT_FOLD_MASK) >> 15);
}


//================================================================================
//         INTERNAL FUNCTIONS
//================================================================================
//   Don't use PADi_ internal functions if possible.
//   Using key interrupts may cause some bugs
//   because there is the problem with key chattering

//---------------- interrupt key logic
typedef enum
{
    // condition for interrupt occurrence
    PAD_LOGIC_OR = (0 << REG_PAD_KEYCNT_LOGIC_SHIFT),   //   pushing ONE of keys you specified
    PAD_LOGIC_AND = (1 << REG_PAD_KEYCNT_LOGIC_SHIFT),  //   pushing ALL of keys at a time you specified

    //---- for compatibility with old description
    PAD_OR_INTR = PAD_LOGIC_OR,
    PAD_AND_INTR = PAD_LOGIC_AND
}
PADLogic;

/*---------------------------------------------------------------------------*
  Name:         PADi_SetIrq

  Description:  set key interrupt

  Arguments:    logic: key logic
                          PAD_OR_INTR / PAD_AND_INTR
                enable : TRUE if interrupts enabled, FALSE if not
                padMask : buttons to trigger interrupt

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void PADi_SetIrq(PADLogic logic, BOOL enable, u16 padMask)
{
    SDK_ASSERT(!(padMask & (~PAD_KEYPORT_MASK)));       // check X, Y, Debug button
    reg_PAD_KEYCNT = (u16)(((u16)logic
                            | (enable ? REG_PAD_KEYCNT_INTR_MASK : 0)
                            | (PAD_KEYPORT_MASK & padMask)));
}

/*---------------------------------------------------------------------------*
  Name:         PADi_ClearIrq

  Description:  unset key interrupt

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void PADi_ClearIrq(void)
{
    reg_PAD_KEYCNT = 0;
}

//================================================================================

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PAD_PAD_H_ */
#endif
