/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     functionCost.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: functionCost.h,v $
  Revision 1.13  2007/02/20 00:28:10  kitase_hirotake
  indent source

  Revision 1.12  2006/08/22 07:20:23  yada
  add the feature which is the check if the buffer overflowed the limit

  Revision 1.11  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.10  2005/07/11 05:05:08  yada
  fix around static inline

  Revision 1.9  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.8  2004/10/07 12:38:10  yada
  fix around OS_CalcThreadStatistics()

  Revision 1.7  2004/05/18 06:35:15  yada
  consider for thread that is not current

  Revision 1.6  2004/05/18 06:10:38  yada
  consider for thread interval

  Revision 1.5  2004/05/12 10:59:42  yada
  fix structure offset description

  Revision 1.4  2004/05/12 08:19:26  yada
  fix bad endif

  Revision 1.3  2004/05/12 08:03:01  yada
  fix include guard

  Revision 1.2  2004/05/12 05:07:40  yada
  modify SDK_XXX / OS_XXX option

  Revision 1.1  2004/05/10 11:38:08  yada
  first release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_OS_FUNCTIONCOST_H_
#define NITRO_OS_FUNCTIONCOST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/os/common/profile.h"

//================================================================================
//---- define if consider thread interval

#if defined(OS_PROFILE_AVAILABLE) && defined(OS_PROFILE_FUNCTION_COST)
#ifndef OS_NO_FUNCTIONCOST
#define OSi_FUNCTIONCOST_THREAD_INTERVAL
#endif
#endif

//================================================================================
//---------------- functionCost structure

#define OSi_FUNCTIONCOST_EXIT_TAG   0xffffffff

typedef union
{
    struct
    {
        u32     name;                  // pointer to function name
        u32     time;                  // time for __PROFILE_ENTRY
#ifdef OSi_FUNCTIONCOST_THREAD_INTERVAL
        u32     interval;
#endif
    }
    entry;
    struct
    {
        u32     tag;                   // tag(0xffffffff)
        u32     time;                  // time for __PROFILE_EXIT
#ifdef OSi_FUNCTIONCOST_THREAD_INTERVAL
        u32     interval;
#endif
    }
    exit;
}
OSFunctionCost;

#define OSi_SIZEOF_FUNCTIONCOST      sizeof(OSFunctionCost)

//---------------- functionCostInfo structure
typedef struct
{
    OSFunctionCost *current;           // current pointer
    OSFunctionCost *limit;             // buffer limit as hi-address
    u16     enable;
    u16     padding;                   // padding
#ifdef OSi_FUNCTIONCOST_THREAD_INTERVAL
    u32     breakTime;
#endif
    OSFunctionCost array[1];           // valiable length

}
OSFunctionCostInfo;

#define OSi_COSTINFO_SIZEOF_HEADERPART (sizeof(OSFunctionCostInfo) - sizeof(OSFunctionCost))

//---------------- statstics
typedef struct
{
    u32     name;
    u32     count;
    u64     time;
}
OSFunctionCostStatistics;

typedef struct
{
    u32     size;
    OSFunctionCostStatistics *limit;
    OSFunctionCostStatistics array[1]; // valiable length
}
OSFunctionCostStatisticsInfo;


#define OSi_STATISTICS_SIZEOF_HEADERPART (sizeof(OSFunctionCostStatisticsInfo) - sizeof(OSFunctionCostStatistics))
#define OSi_STATISTICS_LEAST_SIZE        (OSi_STATISTICS_SIZEOF_HEADERPART + sizeof(OSFunctionCostStatistics))

