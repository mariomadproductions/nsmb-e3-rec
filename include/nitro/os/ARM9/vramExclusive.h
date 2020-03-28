/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     vramExclusive.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: vramExclusive.h,v $
  Revision 1.3  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.2  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.1  2005/02/08 08:39:49  terui
  Initial release.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_OS_ARM9_VRAMEXCLUSIVE_H_
#define NITRO_OS_ARM9_VRAMEXCLUSIVE_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include "nitro/types.h"


/*---------------------------------------------------------------------------*
    constant definitions
 *---------------------------------------------------------------------------*/
#define		OS_VRAM_BANK_ID_A		0x0001
#define		OS_VRAM_BANK_ID_B		0x0002
#define		OS_VRAM_BANK_ID_C		0x0004
#define		OS_VRAM_BANK_ID_D		0x0008
#define		OS_VRAM_BANK_ID_E		0x0010
#define		OS_VRAM_BANK_ID_F		0x0020
#define		OS_VRAM_BANK_ID_G		0x0040
#define		OS_VRAM_BANK_ID_H		0x0080
#define		OS_VRAM_BANK_ID_I		0x0100
#define		OS_VRAM_BANK_ID_ALL		0x01ff

#define		OS_VRAM_BANK_KINDS		9


/*---------------------------------------------------------------------------*
  Name:         OSi_InitVramExclusive

  Description:  Initializes VRAM exclusive process.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OSi_InitVramExclusive(void);

/*---------------------------------------------------------------------------*
  Name:         OSi_TryLockVram

  Description:  Tries the VRAM exclusive lock.

  Arguments:    bank	-	ID bitmap of VRAM ID for which exclusive lock is attempted.
				lockId	-	Arbitrary ID that will become a key when locking

  Returns:      BOOL	-	Returns TRUE if lock succeeds.
 *---------------------------------------------------------------------------*/
BOOL    OSi_TryLockVram(u16 bank, u16 lockId);

/*---------------------------------------------------------------------------*
  Name:         OSi_InitVramExclusive

  Description:  Releases VRAM exclusive lock.

  Arguments:    bank	-	ID bitmap of VRAM ID for which exclusive lock is released.
				lockId	-	lockId  -  Optional ID specified when locked.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OSi_UnlockVram(u16 bank, u16 lockId);


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_OS_ARM9_VRAMEXCLUSIVE_H_ */

/*---------------------------------------------------------------------------*
    End of file
 *---------------------------------------------------------------------------*/
