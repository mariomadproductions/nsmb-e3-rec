/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     swap.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: swap.h,v $
  Revision 1.7  2006/01/18 02:12:29  kitase_hirotake
  do-indent

  Revision 1.6  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.5  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.4  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.3  2004/03/30 04:51:44  yada
  only fix comment

  Revision 1.2  2004/02/10 06:04:31  yada
  changed return value type to u32

  Revision 1.1  2004/02/10 01:20:25  yada
  Migration from UTL_


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_SWAP_H_
#define NITRO_MI_SWAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"

/*---------------------------------------------------------------------------*
  Name:         MI_SwapWord / MI_SwapByte

  Description:  swap data and memory

  Arguments:    setData      data to swap
                destp        memory address to swap

  Returns:      swapped memory data

  *Notice: Cannot access main memory by byte unless cache.
           Use MI_SwapWord() not MI_SwapByte basically.
 *---------------------------------------------------------------------------*/
//---- by word
u32     MI_SwapWord(u32 setData, volatile u32 *destp);

//---- by byte
u8      MI_SwapByte(u32 setData, volatile u8 *destp);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_SWAP_H_ */
#endif