//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_InitFunctionCost

  Description:  Initialize functionCost buffer,
                and start recording.

  Arguments:    buf    address to buffer for recording entering and exitting function.
                size   size of buffer (by byte)

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
void    OS_InitFunctionCost(void *buf, u32 size);
#else
static inline void OS_InitFunctionCost(void *, u32)
{                                      /* do nothing */
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_CalcFunctionCostLines

  Description:  calculate number of lines to be able to be allocated

  Arguments:    size :    FunctionCost buffer size
                          same as argument of OS_InitFunctionCost()'s size

  Returns:      number of lines to be able to allocate in 'size' byte
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
int     OS_CalcFunctionCostLines(u32 size);
#else
static inline int OS_CalcFunctionCostLines(u32)
{
    return 0;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_CalcFunctionCostBufferSize

  Description:  calculate buffer size to allocate specified lines

  Arguments:    lines :   lines to want to allocate

  Returns:      buffer size to need
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
u32     OS_CalcFunctionCostBufferSize(int lines);
#else
static inline u32 OS_CalcFunctionCostBufferSize(int)
{
    return 0;
}
#endif


/*---------------------------------------------------------------------------*
  Name:         OS_CheckFunctionCostBuffer

  Description:  check if function cost buffer overflows the limit.

  Arguments:    buf    address to buffer for recording entering and exitting function.

  Returns:      FALSE if overflowed. TRUE if not
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
BOOL    OS_CheckFunctionCostBuffer(void *buf);
#else
static inline BOOL OS_CheckFunctionCostBuffer(void *buf)
{
#pragma unused(buf)
    return FALSE;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_ClearFunctionCostBuffer

  Description:  clear buffer

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
extern void OSi_ClearThreadFunctionCostBuffer(OSThread *thread);
static inline void OS_ClearFunctionCostBuffer(void)
{
    OSi_ClearThreadFunctionCostBuffer(NULL);
}
#else
static inline void OS_ClearFunctionCostBuffer(void)
{                                      /* do nothing */
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_EnableFunctionCost

  Description:  enable functionCost

  Arguments:    None

  Returns:      previous status. TRUE if enable 
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
BOOL    OS_EnableFunctionCost();
#else
static inline BOOL OS_EnableFunctionCost()
{
    return FALSE;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_DisableFunctionCost

  Description:  disble functionCost

  Arguments:    None

  Returns:      previous status. TRUE if enable 
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
BOOL    OS_DisableFunctionCost();
#else
static inline BOOL OS_DisableFunctionCost()
{
    return FALSE;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_RestoreFunctionCost

  Description:  set status of functionCost

  Arguments:    enable :  TRUE if set to be enable, FALSE if not

  Returns:      previous status. TRUE if enable 
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
BOOL    OS_RestoreFunctionCost(BOOL enable);
#else
static inline BOOL OS_RestoreFunctionCost(BOOL)
{
    return FALSE;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_InitStatistics

  Description:  initialize statistics buffer

  Arguments:    statBuf  pointer to statistics buffer
                size     size of statBuf

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
void    OS_InitStatistics(void *statBuf, u32 size);
#else
static inline void OS_InitStatistics(void *, u32)
{                                      /* do nothing */
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_CalcThreadStatistics

  Description:  calculate statistics to statBuf of thread

  Arguments:    statBuf    pointer to statistics buffer
                thread     thread to calculate.
                           if current or no thread then specify NULL

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
void    OS_CalcThreadStatistics(void *statBuf, OSThread *thread);
#else
static inline void OS_CalcThreadStatistics(void *, OSThread *)
{                                      /* do nothing */
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_CalcStatistics

  Description:  calculate statistics to statBuf

  Arguments:    statBuf    pointer to statistics buffer

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void OS_CalcStatistics(void *statBuf)
{
    OS_CalcThreadStatistics(statBuf, NULL);
}


/*---------------------------------------------------------------------------*
  Name:         OS_CheckStatisticsBuffer

  Description:  check if statistics buffer overflows the limit.

  Arguments:    statBuf    pointer to statistics buffer

  Returns:      FALSE if overflowed. TRUE if not
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
BOOL    OS_CheckStatisticsBuffer(void *statBuf);
#else
static inline BOOL OS_CheckStatisticsBuffer(void *statBuf)
{
#pragma unused(statBuf)
    return FALSE;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_DumpStatistics

  Description:  dump statistics of functionCost

  Arguments:    statBuf  buffer for statistics

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_FUNCTIONCOST
void    OS_DumpStatistics(void *statBuf);
#else
static inline void OS_DumpStatistics(void *)
{                                      /* do nothing */
}
#endif


//--------------------------------------------------------------------------------
#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_FUNCTIONCOST_H_ */
#endif
