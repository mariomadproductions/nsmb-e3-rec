/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     dma.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: dma.h,v $
  Revision 1.48  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.47  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.46  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.45  2004/11/02 08:58:57  yada
  fix a little

  Revision 1.44  2004/10/21 07:40:01  yada
  just fix typo

  Revision 1.43  2004/10/12 02:04:00  yosizaki
  add MIi_DMA_TIMING_ANY.

  Revision 1.42  2004/10/08 11:59:08  yosizaki
  add MIi_CardDmaCopy.

  Revision 1.41  2004/09/28 04:32:50  yada
  fix MI_SendGXCommand(), add MI_SendGXCommandFast()

  Revision 1.40  2004/08/30 04:30:38  yada
  move some definitions from private folder

  Revision 1.39  2004/08/26 00:11:59  yada
  add MI_SendGXCommandAsyncFast

  Revision 1.38  2004/06/29 04:31:59  yada
  fix typo (if -> is)

  Revision 1.37  2004/06/22 02:05:35  yada
  only change comment

  Revision 1.36  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.35  2004/02/10 01:20:12  yada
  Moved MI_Cpu* to memory.h

  Revision 1.34  2004/02/05 11:39:03  yada
  Made the *Send*() function's transfer destination pointer volatile.

  Revision 1.33  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.32  2004/02/05 01:59:19  yada
  Changed to use UTL_* instead of SVC_*.

  Revision 1.31  2004/02/02 01:51:51  yada
  Corrected definitions of the value to write in the control register

  Revision 1.30  2004/01/30 05:00:39  yada
  Added MI_DmaSend* and MI_CpuSend*

  Revision 1.29  2004/01/26 12:45:39  yada
  Revised inline

  Revision 1.28  2004/01/19 01:26:49  yada
  Removed "_"  to change the asynchronous function names from xxx_Async to xxxAsync

  Revision 1.27  2004/01/18 04:46:53  yada
  Corrected function name mistakes

  Revision 1.26  2004/01/17 11:47:41  yada
  (none)

  Revision 1.24  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.23  2004/01/16 11:45:13  yada
  The method of referencing changed because the DMA clear buffer was moved

  Revision 1.22  2004/01/06 00:36:46  yada
  Changed the size argument of MI_SendGXCommand* from "the number of commands" to "the number of bytes."

  Revision 1.21  2003/12/25 07:30:24  yada
  Changes as per unified type rules

  Revision 1.20  2003/12/18 07:17:37  yada
  Deleted red-sdk specification

  Revision 1.19  2003/12/17 06:06:15  yasu
  prefix revision: __MI -> MIi_

  Revision 1.18  2003/12/16 05:30:17  yasu
  Changed OS_SystemWork

  Revision 1.17  2003/12/11 09:58:30  yada
  Revised 32 bit-width transfers with MI_CpuCopy16()

  Revision 1.16  2003/12/09 08:35:26  yasu
  Revamped the memory map and the related area

  Revision 1.15  2003/11/30 05:50:38  yada
  Made to return if the DMA transfer size is 0

  Revision 1.14  2003/11/28 01:54:21  yada
  Reflects REDSDK 03-11-27

  Revision 1.13  2003/11/26 09:54:41  yada
  (none)

  Revision 1.12  2003/11/26 09:51:17  yada
  Fixed bug which described reg_G3X_... in the part required by the register address.

  Revision 1.11  2003/11/21 12:35:52  yada
  Fixed bug which described reg_MI_... in the part required by the register address.

  Revision 1.10  2003/11/18 00:22:29  yada
  (none)

  Revision 1.9  2003/11/17 02:23:05  yada
  After DMA commands, created an INLINE which is the same as a non-waiting source

  Revision 1.8  2003/11/14 05:22:22  yada
  Completely separated the DMA-related definitions from the Research & Engineering Department's material
  Also, corrected register access macro REG_XXX -> reg_XXX

  Revision 1.7  2003/11/13 06:48:57  yada
  Major revision of DMA process definitions MI_DmaCopy32(...), etc.

  Revision 1.5  2003/11/12 07:50:37  yada
  Corrected GX, G3X definitions

  Revision 1.4  2003/11/12 06:37:55  yada
  For now, created a corrected DMA-related header file.

  Revision 1.3  2003/11/07 07:52:22  yada
  Corrected mistake in DMA0 register's address specification in MI_DmaSet()

  Revision 1.2  2003/11/06 10:37:04  yada
  Corrected #define

  Revision 1.1  2003/11/04 09:09:40  yada
  Initial release.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_DMA_H_
