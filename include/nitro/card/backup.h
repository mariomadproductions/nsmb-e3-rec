/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CARD - include
  File:     backup.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: backup.h,v $
  Revision 1.17  2007/11/13 04:20:24  yosizaki
  Support for erase-SUBSECTOR.

  Revision 1.16  2007/10/04 13:08:51  yosizaki
  Added test commands.

  Revision 1.15  2007/02/20 00:28:12  kitase_hirotake
  Indented source

  Revision 1.14  2006/05/25 02:51:15  yosizaki
  Added erase-chip, write-sector.

  Revision 1.13  2006/04/10 04:12:42  yosizaki
  Cleaned up source code indent.

  Revision 1.12  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.11  2005/09/02 07:35:02  yosizaki
  Minor fixes.

  Revision 1.10  2005/09/02 07:14:55  yosizaki
  Added CARD_CancelBackupAsync().

  Revision 1.9  2005/05/12 11:21:18  yosizaki
  Added some internal parameters.

  Revision 1.8  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.7  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.6  2004/12/08 06:46:28  yosizaki
  Added comments.

  Revision 1.5  2004/09/06 13:44:31  yosizaki
  Moved CARD_(Lock/Unlock)Backup

  Revision 1.4  2004/08/23 10:39:07  yosizaki
  Added write-command.
  Deleted erase-command. (FLASH)

  Revision 1.3  2004/08/18 13:40:49  yosizaki
  Added FLASH 2Mbit.

  Revision 1.2  2004/07/28 13:18:29  yosizaki
  Asynchronous mode support.

  Revision 1.1  2004/07/23 08:32:18  yosizaki
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/


#if	!defined(NITRO_CARD_BACKUP_H_)
#define NITRO_CARD_BACKUP_H_


#include "nitro/types.h"


