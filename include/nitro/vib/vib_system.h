/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include - nitro - vib
  File:     vib_system.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: vib_system.h,v $
  Revision 1.3  2007/01/22 08:48:12  okubata_ryoma
  Added log

  Revision 1.2  2006/03/03 00:35:00  okubata_ryoma
  Moved 'include' to outside of extern"C"

  Revision 1.1  2006/03/02 10:22:14  okubata_ryoma
  Added vib_system.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef PULSE_VIB_H
#define PULSE_VIB_H

#include "nitro.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*
                    Type, Constant
 *-----------------------------------------------------------------------*/

/*!
    Maximum number of pulses in pulse set Rebuild the library if changes are made.
*/
#define VIB_PULSE_NUM_MAX   6

/*!
    Maximum value of on_time at one time (in 0.1ms units)
*/
#define VIB_ON_TIME_MAX 15

/*!
    Minimum value of rest_time (in 0.1ms units)
*/
#define VIB_REST_TIME_MIN   15

/*!
    Displays the status of the pulse rumble.
    
    The standard rumble is a pulse that is 1.5ms ON, 1.5ms OFF, and 1.5ms ON.
    This allows generation of the strongest rumble.
    
    The hardware specifications demand that value of demand must follow the rules below.
    
    @li A single on_time must not exceed 1.5ms.
    @li off_time[n] must be set to a value that exceeds that of the previous on_time[n].
    @li rest_time must exceed 1.5ms.
    
    Note that these conditions are checked when the VIB_StartPulse function is called.
    
    @image html pulse_vib.jpg "Pulse rumble example (when pulse count is three)"
*/
typedef struct
{
    u32     pulse_num;                  /*! How many pulses to generates in a single pulse set. Must be at least one and less than VIB_PULSE_NUM_MAX. */
    u32     rest_time;                  /*! Length of pause during pulse-set period. 1=0.1 millisecond */
    u32     on_time[VIB_PULSE_NUM_MAX]; /*! Length of start time. Set a value larger than 0. 1=0.1 millisecond */
    u32     off_time[VIB_PULSE_NUM_MAX];/*! Length of stop time. Set a value larger than 0. 1=0.1 millisecond */
    u32     repeat_num;                 /*! Number of times to repeat pulse set. When 0, repeats endlessly. */
}
VIBPulseState;

/*! Cartridge-removal callback type. */
typedef void (*VIBCartridgePulloutCallback) (void);

/*-----------------------------------------------------------------------*
                    Function external declaration
 *-----------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         VIB_Init

  Description:  Initializes Rumble Pak library.
                If this function is called again after it has been called once,
                it has the same effect as the VIB_IsCartridgeEnabled function.
                
                Inside this function, before entering sleep mode using the PM_AppendPreSleepCallback function,
                the callback that stops the rumble is registered.
                
                This function also registers the callback that stops rumbling when cartridge removal is detected.
                Accordingly, after calling this function, if you set the cartridge removal callback with the CTRDG_SetPulledOutCallback function,
                the cartridge removal detection callback set with VIB_Init is overwritten.
                In that case, you need to stop the rumbling inside the cartridge removal callback that was set.
                If you want to perform processing that goes beyond stopping rumbling inside the cartridge removal callback,
                register the callback using the VIB_SetCartridgePulloutCallback function,
                and perform it inside that callback. 

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL VIB_Init(void);

/*---------------------------------------------------------------------------*
  Name:         VIB_End

  Description:  Terminate usage of the Rumble Pak library.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void VIB_End(void);

/*---------------------------------------------------------------------------*
  Name:         VIB_StartPulse

  Description:  Start pulse rumble.
                If the previous pulse rumble has not been completed, stop it and then start.
                Because the status is copied on the library side, there is no need to allocate memory.

  Arguments:    state : Pulse rumble status

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void VIB_StartPulse(const VIBPulseState * state);

/*---------------------------------------------------------------------------*
  Name:         VIB_StopPulse

  Description:  Stops pulse rumble.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void VIB_StopPulse(void);

/*---------------------------------------------------------------------------*
  Name:         VIB_StopPulse

  Description:  Determines whether pulse rumble is in progress.
                Returns TRUE from the time when rumble is turned on using the VIB_StartPulse function until the time when rumble is turned off using the VIB_StopPulse function.

  Arguments:    None.

  Returns:      TRUE  : State in which pulse rumble is in progress
                FALSE : State in which pulse rumble is not in progress
 *---------------------------------------------------------------------------*/
extern BOOL VIB_IsExecuting(void);

/*---------------------------------------------------------------------------*
  Name:         VIB_SetCartridgePulloutCallback

  Description:  Register the Game Pak removal callback.
                When Game Pak removal occurs, the library immediately stops the pulse rumble.
                If the callback is registered using this function, the callback is called afterwards. 

  Arguments:    func     : Cartridge removal callback

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void VIB_SetCartridgePulloutCallback(VIBCartridgePulloutCallback func);

/*---------------------------------------------------------------------------*
  Name:         VIB_IsCartridgeEnabled

  Description:  Determines whether a Rumble Pak is inserted.

  Arguments:    None.

  Returns:      TRUE  : State in which rumble pack was inserted at startup
                FALSE : State in which rumble pack was not inserted at startup
 *---------------------------------------------------------------------------*/
extern BOOL VIB_IsCartridgeEnabled(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* PULSE_VIB_H */
