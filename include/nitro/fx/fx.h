/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FX -
  File:     fx.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fx.h,v $
  Revision 1.45  2006/04/28 07:29:19  okubata_ryoma
  Added FX32_CAST

  Revision 1.44  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.43  2005/11/14 05:10:03  okubata_ryoma
  Added support for SDK_INLINE

  Revision 1.42  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.41  2005/09/08 11:33:00  yasu
  Moved processing for structures without member names in VC.net to nitro_win32.h.

  Revision 1.40  2005/09/08 11:28:06  yasu
  Revised _MSC_VER definition check

  Revision 1.39  2005/09/08 11:15:25  yasu
  Support for structures without member names in VC.net

  Revision 1.38  2005/09/05 09:57:13  takano_makoto
  Corrected FX_FX64C_TO_F32 macro

  Revision 1.37  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.36  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.35  2004/09/13 06:53:37  yasu
  SDK_ARM -> SDK_CODE_ARM

  Revision 1.34  2004/06/14 04:07:48  takano_makoto
  Added FX16_CONST, FX64_CONST and FX64C_CONST. Corrected FX_F32_TO_FX32.

  Revision 1.33  2004/05/25 00:19:47  yasu
  add FX32_CONST(x)

  Revision 1.32  2004/05/14 11:59:00  takano_makoto
  Add #ifndef SDK_FROM_TOOL for VC or BCB.

  Revision 1.31  2004/03/23 05:17:38  takano_makoto
  At FX_MUL, FX_MUL32x64C and FX_Mul32x64c, change to return round decimal.

  Revision 1.30  2004/02/25 06:24:27  nishida_kenji
  FX_Mul and FX_Mul32x64c become macros.

  Revision 1.29  2004/02/16 02:35:18  nishida_kenji
  Add VecFx16.

  Revision 1.28  2004/02/13 00:54:23  nishida_kenji
  Add FX_Modf.

  Revision 1.27  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.26  2004/02/04 11:49:33  nishida_kenji
  small fix.

  Revision 1.25  2004/01/27 11:15:10  nishida_kenji
  appends 'static' to inline function prototypes.

  Revision 1.24  2004/01/26 07:15:14  nishida_kenji
  revise FX_Mul and FX_Mul32x64c for thumb

  Revision 1.23  2004/01/18 04:37:11  nishida_kenji
  removes FX_Dot2, FX_Dot3, FX_Dot4

  Revision 1.22  2004/01/17 13:22:56  nishida_kenji
  small bug fix

  Revision 1.21  2004/01/17 08:32:01  nishida_kenji
  improve precision of FX_Mul32x64c

  Revision 1.20  2004/01/17 07:17:25  nishida_kenji
  remove external include guards

  Revision 1.19  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.18  2004/01/16 11:25:53  nishida_kenji
  small fix

  Revision 1.17  2004/01/16 10:38:39  nishida_kenji
  add FX_Init for table setup

  Revision 1.16  2004/01/05 06:29:03  nishida_kenji
  add FX_Whole, FX_Floor

  Revision 1.15  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.14  2003/12/18 00:08:55  nishida_kenji
  removed VecFx16

  Revision 1.13  2003/12/11 09:18:28  nishida_kenji
  fix comments

  Revision 1.12  2003/12/11 06:17:47  nishida_kenji
  add FX_Dot4 and comments

  Revision 1.11  2003/12/09 11:27:02  nishida_kenji
  improve asserts and comments

  Revision 1.10  2003/12/04 07:31:50  nishida_kenji
  MTX_Inverse33, MTX_Inverse43

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_FX_H_
#define NITRO_FX_H_

#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#include "nitro/misc.h"
#endif

#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//#define SDK_FX_DYNAMIC_TABLE

//----------------------------------------------------------------------------
//    fx32: s19.12 fixed point number
//----------------------------------------------------------------------------
typedef s32 fx32;
#define FX32_SHIFT          12
#define FX32_INT_SIZE       19
#define FX32_DEC_SIZE       12

#define FX32_INT_MASK       0x7ffff000
#define FX32_DEC_MASK       0x00000fff
#define FX32_SIGN_MASK      0x80000000

#define FX32_MAX            ((fx32)0x7fffffff)
#define FX32_MIN            ((fx32)0x80000000)

#define FX_MUL(v1, v2)       FX32_CAST(((fx64)(v1) * (v2) + 0x800LL) >> FX32_SHIFT)
#define FX_MUL32x64C(v1, v2) FX32_CAST(((v2) * (v1) + 0x80000000LL) >> 32)

#define FX_FX32_TO_F32(x)    ((f32)((x) / (f32)(1 << FX32_SHIFT)))
#define FX_F32_TO_FX32(x)    ((fx32)(((x) > 0) ? \
                                     ((x) * (1 << FX32_SHIFT) + 0.5f ) : \
                                     ((x) * (1 << FX32_SHIFT) - 0.5f )))

