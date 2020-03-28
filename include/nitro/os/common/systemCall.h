/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     systemCall.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: systemCall.h,v $
  Revision 1.24  2006/03/13 05:59:37  okubata_ryoma
  Minor revisions to macro

  Revision 1.23  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.22  2005/11/21 02:25:10  terui
  Reconstruct SVC_WaitVBlankIntr definition.

  Revision 1.21  2005/10/24 00:49:42  adachi_hiroaki
  Removed SDK_WEAK_SYMBOL specification from SVC_WaitVBlankIntr()

  Revision 1.20  2005/10/21 09:00:02  yada
  let SVC_WaitVBlankIntr be weak symbol.

  Revision 1.19  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.18  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.17  2004/11/02 09:48:48  yada
  just fix comment

  Revision 1.16  2004/07/20 07:27:11  yada
  system call functions were renewed

  Revision 1.15  2004/05/26 11:10:02  terui
  change comment of SVC_WaitByLoop

  Revision 1.14  2004/04/15 11:52:27  yada
  delete SVC_ReadCard

  Revision 1.13  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.12  2004/03/26 13:11:31  yasu
  #if SDK_ARM7 -> #ifdef SDK_ARM7

  Revision 1.11  2004/03/25 09:43:20  yada
  Added SVC_Halt(), SVC_WaitByLoop() for ARM7

  Revision 1.10  2004/03/17 10:36:50  yasu
  fix SVC_CpuCopyFast

  Revision 1.9  2004/02/10 11:34:05  yada
  Delete SystemCall().

  Revision 1.8  2004/02/05 07:27:19  yada
  Returned the parts that were IRIS in the history string from NITRO to IRIS.

  Revision 1.7  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.6  2004/02/05 00:19:53  yada
  With #define made so that anything enclosed by only { } will become do{ }while(0).

  Revision 1.5  2004/01/19 06:14:09  yada
  Corrected places inside SVC_CpuSet() where MI_ was not affixed to constants

  Revision 1.4  2003/12/11 00:35:20  yasu
  Revised IRIS_TS -> SDK_TS, etc

  Revision 1.3  2003/11/28 01:54:54  yada
  Reflects REDSDK 03-11-27

  Revision 1.2  2003/11/11 12:27:28  yada
  Moved some system call portions from interrupt.h to systemCall.h

  Revision 1.1  2003/11/07 07:55:16  yada
  Provisional version. Will surely be changed considerably.


  $NoKeywords: $

 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_SYSTEMCALL_H_
#define NITRO_OS_SYSTEMCALL_H_

#include "nitro/mi/stream.h"
#include "nitro/mi/uncompress.h"
#include "nitro/os/common/system.h"

