/*---------------------------------------------------------------------------*
  Project:  NitroSDK - -include - PXI
  File:     init.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: init.h,v $
  Revision 1.3  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.2  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.1  2004/03/08 01:54:59  yasu
  add init.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_PXI_COMMON_INIT_H_
#define NITRO_PXI_COMMON_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
  Name:         PXI_Init

  Description:  initialize PXI system

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    PXI_Init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_PXI_COMMON_INIT_H_ */
