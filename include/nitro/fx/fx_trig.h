/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FX -
  File:     fx_trig.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fx_trig.h,v $
  Revision 1.23  2007/01/18 04:08:37  okubata_ryoma
  Added FX_AsinIdx and FX_AcosIdx functions

  Revision 1.22  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.21  2005/11/14 05:10:03  okubata_ryoma
  Added support for SDK_INLINE

  Revision 1.20  2005/03/03 13:11:32  takano_makoto
  Revised variable declarations that were missing extern

  Revision 1.19  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.18  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.17  2004/06/16 11:23:42  seiki_masashi
  FX_AtanIdx, FX_Atan2Idx

  Revision 1.16  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.15  2004/02/04 11:49:33  nishida_kenji
  small fix.

  Revision 1.14  2004/01/27 11:15:10  nishida_kenji
  appends 'static' to inline function prototypes.

  Revision 1.13  2004/01/17 09:32:31  nishida_kenji
  FX_SinIdx and FX_CosIdx take int.

  Revision 1.12  2004/01/17 07:17:21  nishida_kenji
  remove external include guards

  Revision 1.11  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.10  2004/01/16 11:25:53  nishida_kenji
  small fix

  Revision 1.9  2004/01/16 10:38:31  nishida_kenji
  add FX_Init for table setup

  Revision 1.8  2003/12/25 00:27:13  nishida_kenji
  remove needless APIs

  Revision 1.7  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.6  2003/12/18 11:36:17  nishida_kenji
  bug fix on SinIdx and CosIdx

  Revision 1.5  2003/12/11 12:07:33  nishida_kenji
  improve FX_xxx_TO_yyy's precision

  Revision 1.4  2003/12/11 09:18:24  nishida_kenji
  fix comments

  Revision 1.3  2003/12/11 01:17:46  nishida_kenji
  add macros and comments

  Revision 1.2  2003/12/10 05:37:47  nishida_kenji
  FX_Atan, FX_Atan2

  Revision 1.1  2003/12/10 00:14:03  nishida_kenji
  new

  $NoKeywords: $
 *---------------------------------------------------------------------------*/


#ifndef NITRO_FXTRIG_H_
#define NITRO_FXTRIG_H_

#include "nitro/fx/fx.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------
#ifdef SDK_FX_DYNAMIC_TABLE
extern fx16 FX_SinCosTable_[];
#else
extern const fx16 FX_SinCosTable_[];
#endif

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

// deg must be in fx32/fx16 format
#define FX_DEG_TO_RAD(deg)            ((fx32)((FX64C_TWOPI_360 * (deg) + 0x80000000LL) >> 32))
#define FX_DEG_TO_IDX(deg)            ((u16) ((FX64C_65536_360 * (deg) + 0x80000000000LL) >> 44))

// rad must be in fx32/fx16 format
#define FX_RAD_TO_DEG(rad)            ((fx32)((FX64C_360_TWOPI * (rad) + 0x80000000LL) >> 32))
#define FX_RAD_TO_IDX(rad)            ((u16)((FX64C_65536_TWOPI * (rad) + 0x80000000000LL) >> 44))

#define FX_IDX_TO_RAD(idx)            ((fx32)((FX64C_TWOPI_65536 * (idx) + 0x80000LL) >> 20))
#define FX_IDX_TO_DEG(idx)            ((fx32)((FX64C_360_65536 * (idx) + 0x80000LL) >> 20))

SDK_DECL_INLINE fx16 FX_SinIdx(int idx);
SDK_DECL_INLINE fx16 FX_CosIdx(int idx);

u16     FX_AtanIdx(fx32 x);
u16     FX_Atan2Idx(fx32 y, fx32 x);

fx16    FX_Atan(fx32 x);
fx16    FX_Atan2(fx32 y, fx32 x);

u16     FX_AsinIdx(fx32 x);
u16     FX_AcosIdx(fx32 x);

fx64c   FX_SinFx64c(fx32 rad);
fx64c   FX_CosFx64c(fx32 rad);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         FX_SinIdx

  Description:  Obtain approximation of sine by table reference

  Arguments:    idx        treat (2 * pi / 65536) as 1

  Returns:      approximated sine value in fx16 format
 *---------------------------------------------------------------------------*/
SDK_INLINE fx16 FX_SinIdx(int idx)
{
    SDK_MINMAX_ASSERT(idx, 0, 65535);

    return FX_SinCosTable_[((idx >> 4) << 1)];
}

/*---------------------------------------------------------------------------*
  Name:         FX_CosIdx

  Description:  Obtain approximation of cosine by table reference

  Arguments:    idx        treat (2 * pi / 65536) as 1

  Returns:      approximated cosine value in fx16 format
 *---------------------------------------------------------------------------*/
SDK_INLINE fx16 FX_CosIdx(int idx)
{
    SDK_MINMAX_ASSERT(idx, 0, 65535);

    return FX_SinCosTable_[((idx >> 4) << 1) + 1];
}

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
