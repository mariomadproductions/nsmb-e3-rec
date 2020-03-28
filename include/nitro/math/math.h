/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MATH -
  File:     math/math.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: math.h,v $
  Revision 1.15  2006/08/07 13:34:42  yosizaki
  remove prototype of MATH_CLZ.

  Revision 1.14  2006/06/26 13:06:44  yosizaki
  fix MATH_CLZ().

  Revision 1.13  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.12  2005/12/22 06:04:01  yosizaki
  add MATH_CTZ, LSB, MSB.
  change inline to SDK_INLINE.

  Revision 1.11  2005/03/04 11:09:27  yasu
  Changed __declspec(weak) to SDK_WEAK_SYMBOL

  Revision 1.10  2005/02/28 05:26:24  yosizaki
  do-indent.

  Revision 1.9  2005/01/21 09:54:42  yasu
  Copyright year 2004->2005

  Revision 1.8  2005/01/21 07:34:19  yasu
  merge with RC4branch

  Revision 1.7.2.1  2005/01/21 05:59:43  yasu
  Fix a bug "MATH_CountLeadingZeros() not inlined"

  Revision 1.7  2004/12/16 09:58:14  takano_makoto
  small fix

  Revision 1.6  2004/12/15 10:52:38  seiki_masashi
  Added MATH_ROUNDUP32,DOWN32

  Revision 1.5  2004/12/15 09:39:26  seiki_masashi
  Added MATH_ROUNDUP,DOWN

  Revision 1.4  2004/12/15 09:17:07  seiki_masashi
  Added MATH_CountPopulation

  Revision 1.3  2004/12/15 07:13:31  takano_makoto
  Added MATH_ABS, MATH_IAbs, MATH_CLAMP

  Revision 1.2  2004/12/15 00:34:25  seiki_masashi
  Added "static" qualifier to "inline" function.
  Changed the order of evaluating the MATH_MIN, MAX arguments to be same as the order of the arguments themselves.

  Revision 1.1  2004/12/14 10:52:20  seiki_masashi
  Added MATH genre

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MATH_MATH_H_
#define NITRO_MATH_MATH_H_

#include "nitro/misc.h"
#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         MATH_ABS

  Description:  Macro that returns absolute value.
                Be careful about side effects, since each argument is subjected to multiple 
  
  Arguments:    a

  Returns:      If a < 0 -a. Otherwise, a
 *---------------------------------------------------------------------------*/
#define MATH_ABS(a) ( ( (a) < 0 ) ? (-(a)) : (a) )

/*---------------------------------------------------------------------------*
  Name:         MATH_IAbs

  Description:  Inline function that returns absolute value.
                Since this is implemented as an inline function, there are no side effects.
  
  Arguments:    a

  Returns:      If a < 0 -a. Otherwise, a
 *---------------------------------------------------------------------------*/
SDK_INLINE int MATH_IAbs(int a)
{
    return (a < 0) ? -a : a;
}


/*---------------------------------------------------------------------------*
  Name:         MATH_CLAMP

  Description:  Macro that gets values in the range from "low" to "high."
                Be careful about side effects, since each argument is subjected to multiple 
  
  Arguments:    x
                low   Maximum value
                hight Minimum value
  
  Returns:      If x < low, low.  If x > high, high. Otherwise x.
 *---------------------------------------------------------------------------*/
#define MATH_CLAMP(x, low, high) ( ( (x) > (high) ) ? (high) : ( ( (x) < (low) ) ? (low) : (x) ) )


/*---------------------------------------------------------------------------*
  Name:         MATH_MIN

  Description:  Compares two arguments and returns the smaller one.
                This is implemented as a macro, so it can be used in the
                type that defines the inequality operator. Be careful about side effects, since each argument is subjected to multiple 

  Arguments:    a, b

  Returns:      If a < b, a. Otherwise, b.
 *---------------------------------------------------------------------------*/
#define MATH_MIN(a,b) (((a) <= (b)) ? (a) : (b))


/*---------------------------------------------------------------------------*
  Name:         MATH_IMin

  Description:  Compares two int-type integer arguments and returns the smaller one.
                Since this is implemented as an inline function, there are no side effects.

  Arguments:    a, b - int type integers

  Returns:      If a < =b, a. Otherwise, b.
 *---------------------------------------------------------------------------*/
