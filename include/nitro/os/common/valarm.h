/*---------------------------------------------------------------------------*
  Project: NitroSDK - OS - include
  File: valarm.h

  Copyright 2003-2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: valarm.h,v $
  Revision 1.12  2007/05/28 02:34:31  okubata_ryoma
  OSAlarmHandler->OSVAlarmHandler

  Revision 1.11  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.10  2005/03/01 01:57:00  yosizaki
  Revised copyright year.

  Revision 1.9  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.8  2004/11/02 11:58:22  yada
  Fixed a little.

  Revision 1.7  2004/11/02 09:48:12  yada
  Revised comments.

  Revision 1.6  2004/10/21 13:43:50  yasu
  Added OS_VALARM_DELAY_MAX macro.

  Revision 1.5  2004/10/21 06:11:29  yada
  Fix a lot.  Consider for delay.

  Revision 1.4  2004/04/07 02:03:17  yada
  Fixed header comment.

  Revision 1.3  2004/03/08 05:35:03  yada
  Made so you can set the allowable delay range of periodic VCount.

  Revision 1.2  2004/03/02 11:04:36  yada
  Took into consideration delay of V interrupt.

  Revision 1.1  2004/02/23 11:57:58  yada
  firstRelease


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_VALARM_H_
#define NITRO_OS_VALARM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"


//--------------------------------------------------------------------------------
//---- VAlarm Handler
typedef void (*OSVAlarmHandler) (void *);

//---- struct of VAlarm
typedef struct OSiVAlarm OSVAlarm;
struct OSiVAlarm
{
    //---- callback
    OSVAlarmHandler handler;
    void   *arg;

    //---- tag (system use 0)
    u32     tag;

    //---- fire time
    u32     frame;
    s16     fire;

    //---- permissible range to fire alarm
    s16     delay;

    //---- link information (system uses)
    OSVAlarm *prev;
    OSVAlarm *next;

    //---- periodic alarm or not
    BOOL    period;

    //---- flag whether its called
    BOOL    finish;

    //---- flag for check to cancel
    BOOL    canceled;
};

//--------------------------------------------------------------------------------
/*---------------------------------------------------------------------------*
  Name: OS_InitVAlarm

  Description: Initialize v-alarm module

  Arguments: None.

  Returns: None.
 *---------------------------------------------------------------------------*/
void    OS_InitVAlarm(void);

/*---------------------------------------------------------------------------*
  Name: OS_EndVAlarm

  Description: end v-alarm system

  Arguments: None

  Returns: None
 *---------------------------------------------------------------------------*/
void    OS_EndVAlarm(void);

/*---------------------------------------------------------------------------*
  Name: OS_IsVAlarmAvailable

  Description: check v-alarm system is available

  Arguments: None

  Returns: if available, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    OS_IsVAlarmAvailable(void);

/*---------------------------------------------------------------------------*
  Name: OS_CreateVAlarm

  Description: Create v-alarm

  Arguments: alarm       pointer to v-alarm to be initialized

  Returns: None.
 *---------------------------------------------------------------------------*/
void    OS_CreateVAlarm(OSVAlarm *alarm);

/*---------------------------------------------------------------------------*
  Name: OS_SetVAlarm

  Description: Set v-alarm as a relative time

  Arguments: alarm       pointer to v-alarm to be set
                count       count to fire
                delay       permission range of delay
                handler     v-alarm handler to be called
                arg         argument of handler

  Returns: None.
 *---------------------------------------------------------------------------*/
#define OS_VALARM_DELAY_MAX HW_LCD_LINES
void    OS_SetVAlarm(OSVAlarm *alarm, s16 count, s16 delay, OSVAlarmHandler handler, void *arg);

/*---------------------------------------------------------------------------*
( for compatibility with old definition )
  Name: OS_SetOneTimeVAlarm

  Description: Set v-alarm as a relative time

  Arguments: alarm       pointer to v-alarm to be set
                count       count to fire
                handler     v-alarm handler to be called
                arg         argument of handler

  Returns: None.
 *---------------------------------------------------------------------------*/
#define OSi_DELAYMARGIN  10
static inline void OS_SetOneTimeVAlarm(OSVAlarm *alarm, s16 count, OSVAlarmHandler handler,
                                       void *arg)
{
    OS_SetVAlarm(alarm, count, OSi_DELAYMARGIN, handler, arg);
}

/*---------------------------------------------------------------------------*
  Name: OS_SetPeriodicVAlarm

  Description: set periodic v-alarm

  Arguments: alarm       pointer to v-alarm to be set
                count          count to fire cyclically
                delay       permission range of delay
                handler     v-alarm handler to be called
                arg         argument of handler

  Returns: None.
 *---------------------------------------------------------------------------*/
void    OS_SetPeriodicVAlarm(OSVAlarm *alarm, s16 count, s16 delay, OSVAlarmHandler handler,
                             void *arg);

/*---------------------------------------------------------------------------*
  Name: OS_SetVAlarmTag

  Description: set tag which is used OS_CancelAlarms

  Arguments: alarm        alarm to be set tag
                tag          tagNo

  Returns: None.
 *---------------------------------------------------------------------------*/
void    OS_SetVAlarmTag(OSVAlarm *alarm, u32 tag);

/*---------------------------------------------------------------------------*
  Name: OS_CancelVAlarms

  Description: cancel v-alarms which have specified tag

  Arguments: tag          tagNo. to be cancelled. not 0

  Returns: None.
 *---------------------------------------------------------------------------*/
void    OS_CancelVAlarm(OSVAlarm *alarm);

/*---------------------------------------------------------------------------*
  Name: OS_CancelAllVAlarms

  Description: cancel all v-alarms

  Arguments: None

  Returns: None.
 *---------------------------------------------------------------------------*/
void    OS_CancelVAlarms(u32 tag);

/*---------------------------------------------------------------------------*
  Name: OS_CancelAllVAlarms

  Description: cancel all v-alarms

  Arguments: None

  Returns: None.
 *---------------------------------------------------------------------------*/
void    OS_CancelAllVAlarms(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_VALARM_H_ */
#endif
