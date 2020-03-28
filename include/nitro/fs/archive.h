/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FS - libraries
  File:     archive.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/


#if	!defined(NITRO_FS_ARCHIVE_H_)
#define NITRO_FS_ARCHIVE_H_

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/os/common/thread.h"


#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************/
/* constant */

enum
{
    /* Maximum archive name length */
    FS_ARCHIVE_NAME_LEN_MAX = 3
};

/*
 * Archive internal status flag (for inline functions)
 * The user does not directly use these constants.
 */
#define	FS_ARCHIVE_FLAG_REGISTER	0x00000001
#define	FS_ARCHIVE_FLAG_LOADED		0x00000002
#define	FS_ARCHIVE_FLAG_TABLE_LOAD	0x00000004
#define	FS_ARCHIVE_FLAG_SUSPEND		0x00000008
#define	FS_ARCHIVE_FLAG_RUNNING		0x00000010
#define	FS_ARCHIVE_FLAG_CANCELING	0x00000020
#define	FS_ARCHIVE_FLAG_SUSPENDING	0x00000040
#define	FS_ARCHIVE_FLAG_UNLOADING	0x00000080
#define	FS_ARCHIVE_FLAG_IS_ASYNC	0x00000100
#define	FS_ARCHIVE_FLAG_IS_SYNC		0x00000200

/*
 * To implement the archive, FSArchive::flag can define and use the following bit areas freely.
 * 
 */
#define	FS_ARCHIVE_FLAG_USER_RESERVED_BIT	0x00010000
#define	FS_ARCHIVE_FLAG_USER_RESERVED_MASK	0xFFFF0000

/*
 * File command and archive messages.
 * Used in user procedure during archive implementation.
 */
typedef enum
{
    /* Asynchronous commands */
    FS_COMMAND_ASYNC_BEGIN = 0,
    FS_COMMAND_READFILE = FS_COMMAND_ASYNC_BEGIN,
    FS_COMMAND_WRITEFILE,
    FS_COMMAND_ASYNC_END,

    /* Synchronous commands */
    FS_COMMAND_SYNC_BEGIN = FS_COMMAND_ASYNC_END,
    FS_COMMAND_SEEKDIR = FS_COMMAND_SYNC_BEGIN,
    FS_COMMAND_READDIR,
    FS_COMMAND_FINDPATH,
    FS_COMMAND_GETPATH,
    FS_COMMAND_OPENFILEFAST,
    FS_COMMAND_OPENFILEDIRECT,
    FS_COMMAND_CLOSEFILE,
    FS_COMMAND_SYNC_END,

    /* Archive messages */
    FS_COMMAND_STATUS_BEGIN = FS_COMMAND_SYNC_END,
    FS_COMMAND_ACTIVATE = FS_COMMAND_STATUS_BEGIN,
    FS_COMMAND_IDLE,
    FS_COMMAND_SUSPEND,
    FS_COMMAND_RESUME,
    FS_COMMAND_STATUS_END,

    FS_COMMAND_INVALID
}
FSCommandType;

/*
 * User procedure setting flag.
 * Specify with argument "flags" of FS_SetArchiveProc().
 *  Enable bits for only those that require callbacks.
 */

/* Asynchronous commands */
#define	FS_ARCHIVE_PROC_READFILE		(1 << FS_COMMAND_READFILE)
#define	FS_ARCHIVE_PROC_WRITEFILE		(1 << FS_COMMAND_WRITEFILE)
        /* All asynchronous commands */
#define	FS_ARCHIVE_PROC_ASYNC	\
	(FS_ARCHIVE_PROC_READFILE | FS_ARCHIVE_PROC_WRITEFILE)

/* Synchronous commands */
#define	FS_ARCHIVE_PROC_SEEKDIR			(1 << FS_COMMAND_SEEKDIR)
#define	FS_ARCHIVE_PROC_READDIR			(1 << FS_COMMAND_READDIR)
#define	FS_ARCHIVE_PROC_FINDPATH		(1 << FS_COMMAND_FINDPATH)
#define	FS_ARCHIVE_PROC_GETPATH			(1 << FS_COMMAND_GETPATH)
#define	FS_ARCHIVE_PROC_OPENFILEFAST	(1 << FS_COMMAND_OPENFILEFAST)
#define	FS_ARCHIVE_PROC_OPENFILEDIRECT	(1 << FS_COMMAND_OPENFILEDIRECT)
#define	FS_ARCHIVE_PROC_CLOSEFILE		(1 << FS_COMMAND_CLOSEFILE)
        /* All synchronous commands */
