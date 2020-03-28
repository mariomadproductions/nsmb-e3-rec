/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     byteAccess.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: byteAccess.h,v $
  Revision 1.8  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.7  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.6  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.5  2004/05/20 07:24:52  yasu
  MI_WriteByte/ReadByte are valid only on the TEG

  Revision 1.4  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.3  2004/04/06 11:02:03  yosizaki
  change arg-type of MI_ReadByte. (void* -> const void*)

  Revision 1.2  2004/04/05 01:05:49  yada
  only added comment

  Revision 1.1  2004/03/30 11:00:48  yada
  Changed byte access functions from ARM7 only to common.

  Revision 1.1  2004/03/23 00:54:26  yada
  first release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_BYTEACCESS_H_
#define NITRO_MI_BYTEACCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/ioreg.h"

/*---------------------------------------------------------------------------*
  Name:         MI_ReadByte

  Description:  read byte data

  Arguments:    address ... address to read byte data

  Returns:      byte data
 *---------------------------------------------------------------------------*/
#ifdef	SDK_TEG
u8      MI_ReadByte(const void *address);
#else
static inline u8 MI_ReadByte(const void *address)
{
    return *(u8 *)address;
}
#endif


/*---------------------------------------------------------------------------*
  Name:         MI_WriteByte

  Description:  write byte data

  Arguments:    address ... address to write byte data

  Returns:      None.
 *---------------------------------------------------------------------------*/
#ifdef	SDK_TEG
void    MI_WriteByte(void *address, u8 value);
#else
static inline void MI_WriteByte(void *address, u8 value)
{
    *(u8 *)address = value;
}
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_BYTEACCESS_H_ */
#endif
