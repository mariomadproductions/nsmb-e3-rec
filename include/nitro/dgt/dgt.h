/*---------------------------------------------------------------------------*
  Project:  NitroSDK - DGT - include
  File:     dgt.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: dgt.h,v $
  Revision 1.10  2005/09/08 11:35:39  yasu
  Support for SDK_FROM_TOOL

  Revision 1.9  2005/07/14 02:49:03  seiki_masashi
  Minor fixes

  Revision 1.8  2005/07/14 02:32:02  seiki_masashi
  Cleaned up compile switches

  Revision 1.7  2005/07/08 12:34:33  seiki_masashi
  Speedup of HASH2 algorithm

  Revision 1.6  2005/06/27 00:12:05  seiki_masashi
  Revised to C standard types

  Revision 1.5  2005/06/24 01:16:46  seiki_masashi
  Deleted old implementation

  Revision 1.4  2005/06/24 01:10:28  seiki_masashi
  Changed MD5 implementation

  Revision 1.3  2005/03/29 03:59:26  seiki_masashi
  Revised copyright.

  Revision 1.2  2005/03/29 00:07:23  seiki_masashi
  Revised to C standard types

  Revision 1.1  2005/03/28 04:18:34  seiki_masashi
  Moved part of common.h to dgt.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_DGT_DGT_H_
#define NITRO_DGT_DGT_H_

#include "nitro/dgt/common.h"

#ifdef __cplusplus
extern "C" {
#endif

// Declaration of context structure
typedef struct DGTHash1Context
{
    union
    {
        struct
        {
            unsigned long a, b, c, d;
        };
        unsigned long state[4];
    };
    unsigned long long length;
    union
    {
        unsigned long buffer32[16];
        unsigned char buffer8[64];
    };
} DGTHash1Context;

#if defined(SDK_DGT_HASH2_CODE_SAFE) || defined(SDK_WIN32) || defined(SDK_FROM_TOOL)
typedef struct DGTHash2Context
{
    unsigned long Intermediate_Hash[5];
    unsigned long Length_Low;
    unsigned long Length_High;
    int Message_Block_Index;
    unsigned char Message_Block[64];
    int Computed;
    int Corrupted;
} DGTHash2Context;
#else
typedef struct DGTHash2Context
{
    unsigned long h0,h1,h2,h3,h4;
    unsigned long Nl,Nh;
    int num;
    unsigned long data[64/4];
    int dummy[2];
} DGTHash2Context;
#endif // defined(SDK_DGT_HASH2_CODE_SAFE) || defined(SDK_WIN32) || defined(SDK_FROM_TOOL)


// Calculate hash
#ifdef SDK_DGT_HASH1_CODE_SAFE
void DGT_Hash1Reset(DGTHash1Context*);
void DGT_Hash1SetSource(DGTHash1Context*, unsigned char*, unsigned long);
void DGT_Hash1GetDigest_R(unsigned char digest[16], DGTHash1Context*);
#else
void DGT_Hash1Reset(DGTHash1Context*);
void DGT_Hash1SetSource(DGTHash1Context*, const void*, unsigned long);
void DGT_Hash1GetDigest_R(void* digest, DGTHash1Context*);
#endif

#if defined(SDK_DGT_HASH2_CODE_SAFE) || defined(SDK_WIN32) || defined(SDK_FROM_TOOL)
void DGT_Hash2Reset(DGTHash2Context*);
void DGT_Hash2SetSource(DGTHash2Context*, unsigned char*, unsigned long);
void DGT_Hash2GetDigest(DGTHash2Context*, unsigned char digest[20]);
#else
void DGT_Hash2Reset(DGTHash2Context*);
void DGT_Hash2SetSource(DGTHash2Context*, const unsigned char*, unsigned long);
void DGT_Hash2GetDigest(DGTHash2Context*, unsigned char* digest);
#endif


// Calculate HMAC
void	DGT_Hash1CalcHmac(
            void*   digest,     //  Digest output region
		    void*   bin_ptr,    //  Pointer to data
		    int     bin_len,    //  Data length
		    void*   key_ptr,    //  Pointer to key
		    int     key_len     //  Key length
		    );

void	DGT_Hash2CalcHmac(
            void*   digest,     //  Digest output region
		    void*   bin_ptr,    //  Pointer to data
		    int     bin_len,    //  Data length
		    void*   key_ptr,    //  Pointer to key
		    int     key_len     //  Key length
		    );

//  Create the HMAC value from these three regions: RomHeader,main & sub
int     DGT_Hash1CalcHmacForRms(
                    void*   digest,     //  Create digest region
                    void*   romh_ptr,   //  Pointer to data
                    int     romh_len,   //  Data length
                    void*   mbin_ptr,   //  Pointer to data
                    int     mbin_len,   //  Data length
                    void*   sbin_ptr,   //  Pointer to data
                    int     sbin_len,   //  Data length
                    void*   key_ptr,    //  Pointer to key
                    int     key_len     //  Key length
                    );

int     DGT_Hash2CalcHmacForRms(
                    void*   digest,     //  Create digest region
                    void*   romh_ptr,   //  Pointer to data
                    int     romh_len,   //  Data length
                    void*   mbin_ptr,   //  Pointer to data
                    int     mbin_len,   //  Data length
                    void*   sbin_ptr,   //  Pointer to data
                    int     sbin_len,   //  Data length
                    void*   key_ptr,    //  Pointer to key
                    int     key_len     //  Key length
                    );

//  Check the HMAC value from these three regions: RomHeader,main & sub
int     DGT_Hash1TestHmacForRms(
                    void*   digest,     //  Confirm digest region
                    void*   romh_ptr,   //  Pointer to data
                    int     romh_len,   //  Data length
                    void*   mbin_ptr,   //  Pointer to data
                    int     mbin_len,   //  Data length
                    void*   sbin_ptr,   //  Pointer to data
                    int     sbin_len,   //  Data length
                    void*   key_ptr,    //  Pointer to key
                    int     key_len     //  Key length
                    );

int     DGT_Hash2TestHmacForRms(
                    void*   digest,     //  Confirm digest region
                    void*   romh_ptr,   //  Pointer to data
                    int     romh_len,   //  Data length
                    void*   mbin_ptr,   //  Pointer to data
                    int     mbin_len,   //  Data length
                    void*   sbin_ptr,   //  Pointer to data
                    int     sbin_len,   //  Data length
                    void*   key_ptr,    //  Pointer to key
                    int     key_len     //  Key length
                    );

int     DGT_SetOverlayTableMode( int flag );

#ifdef __cplusplus
}
#endif
#endif
