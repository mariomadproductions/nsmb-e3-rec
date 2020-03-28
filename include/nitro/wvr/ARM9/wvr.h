/*---------------------------------------------------------------------------*
  Project:  NitroSDK - WVR - include
  File:     wvr.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: wvr.h,v $
  Revision 1.3  2005/02/28 05:26:35  yosizaki
  do-indent.

  Revision 1.2  2005/02/09 09:13:16  terui
  Added parameters to StartUp function.
  Corrected function explanations to reflect ability to specify VRAM.

  Revision 1.1  2004/12/20 00:44:36  terui
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_WVR_ARM9_WVR_H_
#define NITRO_WVR_ARM9_WVR_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include "nitro/gx/gx_vramcnt.h"

// Callback function type for asynchronous API
typedef void (*WVRCallbackFunc) (void *arg, WVRResult result);


/*---------------------------------------------------------------------------*
  Name:         WVR_StartUpAsync

  Description:  Starts operations of the wireless library.
                Until forcedly stopped, access to the specified VRAM (C or D) is prohibited.

  Arguments:    vram        -   Specifies VRAM bank allocated to ARM7.
                callback    -   Specifies callback function at time process ends.
                arg         -   Specifies argument passed to callback functions.

  Returns:      The result of the process.
 *---------------------------------------------------------------------------*/
WVRResult WVR_StartUpAsync(GXVRamARM7 vram, WVRCallbackFunc callback, void *arg);

/*---------------------------------------------------------------------------*
  Name:         WVR_TerminateAsync

  Description:  Forcedly stops operations of the wireless library.
                Access to VRAM (C or D) is permitted after this asynchronous process is completed.

  Arguments:    callback    -   Specifies callback function at time process ends.
                arg         -   Specifies argument passed to callback functions.

  Returns:      The result of the process.
 *---------------------------------------------------------------------------*/
WVRResult WVR_TerminateAsync(WVRCallbackFunc callback, void *arg);


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_WVR_ARM9_WVR_H_ */

/*---------------------------------------------------------------------------*
    End of file
 *---------------------------------------------------------------------------*/
