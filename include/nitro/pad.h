/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PAD
  File:     pad.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: pad.h,v $
  Revision 1.2  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.1  2004/02/18 01:23:03  yada
  Newly created because pad region is divided ARM7/9.


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PAD_H_
#define NITRO_PAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/pad/common/pad.h"

#ifdef	SDK_ARM9
#else
#include "nitro/pad/ARM7/xyButton.h"
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PAD_H_ */
#endif
