/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     sinit.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: sinit.h,v $
  Revision 1.5  2006/03/17 00:33:27  yosizaki
  support SDK_FORCE_EXPORT

  Revision 1.4  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.3  2005/10/19 07:48:57  okubata_ryoma
  Corrected method of coding parameters for #pragma difine_section.

  Revision 1.2  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.1  2004/09/24 13:24:04  yasu
  Support NitroStaticInit

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#if	defined(SDK_CW) || defined(__MWERKS__)
//
// Setup NitroStaticInit
//
static void NitroStaticInit(void);
#pragma define_section SINIT ".sinit" abs32 RWX
#pragma section        SINIT begin
SDK_FORCE_EXPORT static void *NitroStaticInit_[] = { NitroStaticInit };
#pragma section        SINIT end

#elif	defined(SDK_ADS)

TO BE   DEFINED
#elif	defined(SDK_GCC)

TO BE   DEFINED
#endif
