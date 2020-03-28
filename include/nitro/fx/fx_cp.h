/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FX -
  File:     fx_cp.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fx_cp.h,v $
  Revision 1.25  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.24  2005/11/14 05:10:03  okubata_ryoma
  Added support for SDK_INLINE

  Revision 1.23  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.22  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.21  2004/11/02 17:54:17  takano_makoto
  fix comments.

  Revision 1.20  2004/02/16 02:24:12  nishida_kenji
  small fix.

  Revision 1.19  2004/02/13 08:45:24  nishida_kenji
  Inline FX_Mod.

  Revision 1.18  2004/02/13 03:50:24  nishida_kenji
  small fix

  Revision 1.17  2004/02/13 00:55:07  nishida_kenji
  Add FX_Mod, FX_DivS32, FX_ModS32, etc.

  Revision 1.16  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.15  2004/01/27 11:15:10  nishida_kenji
  appends 'static' to inline function prototypes.

  Revision 1.14  2004/01/18 04:38:08  nishida_kenji
  revises the interfaces for asynchronous calculation

  Revision 1.13  2004/01/17 13:23:26  nishida_kenji
  add FX_InvSqrt

  Revision 1.12  2004/01/17 07:17:21  nishida_kenji
  remove external include guards

  Revision 1.11  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.10  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.9  2003/12/12 05:07:43  nishida_kenji
  some functions moved too .c file

  Revision 1.8  2003/12/11 09:18:24  nishida_kenji
  fix comments

  Revision 1.7  2003/12/11 07:26:41  nishida_kenji
  add comments

  Revision 1.6  2003/12/09 11:26:58  nishida_kenji
  improve asserts and comments

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_FX_CP_H_
#define NITRO_FX_CP_H_

#include "nitro/fx/fx.h"
#include "nitro/fx/fx_const.h"
#include "nitro/cp/divider.h"
#include "nitro/cp/sqrt.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

fx32    FX_Div(fx32 numer, fx32 denom);
fx64c   FX_DivFx64c(fx32 numer, fx32 denom);
SDK_DECL_INLINE fx32 FX_Mod(fx32 numer, fx32 denom);
fx32    FX_Sqrt(fx32 x);
fx32    FX_Inv(fx32 denom);
fx64c   FX_InvFx64c(fx32 denom);
fx32    FX_InvSqrt(fx32 x);

void    FX_DivAsync(fx32 numer, fx32 denom);
SDK_DECL_INLINE void FX_DivAsyncImm(fx32 numer, fx32 denom);
fx64c   FX_GetDivResultFx64c(void);
fx32    FX_GetDivResult(void);
fx64c   FX_GetDivRemainderFx64c(void);
fx32    FX_GetDivRemainder(void);

void    FX_InvAsync(fx32 denom);
SDK_DECL_INLINE void FX_InvAsyncImm(fx32 denom);
SDK_DECL_INLINE fx64c FX_GetInvResultFx64c(void);
SDK_DECL_INLINE fx32 FX_GetInvResult(void);

void    FX_SqrtAsync(fx32 x);
void    FX_SqrtAsyncImm(fx32 x);
fx32    FX_GetSqrtResult(void);

s32     FX_DivS32(s32 a, s32 b);
s32     FX_ModS32(s32 a, s32 b);

#define FX_DIVISION_BY_ZERO(a, b) \
    SDK_WARNING(b != 0, "Division by zero(%d / %d)", a, b)

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

// Inv
/*---------------------------------------------------------------------------*
  Name:         FX_InvAsyncImm

  Description:  Just the same as FX_DivAsyncImm(FX32_ONE, denom).
                This function sets numer and denom onto the divider.
                It assumes that the divider is in DIVMODE 01(64/32).

  Arguments:    denom     in fx32 format

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void FX_InvAsyncImm(fx32 denom)
{
    SDK_ASSERT(!CP_IsDivBusy());
    FX_DIVISION_BY_ZERO(FX32_ONE, denom);

    CP_SetDivImm64_32((u64)FX32_ONE << 32, (u32)denom);
}


/*---------------------------------------------------------------------------*
  Name:         FX_GetInvResultFx64c

  Description:  Just the same as FX_GetDivResultFx64c().

  Arguments:    none

  Returns:      a reciprocal in fx64c format
 *---------------------------------------------------------------------------*/
SDK_INLINE fx64c FX_GetInvResultFx64c(void)
{
    return FX_GetDivResultFx64c();
}

/*---------------------------------------------------------------------------*
  Name:         FX_GetInvResult

  Description:  Just the same as FX_GetDivResult().

  Arguments:    none

  Returns:      a reciprocal in fx32 format
 *---------------------------------------------------------------------------*/
SDK_INLINE fx32 FX_GetInvResult(void)
{
    return FX_GetDivResult();
}

/*---------------------------------------------------------------------------*
  Name:         FX_DivAsyncImm

  Description:  Use a divider asynchronously.
                This function sets numer and denom onto the divider.
                It assumes that the divider is in DIVMODE 01(64/32).

  Arguments:    numer     in fx32 format
                denom     in fx32 format

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void FX_DivAsyncImm(fx32 numer, fx32 denom)
{
    SDK_ASSERT(!CP_IsDivBusy());
    FX_DIVISION_BY_ZERO(numer, denom);

    CP_SetDivImm64_32((u64)numer << 32, (u32)denom);
}

/*---------------------------------------------------------------------------*
  Name:         FX_Mod

  Description:  Divides 'numer' by 'denom', and returns the remainder in fx32
                format. This uses the divider.

  Arguments:    numer        a value in fx32 format
                denom        a value in fx32 format

  Returns:      result in fx32 format
 *---------------------------------------------------------------------------*/
SDK_INLINE fx32 FX_Mod(fx32 numer, fx32 denom)
{
    return (fx32)FX_ModS32(numer, denom);
}

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