#ifdef __cplusplus
extern "C" {
#endif


//================================================================================
/*---------------------------------------------------------------------------*
  Name:         SVC_WaitVBlankIntr

  Description:  wait for VBlank

              - Waits in hold state until V-blank interrupt is generated.
              - Set by the interrupt process the flag corresponding to
                INTR_CHECK_BUF (DTCM_END - 0x8).
              - If multiple interrupts are combined, SVC_Halt() will be repeatedly called
                call overhead compared to when SVC_Halt() is called
                repeatedly.
              - If the system enters Halt when using threads, until an interrupt occurs,
                until an interrupt is generated. So we recommend using
                OS_WaitIrq(1, OS_IE_V_BLANK) for threads other than idle thread.

  Arguments:    None

  Returns:      None

 *---------------------------------------------------------------------------*/
#ifdef  SDK_SVC_WAITVBLANK_COMPATIBLE
void    SVC_WaitVBlankIntr(void);
#else
#define SVC_WaitVBlankIntr  OS_WaitVBlankIntr
#endif

/*---------------------------------------------------------------------------*
  Name:         SVC_WaitByLoop

  Description:  loop specified times

              - Performs loop processing in system ROM specified number of times.
              - It takes four cycles for one loop.
              - In states during normal operation where the sub-processor has priority to access main memory, it is possible to reduce stalling of the main processor by having the sub-processor run programs in system ROM.
                
                
              - When it is necessary to give priority to main processor in main memory display mode,
                Although there may be situations in which calling by the main processor may be enabled if necessary, there is no need to call this function from the main processor as long as most of the period is running in the cache or on the TCM.
                
                

              - Arguments:
                  count :     loop count

  Arguments:    count : times to loop

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_WaitByLoop(s32 count);

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuSet

  Description:  clear or copy memory by cpu

               - Clears or copies RAM using DmaSet macro compatible parameters.
               - Accessed forcibly with 4-byte boundary with 32-bit transfer, but
                 with 16-bit transfer the arguments need to be matched up with the 2-byte boundary and passed.

               - Arguments:
                   srcp          source address
                   destp         destination address
                   dmaCntData    MI_DMA_SRC_FIX/MI_DMA_32BIT_BUS/MI_DMA_COUNT_MASK  only enabled

                         MI_DMA_SRC_FIX(0, 1) = (source address/index, source address fixation)
                         MI_DMA_32BIT_BUS(0, 1) = (16-bit transfer, 32-bit transfer)
                         MI_DMA_COUNT_MASK & dmaCntData = number of transfers

               - upper macro:
                   SVC_CpuClear, SVC_CpuClearArray, SVC_CpuCopy, SVC_CpuCopyArray

  Arguments:    srcp :       source address
                destp :      destination address
                dmaCntData : dma control data
                            (only MI_DMA_SRC_FIX/MI_DMA_32BIT_BUS/MI_DMA_COUNT_MASK
                             is available)

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_CpuSet(const void *srcp, void *destp, u32 dmaCntData);

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuSetFast

  Description:  clear or copy memory by cpu quickly

              - Clears and copies RAM at high speed with DmaSet macro compatible parameters.
              - When access in 32-Byte units is possible, multiple load/store instructions are used,
                and the fraction is accessed in 4-Byte units.
              - Even if you provide an argument outside the 4-Byte limit, access is forcibly within the 4-Byte limit.

              - Arguments:
                  srcp          source address
                  destp         destination address
                  dmaCntData    only MI_DMA_SRC_FIX and MI_DMA_COUNT_MASK valid

                        MI_DMA_SRC_FIX(0, 1) = (source address/index, source address fixation)
                        MI_DMA_COUNT_MASK & dmaCntData = number of transfers

              - upper macro:
                  SVC_CpuClearFast, SVC_CpuClearArrayFast, SVC_CpuCopyFast, SVC_CpuCopyArrayFast

  Arguments:    srcp :       source address
                destp :      destination address
                dmaCntData : dma control data
                            (only MI_DMA_SRC_FIX/MI_DMA_COUNT_MASK
                             is available)

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_CpuSetFast(const void *srcp, void *destp, u32 dmaCntData);

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuClear

  Description:  clear memory by SVC_CpuSet

              - Calls system call that does RAM clear on CPU.
              - Clear data is put in stack, and that is copied to the destination.

              - Arguments:
                  data        clear data
                  destp       destination address
                  size        number of cleared bytes
                  bit         transfer bit width (16|32)

  Arguments:    data   : clear data
                destp  : destination address
                size   : clear size ( by byte )
                bit    : bit width ( 16 or 32 )

  Returns:      None

 *---------------------------------------------------------------------------*/
#define SVC_CpuClear( data, destp, size, bit )                  \
do{                                                             \
    vu##bit tmp = (vu##bit )(data);                             \
    SVC_CpuSet((u8 *)&(tmp), (u8 *)(destp), (                   \
        MI_DMA_SRC_FIX        |                                 \
        MI_DMA_##bit##BIT_BUS | ((size)/((bit)/8) & 0x1fffff)));  \
} while(0)

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuClearArray

  Description:  clear memory by SVC_CpuSet

              - Calls system call that does RAM clear on CPU.
              - Clear data is put in stack, and that is copied to the destination.
              - SVC_CpuClearArray clears the entire destination array.

              - Arguments:
                  data        clear data
                  destp       destination address
                  bit         transfer bit width (16|32)

  Arguments:    data  : clear data
                destp : destination address
                bit   : bit width ( 16 or 32 )

  Returns:      None

 *---------------------------------------------------------------------------*/
#define SVC_CpuClearArray( data, destp, bit )                   \
        SVC_CpuClear( data, destp, sizeof(destp), bit )

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuCopy

  Description:  copy memory by SVC_CpuSet

              - Calls system call that does copy on CPU.
              - SVC_CpuCopyArray copies the entire source array.

              - Arguments:
                  srcp   :  source address
                  destp  :  destination address
                  size   :  number of bytes transferred
                  bit    :  transfer bit width (16|32)

  Arguments:    srcp  : source address
                destp : destination address
                size  : size to copy ( by byte )
                bit   : bit width ( 16 or 32 )

  Returns:      None

 *---------------------------------------------------------------------------*/
#define SVC_CpuCopy( srcp, destp, size, bit )                   \
                                                                \
    SVC_CpuSet((u8 *)(srcp), (u8 *)(destp),  (                  \
        MI_DMA_SRC_INC        |                                 \
        MI_DMA_##bit##BIT_BUS | ((size)/((bit)/8) & 0x1fffff)))

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuCopyArray

  Description:  copy memory by SVC_CpuSet

              - Calls system call that does copy on CPU.
              - SVC_CpuCopyArray copies the entire source array.

              - Arguments:
                  srcp  :  source address
                  destp :  destination address
                  bit   :  transfer bit width (16|32)

  Arguments:    srcp  : source address
                destp : destination address
                bit   : bit width ( 16 or 32 )

  Returns:      None

 *---------------------------------------------------------------------------*/
#define SVC_CpuCopyArray( srcp, destp, bit  )                  \
        SVC_CpuCopy( srcp, destp, sizeof(srcp), bit )

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuClearFast

  Description:  clear memory by SVC_CpuSetFast quickly

              - Calls the system call that clears rapidly clears RAM in the CPU.
              - Clear data is put in stack, and that is copied to the destination.
              - When access is possible in 32-Byte units, multiple 32-Byte unit store instructions are used,
                and the fraction is accessed in 4-Byte units.

              Arguments:
                  data        clear data
                  destp       destination address
                  size        number of cleared bytes

  Arguments:    data   : clear data
                destp  : destination address
                size   : clear size ( by byte )

  Returns:      None

 *---------------------------------------------------------------------------*/
#define SVC_CpuClearFast( data, destp, size )                   \
do{                                                             \
    vu32 tmp = (vu32 )(data);                                   \
    SVC_CpuSetFast((u8 *)&(tmp), (u8 *)(destp), (               \
        MI_DMA_SRC_FIX | ((size)/(32/8) & 0x1fffff)));   \
} while(0)

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuClearArrayFast

  Description:  clear memory by SVC_CpuSetFast quickly

              - Calls the system call that clears rapidly clears RAM in the CPU.
              - Clear data is put in stack, and that is copied to the destination.
              - When access is possible in 32-Byte units, multiple 32-Byte unit store instructions are used,
                and the fraction is accessed in 4-Byte units.
              - SVC_CpuClearArrayFast clears the entire destination array.

              - Arguments:
                  data        clear data
                  destp       destination address

  Arguments:    data   : clear data
                size   : size to clear ( by byte )

  Returns:      None
 *---------------------------------------------------------------------------*/
#define SVC_CpuClearArrayFast( data, destp )                    \
        SVC_CpuClearFast( data, destp, sizeof(destp) )

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuCopyFast

  Description:  clear memory by SVC_CpuSetFast quickly

              - Calls the system call that rapidly copies in the CPU.
              - When access in 32-Byte units is possible, multiple load/store instructions are used,
                and the fraction is accessed in 4-Byte units.

              - Arguments:
                  srcp          source address
                  destp         destination address
                  size          number of transfer bytes

  Arguments:    srcp   : source address
                destp  : destination address
                size   : size to copy ( by byte )

  Returns:      None

 *---------------------------------------------------------------------------*/
#define SVC_CpuCopyFast( srcp, destp, size )                    \
                                                                \
    SVC_CpuSetFast((u8 *)(srcp), (u8 *)(destp),  (              \
        MI_DMA_SRC_INC | ((size)/(32/8) & 0x1fffff)))

/*---------------------------------------------------------------------------*
  Name:         SVC_CpuCopyArrayFast

  Description:  clear memory by SVC_CpuSetFast quickly

              - Calls the system call that rapidly copies in the CPU.
              - When access in 32-Byte units is possible, multiple load/store instructions are used,
                and the fraction is accessed in 4-Byte units.
              - SVC_CpuCopyArrayFast copies the entire source array.

              - Arguments:
                  srcp          source address
                  destp         destination address

  Arguments:    srcp  : source address
                destp : destination address

  Returns:      None

 *---------------------------------------------------------------------------*/
#define SVC_CpuCopyArrayFast( srcp, destp )                     \
        SVC_CpuCopyFast( srcp, destp, sizeof(srcp) )

/*---------------------------------------------------------------------------*
  Name:         SVC_UnpackBits

  Description:  unpack bits

              - Unpacks data that packs 0 fixed bit.
              - Align the destination address to a 4-byte boundary.

              - Arguments:
                   srcp          source address
                   destp         destination address
                   paramp        address of MIUnpackBitsParam structure

              - MIUnpackBitsParam Structure
                    u16 srcNum              Number of bytes of source data
                    u8  srcBitNum           Number of bits per source data
                    u8  destBitNum          Number of bits per destination data
                    u32 destOffset:31       Offset number to add to source data.
                        destOffset0_On:1    Flag for whether to add an offset to 0 data.

  Arguments:    srcp   : source address
                destp  : destination address
                paramp : parameter structure address

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_UnpackBits(const void *srcp, void *destp, const MIUnpackBitsParam *paramp);

/*---------------------------------------------------------------------------*
  Name:         SVC_UncompressLZ8

  Description:  uncompress LZ77

              - Expands LZ77 compressed data, and writes in 8-bit units.
              - You cannot directly uncompress VRAM that cannot be byte accessed.
              - If the size of compressed data is not a multiple of four,
                adjust as necessary by padding with 0s.
              - Align source address to a 4-byte boundary.

              - Arguments:
                   srcp          source address
                   destp         destination address

               -  Data header
                   u32 :4                  reserved
                        compType:4          compression type  ( = 1)
                        destSize:24         Data size after decoding

               - Flag data format
                    u8  flags               compression/no compression flag
                                            (0, 1) = (not compressed, compressed)
               - Code data format (Big Endian)
                    u16 length:4            Expansion data length - 3(Only compress when the match length is 3-bytes or greater)
                        offset:12           match data offset - 1

  Arguments:    srcp  : source address
                destp : destination address

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_UncompressLZ8(const void *srcp, void *destp);

/*---------------------------------------------------------------------------*
  Name:         SVC_UncompressRL8

  Description:  uncompress run length

              - Expands runlength compressed data, and writes in 8-bit units.
              - You cannot directly uncompress VRAM that cannot be byte accessed.
              - If the size of compressed data is not a multiple of four,
                adjust as necessary by padding with 0s.
              - Align source address to a 4-byte boundary.

              - Arguments:
                   srcp          source address
                   destp         destination address

              - Data header
                   u32 :4                  reserved
                       compType:4          compression type  ( = 3)
                       destSize:24         Data size after decoding

              - Flag data format
                   u8  length:7            Expansion data length - 1 (When not compressed)
                                           Expansion data length - 3 (Only compress when the contiguous length is 3-bytes or greater)
                       flag:1              (0, 1) = (not compressed, compressed)

  Arguments:    srcp  : source address
                destp : destination address

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_UncompressRL8(const void *srcp, void *destp);

#ifdef SDK_TS
/*---------------------------------------------------------------------------*
  Name:         SVC_UncompressLZ16FromDevice

  Description:  uncompress LZ77 from device

              - Expands LZ77 compressed data, and writes in 16-bit units.
              - You can directly uncompress compressed data on a non-memory
                mapped device without using temporary buffer.
              - You can also uncompress in RAM that cannot byte-access,
                but it is slower than SVC_UncompressLZ8().
              - For compress data, search for a matching character string from a minimum of 2 bytes before.
              - If the size of compressed data is not a multiple of four,
                adjust as necessary by padding with 0s.
              - Align source address to a 4-byte boundary.
              - When successful, returns the size after uncompression.
                Returns a negative value when it fails.
                Return a negative value when an error is detected in the initStream/terminateStream callback function.

              - Arguments:
                   srcp          source address
                   destp         destination address
                   paramp        address of parameter passed to the initStream function of the MIReadStreamCallbacks structure
                   callbacks     address of the MIReadStreamCallbacks structure

               - Data header
                   u32 :4                  reserved
                       compType:4          compression type  ( = 1)
                       destSize:23         Data size after decoding
                       :1                  unusable

               - Flag data format
                    u8  flags               compression/no compression flag
                                            (0, 1) = (not compressed, compressed)
               - Code data format (Big Endian)
                    u16 length:4            Expansion data length - 3(Only compress when the match length is 3-bytes or greater)
                        offset:12           match data offset - 1

  Arguments:    srcp      : source address
                destp     : destination address
                callbacks : address of stream callbacks structure

  Returns:      uncompressed size >= 0
                error < 0

 *---------------------------------------------------------------------------*/
s32     SVC_UncompressLZ16FromDevice(const void *srcp, void *destp, const void *paramp,
                                     const MIReadStreamCallbacks *callbacks);

/*---------------------------------------------------------------------------*
  Name:         SVC_UncompressRL16FromDevice

  Description:  uncompress run length from device

              - Expands runlength compressed data, and writes in 16-bit units.
              - You can directly uncompress compressed data on a non-memory
                mapped device without using temporary buffer.
              - You can also uncompress in RAM that cannot byte-access,
                but it is slower than SVC_UncompressRL8().
              - If the size of compressed data is not a multiple of four,
                adjust as necessary by padding with 0s.
              - Align source address to a 4-byte boundary.
              - When successful, returns the size after uncompression.
                Returns a negative value when it fails.
                Return a negative value when an error is detected in the initStream/terminateStream callback function.

              - Arguments:
                   srcp          source address
                   destp         destination address
                   paramp        address of parameter passed to the initStream function of the MIReadStreamCallbacks structure
                   callbacks     address of the MIReadStreamCallbacks structure

              - Data header
                   u32 :4                  reserved
                       compType:4          compression type  ( = 3)
                       destSize:23         Data size after decoding
                       :1                  unusable

              - Flag data format
                   u8  length:7            Expansion data length - 1 (When not compressed)
                                           Expansion data length - 3 (Only compress when the contiguous length is 3-bytes or greater)
                       flag:1              (0, 1) = (not compressed, compressed)

  Arguments:    srcp      : source address
                destp     : destination address
                callbacks : address of stream callbacks structure

  Returns:      uncompressed size >= 0
                error < 0

 *---------------------------------------------------------------------------*/
s32     SVC_UncompressRL16FromDevice(const void *srcp, void *destp, const void *paramp,
                                     const MIReadStreamCallbacks *callbacks);

/*---------------------------------------------------------------------------*
  Name:         SVC_UncompressHuffmanFromDevice

  Description:  uncompress huffman from device

              - Expands Huffman compressed data, and writes in 32-bit units.
              - You can directly uncompress compressed data on a non-memory
                mapped device without using temporary buffer.
              - If the size of compressed data is not a multiple of four,
                adjust as necessary by padding with 0s.
              - Align source address to a 4-byte boundary.
              - When successful, returns the size after uncompression.
                Returns a negative value when it fails.
                Return a negative value when an error is detected in the initStream/terminateStream callback function.

              - Arguments:
                   srcp          source address
                   destp         destination address
                   tableBufp     tree table storage buffer  (maximum 512 Bytes)
                                 When you wish to pass parameters to the initStream function of the MIReadStreamCallbacks structure,
                                 you can pass them with this buffer.
                                 However, after calling the initStream function, the tree table is overwritten.
                   callbacks     address of the MIReadStreamCallbacks structure

              - Data header
                   u32 bitSize:4           1 data bit size (Normally 4|8)
                       compType:4          compression type  ( = 2)
                       destSize:23         Data size after decoding
                       :1                  unusable

              - Tree table
                   u8           treeSize        tree table size/2 - 1
                   TreeNodeData nodeRoot        root node

                   TreeNodeData nodeLeft        root left node
                   TreeNodeData nodeRight       root right node

                   TreeNodeData nodeLeftLeft    left left node
                   TreeNodeData nodeLeftRight   left ride node

                   TreeNodeData nodeRightLeft   right left node
                   TreeNodeData nodeRightRight  right right node

                           .
                           .

                The compress data structure follows

              - TreeNodeData structure
                  u8  nodeNextOffset:6    Offset to the next node data - 1 (2-byte units)
                      rightEndFlag:1      right node end flag
                      leftEndflag:1       left node end flag
                                          when end flag is set
                                          there is data in next node

  Arguments:    srcp      : source address
                destp     : destination address
                callbacks : address of stream callbacks structure

  Returns:      uncompressed size >= 0
                error < 0

 *---------------------------------------------------------------------------*/
s32     SVC_UncompressHuffmanFromDevice(const void *srcp, void *destp, u8 *tableBufp,
                                        const MIReadStreamCallbacks *callbacks);

/*---------------------------------------------------------------------------*
  Name:         SVC_GetCRC16

  Description:  calculate CRC-16

              - Calculates CRC-16.
              - Keep the data address and size within the 2 Byte limit.

              - Arguments:
                   start         initial value
                   datap         data address
                   size          size (number of bytes)

  Arguments:    start  : start value
                datap  : data address
                size   : data size (by byte)

  Returns:      CRC-16

 *---------------------------------------------------------------------------*/
u16     SVC_GetCRC16(u32 start, const void *datap, u32 size);

/*---------------------------------------------------------------------------*
  Name:         SVC_IsMmemExpanded

  Description:  check if main memory is expanded

              - Checks whether main memory is expanded to 8MB.
              - In the ARM9, you must set 0x023FFFF8 and 0x027FFFF8 addresses
                to a cache-unavailable setting.

  Arguments:    None

  Returns:      TRUE if main memory is expanded

 *---------------------------------------------------------------------------*/
BOOL    SVC_IsMmemExpanded(void);

#endif // SDK_TS

#if defined(SDK_ARM7) || (defined(SDK_ARM9) && defined(SDK_TS))
/*---------------------------------------------------------------------------*
  Name:         SVC_Div

  Description:  quotient of division

              - Calculates the numerator and denominator.
              - The register value is restored with r0=numer/denom, r1=numer%denom,
                r3=Restored with |numer/denom.
              - In order to reduce code size, this is not very fast.

              Arguments:
                   numer        numerator
                   denom        denominator

  Arguments:    numer  : 
                denom  : 

  Returns:      quotient

 *---------------------------------------------------------------------------*/
s32     SVC_Div(s32 number, s32 denom);

/*---------------------------------------------------------------------------*
  Name:         SVC_DivRem

  Description:  remainder of division

              - Calculates numer%denom.
              - Returns register value as r0=number%denom, r1=number%denom,
                r3=Restored with |numer/denom.
              - In order to reduce code size, this is not very fast.

              Arguments:
                   number        numerator
                   denom         denominator

  Arguments:    numer  : 
                denom  : 

  Returns:      remainder

 *---------------------------------------------------------------------------*/
s32     SVC_DivRem(s32 number, s32 denom);

/*---------------------------------------------------------------------------*
  Name:         SVC_Sqrt

  Description:  square root

              - Calculates square root.
              - To improve accuracy, make the argument a multiple of 2 only, left shift, and pass.
                Shift the return value as well to align the digits.
              - In order to reduce code size, this is not very fast.

  Arguments:    src: 

  Returns:      square root

 *---------------------------------------------------------------------------*/
u16     SVC_Sqrt(u32 src);

/*---------------------------------------------------------------------------*
  Name:         SVC_Halt

  Description:  halt

                - Only stops CPU core
                - The relevant interrupt will return by means
                  of an allowed (IE set) interrupt request (IF set)
                - If the CPSR's IRQ disable flag is set,
                  Control will return to (OS_DisableInterrupts) from halts, but interrupts will not occur.
                 
                - If a halt is entered during a state with IME cleared, (OS_DisableIrq) retun will become impossible.
                  

  Arguments:    None

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_Halt(void);

#endif // SDK_ARM7 || (SDK_ARM9 && SDK_TS)

#ifdef SDK_ARM7
/*---------------------------------------------------------------------------*
  Name:         SVC_Sleep

  Description:  sleep

              - Stops source oscillation.
              - The return is made generating the corresponding interrupt requestion condition when RTC, key, card, cartridge, or console open interrupt is permitted (set in IE).
              - Because source oscillation is stopped, the IF flag will not be set directly after returning, but when the  interrupt request signal to the terminal to the terminal is in there until the CPU restarts, the IF flag is set at that time.
              - First, 0 clear POWCNT register for both processors
                stop all blocks, stop sound amp and wireless module,
                set ARM9 to halt status, and then call this function.
              - Set the POWCNT register's LCD enable flag to 0
                at least 100ms before calling this function. If you do not,
                it is possible that the DS will shut down.

  Arguments:    None

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_Sleep(void);

/*---------------------------------------------------------------------------*
  Name:         SVC_SetSoundBias

  Description:  set sound bias

              - Changes sound BIAS from 0 to intermediate value  (0x200).

              - Arguments:
                   stepLoops     number of loops between each sound bias change steps (4 cycles/loop).
                                 The higher the value, more gradually sound bias is changed.

  Arguments:    stepLoops : 

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_SetSoundBias(s32 stepLoops);

/*---------------------------------------------------------------------------*
  Name:         SVC_ResetSoundBias

  Description:  set sound bias

              - Changes sound BIAS from the intermediate value (0x200)  to 0.

              - Arguments:
                   stepLoops     number of loops between each sound bias change steps (4 cycles/loop).
                                 The higher the value, more gradually sound bias is changed.

  Arguments:    stepLoops : 

  Returns:      None

 *---------------------------------------------------------------------------*/
void    SVC_ResetSoundBias(s32 stepLoops);

#ifdef SDK_TS
/*---------------------------------------------------------------------------*
  Name:         SVC_GetSinTable
                SVC_GetPitchTable
                SVC_GetVolumeTable

  Description:  get sound table data

              - References the sound table and returns value.

              - Arguments:
                   index         index

  Arguments:    index  : 

  Returns:      sound table data

 *---------------------------------------------------------------------------*/
s16     SVC_GetSinTable(int index);
u16     SVC_GetPitchTable(int index);
u8      SVC_GetVolumeTable(int index);

#endif // SDK_TS

#endif // SDK_ARM7


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_SYSTEMCALL_H_ */
#endif
