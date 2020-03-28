/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     alarm.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: alarm.h,v $
  Revision 1.12  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.11  2005/08/08 11:26:36  yada
  change declaration of alarm struct

  Revision 1.10  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.9  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.8  2004/11/02 09:58:57  yada
  just fix comment

  Revision 1.7  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.6  2004/02/25 11:28:44  yada
  Changes related to switch from systemClock to Tick

  Revision 1.5  2004/02/24 10:50:47  yada
  added alarm counter and actual time conversion definition

  Revision 1.4  2004/02/19 08:43:36  yada
  only added comment

  Revision 1.3  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.2  2004/02/04 07:31:46  yada
  added OS_IsAlarmAvailable(), OS_EndAlarm()

  Revision 1.1  2004/02/03 11:18:58  yada
  firstRelease

  Revision 1.1  2003/12/22 01:35:16  yada
  made init.h in accordance with OS_Init() installation


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_ALARM_H_
#define NITRO_OS_ALARM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/os/common/thread.h"


//--------------------------------------------------------------------------------
//---- Alarm Handler
typedef void (*OSAlarmHandler) (void *);


//---- struct of Alarm
//typedef struct OSiAlarm OSAlarm;   // this is decleared in thread.h
struct OSiAlarm
{
    OSAlarmHandler handler;
    void   *arg;

    u32     tag;
    OSTick  fire;
    OSAlarm *prev;
    OSAlarm *next;

    //---- for periodic alarm
    OSTick  period;
    OSTick  start;
};

//--------------------------------------------------------------------------------
/*---------------------------------------------------------------------------*
  Name:         OS_InitAlarm

  Description:  initalize alarm system

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_InitAlarm(void);


/*---------------------------------------------------------------------------*
  Name:         OS_EndAlarm

  Description:  end alarm system

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_EndAlarm(void);


/*---------------------------------------------------------------------------*
  Name:         OS_IsAlarmAvailable

  Description:  check alarm system is available

  Arguments:    None

  Returns:      if available, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    OS_IsAlarmAvailable(void);


/*---------------------------------------------------------------------------*
  Name:         OS_CreateAlarm

  Description:  Create alarm

  Arguments:    alarm       pointer to alarm to be initialized

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_CreateAlarm(OSAlarm *alarm);


/*---------------------------------------------------------------------------*
  Name:         OS_SetAlarm

  Description:  Set alarm as a relative time

  Arguments:    alarm       pointer to alarm to be set
                tick        ticks to count before firing
                handler     alarm handler to be called
                arg         argument of handler

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_SetAlarm(OSAlarm *alarm, OSTick tick, OSAlarmHandler handler, void *arg);


/*---------------------------------------------------------------------------*
  Name:         OS_SetPeriodicAlarm

  Description:  set periodic alarm

  Arguments:    alarm       pointer to alarm to be set
                start       origin of the period in absolute time
                period      ticks to count for each period
                handler     alarm handler to be called
                arg         argument of handler

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_SetPeriodicAlarm(OSAlarm *alarm, OSTick start, OSTick period, OSAlarmHandler handler,
                            void *arg);


/*---------------------------------------------------------------------------*
  Name:         OS_SetAlarmTag

  Description:  set tag which is used OS_CancelAlarms

  Arguments:    alarm        alarm to be set tag
                tag          tagNo

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_SetAlarmTag(OSAlarm *alarm, u32 tag);


/*---------------------------------------------------------------------------*
  Name:         OS_CancelAlarm

  Description:  Cancel alarm

  Arguments:    alarm       pointer to alarm to be canceled

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_CancelAlarm(OSAlarm *alarm);


/*---------------------------------------------------------------------------*
  Name:         OS_CancelAlarms

  Description:  cancel alarms which have specified tag

  Arguments:    tag          tagNo. to be cancelled. not 0

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_CancelAlarms(u32 tag);


/*---------------------------------------------------------------------------*
  Name:         OS_CancelAllAlarms

  Description:  cancel all alarms

  Arguments:    None

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_CancelAllAlarms(void);

//================================================================================
//  The following definitions or declarations are for internal use.
//  Don't call these from use program.
struct OSiAlarmQueue
{
    OSAlarm *head;
    OSAlarm *tail;
};
struct OSiAlarmQueue *OSi_GetAlarmQueue(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_ALARM_H_ */
#endif
