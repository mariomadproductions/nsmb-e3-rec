/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SPI - include
  File:     api.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mic.h,v $
  Revision 1.13  2006/01/18 02:11:30  kitase_hirotake
  do-indent

  Revision 1.12  2005/02/28 05:26:25  yosizaki
  do-indent.

  Revision 1.11  2005/01/11 07:54:12  takano_makoto
  fix copyright header.

  Revision 1.10  2005/01/07 12:30:24  terui
  Added MIC_AdjustAutoSampling[Async] function

  Revision 1.9  2004/12/03 05:40:03  terui
  Complied with the added feature that explicitly indicates the data that was left out during the MIC auto sampling.

  Revision 1.8  2004/11/04 07:12:12  terui
  Comments revised.

  Revision 1.7  2004/11/02 04:30:47  terui
  Fixed comments.

  Revision 1.6  2004/09/17 09:36:03  terui
  Revised in connection with changes to MIC_StartAutoSampling(Async) parameters.

  Revision 1.5  2004/07/13 09:21:21  terui
  Changes reflecting addition of signed sampling types

  Revision 1.4  2004/06/03 04:09:09  terui
  Changed definition of shortest sampling rate.

  Revision 1.3  2004/06/01 02:02:08  terui
  Added typical sampling rate definitions to MICSamplingRate.

  Revision 1.2  2004/06/01 00:54:39  terui
  Deleted sampling rate definitions.
  Defined shortest sampling period that is supported.

  Revision 1.1  2004/05/31 08:39:06  terui
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SPI_ARM9_MIC_H_
#define NITRO_SPI_ARM9_MIC_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include "nitro/spi/common/type.h"
#include "nitro/pxi.h"


/*---------------------------------------------------------------------------*
    constant definitions
 *---------------------------------------------------------------------------*/
// Process result definition
typedef enum MICResult
{
    MIC_RESULT_SUCCESS = 0,            // Succeeded
    MIC_RESULT_BUSY,                   // Exclusive operation being performed
    MIC_RESULT_ILLEGAL_PARAMETER,      // Illegal parameter
    MIC_RESULT_SEND_ERROR,             // Failed transmission by PXI
    MIC_RESULT_INVALID_COMMAND,        // Unknown command
    MIC_RESULT_ILLEGAL_STATUS,         // Status does not permit execution
    MIC_RESULT_FATAL_ERROR,            // Errors other than those above
    MIC_RESULT_MAX
}
MICResult;

// Sampling type definitions
typedef enum MICSamplingType
{
    MIC_SAMPLING_TYPE_8BIT = 0,        //  8 bit sampling
    MIC_SAMPLING_TYPE_12BIT,           // 12 bit sampling
    MIC_SAMPLING_TYPE_SIGNED_8BIT,     // Signed 8-bit sampling
    MIC_SAMPLING_TYPE_SIGNED_12BIT,    // Signed 12-bit sampling
    MIC_SAMPLING_TYPE_12BIT_FILTER_OFF,
    MIC_SAMPLING_TYPE_SIGNED_12BIT_FILTER_OFF,
    MIC_SAMPLING_TYPE_MAX
}
MICSamplingType;

// Typical sampling periods are defined in ARM7 clock ticks
typedef enum MICSamplingRate
{
    MIC_SAMPLING_RATE_8K = (HW_CPU_CLOCK_ARM7 / 8000),  // Approx. 8.0 kHz
    MIC_SAMPLING_RATE_11K = (HW_CPU_CLOCK_ARM7 / 11025),        // Approx. 11.025 kHz
    MIC_SAMPLING_RATE_16K = (HW_CPU_CLOCK_ARM7 / 16000),        // Approx. 16.0 kHz
    MIC_SAMPLING_RATE_22K = (HW_CPU_CLOCK_ARM7 / 22050),        // Approx. 22.05 kHz
    MIC_SAMPLING_RATE_32K = (HW_CPU_CLOCK_ARM7 / 32000),        // Approx. 32.0 kHz
    MIC_SAMPLING_RATE_LIMIT = 1024
}
MICSamplingRate;

/*---------------------------------------------------------------------------*
    structure definitions
 *---------------------------------------------------------------------------*/
// Callback function type definition
typedef void (*MICCallback) (MICResult result, void *arg);

// Auto-sampling setting definitions
typedef struct MICAutoParam
{
    MICSamplingType type;              // Sampling type
    void   *buffer;                    // Pointer to result storage buffer
    u32     size;                      // Buffer size
    u32     rate;                      // Sampling period (ARM7 clock count)
    BOOL    loop_enable;               // Enable/disable loop when buffer is full
    MICCallback full_callback;         // Callback when buffer is full
    void   *full_arg;                  // Argument to specify for the above callbacks

}
MICAutoParam;


