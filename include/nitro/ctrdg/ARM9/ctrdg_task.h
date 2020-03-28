/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CTRDG - include
  File:     ctrdg_task.h

  Copyright 2006,2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: ctrdg_task.h,v $
  Revision 1.3  2007/02/20 00:28:11  kitase_hirotake
  indent source

  Revision 1.2  2006/04/07 03:28:00  okubata_ryoma
  the CTRDG_SetTaskThreadPriority function was published, and thread priorities were changed

  Revision 1.1  2006/04/05 10:34:15  okubata_ryoma
  changes made for AGB backup library's SDK collection


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef	NITRO_CTRDG_TASK_H_
#define	NITRO_CTRDG_TASK_H_

#include "nitro.h"

/* task thread priority level */
#define CTRDG_TASK_PRIORITY_DEFAULT 20 // enables the creation of multiple threads between the task and main threads, with lower priorities than that of the main thread

/* the task thread stack size */
#define CTRDG_TASK_STACK_SIZE 1024

struct CTRDGTaskInfo_tag;

// the argument declares a CTRDGTaskInfo_tag function pointer
typedef u32 (*CTRDG_TASK_FUNC) (struct CTRDGTaskInfo_tag *);

/*
 * Task information structure requested in task thread.
 */
typedef struct CTRDGTaskInfo_tag
{
    // TRUE in the interval between leaving the standby loop awaiting a task in the task list for the waiting thread and the task's completion
    CTRDG_TASK_FUNC task;              /* task function */
    CTRDG_TASK_FUNC callback;          /* callback */
    u32     result;                    /* the task function's return value */
    u8     *data;                      /* only the program command for the data to be written can be used */
    u8     *adr;                       /* the address of the data to be read/written */
    u32     offset;                    /* the offset, in bytes, within the sector */
    u32     size;                      /* size */
    u8     *dst;                       /* the address of the work region where the read data is stored */
    u16     sec_num;                   /* the sector number */
    u8      busy;                      /* if now processing */
    u8      param[1];                  /* user-defined argument and return-value */
}
CTRDGTaskInfo;

typedef struct
{
    OSThread th[1];                    /* thread context */
    CTRDGTaskInfo *volatile list;      /* waiting task list */
    CTRDGTaskInfo end_task;            /* task structure for end-command */
}
CTRDGiTaskWork;

/*---------------------------------------------------------------------------*
  Name:         CTRDGi_InitTaskThread

  Description:  Starts task thread.
                
  Arguments:    p_work     Buffer for internal work.
                           Used internally until CTRDGi_EndTaskThread() completes.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CTRDGi_InitTaskThread(void *p_work);

/*---------------------------------------------------------------------------*
  Name:         CTRDGi_IsTaskAvailable

  Description:  Checks if task thread is currently available.
                
  Arguments:    None.

  Returns:      Returns TRUE if curently available. Otherwise returns FALSE.
 *---------------------------------------------------------------------------*/
BOOL    CTRDGi_IsTaskAvailable(void);

/*---------------------------------------------------------------------------*
  Name:         CTRDGi_InitTaskInfo

  Description:  Initializes task information structure.
                Must be called once before using.

  Arguments:    pt         uninitialized task information structure

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CTRDGi_InitTaskInfo(CTRDGTaskInfo * pt);

/*---------------------------------------------------------------------------*
  Name:         CTRDGi_IsTaskBusy

  Description:  Checks if task information is currently being used.
                
  Arguments:    pt         task information

  Returns:      Returns TRUE if currently being used. Otherwise returns FALSE.
 *---------------------------------------------------------------------------*/
BOOL    CTRDGi_IsTaskBusy(volatile const CTRDGTaskInfo * pt);

/*---------------------------------------------------------------------------*
  Name:         CTRDGi_SetTask

  Description:  Adds task to internal thread.
                
  Arguments:    pt         currently unused task information
                task       task function
                callback   callback when task completes (ignored if NULL)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CTRDGi_SetTask(CTRDGTaskInfo * pt, CTRDG_TASK_FUNC task, CTRDG_TASK_FUNC callback);

/*---------------------------------------------------------------------------*
  Name:         CTRDGi_EndTaskThread

  Description:  Ends task thread.
                
  Arguments:    callback   callback when task thread ends (ignored if NULL)
                           This callback is called in the state just before the task thread ends, while
                           interrupts are prohibited.
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CTRDGi_EndTaskThread(CTRDG_TASK_FUNC callback);

/*---------------------------------------------------------------------------*
  Name:         CTRDG_SetTaskThreadPriority

  Description:  Changes the task thread's priority.
                
  Arguments:    priority    the task thread's priority
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CTRDG_SetTaskThreadPriority(u32 priority);

#endif /* NITRO_CTRDG_TASK_H_ */
