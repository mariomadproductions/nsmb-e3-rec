/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SPI - TP
  File:     tp.h
  
  Copyright 2003-2006 Nintendo.  All rights reserved.
  
  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.
  
  $Log: tp.h,v $
  Revision 1.15  2006/01/18 02:12:27  kitase_hirotake
  do-indent

  Revision 1.14  2005/02/28 05:26:26  yosizaki
  do-indent.

  Revision 1.13  2004/12/29 03:59:49  takano_makoto
  Added retry parameter to the arguments of TP_RequestSetStability function to maintain compatibility with older versions (not used internally)

  Revision 1.12  2004/12/29 02:09:11  takano_makoto
  Removed retry parameter in SetStability function

  Revision 1.11  2004/06/10 05:27:03  yasu
  Add TP_GetCalibratedResult

  Revision 1.10  2004/06/02 06:15:27  takano_makoto
  Changed arguments for TP_RequestAutoSamplingStart(), TP_SetCallback()

  Revision 1.9  2004/05/21 09:52:51  takano_makoto
  Added TP_GetUserInfo()

  Revision 1.8  2004/05/14 00:41:48  takano_makoto
  Modify Calibrate Parameter format.

  Revision 1.7  2004/04/22 09:02:27  takano_makoto
  Add include type.h and misc.h

  Revision 1.6  2004/04/21 12:08:56  takano_makoto
  Add Async function.

  Revision 1.5  2004/04/19 12:00:36  takano_makoto
  Add TPCommandFlag.

  Revision 1.4  2004/04/16 02:13:53  takano_makoto
  Modify for STRB warning.

  Revision 1.3  2004/04/15 13:55:07  takano_makoto
  Chang any function name.

  Revision 1.2  2004/04/15 11:54:46  takano_makoto
  Change define to NITRO_SPI_ARM9_TP_H

  Revision 1.1  2004/04/15 11:01:26  takano_makoto
  Initial Update.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SPI_ARM9_TP_H_
#define NITRO_SPI_ARM9_TP_H_

#include "nitro/misc.h"
#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif


#define     TP_SAMPLING_FREQUENCY_MAX   16      // Sampling frequency limit

// Touch panel contact
#define     TP_TOUCH_OFF                0       // Not being touched
#define     TP_TOUCH_ON                 1       // Being touched

// Touch panel data validity
#define     TP_VALIDITY_VALID           0       // Valid
#define     TP_VALIDITY_INVALID_X       1       // Data with invalid X coordinate
#define     TP_VALIDITY_INVALID_Y       2       // Data with invalid Y coordinate
#define     TP_VALIDITY_INVALID_XY      (TP_VALIDITY_INVALID_X | TP_VALIDITY_INVALID_Y) // Data with invalid X and Y coordinates

// Types of commands issued to the touch panel
typedef enum
{
    TP_REQUEST_COMMAND_SAMPLING = 0x0, // Performs sampling once
    TP_REQUEST_COMMAND_AUTO_ON = 0x1,  // Starts auto sampling
    TP_REQUEST_COMMAND_AUTO_OFF = 0x2, // Stops auto sampling
    TP_REQUEST_COMMAND_SET_STABILITY = 0x3,     // Sets the chattering value
    TP_REQUEST_COMMAND_AUTO_SAMPLING = 0x10     // Receive the result of auto sampling
}
TPRequestCommand;

// Command flags to touch panel
typedef enum
{
    TP_REQUEST_COMMAND_FLAG_SAMPLING = 1 << TP_REQUEST_COMMAND_SAMPLING,        // Performs sampling once
    TP_REQUEST_COMMAND_FLAG_AUTO_ON = 1 << TP_REQUEST_COMMAND_AUTO_ON,  // Starts auto sampling
    TP_REQUEST_COMMAND_FLAG_AUTO_OFF = 1 << TP_REQUEST_COMMAND_AUTO_OFF,        // Stops auto sampling
    TP_REQUEST_COMMAND_FLAG_SET_STABILITY = 1 << TP_REQUEST_COMMAND_SET_STABILITY       // Sets the chattering value
}
TPRequestCommandFlag;

