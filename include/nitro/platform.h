/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include
  File:     platform.h

  Copyright 2006,2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: platform.h,v $
  Revision 1.3  2007/08/22 05:22:32  yosizaki
  Fixed dependencies.

  Revision 1.2  2007/02/20 00:28:10  kitase_hirotake
  Indented source

  Revision 1.1  2006/06/27 08:21:58  yosizaki
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_PLATFORM_HEADER__
#define NITRO_PLATFORM_HEADER__


// for OS_DisableInterrupts()
#include "nitro/os/common/system.h"


/*****************************************************************************/
/* Shared definitions */

/* Endian and bit-order definitions */
#define PLATFORM_ENDIAN_BIG     0
#define PLATFORM_ENDIAN_LITTLE  1


/*****************************************************************************/
/* Platform-specific definitions */

/* Endian (PLATFORM_ENDIAN_*) */
#define PLATFORM_BYTES_ENDIAN           PLATFORM_ENDIAN_LITTLE

/* When accessing data, if a boundary alignment is needed with the access width, it is 1, otherwise it is 0. */
#define PLATFORM_BYTES_ALIGN            1

/* The size of the cache line that the program needs to be aware of (1 if not needed) */
#define PLATFORM_CACHE_SIZE             32

/* The modifier designated by the variable that shows cache line boundary alignment is needed (empty definition if not needed) */
#define PLATFORM_ATTRIBUTE_CACHEALIGN   ATTRIBUTE_ALIGN(32)

/* Interrupt prohibition functions that can be called at the start of the block */
#define PLATFORM_ENTER_CRITICALSECTION()    OSIntrMode bak_interrupt_mode_ = OS_DisableInterrupts()

/* Interrupt cancellation functions paired up with the functions above */
#define PLATFORM_LEAVE_CRITICALSECTION()    (void)OS_RestoreInterrupts(bak_interrupt_mode_)


/*****************************************************************************/
/* Processing-specific definitions */

#if	defined(SDK_CW) || defined(__MWERKS__)

/* The order in which the bit field was filled (PLATFORM_ENDIAN_*) */
#define PLATFORM_BITFIELDS_ENDIAN       PLATFORM_ENDIAN_LITTLE

/* Macro for determining validity when compiling */
#define PLATFORM_COMPILER_ASSERT(expr) \
    extern void platform_compiler_assert ## __LINE__ (char is[(expr) ? +1 : -1])

/*
 * So that the structure is not padded with a value larger than the maximum member size, this modifier makes an explicit specification after the } of the structure definition.
 * 
 */
#define PLATFORM_STRUCT_PADDING_FOOTER

/* Function inline specifier */
#define PLATFORM_ATTRIBUTE_INLINE       SDK_INLINE


#else
# TO BE DEFINED
#endif


/*****************************************************************************/
/* Shared type definitions */

/*
 * Size-specified integer structure
 *
 * For the integer data that is exchanged via external devices or communication pathways, these are used in place of integrated types for the purpose of asserting the prohibition on improper direct access.
 * 
 * When storing from an integrated type to this structure, use some MI_Store* function. When referencing a value from this structure, use some MI_Load* function.
 * 
 */

/* 8-bit little endian type */
typedef struct PLATFORM_LE8
{
    unsigned char byte[1];
}
PLATFORM_STRUCT_PADDING_FOOTER PLATFORM_LE8;

/* 16-bit little endian type */
typedef struct PLATFORM_LE16
{
    unsigned char byte[2];
}
PLATFORM_STRUCT_PADDING_FOOTER PLATFORM_LE16;

/* 32-bit little endian type */
typedef struct PLATFORM_LE32
{
    unsigned char byte[4];
}
PLATFORM_STRUCT_PADDING_FOOTER PLATFORM_LE32;

/* 8-bit big endian type */
typedef struct PLATFORM_BE8
{
    unsigned char byte[1];
}
PLATFORM_STRUCT_PADDING_FOOTER PLATFORM_BE8;

/* 16-bit big endian type */
typedef struct PLATFORM_BE16
{
    unsigned char byte[2];
}
PLATFORM_STRUCT_PADDING_FOOTER PLATFORM_BE16;

/* 32-bit big endian type */
typedef struct PLATFORM_BE32
{
    unsigned char byte[4];
}
PLATFORM_STRUCT_PADDING_FOOTER PLATFORM_BE32;


/*****************************************************************************/


#endif /* NINTENDO_PLATFORM_HEADER__ */
