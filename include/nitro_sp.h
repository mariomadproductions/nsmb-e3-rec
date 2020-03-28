/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     nitro_sp.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: nitro_sp.h,v $
  Revision 1.10  2005/02/28 05:26:27  yosizaki
  do-indent.

  Revision 1.9  2004/02/13 02:42:01  yasu
  fix ARM9/ARM7 macro word control

  Revision 1.8  2004/02/12 13:12:13  yasu
  merge nitro.h and nitro_sp.h

  Revision 1.7  2004/02/10 02:04:59  yada
  mi/*.h was increased, so it was put together into mi.h

  Revision 1.6  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.5  2003/12/22 14:07:05  yasu
  Essential file corrections

  Revision 1.4  2003/12/22 04:01:47  ida
  Added snd/snd.h

  Revision 1.3  2003/12/16 10:52:29  yasu
  Added file

  Revision 1.2  2003/12/16 05:26:45  yasu
  Changed ioreg file name

  Revision 1.1  2003/11/13 02:29:56  yasu
  Moved from below include/iris to directly below include

  Revision 1.1  2003/11/12 12:33:50  yasu
  Initial version.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef		SDK_ARM7
#define		SDK_ARM7
#endif
#ifdef		SDK_ARM9
#undef		SDK_ARM9
#endif
#include "nitro.h"
