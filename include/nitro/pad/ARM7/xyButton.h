/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PAD - include
  File:     xyButton.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: xyButton.h,v $
  Revision 1.5  2006/01/18 02:12:40  kitase_hirotake
  do-indent

  Revision 1.4  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.3  2005/02/28 05:26:35  yosizaki
  do-indent.

  Revision 1.2  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.1  2004/02/18 01:23:36  yada
  firstRelease


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PAD_XYBUTTON_H_
#define NITRO_PAD_XYBUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"

extern BOOL PADi_XYButtonAvailable;


/*---------------------------------------------------------------------------*
  Name:         PAD_InitXYButton

  Description :  Start to sense XY-Button.
                Need to start systemClock and Alarm before this function.

  Arguments:    None.

  Returns:      TRUE if initialize, FALSE if not initialize.
 *---------------------------------------------------------------------------*/
BOOL    PAD_InitXYButton(void);


/*---------------------------------------------------------------------------*
  Name:         PAD_IsXYButtonAvailable

  Description :  is available XY-Button sensing system

  Arguments:    None

  Returns:      TRUE if available, FALSE if no available.
 *---------------------------------------------------------------------------*/
static inline BOOL PAD_IsXYButtonAvailable(void)
{
    return PADi_XYButtonAvailable;
}


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PAD_XY_BUTTON_H_ */
#endif
