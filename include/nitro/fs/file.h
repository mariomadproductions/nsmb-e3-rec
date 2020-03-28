/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FS - include
  File:     file.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/


#if	!defined(NITRO_FS_FILE_H_)
#define NITRO_FS_FILE_H_

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/mi.h"
#include "nitro/fs/archive.h"
#include "nitro/card.h"


#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************/
/* constant */

/* max file-path length */
#define	FS_FILE_NAME_MAX	127

/* use cpu-copy instead of DMA */
#define	FS_DMA_NOT_USE	((u32)~0)

/* for FS_Seek() */
typedef enum
{
    FS_SEEK_SET,                       /* seek from begin */
    FS_SEEK_CUR,                       /* seek from current */
    FS_SEEK_END                        /* seek from end */
}
FSSeekFileMode;

/* file status (internal use) */
#define	FS_FILE_STATUS_BUSY			0x00000001
#define	FS_FILE_STATUS_CANCEL		0x00000002
#define	FS_FILE_STATUS_SYNC			0x00000004
#define	FS_FILE_STATUS_ASYNC		0x00000008
#define	FS_FILE_STATUS_IS_FILE		0x00000010
#define	FS_FILE_STATUS_IS_DIR		0x00000020
#define FS_FILE_STATUS_OPERATING    0x00000040


/* file status (for archive implements) */
#define	FS_FILE_STATUS_USER_RESERVED_BIT	0x00010000
#define	FS_FILE_STATUS_USER_RESERVED_MASK	0xFFFF0000


/*****************************************************************************/
/* declaration */

/* file operation structure */
struct FSFile;


/* directory position structure.
   for FS_TellDir(), FS_SeekDir(), FS_ReadDir() */
typedef struct
{
/* private: (except direct operation with FSArchive) */
    struct FSArchive *arc;             /* attached archive */
    u16     own_id;                    /* own directory id */
    u16     index;                     /* if next FSDirEntry is file, its id */
    u32     pos;                       /* seek offset to next FSDirEntry */
}
FSDirPos;


/* file id structure.
   for FS_OpenFileFast() */
typedef struct
{
/* private: (except direct operation with FSArchive) */
    struct FSArchive *arc;             /* attached archive */
    u32     file_id;                   /* index of FAT of attached archive */
}
FSFileID;


/* file-and-directory entry information structure.
   for FS_ReadDir() */
typedef struct
{
    union
    {
        FSFileID file_id;              /* valid if !is_directory */
        FSDirPos dir_id;               /* valid if is_directory */
    };
    u32     is_directory;              /* directory ? 1 : 0 */
    u32     name_len;                  /* strlen(name) */
    char    name[FS_FILE_NAME_MAX + 1]; /* string with '\0' */
}
FSDirEntry;


/* file command argument structure.
	for default implements and user procedure */

        /* for FS_COMMAND_SSEKDIR */
typedef struct
{
    FSDirPos pos;
}
FSSeekDirInfo;

        /* for FS_COMMAND_READDIR */
typedef struct
{
    FSDirEntry *p_entry;
    BOOL    skip_string;
}
FSReadDirInfo;

        /* for FS_COMMAND_FINDPATH */
typedef struct
{
    FSDirPos pos;
    const char *path;
    BOOL    find_directory;
    union
    {
        FSFileID *file;
        FSDirPos *dir;
    }
    result;
}
FSFindPathInfo;

        /* for FS_COMMAND_GETPATH */
typedef struct
{
    u8     *buf;
    u32     buf_len;
    u16     total_len;
    u16     dir_id;
}
FSGetPathInfo;

        /* for FS_COMMAND_OPENFILEFAST */
typedef struct
{
    FSFileID id;
}
FSOpenFileFastInfo;

        /* for FS_COMMAND_OPENFILEDIRECT */
typedef struct
{
    u32     top;
    u32     bottom;
    u32     index;
}
FSOpenFileDirectInfo;

        /* for FS_COMMAND_CLOSEFILE */
typedef struct
{
    u32     reserved;
}
FSCloseFileInfo;

        /* for FS_COMMAND_READFILE */
typedef struct
{
    void   *dst;
    u32     len_org;
    u32     len;
}
FSReadFileInfo;

        /* for FS_COMMAND_WRITEFILE */
