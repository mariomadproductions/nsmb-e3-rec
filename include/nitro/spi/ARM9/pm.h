/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PM - include
  File:     pm.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: pm.h,v $
  Revision 1.26  2006/01/25 05:49:36  okubata_ryoma
  small fix

  Revision 1.24  2006/01/18 02:12:27  kitase_hirotake
  do-indent

  Revision 1.23  2005/02/28 05:26:25  yosizaki
  do-indent.

  Revision 1.22  2004/11/02 09:46:58  yada
  just fix comment

  Revision 1.21  2004/10/06 08:28:03  yada
  change around sleep callback

  Revision 1.20  2004/10/05 04:13:39  yada
  support pre/post sleep mode callback

  Revision 1.19  2004/08/26 08:32:21  yada
  only fix comment

  Revision 1.18  2004/08/26 08:19:47  yada
  add PM_GetLEDPattern*

  Revision 1.17  2004/08/23 08:06:49  yada
  add LED self blink

  Revision 1.16  2004/08/16 04:14:46  yada
  change argument of PMi_SetLCDPower()

  Revision 1.15  2004/08/10 10:51:39  yada
  LCD power interval become to be controlled with VBlank counter.
  PM_ForcedPowerOff -> PM_ForceToPowerOff

  Revision 1.14  2004/08/09 09:49:28  yada
  delete PM_SetSoundPower/SoundVolume, PM_GetSoundPower/SoundVolume
  (PM -> PMi)

  Revision 1.13  2004/08/09 04:59:43  yada
  add PM_GetSoundPower/SoundVolume/Amp/AmpGain

  Revision 1.12  2004/08/09 01:59:29  yada
  delete async function from PM_Get*

  Revision 1.11  2004/08/07 07:25:29  yada
  PM_CheckBattery -> PM_GetBattery

  Revision 1.10  2004/08/07 07:02:07  yada
  PM_SetForcedPower -> PM_ForcedPowerOff

  Revision 1.9  2004/08/06 12:40:17  yada
  delete power save mode proc

  Revision 1.8  2004/08/05 05:54:15  yada
  create functions about powerSaveMode

  Revision 1.7  2004/08/04 00:44:21  yada
  PM_SetBackLightTop/Bottom -> PM_SetBackLight

  Revision 1.6  2004/08/03 08:40:41  yada
  fix in end sleeping

  Revision 1.5  2004/08/02 12:53:16  yada
  fix a little

  Revision 1.4  2004/08/02 06:14:34  yada
  PM_SetLED, PM_WriteRegister, PM_ReadRegister : PM->PMi
  standby->sleep

  Revision 1.3  2004/08/02 00:35:44  yada
  change some argument in pm api. define enums about pm.

  Revision 1.2  2004/07/31 01:30:45  yada
  add PM_SetAmp, PM_SetAmpGain, PM_SetVDETVoltage

  Revision 1.1  2004/07/29 09:00:50  yada
  initial release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PM_ARM9_H_
#define NITRO_PM_ARM9_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/spi/common/pm_common.h"
#include "nitro/spi/common/type.h"
#include "nitro/pxi/common/fifo.h"

//================================================================
//---- callback for async function
typedef void (*PMCallback) (u32 result, void *arg);

//---- for use read value
typedef struct
{
    u16     flag;
    u16     padding;                   //dummy
    u16    *buffer;
}
PMData16;

//================================================================
//     parameters for PM API
//================================================================
//---- LCD target
typedef enum
{
    PM_LCD_TOP = 0,
    PM_LCD_BOTTOM = 1,
    PM_LCD_ALL = 2
}
PMLCDTarget;

//---- back light
typedef enum
{
    PM_BACKLIGHT_OFF = 0,
    PM_BACKLIGHT_ON = 1
}
PMBackLightSwitch;

//---- battery status (VDET terminal voltage)
typedef enum
{
    PM_BATTERY_HIGH = 0,
    PM_BATTERY_LOW = 1
}
PMBattery;

//---- programable gain amp
typedef enum
{
    PM_AMP_OFF = 0,
    PM_AMP_ON = 1
}
PMAmpSwitch;

//---- gain of programable gain amp
typedef enum
{
    PM_AMPGAIN_20 = 0,
    PM_AMPGAIN_40 = 1,
    PM_AMPGAIN_80 = 2,
    PM_AMPGAIN_160 = 3,
    PM_AMPGAIN_DEFAULT = PM_AMPGAIN_40
}
PMAmpGain;

#define PM_GAINAMP_DEFAULT  PM_AMPGAIN_DEFAULT    // for compatible

