/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     tick.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: tick.h,v $
  Revision 1.8  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.7  2005/10/07 06:10:17  yada
  tick and real time conversion functions changed

  Revision 1.6  2005/10/06 04:41:07  yada
  modified tick and seconds conversion functions to consider for u32 overflow

  Revision 1.5  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.4  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.3  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.2  2004/03/02 06:59:13  yasu
  add one more ')' at OS_TicksToMicroSeconds

  Revision 1.1  2004/02/25 11:36:52  yada
  Changes related to switch from systemClock to Tick

  Revision 1.8  2004/02/24 12:37:15  yada
  Fixed misspelling in OS_GetTick()

  Revision 1.7  2004/02/24 10:49:49  yada
  Added OS_GetTick()

  Revision 1.6  2004/02/12 13:36:40  yasu
  change directory of ioreg.h

  Revision 1.5  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.4  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.3  2004/02/04 07:36:25  yada
  Added OS_IsSystemClockAvailable()
  Changed names from OS_GetSystemClock(), OS_SetSystemClock()
  Changed names to OS_GetTime(), OS_SetTime()

  Revision 1.2  2004/02/03 11:18:29  yada
  Changed the systemClock value from u32 to OSTime(u64).

  Revision 1.1  2004/02/02 05:29:18  yada
  System clock firstRelease


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_TICK_H_
#define NITRO_OS_TICK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/ioreg.h"


//---- unit of tick
typedef u64 OSTick;

//---- conversion tick count <-> real time count
#define OS_SYSTEM_CLOCK                HW_SYSTEM_CLOCK

#define OSi_BOUND_SEC1	 			   128154       // 2^8 / (OS_SYSTEM_CLOCK/1000) = 128154.4
#define OSi_BOUND_SEC2 				   128  // 2^8 / OS_SYSTEM_CLOCK = 128.2
#define OSi_BOUND_TICK1				   67108        // 2^8 / (64*1000) = 67108.9
#define OSi_BOUND_TICK2 			   67108863     // 2^8 / 64 = 67108864

//---- sec to tick
#define  OS_MicroSecondsToTicks(   usec ) ((OSTick)( ((OS_SYSTEM_CLOCK/1000) * (u64)(usec)) / 64 / 1000 ))
#define  OS_MicroSecondsToTicks32( usec ) ((OSTick)( ((OS_SYSTEM_CLOCK/1000) * (u32)(usec)) / 64 / 1000 ))

#define  OS_MilliSecondsToTicks(   msec ) ((OSTick)( ((OS_SYSTEM_CLOCK/1000) * (u64)(msec)) / 64 ))
#define  OS_MilliSecondsToTicks32( msec ) ((OSTick)( ((OS_SYSTEM_CLOCK/1000) * (u32)(msec)) / 64 ))

#define  OS_SecondsToTicks(         sec ) ((OSTick)( (OS_SYSTEM_CLOCK * (u64)(sec)) / 64 ))
#define  OS_SecondsToTicks32(       sec ) ((OSTick)( (OS_SYSTEM_CLOCK * (u32)(sec)) / 64 ))

//---- tick to sec
#define  OS_TicksToMicroSeconds(   tick ) ( ((u64)(tick) * 64 * 1000) / (OS_SYSTEM_CLOCK/1000) )
#define  OS_TicksToMicroSeconds32( tick ) ( ((u32)(tick) * 64 * 1000) / (OS_SYSTEM_CLOCK/1000) )

#define  OS_TicksToMilliSeconds(   tick ) ( ((u64)(tick) * 64) / (OS_SYSTEM_CLOCK/1000) )
#define  OS_TicksToMilliSeconds32( tick ) ( ((u32)(tick) * 64) / (OS_SYSTEM_CLOCK/1000) )

#define  OS_TicksToSeconds(        tick ) ( ((u64)(tick) * 64) / OS_SYSTEM_CLOCK )
#define  OS_TicksToSeconds32(      tick ) ( ((u32)(tick) * 64) / OS_SYSTEM_CLOCK )

/*---------------------------------------------------------------------------*
  Name:         OS_InitTick

  Description:  Initialize tick system

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_InitTick(void);


/*---------------------------------------------------------------------------*
  Name:         OS_IsTickAvailable

  Description:  check tick system is available

  Arguments:    None

  Returns:      if available, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    OS_IsTickAvailable(void);


/*---------------------------------------------------------------------------*
  Name:         OS_GetTick

  Description:  get tick value

  Arguments:    None

  Returns:      tick value
 *---------------------------------------------------------------------------*/
OSTick  OS_GetTick(void);


/*---------------------------------------------------------------------------*
  Name:         OS_GetTickLo

  Description:  get tick value (only u16 part)

  Arguments:    None

  Returns:      sytem clock value (only u16 part)
 *---------------------------------------------------------------------------*/
u16     OS_GetTickLo(void);


/*---------------------------------------------------------------------------*
  Name:         OS_SetTick

  Description:  set tick value

  Arguments:    count     value of tick to be set

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SetTick(OSTick count);



#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_TICK_H_ */
#endif
