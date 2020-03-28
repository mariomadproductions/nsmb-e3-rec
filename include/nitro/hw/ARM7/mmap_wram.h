/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include/sp - HW
  File:     mmap_wram.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mmap_wram.h,v $
  Revision 1.13  2005/02/28 05:26:27  yosizaki
  do-indent.

  Revision 1.12  2004/07/06 08:54:21  yasu
  Add Wireless driver reserved area

  Revision 1.11  2004/06/15 02:12:22  yada
  add HW_PRV_WRAM_DMA_CLEAR_DATA_BUF

  Revision 1.10  2004/05/21 11:14:49  yada
  add HW_PRV_WRAM_RED_RESERVED area

  Revision 1.9  2004/03/24 05:17:35  yada
  Make highest address position of ARM7 dedicated WRAM platform-independent.

  Revision 1.8  2004/03/23 07:41:29  yada
  Consideration for ARM-exclusive WRAM when not TEG

  Revision 1.7  2004/02/17 08:51:00  yada
  (none)

  Revision 1.6  2004/02/17 08:20:44  yada
  removed the fixed SYS mode stack position definition

  Revision 1.5  2004/02/16 09:38:30  yada
  Revised stack definitions
  Changed system reserved area: 0x20->0x40.

  Revision 1.4  2004/02/13 02:17:03  yada
  Changed stack size name.

  Revision 1.3  2004/02/12 13:32:25  yasu
  change include guards

  Revision 1.2  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.1  2003/12/22 14:05:31  yasu
  new additions

  Revision 1.1  2003/12/16 10:56:38  yasu
  Moved from spcode

  Revision 1.1  2003/12/16 06:29:59  ida
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_ARM7_HW_MMAP_WRAM_H_
#define NITRO_ARM7_HW_MMAP_WRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------
//  MEMORY MAP of WRAM
//----------------------------------------------------------------------
//---- stack size
#define HW_SVC_STACK_SIZE               0x40

//---- system reserved size
#define HW_PRV_WRAM_SYSRV_SIZE          0x40

//----------------------------------------------------------------
//---- stack address ( for initial stack pointer )
#define HW_PRV_WRAM_IRQ_STACK_END       (HW_PRV_WRAM_SVC_STACK)
#define HW_PRV_WRAM_SVC_STACK           (HW_PRV_WRAM_SVC_STACK_END - HW_SVC_STACK_SIZE)
#define HW_PRV_WRAM_SVC_STACK_END       (HW_PRV_WRAM_SYSRV)

//---- RED reserved
#define HW_PRV_WRAM_RED_RESERVED        (HW_PRV_WRAM + 0xfc00)  // 64 bytes
#define HW_PRV_WRAM_RED_RESERVED_END    (HW_PRV_WRAM + 0xfc40)

//---- offset in system reserved area
#define HW_PRV_WRAM_SYSRV               (HW_PRV_WRAM + HW_PRV_WRAM_SIZE - HW_PRV_WRAM_SYSRV_SIZE)
#define HW_PRV_WRAM_SYSRV_OFS_EXCP_VECTOR    0x1c
#define HW_PRV_WRAM_SYSRV_OFS_DMA_CLEAR_BUF  0x20       // 16bytes
#define HW_PRV_WRAM_SYSRV_OFS_WM_RESERVED_0  0x30
#define HW_PRV_WRAM_SYSRV_OFS_WM_RESERVED_1  0x34
#define HW_PRV_WRAM_SYSRV_OFS_INTR_CHECK     0x38
#define HW_PRV_WRAM_SYSRV_OFS_INTR_VECTOR    0x3c

//---- system reserved area 1
#define HW_EXCP_VECTOR_BUF              (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_EXCP_VECTOR)

//---- DMA clear data buffer for ARM7
#define HW_PRV_WRAM_DMA_CLEAR_DATA_BUF  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_DMA_CLEAR_BUF)

//---- MITSUMI reserved
#define HW_PRV_WRAM_MITSUMI_RESERVED_0  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_WM_RESERVED_0)
#define HW_PRV_WRAM_MITSUMI_RESERVED_1  (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_WM_RESERVED_1)

//---- system reserved area 2
#define HW_INTR_CHECK_BUF               (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_INTR_CHECK)
#define HW_INTR_VECTOR_BUF              (HW_PRV_WRAM_SYSRV + HW_PRV_WRAM_SYSRV_OFS_INTR_VECTOR)

#ifdef __cplusplus
} /* extern "C" */
#endif
/* NITRO_ARM7_HW_MMAP_WRAM_H_ */
#endif
