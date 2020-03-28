/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     context.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: context.h,v $
  Revision 1.20  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.19  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.18  2004/05/13 04:53:48  yada
  OS_CONTEXT_HAS_SP_SVC -> SDK_CONTEXT_HAS_SP_SVC

  Revision 1.17  2004/05/06 02:58:58  takano_makoto
  Add CPContext to OSContext.

  Revision 1.16  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.15  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.14  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.13  2003/12/25 07:29:11  yada
  Changes as per unified type rules

  Revision 1.12  2003/12/17 08:21:15  yasu
  Changed OS_InitContext arguments

  Revision 1.11  2003/12/16 07:14:34  yada
  Moved thread range information from context to thread structure

  Revision 1.10  2003/12/16 00:16:35  yada
  Included stack range information in thread

  Revision 1.9  2003/12/12 01:27:14  yada
  Corrected due to the name change of include (os/system.h and hw/armArch.h)

  Revision 1.8  2003/12/08 01:25:05  yasu
  Added SP_svc to 'context'

  Revision 1.7  2003/12/01 09:52:16  yasu
  Value saved in context changed: PC->PC+4

  Revision 1.6  2003/11/30 04:18:22  yasu
  Put CPU CPSR settings-related description in cpsr.h

  Revision 1.5  2003/11/28 02:53:01  yada
  Configured OS_MODE_BIT_MASK

  Revision 1.4  2003/11/27 13:44:33  yasu
  Added CPSR register 'bit' definitions

  Revision 1.3  2003/11/25 09:29:03  yasu
  Added OS_DumpContext

  Revision 1.2  2003/11/25 05:01:29  yasu
  Added to prototype declarations

  Revision 1.1  2003/11/25 04:32:38  yasu
  initial version additions

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_CONTEXT_H_
#define NITRO_OS_CONTEXT_H_

#include "nitro/os/common/system.h"
#ifdef SDK_ARM9
#include "nitro/cp/context.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
#define SDK_CONTEXT_HAS_SP_SVC

//----------------------------------------------------------------------------

#define OS_CONTEXT_CPSR      0
#define OS_CONTEXT_R0        4
#define OS_CONTEXT_R1        8
#define OS_CONTEXT_R2       12
#define OS_CONTEXT_R3       16
#define OS_CONTEXT_R4       20
#define OS_CONTEXT_R5       24
#define OS_CONTEXT_R6       28
#define OS_CONTEXT_R7       32
#define OS_CONTEXT_R8       36
#define OS_CONTEXT_R9       40
#define OS_CONTEXT_R10      44
#define OS_CONTEXT_R11      48
#define OS_CONTEXT_R12      52
#define OS_CONTEXT_R13      56
#define OS_CONTEXT_R14      60
#define OS_CONTEXT_PC_PLUS4 64         // Should be set to PC+4 for interrupt handling

#define OS_CONTEXT_SP       OS_CONTEXT_R13
#define OS_CONTEXT_LR       OS_CONTEXT_R14

#ifdef  SDK_CONTEXT_HAS_SP_SVC
#define OS_CONTEXT_R13_SVC  68
#define OS_CONTEXT_SP_SVC   OS_CONTEXT_R13_SVC
#endif

#ifdef SDK_ARM9
#ifdef SDK_CONTEXT_HAS_SP_SVC
#define OS_CONTEXT_CP_CONTEXT 72
#else
#define OS_CONTEXT_CP_CONTEXT 68
#endif
#endif


typedef struct OSContext
{
    u32     cpsr;
    u32     r[13];
    u32     sp;
    u32     lr;
    u32     pc_plus4;
#ifdef  SDK_CONTEXT_HAS_SP_SVC
    u32     sp_svc;
#endif
#ifdef  SDK_ARM9
    CPContext cp_context;
#endif
}
OSContext;


//----------------------------------------------------------------------------

void    OS_InitContext(OSContext *context, u32 newpc, u32 newsp);
BOOL    OS_SaveContext(OSContext *context);
void    OS_LoadContext(OSContext *context);
void    OS_DumpContext(OSContext *context);

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_CONTEXT_H_ */
#endif
