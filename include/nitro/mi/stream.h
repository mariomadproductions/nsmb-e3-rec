/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     stream.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: stream.h,v $
  Revision 1.4  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.3  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.2  2004/09/09 09:29:33  yada
  only fix comment

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MI_STREAM_H_
#define NITRO_MI_STREAM_H_

#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif


//---- type definition for reading stream
typedef s32 (*MIi_InitReadStreamCallback) (const u8 *devicep, void *ramp, const void *paramp);
typedef s32 (*MIi_TerminateReadStreamCallback) (const u8 *devicep);
typedef u8 (*MIi_ReadByteStreamCallback) (const u8 *devicep);
typedef u16 (*MIi_ReadShortStreamCallback) (const u8 *devicep);
typedef u32 (*MIi_ReadWordStreamCallback) (const u8 *devicep);

//---- structure of callbacks to read stream.
//     genellary used for reading data from devices.
typedef struct
{
    MIi_InitReadStreamCallback initStream;      //---- initialization
    MIi_TerminateReadStreamCallback terminateStream;    //---- termination
    MIi_ReadByteStreamCallback readByteStream;  //---- reading byte stream
    MIi_ReadShortStreamCallback readShortStream;        //---- reading half word stream
    MIi_ReadWordStreamCallback readWordStream;  //---- reading word stream
}
MIReadStreamCallbacks;


//---- get callbacks structure pointer of reading memory stream
MIReadStreamCallbacks *MI_GetReadStreamFromMemoryCallbacks(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MI_STREAM_H_ */
#endif
