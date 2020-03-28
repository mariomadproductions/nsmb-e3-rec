/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     uncompress.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: uncompress.h,v $
  Revision 1.12  2006/01/18 02:12:29  kitase_hirotake
  do-indent

  Revision 1.11  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.10  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.9  2004/11/30 07:40:22  takano_makoto
  Added MICompressionHeader structure

  Revision 1.8  2004/11/15 07:53:18  takano_makoto
  Added MI_UnfilterDiff8(), MI_UnfilterDiff16().

  Revision 1.7  2004/09/04 12:40:36  yasu
  Change interface between compstatic tool

  Revision 1.6  2004/09/02 09:48:37  yasu
  Add MIi_UncompressModule

  Revision 1.5  2004/07/20 07:28:42  yada
  some uncompressing functions are changed in system call functions renewal

  Revision 1.4  2004/06/18 01:28:48  yada
  add MI_GetUncompressedSize(), MI_GetCompressionType()

  Revision 1.3  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.2  2004/02/10 06:38:55  yada
  Changed function name. UnComp -> UnCompress, etc.

  Revision 1.1  2004/02/10 01:20:25  yada
  Migration from UTL_


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_UNCOMPRESS_H_
#define NITRO_MI_UNCOMPRESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"


//---- compression type
typedef enum
{
    MI_COMPRESSION_LZ = 0x10,          // LZ77
    MI_COMPRESSION_HUFFMAN = 0x20,     // Huffman
    MI_COMPRESSION_RL = 0x30,          // Run Length
    MI_COMPRESSION_DIFF = 0x80,        // Differential filter

    MI_COMPRESSION_TYPE_MASK = 0xf0,
    MI_COMPRESSION_TYPE_EX_MASK = 0xff
}
MICompressionType;


//----------------------------------------------------------------
// Compressed data header
//
typedef struct
{
    u32     compParam:4;
    u32     compType:4;
    u32     destSize:24;

}
MICompressionHeader;



//----------------------------------------------------------------
// Parameters for expanding bit compressed data
//
typedef struct
{
    u16     srcNum;                    // Source data. Number of bytes.   
    u16     srcBitNum:8;               // 1 source data. Number of bits.   
    u16     destBitNum:8;              // 1 destination data. Number of bits.  
    u32     destOffset:31;             // Number to add to source data
    u32     destOffset0_on:1;          // Flag for whether to add an offset to 0 data.
}
MIUnpackBitsParam;


//======================================================================
//          Expanding compressed data
//======================================================================

//----------------------------------------------------------------------
//          Expanding bit compressed data
//
//- Unpacks data padded with bits fixed to 0.
//- Align the destination address to a 4-byte boundary.
//
//- Arguments:
//             void *srcp              source address
//             void *destp             destination address
//  MIUnpackBitsParam *paramp   Address of MIUnpackBitsParam structure
//
//- MIUnpackBitsParam Structure
//    u16 srcNum              Number of bytes of source data
//    u8  srcBitNum           Number of bits per source data
//    u8  destBitNum          Number of bits per destination data
//    u32 destOffset:31       Offset number to add to source data.
//        destOffset0_On:1    Flag for whether to add an offset to 0 data.
//
//- Return value: None
//----------------------------------------------------------------------

void    MI_UnpackBits(const void *srcp, void *destp, MIUnpackBitsParam *paramp);


//----------------------------------------------------------------------
//          8-bit expansion of LZ77 compressed data
//
//- Expands LZ77 compressed data, and writes in 8-bit units.
//- Cannot decode directly into VRAM
//- If the size of compressed data is not a multiple of four,
//  adjust as necessary by padding with 0s.
//- Align source address to a 4-byte boundary.
//
//- Arguments:
//    void *srcp              source address
//    void *destp             destination address
//
//- Data header
//    u32 :4                  reserved
//        compType:4          compression type  ( = 1)
//        destSize:24         Data size after decoding
//
//- Flag data format
//    u8  flags               compression/no compression flag
//                            (0, 1) = (not compressed, compressed)
//- Code data format (Big Endian)
//    u16 length:4            Expansion data length - 3(Only compress when the match length is 3-bytes or greater)
//        offset:12           match data offset - 1
//
//- Return value: None
//----------------------------------------------------------------------

