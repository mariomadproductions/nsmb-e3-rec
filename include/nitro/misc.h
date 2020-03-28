/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include -
  File:     misc.h

  Copyright 2003-2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: misc.h,v $
  Revision 1.42  2007/04/20 08:48:16  yosizaki
  Fixed warning about unused arguments.

  Revision 1.41  2007/04/20 06:53:31  yosizaki
  Added OSi_AbortByUnsupportedRegister.

  Revision 1.40  2006/03/13 05:58:26  okubata_ryoma
  Minor revisions to macros

  Revision 1.39  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.38  2005/11/07 01:55:34  okubata_ryoma
  Minor revisions

  Revision 1.35  2005/11/01 05:39:01  okubata_ryoma
  Minor revisions

  Revision 1.33  2005/10/19 07:49:05  okubata_ryoma
  Corrected method of coding parameters for #pragma define_section.

  Revision 1.32  2005/07/11 05:01:41  yada
  Section block is moved to section.h

  Revision 1.31  2005/07/05 10:55:55  yasu
  Returned include position of utest.h to original location

  Revision 1.30  2005/07/05 09:35:49  yasu
  Added nitro/utest.h

  Revision 1.29  2005/04/08 09:32:06  yosizaki
  define_section VERSION.
  Added several macros for embedded middleware.

  Revision 1.28  2005/03/04 10:07:03  yasu
  Split compiler dependant sections according to conditions

  Revision 1.27  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.26  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.25  2004/11/24 10:27:35  yasu
  Defines for parent section

  Revision 1.24  2004/09/11 07:21:50  yasu
  Added SDK_T* version

  Revision 1.23  2004/07/02 08:40:51  yada
  Added section definition

  Revision 1.22  2004/02/12 10:56:04  yasu
  New location of include files ARM9/ARM7

  Revision 1.21  2004/02/05 07:09:03  yasu
  Changed SDK prefix iris to nitro

  Revision 1.20  2004/01/29 02:40:14  nishida_kenji
  Added SDK_MIN_ASSERT, SDK_MAX_ASSERT, SDK_ALIGN2_ASSERT.

  Revision 1.19  2003/12/29 08:43:49  yasu
  Workaround for OS_Warning

  Revision 1.18  2003/12/29 04:27:24  yasu
  Workaround for OS_Warning, OS_Panic

  Revision 1.17  2003/12/25 00:21:16  nishida_kenji
  Removed INLINE macro(use inline)

  Revision 1.16  2003/12/09 06:44:50  nishida_kenji
  Added SDK_ALIGN4_ASSERT(exp)

  Revision 1.15  2003/12/09 04:59:12  nishida_kenji
  Small bug fix

  Revision 1.14  2003/12/09 04:48:57  nishida_kenji
  Additions:
  SDK_NULL_ASSERT(exp)
  SDK_MINMAX_ASSERT(exp,min,max)
  SDK_FATAL_ERROR(...)
  SDK_INTERNAL_ERROR(...)

  Revision 1.13  2003/12/02 12:09:22  yasu
  Make arrangement for fact that the preprocessor in the assembler interprets #<SPACE> as a comment.

  Revision 1.12  2003/12/01 00:47:40  nishida_kenji
  Defined SDK_IFDEFCPP and SDK_ENDIFCPP

  Revision 1.11  2003/11/17 01:20:28  yasu
  Small bug fix

  Revision 1.10  2003/11/17 00:49:06  yada
  Corrected OS_Warning() definition mistakes

  Revision 1.9  2003/11/17 00:34:41  yasu
  Separated OS_Printf etc. to iris/os/printf.h and changed so include is done on them

  Revision 1.8  2003/11/17 00:00:42  yada
  Added prototype definitions OS_Printf(), OS_Warning() and OS_Panic()

  Revision 1.7  2003/11/14 07:54:35  yada
  Corrected #ifdef IRIS_DEBUG to read  ->  #ifdef SDK_DEBUG

  Revision 1.6  2003/11/14 07:02:01  yada
  Minor revisions

  Revision 1.5  2003/11/14 06:58:11  yada
  (none)

  Revision 1.4  2003/11/14 06:51:14  yada
  Added definitions for SDK_WARNING(), SDK_ASSERT(), OS_Halt() and OS_Panic()

  Revision 1.3  2003/11/14 04:31:10  yada
  Added SDK_WARNING(x,msg)
  (just as placeholders for now)

  Revision 1.2  2003/11/11 08:56:31  yada
  Added SDK_ASSERTMSG(x,msg)

  Revision 1.1  2003/11/11 06:14:54  yada
  Moved from os directory

  Revision 1.1  2003/11/11 05:46:42  yada
  Initial version created


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MISC_H_
#define NITRO_MISC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/os/common/printf.h"

