/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX
  File:     gx.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: gx.h,v $
  Revision 1.4  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.3  2005/08/10 08:57:36  yasu
  Corrected g3b.c and g3c.c so that they can be compiled on a PC.

  Revision 1.2  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.1  2004/05/14 11:55:54  takano_makoto
  Move gx include description from nitro.h to nitro/gx.h, Because to add SDK_FROM_TOOL.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_GX_H_
#define NITRO_GX_H_

#ifdef __cplusplus
extern "C" {
#endif


#ifdef  SDK_ARM9

#include "nitro/gx/g3.h"
#include "nitro/gx/g3x.h"
#include "nitro/gx/g2.h"
#include "nitro/gx/gx.h"
#include "nitro/gx/gx_vramcnt.h"
#include "nitro/gx/gx_bgcnt.h"
#include "nitro/gx/gx_capture.h"
#include "nitro/gx/g2_oam.h"
#include "nitro/gx/struct_2d.h"
#include "nitro/gx/g3b.h"
#include "nitro/gx/g3c.h"

/* if include from Other Environment for exsample VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

#include "nitro/gx/g3imm.h"
#include "nitro/gx/g3_util.h"
#include "nitro/gx/gx_load.h"

#endif // SDK_FROM_TOOL


#else  //SDK_ARM7

/* if include from Other Environment for exsample VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

#include "nitro/gx/gx_sp.h"

#endif // SDK_FROM_TOOL

#endif




#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_GX_H_ */
#endif