//---- LCD power
typedef enum
{
    PM_LCD_POWER_OFF = 0,
    PM_LCD_POWER_ON = 1
}
PMLCDPower;

//---- callback type to be called before/after sleep mode
typedef void (*PMSleepCallback) (void *);

//---- callback info type
typedef struct PMiSleepCallbackInfo PMSleepCallbackInfo;
struct PMiSleepCallbackInfo
{
    PMSleepCallback callback;
    void   *arg;
    PMSleepCallbackInfo *next;
};

//================================================================================
//           INITIALIZE
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         PM_Init

  Description:  initialize PM

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_Init(void);

//================================================================================
//           SEND COMMAND TO ARM7
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         PM_SendUtilityCommandAsync / PM_SendUtilityCommand

  Description:  send utility command to ARM7

  Arguments:    number   : action number
                callback : callback function
                arg      : argument of callback

  Returns:      result of issuing command
                PM_RESULT_BUSY    : busy
                PM_RESULT_SUCCESS : success
 *---------------------------------------------------------------------------*/
u32     PM_SendUtilityCommandAsync(u32 number, PMCallback callback, void *arg);
u32     PM_SendUtilityCommand(u32 number);

/*---------------------------------------------------------------------------*
  Name:         PM_SetBackLightAsync / PM_SetBackLight

  Description:  change backlight switch

  Arguments:    targer   : target LCD.
                           PM_LCD_TOP    : top LCD
                           PM_LCD_BOTTOM : bottom LCD
                           PM_LCD_ALL    : top and bottom LCD
                sw       : switch of top LCD.
                           PM_BACKLIGHT_OFF : off
                           PM_BACKLIGHT_ON  : on
                callback : callback function
                arg      : callback argument

  Returns:      result.
                PM_RESULT_SUCCESS  : success to exec command
                PM_INVALID_COMMAND : bad status given
                PM_RESULT_ERROR    : some error occurred in ARM7
 *---------------------------------------------------------------------------*/
u32     PM_SetBackLightAsync(PMLCDTarget target, PMBackLightSwitch sw, PMCallback callback,
                             void *arg);
u32     PM_SetBackLight(PMLCDTarget target, PMBackLightSwitch status);

/*---------------------------------------------------------------------------*
  Name:         PM_ForceToPowerOffAsync / PM_ForceToPowerOff

  Description:  force to turn off main power

  Arguments:    callback : callback function
                arg      : callback argument

  Returns:      result.
                PM_RESULT_SUCCESS  : success to exec command
                PM_RESULT_ERROR    : some error occurred in ARM7

                If success, maybe you cannot do anything because power if off.
 *---------------------------------------------------------------------------*/
u32     PM_ForceToPowerOffAsync(PMCallback callback, void *arg);
u32     PM_ForceToPowerOff(void);

/*---------------------------------------------------------------------------*
  Name:         PM_SetAmpAsync / PM_SetAmp

  Description:  switch amp

  Arguments:    sw       : switch of programable gain amp
                          PM_AMP_ON   : on
                          PM_AMP_OFF  : off
                callback : callback function
                arg      : callback argument

  Returns:      result.
                PM_RESULT_SUCCESS  : success to exec command
                PM_INVALID_COMMAND : bad status given
                PM_RESULT_ERROR    : some error occurred in ARM7
 *---------------------------------------------------------------------------*/
u32     PM_SetAmpAsync(PMAmpSwitch sw, PMCallback callback, void *arg);
u32     PM_SetAmp(PMAmpSwitch sw);

/*---------------------------------------------------------------------------*
  Name:         PM_SetAmpGainAsync / PM_SetAmpGain

  Description:  change amp gain

  Arguments:    gain      : gain
                          PM_AMPGAIN_20   : gain=20
                          PM_AMPGAIN_40   : gain=40
                          PM_AMPGAIN_80   : gain=80
                          PM_AMPGAIN_160  : gain=160
                callback : callback function
                arg      : callback argument

  Returns:      result.
                PM_RESULT_SUCCESS  : success to exec command
                PM_INVALID_COMMAND : bad status given
                PM_RESULT_ERROR    : some error occurred in ARM7
 *---------------------------------------------------------------------------*/
u32     PM_SetAmpGainAsync(PMAmpGain gain, PMCallback callback, void *arg);
u32     PM_SetAmpGain(PMAmpGain gain);


