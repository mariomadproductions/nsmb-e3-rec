/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     thread.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: thread.h,v $
  Revision 1.78  2006/08/16 01:45:16  yosizaki
  add OS_SleepThreadDirect

  Revision 1.77  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.76  2005/09/06 06:22:34  yada
  consider for const OSThread*.

  Revision 1.75  2005/08/09 09:00:10  yada
  change OSThread struct. (not to change struct size)

  Revision 1.74  2005/08/09 01:40:55  yada
  change argument of OS_SetThreadDestructorStack

  Revision 1.73  2005/08/08 11:25:46  yada
  able to specify thread destructor stack.
  cancel alarm for OS_Sleep when that thread exits.

  Revision 1.72  2005/07/19 07:14:41  yada
  fix typo. OSi_SPECFIC_CPS -> OSi_SPECIFIC_CPS

  Revision 1.71  2005/07/13 02:13:35  yada
  fix around thread info offset

  Revision 1.70  2005/07/11 08:31:35  yada
  fixed around SDK_THREAD_INFINITY

  Revision 1.69  2005/07/11 00:46:16  yada
  add OSi_SetSpecificData() / OSi_GetSpecificData()

  Revision 1.68  2005/07/08 08:50:06  yada
  OS_Set/GetUserParameter -> OS_Set/GetThreadParameter

  Revision 1.67  2005/07/06 06:37:21  yasu
  Added OS_KillThreadWithPriority

  Revision 1.66  2005/07/05 09:43:13  yasu
  Switching of define depending on SDK version by referencing version.h

  Revision 1.65  2005/07/01 09:20:06  yada
  specific size becomes 4

  Revision 1.64  2005/07/01 04:17:28  yada
  add system error number

  Revision 1.63  2005/06/30 11:23:41  yada
  add thread destructor and user parameter

  Revision 1.62  2005/06/28 09:49:44  yada
  applied for SDK_THREAD_INFINITY

  Revision 1.61  2005/06/16 07:57:31  yada
  add OS_YieldThread()

  Revision 1.60  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.59  2005/01/21 04:21:34  yada
  add OS_Enable/DisableScheduler()

  Revision 1.58  2005/01/11 07:53:54  takano_makoto
  fix copyright header.

  Revision 1.57  2005/01/07 04:17:04  yada
  release OS_DestroyThread as public function

  Revision 1.56  2004/11/02 11:58:22  yada
  fix a little

  Revision 1.55  2004/11/02 09:49:24  yada
  just fix comment

  Revision 1.54  2004/10/04 10:06:12  yasu
  support SDK_NO_MESSAGE

  Revision 1.53  2004/06/28 06:28:47  yada
  only fix comment typo

  Revision 1.52  2004/06/25 04:41:54  yada
  add OS_JoinThread(), OS_IsThreadTerminate()

  Revision 1.51  2004/06/08 00:28:51  yada
  only fix spacing

  Revision 1.50  2004/06/03 04:28:10  yada
  member 'calltrace' becomes 'profiler'

  Revision 1.49  2004/05/26 10:32:08  yada
  fix comment

  Revision 1.48  2004/05/26 05:17:05  yada
  add OS_GetNumberOfThread(), OS_THREAD_MAX_NUM changed 8 to 16

  Revision 1.47  2004/05/18 11:59:44  yasu
  add IRQ level counter 'irqDepth' in OSThreadInfo

  Revision 1.46  2004/05/18 08:21:47  yasu
  add flag macros for isNeedReschduling

  Revision 1.45  2004/05/18 06:36:56  yada
  only fix comment

  Revision 1.44  2004/05/13 05:35:19  yada
  add dummyPtr for structure size arrangement

  Revision 1.43  2004/05/12 12:13:58  yada
  delete unused define

  Revision 1.42  2004/05/12 05:13:41  yada
  modify SDK_XXX / OS_XXX option

  Revision 1.41  2004/05/10 12:05:07  yada
  consider for functionCost

  Revision 1.40  2004/04/30 02:17:20  yada
  add stack check function OS_GetStackStatus()

  Revision 1.39  2004/04/27 02:44:14  yada
  add function to get idle thread

  Revision 1.38  2004/04/26 07:37:25  yada
  only arrange indent

  Revision 1.37  2004/04/19 02:02:46  yada
  CALLSTACK->CALLTRACE

  Revision 1.36  2004/04/14 02:57:50  yada
  CALLSTACK->CALLTRACE

  Revision 1.35  2004/04/13 06:20:52  yada
  Added OS_DumpThreadCallTrace()

  Revision 1.34  2004/04/12 12:11:45  yada
  add callTrace.h

  Revision 1.33  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.32  2004/04/02 12:49:25  yada
  Added mutex queue to OSThread

  Revision 1.31  2004/03/31 09:25:14  yada
  add thread switch callback function

  Revision 1.30  2004/03/30 05:58:40  yada
  Added OS_IsThreadAvailable

  Revision 1.29  2004/03/03 07:03:44  yada
  Revised the location of the thread list pointer in the structure

  Revision 1.28  2004/03/02 11:54:29  yada
  Added OS_Sleep()

  Revision 1.27  2004/02/26 12:14:10  yada
  Priority range. Defined launch priority as 16.

  Revision 1.26  2004/02/26 09:42:04  yada
  Changed so that threads are managed in a priority list.

  Revision 1.25  2004/02/26 05:49:42  yada
  Added start function argument to OS_CreateThread().

  Revision 1.24  2004/02/17 09:29:21  yada
  Reshaped tab

  Revision 1.23  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.22  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.21  2004/01/21 12:02:05  yada
  Created a stack overflow check.

  Revision 1.20  2004/01/18 04:47:31  yada
  Reformed indents, etc.

  Revision 1.19  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.18  2003/12/25 07:30:11  yada
  Changes as per unified type rules

  Revision 1.17  2003/12/17 08:19:05  yasu
  Merged OSi_isNeedRescheduling into OS_ThreadInfo
  Changed OS_InitContext arguments

  Revision 1.16  2003/12/16 10:52:52  yasu
  Deleted unnecessary comments

  Revision 1.15  2003/12/16 07:14:05  yada
  Added a thread overflow check mechanism

  Revision 1.14  2003/12/16 06:07:57  yasu
  Added misc.h

  Revision 1.13  2003/12/16 00:18:02  yada
  Changed as per collection of thread information

  Revision 1.12  2003/12/11 11:54:27  yada
  Revised name OS_CreateThreadQueue() -> OS_InitThreadQueue()
  Made OS_GetMaxThreadId() not to be 'inline'

  Revision 1.11  2003/12/11 11:37:51  yada
  Added OS_GetThread, OS_GetThreadId, OS_GetMaxThreadId, OS_GetThreadContext, OS_GetThreadState

  Revision 1.10  2003/11/30 06:16:09  yasu
  Made it possible to call thread-related functions from interrupt service

  Revision 1.9  2003/11/30 02:08:23  yada
  Added stack size to the OS_CreateThread() arguments; made it so stack is cleared when thread is created

  Revision 1.8  2003/11/27 07:32:43  yasu
  Made OS_ThreadQueue minimum size 16 bit

  Revision 1.7  2003/11/26 10:51:42  yasu
  Opened OS_GetCurrentThread/OS_SetCurrentThread and made it 'inline'

  Revision 1.6  2003/11/26 09:31:15  yasu
  Separated OS_Reschedule and created OS_SelectThread

  Revision 1.5  2003/11/26 01:27:13  yasu
  Changed the OS_CreateThread interface
  Added OS_InitThread

  Revision 1.4  2003/11/25 13:31:56  yasu
  Added ThreadQueue

  Revision 1.3  2003/11/25 06:28:32  yasu
  Change the OS_CreateThread argument type

  Revision 1.2  2003/11/25 05:01:12  yasu
  Corrected typo and added prototype declarations

  Revision 1.1  2003/11/25 04:32:38  yasu
  initial version additions

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_THREAD_H_
#define NITRO_OS_THREAD_H_

