/*---------------------------------------------------------------------------*
  Project:  NitroSDK - RTC - include
  File:     type.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: type.h,v $
  Revision 1.3  2006/01/18 02:12:38  kitase_hirotake
  do-indent

  Revision 1.2  2005/02/28 05:26:09  yosizaki
  do-indent.

  Revision 1.1  2004/05/12 02:27:35  terui
  initial upload

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef	NITRO_RTC_COMMON_TYPE_H_
#define	NITRO_RTC_COMMON_TYPE_H_

#ifdef	__cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include "nitro/types.h"

/*---------------------------------------------------------------------------*
    constant definitions
 *---------------------------------------------------------------------------*/
// RTC interrupt related definitions
#define		RTC_INTERRUPT_MODE_NONE				0x0     // No interrupts
#define		RTC_INTERRUPT_MODE_32kHz			0x8     // 32 kHz standing wave output
#define		RTC_INTERRUPT_MODE_PULSE			0x1     // Selected frequency steady interrupt
#define		RTC_INTERRUPT_MODE_MINUTE_EDGE		0x2     // Once a minute edge interrupt
#define		RTC_INTERRUPT_MODE_MINUTE_PULSE1	0x3     // Once a minute steady interrupt 1 (50% duty)
#define		RTC_INTERRUPT_MODE_ALARM			0x4     // Alarm interrupt
#define		RTC_INTERRUPT_MODE_MINUTE_PULSE2	0x7     // Once a minute steady interrupt 2

#define		RTC_INTERRUPT_MASK_32kHz			0x8     // Bit mask having meaning during 32 kHz standing wave output
#define		RTC_INTERRUPT_MASK_PULSE			0xb     // Bit mask having meaning during selected frequency steady interrupt
#define		RTC_INTERRUPT_MASK_MINUTE_EDGE		0xb     // Bit mask having meaning during selected once a minute edge interrupt

// Frequency duty definitions
#define		RTC_PULSE_DUTY_1HZ					0x01
#define		RTC_PULSE_DUTY_2HZ					0x02
#define		RTC_PULSE_DUTY_4HZ					0x04
#define		RTC_PULSE_DUTY_8HZ					0x08
#define		RTC_PULSE_DUTY_16HZ					0x10
/* When there are multiple configured, high will be output to the interrupt signal line when all of the configured pulses become high. Low will be output if any of them is low.*/


/*---------------------------------------------------------------------------*
    structure definitions
 *---------------------------------------------------------------------------*/
// Date structure
typedef struct RTCRawDate
{
    u32     year:8;                    // Year ( 00 - 99 )
    u32     month:5;                   // Month ( 01 - 12 )
    u32     dummy0:3;
    u32     day:6;                     // Day ( 01 - 31 ) Month / Upper limit will change with leap year
    u32     dummy1:2;
    u32     week:3;                    // Day of week ( 00 - 06 )
    u32     dummy2:5;

}
RTCRawDate;

// Time structure
typedef struct RTCRawTime
{
    u32     hour:6;                    // Hour ( 00 - 23 or 00 - 11 )
    u32     afternoon:1;               // p.m. flag in the case of 12-hour notation
    u32     dummy0:1;
    u32     minute:7;                  // Minutes ( 00 - 59 )
    u32     dummy1:1;
    u32     second:7;                  // Second ( 00 - 59 )
    u32     dummy2:9;

}
RTCRawTime;

// Status 1 structure
typedef struct RTCRawStatus1
{
    u16     reset:1;                   // W   Reset flag
    u16     format:1;                  // R/W Hour notation flag (0: 12-hour; 1: 24-hour)
    u16     dummy0:2;
    u16     intr1:1;                   // R   Interrupt 1 generated flag (low will be output on the interrupt signal line)
    u16     intr2:1;                   // R   Interrupt 2 generated flag (low will be output on the interrupt signal line)
    u16     bld:1;                     // R   Power source voltage drop detection flag
    u16     poc:1;                     // R   Power source turned on detection flag
    u16     dummy1:8;

}
RTCRawStatus1;

// Status 2 structure
typedef struct RTCRawStatus2
{
    u16     intr_mode:4;               // R/W interrupt 1 selection ( RTC_INTERRUPT_MODE_* )
    u16     dummy0:2;
    u16     intr2_mode:1;              // R/W interrupt 2 enable flag
    u16     test:1;                    // R/W test mode flag
    u16     dummy1:8;

}
RTCRawStatus2;

// Alarm structure
typedef struct RTCRawAlarm
{
    u32     week:3;                    // Day of week ( 00 - 06 )
    u32     dummy0:4;
    u32     we:1;                      // Day of week parameter enable flag
    u32     hour:6;                    // Time ( 00 - 23 or 00 - 11 ). Hour notation depends on status 1.
    u32     afternoon:1;               // p.m. flag in the case of 12-hour notation
    u32     he:1;                      // Hour parameter enable flag
    u32     minute:7;                  // Minutes ( 00 - 59 )
    u32     me:1;                      // Minute parameter enable flag
    u32     dummy2:8;

}
RTCRawAlarm;

// Pulse structure
typedef struct RTCRawPulse
{
    u32     pulse:5;                   // Frequency duty flag ( RTC_PULSE_DUTY_* )
    u32     dummy:27;

}
RTCRawPulse;

// Clock adjust register structure
typedef struct RTCRawAdjust
{
    u32     adjust:8;                  // Clock adjust register ( see other document for settings )
    u32     dummy:24;

}
RTCRawAdjust;

// Free register structure
typedef struct RTCRawFree
{
    u32     free:8;                    // Free register
    u32     dummy:24;

}
RTCRawFree;

// ARM9 <-> ARM7 transfer data structure (8 byte union)
typedef union RTCRawData
{
    struct
    {
        RTCRawDate date;               // Date
        RTCRawTime time;               // Time
    }
    t;

    struct
    {
        RTCRawStatus1 status1;         // Status 1 register
        RTCRawStatus2 status2;         // Status 2 register
        union
        {
            RTCRawPulse pulse;         // Set register for frequency periodic interrupt
            RTCRawAlarm alarm;         // Set register for alarm ( 1 or 2 )
            RTCRawAdjust adjust;       // Set register for clock adjustment
            RTCRawFree free;           // Set free register
        };
    }
    a;

    u32     words[2];                  // For 4-byte access

    u16     halfs[4];                  // For 2-byte access

    u8      bytes[8];                  // For byte access

}
RTCRawData;


/*===========================================================================*/

#ifdef	__cplusplus
}          /* extern "C" */
#endif

#endif /* NITRO_RTC_COMMON_TYPE_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
