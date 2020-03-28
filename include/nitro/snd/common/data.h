/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     data.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: data.h,v $
  Revision 1.9  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.8  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.7  2004/10/15 15:17:55  yasu
  sound patch for NITRO-System 10/12

  Revision 1.3  2004/05/14 01:46:37  ida
  remove SND_FindBinaryBlock

  Revision 1.2  2004/05/13 01:04:11  ida
  SNDBinaryHeader -> SNDBinaryFileHeader

  Revision 1.1  2004/05/12 06:38:31  ida
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_DATA_H_
#define NITRO_SND_COMMON_DATA_H_

#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
	structure definition
 ******************************************************************************/

typedef struct SNDBinaryFileHeader
{
    char    signature[4];
    u16     byteOrder;
    u16     version;
    u32     fileSize;
    u16     headerSize;
    u16     dataBlocks;
}
SNDBinaryFileHeader;

typedef struct SNDBinaryBlockHeader
{
    u32     kind;
    u32     size;
}
SNDBinaryBlockHeader;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_DATA_H_ */