#define NITRO_MI_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/memorymap.h"

//================================================================================
//                    DMA control definition
//================================================================================
//---- maximum DMA channel No.
#define MI_DMA_MAX_NUM             3

//---- enable
#define MI_DMA_ENABLE              (1UL << REG_MI_DMA0CNT_E_SHIFT)      // DMA enable
#define MI_DMA_IF_ENABLE           (1UL << REG_MI_DMA0CNT_I_SHIFT)      // interrupt enable

//---- DMA timing
#ifdef SDK_ARM9
#  define MI_DMA_TIMING_MASK       (REG_MI_DMA0CNT_MODE_MASK)   // mask  of start field
#  define MI_DMA_TIMING_SHIFT      (REG_MI_DMA0CNT_MODE_SHIFT)  // shift of start field
#  define MI_DMA_TIMING_IMM        (0UL << REG_MI_DMA0CNT_MODE_SHIFT)   // start immediately
#  define MI_DMA_TIMING_V_BLANK    (1UL << REG_MI_DMA0CNT_MODE_SHIFT)   // start by VBlank
#  define MI_DMA_TIMING_H_BLANK    (2UL << REG_MI_DMA0CNT_MODE_SHIFT)   // start by HBlank
#  define MI_DMA_TIMING_DISP       (3UL << REG_MI_DMA0CNT_MODE_SHIFT)   // display sync
#  define MI_DMA_TIMING_DISP_MMEM  (4UL << REG_MI_DMA0CNT_MODE_SHIFT)   // main memory display sync
#  define MI_DMA_TIMING_CARD       (5UL << REG_MI_DMA0CNT_MODE_SHIFT)   // card
#  define MI_DMA_TIMING_CARTRIDGE  (6UL << REG_MI_DMA0CNT_MODE_SHIFT)   // cartridge
#  define MI_DMA_TIMING_GXFIFO     (7UL << REG_MI_DMA0CNT_MODE_SHIFT)   // geometry FIFO
#  define MIi_DMA_TIMING_ANY       (u32)(~0)    // for internal use (MIi_CardDmaCopy32)
#else  // SDK_ARM9
#  define MI_DMA_TIMING_MASK       (REG_MI_DMA0CNT_TIMING_MASK) // mask  of start field
#  define MI_DMA_TIMING_SHIFT      (REG_MI_DMA0CNT_TIMING_SHIFT)        // shift of start field
#  define MI_DMA_TIMING_IMM        (0UL << REG_MI_DMA0CNT_TIMING_SHIFT) // start immediately
#  define MI_DMA_TIMING_V_BLANK    (1UL << REG_MI_DMA0CNT_TIMING_SHIFT) // start by VBlank
#  define MI_DMA_TIMING_CARD       (2UL << REG_MI_DMA0CNT_TIMING_SHIFT) // card
#  define MI_DMA_TIMING_WIRELESS   (3UL << REG_MI_DMA0CNT_TIMING_SHIFT) // DMA0,2:wireless interrupt
#  define MI_DMA_TIMING_CARTRIDGE  MI_DMA_TIMING_WIRELESS       // DMA1,3:cartridge warning
#endif //SDK_ARM9

//---- DMA bus width
#define MI_DMA_16BIT_BUS           (0UL << REG_MI_DMA0CNT_SB_SHIFT)     // 16bit width
#define MI_DMA_32BIT_BUS           (1UL << REG_MI_DMA0CNT_SB_SHIFT)     // 32bit width

//---- continuous mode
#define MI_DMA_CONTINUOUS_OFF      (0UL << REG_MI_DMA0CNT_CM_SHIFT)     // continuous mode off
#define MI_DMA_CONTINUOUS_ON       (1UL << REG_MI_DMA0CNT_CM_SHIFT)     // continuous mode on

