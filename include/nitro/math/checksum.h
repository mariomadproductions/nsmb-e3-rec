/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MATH -
  File:     math/dgt.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: checksum.h,v $
  Revision 1.4  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.3  2005/04/13 11:58:43  seiki_masashi
  GetDigest -> GetHash

  Revision 1.2  2005/04/13 04:52:54  seiki_masashi
  Changed to allow Checksum16 to be used regardless of the byte boundary.

  Revision 1.1  2005/04/12 11:11:43  seiki_masashi
  Added checksum.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MATH_CHECKSUM_H_
#define NITRO_MATH_CHECKSUM_H_

#include "nitro/misc.h"
#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Constant definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

typedef u16 MATHChecksum16Context;
typedef MATHChecksum16Context MATHChecksum8Context;

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

/*****************************************************************************/
/* Checksum16                                                                */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_Checksum16Init

  Description:  Used to request the 16bit Checksum value.
                Initializes the MATHChecksum16Context structure.
  
  Arguments:    context MATHChecksum16Context structure
                init    Initial value of CRC
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_Checksum16Init(MATHChecksum16Context * context)
{
    *context = 0;
}

/*---------------------------------------------------------------------------*
  Name:         MATH_Checksum16Update

  Description:  Updates the 16bit Checksum value with added data.
  
  Arguments:    context MATHChecksum16Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_Checksum16Update(MATHChecksum16Context * context, const void *input, u32 length);

/*---------------------------------------------------------------------------*
  Name:         MATH_Checksum16GetHash

  Description:  Gets the final Checksum value.
  
  Arguments:    context MATHChecksum16Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u16 MATH_Checksum16GetHash(MATHChecksum16Context * context)
{
    return (u16)(~(*context));
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcChecksum16

  Description:  Calculates the 16bit Checksum.
  
  Arguments:    data        Pointer to input data.
                dataLength  Length of input data.
  
  Returns:      Checksum value.
 *---------------------------------------------------------------------------*/
u16     MATH_CalcChecksum16(const void *data, u32 dataLength);


/*****************************************************************************/
/* Checksum8                                                                 */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_Checksum8Init

  Description:  Used to request the 8bit Checksum value.
                Initializes the MATHChecksum8Context structure.
  
  Arguments:    context MATHChecksum8Context structure
                init    Initial value of CRC
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_Checksum8Init(MATHChecksum8Context * context)
{
    *context = 0;
}

/*---------------------------------------------------------------------------*
  Name:         MATH_Checksum8Update

  Description:  Updates the 8bit Checksum value with added data.
  
  Arguments:    context MATHChecksum8Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_Checksum8Update(MATHChecksum8Context * context, const void *input, u32 length);

/*---------------------------------------------------------------------------*
  Name:         MATH_Checksum8GetHash

  Description:  Gets the final Checksum value.
  
  Arguments:    context MATHChecksum8Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u8 MATH_Checksum8GetHash(MATHChecksum8Context * context)
{
    u32     sum = *context;
    sum = (sum >> 8) + (sum & 0xff);
    sum += (sum >> 8);

    return (u8)(~sum);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcChecksum8

  Description:  Calculates the 8bit Checksum.
  
  Arguments:    data        Pointer to input data.
                dataLength  Length of input data.
  
  Returns:      Checksum value.
 *---------------------------------------------------------------------------*/
u8      MATH_CalcChecksum8(const void *data, u32 dataLength);



#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_MATH_CHECKSUM_H_ */
#endif