//================================================================================
//           GET STATUS FROM ARM7
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         PM_GetBattery

  Description:  get battery status

  Arguments:    batteryBuf  : buffer to store result

  Returns:      result.
                PM_RESULT_SUCCESS  : success to exec command
                PM_RESULT_ERROR    : some error occurred in ARM7
 *---------------------------------------------------------------------------*/
u32     PM_GetBattery(PMBattery *batteryBuf);

/*---------------------------------------------------------------------------*
  Name:         PM_GetBackLight

  Description:  get backlight status

  Arguments:    top    : buffer to set result of top LCD
                bottom : buffer to set result of bottom LCD

  Returns:      result.
                PM_RESULT_SUCCESS  : success to exec command
                PM_RESULT_ERROR    : some error occurred in ARM7
 *---------------------------------------------------------------------------*/
u32     PM_GetBackLight(PMBackLightSwitch *top, PMBackLightSwitch *bottom);

/*---------------------------------------------------------------------------*
  Name:         PM_GetAmp

  Description:  get status of amp switch

  Arguments:    swBuf  : buffer to store result

  Returns:      result.
                PM_RESULT_SUCCESS  : success to exec command
                PM_RESULT_ERROR    : some error occurred in ARM7

 *---------------------------------------------------------------------------*/
u32     PM_GetAmp(PMAmpSwitch *swBuf);

/*---------------------------------------------------------------------------*
  Name:         PM_GetAmpGain

  Description:  get status of amp gain

  Arguments:    gainBuf  : buffer to store result

  Returns:      result.
                PM_RESULT_SUCCESS  : success to exec command
                PM_RESULT_ERROR    : some error occurred in ARM7
 *---------------------------------------------------------------------------*/
u32     PM_GetAmpGain(PMAmpGain *gainBuf);

//================================================================================
//           SLEEP
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         PM_GoSleepMode

  Description:  go to be in sleep mode

  Arguments:    trigger    : factors to return from being on sleep
                logic      : key logic to key interrupt
                             PM_PAD_LOGIC_AND : occur interrupt at all specified button pushed
                             PM_PAD_LOGIC_OR  : occur interrupt at one of specified buttons pushed
                keyPattern : keys to wakeup

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_GoSleepMode(PMWakeUpTrigger trigger, PMLogic logic, u16 keyPattern);

//================================================================================
//           CALLBACK for sleep mode
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         PM_SetSleepCallbackInfo

  Description:  set up sleep callback info

  Arguments:    info     : callback info
                callback : callback to set
                arg      : arg to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void PM_SetSleepCallbackInfo(PMSleepCallbackInfo *info, PMSleepCallback callback,
                                           void *arg)
{
    info->callback = callback;
    info->arg = arg;
}

/*---------------------------------------------------------------------------*
  Name:         PM_AppendPreSleepCallback

  Description:  append callback info to pre-callback info list

  Arguments:    info : callback info to append

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_AppendPreSleepCallback(PMSleepCallbackInfo *info);

/*---------------------------------------------------------------------------*
  Name:         PM_PrependPreSleepCallback

  Description:  prepend callback info to pre-callback info list

  Arguments:    info : callback info to prepend

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_PrependPreSleepCallback(PMSleepCallbackInfo *info);

/*---------------------------------------------------------------------------*
  Name:         PM_AppendPostSleepCallback

  Description:  append callback info to post-callback info list

  Arguments:    info : callback info to append

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_AppendPostSleepCallback(PMSleepCallbackInfo *info);

/*---------------------------------------------------------------------------*
  Name:         PM_PrependPostSleepCallback

  Description:  prepend callback info to post-callback info list

  Arguments:    info : callback info to prepend

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_PrependPostSleepCallback(PMSleepCallbackInfo *info);

/*---------------------------------------------------------------------------*
  Name:         PM_DeletePreSleepCallback

  Description:  delete callback info from pre-callback info list

  Arguments:    info : callback info to delete

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_DeletePreSleepCallback(PMSleepCallbackInfo *info);

/*---------------------------------------------------------------------------*
  Name:         PM_DeletePostSleepCallback

  Description:  delete callback info from post-callback info list

  Arguments:    info : callback info to delete

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_DeletePostSleepCallback(PMSleepCallbackInfo *info);


//================================================================================
//             LCD
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         PM_SetLCDPower

  Description:  turn on/off LCD power

  Arguments:    sw : switch
                   PM_LCD_POWER_ON  : on
                   PM_LCD_POWER_OFF : off

  Returns:      TRUE   if success
                FALSE  if fail. maybe interval of LCD off->on is too short.
 *---------------------------------------------------------------------------*/
