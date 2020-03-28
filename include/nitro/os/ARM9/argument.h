/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     argument.h

  Copyright 2005,2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: argument.h,v $
  Revision 1.11  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.10  2005/09/16 01:17:19  yasu
  Support loading from nitro_win32.h.

  Revision 1.9  2005/09/09 05:20:42  yada
  small fix

  Revision 1.8  2005/09/09 04:34:50  yada
  add conversion from string to arguments

  Revision 1.7  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.6  2005/09/08 11:18:01  yasu
  Switched from SDK_WIN32 to SDK_FROM_TOOL.

  Revision 1.5  2005/09/08 11:01:13  yasu
  SDK_WIN32 support

  Revision 1.4  2005/08/30 09:00:34  yasu
  Added OS_GetOpt.

  Revision 1.3  2005/07/21 12:41:50  yada
  consider for NITRO_FINALROM

  Revision 1.2  2005/07/21 09:43:10  yada
  fix bury rule

  Revision 1.1  2005/07/21 07:01:29  yada
  initial release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_ARGUMENT_H_
#define NITRO_OS_ARGUMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

//---- force to be available argument area
//#define OS_ARGUMENT_FORCE_TO_BE_AVAILABLE   TRUE

// if finalrom, no argument
#ifdef SDK_FINALROM
#define OS_NO_ARGUMENT    TRUE
#endif

// if forced, let argument area available
#ifdef OS_ARGUMENT_FORCE_TO_BE_AVAILABLE
#ifdef OS_NO_ARGUMENT
#undef OS_NO_ARGUMENT
#endif
#endif

// no assert on win32
#if (defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#define SDK_ASSERT(exp)                         ((void) 0)
#define SDK_ALIGN4_ASSERT(exp)                  ((void) 0)
#define SDK_MINMAX_ASSERT(exp, min, max)        ((void) 0)
#define SDK_NULL_ASSERT(exp)                    ((void) 0)
// inline for VC
#if (defined(_MSC_VER) && !defined(__cplusplus))
#define inline __inline
#endif
#endif

//================================================================================

//---- argument string buffer size
#define OS_ARGUMENT_BUFFER_SIZE  	256

//---- argument buffer identification string (max 17 chars)
#define OS_ARGUMENT_ID_STRING      	":$@$Argument$@$:"
#define OS_ARGUMENT_ID_STRING_BUFFER_SIZE 18

//---- argument buffer struct
typedef struct OSArgumentBuffer
{
    char    argMark[OS_ARGUMENT_ID_STRING_BUFFER_SIZE];
    u16     size;
#if defined(SDK_WIN32) || defined(SDK_FROM_TOOL)
    char    buffer[OS_ARGUMENT_BUFFER_SIZE];
#else
    const char buffer[OS_ARGUMENT_BUFFER_SIZE];
#endif
}
OSArgumentBuffer;


/*---------------------------------------------------------------------------*
  Name:         OS_GetArgc

  Description:  Get number of valid arguments.
                This function is for debug.

  Arguments:    None

  Returns:      number of valid arguments.
                if no argument, return 1.
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_ARGUMENT
extern int OS_GetArgc(void);
#else
static inline int OS_GetArgc(void)
{
    return 0;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_GetArgv

  Description:  Get the pointer to the specified argument string.
                This function is for debug.

  Arguments:    n : index of argument. n==1 means the first argument.

  Returns:      n must less than value of OS_GetArgc()
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_ARGUMENT
extern const char *OS_GetArgv(int n);
#else
static inline const char *OS_GetArgv(int n)
{
#pragma unused(n)
    return NULL;
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_GetOpt/OS_GetOptArg/OS_GetOptInd/OS_GetOptOpt

  Description:  getopt() like function to get command line options
  
  Arguments:    optstring: Option character string
                           Internal parameters are reset if NULL.

  Returns:      Option character code.
                '?' Indicates the option character code is unclear
                -1  Indicates the option does not exist
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_ARGUMENT
int     OS_GetOpt(const char *optstring);
#else
static inline int OS_GetOpt(const char *optstring)
{
#pragma unused(optstring)
    return -1;
}
#endif

extern const char *OSi_OptArg;
extern int OSi_OptInd;
extern int OSi_OptOpt;

static inline const char *OS_GetOptArg(void)
{
    return OSi_OptArg;
}
static inline int OS_GetOptInd(void)
{
    return OSi_OptInd;
}
static inline int OS_GetOptOpt(void)
{
    return OSi_OptOpt;
}

/*---------------------------------------------------------------------------*
  Name:         OS_ConvertToArguments

  Description:  convert string data to arg binary
  
  Arguments:    str     : string
  				cs	    : character to separate
  				buffer  : buffer to store
  				bufSize : max buffer size
 
  Returns:      None.
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_ARGUMENT
extern void OS_ConvertToArguments(const char *str, char cs, char *buffer, u32 bufSize);
#else
static inline void OS_ConvertToArguments(const char *str, char cs, char *buffer, u32 bufSize)
{
#pragma unused(str, cs, buffer, bufSize)
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_SetArgumentBuffer

  Description:  force to set argument buffer.
  
  Arguments:    buffer  : argument buffer
 
  Returns:      None.
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_ARGUMENT
extern void OS_SetArgumentBuffer(const char *buffer);
#else
static inline void OS_SetArgumentBuffer(const char *buffer)
{
#pragma unused(buffer)
}
#endif

/*---------------------------------------------------------------------------*
  Name:         OS_GetArgumentBuffer

  Description:  get pointer to argument buffer.
  
  Arguments:    None.
 
  Returns:      pointer to argument buffer.
 *---------------------------------------------------------------------------*/
#ifndef OS_NO_ARGUMENT
extern const char *OS_GetArgumentBuffer(void);
#else
static inline const char *OS_GetArgumentBuffer(void)
{
    return NULL;
}
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_ARGUMENT_H_ */
#endif
