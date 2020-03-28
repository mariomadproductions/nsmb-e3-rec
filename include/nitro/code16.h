/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     code16.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: code16.h,v $
  Revision 1.7  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.6  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.5  2005/01/21 09:54:31  yasu
  Copyright year 2004->2005

  Revision 1.4  2005/01/21 07:34:19  yasu
  merge with RC4branch

  Revision 1.3.38.1  2005/01/21 05:59:43  yasu
  Fix a bug "MATH_CountLeadingZeros() not inlined"

  Revision 1.3  2004/02/25 06:25:03  nishida_kenji
  Switches FX_Mul/FX_Mul32x64c implementation.

  Revision 1.2  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.1  2003/12/16 10:56:00  yasu
  Initial version.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#if	defined(SDK_CW) || defined(__MWERKS__)
#pragma thumb on
#elif	defined(SDK_ADS)
TO BE   DEFINED
#elif	defined(SDK_GCC)
TO BE   DEFINED
#endif
// Prepare to switch the definition of FX_Mul
#ifdef FX_Mul
#undef FX_Mul
#endif
// Prepare to switch the definition of FX_MulFx64c
#ifdef FX_Mul32x64c
#undef FX_Mul32x64c
#endif
// Prepare to switch the definition of MATH_CountLeadingZeros
#ifdef MATH_CountLeadingZeros
#undef MATH_CountLeadingZeros
#endif
// Because CPU is in ARM mode, function versions are used.
#define FX_Mul(v1, v2)                 FX_MulFunc(v1, v2)
#define FX_Mul32x64c(v32, v64c)        FX_Mul32x64cFunc(v32, v64c)
#define MATH_CountLeadingZeros(x)      MATH_CountLeadingZerosFunc(x)
