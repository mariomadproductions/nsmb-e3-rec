/*---------------------------------------------------------------------------*
  Project:  NitroSDK - init - include
  File:     crt0.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: crt0.h,v $
  Revision 1.8  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.7  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.6  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.5  2004/02/18 02:38:06  yada
  Added StartUp function definition

  Revision 1.4  2004/02/14 10:14:10  yasu
  aliased NitroMain -> NitroSpMain when ARM7

  Revision 1.3  2004/02/13 08:17:52  yasu
  support ARM7

  Revision 1.2  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.1  2003/11/12 12:24:00  yasu
  Released crt0.o from base library

  Revision 1.1  2003/11/10 09:03:04  yada
  Configured void IrisMain(void)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_INIT_CRT0_H_
#define NITRO_INIT_CRT0_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	SDK_ARM9
void    NitroMain(void);
void    NitroStartUp(void);
#else
void    NitroSpMain(void);
void    NitroSpStartUp(void);
#define NitroMain(x)  NitroSpMain(x)
#define NitroStartUp(x)  NitroSpStartUp(x)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_INIT_CRT0_H_ */
#endif
