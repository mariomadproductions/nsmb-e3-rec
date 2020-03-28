/*---------------------------------------------------------------------------*
  Project:  NitroSDK - HW - include
  File:     mmap_tcm.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mmap_tcm.h,v $
  Revision 1.15  2006/01/18 02:11:30  kitase_hirotake
  do-indent

  Revision 1.14  2005/02/28 05:26:27  yosizaki
  do-indent.

  Revision 1.13  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.12  2004/03/30 04:51:14  yada
  removed the line defining HW_DTCM_ARENA_HI_MAX

  Revision 1.11  2004/02/17 08:20:44  yada
  removed the fixed SYS mode stack position definition

  Revision 1.10  2004/02/16 09:37:57  yada
  added definition for stack start address

  Revision 1.9  2004/02/09 11:32:48  yada
  made so that the size of the array is obtained from a size definition
  deleted OS_GetDTCM()

  Revision 1.8  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.7  2004/01/27 00:12:08  yada
  revised size of DTCM internal reserved area, etc

  Revision 1.6  2004/01/16 04:12:04  yada
  revised stack size definition

  Revision 1.5  2004/01/15 08:25:44  yada
  comments added

  Revision 1.4  2004/01/08 12:04:00  yada
  added 0x20 to DTCM reserved area

  Revision 1.3  2004/01/07 01:41:54  yada
  defined default Lo/Hi values for DTCM, ITCM arenas

  Revision 1.2  2003/12/22 13:37:18  yasu
  put OS_GetDTCM in a macro

  Revision 1.1  2003/12/17 06:05:39  yasu
  split mmap_reserved.h into mmap_tcm.h and mmap_shared.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_HW_MMAP_TCM_H_
#define NITRO_HW_MMAP_TCM_H_

#ifdef __cplusplus
extern "C" {
#endif


//----------------------------------------------------------------------
//  size definition in DTCM
//----------------------------------------------------------------------
//---- stack size
#define HW_SYS_AND_IRQ_STACK_SIZE_MAX   (HW_DTCM_SIZE - HW_SVC_STACK_SIZE - HW_DTCM_SYSRV_SIZE)
#define HW_SVC_STACK_SIZE               0x40

//---- system reserved size
#define HW_DTCM_SYSRV_SIZE              0x40


//----------------------------------------------------------------------
//  structure of DTCM
//----------------------------------------------------------------------
#ifndef SDK_ASM
#include "nitro/types.h"

typedef volatile struct
{
    //---- stack/heap area
    u8      sys_and_irq_stack[HW_SYS_AND_IRQ_STACK_SIZE_MAX];   // 0000-3f80 system & irq stack
    u8      svc_stack[HW_SVC_STACK_SIZE];       // 3f80-3fbf svc stack

    //---- system reserved area
    u8      reserved[HW_DTCM_SYSRV_SIZE - 8];   // 3fc0-3ff7 ????
    u32     intr_check;                // 3ff8-3ffb intr_check for svc
    void   *intr_vector;               // 3ffc-3fff intr handler

}
OS_DTCM;
#endif

//----------------------------------------------------------------------
//  other definition
//----------------------------------------------------------------------
//---- stack address ( for initial stack pointer )
#define HW_DTCM_SYS_STACK_DEFAULT       (HW_DTCM)
#define HW_DTCM_IRQ_STACK_END           (HW_DTCM_SVC_STACK)
#define HW_DTCM_SVC_STACK               (HW_DTCM_SVC_STACK_END - HW_SVC_STACK_SIZE)
#define HW_DTCM_SVC_STACK_END           (HW_DTCM + 0x00003fc0)

//---- offset in system reserved area
#define HW_DTCM_SYSRV_OFS_DEBUGGER      0x00
#define HW_DTCM_SYSRV_OFS_EXCP_VECTOR   0x1c
#define HW_DTCM_SYSRV_OFS_RESERVED      0x20
#define HW_DTCM_SYSRV_OFS_INTR_CHECK    0x38
#define HW_DTCM_SYSRV_OFS_INTR_VECTOR   0x3c

//---- system reserved area
#define HW_DTCM_SYSRV                   (HW_DTCM + 0x00003fc0)
#define HW_EXCP_VECTOR_BUF              (HW_DTCM_SYSRV + HW_DTCM_SYSRV_OFS_EXCP_VECTOR)
#define HW_INTR_CHECK_BUF               (HW_DTCM_SYSRV + HW_DTCM_SYSRV_OFS_INTR_CHECK)
#define HW_INTR_VECTOR_BUF              (HW_DTCM_SYSRV + HW_DTCM_SYSRV_OFS_INTR_VECTOR)

#ifdef  SDK_CWBUG_VSNPRINTF
// workaround until vsnprintf supports anti-strb
// allocate DTCM for string buffer
#define HW_DTCM_STRING_SIZE             256
#define HW_DTCM_STRING                  HW_DTCM
#endif

//----------------------------------------------------------------------
//  definition for Arena
//----------------------------------------------------------------------
//---- default address for DTCM Arena
#define HW_DTCM_ARENA_LO_DEFAULT        HW_DTCM
#define HW_DTCM_ARENA_HI_DEFAULT        HW_DTCM

//---- default address for ITCM Arena
#define HW_ITCM_ARENA_LO_DEFAULT        HW_ITCM
#define HW_ITCM_ARENA_HI_DEFAULT        HW_ITCM_END


#ifdef __cplusplus
} /* extern "C" */
#endif
/* NITRO_HW_MMAP_TCM_H_ */
#endif