SDK_INLINE int MATH_IMin(int a, int b)
{
    return (a <= b) ? a : b;
}

/*---------------------------------------------------------------------------*
  Name:         MATH_MAX

  Description:  Compares two arguments and returns the larger one.
                This is implemented as a macro, so it can be used in the
                type that defines the inequality operator. Be careful about side effects, since each argument is subjected to multiple 

  Arguments:    a, b

  Returns:      If a > =b, a. Otherwise, b.
 *---------------------------------------------------------------------------*/
#define MATH_MAX(a,b) (((a) >= (b)) ? (a) : (b))

/*---------------------------------------------------------------------------*
  Name:         MATH_IMax

  Description:  Compares two int-type integer arguments and returns the larger one.
                Since this is implemented as an inline function, there are no side effects.

  Arguments:    a, b - int type integers

  Returns:      If a > =b, a. Otherwise, b.
 *---------------------------------------------------------------------------*/
SDK_INLINE int MATH_IMax(int a, int b)
{
    return (a >= b) ? a : b;
}

/*---------------------------------------------------------------------------*
  Name:         MATH_ROUNDUP

  Description:  Macro that returns the rounded-up value.
  
  Arguments:    x
                base - Base to the second power

  Returns:      Smallest multiple of "base" that is greater or equal to x
 *---------------------------------------------------------------------------*/
#define MATH_ROUNDUP(x, base) (((x) + ((base)-1)) & ~((base)-1))

/*---------------------------------------------------------------------------*
  Name:         MATH_ROUNDDOWN

  Description:  Macro that returns the rounded-down value.
  
  Arguments:    x
                base - Base to the second power

  Returns:      Largest multiple of "base" that is equal or less than x
 *---------------------------------------------------------------------------*/
#define MATH_ROUNDDOWN(x, base) ((x) & ~((base)-1))

/*---------------------------------------------------------------------------*
  Name:         MATH_ROUNDUP32

  Description:  Macro that returns the value rounded-up to a multiple of 32.
  
  Arguments:    x

  Returns:      Smallest multiple of 32 that is greater or equal to x
 *---------------------------------------------------------------------------*/
#define MATH_ROUNDUP32(x) MATH_ROUNDUP(x, 32)

/*---------------------------------------------------------------------------*
  Name:         MATH_ROUNDDOWN32

  Description:  Macro that returns the value rounded-down to a multiple of 32.
  
  Arguments:    x

  Returns:      Largest multiple of 32 that is equal or less than x
 *---------------------------------------------------------------------------*/
#define MATH_ROUNDDOWN32(x) MATH_ROUNDDOWN(x, 32)

/*---------------------------------------------------------------------------*
  Name:         MATH_CountLeadingZeros

  Description:  Determines how many bits from the top have the value 0 expressed in binary 32bit.
                In the ARM9 ARM code, this is 1 command.

  Arguments:    x

  Returns:      The number of contiguous bit 0 from the top
 *---------------------------------------------------------------------------*/
u32     MATH_CountLeadingZerosFunc(u32 x);

#if !defined(PLATFORM_INTRINSIC_FUNCTION_BIT_CLZ32)

/* clz is available ARM mode only */
#ifdef  SDK_ARM9
#if     defined(SDK_CW) || defined(__MWERKS__)
#pragma thumb off
SDK_INLINE u32 MATH_CountLeadingZerosInline(u32 x)
{
	asm("clz x, x");
    return  x;
}

#pragma thumb reset
#elif   defined(SDK_ADS)
TO BE   DEFINED
#elif   defined(SDK_GCC)
TO BE   DEFINED
#endif
#endif
#endif /* PLATFORM_INTRINSIC_FUNCTION_BIT_CLZ32 */

#ifndef MATH_CountLeadingZeros
#if       defined(PLATFORM_INTRINSIC_FUNCTION_BIT_CLZ32)
#define MATH_CountLeadingZeros(x) PLATFORM_INTRINSIC_FUNCTION_BIT_CLZ32(x)
#elif     defined(SDK_ARM9) && defined(SDK_CODE_ARM)
#define MATH_CountLeadingZeros(x) MATH_CountLeadingZerosInline(x)
#else                                  // not (ARM9 && CODE_ARM)
#define MATH_CountLeadingZeros(x) MATH_CountLeadingZerosFunc(x)
#endif                                 // ARM9 && CODE_ARM
#endif

