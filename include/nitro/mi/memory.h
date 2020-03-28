/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     memory.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: memory.h,v $
  Revision 1.16  2006/06/26 13:12:11  yosizaki
  small fix.

  Revision 1.15  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.14  2005/10/04 01:17:25  yada
  modified around fill functions

  Revision 1.13  2005/08/19 11:07:17  yada
  back to 1.11

  Revision 1.12  2005/08/19 07:48:16  yada
  add MI_StrNCpy(), MI_StrCpy()

  Revision 1.11  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.10  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.9  2004/11/02 08:59:27  yada
  fix a little

  Revision 1.8  2004/07/08 11:03:13  yada
  MI_CopyCpuFast, MI_FillCpuFast, 32byte-align -> 4byte-align

  Revision 1.7  2004/05/26 04:57:16  yada
  arrange comments

  Revision 1.6  2004/04/27 04:09:22  yosizaki
  add MI_CpuCopy8, MI_CpuFill8. MI_CpuClear8.

  Revision 1.5  2004/04/15 09:09:24  takano_makoto
  Add MI_Copy16B

  Revision 1.4  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.3  2004/03/16 11:53:06  yasu
  move HW_READ32/WRITE32 -> MI_ReadWord/WriteWord

  Revision 1.2  2004/02/10 06:01:23  nishida_kenji
  Add MI_CopyxB, MI_ZeroxB.

  Revision 1.1  2004/02/10 01:20:25  yada
  Migration from UTL_


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_MEMORY_H_
#define NITRO_MI_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"


//======================================================================
void    MIi_CpuClear16(u16 data, void *destp, u32 size);
void    MIi_CpuCopy16(const void *srcp, void *destp, u32 size);
void    MIi_CpuSend16(const void *srcp, volatile void *destp, u32 size);

void    MIi_CpuClear32(u32 data, void *destp, u32 size);
void    MIi_CpuCopy32(const void *srcp, void *destp, u32 size);
void    MIi_CpuSend32(const void *srcp, volatile void *destp, u32 size);

void    MIi_CpuClearFast(u32 data, void *destp, u32 size);
void    MIi_CpuCopyFast(const void *srcp, void *destp, u32 size);


