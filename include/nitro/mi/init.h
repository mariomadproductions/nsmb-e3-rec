/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     init.h

  Copyright 2005-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: init.h,v $
  Revision 1.3  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.2  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.1  2005/02/10 04:07:40  yada
  initial release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_INIT_H_
#define NITRO_MI_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"


/*---------------------------------------------------------------------------*
  Name:         MI_Init

  Description:  initialize MI functions

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_Init(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_INIT_H_ */
#endif