BOOL    PM_SetLCDPower(PMLCDPower sw);

/*---------------------------------------------------------------------------*
  Name:         PM_GetLCDPower

  Description:  get status of LCD power

  Arguments:    None

  Returns:      status.
                PM_LCD_POWER_ON  : on
                PM_LCD_POWER_OFF : off
 *---------------------------------------------------------------------------*/
PMLCDPower PM_GetLCDPower(void);


//================================================================================
//             LED
//================================================================================
u32     PMi_SendLEDPatternCommandAsync(PMLEDPattern pattern, PMCallback callback, void *arg);
u32     PMi_SendLEDPatternCommand(PMLEDPattern pattern);
/*---------------------------------------------------------------------------*
  Name:         PM_SetLEDPatternAsync / PM_SetLEDPattern

  Description:  set up LED blink pattern

  Arguments:    pattern  : LED blink pattern
                callback : callback function
                arg      : callback argument

  Returns:      result of issuing command
                PM_RESULT_BUSY    : busy
                PM_RESULT_SUCCESS : success
 *---------------------------------------------------------------------------*/
inline u32 PM_SetLEDPatternAsync(PMLEDPattern pattern, PMCallback callback, void *arg)
{
    return PMi_SendLEDPatternCommandAsync(pattern, callback, arg);
}
inline u32 PM_SetLEDPattern(PMLEDPattern pattern)
{
    return PMi_SendLEDPatternCommand(pattern);
}

/*---------------------------------------------------------------------------*
  Name:         PM_GetLEDPatternAsync / PM_GetLEDPattern

  Description:  get current LED pattern

  Arguments:    patternBuf  : area to set LED status
                callback    : callback function
                arg         : callback argument

  Returns:      result of issuing command
                PM_RESULT_BUSY    : busy
                PM_RESULT_SUCCESS : success
 *---------------------------------------------------------------------------*/
u32     PM_GetLEDPatternAsync(PMLEDPattern *patternBuf, PMCallback callback, void *arg);
u32     PM_GetLEDPattern(PMLEDPattern *patternBuf);

//================================================================
//         internal functions
//================================================================
//
// these PMi_ functions are internal function.
// don't use these functions
//
//---- sound power
typedef enum
{
    PM_SOUND_POWER_OFF = 0,
    PM_SOUND_POWER_ON = 1
}
PMSoundPowerSwitch;

//---- sound volume control
typedef enum
{
    PM_SOUND_VOLUME_OFF = 0,
    PM_SOUND_VOLUME_ON = 1
}
PMSoundVolumeSwitch;

//---------------- set LCD and LED
BOOL    PMi_SetLCDPower(PMLCDPower sw, PMLEDStatus led, BOOL skip, BOOL isSync);

//---------------- change sound power switch
u32     PMi_SetSoundPowerAsync(PMSoundPowerSwitch sw, PMCallback callback, void *arg);
u32     PMi_SetSoundPower(PMSoundPowerSwitch sw);

//---------------- change sound volume control switch
u32     PMi_SetSoundVolumeAsync(PMSoundVolumeSwitch sw, PMCallback callback, void *arg);
u32     PMi_SetSoundVolume(PMSoundVolumeSwitch sw);

//---------------- get status of sound power switch
u32     PMi_GetSoundPower(PMSoundPowerSwitch *swBuf);

//---------------- get status of sound volume control switch
u32     PMi_GetSoundVolume(PMSoundVolumeSwitch *swBuf);

//---------------- send data to ARM7
void    PMi_SendPxiData(u32 data);

//---------------- callback
void    PMi_CommonCallback(PXIFifoTag tag, u32 data, BOOL err);

//---------------- send sleep command / dispose sleep end
u32     PMi_SendSleepStart(u16 trigger, u16 keyIntrData);
u32     PMi_DisposeSleepEnd(void);

//---------------- read register
u32     PMi_ReadRegisterAsync(u16 registerAddr, u16 *buffer, PMCallback callback, void *arg);
u32     PMi_ReadRegister(u16 registerAddr, u16 *buffer);

//---------------- write register
u32     PMi_WriteRegisterAsync(u16 registerAddr, u16 data, PMCallback callback, void *arg);
u32     PMi_WriteRegister(u16 registerAddr, u16 data);

//---------------- set LED status
u32     PMi_SetLEDAsync(PMLEDStatus status, PMCallback callback, void *arg);
u32     PMi_SetLED(PMLEDStatus status);

//---------------- get counter value LCD turned off
u32     PMi_GetLCDOffCount(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PM_ARM9_H_ */
#endif
