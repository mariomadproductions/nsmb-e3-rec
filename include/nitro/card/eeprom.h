/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CARD - include
  File:     eeprom.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: eeprom.h,v $
  Revision 1.8  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.7  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.6  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.5  2004/08/18 08:19:19  yosizaki
  change CARDBackupType format.

  Revision 1.4  2004/07/28 13:18:29  yosizaki
  asynchronous mode support.

  Revision 1.3  2004/07/23 08:31:40  yosizaki
  add new function.

  Revision 1.2  2004/07/05 08:10:03  yosizaki
  delete internal command. (write-protect)

  Revision 1.1  2004/06/28 01:55:02  yosizaki
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/


#if	!defined(NITRO_CARD_EEPROM_H_)
#define NITRO_CARD_EEPROM_H_


#include "nitro/types.h"
#include "nitro/card/common.h"
#include "nitro/card/backup.h"


#if	defined(__cplusplus)
extern  "C"
{
#endif


/* Determine whether the currently set device is EEPROM */
    static inline BOOL CARD_IsBackupEeprom(void)
    {
        const CARDBackupType t = CARD_GetCurrentBackupType();
             
             
            return (((t >> CARD_BACKUP_TYPE_DEVICE_SHIFT) &
                     CARD_BACKUP_TYPE_DEVICE_MASK) == CARD_BACKUP_TYPE_DEVICE_EEPROM);
    }

/* Data read */
    static inline BOOL CARD_ReadEeprom(u32 src, void *dst, u32 len)
    {
        return CARD_ReadBackup(src, dst, len);
    }
    static inline void CARD_ReadEepromAsync(u32 src, void *dst, u32 len, MIDmaCallback callback,
                                            void *arg)
    {
        CARD_ReadBackupAsync(src, dst, len, callback, arg);
    }


/* Data write (equivalent to EEPROM chip command "program") */
    static inline BOOL CARD_WriteEeprom(u32 dst, const void *src, u32 len)
    {
        return CARD_ProgramBackup(dst, src, len);
    }
    static inline void CARD_WriteEepromAsync(u32 dst, const void *src, u32 len,
                                             MIDmaCallback callback, void *arg)
    {
        CARD_ProgramBackupAsync(dst, src, len, callback, arg);
    }

/* Data verify */
    static inline BOOL CARD_VerifyEeprom(u32 dst, const void *src, u32 len)
    {
        return CARD_VerifyBackup(dst, src, len);
    }
    static inline void CARD_VerifyEepromAsync(u32 dst, const void *src, u32 len,
                                              MIDmaCallback callback, void *arg)
    {
        CARD_VerifyBackupAsync(dst, src, len, callback, arg);
    }

/* Data write + verify */
    static inline BOOL CARD_WriteAndVerifyEeprom(u32 dst, const void *src, u32 len)
    {
        return CARD_ProgramAndVerifyBackup(dst, src, len);
    }
    static inline void CARD_WriteAndVerifyEepromAsync(u32 dst, const void *src, u32 len,
                                                      MIDmaCallback callback, void *arg)
    {
        CARD_ProgramAndVerifyBackupAsync(dst, src, len, callback, arg);
    }


#if	defined(__cplusplus)
}                                      /* extern "C" */
#endif


#endif /* NITRO_CARD_EEPROM_H_ */
