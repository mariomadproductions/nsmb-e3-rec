/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CTRDG - include
  File:     ctrdg_flash.h

  Copyright 2003,2004,2006,2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: ctrdg_flash.h,v $
  Revision 1.3  2007/02/20 00:28:11  kitase_hirotake
  indent source

  Revision 1.2  2006/04/07 03:28:43  okubata_ryoma
  Corrected comment

  Revision 1.1  2006/04/05 10:34:15  okubata_ryoma
  changes made for AGB backup library's SDK collection


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CTRDG_FLASH_H_
#define NITRO_CTRDG_FLASH_H_

#include "nitro.h"

#ifdef __cplusplus
extern "C" {
#endif

/* definition ****************************************************************/

/* flash header address */
#define CTRDG_AGB_FLASH_ADR           0x0A000000

/* the maximum number of retries for the CTRDG_WriteAndVerifyAgbFlash function */
#define CTRDG_AGB_FLASH_RETRY_MAX     3


typedef struct CTRDGiFlashSectorTag
{
    u32     size;                      /* sector size */
    u16     shift;                     /* the value after converting the sector size into shift numbers */
    u16     count;                     /* the number of sectors */
    u16     top;                       /* the available leading sector number */
    u8      reserved[2];               /* Padding */
}
CTRDGiFlashSector;

typedef struct CTRDGFlashTypeTag
{
    u32     romSize;                   /* the ROM size */
    CTRDGiFlashSector sector;          /* sector data (* see CTRDGiFlashSector above) */
    MICartridgeRamCycle agbWait[2];    /* the AGB cartridge bus RAM region's read/write weight value */
    u16     makerID;                   /* the vendor ID */
    u16     deviceID;                  /* the device ID */
}
CTRDGFlashType;

extern void CTRDGi_SetFlashBankMx(u16 bank);
extern u16 CTRDGi_ReadFlashID(void);
extern void StartFlashTimer(u16 phase);
extern void CheckFlashTimer(void);
extern void CTRDGi_SetFlashBankMx(u16 bank);
extern u16 CTRDGi_PollingSR512kCOMMON(u16 phase, u8 *adr, u16 lastData);
extern u16 CTRDGi_PollingSR1MCOMMON(u16 phase, u8 *adr, u16 lastData);

/*------------------------------------------------------------------*/
/*          Global Variables                                          */
/*------------------------------------------------------------------*/

/*
 * Pointer to the data indicated the flash structure content.
 * (for details, see the data definitions above)
 */
extern const CTRDGFlashType *AgbFlash;

/*
 * the barometer indicating progress during flash writes
 * NB: ctrdg_flash_remainder goes down in 128 increments for flash made by Atmel,
 * but the decrement is 1 for other devices.
 */
extern u16 ctrdg_flash_remainder;

/*------------------------------------------------------------------*/
/*          data read                                          */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_ReadAgbFlash
                CTRDG_ReadAgbFlashAsync
  
                corresponding AGB function: extern void ReadFlash(u16 secNo,u32 offset,u8 *dst,u32 size)

  Description:  Reads data in the size byte amount from the address that is offset bytes ahead
                within the target flash sector number, and writes it to the working dst address.
                
                Access cycle settings are made within the function, and do not need to occur in advance.

                * Be aware that within this function the cartridge bus is locked for a fixed period of time.

                
  Arguments:    secNo    : the target sector number
                offset   : the offset, in bytes, within the sector
                dst      : the address of the work region where the read data is stored
                size     : the read size in bytes
                callback : the callback function called when the read processes complete (only for asynchronous functions)

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void CTRDG_ReadAgbFlash(u16 sec_num, u32 offset, u8 *dst, u32 size);
extern void CTRDG_ReadAgbFlashAsync(u16 sec_num, u32 offset, u8 *dst, u32 size,
                                    CTRDG_TASK_FUNC callback);


/*------------------------------------------------------------------*/
/*          chip deletion                                              */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_EraseAgbFlashChip
                CTRDG_EraseAgbFlashChipAsync
                
                the corresponding AGB function: extern u16 (*EraseFlashChip)()

  Description:  Completely erases the entire chip.
  
                Access cycle settings are made within the function, and do not need to occur in advance.
                As this function uses ticks to measure timeouts,
                the OS_InitTick function must be called in advance.
                
                In addition, by referring to result, a member of the CTRDGTaskInfo structure that is an argument
                of the callback function returned after calling this routine, it is possible to know whether the Erase processes succeeded.

                * Be aware that within this function, all interrupts are prohibited for a certain period of time, and the cartridge is locked.
                In particular, when calling this function do not use DMAs that automatically launch at
                specific times, as for direct sound, VH Blank synchronization, display synchronization, cartridge requests, etc.

                
  Arguments:    callback : the callback function called when the erase processes complete (only for asynchronous functions)

  Returns:      0       : normal completion (only for synchronous functions)
                non-zero: erase error
 *---------------------------------------------------------------------------*/
extern u16 CTRDG_EraseAgbFlashChip(void);
extern void CTRDG_EraseAgbFlashChipAsync(CTRDG_TASK_FUNC callback);


/*------------------------------------------------------------------*/
/*          sector deletion                                              */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_EraseAgbFlashSector
                CTRDG_EraseAgbFlashSectorAsync
                
                the corresponding AGB function: extern u16 (*EraseFlashSector)(u16 secNo)

  Description:  Erases the sector with the target sector number.
                Because this routine is called within write routines,
                there is no need to normally call this routine before writing.
                An error is returned when the target sector number is out of scope.
                
                In addition, by referring to result, a member of the CTRDGTaskInfo structure that is an argument
                of the callback function returned after calling this routine, it is possible to know whether the Erase processes succeeded.
                
                Access cycle settings are made within the function, and do not need to occur in advance.
                As this function uses ticks to measure timeouts,
                the OS_InitTick function must be called in advance.

                * Be aware that within this function, all interrupts are prohibited for a certain period of time, and the cartridge is locked.
                In particular, when calling this function do not use DMAs that automatically launch at
                specific times, as for direct sound, VH Blank synchronization, display synchronization, cartridge requests, etc.

                
  Arguments:    sec_num   : the target sector number
                callback  : the callback function called when the erase processes complete (only for asynchronous functions)

  Returns:      0       : normal completion (only for synchronous functions)
                non-zero: erase error
 *---------------------------------------------------------------------------*/
extern u16 CTRDG_EraseAgbFlashSector(u16 sec_num);
extern void CTRDG_EraseAgbFlashSectorAsync(u16 sec_num, CTRDG_TASK_FUNC callback);


/*------------------------------------------------------------------*/
/*          writing the data in sector units                                */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_WriteAgbFlashSector
                CTRDG_WriteAgbFlashSectorAsync
                
                the corresponding AGB function: extern u16 (*ProgramFlashSector)(u16 secNo,u8 *src)

  Description:  Writes a sector (4 KB) of data to the target sector number from the src address.
                Writes within this routine occur after the above CTRDG_EraseAgbFlashSector is called and the sector erased.
                An error is returned when the target sector number is out of scope.
                As this routine runs, the global variable, ctrdg_flash_remainder, can be referenced to know how many bytes remain.
                
                In addition, by referring to result, a member of the CTRDGTaskInfo structure that is an argument
                of the callback function returned after calling this routine, it is possible to know whether the Write processes succeeded.
                
                Access cycle settings are made within the function, and do not need to occur in advance.
                As this function uses ticks to measure timeouts,
                the OS_InitTick function must be called in advance.

                * Be aware that within this function, all interrupts are prohibited for a certain period of time, and the cartridge is locked.
                In particular, when calling this function do not use DMAs that automatically launch at
                specific times, as for direct sound, VH Blank synchronization, display synchronization, cartridge requests, etc.

                
  Arguments:    sec_num   : the target sector number
                src       : the write source address
                callback  : the callback function called when the write processes complete (only for asynchronous functions)

  Returns:      0        : normal completion (only for synchronous functions)
                non-zero : write error
 *---------------------------------------------------------------------------*/
extern u16 CTRDG_WriteAgbFlashSector(u16 sec_num, u8 *src);
extern void CTRDG_WriteAgbFlashSectorAsync(u16 sec_num, u8 *src, CTRDG_TASK_FUNC callback);


/*------------------------------------------------------------------*/
/*          data verify in bytes                              */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_VerifyAgbFlash
                CTRDG_VerifyAgbFlashAsync
                
                corresponding AGB function: extern u32 VerifyFlash(u16 secNo,u8 *src,u32 size)

  Description:  Verifies target flash sector number data in size byte portions from data in the src address.
                This function returns a 0 when verifies end normally, and returns the address where the error occurred when a verify error occurs.
                In addition, by referring to result, a member of the CTRDGTaskInfo structure that is an argument
                of the callback function returned after calling this routine, it is possible to know whether the Verify processes succeeded.
                
  Arguments:    sec_num   : the target sector number
                src       : the verify source address (the original data)
                size      : verify size (bytes)
                callback  : the callback function called when the verify processes complete (only for asynchronous functions)

  Returns:      0        : normal completion (only for synchronous functions)
                non-zero : Returns the device-side error address for a verify error.
 *---------------------------------------------------------------------------*/
extern u32 CTRDG_VerifyAgbFlash(u16 sec_num, u8 *src, u32 size);
extern void CTRDG_VerifyAgbFlashAsync(u16 sec_num, u8 *src, u32 size, CTRDG_TASK_FUNC callback);


/*------------------------------------------------------------------*/
/*          data writing by sector & verify by byte          */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_WriteAndVerifyAgbFlash
                CTRDG_WriteAndVerifyAgbFlashAsync
                
                corresponding AGB function: extern u32 ProgramFlashSectorEx2(u16 secNo,u8 *src,u32 verifySize)

  Description:  This function verifies in verifysize byte portions with the CTRDG_VerifyAgbFlash function
                after the CTRDG_WriteAgbFlashSector function finishes writing.
                When errors occur, retries are made up to a maximum of CTRDG_AGB_FLASH_RETRY_MAX (defined in ctrdg_flash.h) times.
                
                * This function returns a 16-bit error code within 32 bits when write errors occur,
                and a 32-bit device-side error address is returned for verify errors.
                Be aware of this when confirming the error code.
                In addition, by referring to result, a member of the CTRDGTaskInfo structure that is an argument
                of the callback function returned after calling this routine, it is possible to know whether the WriteAndVerify processes succeeded.
                
                Access cycle settings are made within the function, and do not need to occur in advance.
                As this function uses ticks to measure timeouts,
                the OS_InitTick function must be called in advance.

                * Be aware that within this function, all interrupts are prohibited for a certain period of time, and the cartridge is locked.
                In particular, when calling this function do not use DMAs that automatically launch at
                specific times, as for direct sound, VH Blank synchronization, display synchronization, cartridge requests, etc.

                
  Arguments:    sec_num    : the target sector number
                src        : the write source address
                verifysize : the verify size (bytes)
                callback   : the callback function called when the WriteAndVerify processes complete (only for asynchronous functions)

  Returns:      0        : normal completion (only for synchronous functions)
                non-zero : Returns the device-side error address for a verify error.
 *---------------------------------------------------------------------------*/
extern u32 CTRDG_WriteAndVerifyAgbFlash(u16 sec_num, u8 *src, u32 verifysize);
extern void CTRDG_WriteAndVerifyAgbFlashAsync(u16 sec_num, u8 *src, u32 verifysize,
                                              CTRDG_TASK_FUNC callback);


#ifdef __cplusplus
}      /* extern "C" */
#endif


#endif /* NITRO_CTRDG_FLASH_H_ */
