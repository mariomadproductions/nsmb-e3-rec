/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     codereset.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: codereset.h,v $
  Revision 1.4  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.3  2004/03/18 12:43:52  yasu
  SDK_ARM -> SDK_CODE_ARM

  Revision 1.2  2004/02/25 09:15:54  yasu
  don't use pragma when reseting thumb mode

  Revision 1.1  2004/02/09 06:39:52  yasu
  reset arm/thumb instruction mode

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifdef	SDK_CODE_ARM                   // switch by default codegen
#include "nitro/code32.h"
#else  //SDK_CODE_THUMB
#include "nitro/code16.h"
#endif
