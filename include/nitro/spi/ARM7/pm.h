/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PM - include
  File:     pm.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: pm.h,v $
  Revision 1.3  2006/01/18 02:12:27  kitase_hirotake
  do-indent

  Revision 1.2  2005/02/28 05:26:29  yosizaki
  do-indent.

  Revision 1.1  2004/08/24 05:19:18  yada
  initial release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PM_ARM7_H_
#define NITRO_PM_ARM7_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/spi/common/pm_common.h"
#include "nitro/spi/common/type.h"
#include "nitro/pxi/common/fifo.h"

//================================================================================
//             LED
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         PM_SetLEDPattern

  Description:  set self blink pattern

  Arguments:    pattern: self blink pattern

  Returns:      None
 *---------------------------------------------------------------------------*/
void    PM_SetLEDPattern(PMLEDPattern pattern);


/*---------------------------------------------------------------------------*
  Name:         PM_GetLEDPattern

  Description:  get current self blink pattern

  Arguments:    None

  Returns:      current self blink pattern
 *---------------------------------------------------------------------------*/
PMLEDPattern PM_GetLEDPattern(void);



#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PM_ARM7_H_ */
#endif
