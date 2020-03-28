/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     callTrace.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: callTrace.h,v $
  Revision 1.15  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.14  2005/07/11 05:05:08  yada
  fix around static inline

  Revision 1.13  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.12  2004/05/12 10:58:53  yada
  optional r0,r1,r2,r3 each

  Revision 1.11  2004/05/12 08:19:12  yada
  fix bad endif

  Revision 1.10  2004/05/12 08:03:01  yada
  fix include guard

  Revision 1.9  2004/05/12 05:07:12  yada
  modify SDK_XXX / OS_XXX option

  Revision 1.8  2004/05/10 11:45:40  yada
  consider for functionCost

  Revision 1.7  2004/04/26 01:44:49  yada
  OSi->OS: about OS_Enable/Disable/RestoreCallTrace

  Revision 1.6  2004/04/23 06:01:48  yada
  fix spell mistake

  Revision 1.5  2004/04/23 00:30:02  yada
  added support for log mode

  Revision 1.4  2004/04/15 02:28:14  yada
  consider for FINALROM

  Revision 1.3  2004/04/14 02:57:50  yada
  CALLSTACK->CALLTRACE

  Revision 1.2  2004/04/13 06:21:58  yada
  added OS_DumpThreadCallTrace() (only explanation)

  Revision 1.1  2004/04/12 12:11:14  yada
  first release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_CALLTRACE_H_
#define NITRO_OS_CALLTRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/os/common/profile.h"

// define if do checking callTrace stack over/underflow
#define OS_CALLTRACE_CHECK_OVERSTACK

// define if record register
#define OS_CALLTRACE_RECORD_R0
#define OS_CALLTRACE_RECORD_R1
#define OS_CALLTRACE_RECORD_R2
#define OS_CALLTRACE_RECORD_R3

// define if record call level
#define OS_CALLTRACE_LEVEL_AVAILABLE

//================================================================================
//---------------- callTrace structure
typedef struct
{
    u32     name;                      // pointer to function name
    u32     returnAddress;             // value of lr register

#ifdef OS_CALLTRACE_LEVEL_AVAILABLE
    u32     level;                     // call level
#endif

#ifdef OS_CALLTRACE_RECORD_R0
    u32     r0;                        // value of r0 register
#endif
#ifdef OS_CALLTRACE_RECORD_R1
    u32     r1;                        // value of r1 register
#endif
#ifdef OS_CALLTRACE_RECORD_R2
    u32     r2;                        // value of r2 register
#endif
#ifdef OS_CALLTRACE_RECORD_R3
    u32     r3;                        // value of r3 register
#endif
}
OSCallTrace;

#define OSi_SIZEOF_CALLTRACE     sizeof(OSCallTrace)

//---------------- callTraceInfo structure
typedef struct
{
    OSCallTrace *current;              // current pointer
    OSCallTrace *limit;                // buffer limit as hi-address
    u16     enable;
    u16     circular;
#ifdef OS_CALLTRACE_LEVEL_AVAILABLE
    u32     level;                     // call level
#endif
    OSCallTrace array[1];              // valiable length
}
OSCallTraceInfo;

#define OSi_TRACEINFO_SIZEOF_HEADERPART (sizeof(OSCallTraceInfo) - sizeof(OSCallTrace))


//---------------- mode
typedef enum
{
    OS_CALLTRACE_STACK = 0,
    OS_CALLTRACE_LOG = 1
}
OSCallTraceMode;

//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_InitCallTrace

  Description:  Initialize callTrace stack,
                and start record trace.

  Arguments:    buf     address to record trace infomation
                size    size of buffer (by byte)
                logFlag OS_CALLTRACE_LOG if remain record in __PROFILE_EXIT as log
                        OS_CALLTRACE_NOLOG if not remain

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_CALLTRACE
void    OS_InitCallTrace(void *buf, u32 size, OSCallTraceMode mode);
#else
static inline void OS_InitCallTrace(void *, u32, OSCallTraceMode)
{                                      /* do nothing */
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_DumpCallTrace

  Description:  Dump callTrace

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_CALLTRACE
void    OS_DumpCallTrace(void);
#else
static inline void OS_DumpCallTrace(void)
{                                      /* do nothing */
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_DumpThreadCallTrace

  Description:  dump callStack of thread

  Arguments:    thread :    thread

  Returns:      None
 *---------------------------------------------------------------------------*/
//  void OS_DumpThreadCallTrace( OSThread* thread );
//
// notice: This function is defined in os_thread.h because 'OSThread' declaration.
//

/*---------------------------------------------------------------------------*
  Name:         OS_CalcCallTraceLines

  Description:  calculate number of lines to be able to be allocated

  Arguments:    size :    CallTrace buffer size
                          same as argument of OS_InitCallTrace()'s size

  Returns:      number of lines to be able to allocate in 'size' byte
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_CALLTRACE
int     OS_CalcCallTraceLines(u32 size);
#else
static inline int OS_CalcCallTraceLines(u32)
{
    return 0;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_CalcCallTraceBufferSize

  Description:  calculate buffer size to allocate specified lines

  Arguments:    lines :   lines to want to allocate

  Returns:      buffer size to need
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_CALLTRACE
u32     OS_CalcCallTraceBufferSize(int lines);
#else
static inline u32 OS_CalcCallTraceBufferSize(int)
{
    return 0;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_ClearCallTraceBuffer

  Description:  clear buffer if used for logging

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_CALLTRACE
void    OS_ClearCallTraceBuffer(void);
#else
static inline void OS_ClearCallTraceBuffer(void)
{                                      /* do nothing */
}
#endif


/*---------------------------------------------------------------------------*
  Name:         OS_EnableCallTrace

  Description:  enable callTrace

  Arguments:    None

  Returns:      previous status. TRUE if enable
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_CALLTRACE
BOOL    OS_EnableCallTrace();
#else
static inline BOOL OS_EnableCallTrace()
{
    return FALSE;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_DisableCallTrace

  Description:  disable callTrace

  Arguments:    None

  Returns:      previous status. TRUE if enable
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_CALLTRACE
BOOL    OS_DisableCallTrace();
#else
static inline BOOL OS_DisableCallTrace()
{
    return FALSE;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_RestoreCallTrace

  Description:  set status of callTrace

  Arguments:    enable :  TRUE if set to be enable, FALSE if not

  Returns:      previous status. TRUE if enable
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_CALLTRACE
BOOL    OS_RestoreCallTrace(BOOL enable);
#else
static inline BOOL OS_RestoreCallTrace(BOOL)
{
    return FALSE;
}
#endif


//---- following functions are for calling from other os library.
//     don't call from user proc.
//
#ifndef OS_NO_CALLTRACE
void    OSi_SetCallTraceEntry(const char *name, u32 lr);
#else
static inline void OSi_SetCallTraceEntry(const char *name, u32 lr);
#endif


//--------------------------------------------------------------------------------
#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_CALLTRACE_H_ */
#endif