// Types of results from touch panel
typedef enum
{
    TP_RESULT_SUCCESS = 0,             // Succeeded
    TP_RESULT_INVALID_PARAMETER,       // Parameter is abnormal
    TP_RESULT_ILLEGAL_STATUS,          // State that cannot receive instructions
    TP_RESULT_EXCLUSIVE,               // SPI device is busy
    TP_RESULT_PXI_BUSY                 // PXI communication with ARM7 is busy
}
TPRequestResult;

// Touch panel status
typedef enum
{
    TP_STATE_READY = 0,                // Ready status
    TP_STATE_SAMPLING,                 // Currently requesting sampling
    TP_STATE_AUTO_SAMPLING,            // Currently auto sampling
    TP_STATE_AUTO_WAIT_END             // Waiting for auto sampling to end
}
TPState;

/*---------------------------------------------------------------------------*
    Structures definition
 *---------------------------------------------------------------------------*/

// Touch panel input structure
typedef struct
{
    u16     x;                         // x coordinate ( 0 - 4095 )
    u16     y;                         // y coordinate ( 0 - 4095 )
    u16     touch;                     // Touch yes/no
    u16     validity;                  // Valid yes/no
}
TPData;


#define TP_CALIBRATE_DOT_SCALE_SHIFT        8   // X dot size precision
#define TP_CALIBRATE_ORIGIN_SCALE_SHIFT     2   // Origin coordinate precision

// Touch Panel Calibration Data
typedef struct NvTpData
{
    s16     x0;                        // X origin coordinate
    s16     y0;                        // Y origin coordinate
    s16     xDotSize;                  // X dot size
    s16     yDotSize;                  // Y dot size
}
TPCalibrateParam;                      // 8 bytes


// User callback function
typedef void (*TPRecvCallback) (TPRequestCommand command, TPRequestResult result, u16 index);

/*===========================================================================*
    Function definition
 *===========================================================================*/
void    TP_Init(void);
void    TP_SetCallback(TPRecvCallback callback);
void    TP_SetCalibrateParam(const TPCalibrateParam *param);

void    TP_RequestSamplingAsync(void);
u32     TP_WaitRawResult(TPData *result);
u32     TP_WaitCalibratedResult(TPData *result);
u32     TP_GetCalibratedResult(TPData *result);
void    TP_RequestAutoSamplingStartAsync(u16 vcount, u16 frequence, TPData samplingBufs[],
                                         u16 bufSize);
void    TP_RequestAutoSamplingStopAsync(void);
void    TP_RequestSetStabilityAsync(u8 retry, u16 range);
void    TP_WaitBusy(TPRequestCommandFlag command_flgs);
void    TP_WaitAllBusy(void);
u32     TP_CheckBusy(TPRequestCommandFlag command_flgs);
u32     TP_CheckError(TPRequestCommandFlag command);

void    TP_GetLatestRawPointInAuto(TPData *result);
void    TP_GetLatestCalibratedPointInAuto(TPData *result);
u16     TP_GetLatestIndexInAuto(void);
u32     TP_CalcCalibrateParam(TPCalibrateParam *calibrate,
                              u16 raw_x1, u16 raw_y1,
                              u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2, u16 dx2, u16 dy2);
BOOL    TP_GetUserInfo(TPCalibrateParam *calibrate);
void    TP_GetCalibratedPoint(TPData *disp, const TPData *raw);
void    TP_GetUnCalibratedPoint(u16 *raw_x, u16 *raw_y, u16 dx, u16 dy);

/*---------------------------------------------------------------------------*
    Inline function definition
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
  Name:         TP_RequestSetStability

  Description:  Sets touch panel chattering parameters.
                Sets the number of times to retry sampling until values stabilize
                and a range for determining whether values have stabilized.

  Arguments:    retry -  This argument is not used internally.
                range -  Range for determining whether the values have stabilized.
                         (Range: 0 to 255, Default value:
                
  Returns:      u32   - If request succeeds, 0
                        If request fails, other than 0.
 *---------------------------------------------------------------------------*/
