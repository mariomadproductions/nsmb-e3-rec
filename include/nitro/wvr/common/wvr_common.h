/*---------------------------------------------------------------------------*
  Project:  NitroSDK - WVR - include
  File:     wvr_common.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: wvr_common.h,v $
  Revision 1.3  2005/02/28 05:26:35  yosizaki
  do-indent.

  Revision 1.2  2005/02/09 09:12:08  terui
  Added RESULT class

  Revision 1.1  2004/12/20 00:44:16  terui
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_WVR_COMMON_WVR_COMMON_H_
#define NITRO_WVR_COMMON_WVR_COMMON_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*===========================================================================*/

// API process results
typedef enum WVRResult
{
    WVR_RESULT_SUCCESS = 0,            // Succeeded
    WVR_RESULT_OPERATING,              // Successful start of asynchronous process
    WVR_RESULT_DISABLE,                // Component does not support WVR library
    WVR_RESULT_INVALID_PARAM,          // Invalid parameter specified
    WVR_RESULT_FIFO_ERROR,             // PXI transmission request to ARM7 has failed
    WVR_RESULT_ILLEGAL_STATUS,         // Requests cannot be executed in this state
    WVR_RESULT_VRAM_LOCKED,            // VRAM locked. Cannot use.
    WVR_RESULT_FATAL_ERROR,            // Unexpected fatal error

    WVR_RESULT_MAX
}
WVRResult;

// PXI Command
#define     WVR_PXI_COMMAND_STARTUP     0x00010000
#define     WVR_PXI_COMMAND_TERMINATE   0x00020000


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_WVR_COMMON_WVR_COMMON_H_ */

/*---------------------------------------------------------------------------*
    End of file
 *---------------------------------------------------------------------------*/