#define FX32_CONST(x)        FX_F32_TO_FX32(x)


//----------------------------------------------------------------------------
//  fx64: s51.12 fixed point number
//----------------------------------------------------------------------------
typedef s64 fx64;
#define FX64_SHIFT          12
#define FX64_INT_SIZE       51
#define FX64_DEC_SIZE       12

#define FX64_INT_MASK       ((fx64)0x7ffffffffffff000)
#define FX64_DEC_MASK       ((fx64)0x0000000000000fff)
#define FX64_SIGN_MASK      ((fx64)0x8000000000000000)

#define FX64_MAX            ((fx64)0x7fffffffffffffff)
#define FX64_MIN            ((fx64)0x8000000000000000)

#define FX_FX64_TO_F32(x)   ((f32)((x) / (f32)(1 << FX64_SHIFT)))
#define FX_F32_TO_FX64(x)   ((fx64)(((x) > 0) ? \
                                    ((x) * (1 << FX32_SHIFT) + 0.5f ) : \
                                    ((x) * (1 << FX32_SHIFT) - 0.5f )))

#define FX64_CONST(x)       FX_F32_TO_FX64(x)


//----------------------------------------------------------------------------
//  fx64c: s31.32 fixed point number
//----------------------------------------------------------------------------
typedef s64 fx64c;
#define FX64C_SHIFT          32
#define FX64C_INT_SIZE       31
#define FX64C_DEC_SIZE       32

#define FX64C_INT_MASK       ((fx64c)0x7fffffff00000000)
#define FX64C_DEC_MASK       ((fx64c)0x00000000ffffffff)
#define FX64C_SIGN_MASK      ((fx64c)0x8000000000000000)

#define FX64C_MAX            ((fx64c)0x7fffffffffffffff)
#define FX64C_MIN            ((fx64c)0x8000000000000000)

#define FX_FX64C_TO_F32(x)   ((f32)((x) / (f32)((fx64c)1 << FX64C_SHIFT)))
#define FX_F32_TO_FX64C(x)   ((fx64c)(((x) > 0) ? \
                                      ((x) * ((fx64c)1 << FX64C_SHIFT) + 0.5f ) : \
                                      ((x) * ((fx64c)1 << FX64C_SHIFT) - 0.5f )))

#define FX64C_CONST(x)      FX_F32_TO_FX64C(x)

// 4294967296 = 2^32

//----------------------------------------------------------------------------
//  fx16: s3.12 fixed point number
//----------------------------------------------------------------------------
typedef s16 fx16;
#define FX16_SHIFT          12
#define FX16_INT_SIZE       3
#define FX16_DEC_SIZE       12

#define FX16_INT_MASK       0x7000
#define FX16_DEC_MASK       0x0fff
#define FX16_SIGN_MASK      0x8000

/* 7.999759  */
#define FX16_MAX            ((fx16)0x7fff)
/* -8        */
#define FX16_MIN            ((fx16)0x8000)

#define FX_FX16_TO_F32(x)    ((f32)((x) / (f32)(1 << FX16_SHIFT)))
#define FX_F32_TO_FX16(x)    ((fx16)(((x) > 0) ? \
                                     (fx16)((x) * (1 << FX16_SHIFT) + 0.5f ) : \
                                     (fx16)((x) * (1 << FX16_SHIFT) - 0.5f )))

#define FX16_CONST(x)       FX_F32_TO_FX16(x)

//----------------------------------------------------------------------------
//  VecFx32: 3D Vector of fx32
//----------------------------------------------------------------------------
typedef struct
{
    fx32    x;
    fx32    y;
    fx32    z;
}
VecFx32;

//----------------------------------------------------------------------------
//  VecFx16: 3D Vector of fx16
//----------------------------------------------------------------------------
typedef struct
{
    fx16    x;
    fx16    y;
    fx16    z;
}
VecFx16;


//----------------------------------------------------------------------------
//  MtxFx44: 4x4 Matrix of fx32
//----------------------------------------------------------------------------
#ifdef SDK_ADS
typedef struct
{
    fx32    _00, _01, _02, _03;
    fx32    _10, _11, _12, _13;
    fx32    _20, _21, _22, _23;
    fx32    _30, _31, _32, _33;
}
MtxFx44;
#else
typedef union
{
    struct
    {
        fx32    _00, _01, _02, _03;
        fx32    _10, _11, _12, _13;
        fx32    _20, _21, _22, _23;
        fx32    _30, _31, _32, _33;
    };
    fx32    m[4][4];
    fx32    a[16];
}
MtxFx44;
#endif

//----------------------------------------------------------------------------
//  MtxFx43: 4x3 Matrix of fx32
//----------------------------------------------------------------------------
#ifdef SDK_ADS
typedef struct
{
    fx32    _00, _01, _02;
    fx32    _10, _11, _12;
    fx32    _20, _21, _22;
    fx32    _30, _31, _32;
}
MtxFx43;
#else
typedef union
{
    struct
    {
        fx32    _00, _01, _02;
        fx32    _10, _11, _12;
        fx32    _20, _21, _22;
        fx32    _30, _31, _32;
    };
    fx32    m[4][3];
    fx32    a[12];
}
MtxFx43;
#endif

