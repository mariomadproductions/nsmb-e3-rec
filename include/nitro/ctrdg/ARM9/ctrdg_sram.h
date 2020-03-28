/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CTRDG - include
  File:     ctrdg_sram.h

  Copyright 2003,2004,2006,2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: ctrdg_sram.h,v $
  Revision 1.3  2007/02/20 00:28:11  kitase_hirotake
  indent source

  Revision 1.2  2006/04/07 03:28:23  okubata_ryoma
  Corrected comment

  Revision 1.1  2006/04/05 10:34:15  okubata_ryoma
  changes made for AGB backup library's SDK collection


  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_CTRDG_SRAM_H_
#define NITRO_CTRDG_SRAM_H_

#include "nitro.h"

#ifdef __cplusplus
extern "C" {
#endif

/* For debugging */
//#ifndef __SRAM_DEBUG
#define CTRDG_AGB_SRAM_ADR          0x0A000000  /* SRAM leading address */
#define CTRDG_AGB_SRAM_SIZE_256K    0x00008000  /* 256K SRAM size */
#define CTRDG_AGB_SRAM_SIZE_512K    0x00010000  /* 512K SRAM size */
//#else
//#define CTRDG_AGB_SRAM_ADR        0x02018000
//#define CTRDG_AGB_SRAM_SIZE_256K    0x00000400
//#define CTRDG_AGB_SRAM_SIZE_512K    0x00000800
//#endif

/* the maximum number of retries for the CTRDG_WriteAgbSramEx function */
#define CTRDG_AGB_SRAM_RETRY_MAX    3


/*------------------------------------------------------------------
--------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*          data read                                          */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_ReadAgbSram
                CTRDG_ReadAgbSramAsync
  
                corresponding AGB function: extern void ReadSram(u8 *src,u8 *dst,u32 size)

  Description:  From the SRAM address specified in the argument, the size byte data
                is read from the working dst address and beyond.
                
  Arguments:    src      : the read source SRAM address (the address in the AGB memory map)
                dst      : the work region address (the address in the AGB memory map) where the read data is stored
                size     : the read size in bytes
                callback : the callback function called when the read processes complete (only for asynchronous functions)

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void CTRDG_ReadAgbSram(u32 src, void *dst, u32 size);
extern void CTRDG_ReadAgbSramAsync(u32 src, void *dst, u32 size, CTRDG_TASK_FUNC callback);


/*------------------------------------------------------------------*/
/*          writing the data                                          */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_WriteAgbSram
                CTRDG_WriteAgbSramAsync
                
                corresponding AGB function: extern void WriteSram(u8 *dst,u8 *src,u32 size)

  Description:  From the work region address specified in the argument, the size byte data
                is written from the SRAM dst address and beyond.
                
  Arguments:    dst      : the write destination SRAM address (the address in the AGB memory map)
                src      : the write source work region address
                size     : the write size in bytes
                callback : the callback function called when the write processes complete (only for asynchronous functions)

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void CTRDG_WriteAgbSram(u32 dst, const void *src, u32 size);
extern void CTRDG_WriteAgbSramAsync(u32 dst, const void *src, u32 size, CTRDG_TASK_FUNC callback);


/*------------------------------------------------------------------*/
/*          Data verify                                        */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_VerifyAgbSram
                CTRDG_VerifyAgbSramAsync
                
                corresponding AGB function: extern u32 VerifySram(u8 *tgt,u8 *src,u32 size)

  Description:  Verifies the data from work region src address and the SRAM's tgt address in size byte portions.
                This function returns a 0 when verified, and the address from which
                the error originated if a verify error occurs.
                In addition, by referring to result, a member of the CTRDGTaskInfo structure that is an argument
                of the callback function returned after calling this routine, it is possible to know whether the Verify processes succeeded.
                
  Arguments:    tgt      : a pointer to the verify-target SRAM address (address of the write-target address in the AGB memory map)
                src      : a pointer to the verify-source work region address (the original data)
                size     : the verify size in bytes
                callback : the callback function called when the verify processes complete (only for asynchronous functions)

  Returns:      0        : normal end
                non-zero : Returns the device-side error address for a verify error. (only for synchronous functions)
 *---------------------------------------------------------------------------*/
extern u32 CTRDG_VerifyAgbSram(u32 tgt, const void *src, u32 size);
extern void CTRDG_VerifyAgbSramAsync(u32 tgt, const void *src, u32 size, CTRDG_TASK_FUNC callback);


/*------------------------------------------------------------------*/
/*          writing & verifying the data                              */
/*------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         CTRDG_WriteAndVerifyAgbSram
                CTRDG_WriteAndVerifyAgbSramAsync
                
                corresponding AGB function: extern u32 WriteSramEx(u8 *dst, u8 *src, u32 size)

  Description:  After writes are performed internally with CTRDG_WriteAgbSram, verifies are performed with CTRDG_VerifyAgbSram;
                when errors occur, retries are made up to a maximum of CTRDG_AGB_SRAM_RETRY_MAX (defined in ctrdg_sram.h) times.
                
                In addition, by referring to result, a member of the CTRDGTaskInfo structure that is an argument
                of the callback function returned after calling this routine, it is possible to know whether the WriteAndVerify processes succeeded.
                
  Arguments:    dst      : the write destination SRAM address (the address in the AGB memory map)
                src      : the write source work region address
                size     : the write/verify size in bytes
                callback : the callback function called when the WriteAndVerify processes complete (only for asynchronous functions)

  Returns:      0        : normal end
                non-zero : Returns the device-side error address for a verify error. (only for synchronous functions)
 *---------------------------------------------------------------------------*/
extern u32 CTRDG_WriteAndVerifyAgbSram(u32 dst, const void *src, u32 size);
extern void CTRDG_WriteAndVerifyAgbSramAsync(u32 dst, const void *src, u32 size,
                                             CTRDG_TASK_FUNC callback);


#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif /* NITRO_CTRDG_SRAM_H_ */