#ifdef __cplusplus
extern  "C"
{
#endif


/*---------------------------------------------------------------------------*
  Name:         CARD_LockBackup

  Description:  Locks the CARD-bus before backup operation.

  Arguments:    lock id.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CARD_LockBackup(u16 lock_id);

/*---------------------------------------------------------------------------*
  Name:         CARD_UnlockBackup

  Description:  Unlocks the CARD-bus after backup operation.

  Arguments:    lock id which is used by CARD_LockBackup().

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CARD_UnlockBackup(u16 lock_id);


/*---------------------------------------------------------------------------*
  Name:         CARD_TryWaitBackupAsync

  Description:  Checks if asynchronous backup operation has been completed.

  Arguments:    None.

  Returns:      if operation has been completed, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    CARD_TryWaitBackupAsync(void);

/*---------------------------------------------------------------------------*
  Name:         CARD_TryWaitBackupAsync

  Description:  Waits for completion of current asynchronous backup operation.

  Arguments:    None.

  Returns:      if the newest operation is successful, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    CARD_WaitBackupAsync(void);

/*---------------------------------------------------------------------------*
  Name:         CARD_CancelBackupAsync

  Description:  Requests to cancel current asynchronous backup operation.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CARD_CancelBackupAsync(void);

/* internal chip command as Serial-Bus-Interface */


/*---------------------------------------------------------------------------*
  Name:         CARDi_RequestStreamCommand

  Description:  Issues request for command to transfer data.

  Arguments:    src:        Transfer source offset or memory address.
                dst:        Transfer destination offset or memory address.
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE
                req_type:   Command request type
                req_retry:  Maximum number of retries when command request fails
                req_mode:   Command request operation mode

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    CARDi_RequestStreamCommand(u32 src, u32 dst, u32 len,
                                   MIDmaCallback callback, void *arg, BOOL is_async,
                                   CARDRequest req_type, int req_retry, CARDRequestMode req_mode);

/*---------------------------------------------------------------------------*
  Name:         CARDi_RequestWriteSectorCommand

  Description:  Erases sectors and issues program requests.

  Arguments:    src:        Transfer source memory address
                dst:        Transfer destination offset
                len:        Transfer size
                verify:     TRUE when performing a verify
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    CARDi_RequestWriteSectorCommand(u32 src, u32 dst, u32 len, BOOL verify,
                                        MIDmaCallback callback, void *arg, BOOL is_async);

/*---------------------------------------------------------------------------*
  Name:         CARDi_ReadBackup

  Description:  Issues chip command "read".

  Arguments:    src:        Transfer source offset or memory address.
                dst:        Transfer destination offset or memory address.
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_ReadBackup(u32 src, void *dst, u32 len,
                                 MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len,
                                      callback, arg, is_async,
                                      CARD_REQ_READ_BACKUP, 1, CARD_REQUEST_MODE_RECV);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_ProgramBackup

  Description:  Issues read command using chip command "program".

  Arguments:    src:        Transfer source offset or memory address.
                dst:        Transfer destination offset or memory address.
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_ProgramBackup(u32 dst, const void *src, u32 len,
                                    MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len, callback, arg, is_async,
                                      CARD_REQ_PROGRAM_BACKUP, CARD_RETRY_COUNT_MAX,
                                      CARD_REQUEST_MODE_SEND);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_WriteBackup

  Description:  Issues a write command that uses chip command "write".

  Arguments:    src:        Transfer source offset or memory address.
                dst:        Transfer destination offset or memory address.
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_WriteBackup(u32 dst, const void *src, u32 len,
                                  MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len, callback, arg, is_async,
                                      CARD_REQ_WRITE_BACKUP, CARD_RETRY_COUNT_MAX,
                                      CARD_REQUEST_MODE_SEND);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_VerifyBackup

  Description:  Issues a verify command that uses chip command "read".

  Arguments:    src:        Transfer source offset or memory address.
                dst:        Transfer destination offset or memory address.
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_VerifyBackup(u32 dst, const void *src, u32 len,
                                   MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len, callback, arg, is_async,
                                      CARD_REQ_VERIFY_BACKUP, 1, CARD_REQUEST_MODE_SEND);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_ProgramAndVerifyBackup

  Description:  Issues program and verify command using chip command "program".

  Arguments:    src:        Transfer source offset or memory address.
                dst:        Transfer destination offset or memory address.
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_ProgramAndVerifyBackup(u32 dst, const void *src, u32 len,
                                             MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len, callback, arg, is_async,
                                      CARD_REQ_PROGRAM_BACKUP, CARD_RETRY_COUNT_MAX,
                                      CARD_REQUEST_MODE_SEND_VERIFY);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_WriteAndVerifyBackup

  Description:  Issues program and verify command using chip command "write".

  Arguments:    src:        Transfer source offset or memory address.
                dst:        Transfer destination offset or memory address.
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_WriteAndVerifyBackup(u32 dst, const void *src, u32 len,
                                           MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand((u32)src, (u32)dst, len, callback, arg, is_async,
                                      CARD_REQ_WRITE_BACKUP, CARD_RETRY_COUNT_MAX,
                                      CARD_REQUEST_MODE_SEND_VERIFY);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_EraseBackupSector

  Description:  Issues a sector deletion command using the chip command, "erase sector".

  Arguments:    dst:        the deletion target offset
                len:        the deletion size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_EraseBackupSector(u32 dst, u32 len,
                                        MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand(0, (u32)dst, len, callback, arg, is_async,
                                      CARD_REQ_ERASE_SECTOR_BACKUP, CARD_RETRY_COUNT_MAX,
                                      CARD_REQUEST_MODE_SPECIAL);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_EraseBackupSubSector

  Description:  Issues a sector deletion command using the chip command, "erase subsector".

  Arguments:    dst:        the deletion target offset
                len:        the deletion size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_EraseBackupSubSector(u32 dst, u32 len,
                                           MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand(0, (u32)dst, len, callback, arg, is_async,
                                      CARD_REQ_ERASE_SUBSECTOR_BACKUP, CARD_RETRY_COUNT_MAX,
                                      CARD_REQUEST_MODE_SPECIAL);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_EraseBackupChip

  Description:  Issues a sector deletion command using the chip command, "erase chip".

  Arguments:    callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)
                is_async:   If async operation was specified, TRUE

  Returns:      If action is successful, TRUE.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_EraseBackupChip(MIDmaCallback callback, void *arg, BOOL is_async)
{
    return CARDi_RequestStreamCommand(0, 0, 0, callback, arg, is_async,
                                      CARD_REQ_ERASE_CHIP_BACKUP, 1, CARD_REQUEST_MODE_SPECIAL);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_ReadBackupAsync

  Description:  Asynchronous backup read (equivalent to the chip command "read").

  Arguments:    src:        Transfer source offset
                dst:        Transfer destination memory address.
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_ReadBackupAsync(u32 src, void *dst, u32 len, MIDmaCallback callback, void *arg)
{
    (void)CARDi_ReadBackup(src, dst, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_ReadBackup

  Description:  Synchronous backup read (equivalent to the chip command "read").

  Arguments:    src:        Transfer source offset
                dst:        Transfer destination memory address.
                len:        Transfer size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_ReadBackup(u32 src, void *dst, u32 len)
{
    return CARDi_ReadBackup(src, dst, len, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_ProgramBackupAsync

  Description:  Asynchronous backup program (equivalent to the chip command "program").

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_ProgramBackupAsync(u32 dst, const void *src, u32 len,
                                        MIDmaCallback callback, void *arg)
{
    (void)CARDi_ProgramBackup(dst, src, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_ProgramBackup

  Description:  Synchronous backup program (equivalent to the chip command "program").

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_ProgramBackup(u32 dst, const void *src, u32 len)
{
    return CARDi_ProgramBackup(dst, src, len, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_WriteBackupAsync

  Description:  Asynchronous backup write (equivalent to the chip command "write").

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_WriteBackupAsync(u32 dst, const void *src, u32 len,
                                      MIDmaCallback callback, void *arg)
{
    (void)CARDi_WriteBackup(dst, src, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_WriteBackup

  Description:  Synchronous backup write (equivalent to the chip command "write").

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_WriteBackup(u32 dst, const void *src, u32 len)
{
    return CARDi_WriteBackup(dst, src, len, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_VerifyBackupAsync

  Description:  Asynchronous backup verify (equivalent to the chip command "read").

  Arguments:    src:        Comparison source offset
                dst:        Comparison destination memory address
                len:        Comparison size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_VerifyBackupAsync(u32 dst, const void *src, u32 len,
                                       MIDmaCallback callback, void *arg)
{
    (void)CARDi_VerifyBackup(dst, src, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_VerifyBackup

  Description:  Synchronous backup verify (equivalent to the chip command "read").

  Arguments:    src:        Comparison source offset
                dst:        Comparison destination memory address
                len:        Comparison size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_VerifyBackup(u32 dst, const void *src, u32 len)
{
    return CARDi_VerifyBackup(dst, src, len, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_ProgramAndVerifyBackupAsync

  Description:  Asynchronous backup program + verify.

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_ProgramAndVerifyBackupAsync(u32 dst, const void *src, u32 len,
                                                 MIDmaCallback callback, void *arg)
{
    (void)CARDi_ProgramAndVerifyBackup(dst, src, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_ProgramAndVerifyBackup

  Description:  Synchronous backup program + verify.

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_ProgramAndVerifyBackup(u32 dst, const void *src, u32 len)
{
    return CARDi_ProgramAndVerifyBackup(dst, src, len, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_WriteAndVerifyBackupAsync

  Description:  Asynchronous backup write + verify.

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_WriteAndVerifyBackupAsync(u32 dst, const void *src, u32 len,
                                               MIDmaCallback callback, void *arg)
{
    (void)CARDi_WriteAndVerifyBackup(dst, src, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_WriteAndVerifyBackup

  Description:  Synchronous backup write + Verify.

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_WriteAndVerifyBackup(u32 dst, const void *src, u32 len)
{
    return CARDi_WriteAndVerifyBackup(dst, src, len, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_EraseBackupSectorAsync

  Description:  Asynchronous sector deletion.

  Arguments:    dst:        the deletion target offset
                len:        the deletion size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_EraseBackupSectorAsync(u32 dst, u32 len, MIDmaCallback callback, void *arg)
{
    (void)CARDi_EraseBackupSector(dst, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_EraseBackupSector

  Description:  Synchronous sector deletion.

  Arguments:    dst:        the deletion target offset
                len:        the deletion size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_EraseBackupSector(u32 dst, u32 len)
{
    return CARDi_EraseBackupSector(dst, len, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_EraseBackupSubSectorAsync

  Description:  Asynchronous subsector deletion.

  Arguments:    dst:        the deletion target offset
                len:        the deletion size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_EraseBackupSubSectorAsync(u32 dst, u32 len, MIDmaCallback callback, void *arg)
{
    (void)CARDi_EraseBackupSubSector(dst, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_EraseBackupSubSector

  Description:  Synchronous subsector deletion.

  Arguments:    dst:        the deletion target offset
                len:        the deletion size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_EraseBackupSubSector(u32 dst, u32 len)
{
    return CARDi_EraseBackupSubSector(dst, len, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_EraseBackupChipAsync

  Description:  Asynchronous chip deletion.

  Arguments:    callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_EraseBackupChipAsync(MIDmaCallback callback, void *arg)
{
    (void)CARDi_EraseBackupChip(callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_EraseBackupChip

  Description:  Synchronous sector deletion.

  Arguments:    None.

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_EraseBackupChip(void)
{
    return CARDi_EraseBackupChip(NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_WriteBackupSectorAsync

  Description:  Erases in sector units and programs in sector units.

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_WriteBackupSectorAsync(u32 dst, const void *src, u32 len,
                                            MIDmaCallback callback, void *arg)
{
    (void)CARDi_RequestWriteSectorCommand((u32)src, dst, len, FALSE, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_WriteBackupSector

  Description:  Erases in sector units and programs in sector units.

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_WriteBackupSector(u32 dst, const void *src, u32 len)
{
    return CARDi_RequestWriteSectorCommand((u32)src, dst, len, FALSE, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_WriteAndVerifyBackupSectorAsync

  Description:  Erases in sector units, programs in sector units, and verifies.

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size
                callback:   Completion callback (NULL if not used)
                arg:        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
SDK_INLINE void CARD_WriteAndVerifyBackupSectorAsync(u32 dst, const void *src, u32 len,
                                                     MIDmaCallback callback, void *arg)
{
    (void)CARDi_RequestWriteSectorCommand((u32)src, dst, len, TRUE, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_WriteAndVerifyBackupSector

  Description:  Erases in sector units, programs in sector units, and verifies.

  Arguments:    dst:        Transfer destination offset
                src:        Transfer source memory address
                len:        Transfer size

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARD_WriteAndVerifyBackupSector(u32 dst, const void *src, u32 len)
{
    return CARDi_RequestWriteSectorCommand((u32)src, dst, len, TRUE, NULL, NULL, FALSE);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_AccessStatus

  Description:  Status read or write (for testing).

  Arguments:    command:    CARD_REQ_READ_STATUS or CARD_REQ_WRITE_STATUS
                value:      The value to write, if CARD_REQ_WRITE_STATUS

  Returns:      Returns a value of 0 or higher if successful; a negative number otherwise.
 *---------------------------------------------------------------------------*/
int CARDi_AccessStatus(CARDRequest command, u8 value);

/*---------------------------------------------------------------------------*
  Name:         CARDi_ReadStatus

  Description:  Status read (for testing).

  Arguments:    None.

  Returns:      Returns a value of 0 or higher if successful; a negative number otherwise.
 *---------------------------------------------------------------------------*/
SDK_INLINE int CARDi_ReadStatus(void)
{
    return CARDi_AccessStatus(CARD_REQ_READ_STATUS, 0);
}

/*---------------------------------------------------------------------------*
  Name:         CARDi_WriteStatus

  Description:  Status write (for testing).

  Arguments:    value:      The value to be written

  Returns:      TRUE if completed with CARD_RESULT_SUCCESS, FALSE for everything else.
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL CARDi_WriteStatus(u8 value)
{
    return (CARDi_AccessStatus(CARD_REQ_WRITE_STATUS, value) >= 0);
}


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* NITRO_CARD_BACKUP_H_ */
