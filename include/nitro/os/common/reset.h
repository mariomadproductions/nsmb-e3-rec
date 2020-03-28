/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     reset.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: reset.h,v $
  Revision 1.5  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.4  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.3  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.2  2004/09/01 08:37:32  yada
  OS_Reset -> OS_ResetSystem

  Revision 1.1  2004/09/01 04:21:08  yada
  initial release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_RESET_H_
#define NITRO_OS_RESET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"

//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_InitReset

  Description:  init reset system

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_InitReset(void);

/*---------------------------------------------------------------------------*
  Name:         OS_ResetSystem

  Description:  start reset proc

  Arguments:    parameter : parameter to be sent to next boot.

  Returns:      None.
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
void    OS_ResetSystem(u32 parameter);
#else
void    OS_ResetSystem(void);
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_IsResetOccurred

  Description:  get whethre reset event occurred

  Arguments:    None.

  Returns:      TRUE  : if reset occurred
                FALSE : if not
 *---------------------------------------------------------------------------*/
BOOL    OS_IsResetOccurred(void);

/*---------------------------------------------------------------------------*
  Name:         OS_GetResetParameter

  Description:  get parameter from previous reset

  Arguments:    None.

  Returns:      reset parameter
 *---------------------------------------------------------------------------*/
inline u32 OS_GetResetParameter(void)
{
    return (u32)*(u32 *)HW_RESET_PARAMETER_BUF;
}

//================================================================================
#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_RESET_H_ */
#endif