//================================================================================
//               32 bit version
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_CpuFill32

  Description:  fill memory with specified data. (32 bit version)

  Arguments:    dest :  destination address to fill data, must be in 4 byte alignment
                data :  data to fill
                size :  size (byte), must be in 4 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuFill32(void *dest, u32 data, u32 size)
{
    SDK_ASSERTMSG((size & 3) == 0, "size & 3 must be 0");
    SDK_ASSERTMSG(((u32)dest & 3) == 0, "destination address must be in 4-byte alignment");

    MIi_CpuClear32(data, dest, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_CpuCopy32

  Description:  copy memory data (32 bit version)

  Arguments:    src  :  source address, must be in 4 byte alignment
                dest :  destination address, must be in 4 byte alignment
                size :  size (byte), must be in 4 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuCopy32(const void *src, void *dest, u32 size)
{
    SDK_ASSERTMSG((size & 3) == 0, "size & 3 must be 0");
    SDK_ASSERTMSG(((u32)src & 3) == 0, "source address must be in 4-byte alignment");
    SDK_ASSERTMSG(((u32)dest & 3) == 0, "destination address must be in 4-byte alignment");

    MIi_CpuCopy32(src, dest, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_CpuClear32

  Description:  fill memory with 0 (32 bit version)

  Arguments:    dest :  destination address, must be in 4 byte alignment
                size :  size (byte), must be in 4 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuClear32(void *dest, u32 size)
{
    MI_CpuFill32(dest, 0, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_CpuSend32

  Description:  write some data to fixed address (32 bit version)

  Arguments:    src  :  source address, must be in 4 byte alignment
                dest :  destination address, must be in 4 byte alignment
                size :  size (byte), must be in 4 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuSend32(const void *src, volatile void *dest, u32 size)
{
    SDK_ASSERTMSG((size & 3) == 0, "size & 3 must be 0");
    SDK_ASSERTMSG(((u32)src & 3) == 0, "source address must be in 4-byte alignment");
    SDK_ASSERTMSG(((u32)dest & 3) == 0, "destination address must be in 4-byte alignment");

    MIi_CpuSend32(src, dest, size);
}

//================================================================================
//               16 bit version
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_CpuFill16

  Description:  fill memory with specified data.  (16 bit version)

  Arguments:    dest :  destination address to fill data, must be in 2 byte alignment
                data :  data to fill
                size :  size (byte), must be in 2 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuFill16(void *dest, u16 data, u32 size)
{
    SDK_ASSERTMSG((size & 1) == 0, "size & 1 must be 0");
    SDK_ASSERTMSG(((u32)dest & 1) == 0, "source address must be in 2-byte alignment");

    MIi_CpuClear16(data, dest, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_CpuCopy16

  Description:  copy memory data (16 bit version)

  Arguments:    src  :  source address, must be in 2 byte alignment
                dest :  destination address, must be in 2 byte alignment
                size :  size (byte), must be in 2 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuCopy16(const void *src, void *dest, u32 size)
{
    SDK_ASSERTMSG((size & 1) == 0, "size & 1 must be 0");
    SDK_ASSERTMSG(((u32)src & 1) == 0, "source address must be in 2-byte alignment");
    SDK_ASSERTMSG(((u32)dest & 1) == 0, "destination address must be in 2-byte alignment");

    MIi_CpuCopy16(src, dest, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_CpuClear16

  Description:  fill memory with 0 (16 bit version)

  Arguments:    dest :  destination address, must be in 2 byte alignment
                size :  size (byte), must be in 2 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuClear16(void *dest, u32 size)
{
    MI_CpuFill16(dest, 0, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_CpuSend16

  Description:  write some data to fixed address (16 bit version)

  Arguments:    src  :  source address, must be in 2 byte alignment
                dest :  destination address, must be in 4 byte alignment
                size :  size (byte), must be in 2 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuSend16(const void *src, volatile void *dest, u32 size)
{
    SDK_ASSERTMSG((size & 1) == 0, "size & 1 must be 0");
    SDK_ASSERTMSG(((u32)src & 1) == 0, "source address must be in 2-byte alignment");
    SDK_ASSERTMSG(((u32)dest & 1) == 0, "destination address must be in 2-byte alignment");

    MIi_CpuSend16(src, dest, size);
}

//================================================================================
//               32 byte unit version
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_CpuFillFast

  Description:  fill memory with specified data quickly.  (32 byte unit version)

  Arguments:    dest :  destination address to fill data
                data :  data to fill
                size :  size (byte), must be in 4 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuFillFast(void *dest, u32 data, u32 size)
{
    SDK_ASSERTMSG((size & 3) == 0, "size & 3 must be 0");
    SDK_ASSERTMSG(((u32)dest & 3) == 0, "source address must be in 4-byte alignment");

    MIi_CpuClearFast(data, dest, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_CpuCopyFast

  Description:  copy memory data quickly (32 byte unit version)

  Arguments:    src  :  source address, must be in 4 byte alignment
                dest :  destination address, must be in 4 byte alignment
                size :  size (byte), must be in 4 byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuCopyFast(const void *src, void *dest, u32 size)
{
    SDK_ASSERTMSG((size & 3) == 0, "size & 3 must be 0");
    SDK_ASSERTMSG(((u32)src & 3) == 0, "source address must be in 4-byte alignment");
    SDK_ASSERTMSG(((u32)dest & 3) == 0, "destination address must be in 4-byte alignment");

    MIi_CpuCopyFast(src, dest, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_CpuClearFast

  Description:  fill memory with 0 quickly (32 byte unit version)

  Arguments:    dest :  destination address, must be in 4 byte alignment
                size :  size (byte), must be in 4-byte alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuClearFast(void *dest, u32 size)
{
    MI_CpuFillFast(dest, 0, size);
}


//================================================================================
//               8 bit version
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_CpuFill8

  Description:  fill memory with specified data.  (8 bit version)

  Arguments:    dest :  destination address to fill data, no limitation for alignment
                data :  data to fill
                size :  size (byte), no limitation for alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_CpuFill8(void *dest, u8 data, u32 size);

/*---------------------------------------------------------------------------*
  Name:         MI_CpuCopy8

  Description:  copy memory data (8 bit version)

  Arguments:    src  :  source address, no limitation for alignment
                dest :  destination address, no limitation for alignment
                size :  size (byte), no limitation for alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_CpuCopy8(const void *src, void *dest, u32 size);

/*---------------------------------------------------------------------------*
  Name:         MI_CpuClear8

  Description:  fill memory with 0 (8 bit version)

  Arguments:    dest :  destination address, no limitation for alignment
                size :  size (byte), no limitation for alignment

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_CpuClear8(void *dest, u32 size)
{
    MI_CpuFill8(dest, 0, size);
}

//================================================================================
//               32 bit version
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_ReadWord

  Description:  read 32 bit data from specified address

  Arguments:    adrs :  address to read

  Returns:      data which is read
 *---------------------------------------------------------------------------*/
#ifndef SDK_ASM
#define MI_ReadWord( adrs )   (*(vu32 *)(adrs))
#endif

/*---------------------------------------------------------------------------*
  Name:         MI_WriteWord

  Description:  write 32 bit data to specified adress

  Arguments:    adrs :  address to write
                val  :  data to write

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef SDK_ASM
#define MI_WriteWord( adrs, val )  do { (*(vu32 *)(adrs)) = (u32)(val); } while(0)
#endif



//================================================================================
//      the following functions are prepared for SDK private use.
//      don't use in application thoughtlessly
//================================================================================
void    MI_Copy16B(register const void *pSrc, register void *pDest);
void    MI_Copy32B(register const void *pSrc, register void *pDest);
void    MI_Copy36B(register const void *pSrc, register void *pDest);
void    MI_Copy48B(register const void *pSrc, register void *pDest);
void    MI_Copy64B(register const void *pSrc, register void *pDest);
void    MI_Copy128B(register const void *pSrc, register void *pDest);

void    MI_Zero32B(register void *pDest);
void    MI_Zero36B(register void *pDest);
void    MI_Zero48B(register void *pDest);
void    MI_Zero64B(register void *pDest);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_MEMORY_H_ */
#endif
