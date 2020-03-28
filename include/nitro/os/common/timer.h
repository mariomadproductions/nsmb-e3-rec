/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     timer.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: timer.h,v $
  Revision 1.24  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.23  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.22  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.21  2004/11/24 04:36:59  yada
  just fix typo

  Revision 1.20  2004/09/02 06:26:54  yada
  only change comment

  Revision 1.19  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.18  2004/02/12 13:36:40  yasu
  change directory of ioreg.h

  Revision 1.17  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.16  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.15  2004/01/27 01:47:52  yada
  Revised inline

  Revision 1.14  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.13  2004/01/08 05:42:39  yada
  Revised ASSERT

  Revision 1.12  2004/01/08 05:06:34  yada
  Revised cast mistake.

  Revision 1.11  2004/01/08 04:55:48  yada
  Fixed timer setting bug. Added OS_StopTimer().

  Revision 1.10  2003/12/25 07:30:15  yada
  Changes as per unified type rules

  Revision 1.9  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.8  2003/11/17 01:28:34  yada
  Fixed a mistake in assert.

  Revision 1.7  2003/11/14 04:58:11  yada
  Changed the register access macro from REG_XXX to reg_XXX

  Revision 1.6  2003/11/13 04:03:30  yada
  Discontinued OSENUM...

  Revision 1.5  2003/11/05 01:05:20  yada
  (none)

  Revision 1.4  2003/11/05 01:03:18  yada
  Made the cast more strict At least make it so no warnings appear.

  Revision 1.3  2003/10/31 04:11:37  yada
  "}" was missing for extern"C".

  Revision 1.2  2003/10/30 11:42:52  yada
  Decided to use REGTypexx in the register type

  Revision 1.1  2003/10/30 06:56:20  yada
  Created initial version

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_TIMER_H_
#define NITRO_OS_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/ioreg.h"

//----------------------------------------------------------------------
//---- pre-scaler
typedef enum
{
    OS_TIMER_PRESCALER_1 = (0UL << REG_OS_TM0CNT_H_PS_SHIFT),   // x 1
    OS_TIMER_PRESCALER_64 = (1UL << REG_OS_TM0CNT_H_PS_SHIFT),  // x 64
    OS_TIMER_PRESCALER_256 = (2UL << REG_OS_TM0CNT_H_PS_SHIFT), // x 256
    OS_TIMER_PRESCALER_1024 = (3UL << REG_OS_TM0CNT_H_PS_SHIFT) // x 1024
}
OSTimerPrescaler;

//---- timer number
typedef enum
{
    OS_TIMER_0 = 0,
    OS_TIMER_1 = 1,
    OS_TIMER_2 = 2,
    OS_TIMER_3 = 3
}
OSTimer;

//---- timer number ( if use 32 bit timer )
typedef enum
{
    OS_TIMER32_01 = 0,
    OS_TIMER32_12 = 1,
    OS_TIMER32_23 = 2
}
OSTimer32;

//---- timer number ( if use 48 bit timer )
typedef enum
{
    OS_TIMER48_012 = 0,
    OS_TIMER48_123 = 1
}
OSTimer48;

//================================================================================
//            TIMER
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_SetTimerCount

  Description:  set timer count

  Arguments:    id         timerNo
                count      count value to be set to timer

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void OS_SetTimerCount(OSTimer id, u16 count)
{
    SDK_ASSERT(OS_TIMER_0 <= id && id <= OS_TIMER_3);
    *((REGType16 *)((u32)REG_TM0CNT_L_ADDR + id * 4)) = count;
}

/*---------------------------------------------------------------------------*
  Name:         OS_SetTimerControl

  Description:  set timer control

  Arguments:    id         timerNo
                control    control value to be set to timer

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void OS_SetTimerControl(OSTimer id, u16 control)
{
    SDK_ASSERT(OS_TIMER_0 <= id && id <= OS_TIMER_3);
    *((REGType16 *)((u32)REG_TM0CNT_H_ADDR + id * 4)) = control;
}

/*---------------------------------------------------------------------------*
  Name:         OS_StartTimer

  Description:  set timer(s) and start

  Arguments:    id         timerNo
                count      count value to be set to timer
                preScale   preScale

  Returns:      None
 *---------------------------------------------------------------------------*/
//
//   use 1 timer, 16bit counter,  timer<id> interrupt occurs by overflow
//
void    OS_StartTimer(OSTimer id, u16 count, OSTimerPrescaler preScale);
//
//   use 2 timers, 32bit counter, timer<id+1> interrupt occurs by overflow
//
void    OS_StartTimer32(OSTimer32 id, u32 count, OSTimerPrescaler preScale);
//
//   use 3 timers, 48bit counter, timer<id+2> interrupt occurs by overflow
//
void    OS_StartTimer48(OSTimer48 id, u64 count, OSTimerPrescaler preScale);
//
//   use all 4 timers, 64bit counter, timer3 interrupt occurs by overflow
//
void    OS_StartTimer64(u64 count, OSTimerPrescaler preScale);


/*---------------------------------------------------------------------------*
  Name:         OS_StopTimer

  Description:  stop timer(s)

  Arguments:    id         timerNo

  Returns:      None
 *---------------------------------------------------------------------------*/
//
//  stop a timer
//
void    OS_StopTimer(OSTimer id);
//
//  stop 2 timers
//
void    OS_StopTimer32(OSTimer32 id);
//
//  stop 3 timers
//
void    OS_StopTimer48(OSTimer48 id);
//
//  stop all 4 timers
//
void    OS_StopTimer64(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_TIMER_H_ */
#endif
