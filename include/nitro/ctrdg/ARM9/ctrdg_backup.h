/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CTRDG - include
  File:     ctrdg_backup.h

  Copyright 2001,2003,2004,2006,2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: ctrdg_backup.h,v $
  Revision 1.4  2007/02/20 00:28:11  kitase_hirotake
  indent source

  Revision 1.3  2006/04/07 07:56:11  okubata_ryoma
  added notes

  Revision 1.2  2006/04/07 03:29:03  okubata_ryoma
  Corrected comment

  Revision 1.1  2006/04/05 10:34:15  okubata_ryoma
  changes made for AGB backup library's SDK collection


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CTRDG_BACKUP_H_
#define NITRO_CTRDG_BACKUP_H_

#include "nitro.h"
#include "ctrdg_task.h"
#include "ctrdg_flash.h"
#include "ctrdg_sram.h"

// define data----------------------------------
#define CTRDG_BACKUP_PHASE_VERIFY           0x0000
#define CTRDG_BACKUP_PHASE_PROGRAM          0x0001
#define CTRDG_BACKUP_PHASE_SECTOR_ERASE     0x0002
#define CTRDG_BACKUP_PHASE_CHIP_ERASE       0x0003
#define CTRDG_BACKUP_PHASE_VERIFY_ERASE     0x0004
#define CTRDG_BACKUP_PHASE_PARAMETER_CHECK  0x00ff

#define CTRDG_BACKUP_RESULT_OK              0x0000
#define CTRDG_BACKUP_RESULT_ERROR           0x8000
#define CTRDG_BACKUP_RESULT_TIMEOUT         0x4000
#define CTRDG_BACKUP_RESULT_Q5TIMEOUT       0x2000
#define CTRDG_BACKUP_RESULT_PULLEDOUT       0x1000

/* For debugging */
//#ifndef   __FLASH_DEBUG
#define CTRDG_BACKUP_VENDER_ID_ADR      (CTRDG_AGB_FLASH_ADR+0x00000000)
#define CTRDG_BACKUP_DEVICE_ID_ADR      (CTRDG_AGB_FLASH_ADR+0x00000001)
#define CTRDG_BACKUP_COM_ADR1           (CTRDG_AGB_FLASH_ADR+0x00005555)
#define CTRDG_BACKUP_COM_ADR2           (CTRDG_AGB_FLASH_ADR+0x00002aaa)
//#else
//#define   VENDER_ID_ADR       0x02003ffc
//#define   DEVICE_ID_ADR       0x02003ffd
//#define   COM_ADR1            0x02003ffe
//#define COM_ADR2          0x02003fff
//#endif

#define CTRDG_BACKUP_MEGA_512K_ID       0x1cc2
#define CTRDG_BACKUP_MEGA_1M_ID         0x09c2
//#define   CTRDG_BACKUP_MEGA_1M_ID         0x1cc2

// data type declaration------------------------
typedef struct CTRDGiFlashTypePlusTag
{
    u16     (*CTRDGi_WriteAgbFlashSector) (u16 secNo, u8 *src);
    u16     (*CTRDGi_EraseAgbFlashChip) (void);
    u16     (*CTRDGi_EraseAgbFlashSector) (u16 secNo);
    void    (*CTRDGi_WriteAgbFlashSectorAsync) (u16 secNo, u8 *src, CTRDG_TASK_FUNC callback);
    void    (*CTRDGi_EraseAgbFlashChipAsync) (CTRDG_TASK_FUNC callback);
    void    (*CTRDGi_EraseAgbFlashSectorAsync) (u16 secNo, CTRDG_TASK_FUNC callback);
    u16     (*CTRDGi_PollingSR) (u16 phase, u8 *adr, u16 lastData);
    const u16 *maxtime;
    CTRDGFlashType type;
}
CTRDGiFlashTypePlus;

typedef enum
{
    CTRDG_BACKUP_TYPE_FLASH_512K,      /* 512K flash */
    CTRDG_BACKUP_TYPE_FLASH_1M,        /* 1M flash */
    CTRDG_BACKUP_TYPE_SRAM             /* 256K SRAM */
}
CTRDGBackupType;

// extern variables declaration----------------------
extern u16 ctrdg_flash_remainder;
extern const u16 *ctrdgi_fl_maxtime;
extern u16 (*CTRDGi_PollingSR) (u16 phase, u8 *adr, u16 lastData);

// function declaration-------------------------
extern const CTRDGFlashType *AgbFlash;
extern u16 (*CTRDGi_WriteAgbFlashSector) (u16 secNo, u8 *src);
extern u16 (*CTRDGi_EraseAgbFlashChip) (void);
extern u16 (*CTRDGi_EraseAgbFlashSector) (u16 secNo);
extern void (*CTRDGi_WriteAgbFlashSectorAsync) (u16 secNo, u8 *src, CTRDG_TASK_FUNC callback);
extern void (*CTRDGi_EraseAgbFlashChipAsync) (CTRDG_TASK_FUNC callback);
extern void (*CTRDGi_EraseAgbFlashSectorAsync) (u16 secNo, CTRDG_TASK_FUNC callback);
extern u16 (*pollingSR) (u16 phase, u8 *adr, u16 lastData);

/*------------------------------------------------------------------*/
/*          device identifier and default settings                  */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_IdentifyAgbBackup
                
                the corresponding AGB function: extern u16 IdentifyFlash_512K()
                the corresponding AGB function: extern u16 IdentifyFlash_1M()
                
  Description:  Specifies the backup device on the NITRO-CTRDG.
                When the backup device is flash memory, the flash ID is read,
                the flash on the cartridge is identified,
                it's volume and sector size and gotten, the access speed is set,
                and the corresponding flash access functions are set.
                The gotten flash data can be referenced with the global variable, CTRDGFlashType *AgbFlash.
                (See the definitions above for more on CTRDGFlashType.)
                
                This function must be called once before accessing (including reads) the backup device.
                An error is returned if the device cannot be identified, and the following access functions can no longer be used.
                
                Access cycle settings are made within the function, and do not need to occur in advance.
                As this function uses ticks to measure timeouts,
                the OS_InitTick function must be called in advance.

                * Be aware that within this function, all interrupts are prohibited for a certain period of time, and the cartridge is locked.
                In particular, when calling this function do not use DMAs that automatically launch at
                specific times, as for direct sound, VH Blank synchronization, display synchronization, cartridge requests, etc.
                
                In addition, when the arguments CTRDG_BACKUP_TYPE_FLASH_512K or CTRDG_BACKUP_TYPE_FLASH_1M are used,
                write operations for the device will begin, and if a device different than that of the argument is on the NITRO-CTRDG,
                be aware that the backup data may be corrupted.


  Arguments:    type: the type of backup device on the NITRO-CTRDG

  Returns:      0       : normal end
                non-zero: identification error
 *---------------------------------------------------------------------------*/
extern u16 CTRDG_IdentifyAgbBackup(CTRDGBackupType type);

#endif // NITRO_CTRDG_BACKUP_H_