void    MI_UncompressLZ8(const void *srcp, void *destp);


//----------------------------------------------------------------------
//          16-bit expansion of LZ77 compressed data
//
//- Expands LZ77 compressed data, and writes in 16-bit units.
//- Although it can expand in data TCM and main memory,
//  it is slower than MI_UncompressRL8().
//- For compress data, search for a matching character string from a minimum of 2 bytes before.
//- If the size of compressed data is not a multiple of four,
//  adjust as necessary by padding with 0s.
//- Align source address to a 4-byte boundary.
//
//-Arguments:
//    void *srcp              source address
//    void *destp             destination address
//
//- Data header
//    u32 :4                  reserved
//        compType:4          compression type  ( = 1)
//        destSize:24         Data size after decoding
//
//- Flag data format
//    u8  flags               compression/no compression flag
//                            (0, 1) = (not compressed, compressed)
//- Code data format (Big Endian)
//    u16 length:4            Expansion data length - 3(Only compress when the match length is 3-bytes or greater)
//        offset:12           Match data offset ( >= 2) - 1
//
//- Return value: None
//----------------------------------------------------------------------

void    MI_UncompressLZ16(const void *srcp, void *destp);


//----------------------------------------------------------------------
//          Expansion of Huffman-compressed data
//
//- Expands Huffman compressed data, and writes in 32-bit units.
//- If the size of compressed data is not a multiple of four,
//  adjust as necessary by padding with 0s.
//- Align source address to a 4-byte boundary.
//
//- Arguments:
//    void *srcp              source address
//    void *destp             destination address
//
//- Data header
//    u32 bitSize:4           1 data bit size (Normally 4|8)
//        compType:4          compression type  ( = 2)
//        destSize:24         Data size after decoding
//
//- Tree table
//    u8           treeSize        tree table size/2 - 1
//    TreeNodeData nodeRoot        root node
//
//    TreeNodeData nodeLeft        root left node
//    TreeNodeData nodeRight       root right node
//
//    TreeNodeData nodeLeftLeft    left left node
//    TreeNodeData nodeLeftRight   left ride node
//
//    TreeNodeData nodeRightLeft   right left node
//    TreeNodeData nodeRightRight  right right node
//
//            .
//            .
//
//  The compress data structure follows
//
//- TreeNodeData structure
//    u8  nodeNextOffset:6    Offset to the next node data - 1 (2-byte units)
//        rightEndFlag:1      right node end flag
//        leftEndzflag:1       Left node end flag
//                            when end flag is set
//                            there is data in next node
//
//- Return value: None
//----------------------------------------------------------------------

void    MI_UncompressHuffman(const void *srcp, void *destp);


//----------------------------------------------------------------------
//          8-bit expansion of runlength-compressed data
//
//- Expands runlength compressed data, and writes in 8-bit units.
//- Cannot decode directly into VRAM
//- If the size of compressed data is not a multiple of four,
//  adjust as necessary by padding with 0s.
//- Align source address to a 4-byte boundary.
//
//- Arguments:
//    void *srcp              source address
//    void *destp             destination address
//
//- Data header
//    u32 :4                  reserved
//        compType:4          compression type  ( = 3)
//        destSize:24         Data size after decoding
//
//- Flag data format
//    u8  length:7            Expansion data length - 1 (When not compressed)
//                            Expansion data length - 3 (Only compress when the contiguous length is 3-bytes or greater)
//        flag:1              (0, 1) = (not compressed, compressed)
//
//- Return value: None
//----------------------------------------------------------------------

void    MI_UncompressRL8(const void *srcp, void *destp);