#define	FS_ARCHIVE_PROC_SYNC	\
	(FS_ARCHIVE_PROC_SEEKDIR | FS_ARCHIVE_PROC_READDIR |	\
	 FS_ARCHIVE_PROC_FINDPATH | FS_ARCHIVE_PROC_GETPATH |	\
	FS_ARCHIVE_PROC_OPENFILEFAST | FS_ARCHIVE_PROC_OPENFILEDIRECT | FS_ARCHIVE_PROC_CLOSEFILE)

/* Messages when status changes */
#define	FS_ARCHIVE_PROC_ACTIVATE		(1 << FS_COMMAND_ACTIVATE)
#define	FS_ARCHIVE_PROC_IDLE			(1 << FS_COMMAND_IDLE)
#define	FS_ARCHIVE_PROC_SUSPENDING		(1 << FS_COMMAND_SUSPEND)
#define	FS_ARCHIVE_PROC_RESUME			(1 << FS_COMMAND_RESUME)
        /* All messages when status changes */
#define	FS_ARCHIVE_PROC_STATUS	\
	(FS_ARCHIVE_PROC_ACTIVATE | FS_ARCHIVE_PROC_IDLE |	\
	 FS_ARCHIVE_PROC_SUSPENDING | FS_ARCHIVE_PROC_RESUME)

/* All messages */
#define	FS_ARCHIVE_PROC_ALL	(~0)

typedef enum
{
    /****************************************************************
	 * User error codes
	 * Get with FS_GetErrorCode().
	 ****************************************************************/

    /*
     * Indicates success as the result of correct processing.
     * For example, even if you attempted to read 100 bytes and only 50 bytes were read because the end was reached, the process would be treated as "successful."
     * 
     * 
     */
    FS_RESULT_SUCCESS = 0,

    /*
     * Indicates failure as the result of correct processing.
     * Refers to a failure that is within the acceptable range of processing, such as reading a termination with ReadDir.
     * 
     */
    FS_RESULT_FAILURE,

    /*
     * Indicates that a command is currently being processed.
     * Since the command is not completed, this is not strictly an error.
     */
    FS_RESULT_BUSY,

    /*
     * Indicates that the command was cancelled.
     * It could be cancelled explicitly by the user,
     * or cancelled forcibly during archive unloading.
     */
    FS_RESULT_CANCELED,
    FS_RESULT_CANCELLED = FS_RESULT_CANCELED,

    /*
     * Indicates that the archive does not support the specified command.
     * This error is issued by an archive that goes so far as to ignore a command, and the user should find out the particular specifications of the target archive.
     * 
     */
    FS_RESULT_UNSUPPORTED,

    /*
     * Indicates failure from an error in the file system or archive.
     */
    FS_RESULT_ERROR,

    /****************************************************************
	 * Procedure level error codes
	 * Returned by the user procedure. Not included in FS_GetErrorCode().
	 ****************************************************************/

    /*
     * Returns control for now because the command processing is done asynchronously.
     * If this value is returned, completion must be acknowledged with FS_NotifyArchiveAsyncEnd(), just as with a read/write callback.
     * 
     */
    FS_RESULT_PROC_ASYNC,

    /*
     * At least this time, leave it to the default process.
     * Next time, a user procedure to the relevant command will be called.
     * Returned each time you want to simply hook a command etc.
     */
    FS_RESULT_PROC_DEFAULT,

    /*
     * Will give this command over to the default process this time and each time hereafter.
     * Cancels the flag that calls procedure to the relevant command, and
     * will not be called from the next time.
     */
    FS_RESULT_PROC_UNKNOWN
}
FSResult;


/*****************************************************************************/
/* declaration */

struct FSFile;
struct FSFileLink;
struct FSArchiveFAT;
struct FSArchiveFNT;
struct FSArchive;

/*
 * User Procedure
 * Set by the user to customize the archive.
 */
typedef FSResult (*FS_ARCHIVE_PROC_FUNC) (struct FSFile *, FSCommandType);

