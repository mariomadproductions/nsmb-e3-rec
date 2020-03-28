/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     entropy.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: entropy.h,v $
  Revision 1.2  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.1  2005/07/27 07:37:41  seiki_masashi
  new additions

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_ENTROPY_H_
#define NITRO_OS_ENTROPY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/ioreg.h"

#define OS_LOW_ENTROPY_DATA_SIZE 32

/*---------------------------------------------------------------------------*
  Name:         OS_GetLowEntropyData

  Description:  Gets low entropy data that changes according to the system status.

  Arguments:    buffer - Pointer to the array that holds the data string.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_GetLowEntropyData(u32 buffer[OS_LOW_ENTROPY_DATA_SIZE / sizeof(u32)]);



#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_ENTROPY_H_ */
#endif
