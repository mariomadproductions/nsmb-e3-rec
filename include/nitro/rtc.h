/*---------------------------------------------------------------------------*
  Project:  NitroSDK - RTC - include
  File:     rtc.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: rtc.h,v $
  Revision 1.3  2005/05/17 13:01:56  seiki_masashi
  Added conversion function

  Revision 1.2  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.1  2004/05/12 02:27:09  terui
  initial upload

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef	NITRO_RTC_H_
#define	NITRO_RTC_H_

#ifdef	__cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include "nitro/rtc/common/type.h"
#include "nitro/rtc/common/fifo.h"

#ifdef	SDK_ARM7

#include "nitro/rtc/ARM7/control.h"
#include "nitro/rtc/ARM7/instruction.h"
#include "nitro/rtc/ARM7/gpio.h"

#else  // SDK_ARM9

#include "nitro/rtc/ARM9/api.h"
#include "nitro/rtc/ARM9/convert.h"

#endif

/*===========================================================================*/

#ifdef	__cplusplus
}          /* extern "C" */
#endif

#endif /* NITRO_RTC_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