/*
 * Read/Write access callback
 *
 * If access completes during the call, it must return FS_RESULT_SUCCESS.
 * If async. or other processing continues, FS_RESULT_PROC_ASYNC is returned and
 * FS_NotifyArchiveAsyncEnd() must be called at completion.
 *
 * All command default processing is realized by using this callback
 * to access FAT/FNT/file images.
 * Conversely, these callbacks will not be called if all necessary commands are overridden properly
 * in the process within the user procedure.
 */
typedef FSResult (*FS_ARCHIVE_READ_FUNC) (struct FSArchive *p, void *dst, u32 pos, u32 size);
typedef FSResult (*FS_ARCHIVE_WRITE_FUNC) (struct FSArchive *p, const void *src, u32 pos, u32 size);

/*
 * The following structures are released for the convenience of archive implementers.
 * They are not needed directly in the file system API.
 */

typedef struct FSFileLink
{
    struct FSFile *prev;
    struct FSFile *next;
}
FSFileLink;

typedef struct FSArchiveFAT
{
    u32     top;
    u32     bottom;
}
FSArchiveFAT;

typedef struct FSArchiveFNT
{
    u32     start;
    u16     index;
    u16     parent;
}
FSArchiveFNT;

/*
 * Archive structure
 * The archive implementer creates an entity of the structure. Then:
 *
 * (1) Initialize with FS_InitArchive()
 * (2) Register the name with FS_RegisterArchiveName()
 * (3) Load the archive into the system with FS_LoadArchive().
 *
 * With this procedure, you can add an archive to the file system.
 * If the archive is dynamic:
 *
 * (4) Unload the archive from the system with FS_UnloadArchive()
 *
 * Then, the archive is released and it can be used again.
 * If you want to change an archive name dynamically:
 *
 * (5) Release the name with FS_ReleaseArchiveName()
 *
 * And then you can repeat the process from (2) onward.
 */

typedef struct FSArchive
{
/* private: */

    /* Variables for file system management */
    union
    {
        /* A unique name to identify the archive.
           A name of 1-3 alphanumeric chars. Not case sensitive. */
        char    ptr[FS_ARCHIVE_NAME_LEN_MAX + 1];
        u32     pack;
    }
    name;
    /* System's internal archive linked list */
    struct FSArchive *next;
    struct FSArchive *prev;

    /* Variables for managing command process status. */
    OSThreadQueue sync_q;              /* Synchronous processes (SeekDir etc) */
    OSThreadQueue stat_q;              /* Status changes (Suspend etc) */
    u32     flag;                      /* Internal status flags (FS_ARCHIVE_FLAG_*) */

    FSFileLink list;                   /* Process wait command list */

    /* Types of offset that complies with ROM file format */
    u32     base;                      /* Base offset */
    u32     fat;                       /* FAT offset */
    u32     fat_size;                  /* FAT size */
    u32     fnt;                       /* FNT offset */
    u32     fnt_size;                  /* FNT size */
    u32     fat_bak;                   /* FAT base offset before preload */
    u32     fnt_bak;                   /* FNT base offset before preload */
    void   *load_mem;                  /* Memory of loaded table */

    /* Base operation callback */
    FS_ARCHIVE_READ_FUNC read_func;
    FS_ARCHIVE_WRITE_FUNC write_func;

    /* Internal callback for table access.
       (Because it does not use FS_IsArchiveTableLoaded() internally each time) */
    FS_ARCHIVE_READ_FUNC table_func;

    /* User procedures (FS_ARCHIVE_PROC_*) */
    FS_ARCHIVE_PROC_FUNC proc;
    u32     proc_flag;

}
FSArchive;


/*****************************************************************************/
/* function */

/*---------------------------------------------------------------------------*
  Name:         FS_InitArchive

  Description:  Initializes the archive structure.

  Arguments:    p_arc          Archive to initialize.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_InitArchive(FSArchive *p_arc);

/*---------------------------------------------------------------------------*
  Name:         FS_GetArchiveName

  Description:  Gets archive name

  Arguments:    p_arc            Archive whose name to get.

  Returns:      Archive name registered in the file system
 *---------------------------------------------------------------------------*/
