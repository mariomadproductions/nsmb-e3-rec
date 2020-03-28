/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     version_end.h

  Copyright 2005-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: version_end.h,v $
  Revision 1.2  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.1  2005/04/08 09:32:32  yosizaki
  initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
//
// include this instead of using C99 pragma extensions for compatibility
//
#if	defined(SDK_CW) || defined(__MWERKS__)
#pragma section VERSION end
#elif	defined(SDK_ADS)
TO BE   DEFINED
#elif	defined(SDK_GCC)
TO BE   DEFINED
#endif
