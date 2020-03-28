/*---------------------------------------------------------------------------*
  Project:  NitroSDK - EXI
  File:     exi.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: exi.h,v $
  Revision 1.2  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.1  2004/02/18 01:24:01  yada
  firstRelease


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_EXI_H_
#define NITRO_EXI_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	SDK_ARM9
// include notiong
#else
#include "nitro/exi/ARM7/genPort.h"
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_EXI_H_ */
#endif
