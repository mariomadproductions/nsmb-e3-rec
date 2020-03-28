/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     snd_sp.h

  Copyright 2004,2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: snd_sp.h,v $
  Revision 1.11  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.10  2004/10/15 15:17:55  yasu
  sound patch for NITRO-System 10/12

  Revision 1.3  2004/06/24 02:52:10  nishida
  Fix header comments.

  Revision 1.2  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.6  2004/02/13 00:51:47  yasu
  fix ARM9/ARM7 macro word control

  Revision 1.5  2004/02/12 13:13:42  yasu
  merge to snd.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef		SDK_ARM7
#define		SDK_ARM7
#endif
#ifdef		SDK_ARM9
#undef		SDK_ARM9
#endif
#include "nitro/snd.h"
