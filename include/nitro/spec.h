/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     spec.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: spec.h,v $
  Revision 1.5  2005/05/26 02:51:08  terui
  Changed default value of SDK_TS_VERSION 200

  Revision 1.4  2005/04/12 11:35:47  terui
  Changed SDK_NVRAM_FORMAT constant to 300

  Revision 1.3  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.2  2004/09/13 05:49:56  yasu
  merged with NitroSDK_2_00pr6_branch

  Revision 1.1.6.1  2004/09/13 05:43:02  yasu
  Support SDK_NVRAM_FORMAT

  Revision 1.1  2004/08/09 11:29:54  yasu
  Add spec.h to switch platform settings

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef	NITRO_SPEC_H_
#  define NITRO_SPEC_H_

// --- NITRO_TS_VERSION = [0/100/200]
//
//      0 : Prototype breadboard ~ ISD-BOX Ver.C
//    100 : ISD-BOX Ver.D
//    200 : ISD-BOX Ver.E

#  ifdef  SDK_TS
#    ifndef SDK_TS_VERSION
#      define SDK_TS_VERSION	200
#    endif
#    ifndef SDK_NVRAM_FORMAT
#      define SDK_NVRAM_FORMAT	300
#    endif
#  endif

#endif
