/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SPI
  File:     spi.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: spi.h,v $
  Revision 1.11  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.10  2004/08/24 05:18:31  yada
  add pm.h to ARM7's include

  Revision 1.9  2004/08/02 00:41:14  yada
  add pm.h

  Revision 1.8  2004/05/31 08:40:51  terui
  Add include ARM9/mic.h

  Revision 1.7  2004/05/28 08:48:41  terui
  Add include common/type.h

  Revision 1.6  2004/05/20 09:38:32  terui
  Delete ARM9 nvram.h
  Add common config.h

  Revision 1.5  2004/05/19 12:34:54  terui
  Add NVRAM library for ARM9.

  Revision 1.4  2004/04/22 00:43:52  takano_makoto
  Fix ifdef statement.

  Revision 1.3  2004/04/21 12:10:03  takano_makoto
  Add ARM9 TP library

  Revision 1.2  2004/04/15 11:27:11  takano_makoto
  move spi/spi.h to spi/ARM7/spi.h.

  Revision 1.1  2004/03/10 05:36:01  yada
  firstRelease

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SPI_H_
#define NITRO_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "nitro/spi/common/config.h"
#include "nitro/spi/common/type.h"

#ifdef  SDK_ARM9

#include "nitro/spi/ARM9/tp.h"
#include "nitro/spi/ARM9/mic.h"
#include "nitro/spi/ARM9/pm.h"

#else  // SDK_ARM7

#include "nitro/spi/ARM7/spi.h"
#include "nitro/spi/ARM7/pm.h"

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_SPI_H_ */
#endif
