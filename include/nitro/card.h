/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CARD - include
  File:     card.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: card.h,v $
  Revision 1.7  2005/07/05 00:19:52  yosizaki
  add FRAM.

  Revision 1.6  2005/04/05 23:52:58  yosizaki
  fix copyright date.

  Revision 1.5  2004/09/27 13:41:45  yada
  consider for ARM7

  Revision 1.4  2004/09/15 05:56:48  yada
  add pullOut.h in SDK_ARM9

  Revision 1.3  2004/08/18 13:40:35  yosizaki
  add FLASH 2Mbit.

  Revision 1.2  2004/07/05 08:11:36  yosizaki
  create common.h and move some functions there.

  Revision 1.1  2004/06/28 01:55:17  yosizaki
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CARD_H_
#define NITRO_CARD_H_

#include "nitro/misc.h"
#include "nitro/types.h"


#include "nitro/card/common.h"
#include "nitro/card/eeprom.h"
#include "nitro/card/flash.h"
#include "nitro/card/fram.h"
#include "nitro/card/rom.h"
#include "nitro/card/pullOut.h"

#endif