//---- direction of src/destination address
#define MI_DMA_SRC_INC             (0UL << REG_MI_DMA0CNT_SAR_SHIFT)    // increment source address
#define MI_DMA_SRC_DEC             (1UL << REG_MI_DMA0CNT_SAR_SHIFT)    // decrement source address
#define MI_DMA_SRC_FIX             (2UL << REG_MI_DMA0CNT_SAR_SHIFT)    // fix source address
#define MI_DMA_DEST_INC            (0UL << REG_MI_DMA0CNT_DAR_SHIFT)    // imcrement destination address
#define MI_DMA_DEST_DEC            (1UL << REG_MI_DMA0CNT_DAR_SHIFT)    // decrement destination address
#define MI_DMA_DEST_FIX            (2UL << REG_MI_DMA0CNT_DAR_SHIFT)    // fix destination address
#define MI_DMA_DEST_RELOAD         (3UL << REG_MI_DMA0CNT_DAR_SHIFT)    // increment destination address and reload

//---- forwarding size
#define MI_DMA_COUNT_MASK          (REG_MI_DMA0CNT_WORDCNT_MASK)        // mask  of forwarding size
#define MI_DMA_COUNT_SHIFT         (REG_MI_DMA0CNT_WORDCNT_SHIFT)       // shift of forwarding size

//--------------------------------------------------------------------------------
//     definitions for convenience.
//
//---- directions and width
#define MI_DMA_SINC_DINC_16        ( MI_DMA_SRC_INC | MI_DMA_DEST_INC | MI_DMA_16BIT_BUS )
#define MI_DMA_SFIX_DINC_16        ( MI_DMA_SRC_FIX | MI_DMA_DEST_INC | MI_DMA_16BIT_BUS )
#define MI_DMA_SINC_DFIX_16        ( MI_DMA_SRC_INC | MI_DMA_DEST_FIX | MI_DMA_16BIT_BUS )
#define MI_DMA_SFIX_DFIX_16        ( MI_DMA_SRC_FIX | MI_DMA_DEST_FIX | MI_DMA_16BIT_BUS )
#define MI_DMA_SINC_DINC_32        ( MI_DMA_SRC_INC | MI_DMA_DEST_INC | MI_DMA_32BIT_BUS )
#define MI_DMA_SFIX_DINC_32        ( MI_DMA_SRC_FIX | MI_DMA_DEST_INC | MI_DMA_32BIT_BUS )
#define MI_DMA_SINC_DFIX_32        ( MI_DMA_SRC_INC | MI_DMA_DEST_FIX | MI_DMA_32BIT_BUS )
#define MI_DMA_SFIX_DFIX_32        ( MI_DMA_SRC_FIX | MI_DMA_DEST_FIX | MI_DMA_32BIT_BUS )

#define MI_DMA_IMM16ENABLE         ( MI_DMA_ENABLE | MI_DMA_TIMING_IMM | MI_DMA_16BIT_BUS )
#define MI_DMA_IMM32ENABLE         ( MI_DMA_ENABLE | MI_DMA_TIMING_IMM | MI_DMA_32BIT_BUS )

//---- clear
#define MI_CNT_CLEAR16(size)       ( MI_DMA_IMM16ENABLE | MI_DMA_SRC_FIX | MI_DMA_DEST_INC | ((size)/2) )
#define MI_CNT_CLEAR32(size)       ( MI_DMA_IMM32ENABLE | MI_DMA_SRC_FIX | MI_DMA_DEST_INC | ((size)/4) )
#define MI_CNT_CLEAR16_IF(size)    ( MI_CNT_CLEAR16((size)) | MI_DMA_IF_ENABLE )
#define MI_CNT_CLEAR32_IF(size)    ( MI_CNT_CLEAR32((size)) | MI_DMA_IF_ENABLE )

//---- copy
#define MI_CNT_COPY16(size)        ( MI_DMA_IMM16ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_INC | ((size)/2) )
#define MI_CNT_COPY32(size)        ( MI_DMA_IMM32ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_INC | ((size)/4) )
#define MI_CNT_COPY16_IF(size)     ( MI_CNT_COPY16((size)) | MI_DMA_IF_ENABLE )
#define MI_CNT_COPY32_IF(size)     ( MI_CNT_COPY32((size)) | MI_DMA_IF_ENABLE )