/*---------------------------------------------------------------------------*
    function definitions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
  Name:         MIC_Init

  Description:  Initializes microphone library.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MIC_Init(void);

/*---------------------------------------------------------------------------*
  Name:         MIC_DoSamplingAsync

  Description:  Performs a single async sample of the mic.

  Arguments:    type      - The sampling type.
                buf       - Buffer that stores the sampling data.
                callback  - Specifies the function to be called when the asynchronous process completed.
                arg       - Specifies the argument used when calling the callback function.

  Returns:      MICResult - Returns the result of the start of the asynchronous operation.
 *---------------------------------------------------------------------------*/
MICResult MIC_DoSamplingAsync(MICSamplingType type, void *buf, MICCallback callback, void *arg);

/*---------------------------------------------------------------------------*
  Name:         MIC_StartAutoSamplingAsync

  Description:  Starts mic auto sampling asynchronously.

  Arguments:    param     - Specifies the auto sampling setting with the pointer to the structure.
                callback  - Specifies the function to be called when the asynchronous process completed.
                arg       - Specifies the argument used when calling the callback function.

  Returns:      MICResult - Returns the result of the start of the asynchronous operation.
 *---------------------------------------------------------------------------*/
MICResult MIC_StartAutoSamplingAsync(const MICAutoParam *param, MICCallback callback, void *arg);

/*---------------------------------------------------------------------------*
  Name:         MIC_StopAutoSamplingAsync

  Description:  Stops auto-sampling with the mic asynchronously.

  Arguments:    callback  - Specifies the function to be called when the asynchronous process completed.
                arg       - Specifies the argument used when calling the callback function.

  Returns:      MICResult - Returns the result of the start of the asynchronous operation.
 *---------------------------------------------------------------------------*/
MICResult MIC_StopAutoSamplingAsync(MICCallback callback, void *arg);

/*---------------------------------------------------------------------------*
  Name:         MIC_AdjustAutoSamplingAsync

  Description:  Asynchronously adjusts the sampling rate used in microphone auto sampling.
                microphone's auto-sampling process

  Arguments:    rate      - Specifies the sampling rate.
                callback  - Specifies the function to be called when the asynchronous process completed.
                arg       - Specifies the argument used when calling the callback function.

  Returns:      MICResult - Returns the result of the start of the asynchronous operation.
 *---------------------------------------------------------------------------*/
MICResult MIC_AdjustAutoSamplingAsync(u32 rate, MICCallback callback, void *arg);

/*---------------------------------------------------------------------------*
  Name:         MIC_GetLastSamplingAddress

  Description:  Gets the address where the most recent mic sampling result is stored.

  Arguments:    None.

  Returns:      void* - Returns the storage address of the sampling result.
                        Returns NULL if not yet sampling.
 *---------------------------------------------------------------------------*/
void   *MIC_GetLastSamplingAddress(void);

/*---------------------------------------------------------------------------*
  Name:         MIC_DoSampling

  Description:  Samples the mic once.

  Arguments:    type      - The sampling type.
                buf       - Buffer that stores the sampling data.

  Returns:      MICResult - Returns the result of device operation process.
 *---------------------------------------------------------------------------*/
MICResult MIC_DoSampling(MICSamplingType type, void *buf);

/*---------------------------------------------------------------------------*
  Name:         MIC_StartAutoSampling

  Description:  Starts auto-sampling with the mic.

  Arguments:    param     - Specifies the auto sampling setting with the pointer to the structure.

  Returns:      MICResult - Returns the result of device operation process.
 *---------------------------------------------------------------------------*/
MICResult MIC_StartAutoSampling(const MICAutoParam *param);

/*---------------------------------------------------------------------------*
  Name:         MIC_StopAutoSampling

  Description:  Stops auto-sampling with the mic.
                If a loop was not specified at the start of auto-sampling,
                it stops sampling automatically at the point where the buffer is full.

  Arguments:    None.

  Returns:      MICResult - Returns the result of device operation process.
 *---------------------------------------------------------------------------*/
MICResult MIC_StopAutoSampling(void);

/*---------------------------------------------------------------------------*
  Name:         MIC_AdjustAutoSampling

  Description:  Adjusts the sampling rate of the microphone automatic sampling.

  Arguments:    rate      - Specifies the sampling rate.

  Returns:      MICResult - Returns the result of device operation process.
 *---------------------------------------------------------------------------*/
MICResult MIC_AdjustAutoSampling(u32 rate);


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_RTC_ARM9_API_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
