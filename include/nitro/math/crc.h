/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MATH -
  File:     math/crc.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: crc.h,v $
  Revision 1.5  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.4  2005/04/13 11:58:43  seiki_masashi
  GetDigest -> GetHash

  Revision 1.3  2005/04/11 10:34:54  seiki_masashi
  Added the Utility function.

  Revision 1.2  2005/04/11 08:24:39  seiki_masashi
  small fix

  Revision 1.1  2005/04/11 01:49:56  seiki_masashi
  Added crc.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MATH_CRC_H_
#define NITRO_MATH_CRC_H_

#include "nitro/misc.h"
#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Constant definition
//----------------------------------------------------------------------------

#define MATH_CRC8_STANDARD_POLY     0x07
#define MATH_CRC8_STANDARD_INIT     0

#define MATH_CRC16_STANDARD_POLY    0xa001      // Items that execute bit inversion also invert generator polynomials.
#define MATH_CRC16_STANDARD_INIT    0
#define MATH_CRC16_CCITT_POLY       0x1021
#define MATH_CRC16_CCITT_INIT       0xffff

#define MATH_CRC32_STANDARD_POLY    0xedb88320  // Items that execute bit inversion also invert generator polynomials.
#define MATH_CRC32_STANDARD_INIT    0xffffffff
#define MATH_CRC32_POSIX_POLY       0x04c11db7
#define MATH_CRC32_POSIX_INIT       0

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

typedef u8 MATHCRC8Context;
typedef u16 MATHCRC16Context;
typedef u32 MATHCRC32Context;

typedef struct MATHCRC8Table
{
    u8      table[256];
}
MATHCRC8Table;

typedef struct MATHCRC16Table
{
    u16     table[256];
}
MATHCRC16Table;

typedef struct MATHCRC32Table
{
    u32     table[256];
}
MATHCRC32Table;

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*****************************************************************************/
/* CRC-8 common                                                               */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC8InitTable

  Description:  Initializes the MATHCRC8Table structure used for requesting the CRC-8 value.
  
  Arguments:    table MATHCRC8Table structure
                poly  Bit representation of the generator polynomial with the top bit removed.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATHi_CRC8InitTable(MATHCRC8Table * table, u8 poly);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC8InitTableRev

  Description:  Initializes the MATHCRC8Table structure used for requesting the CRC-8 value.
                The lower-order bit is handled as the higher-order digit.
  
  Arguments:    table MATHCRC8Table structure
                poly  Bit representation of the generator polynomial with the top bit removed where the top and bottom have been reversed.
                      Reversed top-to-bottom.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATHi_CRC8InitTableRev(MATHCRC8Table * table, u8 poly);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC8Init

  Description:  Initializes the MATHCRC8Context structure used for requesting the CRC-8 value.
  
  Arguments:    context MATHCRC8Context structure
                init    Initial value of CRC
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATHi_CRC8Init(MATHCRC8Context * context, u8 init)
{
    *context = init;
}

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC8Update

  Description:  Updates the CRC-8 value with added data.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC8Table
                context MATHCRC8Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void
 
 MATHi_CRC8Update(const MATHCRC8Table * table, MATHCRC8Context * context, const void *input,
                  u32 length);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC8UpdateRev

  Description:  Updates the CRC-8 value with added data.
                The lower-order bit is handled as the higher-order digit.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC8Table
                context MATHCRC8Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
MATHi_CRC8UpdateRev(const MATHCRC8Table * table, MATHCRC8Context * context, const void *input,
                    u32 length)
{
    MATHi_CRC8Update(table, context, input, length);
}

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC8GetHash

  Description:  Gets the final CRC-8 value.
  
  Arguments:    context MATHCRC8Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u8 MATHi_CRC8GetHash(MATHCRC8Context * context)
{
    return (u8)*context;
}

