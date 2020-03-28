/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PXI
  File:     pxi.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: pxi.h,v $
  Revision 1.5  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.4  2004/03/08 01:54:59  yasu
  add init.h

  Revision 1.3  2004/03/04 08:44:37  yasu
  add defines for fifo access

  Revision 1.2  2004/02/27 01:56:58  yasu
  make new header compparam.h

  Revision 1.1  2004/02/14 06:28:12  yasu
  interProcessor Transport Interface

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PXI_H_
#define NITRO_PXI_H_

//#include "nitro/pxi/common/lowlevel.h"
#include "nitro/pxi/common/init.h"
#include "nitro/pxi/common/compparam.h"
#include "nitro/pxi/common/fifo.h"
#include "nitro/pxi/common/regname.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	SDK_ARM9
#else  //SDK_ARM7
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* NITRO_PXI_H_ */
#endif
