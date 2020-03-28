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
  Revision 1.4  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.3  2005/02/16 23:51:41  terui
  Update copyright.

  Revision 1.2  2005/02/16 10:32:54  terui
  Added an ARM9 side include path

  Revision 1.1  2004/12/20 00:43:47  terui
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_WVR_H_
#define NITRO_WVR_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#ifdef  SDK_ARM9

#include "nitro/wvr/common/wvr_common.h"
#include "nitro/wvr/ARM9/wvr.h"

#else  /* SDK_ARM7 */

#include "nitro/wvr/common/wvr_common.h"
#include "nitro/wvr/ARM7/wvr_sp.h"

#endif

/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_WVR_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
