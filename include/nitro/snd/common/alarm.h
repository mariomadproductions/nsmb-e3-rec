/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     alarm.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: alarm.h,v $
  Revision 1.9  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.8  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.7  2004/10/15 15:17:55  yasu
  sound patch for NITRO-System 10/12

  Revision 1.6  2004/08/19 06:53:17  ida
  work around alarm

  Revision 1.5  2004/08/02 05:36:25  ida
  workaround sound alarm

  Revision 1.4  2004/06/28 07:15:58  ida
  change function interface

  Revision 1.3  2004/06/21 01:19:26  ida
  change function interface

  Revision 1.2  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.1  2004/03/22 02:05:44  ida
  add alarm

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_ALARM_H_
#define NITRO_SND_COMMON_ALARM_H_

#include "nitro/types.h"
#include "nitro/os.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
	macro definition
 ******************************************************************************/

#define SND_ALARM_NUM 8
#define SND_ALARM_MIN 0
#define SND_ALARM_MAX ( SND_ALARM_NUM - 1 )

#define SND_ALARM_PRESCALER 32

/******************************************************************************
	type definition
 ******************************************************************************/

typedef void (*SNDAlarmHandler) (void *);

/******************************************************************************
	structure definition
 ******************************************************************************/

typedef struct SNDAlarm
{
    u8      enable;
    u8      id;
    u16     padding;

    struct
    {
        OSTick  tick;
        OSTick  period;
    }
    setting;

    OSAlarm alarm;
}
SNDAlarm;

/******************************************************************************
	public function declaration
 ******************************************************************************/

void    SND_AlarmInit(void);

#ifdef SDK_ARM7

void    SND_SetupAlarm(int alarmNo, OSTick tick, OSTick period, int id);

void    SND_StartAlarm(int alarmNo);
void    SND_StopAlarm(int alarmNo);

#endif /* SDK_ARM7 */

/******************************************************************************
	private function declaration
 ******************************************************************************/

#ifdef SDK_ARM9

void    SNDi_IncAlarmId(int alarmNo);

u8      SNDi_SetAlarmHandler(int alarmNo, SNDAlarmHandler handler, void *arg);

void    SNDi_CallAlarmHandler(int alarmNo);

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_ALARM_H_ */
