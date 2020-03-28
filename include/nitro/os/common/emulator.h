/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     emulator.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: emulator.h,v $
  Revision 1.8  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.7  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.6  2004/06/29 04:33:27  yada
  add OS_CONSOLE_NITRO

  Revision 1.5  2004/06/08 09:58:30  yada
  add main memory size define

  Revision 1.4  2004/06/07 04:29:39  yada
  add OS_GetConsoleType()

  Revision 1.3  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.2  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.1  2003/11/25 11:19:32  yasu
  Added emulator.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_EMULATOR_H_
#define NITRO_OS_EMULATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

//---- value of 'console not yet detect'
#define OSi_CONSOLE_NOT_DETECT    0xffffffff

//---- running program environment
#define OS_CONSOLE_MASK           0xf0000000
#define OS_CONSOLE_ENSATA         0x10000000
#define OS_CONSOLE_ISEMULATOR     0x20000000
#define OS_CONSOLE_ISDEBUGGER     0x40000000
#define OS_CONSOLE_NITRO          0x80000000

//---- device
#define OS_CONSOLE_DEV_MASK       0x03000000
#define OS_CONSOLE_DEV_CARTRIDGE  0x01000000
#define OS_CONSOLE_DEV_CARD       0x02000000

//---- main memory size
#define OS_CONSOLE_SIZE_MASK      0x00000003
#define OS_CONSOLE_SIZE_4MB       0x00000001
#define OS_CONSOLE_SIZE_8MB       0x00000002


/*---------------------------------------------------------------------------*
  Name:         OS_IsRunOnEmulator

  Description:  Detect emulator

  Arguments:    None

  Returns:      non 0 if emulator
 *---------------------------------------------------------------------------*/
BOOL    OS_IsRunOnEmulator(void);


/*---------------------------------------------------------------------------*
  Name:         OS_GetConsoleType

  Description:  Detect console type

  Arguments:    None

  Returns:      
 *---------------------------------------------------------------------------*/
u32     OS_GetConsoleType(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_EMULATOR_H_ */
#endif
