/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CTRDG - include
  File:     ctrdg.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: ctrdg.h,v $
  Revision 1.4  2006/04/05 10:30:06  okubata_ryoma
  changes made for AGB backup library's SDK collection

  Revision 1.3  2005/04/05 23:52:58  yosizaki
  fix copyright date.

  Revision 1.2  2004/09/14 06:09:44  yada
  check cartridge pulled out in ARM7

  Revision 1.1  2004/09/13 10:54:11  yada
  initial release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CTRDG_H_
#define NITRO_CTRDG_H_


#include "nitro/ctrdg/common/ctrdg_common.h"
#include "nitro/ctrdg/ARM9/ctrdg_backup.h"
#include "nitro/ctrdg/ARM9/ctrdg_flash.h"
#include "nitro/ctrdg/ARM9/ctrdg_sram.h"
#include "nitro/ctrdg/ARM9/ctrdg_task.h"


#ifdef SDK_ARM7
#include "nitro/ctrdg/ARM7/ctrdg_sp.h"
#endif

/* NITRO_CTRDG_H_ */
#endif
