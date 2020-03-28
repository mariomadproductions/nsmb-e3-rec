/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     compress.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: compress.h,v $
  Revision 1.7  2007/11/12 09:46:58  seiki_masashi
  Fixed copyright header.

  Revision 1.6  2007/11/02 00:46:00  takano_makoto
  Support for LZ77 extended compression

  Revision 1.5  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.4  2005/11/29 05:07:22  takano_makoto
  Added MI_CompressLZFast.

  Revision 1.3  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.2  2005/02/01 02:17:18  takano_makoto
  Changed it so the work buffer is passed as an argument during Huffman compression.

  Revision 1.1  2005/01/28 13:12:43  takano_makoto
  Initial update.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_COMPRESS_H_
#define NITRO_MI_COMPRESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"


/*---------------------------------------------------------------------------*
  Name:         MI_CompressLZ
                MI_CompressLZFast

  Description:  Function that performs LZ77 compression
                In the high-speed version of MI_CompressLZFast, a work buffer the byte size of MI_LZ_FAST_COMPRESS_WORK_SIZE is necessary.
                

  Arguments:    srcp:            Pointer to compression source data
                size:            Size of compression source data
                dstp:            Pointer to destination for compressed data
                                The buffer must be larger than the size of the compression source data.

  Returns:      The data size after compression.
                If compressed data is larger than original data, compression is terminated and 0 is returned.
 *---------------------------------------------------------------------------*/
u32     MI_CompressLZImpl(const u8 *srcp, u32 size, u8 *dstp, BOOL exFormat);
u32     MI_CompressLZFastImpl(const u8 *srcp, u32 size, u8 *dstp, u8 *work, BOOL exFormat);

inline u32 MI_CompressLZ(const u8 *srcp, u32 size, u8 *dstp)
{
    return MI_CompressLZImpl( srcp, size, dstp, FALSE );
}
inline u32 MI_CompressLZEx(const u8 *srcp, u32 size, u8 *dstp)
{
    return MI_CompressLZImpl( srcp, size, dstp, TRUE );
}
inline u32 MI_CompressLZFast(const u8 *srcp, u32 size, u8 *dstp, u8 *work)
{
    return MI_CompressLZFastImpl( srcp, size, dstp, work, FALSE );
}
inline u32 MI_CompressLZExFast(const u8 *srcp, u32 size, u8 *dstp, u8 *work)
{
    return MI_CompressLZFastImpl( srcp, size, dstp, work, TRUE );
}


#define MI_LZ_FAST_COMPRESS_WORK_SIZE   ( (4096 + 256 + 256) * sizeof(s16) )



/*---------------------------------------------------------------------------*
  Name:         MI_CompressRL

  Description:  Function that performs run-length compression

  Arguments:    srcp:            Pointer to compression source data
                size:            Size of compression source data
                dstp:            Pointer to destination for compressed data
                                The buffer must be larger than the size of the compression source data.

  Returns:      The data size after compression.
                If compressed data is larger than original data, compression is terminated and 0 is returned.
 *---------------------------------------------------------------------------*/
u32     MI_CompressRL(const u8 *srcp, u32 size, u8 *dstp);


#define MI_HUFFMAN_COMPRESS_WORK_SIZE   ( 12288 + 512 + 1536 )

/*---------------------------------------------------------------------------*
  Name:         MI_CompressHuffman

  Description:  Function that performs Huffman compression

  Arguments:    srcp:            Pointer to compression source data
                size:            Size of compression source data
                dstp:            Pointer to destination for compressed data
                                The buffer must be larger than the size of the compression source data.
                huffBitSize:    The number of bits to encode.
                work:           The work buffer for compression; requires the size of MI_HUFFMAN_COMPRESS_WORK_SIZE.

  Returns:      The data size after compression.
                If compressed data is larger than original data, compression is terminated and 0 is returned.
 *---------------------------------------------------------------------------*/
u32     MI_CompressHuffman(const u8 *srcp, u32 size, u8 *dstp, u8 huffBitSize, u8 *work);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_COMPRESS_H_ */
#endif