/*****************************************************************************/
/* CRC-8                                                                    */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC8InitTable

  Description:  Initializes the MATHCRC8Table structure used for requesting the CRC-8 value.
  
  Arguments:    table MATHCRC8Table structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC8InitTable(MATHCRC8Table * table)
{
    MATHi_CRC8InitTable(table, MATH_CRC8_STANDARD_POLY);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC8Init

  Description:  Initializes the MATHCRC8Context structure used for requesting the CRC-8 value.
  
  Arguments:    context MATHCRC8Context structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC8Init(MATHCRC8Context * context)
{
    MATHi_CRC8Init(context, MATH_CRC8_STANDARD_INIT);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC8Update

  Description:  Updates the CRC-8 value with added data.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC8Table
                context MATHCRC8Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
MATH_CRC8Update(const MATHCRC8Table * table, MATHCRC8Context * context, const void *input,
                u32 length)
{
    MATHi_CRC8Update(table, context, input, length);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC8GetHash

  Description:  Gets the final CRC-8 value.
  
  Arguments:    context MATHCRC8Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u8 MATH_CRC8GetHash(MATHCRC8Context * context)
{
    return MATHi_CRC8GetHash(context);
}

/*****************************************************************************/
/* CRC-16 common                                                               */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC16InitTable

  Description:  Initializes the MATHCRC16Table structure used for requesting the CRC-16 value.
  
  Arguments:    table MATHCRC16Table structure
                poly  Bit representation of the generator polynomial with the top bit removed.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATHi_CRC16InitTable(MATHCRC16Table * table, u16 poly);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC16InitTableRev

  Description:  Initializes the MATHCRC16Table structure used for requesting the CRC-16 value.
                The lower-order bit is handled as the higher-order digit.
  
  Arguments:    table MATHCRC16Table structure
                poly  Bit representation of the generator polynomial with the top bit removed where the top and bottom have been reversed.
                      Reversed top-to-bottom.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATHi_CRC16InitTableRev(MATHCRC16Table * table, u16 poly);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC16Init

  Description:  Initializes the MATHCRC16Context structure used for requesting the CRC-16 value.
  
  Arguments:    context MATHCRC16Context structure
                init    Initial value of CRC
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATHi_CRC16Init(MATHCRC16Context * context, u16 init)
{
    *context = init;
}

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC16Update

  Description:  Updates the CRC-16 value with added data.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC16Table
                context MATHCRC16Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void
 
 MATHi_CRC16Update(const MATHCRC16Table * table, MATHCRC16Context * context, const void *input,
                   u32 length);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC16UpdateRev

  Description:  Updates the CRC-16 value with added data.
                The lower-order bit is handled as the higher-order digit.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC16Table
                context MATHCRC16Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void
 
 MATHi_CRC16UpdateRev(const MATHCRC16Table * table, MATHCRC16Context * context, const void *input,
                      u32 length);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC16GetHash

  Description:  Gets the final CRC-16 value.
  
  Arguments:    context MATHCRC16Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u16 MATHi_CRC16GetHash(MATHCRC16Context * context)
{
    return (u16)*context;
}

/*****************************************************************************/
/* CRC-16/CCITT(X.25)                                                        */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC16CCITTInitTable

  Description:  Initializes the MATHCRC16Table structure used for requesting the CRC-16/CCITT values.
  
  Arguments:    table MATHCRC16Table structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC16CCITTInitTable(MATHCRC16Table * table)
{
    MATHi_CRC16InitTable(table, MATH_CRC16_CCITT_POLY);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC16CCITTInit

  Description:  Initializes the MATHCRC16Context structure used for requesting the CRC-16/CCITT values.
  
  Arguments:    context MATHCRC16Context structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC16CCITTInit(MATHCRC16Context * context)
{
    MATHi_CRC16Init(context, MATH_CRC16_CCITT_INIT);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC16CCITTUpdate

  Description:  Updates the CRC-16/CCITT values with added data.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC16Table
                context MATHCRC16Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
MATH_CRC16CCITTUpdate(const MATHCRC16Table * table, MATHCRC16Context * context, const void *input,
                      u32 length)
{
    MATHi_CRC16Update(table, context, input, length);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC16CCITTGetHash

  Description:  Gets the final CRC-16/CCITT values.
  
  Arguments:    context MATHCRC16Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u16 MATH_CRC16CCITTGetHash(MATHCRC16Context * context)
{
    return MATHi_CRC16GetHash(context);
}

/*****************************************************************************/
/* CRC-16                                                                    */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC16ARCInitTable

  Description:  Initializes the MATHCRC16Table structure used for requesting the CRC-16 value.
  
  Arguments:    table MATHCRC16Table structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC16InitTable(MATHCRC16Table * table)
{
    MATHi_CRC16InitTableRev(table, MATH_CRC16_STANDARD_POLY);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC16ARCInit

  Description:  Initializes the MATHCRC16Context structure used for requesting the CRC-16 value.
  
  Arguments:    context MATHCRC16Context structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC16Init(MATHCRC16Context * context)
{
    MATHi_CRC16Init(context, MATH_CRC16_STANDARD_INIT);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC16ARCUpdate

  Description:  Updates the CRC-16 value with added data.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC16Table
                context MATHCRC16Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
MATH_CRC16Update(const MATHCRC16Table * table, MATHCRC16Context * context, const void *input,
                 u32 length)
{
    MATHi_CRC16UpdateRev(table, context, input, length);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC16ARCGetHash

  Description:  Gets the final CRC-16 value.
  
  Arguments:    context MATHCRC16Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u16 MATH_CRC16GetHash(MATHCRC16Context * context)
{
    return MATHi_CRC16GetHash(context);
}

/*****************************************************************************/
/* CRC-32 common                                                               */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC32InitTable

  Description:  Initializes the MATHCRC32Table structure used for requesting the CRC-32 value.
  
  Arguments:    table MATHCRC32Table structure
                poly  Bit representation of the generator polynomial with the top bit removed.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATHi_CRC32InitTable(MATHCRC32Table * table, u32 poly);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC16InitTableRev

  Description:  Initializes the MATHCRC16Table structure used for requesting the CRC-32 value.
                The lower-order bit is handled as the higher-order digit.
  
  Arguments:    table MATHCRC16Table structure
                poly  Bit representation of the generator polynomial with the top bit removed where the top and bottom have been reversed.
                      Reversed top-to-bottom.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATHi_CRC32InitTableRev(MATHCRC32Table * table, u32 poly);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC32Init

  Description:  Initializes the MATHCRC32Context structure used for requesting the CRC-32 value.
  
  Arguments:    context MATHCRC32Context structure
                init    Initial value of CRC
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATHi_CRC32Init(MATHCRC32Context * context, u32 init)
{
    *context = init;
}

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC32Update

  Description:  Updates the CRC-32 value with added data.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC32Table
                context MATHCRC32Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void
 
 MATHi_CRC32Update(const MATHCRC32Table * table, MATHCRC32Context * context, const void *input,
                   u32 length);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC32UpdateRev

  Description:  Updates the CRC-32 value with added data.
                The lower-order bit is handled as the higher-order digit.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC32Table
                context MATHCRC32Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void
 
 MATHi_CRC32UpdateRev(const MATHCRC32Table * table, MATHCRC32Context * context, const void *input,
                      u32 length);

/*---------------------------------------------------------------------------*
  Name:         MATHi_CRC32GetHash

  Description:  Gets the final CRC-32 value.
  
  Arguments:    context MATHCRC32Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u32 MATHi_CRC32GetHash(MATHCRC32Context * context)
{
    return (u32)*context;
}

/*****************************************************************************/
/* CRC-32                                                                    */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC32InitTable

  Description:  Initializes the MATHCRC32Table structure used for requesting the CRC-32 value.
  
  Arguments:    table MATHCRC32Table structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC32InitTable(MATHCRC32Table * table)
{
    MATHi_CRC32InitTableRev(table, MATH_CRC32_STANDARD_POLY);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC32Init

  Description:  Initializes the MATHCRC32Context structure used for requesting the CRC-32 value.
  
  Arguments:    context MATHCRC32Context structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC32Init(MATHCRC32Context * context)
{
    MATHi_CRC32Init(context, MATH_CRC32_STANDARD_INIT);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC32Update

  Description:  Updates the CRC-32 value with added data.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC32Table
                context MATHCRC32Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
MATH_CRC32Update(const MATHCRC32Table * table, MATHCRC32Context * context, const void *input,
                 u32 length)
{
    MATHi_CRC32UpdateRev(table, context, input, length);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC32GetHash

  Description:  Gets the final CRC-32 value.
  
  Arguments:    context MATHCRC32Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u32 MATH_CRC32GetHash(MATHCRC32Context * context)
{
    return (u32)(~MATHi_CRC32GetHash(context));
}

/*****************************************************************************/
/* CRC-32/POSIX 1003.2                                                       */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC32POSIXInitTable

  Description:  Initializes the MATHCRC32Table structure used for requesting the CRC-32/POSIX value.
  
  Arguments:    table MATHCRC32Table structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC32POSIXInitTable(MATHCRC32Table * table)
{
    MATHi_CRC32InitTable(table, MATH_CRC32_POSIX_POLY);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC32POSIXInit

  Description:  Initializes the MATHCRC32Context structure used for requesting the CRC-32/POSIX value.
  
  Arguments:    context MATHCRC32Context structure
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void MATH_CRC32POSIXInit(MATHCRC32Context * context)
{
    MATHi_CRC32Init(context, MATH_CRC32_POSIX_INIT);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC32POSIXUpdate

  Description:  Updates the CRC-32/POSIX values with added data.
  
  Arguments:    table   Pointer to the table for calculation, MATHCRC32Table
                context MATHCRC32Context structure
                input   Pointer to input data.
                length  Length of input data
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
MATH_CRC32POSIXUpdate(const MATHCRC32Table * table, MATHCRC32Context * context, const void *input,
                      u32 length)
{
    MATHi_CRC32Update(table, context, input, length);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CRC32POSIXGetHash

  Description:  Gets the final CRC-32/POSIX values.
  
  Arguments:    context MATHCRC32Context structure
  
  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
static inline u32 MATH_CRC32POSIXGetHash(MATHCRC32Context * context)
{
    return (u32)(~MATHi_CRC32GetHash(context));
}


/*****************************************************************************/
/* Utility function.                                                        */
/*****************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcCRC8

  Description:  Calculates the CRC-8 value.

  Arguments:    table   Pointer to the table for calculation, MATHCRC8Table
                data    Pointer to input data.
                dataLength  Length of input data.

  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
u8      MATH_CalcCRC8(const MATHCRC8Table * table, const void *data, u32 dataLength);

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcCRC16

  Description:  Calculates the CRC-16 value.

  Arguments:    table   Pointer to the table for calculation, MATHCRC16Table
                data    Pointer to input data.
                dataLength  Length of input data.

  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
u16     MATH_CalcCRC16(const MATHCRC16Table * table, const void *data, u32 dataLength);

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcCRC16CCITT

  Description:  Calculates the CRC-16/CCITT values.

  Arguments:    table   Pointer to the table for calculation, MATHCRC16Table
                data    Pointer to input data.
  Arguments:    data    Pointer to input data.
                dataLength  Length of input data.

  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
u16     MATH_CalcCRC16CCITT(const MATHCRC16Table * table, const void *data, u32 dataLength);

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcCRC32

  Description:  Calculates the CRC-32 value.

  Arguments:    table   Pointer to the table for calculation, MATHCRC32Table
                data    Pointer to input data.
                dataLength  Length of input data.

  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
u32     MATH_CalcCRC32(const MATHCRC32Table * table, const void *data, u32 dataLength);

/*---------------------------------------------------------------------------*
  Name:         MATH_CalcCRC32POSIX

  Description:  Calculates the CRC-32/POSIX values.

  Arguments:    table   Pointer to the table for calculation, MATHCRC32Table
                data    Pointer to input data.
                dataLength  Length of input data.

  Returns:      Calculation result.
 *---------------------------------------------------------------------------*/
u32     MATH_CalcCRC32POSIX(const MATHCRC32Table * table, const void *data, u32 dataLength);





#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_MATH_CRC_H_ */
#endif