/*---------------------------------------------------------------------------*
  Name:         MATH_CLZ

  Description:  This is MATH_CountLeadingZeros under a different name
                Determines how many bits from the top have the value 0 expressed in binary 32bit.
                In the ARM9 ARM code, this is 1 command.

  Arguments:    x

  Returns:      The number of contiguous bit 0 from the top
 *---------------------------------------------------------------------------*/
#define MATH_CLZ(x) MATH_CountLeadingZeros(x)
/*---------------------------------------------------------------------------*
  Name:         MATH_ILog2

  Description:  Looks for the interger portion of the base-2 logarithm log2(x) in the u32 argument x.
                In the special case where x = 0, the function returns -1.
                In the ARM9 ARM code, CLZ command is used for 2 commands.

  Arguments:    x - u32

  Returns:      log2(x) when x > 0, or -1 when x == 0
 *---------------------------------------------------------------------------*/
        SDK_INLINE int MATH_ILog2(u32 x)
{
    return (int)(31 - MATH_CountLeadingZeros(x));
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CountPopulation

  Description:  Determines the number of bit 1 expressed in binary 32bit.

  Arguments:    x

  Returns:      The number of bit 1 in binary format
 *---------------------------------------------------------------------------*/
u8      MATH_CountPopulation(u32 x);


/*---------------------------------------------------------------------------*
  Name:         MATH_CountTrailingZeros

  Description:  Determines how many bits from the bottom have the value 0 expressed in binary 32bit.
                Uses the MATH_CountLeadingZeros function.

  Arguments:    x             u32 value used in determining

  Returns:      The number of contiguous 0 bits from the lower bit
 *---------------------------------------------------------------------------*/
SDK_INLINE u32 MATH_CountTrailingZeros(u32 x)
{
    return (u32)(32 - MATH_CountLeadingZeros((u32)(~x & (x - 1))));
}

/*---------------------------------------------------------------------------*
  Name:         MATH_CTZ

  Description:  This is MATH_CountTrailingZeros under a different name
                Determines how many bits from the bottom have the value 0 expressed in binary 32bit.
                Uses the MATH_CountLeadingZeros function.

  Arguments:    x             u32 value used in determining

  Returns:      The number of contiguous 0 bits from the lower bit
 *---------------------------------------------------------------------------*/
#define MATH_CTZ(x) MATH_CountTrailingZeros(x)

/*---------------------------------------------------------------------------*
  Name:         MATH_GetLeastSignificantBit

  Description:  Determines the lowest 1 bit expressed in binary 32bit.

  Arguments:    x             u32 value used in determining

  Returns:      u32 value to express the bottom 1 bit.
 *---------------------------------------------------------------------------*/
SDK_INLINE u32 MATH_GetLeastSignificantBit(u32 x)
{
    return (u32)(x & -(s32)x);
}

/*---------------------------------------------------------------------------*
  Name:         MATH_LSB

  Description:  Another name for MATH_GetLeastSignificant
                Determines the lowest 1 bit expressed in binary 32bit.

  Arguments:    x             u32 value used in determining

  Returns:      u32 value to express the bottom 1 bit.
 *---------------------------------------------------------------------------*/
#define MATH_LSB(x) MATH_GetLeastSignificantBit(x)

/*---------------------------------------------------------------------------*
  Name:         MATH_GetMostSignificantBit

  Description:  Determines the highest 1 bit expressed in binary 32bit.

  Arguments:    x             u32 value used in determining

  Returns:      u32 value to express the top 1 bit.
 *---------------------------------------------------------------------------*/
SDK_INLINE u32 MATH_GetMostSignificantBit(u32 x)
{
    return (u32)(x & ((s32)0x80000000 >> MATH_CountLeadingZeros(x)));
}

/*---------------------------------------------------------------------------*
  Name:         MATH_MSB

  Description:  Another name for MATH_GetMostSignificant
                Determines the highest 1 bit expressed in binary 32bit.

  Arguments:    x             u32 value used in determining

  Returns:      u32 value to express the top 1 bit.
 *---------------------------------------------------------------------------*/
#define MATH_MSB(x) MATH_GetMostSignificantBit(x)


#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_MATH_MATH_H_ */
#endif
