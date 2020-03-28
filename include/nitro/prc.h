/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PRC - include
  File:     prc.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: prc.h,v $
  Revision 1.7  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.6  2004/07/19 06:52:06  seiki_masashi
  Arrangement of identifier names

  Revision 1.5  2004/06/30 08:49:45  seiki_masashi
  algo_simple -> algo_light
  algo_standard -> algo_fine
  algo_accurate -> algo_superfine
  Addition of new algo_standard

  Revision 1.4  2004/06/25 13:32:01  seiki_masashi
  Addition of recognition algorithm "Standard"

  Revision 1.3  2004/06/24 08:10:50  seiki_masashi
  Addition of recognition algorithm "Accurate"

  Revision 1.2  2004/06/24 07:03:16  seiki_masashi
  Partitioned and arranged header file

  Revision 1.1  2004/06/23 12:00:29  seiki_masashi
  add 'PRC*' to SDK

  Revision 1.5  2004/06/22 11:19:00  seiki_masashi
  Operable Version (simple only)

  Revision 1.4  2004/06/17 08:14:52  seiki_masashi
  PRC_GetPrototypeDBBufferSizeEx

  Revision 1.3  2004/06/17 02:30:29  seiki_masashi
  In order to allow easy replacement of the rethe recognition algorithm, divided at prc_algo_*

  Revision 1.2  2004/06/17 00:52:36  seiki_masashi
  PRC_InitPrototypeDBEX, PRC_InitInputPatternEX

  Revision 1.1  2004/06/16 23:56:09  seiki_masashi
  Renamed ptrcg to prc.

  Revision 1.3  2004/06/15 08:10:55  seiki_masashi
  Sample programs made operable with the dummy library

  Revision 1.2  2004/06/15 05:55:09  seiki_masashi
  Interface improvements

  Revision 1.1  2004/06/15 00:54:42  seiki_masashi
  Interface design


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PRC_H_
#define NITRO_PRC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"

/*===========================================================================*
  Constant Definitions
 *===========================================================================*/

/*===========================================================================*
  Type Definitions
 *===========================================================================*/

/*---------------------------------------------------------------------------*
  Declaration of Algorithm Dependency Type
 *---------------------------------------------------------------------------*/

#include "nitro/prc/algo_standard.h"
#include "nitro/prc/algo_light.h"
#include "nitro/prc/algo_fine.h"
#include "nitro/prc/algo_superfine.h"

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PRC_H_ */
#endif