#include "nitro/misc.h"
#include "nitro/os/common/context.h"
#include "nitro/os/common/callTrace.h"
#include "nitro/version.h"

#ifdef __cplusplus
extern "C" {
#endif

//---- build switch to let number of thread infinity, for version 3.0 or later
#if SDK_VERSION_MAJOR >= 3
#define SDK_THREAD_INFINITY           1
#endif

#ifdef SDK_FINALROM
// define if callTrace system not used
#define OS_NO_CALLTRACE
#endif


#ifndef SDK_THREAD_INFINITY
//---- maximum number of thread
#define OS_THREAD_MAX_NUM             16        // changed 8 to 16 (2004/5/26)
#endif

//---- priority of thread that calls OS_InitThread()
#define OS_THREAD_LAUNCHER_PRIORITY   16

//---- range of thread priority
#define OS_THREAD_PRIORITY_MIN        0
#define OS_THREAD_PRIORITY_MAX        31

//----------------------------------------------------------------------------
typedef struct _OSThread OSThread;

#ifdef SDK_THREAD_INFINITY
typedef struct _OSThreadQueue OSThreadQueue;
typedef struct _OSThreadLink OSThreadLink;
typedef struct _OSMutexQueue OSMutexQueue;
typedef struct _OSMutexLink OSMutexLink;
typedef struct OSMutex OSMutex;
#endif

typedef struct OSiAlarm OSAlarm;

#ifdef SDK_THREAD_INFINITY
struct _OSThreadQueue
{
    OSThread *head;
    OSThread *tail;
};

struct _OSThreadLink
{
    OSThread *prev;
    OSThread *next;
};

struct _OSMutexQueue
{
    OSMutex *head;
    OSMutex *tail;
};

struct _OSMutexLink
{
    OSMutex *next;
    OSMutex *prev;
};

#endif
//---------------- Thread status
typedef enum
{
    OS_THREAD_STATE_WAITING = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_TERMINATED = 2
}
OSThreadState;

#ifndef SDK_THREAD_INFINITY
//---------------- thread queue
#if     ( OS_THREAD_MAX_NUM <= 16 )
typedef u16 OSThreadQueue;
#define OS_SIZEOF_OSTHREADQUEUE  16
#elif   ( OS_THREAD_MAX_NUM <= 32 )
typedef u32 OSThreadQueue;
#define OS_SIZEOF_OSTHREADQUEUE  32
#else
Error:no bit field any more
#endif
#endif
#define OS_THREAD_SPECIFIC_MAX  3
typedef void (*OSThreadDestructor) (void *);

//---------------- Thread structure
struct _OSThread
{
    OSContext context;
    OSThreadState state;
    OSThread *next;
    u32     id;
    u32     priority;

    void   *profiler;

#ifdef SDK_THREAD_INFINITY
    OSThreadQueue *queue;
    OSThreadLink link;
#endif

#ifndef SDK_THREAD_INFINITY
    void   *mutex;
    void   *mutexQueueHead;
    void   *mutexQueueTail;
#else
    OSMutex *mutex;                    // OSMutex
    OSMutexQueue mutexQueue;           // OSMutexQueue
#endif

    u32     stackTop;                  // for stack overflow
    u32     stackBottom;               // for stack underflow
    u32     stackWarningOffset;

#ifndef SDK_THREAD_INFINITY
    OSThreadQueue joinQueue;           // for wakeup threads in thread termination
#if OS_SIZEOF_OSTHREADQUEUE == 16
    u16     padding;
#endif
#else
    OSThreadQueue joinQueue;

    void   *specific[OS_THREAD_SPECIFIC_MAX];   // for internal use
    OSAlarm *alarmForSleep;            // OSAlarm for sleeping
    OSThreadDestructor destructor;     // thread destructor
    void   *userParameter;             // for user

    int     systemErrno;
#endif
};

//---------------- Thread & context packed structure
typedef struct OSThreadInfo
{
    u16     isNeedRescheduling;
#ifndef SDK_THREAD_INFINITY
    u16     max_entry;
    u16     irqDepth;
    u16     padding;
#else
    u16     irqDepth;
#endif
    OSThread *current;
    OSThread *list;
    void   *switchCallback;            // type: OSSwitchThreadCallback
#ifndef SDK_THREAD_INFINITY
    OSThread *entry[OS_THREAD_MAX_NUM];
#endif
}
OSThreadInfo;

// offset
#ifndef SDK_THREAD_INFINITY
#define OS_THREADINFO_OFFSET_ISNEEDRESCHEDULING     0
#define OS_THREADINFO_OFFSET_MAX_ENTRY              2
#define OS_THREADINFO_OFFSET_IRQDEPTH               4
#define OS_THREADINFO_OFFSET_PADDING                6
#define OS_THREADINFO_OFFSET_CURRENT                8
#define OS_THREADINFO_OFFSET_LIST                   12
#define OS_THREADINFO_OFFSET_SWITCHCALLBACK         16
#define OS_THREADINFO_OFFSET_ENTRY                  20
#else  // ifndef SDK_THREAD_INFINITY
#define OS_THREADINFO_OFFSET_ISNEEDRESCHEDULING     0
#define OS_THREADINFO_OFFSET_IRQDEPTH               2
#define OS_THREADINFO_OFFSET_CURRENT                4
#define OS_THREADINFO_OFFSET_LIST                   8
#define OS_THREADINFO_OFFSET_SWITCHCALLBACK         12
#define OS_THREADINFO_OFFSET_ENTRY                  16
#endif

//----------------  CONTEXT OFFSET
#define OS_THREAD_OFFSET_CONTEXT                    0
#define OS_THREAD_OFFSET_STATE          (sizeof(OSContext))
#define OS_THREAD_OFFSET_NEXT           (sizeof(OSContext)+sizeof(OSThreadState))
#define OS_THREAD_OFFSET_ID             (OS_THREAD_OFFSET_NEXT+sizeof(OSThread*))

//---------------- thread stack overflow status
typedef enum
{
    OS_STACK_NO_ERROR = 0,
    OS_STACK_OVERFLOW = 1,
    OS_STACK_ABOUT_TO_OVERFLOW = 2,
    OS_STACK_UNDERFLOW = 3
}
OSStackStatus;

//---------------- thread switch callback
typedef void (*OSSwitchThreadCallback) (OSThread *from, OSThread *to);

//----------------------------------------------------------------------------
//---- private function ( don't use these OSi_* function )
void    OSi_CheckStack(const char *file, int line, const OSThread *thread);
u32     OSi_GetSystemStackPointer(void);
u32     OSi_GetCurrentStackPointer(void);
OSThread *OSi_GetIdleThread(void);

/*---------------------------------------------------------------------------*
  Name:         OS_InitThread

  Description:  Initialize Thread System

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_InitThread(void);

/*---------------------------------------------------------------------------*
  Name:         OS_IsThreadAvailable

  Description:  check if thread system is available

  Arguments:    None

  Returns:      TRUE if available, FALSE if not
 *---------------------------------------------------------------------------*/
BOOL    OS_IsThreadAvailable(void);

/*---------------------------------------------------------------------------*
  Name:         OS_CreateThread

  Description:  Create a new Thread

  Arguments:    thread      pointer of thread structure
                func        function to start thread
                arg         argument for func
                stack       stack bottom address
                stackSize   stack size (byte. must be aligned by 4)
                prio        thread priority

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_CreateThread(OSThread *thread,
                        void (*func) (void *), void *arg, void *stack, u32 stackSize, u32 prio);


/*---------------------------------------------------------------------------*
  Name:         OS_ExitThread

  Description:  Exit thread

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_ExitThread(void);


/*---------------------------------------------------------------------------*
  Name:         OS_DestroyThread

  Description:  destroy specified thread.

  Arguments:    thread: thread to be destroyed

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_DestroyThread(OSThread *thread);


/*---------------------------------------------------------------------------*
  Name:         OS_KillThread

  Description:  switch PC to thread destructor to finalize thread

  Arguments:    thread : thread to wait to finish
                flag   : argument for destructor

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifdef SDK_THREAD_INFINITY
void    OS_KillThread(OSThread *thread, void *arg);
void    OS_KillThreadWithPriority(OSThread *thread, void *arg, u32 prio);
#endif


/*---------------------------------------------------------------------------*
  Name:         OS_JoinThread

  Description:  wait for specified thread to terminated

  Arguments:    thread : thread to wait to finish

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_JoinThread(OSThread *thread);


/*---------------------------------------------------------------------------*
  Name:         OS_IsThreadTeminated

  Description:  check thread status whether it's terminated

  Arguments:    thread : pointer to thread to be examined

  Returns:      TRUE if the thread is terminated. FALSE if not
 *---------------------------------------------------------------------------*/
BOOL    OS_IsThreadTerminated(const OSThread *thread);


/*---------------------------------------------------------------------------*
  Name:         OS_SelectThread

  Description:  Select thread to execute

  Arguments:    None

  Returns:      thread to execute
 *---------------------------------------------------------------------------*/
OSThread *OS_SelectThread(void);


/*---------------------------------------------------------------------------*
  Name:         OS_RescheduleThread

  Description:  do rescheduling threads

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_RescheduleThread(void);

/*---------------------------------------------------------------------------*
  Name:         OS_YieldThread

  Description:  do thread rescheduling. current thread relinquish CPU
                to give chance of running to other threads which has same
                priority.

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
extern void OS_YieldThread(void);


/*---------------------------------------------------------------------------*
  Name:         OS_SleepThread

  Description:  sleep current thread

  Arguments:    thread         Thread queue

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SleepThread(OSThreadQueue *queue);


/*---------------------------------------------------------------------------*
  Name:         OS_SleepThreadDirect

  Description:  Gets the thread into sleep status directly

  Arguments:    thread            thread to sleep
                queue             waiting list queue (or NULL)

  Returns:      none
 *---------------------------------------------------------------------------*/
void    OS_SleepThreadDirect(OSThread *thread, OSThreadQueue *queue);


/*---------------------------------------------------------------------------*
  Name:         OS_WakeupThread

  Description:  wake up threads by queue

  Arguments:    queue         Thread queue

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_WakeupThread(OSThreadQueue *queue);


/*---------------------------------------------------------------------------*
  Name:         OS_WakeupThreadDirect

  Description:  wake up thread by specifying thread directly

  Arguments:    thread        Thread to wake up

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_WakeupThreadDirect(OSThread *thread);


/*---------------------------------------------------------------------------*
  Name:         OS_DumpThreadList

  Description:  Dump All Thread Information (for DEBUG)

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_DumpThreadList(void);


/*---------------------------------------------------------------------------*
  Name:         OS_GetNumberOfThread

  Description:  Get number of thread which exists in system

  Arguments:    None

  Returns:      number of thread which exists in system
 *---------------------------------------------------------------------------*/
int     OS_GetNumberOfThread(void);

/*==== static inlie functions ====*/
/*---------------------------------------------------------------------------*
  Name:         OS_GetThreadInfo

  Description:  Get pointer of system thread info structure.

  Arguments:    None

  Returns:      pointer of thread info structure
 *---------------------------------------------------------------------------*/
extern OSThreadInfo OSi_ThreadInfo;

static inline OSThreadInfo *OS_GetThreadInfo(void)
{
    return &OSi_ThreadInfo;
}

/*---------------------------------------------------------------------------*
  Name:         OS_GetMaxThreadId

  Description:  Gets Max id number of available thread number

  Arguments:    None

  Returns:      Max id of available thread number
 *---------------------------------------------------------------------------*/
static inline u32 OS_GetMaxThreadId(void)
{
#ifndef SDK_THREAD_INFINITY
    return OS_GetThreadInfo()->max_entry;
#else
    return 0x7fffffff;                 // (=maximum number of int)
#endif
}

/*---------------------------------------------------------------------------*
  Name:         OS_GetThread

  Description:  Gets pointer to thread which id is specified

  Arguments:    id : thread id to get thread

  Returns:      pointer to thread which id is specified
 *---------------------------------------------------------------------------*/
#ifndef SDK_THREAD_INFINITY
static inline OSThread *OS_GetThread(u32 id)
{
    SDK_ASSERTMSG(id < OS_THREAD_MAX_NUM, "Thread id illegal\n");
    return OS_GetThreadInfo()->entry[id];
}
#else
extern OSThread *OS_GetThread(u32 id);
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_GetThreadId

  Description:  Gets id of specified thread

  Arguments:    thread      pointer to thread

  Returns:      id of specified thread
 *---------------------------------------------------------------------------*/
static inline u32 OS_GetThreadId(const OSThread *thread)
{
    SDK_ASSERTMSG(thread, "null thread pointer.");
    return thread->id;
}

/*---------------------------------------------------------------------------*
  Name:         OS_GetThreadState

  Description:  Gets state of specified thread

  Arguments:    thread      pointer to thread

  Returns:      state of specified thread
 *---------------------------------------------------------------------------*/
static inline OSThreadState OS_GetThreadState(const OSThread *thread)
{
    SDK_ASSERTMSG(thread, "null thread pointer.");
    return thread->state;
}

/*---------------------------------------------------------------------------*
  Name:         OS_GetThreadContext

  Description:  Gets pointer to context of specified thread

  Arguments:    thread      pointer to thread

  Returns:      pointer to context of specified thread
 *---------------------------------------------------------------------------*/
static inline OSContext *OS_GetThreadContext(const OSThread *thread)
{
    SDK_ASSERTMSG(thread, "null thread pointer.");
    return (OSContext *)&thread->context;
}

/*---------------------------------------------------------------------------*
  Name:         OS_IsThreadRunnable

  Description:  Check if thread is runnable

  Arguments:    thread   pointer to thread

  Returns:      non zero if thread is runnable
 *---------------------------------------------------------------------------*/
static inline BOOL OS_IsThreadRunnable(const OSThread *thread)
{
    return thread->state == OS_THREAD_STATE_READY;
}

/*---------------------------------------------------------------------------*
  Name:         OS_InitThreadQueue

  Description:  Initialize thread queue

  Arguments:    queue   pointer to thread queue

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
#ifndef SDK_THREAD_INFINITY
    *queue = 0;
#else
    queue->head = queue->tail = NULL;
#endif
}

/*---------------------------------------------------------------------------*
  Name:         OS_GetCurrentThread

  Description:  Gets pointer to the current thread

  Arguments:    None

  Returns:      Pointer to the current thread
 *---------------------------------------------------------------------------*/
static inline OSThread *OS_GetCurrentThread(void)
{
    return OS_GetThreadInfo()->current;
}

/*---------------------------------------------------------------------------*
  Name:         OS_SetCurrentThread

  Description:  Saves pointer to the current thread

  Arguments:    thread : thread to be current thread

  Returns:      Pointer to the current thread
 *---------------------------------------------------------------------------*/
static inline void OS_SetCurrentThread(OSThread *thread)
{
    OS_GetThreadInfo()->current = thread;
}

/*==== stack check ====*/
/*---------------------------------------------------------------------------*
  Name:         OS_SetThreadStackWarningOffset

  Description:  Set warning level for stack checker

  Arguments:    thread     thread to set
                offset     offset from stack top. must be multiple of 4

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SetThreadStackWarningOffset(OSThread *thread, u32 offset);


/*---------------------------------------------------------------------------*
  Name:         OS_GetStackStatus

  Description:  check thread stack. check each CheckNUM.
                return result.

  Arguments:    thread   thread checked

  Returns:      0                            no error
                OS_STACK_OVERFLOW            overflow
                OS_STACK_ABOUT_TO_OVERFLOW   about to overflow
                OS_STACK_UNDERFLOW           underflow
 *---------------------------------------------------------------------------*/
OSStackStatus OS_GetStackStatus(const OSThread *thread);

/*---------------------------------------------------------------------------*
  Name:         OS_CheckStack

  Description:  check thread stack. check each CheckNum.
                if changed, display warning and halt.

  Arguments:    thread   thread to check stack

  Returns:      None.
                ( if error occurred, never return )
 *---------------------------------------------------------------------------*/
#if !defined(SDK_FINALROM) && !defined(SDK_NO_MESSAGE)
#define  OS_CheckStack( thread )  OSi_CheckStack( __FILE__, __LINE__, (const OSThread*)thread );
#else
#define  OS_CheckStack( thread )  ((void)0)
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_SetThreadPriority

  Description:  change priority of thread

  Arguments:    thread     thread to set priority
                prio       new priority to be set

  Returns:      TRUE if success
 *---------------------------------------------------------------------------*/
BOOL    OS_SetThreadPriority(OSThread *thread, u32 prio);


/*---------------------------------------------------------------------------*
  Name:         OS_GetThreadPriority

  Description:  get priority of thread

  Arguments:    thread     thread to get priority

  Returns:      priority
 *---------------------------------------------------------------------------*/
u32     OS_GetThreadPriority(const OSThread *thread);


/*---------------------------------------------------------------------------*
  Name:         OS_Sleep

  Description:  sleep specified period

  Arguments:    msec       sleeping period. ( milliseconds )

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_Sleep(u32 msec);


/*---------------------------------------------------------------------------*
  Name:         OS_SetSwitchThreadCallback

  Description:  set callback called at switching thread

  Arguments:    callback      callback function

  Returns:      previous callback function before set callback now
 *---------------------------------------------------------------------------*/
OSSwitchThreadCallback OS_SetSwitchThreadCallback(OSSwitchThreadCallback callback);


// notice: substans is in os_callTrace.c.
//         define here because of OSThread declaration.
/*---------------------------------------------------------------------------*
  Name:         OS_DumpThreadCallTrace

  Description:  dump callStack of thread

  Arguments:    thread :    thread

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_DumpThreadCallTrace(const OSThread *thread);



/*---------------------------------------------------------------------------*
  Name:         OS_DisableScheduler

  Description:  disable scheduler

  Arguments:    None

  Returns:      Previous scheduler suspend count.
                Suspended if value >= 0.
 *---------------------------------------------------------------------------*/
u32     OS_DisableScheduler(void);

/*---------------------------------------------------------------------------*
  Name:         OS_EnableScheduler

  Description:  enable scheduler

  Arguments:    None

  Returns:      Previous scheduler suspend count.
                Suspended if value >= 0.
 *---------------------------------------------------------------------------*/
u32     OS_EnableScheduler(void);


#ifdef SDK_THREAD_INFINITY
/*---------------------------------------------------------------------------*
  Name:         OS_SetThreadDestructor

  Description:  set thread destructor, which is called when that thread exits.

  Arguments:    thread : thread pointer
                dtor   : destructor function

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SetThreadDestructor(OSThread *thread, OSThreadDestructor dtor);

/*---------------------------------------------------------------------------*
  Name:         OS_GetThreadDestructor

  Description:  get thread destructor which is set

  Arguments:    thread : thread pointer

  Returns:      destructor function
 *---------------------------------------------------------------------------*/
OSThreadDestructor OS_GetThreadDestructor(const OSThread *thread);

/*---------------------------------------------------------------------------*
  Name:         OS_SetThreadParameter

  Description:  set user parameter which is allowed to use freely.

  Arguments:    thread    : thread pointer
                parameter : user parameter

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SetThreadParameter(OSThread *thread, void *parameter);

/*---------------------------------------------------------------------------*
  Name:         OS_GetThreadParameter

  Description:  get user parameter which is set

  Arguments:    thread : thread pointer

  Returns:      user parameter which is set
 *---------------------------------------------------------------------------*/
void   *OS_GetThreadParameter(const OSThread *thread);

/*---------------------------------------------------------------------------*
  Name:         OS_GetErrno

  Description:  get system error number.

  Arguments:    None.

  Returns:      error number
 *---------------------------------------------------------------------------*/
int     OS_GetErrno(void);
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_IsThreadInList

  Description:  check if the specified thread is in the thread list

  Arguments:    thread : thread

  Returns:      TRUE if thread is in the thread list
 *---------------------------------------------------------------------------*/
BOOL    OS_IsThreadInList(const OSThread *thread);

/*---------------------------------------------------------------------------*
  Name:         OS_SetThreadDestructorStack

  Description:  specify stack area to call thread destructor

  Arguments:    stack       stack bottom address

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SetThreadDestructorStack(void *stack);


#ifdef SDK_THREAD_INFINITY
//================================================================================
//              The following functions are for internal use. Not for user.
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OSi_RemoveMutexLinkFromQueue

  Description:  remove mutex from mutex queue

  Arguments:    queue  : mutex queue

  Returns:      mutex pointer which is removed
 *---------------------------------------------------------------------------*/
extern OSMutex *OSi_RemoveMutexLinkFromQueue(OSMutexQueue * queue);

/*---------------------------------------------------------------------------*
  Name:         OSi_SetSystemErrno

  Description:  set system error number.

  Arguments:    thread : thread to set error number
                errno  : error number to set

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OSi_SetSystemErrno(OSThread *thread, int errno);

/*---------------------------------------------------------------------------*
  Name:         OSi_GetSystemErrno

  Description:  get system error number.

  Arguments:    thread : thread to set error number

  Returns:      error number
 *---------------------------------------------------------------------------*/
int     OSi_GetSystemErrno(const OSThread *thread);


#define OSi_SPECIFIC_CPS   0

/*---------------------------------------------------------------------------*
  Name:         OSi_SetSpecificData

  Description:  set system specific data

  Arguments:    thread : thread to set data
                index  : index of specific array
                data   : data to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void OSi_SetSpecificData(OSThread *thread, int index, void *data)
{
    SDK_ASSERT(thread && 0 <= index && index < OS_THREAD_SPECIFIC_MAX);
    thread->specific[index] = data;
}

/*---------------------------------------------------------------------------*
  Name:         OSi_GetSpecificData

  Description:  get system specific data

  Arguments:    thread : thread to get data
                index  : index of specific array

  Returns:      error number
 *---------------------------------------------------------------------------*/
static inline void *OSi_GetSpecificData(const OSThread *thread, int index)
{
    SDK_ASSERT(thread && 0 <= index && index < OS_THREAD_SPECIFIC_MAX);
    return thread->specific[index];
}
#endif


//================================================================================
//              The following functions are for operations of thread struct.
//              use carefully.
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_GetThreadList

  Description:  get first thread of thread list.

  Arguments:    None

  Returns:      first thread of thread list
 *---------------------------------------------------------------------------*/
static inline OSThread *OS_GetThreadList(void)
{
    return OS_GetThreadInfo()->list;
}


/*---------------------------------------------------------------------------*
  Name:         OS_GetNextThread

  Description:  get thread which is linked next in thread list

  Arguments:    thread : thread to get next thread

  Returns:      next thread. NULL means no next thread ( specified thread may be last )
 *---------------------------------------------------------------------------*/
static inline OSThread *OS_GetNextThread(const OSThread *thread)
{
    SDK_ASSERT(thread);
    return thread->next;
}



#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_THREAD_H_ */
#endif