//----------------------------------------------------------------------
//          16-bit expansion of runlength-compressed data
//
//- Expands runlength compressed data, and writes in 16-bit units.
//- Although it can expand in data TCM or main memory,
//  it is slower than MI_UncompressRL8().
//- If the size of compressed data is not a multiple of four,
//  adjust as necessary by padding with 0s.
//- Align source address to a 4-byte boundary.
//
//- Arguments:
//    void *srcp              source address
//    void *destp             destination address
//
//- Data header
//    u32 :4                  reserved
//        compType:4          compression type  ( = 3)
//        destSize:24         Data size after decoding
//
//- Flag data format
//    u8  length:7            Expansion data length - 1 (When not compressed)
//                            Expansion data length - 3 (Only compress when the contiguous length is 3-bytes or greater)
//        flag:1              (0, 1) = (not compressed, compressed)
//
//- Return value: None
//----------------------------------------------------------------------

void    MI_UncompressRL16(const void *srcp, void *destp);


//----------------------------------------------------------------------
//          Decode differential filter conversion. Use 8-bit decoding.
//
//- Decodes a differential filter. Writes in 8-bit units.
//- Cannot decode directly into VRAM
//- If the size of compressed data is not a multiple of four,
//  adjust as necessary by padding with 0s.
//- Align source address to a 4-byte boundary.
//
//- Arguments:
//    void *srcp              source address
//    void *destp             destination address
//
//- Data header
//    u32 :4                  Bit size of unit
//        compType:4          compression type  ( = 3)
//        destSize:24         Data size after decoding
//
//- Return value: None
//----------------------------------------------------------------------

void    MI_UnfilterDiff8(const void *srcp, void *destp);

//----------------------------------------------------------------------
//          Decode differential filter conversion. Use 16-bit decoding.
//
//- Decodes a differential filter. Writes in 16-bit units.
//- You can decode to data TCM or VRAM. However,
//  it is slower than MI_UncompressRL8().//---- 
//- If the size of compressed data is not a multiple of four,
//  adjust as necessary by padding with 0s.
//- Align source address to a 4-byte boundary.
//
//- Arguments:
//    void *srcp              source address
//    void *destp             destination address
//
//-  Data header
//    u32 :4                  Bit size of unit
//        compType:4          compression type  ( = 3)
//        destSize:24         Data size after decoding
//
//- Return value: None
//----------------------------------------------------------------------

void    MI_UnfilterDiff16(const void *srcp, void *destp);


//================================================================================
/*---------------------------------------------------------------------------*
  Name:         MI_GetUncompressedSize

  Description:  get data size after uncompressing.
                this function can be used for all compress type
                (LZ8, LZ16, Huffman, RL8, RL16)

  Arguments:    srcp :  compressed data address

  Returns:      size
 *---------------------------------------------------------------------------*/
static inline u32 MI_GetUncompressedSize(const void *srcp)
{
    return (*(u32 *)srcp >> 8);
}

/*---------------------------------------------------------------------------*
  Name:         MI_GetCompressionType

  Description:  get compression type from compressed data

  Arguments:    srcp :  compressed data address

  Returns:      compression type.
                MI_COMPREESION_LZ      : mean compressed by LZ77
                MI_COMPREESION_HUFFMAN : mean compressed by Huffman
                MI_COMPREESION_RL      : mean compressed by Run Length
                MI_COMPRESSION_DIFF    : mean converted by Differential filter
 *---------------------------------------------------------------------------*/
static inline MICompressionType MI_GetCompressionType(const void *srcp)
{
    return (MICompressionType)(*(u32 *)srcp & MI_COMPRESSION_TYPE_MASK);
}



/*---------------------------------------------------------------------------*
  Name:         MIi_UncompressBackward

  Description:  Uncompress special archive for module compression

  Arguments:    bottom      = Bottom adrs of packed archive + 1
                bottom[-12] = offset for top    of compressed data
                                 inp_top = bottom + bottom[-12]
                bottom[-8]  = offset for bottom of compressed data
                                 inp     = bottom + bottom[ -8]
                bottom[ -4] = offset for bottom of original data
                                 outp    = bottom + bottom[ -4]
  
                typedef struct
                {
                    int         bufferTop;
                    int         compressBottom;
                    int         originalBottom;
                }  CompFooter;

  Returns:      None.
 *---------------------------------------------------------------------------*/
// !!!! Coded in libraries/init/ARM9/crt0.c
void    MIi_UncompressBackward(void *bottom);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_UNCOMPRESS_H_ */
#endif
