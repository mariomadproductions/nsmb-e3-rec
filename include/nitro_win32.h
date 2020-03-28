/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     nitro_win32.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: nitro_win32.h,v $
  Revision 1.14  2006/01/18 02:11:30  kitase_hirotake
  do-indent

  Revision 1.13  2005/09/08 11:32:44  yasu
  Support for structures without member names in VC.net

  Revision 1.12  2005/09/08 11:19:20  yasu
  Switched from SDK_WIN32 to SDK_FROM_TOOL.

  Revision 1.11  2005/09/08 00:56:29  yasu
  Added SDK_WIN32 definitions

  Revision 1.10  2005/08/10 08:58:03  yasu
  Corrected g3b.c and g3c.c so that they can be compiled on a PC.

  Revision 1.9  2005/07/21 07:06:28  yada
  add argument.h

  Revision 1.8  2005/02/28 05:26:27  yosizaki
  do-indent.

  Revision 1.7  2004/07/28 11:32:33  takano_makoto
  Change default included type to SDK_ARM9.

  Revision 1.6  2004/06/14 04:46:34  takano_makoto
  Define SDK_ARM9

  Revision 1.5  2004/06/14 04:16:11  takano_makoto
  Add fx.h, fx_const.h

  Revision 1.4  2004/05/24 05:47:30  kitani_toshikazu
  fix header file's path.

  Revision 1.3  2004/05/21 09:31:00  kitani_toshikazu
  added #include "nitro/g3.h"

  Revision 1.2  2004/05/21 08:44:17  yasu
  fix typo

  Revision 1.1  2004/05/20 10:18:51  yasu
  Nitro Header for VC, BCB etc

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_WIN32_H_
#define NITRO_WIN32_H_

//
//  NITRO HEADER for Win32 (VC,BCB or gcc)
//
#ifndef SDK_FROM_TOOL
#define SDK_FROM_TOOL
#endif

#ifndef SDK_WIN32
#define SDK_WIN32
#endif

#ifndef SDK_HAS_LONG_LONG_INT
#define SDK_HAS_NO_LONG_LONG_INT_
#endif

// Default SDK_ARM9
#ifndef SDK_ARM7
#define SDK_ARM9
#endif

#ifdef  _MSC_VER
#pragma warning(disable:4201)          // warning for nameless structure definition
#endif

#include "nitro/gx.h"

#include "nitro/memorymap.h"
#include "nitro/types.h"

#include "nitro/fx/fx.h"
#include "nitro/fx/fx_const.h"

#include "nitro/os/ARM9/argument.h"

#ifdef  _MSC_VER
#pragma warning(default:4201)
#endif

#endif //NITRO_WIN32_H_