typedef struct
{
    const void *src;
    u32     len_org;
    u32     len;
}
FSWriteFileInfo;


/* file and directory structure */
typedef struct FSFile
{
/* private: */

    /* for archive control */
    FSFileLink link;
    struct FSArchive *arc;
    /* for internal status */
    u32     stat;
    FSCommandType command;
    FSResult error;
#ifndef SDK_THREAD_INFINITY
    OSThreadQueue queue[4 / sizeof(OSThreadQueue)];
#else
    OSThreadQueue queue[1];
#endif

/* private: (except direct operation with FSArchive) */

    /* handle property */
    union
    {
        /* file-handle property */
        struct
        {
            u32     own_id;            /* own file-id */
            u32     top;               /* image-top */
            u32     bottom;            /* image-bottom */
            u32     pos;               /* current position */
        }
        file;
        /* directory-handle property */
        struct
        {
            FSDirPos pos;              /* current-directory-position */
            u32     parent;            /* parent directory-id */
        }
        dir;
    }
    prop;

    /* command argument and return value area */
    union
    {
        FSReadFileInfo readfile;
        FSWriteFileInfo writefile;

        FSSeekDirInfo seekdir;
        FSReadDirInfo readdir;
        FSFindPathInfo findpath;
        FSGetPathInfo getpath;
        FSOpenFileFastInfo openfilefast;
        FSOpenFileDirectInfo openfiledirect;
        FSCloseFileInfo closefile;
    }
    arg;

}
FSFile;


/*****************************************************************************/
/* function */

/*---------------------------------------------------------------------------*
  Name:         FS_Init

  Description:  Initialize FS system

  Arguments:    default_dma_no   default DMA channel for FS
                                 if out of range(0-3),
                                 use CpuCopy instead of DMA.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_Init(u32 default_dma_no);

/*---------------------------------------------------------------------------*
  Name:         FS_IsAvailable

  Description:  check if file-system is ready

  Arguments:    None.

  Returns:      If file-system is ready, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_IsAvailable(void);

/*---------------------------------------------------------------------------*
  Name:         FS_End

  Description:  Finalize file-system.
                unload and unregister all the archives.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_End(void);

/*---------------------------------------------------------------------------*
  Name:         FS_GetDefaultDMA

  Description:  get default DMA channel

  Arguments:    None.

  Returns:      current DMA channel.
 *---------------------------------------------------------------------------*/
u32     FS_GetDefaultDMA(void);

/*---------------------------------------------------------------------------*
  Name:         FS_SetDefaultDMA

  Description:  set default DMA channel

  Arguments:    dma_no      default dma channel for FS
                            if out of range(0-3),
                            use CpuCopy instead of DMA.

  Returns:      previous DMA channel.
 *---------------------------------------------------------------------------*/
u32     FS_SetDefaultDMA(u32 dma_no);

/*---------------------------------------------------------------------------*
  Name:         FS_TryLoadTable

  Description:  preload FAT and FNT tables of file-system.
                if specified size is enough to load tables, load it to p_mem.
                then, all the operation using FAT and FNT is with p_mem.

  Arguments:    p_mem       buffer to preload
                size        byte length of p_mem

  Returns:      true size of memory for FAT and FNT.
 *---------------------------------------------------------------------------*/
u32     FS_TryLoadTable(void *p_mem, u32 size);

/*---------------------------------------------------------------------------*
  Name:         FS_GetTableSize

  Description:  get size of memory for FAT and FNT.

  Arguments:    None.

  Returns:      size of memory for FAT and FNT.
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetTableSize(void)
{
    return FS_TryLoadTable(NULL, 0);
}

/*---------------------------------------------------------------------------*
  Name:         FS_LoadTable

  Description:  preload FAT and FNT tables of file-system.
                if specified size is enough to load tables, load it to p_mem.
                then, all the operation using FAT and FNT is with p_mem.

  Arguments:    p_mem       buffer to preload
                size        byte length of p_mem

  Returns:      if preload is succeeded, return TRUE.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_LoadTable(void *p_mem, u32 size)
{
    return (FS_TryLoadTable(p_mem, size) <= size) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_UnloadTable

  Description:  release attached memory for preloading FAT and FNT tables.

  Arguments:    None.

  Returns:      released memory which user specified.
 *---------------------------------------------------------------------------*/
