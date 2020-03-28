/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     memorymap_sp.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: memorymap_sp.h,v $
  Revision 1.6  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.5  2004/02/13 00:51:47  yasu
  fix ARM9/ARM7 macro word control

  Revision 1.4  2004/02/12 13:17:55  yasu
  merge to memorymap.h

  Revision 1.3  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.2  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.1  2003/12/22 14:05:31  yasu
  new additions

  Revision 1.2  2003/12/17 06:05:39  yasu
  split mmap_reserved.h into mmap_tcm.h and mmap_shared.h

  Revision 1.1  2003/12/09 08:35:26  yasu
  Revamped the memory map and the related area

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef	SDK_ARM7
#define	SDK_ARM7
#endif
#ifdef	SDK_ARM9
#undef	SDK_ARM9
#endif
#include "nitro/memorymap.h"