//---- send
#define MI_CNT_SEND16(size)        ( MI_DMA_IMM16ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_FIX | ((size)/2) )
#define MI_CNT_SEND32(size)        ( MI_DMA_IMM32ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_FIX | ((size)/4) )
#define MI_CNT_SEND16_IF(size)     ( MI_CNT_SEND16((size)) | MI_DMA_IF_ENABLE )
#define MI_CNT_SEND32_IF(size)     ( MI_CNT_SEND32((size)) | MI_DMA_IF_ENABLE )

//---- HBlank copy (only for ARM9)
#ifdef SDK_ARM9
#  define MI_CNT_HBCOPY16(size)    ( MI_DMA_ENABLE | MI_DMA_TIMING_H_BLANK | MI_DMA_SRC_INC | MI_DMA_DEST_RELOAD | MI_DMA_CONTINUOUS_ON | MI_DMA_16BIT_BUS | ((size)/2) )
#  define MI_CNT_HBCOPY32(size)    ( MI_DMA_ENABLE | MI_DMA_TIMING_H_BLANK | MI_DMA_SRC_INC | MI_DMA_DEST_RELOAD | MI_DMA_CONTINUOUS_ON | MI_DMA_32BIT_BUS | ((size)/4) )
#  define MI_CNT_HBCOPY16_IF(size) ( MI_CNT_HBCOPY16((size)) | MI_DMA_IF_ENABLE )
#  define MI_CNT_HBCOPY32_IF(size) ( MI_CNT_HBCOPY32((size)) | MI_DMA_IF_ENABLE )
#endif // SDK_ARM9

//---- VBlank copy
#define MI_CNT_VBCOPY16(size)      ( MI_DMA_ENABLE | MI_DMA_TIMING_V_BLANK | MI_DMA_SRC_INC | MI_DMA_DEST_INC | MI_DMA_16BIT_BUS | ((size)/2) )
#define MI_CNT_VBCOPY32(size)      ( MI_DMA_ENABLE | MI_DMA_TIMING_V_BLANK | MI_DMA_SRC_INC | MI_DMA_DEST_INC | MI_DMA_32BIT_BUS | ((size)/4) )
#define MI_CNT_VBCOPY16_IF(size)   ( MI_CNT_VBCOPY16((size)) | MI_DMA_IF_ENABLE )
#define MI_CNT_VBCOPY32_IF(size)   ( MI_CNT_VBCOPY32((size)) | MI_DMA_IF_ENABLE )

//---- CARD read
// (other settings are not available)
#define MI_CNT_CARDRECV32(size)    ( MI_DMA_ENABLE | MI_DMA_TIMING_CARD | MI_DMA_SRC_FIX | MI_DMA_DEST_INC | MI_DMA_32BIT_BUS | ((size)/4) )


//---- memory copy (only for ARM9)
#ifdef SDK_ARM9
#  define MI_CNT_MMCOPY(size)      ( MI_DMA_ENABLE | MI_DMA_TIMING_DISP_MMEM | MI_DMA_SRC_INC | MI_DMA_DEST_FIX | MI_DMA_CONTINUOUS_ON | MI_DMA_32BIT_BUS | (4) )
#endif // SDK_ARM9

//---- geometry command copy (only for ARM9)
#ifdef SDK_ARM9
#  define MI_CNT_GXCOPY(size)      ( MI_DMA_ENABLE | MI_DMA_TIMING_GXFIFO | MI_DMA_SRC_INC | MI_DMA_DEST_FIX | MI_DMA_32BIT_BUS | ((size)/4) )
#  define MI_CNT_GXCOPY_IF(size)   ( MI_CNT_GXCOPY(size) | MI_DMA_IF_ENABLE )
#endif // SDK_ARM9


//---- DMA callback
typedef void (*MIDmaCallback) (void *);