//----------------------------------------------------------------------------
//  MtxFx33: 3x3 Matrix of fx32
//----------------------------------------------------------------------------
#ifdef SDK_ADS
typedef struct
{
    fx32    _00, _01, _02;
    fx32    _10, _11, _12;
    fx32    _20, _21, _22;
}
MtxFx33;
#else
typedef union
{
    struct
    {
        fx32    _00, _01, _02;
        fx32    _10, _11, _12;
        fx32    _20, _21, _22;
    };
    fx32    m[3][3];
    fx32    a[9];
}
MtxFx33;
#endif

//----------------------------------------------------------------------------
//  MtxFx22: 2x2 Matrix of fx32
//----------------------------------------------------------------------------
#ifdef SDK_ADS
typedef struct
{
    fx32    _00, _01;
    fx32    _10, _11;
}
MtxFx22;
#else
typedef union
{
    struct
    {
        fx32    _00, _01;
        fx32    _10, _11;
    };
    fx32    m[2][2];
    fx32    a[4];
}
MtxFx22;
#endif

/* if include from Other Environment for example VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

void    FX_Init(void);

SDK_DECL_INLINE s32 FX_Whole(fx32 v);
SDK_DECL_INLINE fx32 FX_Floor(fx32 v);

fx32    FX_Modf(fx32 x, fx32 *iPtr);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         FX_Whole

  Description:  Convert fx32 number to a whole number(s32)

  Arguments:    v        fx32 variable/constant

  Returns:      floor of v in s32(integer)
 *---------------------------------------------------------------------------*/
SDK_INLINE s32 FX_Whole(fx32 v)
{
    return (s32)(v >> FX32_SHIFT);
}

/*---------------------------------------------------------------------------*
  Name:         FX_Floor

  Description:  Convert fx32 number to a whole number(fx32)

  Arguments:    v        fx32 variable/constant

  Returns:      floor of v in fx32 format
 *---------------------------------------------------------------------------*/
SDK_INLINE fx32 FX_Floor(fx32 v)
{
    return (fx32)(v & (FX32_INT_MASK | FX32_SIGN_MASK));
}

/*---------------------------------------------------------------------------*
  Name:         FX32_CAST

  Description:  Overflow/Underflow check

  Arguments:    res      s64  variable/constant

  Returns:      cast fx32
 *---------------------------------------------------------------------------*/
SDK_INLINE fx32 FX32_CAST(s64 res)
{
    SDK_WARNING(res >= FX32_MIN && res <= FX32_MAX, "FX_Mul: Overflow/Underflow");
    return (fx32)res;
}

/*---------------------------------------------------------------------------*
  Name:         FX_Mul

  Description:  Multiply fx32 and fx32

  Arguments:    v1       fx32 variable/constant to multiply
                v2       fx32 variable/constant to multiply

  Returns:      v1 * v2 in fx32 format
 *---------------------------------------------------------------------------*/
fx32    FX_MulFunc(fx32 v1, fx32 v2);
SDK_DECL_INLINE fx32 FX_MulInline(fx32 v1, fx32 v2);

SDK_INLINE fx32 FX_MulInline(fx32 v1, fx32 v2)
{
    return FX32_CAST(((s64)(v1) * v2 + 0x800LL) >> FX32_SHIFT);
}

#ifndef FX_Mul
#ifdef  SDK_CODE_ARM
#define FX_Mul(v1, v2) FX_MulInline(v1, v2)
#else
#define FX_Mul(v1, v2) FX_MulFunc(v1, v2)
#endif
#endif

#ifndef FX_Mul32x64c
#ifdef  SDK_CODE_ARM
#define FX_Mul32x64c(v32, v64c) FX_Mul32x64cInline(v32, v64c)
#else
#define FX_Mul32x64c(v32, v64c) FX_Mul32x64cFunc(v32, v64c)
#endif
#endif


/*---------------------------------------------------------------------------*
  Name:         FX_Mul32x64c

  Description:  Multiply fx32 and fx64c

  Arguments:    v1       fx32 variable/constant to multiply
                v2       fx64c variable/constant to multiply

  Returns:      v1 * v2 in fx32 format
 *---------------------------------------------------------------------------*/
fx32    FX_Mul32x64cFunc(fx32 v32, fx64c v64c);
SDK_DECL_INLINE fx32 FX_Mul32x64cInline(fx32 v32, fx64c v64c);

SDK_INLINE fx32 FX_Mul32x64cInline(fx32 v32, fx64c v64c)
{
    fx64c   tmp = v64c * v32 + 0x80000000LL;    // for better precision
    return FX32_CAST(tmp >> FX64C_SHIFT);
}


#endif // SDK_FROM_TOOL

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