static inline u32 TP_RequestSetStability(u8 retry, u16 range)
{
    TP_RequestSetStabilityAsync(retry, range);
    TP_WaitBusy(TP_REQUEST_COMMAND_FLAG_SET_STABILITY);
    return TP_CheckError(TP_REQUEST_COMMAND_FLAG_SET_STABILITY);
}


/*---------------------------------------------------------------------------*
  Name:         TP_RequestAutoSamplingStart

  Description:  Sends a request to ARM7 to start auto sampling touch panel values.
                In one frame, data is sampled "frequence" times at equal intervals.
                The result is stored in the array specified by samplingBus.

  Arguments:    vcount       - Sets the VCOUNT value, which is the base for auto sampling.
                frequence    - Setting for the number of times sampling will be done in one frame.
                samplingBufs - Sets the area where auto sampling data will be stored.
                               An area of the size "frequence" must be made available at minimum.

  Returns:      u32    - If request succeeds, 0
                         If request fails, other than 0.
 *---------------------------------------------------------------------------*/
static inline u32 TP_RequestAutoSamplingStart(u16 vcount, u16 frequence, TPData samplingBufs[],
                                              u16 bufSize)
{
    TP_RequestAutoSamplingStartAsync(vcount, frequence, samplingBufs, bufSize);
    TP_WaitBusy(TP_REQUEST_COMMAND_FLAG_AUTO_ON);
    return TP_CheckError(TP_REQUEST_COMMAND_FLAG_AUTO_ON);
}


/*---------------------------------------------------------------------------*
  Name:         TP_RequestAutoSamplingStop

  Description:  Sends a request to ARM7 to stop auto sampling touch panel values.

  Arguments:    None.

  Returns:      u32    - If request succeeds, 0
                         If request fails, other than 0.
 *---------------------------------------------------------------------------*/
static inline u32 TP_RequestAutoSamplingStop(void)
{
    TP_RequestAutoSamplingStopAsync();
    TP_WaitBusy(TP_REQUEST_COMMAND_FLAG_AUTO_OFF);
    return TP_CheckError(TP_REQUEST_COMMAND_FLAG_AUTO_OFF);
}


/*---------------------------------------------------------------------------*
  Name:         TP_RequestRawSampling

  Description:  Requests ARM7 for touch panel values, and reads uncalibrated,
                raw values.
                Chattering measures have been taken for the data that is acquired here.
                Cannot be used while auto sampling.
                
  Arguments:    None.

  Returns:      result - Pointer to a variable that is used to acquire touch panel values.
                         Takes uncalibrated values (0 - 4095) as x,y coordinates.
                
                u32    - If request succeeds, 0
                         If request fails, other than 0.
 *---------------------------------------------------------------------------*/
static inline u32 TP_RequestRawSampling(TPData *result)
{
    TP_RequestSamplingAsync();
    return TP_WaitRawResult(result);
}

/*---------------------------------------------------------------------------*
  Name:         TP_RequestCalibratedSampling

  Description:  Requests touch panel values from ARM7, and reads values that corresponds to the calibrated screen coordinate.
                Chattering measures have been taken for the data that is acquired here.
                Cannot be used while auto sampling.
                
  Arguments:    None.

  Returns:      result - Pointer to a variable that is used to acquire touch panel values.
                         The x, y coordinates will be the values corresponding to the screen coordinates.
                         If no calibration parameter has been set, touch panel values in the range (0-4095) can be obtained.
                
                u32    - If request succeeds, 0
                         If request fails, other than 0.
 *---------------------------------------------------------------------------*/
static inline u32 TP_RequestCalibratedSampling(TPData *result)
{
    TP_RequestSamplingAsync();
    return TP_WaitCalibratedResult(result);
}



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
/* NITRO_SPI_ARM9_TP_H_ */