static inline void *FS_UnloadTable(void)
{
    FSArchive *const p_arc = FS_FindArchive("rom", 3);
    return FS_UnloadArchiveTables(p_arc);
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsBusy

  Description:  check if file is busy for asynchronous operation

  Arguments:    p_file      pointer to FSFile

  Returns:      If busy, True.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsBusy(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_BUSY) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsCanceling

  Description:  check if file is canceling last asynchronous operation

  Arguments:    p_file      pointer to FSFile

  Returns:      If canceling, True.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsCanceling(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_CANCEL) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsSucceeded

  Description:  check if last asynchronous operation is succeeded

  Arguments:    p_file      pointer to FSFile

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsSucceeded(volatile const FSFile *p_file)
{
    return (p_file->error == FS_RESULT_SUCCESS) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsFile

  Description:  check if file is now opened as a file-handle

  Arguments:    p_file      pointer to FSFile

  Returns:      If file-handle, True.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsFile(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_IS_FILE) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsDir

  Description:  check if file is now opened as a directory-position

  Arguments:    p_file      pointer to FSFile

  Returns:      If directory-position, True.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsDir(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_IS_DIR) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsFileSyncMode

  Description:  check if file is in synchronous mode.
                if synchronous mode, command is running in caller's thread.
                else, command is running in FS_NotifyArchiveAsyncEnd().
                this is used for optimized implementation of the archive.

  Arguments:    p_file      pointer to FSFile

  Returns:      If in synchronous mode, True.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsFileSyncMode(const volatile FSFile *p)
{
    return (p->stat & FS_FILE_STATUS_SYNC) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetResultCode

  Description:  get result code of latest command.
                during command operation, result is unfixed.

  Arguments:    p_file      pointer to FSFile

  Returns:      result code of latest command.
 *---------------------------------------------------------------------------*/
static inline FSResult FS_GetResultCode(volatile const FSFile *p_file)
{
    return p_file->error;
}

/*---------------------------------------------------------------------------*
  Name:         FS_InitFile

  Description:  initialize FSFile object

  Arguments:    p_file      pointer to FSFile to be initialized

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_InitFile(FSFile *p_file);

/*---------------------------------------------------------------------------*
  Name:         FS_OpenFile

  Description:  Open file with path-name

  Arguments:    p_file      pointer to FSFile to be opened
                path        relative or absolute path-name

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_OpenFile(FSFile *p_file, const char *path);

/*---------------------------------------------------------------------------*
  Name:         FS_OpenFileFast

  Description:  Open file with file id.

  Arguments:    p_file      pointer to FSFile to be opened
                file_id     file id (by FS_ReadDir)

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_OpenFileFast(FSFile *p_file, FSFileID file_id);

/*---------------------------------------------------------------------------*
  Name:         FS_ConvertPathToFileID

  Description:  get file id with path-name

  Arguments:    p_file_id   destination pointer to FSFileID
                path        relative or absolute path-name

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_ConvertPathToFileID(FSFileID *p_file_id, const char *path);

/*---------------------------------------------------------------------------*
  Name:         FS_CloseFile

  Description:  Close FSFile object

  Arguments:    p_file      pointer to FSFile to be closed

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_CloseFile(FSFile *p_file);

/*---------------------------------------------------------------------------*
  Name:         FS_GetPathName

  Description:  get full path name of file or directory.

  Arguments:    p_file      FSFileID of file or directory
                buf         destination buffer
                len         max length of buf

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_GetPathName(FSFile *p_file, char *buf, u32 len);

/*---------------------------------------------------------------------------*
  Name:         FS_GetPathLength

  Description:  get full path length of file or directory
                it includes '\0'

  Arguments:    p_file      FSFileID of file or directory

  Returns:      If succeeded, path length. If failed, -1.
 *---------------------------------------------------------------------------*/
s32     FS_GetPathLength(FSFile *p_file);

/*---------------------------------------------------------------------------*
  Name:         FS_GetLength

  Description:  Get length of opened FSFile

  Arguments:    p_file      pointer to FSFile

  Returns:      byte length of file.
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetLength(const FSFile *p_file)
{
    return p_file->prop.file.bottom - p_file->prop.file.top;
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetPosition

  Description:  Get seek-position of opened FSFile

  Arguments:    p_file      pointer to FSFile

  Returns:      byte position of file.
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetPosition(const FSFile *p_file)
{
    return p_file->prop.file.pos - p_file->prop.file.top;
}

/*---------------------------------------------------------------------------*
  Name:         FS_ReadFile

  Description:  read data from FSFile

  Arguments:    p_file      pointer to FSFile
                dst         pointer to destination buffer
                len         read size

  Returns:      If succeeded, read size. If failed, -1.
 *---------------------------------------------------------------------------*/
s32     FS_ReadFile(FSFile *p_file, void *dst, s32 len);

/*---------------------------------------------------------------------------*
  Name:         FS_ReadFileAsync

  Description:  Read data from FSFile and return without no blocking

  Arguments:    p_file      pointer to FSFile
                dst         pointer to destination buffer
                len         read size

  Returns:      If succeeded, read size. If failed, -1.
 *---------------------------------------------------------------------------*/
s32     FS_ReadFileAsync(FSFile *p_file, void *dst, s32 len);

/*---------------------------------------------------------------------------*
  Name:         FS_WriteFile

  Description:  write data to FSFile

  Arguments:    p_file      pointer to FSFile
                src         pointer to source buffer
                len         written size

  Returns:      If succeeded, written size. If failed, -1.
 *---------------------------------------------------------------------------*/
s32     FS_WriteFile(FSFile *p_file, const void *src, s32 len);

/*---------------------------------------------------------------------------*
  Name:         FS_WriteFileAsync

  Description:  Write data to FSFile and return without no blocking

  Arguments:    p_file      pointer to FSFile
                src         pointer to source buffer
                len         write size

  Returns:      If succeeded, written size. If failed, -1.
 *---------------------------------------------------------------------------*/
s32     FS_WriteFileAsync(FSFile *p_file, const void *src, s32 len);

/*---------------------------------------------------------------------------*
  Name:         FS_WaitAsync

  Description:  wait for end of asynchronous function and return result.

  Arguments:    file to wait

  Returns:      if succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_WaitAsync(FSFile *p_file);

/*---------------------------------------------------------------------------*
  Name:         FS_CancelFile

  Description:  send request to cancel asynchronous function

  Arguments:    file to cancel

  Returns:      none.
 *---------------------------------------------------------------------------*/
void    FS_CancelFile(FSFile *p_file);

/*---------------------------------------------------------------------------*
  Name:         FS_SeekFile

  Description:  move seek-pointer of FSFile

  Arguments:    p_file      pointer to FSFile
                offset      move offset
                origin      base position for offset

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_SeekFile(FSFile *p_file, s32 offset, FSSeekFileMode origin);

/*---------------------------------------------------------------------------*
  Name:         FS_SeekFileToBegin

  Description:  move seek-pointer of FSFile, to starting position

  Arguments:    p_file      pointer to FSFile

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_SeekFileToBegin(FSFile *p_file)
{
    return FS_SeekFile(p_file, 0, FS_SEEK_SET);
}

/*---------------------------------------------------------------------------*
  Name:         FS_SeekFileToEnd

  Description:  move seek-pointer of FSFile, to end of file

  Arguments:    p_file      pointer to FSFile

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_SeekFileToEnd(FSFile *p_file)
{
    return FS_SeekFile(p_file, 0, FS_SEEK_END);
}

/*---------------------------------------------------------------------------*
  Name:         FS_ChangeDir

  Description:  change current directory

  Arguments:    path        relative or absolute directory-name

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_ChangeDir(const char *path);

/*---------------------------------------------------------------------------*
  Name:         FS_FindDir

  Description:  find directory and seek there

  Arguments:    p_dir       pointer to FSFile
                path        relative or absolute directory-name

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_FindDir(FSFile *p_dir, const char *path);

/*---------------------------------------------------------------------------*
  Name:         FS_ReadDir

  Description:  read 1 FSDirEntry information from directory and step to next

  Arguments:    p_dir       pointer to FSFile
                p_entry     pointer to destination FSDirEntry

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_ReadDir(FSFile *p_dir, FSDirEntry *p_entry);

/*---------------------------------------------------------------------------*
  Name:         FS_TellDir

  Description:  get directory position

  Arguments:    p_dir       pointer to FSFile
                p_pos       pointer to destination FSDirPos

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_TellDir(const FSFile *p_dir, FSDirPos *p_pos);

/*---------------------------------------------------------------------------*
  Name:         FS_SeekDir

  Description:  set FSFile to specified directory position

  Arguments:    p_dir       pointer to FSFile
                p_pos       directory position(by FS_ReadDir, FS_TellDir)

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_SeekDir(FSFile *p_dir, const FSDirPos *p_pos);

/*---------------------------------------------------------------------------*
  Name:         FS_RewindDir

  Description:  set FSFile to starting position

  Arguments:    p_dir       pointer to FSFile

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_RewindDir(FSFile *p_dir);

/*---------------------------------------------------------------------------*
  Name:         FS_OpenFileDirect

  Description:  open file directly by mapping information, without FAT.
                (for archive implements)

  Arguments:    p_file       pointer to FSFile
                p_arc        mapped archive
                image_top    top position of file image
                image_bottom bottom position of file image (last + 1)
                file_index   file index

  Returns:      If succeeded, True.
 *---------------------------------------------------------------------------*/
BOOL    FS_OpenFileDirect(FSFile *p_file, FSArchive *p_arc,
                          u32 image_top, u32 image_bottom, u32 file_index);

/*---------------------------------------------------------------------------*
  Name:         FS_GetAttachedArchive

  Description:  get the pointer to archive
                which is attached to specified file

  Arguments:    p_file      pointer to FSFile

  Returns:      If attached, pointer to archive. If failed, NULL.
 *---------------------------------------------------------------------------*/
static inline FSArchive *FS_GetAttachedArchive(const FSFile *p_file)
{
    return p_file->arc;
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetFileImageTop

  Description:  get top position of file image as offset from archive base

  Arguments:    p_file      pointer to FSFile

  Returns:      If p_file is file, top of file image.
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetFileImageTop(const FSFile *p_file)
{
    return p_file->prop.file.top;
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetFileImageBottom

  Description:  get bottom position of file image as offset from archive base

  Arguments:    p_file      pointer to FSFile

  Returns:      If p_file is file, top of file image.
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetFileImageBottom(const FSFile *p_file)
{
    return p_file->prop.file.bottom;
}

/*---------------------------------------------------------------------------*
  Name:         FS_CreateFileFromRom

  Description:  Temporarily generates a file that maps the specified CARD-ROM area.

  Arguments:    p_file          FSFile structure that stores file handle
                offset          Offset from start of CARD-ROM region for the read
                size            Size in bytes of the target region from the offset

  Returns:      None.
 *---------------------------------------------------------------------------*/
BOOL    FS_CreateFileFromRom(FSFile *p_file, u32 offset, u32 size);

/*---------------------------------------------------------------------------*
  Name:         FS_CreateFileFromMemory

  Description:  Temporarily generates file that maps memory region

  Arguments:    p_file          FSFile structure that stores file handle
                buf             Memory that is target of READ and WRITE
                size            Byte size of buf

  Returns:      None.
 *---------------------------------------------------------------------------*/
BOOL    FS_CreateFileFromMemory(FSFile *p_file, void *buf, u32 size);


/* obsolete function *********************************************************/

/*---------------------------------------------------------------------------*
  Name:         FS_CreateReadServerThread

  Description:  create a background thread of
                OS_SleepThread() and FS_ReadServer().

  Arguments:    priority      thread priority

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void FS_CreateReadServerThread(u32 priority)
{
    (void)CARD_SetThreadPriority(priority);
}


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* NITRO_FS_FILE_H_ */

/*---------------------------------------------------------------------------*
  $Log: file.h,v $
  Revision 1.38  01/18/2006 02:11:19  kitase_hirotake
  do-indent

  Revision 1.37  06/28/2005 11:30:31  yosizaki
  add FS_CreateFileFromMemory(), FS_CreateFileFromRom().

  Revision 1.36  06/28/2005 09:49:44  yada
  applied for SDK_THREAD_INFINITY

  Revision 1.35  06/17/2005 13:08:04  yosizaki
  fix FS_WaitAsync. (add FS_FILE_STATUS_OPERATING)

  Revision 1.34  05/30/2005 04:21:12  yosizaki
  add FS_End().
  add comments.

  Revision 1.33  04/18/2005 02:48:43  yosizaki
  change FS_CreateReadServerThread() to inline-function.

  Revision 1.32  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.31  01/24/2005 06:34:45  yosizaki
  Revised copyright year notation

  Revision 1.30  01/19/2005 11:25:36  yosizaki
  delete pragma `pack'.

  Revision 1.29  11/02/2004 10:07:57  yosizaki
  fix typo.

  Revision 1.28  09/24/2004 13:07:14  yosizaki
  fix FS_UnloadTable.

  Revision 1.27  09/24/2004 12:08:05  yosizaki
  add FS_UnloadTable.

  Revision 1.26  07/27/2004 06:47:07  yosizaki
  small fix (warning "padding inserted")

  Revision 1.25  07/19/2004 13:11:44  yosizaki
  add FS_IsFileSyncMode.
  add FS_GetResultCode.
  delete FS_ReadServer.

  Revision 1.24  07/13/2004 02:54:44  yosizaki
  add FS_CancelFile.

  Revision 1.23  07/12/2004 13:05:10  yosizaki
  change FS_COMMAND_READFILE & FS_COMMAND_WRITEFILE (add argument)

  Revision 1.22  07/08/2004 13:46:28  yosizaki
  move some functions to card/rom.h

  Revision 1.21  07/01/2004 09:41:50  yasu
  support autoload

  Revision 1.20  06/30/2004 04:30:15  yosizaki
  add new command 'FINDPATH'.

  Revision 1.19  06/11/2004 05:42:32  yosizaki
  extern .

  Revision 1.18  06/03/2004 13:32:53  yosizaki
  fix around archive asynchronous operation.

  Revision 1.17  06/01/2004 10:17:23  yosizaki
  add FS_OpenFileDirect(). (private)

  Revision 1.16  05/20/2004 06:30:33  yosizaki
  add FS_ConvertPathToFileID.
  add some structure for archive.

  Revision 1.15  05/19/2004 02:30:34  yosizaki
  add FS_GetPathName().
  add comment.

  Revision 1.14  05/17/2004 08:31:22  yosizaki
  add comment.

  Revision 1.13  05/11/2004 09:35:55  yosizaki
  add FS_CreateReadServerThread().

  Revision 1.12  05/11/2004 04:33:17  yosizaki
  change format of FSDirPos and FSFileID.
  change archive system.

  Revision 1.11  05/10/2004 06:24:32  yosizaki
  add FS_ReadFileAsync, FS_WriteFile, FS_WriteFileAsync.

  Revision 1.10  05/01/2004 03:26:58  yosizaki
  u32 FSFile::arc_id -> void *FSFile::arc.
  change PXI protocol.

  Revision 1.9  04/22/2004 02:31:11  yosizaki
  FS_LoadTables() -> FS_TryLoadTable().
  add FS_LoadTable().
  add FS_GetTableSize().

  Revision 1.8  04/15/2004 11:39:45  yosizaki
  support CARD-on-TEG. (but CARD access routine is extern)
  add FSi_ReadServer().

  Revision 1.7  04/15/2004 00:06:27  yosizaki
  add FSi_Load Archive().
  add FSi_LoadArchiveTables().
  add FS_LoadTables().
  add FS_GetDefaultDMA().

  Revision 1.6  04/13/2004 12:16:19  yosizaki
  fix header comment.
  add FS_IsAvailable.
  change FS_SetDefaultDMA.
  add archive selector system (internal).

  Revision 1.5  04/08/2004 10:46:48  yosizaki
  change FSDir to FSFile
  add FS_SetDefaultDMA()

  Revision 1.4  04/06/2004 11:59:18  yosizaki
  fix FS_SeekDir()

  Revision 1.3  04/06/2004 06:59:12  yosizaki
  change FS_Init()
  change around FSOverlayID

  Revision 1.2  04/05/2004 02:50:07  yosizaki
  change argtype of FSLoadOverlay()

  Revision 1.1  04/01/2004 09:30:45  yosizaki
  (none)


  $NoKeywords: $
 *---------------------------------------------------------------------------*/
