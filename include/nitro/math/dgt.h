/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MATH -
  File:     math/dgt.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: dgt.h,v $
  Revision 1.8  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.7  2005/04/13 11:58:43  seiki_masashi
  GetDigest -> GetHash

  Revision 1.6  2005/04/11 10:34:25  seiki_masashi
  Added the MATH_CalcMD5, MATH_CalcSHA1 function

  Revision 1.5  2005/04/04 01:23:08  seiki_masashi
  small fix

  Revision 1.4  2005/04/01 12:29:14  seiki_masashi
  Changed u8* digest to void* digest

  Revision 1.3  2005/04/01 07:45:37  seiki_masashi
  Changed HMAC-related functions.

  Revision 1.2  2005/03/29 09:30:35  seiki_masashi
  Cleaned up for publication.

  Revision 1.1  2005/03/28 04:20:27  seiki_masashi
  Added math/dgt.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MATH_DGT_H_
#define NITRO_MATH_DGT_H_

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/dgt/common.h"
#include "nitro/dgt/dgt.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Constant definition
//----------------------------------------------------------------------------

// Digest length
#define MATH_MD5_DIGEST_SIZE    DGT_HASH1_DIGEST_SIZE   // 128 bit
#define MATH_SHA1_DIGEST_SIZE   DGT_HASH2_DIGEST_SIZE   // 160 bit

// Process block length
#define MATH_MD5_BLOCK_SIZE     DGT_HASH_BLOCK_SIZE     // 512bit
#define MATH_SHA1_BLOCK_SIZE    DGT_HASH_BLOCK_SIZE     // 512bit

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

typedef DGTHash1Context MATHMD5Context;
typedef DGTHash2Context MATHSHA1Context;

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

/*****************************************************************************/
/* MD5                                                                       */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_MD5Init

  Description:  Initializes the MATHMD5Context structure used for requesting the MD5 value.
  
  Arguments:    context MATHMD5Context structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_MD5Init(MATHMD5Context * context)
{
    DGT_Hash1Reset(context);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_MD5Update

  Description:  Updates the MD5 value with added data.
  
  Arguments:    context MATHMD5Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_MD5Update(MATHMD5Context * context, const void *input, u32 length)
{
    DGT_Hash1SetSource(context, (u8 *)input, length);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_MD5GetHash

  Description:  Gets the final MD5 value.
  
  Arguments:    context MATHMD5Context structure
                digest  Pointer to the location where MD5 is stored.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_MD5GetHash(MATHMD5Context * context, void *digest)
{
    DGT_Hash1GetDigest_R((u8 *)digest, context);
}

// For lower compatibility
static inline void MATH_MD5GetDigest(MATHMD5Context * context, void *digest)
{
    MATH_MD5GetHash(context, digest);
}


/*****************************************************************************/
/* SHA-1                                                                     */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_SHA1Init

  Description:  Initializes the MATHSHA1Context structure used for requesting the SHA1 value.
  
  Arguments:    context MATHSHA1Context structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_SHA1Init(MATHSHA1Context * context)
{
    DGT_Hash2Reset(context);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_SHA1Update

  Description:  Updates the SHA1 value with added data.
  
  Arguments:    context MATHSHA1Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_SHA1Update(MATHSHA1Context * context, const void *input, u32 length)
{
    DGT_Hash2SetSource(context, (u8 *)input, length);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_SHA1GetHash

  Description:  Gets the final SHA1 value.
  
  Arguments:    context MATHSHA1Context structure
                digest  Pointer to the location where the SHA1 value is stored.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_SHA1GetHash(MATHSHA1Context * context, void *digest)
{
    DGT_Hash2GetDigest(context, (u8 *)digest);
}

// For lower compatibility
static inline void MATH_SHA1GetDigest(MATHSHA1Context * context, void *digest)
{
    MATH_SHA1GetHash(context, digest);
}


/*****************************************************************************/
/* Utility function.                                                        */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcMD5

  Description:  Calculates MD5.
  
  Arguments:    digest      Pointer to the location where MD5 is stored.
                data        Pointer to input data.
                dataLength  Length of input data.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_CalcMD5(void *digest, const void *data, u32 dataLength);

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcSHA1

  Description:  Calculates SHA-1.
  
  Arguments:    digest      Pointer to the location where SHA-1 is stored.
                data        Pointer to input data.
                dataLength  Length of input data.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_CalcSHA1(void *digest, const void *data, u32 dataLength);


/*---------------------------------------------------------------------------*
  Name:         MATH_CalcHMACMD5

  Description:  Calculates HMAC-MD5.
  
  Arguments:    digest      Pointer to the location where HMAC-MD5 is stored.
                data        Pointer to input data.
                dataLength  Length of input data.
                key         Pointer to the key
                keyLength   Length of the key
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
MATH_CalcHMACMD5(void *digest, const void *data, u32 dataLength, const void *key, u32 keyLength)
{
    DGT_Hash1CalcHmac(digest, (void *)data, (int)dataLength, (void *)key, (int)keyLength);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcHMACSHA1

  Description:  Calculates HMAC-SHA-1.
  
  Arguments:    digest      Pointer to the location where the HMAC-SHA-1 value is stored.
                data        Pointer to input data.
                dataLength  Length of input data.
                key         Pointer to the key
                keyLength   Length of the key
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
MATH_CalcHMACSHA1(void *digest, const void *data, u32 dataLength, const void *key, u32 keyLength)
{
    DGT_Hash2CalcHmac(digest, (void *)data, (int)dataLength, (void *)key, (int)keyLength);
}

#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_MATH_DGT_H_ */
#endif