static inline const char *FS_GetArchiveName(const FSArchive *p_arc)
{
    return p_arc->name.ptr;
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetArchiveBase

  Description:  Gets the archive's base offset.

  Arguments:    p_arc            Archive for which base offset will be obtained.

  Returns:      The archive's base offset
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetArchiveBase(const FSArchive *p_arc)
{
    return p_arc->base;
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetArchiveFAT

  Description:  Gets the archive's FAT offset.

  Arguments:    p_arc           Archive for which FAT offset is obtained.

  Returns:      The archive's FAT offset
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetArchiveFAT(const FSArchive *p_arc)
{
    return p_arc->fat;
}

/*---------------------------------------------------------------------------*
  Name:         FS_GetArchiveFNT

  Description:  Gets the archive's FNT offset

  Arguments:    p_arc           Archive for which FNT offset is obtained.

  Returns:      The archive's FNT offset
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetArchiveFNT(const FSArchive *p_arc)
{
    return p_arc->fnt;
}

/* Obtain specified position offset from the archive's base */
/*---------------------------------------------------------------------------*
  Name:         FS_GetArchiveOffset

  Description:  Obtains the specified position offset from the archive base

  Arguments:    p_arc            The archive.

  Returns:      Specified position offset with the archive base added
 *---------------------------------------------------------------------------*/
static inline u32 FS_GetArchiveOffset(const FSArchive *p_arc, u32 pos)
{
    return p_arc->base + pos;
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsArchiveLoaded

  Description:  Determines whether the archive is completely loaded into the current file system.

  Arguments:    p_arc            Archive to determine.

  Returns:      If loaded into the file system, TRUE.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsArchiveLoaded(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_LOADED) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsArchiveTableLoaded

  Description:  Determines whether the archive has finished preloading the table.

  Arguments:    p_arc            Archive to determine.

  Returns:      If the table has been preloaded, TRUE.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsArchiveTableLoaded(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_TABLE_LOAD) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_IsArchiveSuspended

  Description:  Determines whether the archive is currently suspended.

  Arguments:    p_arc            Archive to determine.

  Returns:      If the archive is currently suspended, TRUE.
 *---------------------------------------------------------------------------*/
static inline BOOL FS_IsArchiveSuspended(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_SUSPEND) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         FS_FindArchive

  Description:  Searches for archive name.
                If there is no matching name, returns NULL.

  Arguments:    name             Character string of the archive name to search for
                name_len         Length of name string

  Returns:      Pointer to the archive that was found, or NULL.
 *---------------------------------------------------------------------------*/
FSArchive *FS_FindArchive(const char *name, int name_len);

/*---------------------------------------------------------------------------*
  Name:         FS_RegisterArchiveName

  Description:  Registers the archive name in the file system and associates it.
                The archive itself is not yet loaded into the file system.
                The archive name  "rom" is reserved by the file system.

  Arguments:    p_arc            Archive to associate with the name.
                name             String of the name to register
                name_len         Length of name string

  Returns:      None.
 *---------------------------------------------------------------------------*/
BOOL    FS_RegisterArchiveName(FSArchive *p_arc, const char *name, u32 name_len);

/*---------------------------------------------------------------------------*
  Name:         FS_ReleaseArchiveName

  Description:  Release registered archive names.
                They must be unloaded from the file system.

  Arguments:    p_arc            Archive with name to release.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_ReleaseArchiveName(FSArchive *p_arc);

/*---------------------------------------------------------------------------*
  Name:         FS_LoadArchive

  Description:  Loads the archive into the file system.
                Its name must already be registered on the archive list.

  Arguments:    p_arc            Archive to load
                base             Any u32 value that can be uniquely used.
                fat              Starting offset of the FAT table
                fat_size         Size of FAT table
                fat              Starting offset of the FNT table
                fat_size         Size of FNT table
                read_func        Read access callback.
                write_func       Write access callback

  Returns:      If archive is loaded correctly, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    FS_LoadArchive(FSArchive *p_arc, u32 base,
                       u32 fat, u32 fat_size, u32 fnt, u32 fnt_size,
                       FS_ARCHIVE_READ_FUNC read_func, FS_ARCHIVE_WRITE_FUNC write_func);

/*---------------------------------------------------------------------------*
  Name:         FS_UnloadArchive

  Description:  Unload the archive from the file system.
                Block until all currently running tasks are completed.

  Arguments:    p_arc          Archive to unload.

  Returns:      If archive is unloaded correctly, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    FS_UnloadArchive(FSArchive *p_arc);

/*---------------------------------------------------------------------------*
  Name:         FS_LoadArchiveTables

  Description:  Preload archive FAT + FNT in memory.
                Only if within specified size, execute the load and return the required size.

  Arguments:    p_arc            Archive that will preload table.
                p_mem            Storage destination buffer for table data
                max_size         p_mem size

  Returns:      Always returns the total table size.
 *---------------------------------------------------------------------------*/
u32     FS_LoadArchiveTables(FSArchive *p_arc, void *p_mem, u32 max_size);

/*---------------------------------------------------------------------------*
  Name:         FS_UnloadArchiveTables

  Description:  Releases the archive's preloaded memory.

  Arguments:    p_arc            Archive with preloaded memory to release.

  Returns:      Buffer given by the user as preloaded memory.
 *---------------------------------------------------------------------------*/
void   *FS_UnloadArchiveTables(FSArchive *p_arc);

/*---------------------------------------------------------------------------*
  Name:         FS_SuspendArchive

  Description:  Stops archive processing mechanism itself.
                If a process is currently executing, waits for it to complete.

  Arguments:    p_arc          Archive to suspend.

  Returns:      If it was not in a suspended state before the call, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    FS_SuspendArchive(FSArchive *p_arc);

/*---------------------------------------------------------------------------*
  Name:         FS_ResumeArchive

  Description:  Resume the suspended archive processing.

  Arguments:    p_arc            Archive to resume.

  Returns:      If it was not in a suspended state before the call, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    FS_ResumeArchive(FSArchive *p_arc);

/*---------------------------------------------------------------------------*
  Name:         FS_SetArchiveProc

  Description:  Sets the archive's user procedure.
                If proc == NULL or flags = 0,
                merely invalidates the user procedure.

  Arguments:    p_arc     Archive for which to set the user procedure.
                proc             User procedure.
                flags            Bit collection of commands that hook to procedures.

  Returns:      Always returns the total table size.
 *---------------------------------------------------------------------------*/
void    FS_SetArchiveProc(struct FSArchive *p_arc, FS_ARCHIVE_PROC_FUNC proc, u32 flags);

/*---------------------------------------------------------------------------*
  Name:         FS_NotifyArchiveAsyncEnd

  Description:  Call from the archive implementation side in order to notify that asynchronous archive processing is complete.
                

  Arguments:    p_arc           Archive for which to notify completion.
                ret              Processing result.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FS_NotifyArchiveAsyncEnd(FSArchive *p_arc, FSResult ret);

/*---------------------------------------------------------------------------*
  Name:         FSi_EndArchive

  Description:  End all archives and release.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    FSi_EndArchive(void);


/*****************************************************************************/


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* NITRO_FS_ARCHIVE_H_ */

/*---------------------------------------------------------------------------*
  $Log: archive.h,v $
  Revision 1.17  2007/08/24 04:34:29  okubata_ryoma
  Fix related to headerfiles.

  Revision 1.16  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.15  2005/09/02 08:28:29  yosizaki
  Added compatible symbol 'FS_RESULT_CANCELLED'

  Revision 1.14  2005/05/30 04:20:42  yosizaki
  Added FSi_EndArchive().
  Added comments.

  Revision 1.13  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.12  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.11  2004/11/02 10:07:49  yosizaki
  Fixed typo.

  Revision 1.10  2004/07/23 08:32:27  yosizaki
  Fixed command operation.

  Revision 1.9  2004/07/19 13:12:59  yosizaki
  Added all commands.

  Revision 1.8  2004/07/08 13:45:54  yosizaki
  Changed archive commands.

  Revision 1.7  2004/06/30 10:28:08  yosizaki
  Added comments.

  Revision 1.6  2004/06/30 04:30:46  yosizaki
  Implemented user-procedure system.

  Revision 1.5  2004/06/22 01:49:37  yosizaki
  Added user-procedure system (reserved).

  Revision 1.4  2004/06/03 13:32:53  yosizaki
  Fix related to archive asynchronous operation.

  Revision 1.3  2004/05/20 12:37:38  yosizaki
  Fixed FSFileLink definition.

  Revision 1.2  2004/05/20 06:30:33  yosizaki
  Added FS_ConvertPathToFileID.
  Added some structure for archive.

  Revision 1.1  2004/05/11 04:32:58  yosizaki
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
