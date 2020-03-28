/*---------------------------------------------------------------------------*
  Project:  NitroSDK - sp/OS
  File:     os.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: os_sp.h,v $
  Revision 1.8  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.7  2004/02/13 00:51:47  yasu
  fix ARM9/ARM7 macro word control

  Revision 1.6  2004/02/12 13:15:32  yasu
  merge to os.h

  Revision 1.5  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.4  2004/02/10 02:04:41  yada
  Removed utility.h

  Revision 1.3  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.2  2003/12/22 14:06:32  yasu
  Include minimum file set that make will run through.

  Revision 1.1  2003/12/16 10:52:11  yasu
  Initial version.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef	SDK_ARM7
#define	SDK_ARM7
#endif
#ifdef	SDK_ARM9
#undef	SDK_ARM9
#endif
#include "nitro/os.h"