//================================================================================
//            memory operation using DMA (sync)
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_DmaFill32

  Description:  fill memory with specified data.
                sync 32bit version

  Arguments:    dmaNo : DMA channel No.
                dest  : destination address
                data  : fill data
                size  : size (byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaCopy32

  Description:  copy memory with DMA
                sync 32bit version

  Arguments:    dmaNo : DMA channel No.
                src   : source address
                dest  : destination address
                size  : size (byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaClear32

  Description:  fill memory with 0
                sync 32bit version

  Arguments:    dmaNo : DMA channel No.
                dest  : destination address
                size  : size (byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_DmaClear32(u32 dmaNo, void *dest, u32 size)
{
    MI_DmaFill32(dmaNo, dest, 0, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_DmaSend32

  Description:  send u32 data to fixed address
                sync 32bit version

  Arguments:    dmaNo : DMA channel No.
                src   : data stream to send
                dest  : destination address. not incremented
                size  : size (byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaSend32(u32 dmaNo, const void *src, volatile void *dest, u32 size);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaFill16

  Description:  fill memory with specified data.
                sync 16bit version

  Arguments:    dmaNo : DMA channel No.
                dest  : destination address
                data  : fill data
                size  : size (byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaFill16(u32 dmaNo, void *dest, u16 data, u32 size);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaCopy16

  Description:  copy memory with DMA
                sync 16bit version

  Arguments:    dmaNo : DMA channel No.
                src   : source address
                dest  : destination address
                size  : size (byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaClear16

  Description:  fill memory with 0
                sync 16bit version

  Arguments:    dmaNo : DMA channel No.
                dest  : destination address
                size  : size (byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_DmaClear16(u32 dmaNo, void *dest, u32 size)
{
    MI_DmaFill16(dmaNo, dest, 0, size);
}

/*---------------------------------------------------------------------------*
  Name:         MI_DmaSend16

  Description:  send u16 data to fixed address
                sync 16bit version

  Arguments:    dmaNo : DMA channel No.
                src   : data stream to send
                dest  : destination address. not incremented
                size  : size (byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaSend16(u32 dmaNo, const void *src, volatile void *dest, u32 size);

//================================================================================
//            memory operation using DMA (async)
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_DmaFill32Async

  Description:  fill memory with specified data.
                async 32bit version

  Arguments:    dmaNo : DMA channel No.
                dest  : destination address
                data  : fill data
                size  : size (byte)
                callback : callback function called finish DMA
                arg      : callback argument

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaFill32Async(u32 dmaNo, void *dest, u32 data, u32 size, MIDmaCallback callback,
                          void *arg);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaCopy32Async

  Description:  copy memory with DMA
                async 32bit version

  Arguments:    dmaNo : DMA channel No.
                src   : source address
                dest  : destination address
                size  : size (byte)
                callback : callback function called finish DMA
                arg      : callback argument

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback,
                          void *arg);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaClear32Async

  Description:  fill memory with 0
                async 32bit version

  Arguments:    dmaNo : DMA channel No.
                dest  : destination address
                size  : size (byte)
                callback : callback function called finish DMA
                arg      : callback argument

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_DmaClear32Async(u32 dmaNo, void *dest, u32 size, MIDmaCallback callback,
                                      void *arg)
{
    MI_DmaFill32Async(dmaNo, dest, 0, size, callback, arg);
}

/*---------------------------------------------------------------------------*
  Name:         MI_DmaSend32Async

  Description:  send u32 data to fixed address
                async 32bit version

  Arguments:    dmaNo : DMA channel No.
                src   : data stream to send
                dest  : destination address. not incremented
                size  : size (byte)
                callback : callback function called finish DMA
                arg      : callback argument

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaSend32Async(u32 dmaNo, const void *src, volatile void *dest, u32 size,
                          MIDmaCallback callback, void *arg);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaFill16Async

  Description:  fill memory with specified data.
                async 16bit version

  Arguments:    dmaNo : DMA channel No.
                dest  : destination address
                data  : fill data
                size  : size (byte)
                callback : callback function called finish DMA
                arg      : callback argument

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaFill16Async(u32 dmaNo, void *dest, u16 data, u32 size, MIDmaCallback callback,
                          void *arg);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaCopy16Async

  Description:  copy memory with DMA
                async 16bit version

  Arguments:    dmaNo : DMA channel No.
                src   : source address
                dest  : destination address
                size  : size (byte)
                callback : callback function called finish DMA
                arg      : callback argument

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaCopy16Async(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback,
                          void *arg);

/*---------------------------------------------------------------------------*
  Name:         MI_DmaClear16Async

  Description:  fill memory with 0
                async 16bit version

  Arguments:    dmaNo : DMA channel No.
                dest  : destination address
                size  : size (byte)
                callback : callback function called finish DMA
                arg      : callback argument

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void MI_DmaClear16Async(u32 dmaNo, void *dest, u32 size, MIDmaCallback callback,
                                      void *arg)
{
    MI_DmaFill16Async(dmaNo, dest, 0, size, callback, arg);
}

/*---------------------------------------------------------------------------*
  Name:         MI_DmaSend16Async

  Description:  send u16 data to fixed address
                async 16bit version

  Arguments:    dmaNo : DMA channel No.
                src   : data stream to send
                dest  : destination address. not incremented
                size  : size (byte)
                callback : callback function called finish DMA
                arg      : callback argument

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_DmaSend16Async(u32 dmaNo, const void *src, volatile void *dest, u32 size,
                          MIDmaCallback callback, void *arg);

//================================================================================
//            HBlank DMA
//================================================================================
//  32bit
void    MI_HBlankDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
//  16 bit
void    MI_HBlankDmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);
//  32bit, with interrupt when finish DMA
void    MI_HBlankDmaCopy32If(u32 dmaNo, const void *src, void *dest, u32 size);
//  16bit, with interrupt when finish DMA
void    MI_HBlankDmaCopy16If(u32 dmaNo, const void *src, void *dest, u32 size);

//================================================================================
//        VBlank DMA
//================================================================================
//  32bit sync
void    MI_VBlankDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
//  16bit sync
void    MI_VBlankDmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);
//  32bit async
void    MI_VBlankDmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size,
                                MIDmaCallback callback, void *arg);
//  16bit async
void    MI_VBlankDmaCopy16Async(u32 dmaNo, const void *src, void *dest, u32 size,
                                MIDmaCallback callback, void *arg);

//================================================================================
//        CARD DMA
//================================================================================
//  32bit sync (CARD-DMA can not use DMA-callback because of continuous-mode)
void    MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);

//================================================================================
//        main memory display DMA
//================================================================================
//  (Sync)
void    MI_DispMemDmaCopy(u32 dmaNo, const void *src);

//================================================================================
//         geometry FIFO DMA
//================================================================================
//       32bit version only.
//       size unit is byte, equal to 'the amount of commands * 4'
//  (Sync)  
void    MI_SendGXCommand(u32 dmaNo, const void *src, u32 commandLength);
//  (Async, in fragment)
void    MI_SendGXCommandAsync(u32 dmaNo, const void *src, u32 commandLength, MIDmaCallback callback,
                              void *arg);
//  (Sync, at once)
void    MI_SendGXCommandFast(u32 dmaNo, const void *src, u32 commandLength);
//  (Async, at once)
void    MI_SendGXCommandAsyncFast(u32 dmaNo, const void *src, u32 commandLength,
                                  MIDmaCallback callback, void *arg);

//================================================================================
//       DMA WAIT
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_IsDmaBusy

  Description:  check whether DMA is busy or not

  Arguments:    dmaNo : DMA channel No.

  Returns:      TRUE if DMA is busy, FALSE if not
 *---------------------------------------------------------------------------*/
BOOL    MI_IsDmaBusy(u32 dmaNo);

/*---------------------------------------------------------------------------*
  Name:         MI_WaitDma

  Description:  wait while DMA is busy

  Arguments:    dmaNo : DMA channel No.

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_WaitDma(u32 dmaNo);

/*---------------------------------------------------------------------------*
  Name:         MI_StopDma

  Description:  stop DMA

  Arguments:    dmaNo : DMA channel No.

  Returns:      None
 *---------------------------------------------------------------------------*/
void    MI_StopDma(u32 dmaNo);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_DMA_H_ */
#endif