//--------------------------------------------------------------------------------
//  C++ macro
//
#ifdef __cplusplus
#define SDK_IFDEFCPP extern "C" {
#define SDK_ENDIFCPP }
#else
#define SDK_IFDEFCPP
#define SDK_ENDIFCPP
#endif

//--------------------------------------------------------------------------------
//      Assert
//
#ifdef  SDK_DEBUG
#ifndef SDK_ASSERT
#define SDK_ASSERT(exp) \
             (void) ((exp) || (OSi_Panic(__FILE__, __LINE__, "Failed assertion " #exp), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_ASSERT
#define SDK_ASSERT(exp)           ((void) 0)
#endif
#endif // SDK_DEBUG

/* Check done when compiling */
#define SDK_COMPILER_ASSERT(expr) \
    extern void sdk_compiler_assert ## __LINE__ ( char is[(expr) ? +1 : -1] )

//--------------------------------------------------------------------------------
//      Assert message
//
#ifdef  SDK_DEBUG
#ifndef SDK_ASSERTMSG
#define SDK_ASSERTMSG(exp, ...) \
    (void) ((exp) || (OSi_Panic(__FILE__, __LINE__, __VA_ARGS__), 0))
#endif
#ifndef SDK_TASSERTMSG
#define SDK_TASSERTMSG(exp, ...) \
    (void) ((exp) || (OSi_TPanic(__FILE__, __LINE__, __VA_ARGS__), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_ASSERTMSG
#define SDK_ASSERTMSG(exp, ...)     ((void) 0)
#endif
#ifndef SDK_TASSERTMSG
#define SDK_TASSERTMSG(exp, ...)    ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      Warning
//
#ifdef  SDK_DEBUG
#ifndef SDK_WARNING
#define SDK_WARNING(exp, ...) \
    (void) ((exp) || (OSi_Warning(__FILE__, __LINE__, __VA_ARGS__), 0))
#endif
#ifndef SDK_TWARNING
#define SDK_TWARNING(exp, ...) \
    (void) ((exp) || (OSi_TWarning(__FILE__, __LINE__, __VA_ARGS__), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_WARNING
#define SDK_WARNING(exp, ...)     ((void) 0)
#endif
#ifndef SDK_TWARNING
#define SDK_TWARNING(exp, ...)    ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      NULL Assert
//
#ifdef  SDK_DEBUG
#ifndef SDK_NULL_ASSERT
#define SDK_NULL_ASSERT(exp) \
             (void) (((exp) != NULL) || (OSi_Panic(__FILE__, __LINE__, "Pointer must not be NULL ("#exp")"), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_NULL_ASSERT
#define SDK_NULL_ASSERT(exp)           ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      Min Assert
//
#ifdef  SDK_DEBUG
#ifndef SDK_MIN_ASSERT
#define SDK_MIN_ASSERT(exp, min) \
             (void) (((exp) >= (min)) || \
                     (OSi_Panic(__FILE__, __LINE__, #exp " is out of bounds(%d)\n%d <= "#exp" not satisfied.", exp, min), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_MIN_ASSERT
#define SDK_MIN_ASSERT(exp, min)           ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      Max Assert
//
#ifdef  SDK_DEBUG
#ifndef SDK_MAX_ASSERT
#define SDK_MAX_ASSERT(exp, max) \
             (void) (((exp) <= (max)) || \
                     (OSi_Panic(__FILE__, __LINE__, #exp " is out of bounds(%d)\n"#exp" <= %d not satisfied.", exp, max), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_MAX_ASSERT
#define SDK_MAX_ASSERT(exp, max)           ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      Min Max Assert
//
#ifdef  SDK_DEBUG
#ifndef SDK_MINMAX_ASSERT
#define SDK_MINMAX_ASSERT(exp, min, max) \
             (void) (((exp) >= (min) && (exp) <= (max)) || \
                     (OSi_Panic(__FILE__, __LINE__, #exp " is out of bounds(%d)\n%d <= "#exp" <= %d not satisfied.", exp, min, max), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_MINMAX_ASSERT
#define SDK_MINMAX_ASSERT(exp, min, max)           ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      Fatal error
//
#ifdef  SDK_DEBUG
#ifndef SDK_FATAL_ERROR
#define SDK_FATAL_ERROR(...) \
    (void) (OSi_Panic(__FILE__, __LINE__, "Fatal Error\n"__VA_ARGS__), 0)
#endif
#ifndef SDK_TFATAL_ERROR
#define SDK_TFATAL_ERROR(...) \
    (void) (OSi_TPanic(__FILE__, __LINE__, "Fatal Error\n"__VA_ARGS__), 0)
#endif
#else  // SDK_DEBUG
#ifndef SDK_FATAL_ERROR
#define SDK_FATAL_ERROR(...)     ((void) 0)
#endif
#ifndef SDK_TFATAL_ERROR
#define SDK_TFATAL_ERROR(...)    ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      Internal error
//
#ifdef  SDK_DEBUG
#ifndef SDK_INTERNAL_ERROR
#define SDK_INTERNAL_ERROR(...) \
    (void) (OSi_Panic(__FILE__, __LINE__, "SDK Internal error\nPlease e-mail to nintendo\n" __VA_ARGS__), 0)
#endif
#ifndef SDK_TINTERNAL_ERROR
#define SDK_TINTERNAL_ERROR(...) \
    (void) (OSi_TPanic(__FILE__, __LINE__, "SDK Internal error\nPlease e-mail to nintendo\n" __VA_ARGS__), 0)
#endif
#else  // SDK_DEBUG
#ifndef SDK_INTERNAL_ERROR
#define SDK_INTERNAL_ERROR(...)     ((void) 0)
#endif
#ifndef SDK_TINTERNAL_ERROR
#define SDK_TINTERNAL_ERROR(...)    ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      Alignment error(4 bytes)
//
#ifdef  SDK_DEBUG
#ifndef SDK_ALIGN4_ASSERT
#define SDK_ALIGN4_ASSERT(exp) \
             (void) ((((u32)(exp) & 3) == 0) || (OSi_Panic(__FILE__, __LINE__, "Alignment Error(0x%x)\n"#exp" must be aligned to 4 bytes boundary.", exp), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_ALIGN4_ASSERT
#define SDK_ALIGN4_ASSERT(exp)           ((void) 0)
#endif
#endif // SDK_DEBUG

//--------------------------------------------------------------------------------
//      Alignment error(2 bytes)
//
#ifdef  SDK_DEBUG
#ifndef SDK_ALIGN2_ASSERT
#define SDK_ALIGN2_ASSERT(exp) \
             (void) ((((u32)(exp) & 1) == 0) || (OSi_Panic(__FILE__, __LINE__, "Alignment Error(0x%x)\n"#exp" must be aligned to 2 bytes boundary.", exp), 0))
#endif
#else  // SDK_DEBUG
#ifndef SDK_ALIGN2_ASSERT
#define SDK_ALIGN2_ASSERT(exp)           ((void) 0)
#endif
#endif // SDK_DEBUG


//--------------------------------------------------------------------------------
//       macros for linker

// specify force-link.
void    OSi_ReferSymbol(void *symbol);
#define SDK_REFER_SYMBOL(symbol) OSi_ReferSymbol((void*)(symbol))

// for embedding middleware version string in VERSION section.
#define SDK_MIDDLEWARE_STRING(vender, module) "[SDK+" vender ":" module "]"
#define SDK_DEFINE_MIDDLEWARE(id, vender, module) static char id [] = SDK_MIDDLEWARE_STRING(vender, module)
#define SDK_USING_MIDDLEWARE(id) SDK_REFER_SYMBOL(id)


//--------------------------------------------------------------------------------
//       macros for obsolete functions

SDK_INLINE
void*   OSi_AbortByUnsupportedRegister(const char *regname, const char *file, int line)
{
    (void)regname;
    (void)file;
    (void)line;
    OSi_TPanic(file, line, " I/O register \"%s\" is unsupported on this platform!", regname);
    return 0;
}
#define OS_UNSUPPORTED_REGADDR(reg) OSi_AbortByUnsupportedRegister(#reg, __FILE__, __LINE__)
#define OS_UNSUPPORTED_REG8(reg)    *(REGType8*)OSi_AbortByUnsupportedRegister(#reg, __FILE__, __LINE__)
#define OS_UNSUPPORTED_REG16(reg)   *(REGType16*)OSi_AbortByUnsupportedRegister(#reg, __FILE__, __LINE__)
#define OS_UNSUPPORTED_REG32(reg)   *(REGType32*)OSi_AbortByUnsupportedRegister(#reg, __FILE__, __LINE__)
#define OS_UNSUPPORTED_REG64(reg)   *(REGType64*)OSi_AbortByUnsupportedRegister(#reg, __FILE__, __LINE__)


//--------------------------------------------------------------------------------

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_MISC_H_ */
#endif
