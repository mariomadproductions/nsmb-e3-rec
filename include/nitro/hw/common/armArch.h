/*---------------------------------------------------------------------------*
  Project:  NitroSDK - HW - include
  File:     armArch.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: armArch.h,v $
  Revision 1.12  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.11  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.10  2004/05/03 04:50:46  yada
  added HW_CPU_CLOCK*

  Revision 1.9  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.8  2004/03/16 11:53:06  yasu
  move HW_READ32/WRITE32 -> MI_ReadWord/WriteWord

  Revision 1.7  2004/02/25 11:28:59  yada
  added HW_SYSTEM_CLOCK

  Revision 1.6  2004/02/14 06:32:31  yasu
  added HW_READ43/WRITE32 macros

  Revision 1.5  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.4  2003/12/18 01:52:47  yada
  added shift amount for data cache and instruction cache enable flags

  Revision 1.3  2003/12/17 11:38:48  yada
  added cache definitions

  Revision 1.2  2003/12/12 01:29:00  yada
  added HW_PSR_ARM_STATE

  Revision 1.1  2003/12/12 01:24:46  yada
  name change hw/systemControl.h -> hw/armArch.h

  Revision 1.2  2003/11/28 01:55:16  yada
  Reflects REDSDK 03-11-27

  Revision 1.1  2003/11/04 09:11:24  yada
  initial version (maybe not very consistent)


  $NoKeywords: $

 *---------------------------------------------------------------------------*/

#ifndef NITRO_HW_SYSTEMCONTROL_H_
#define NITRO_HW_SYSTEMCONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HW_ICACHE_SIZE              0x2000      //   Instruction cache
#define HW_DCACHE_SIZE              0x1000      // Data cache
#define HW_CACHE_LINE_SIZE          32

#define HW_SYSTEM_CLOCK             33514000    // Exactly 33513982?

#define HW_CPU_CLOCK_ARM7           33513982
#define HW_CPU_CLOCK_ARM9           67027964

#ifdef SDK_ARM7
#define HW_CPU_CLOCK                HW_CPU_CLOCK_ARM7
#else
#define HW_CPU_CLOCK                HW_CPU_CLOCK_ARM9
#endif

//**********************************************************************
//              IRIS register control bits
//**********************************************************************

//----------------------------------------------------------------------
//                  Programs status registers
//----------------------------------------------------------------------

#define HW_PSR_CPU_MODE_MASK       0x1f // CPU mode

#define HW_PSR_USER_MODE           0x10 // USER
#define HW_PSR_FIQ_MODE            0x11 // FIQ
#define HW_PSR_IRQ_MODE            0x12 // IRQ
#define HW_PSR_SVC_MODE            0x13 // Supervisor
#define HW_PSR_ABORT_MODE          0x17 // Abort (prefetch/data)
#define HW_PSR_UNDEF_MODE          0x1b // Undefined instruction
#define HW_PSR_SYS_MODE            0x1f // System

#define HW_PSR_ARM_STATE           0x0 // ARM state
#define HW_PSR_THUMB_STATE         0x20 // THUMB state

#define HW_PSR_FIQ_DISABLE         0x40 // Disable FIQ
#define HW_PSR_IRQ_DISABLE         0x80 // Disable IRQ
#define HW_PSR_IRQ_FIQ_DISABLE     0xc0 // Disable FIQ and IRQ

#define HW_PSR_Q_FLAG              0x08000000   // Sticky overflow
#define HW_PSR_V_FLAG              0x10000000   // Overflow
#define HW_PSR_C_FLAG              0x20000000   // Carry / borrow / extend
#define HW_PSR_Z_FLAG              0x40000000   // Zero
#define HW_PSR_N_FLAG              0x80000000   // Minus / less than


//----------------------------------------------------------------------
//                  System control coprocessor
//----------------------------------------------------------------------

// Register 1 (Master control)

#define HW_C1_SB1_BITSET           0x00000078   // 1 fixed bit row for register 1

#define HW_C1_ITCM_LOAD_MODE       0x00080000   // Instruction TCM load mode
#define HW_C1_DTCM_LOAD_MODE       0x00020000   // Data TCM load mode
#define HW_C1_ITCM_ENABLE          0x00040000   // Enable instruction TCM
#define HW_C1_DTCM_ENABLE          0x00010000   // Enable data TCM
#define HW_C1_LD_INTERWORK_DISABLE 0x00008000   // Disable interworking with Load instruction
#define HW_C1_CACHE_ROUND_ROBIN    0x00004000   // Cache replacement algorithm, round robin (Worst time bit ratio will stabilize)
#define HW_C1_CACHE_PSEUDO_RANDOM  0x00000000   //                            Pseudo random
#define HW_C1_EXCEPT_VEC_UPPER     0x00002000   // Exception vector High-order address (set to this)
#define HW_C1_EXCEPT_VEC_LOWER     0x00000000   //                  Lower-order address
#define HW_C1_ICACHE_ENABLE        0x00001000   // Enable instruction cache
#define HW_C1_DCACHE_ENABLE        0x00000004   // Enable data cache
#define HW_C1_LITTLE_ENDIAN        0x00000000   // Little-endian
#define HW_C1_BIG_ENDIAN           0x00000080   // Big-endian
#define HW_C1_PROTECT_UNIT_ENABLE  0x00000001   // Enable protection unit

#define HW_C1_ICACHE_ENABLE_SHIFT 12
#define HW_C1_DCACHE_ENABLE_SHIFT 2


// Register 2 (Protection region cache setting)

#define HW_C2_PR0_SFT              0   // Protection region 0
#define HW_C2_PR1_SFT              1   //                   1
#define HW_C2_PR2_SFT              2   //                   2
#define HW_C2_PR3_SFT              3   //                   3
#define HW_C2_PR4_SFT              4   //                   4
#define HW_C2_PR5_SFT              5   //                   5
#define HW_C2_PR6_SFT              6   //                   6
#define HW_C2_PR7_SFT              7   //                   7


// Register 3 (Protection region write buffer settings)

#define HW_C3_PR0_SFT              0   // Protection region 0
#define HW_C3_PR1_SFT              1   //                   1
#define HW_C3_PR2_SFT              2   //                   2
#define HW_C3_PR3_SFT              3   //                   3
#define HW_C3_PR4_SFT              4   //                   4
#define HW_C3_PR5_SFT              5   //                   5
#define HW_C3_PR6_SFT              6   //                   6
#define HW_C3_PR7_SFT              7   //                   7


// Register 5 (Protection region access permission)

#define HW_C5_PERMIT_MASK          0xf // Protection region access permission mask

#define HW_C5_PERMIT_NA            0   //                  Access not permitted
#define HW_C5_PERMIT_RW            1   //                  Read write permitted
#define HW_C5_PERMIT_RO            5   //                  Read only permitted

#define HW_C5_PR0_SFT              0   // Protection region 0
#define HW_C5_PR1_SFT              4   //                   1
#define HW_C5_PR2_SFT              8   //                   2
#define HW_C5_PR3_SFT              12  //                   3
#define HW_C5_PR4_SFT              16  //                   4
#define HW_C5_PR5_SFT              20  //                   5
#define HW_C5_PR6_SFT              24  //                   6
#define HW_C5_PR7_SFT              28  //                   7


// Register 6 (protection region base address / size)

#define HW_C6_PR_SIZE_MASK         0x0000003e   // Protection region size
#define HW_C6_PR_BASE_MASK         0xfffff000   //                  base address

#define HW_C6_PR_SIZE_SHIFT        1
#define HW_C6_PR_BASE_SHIFT        12

#define HW_C6_PR_ENABLE            1   // Enable Protection region
#define HW_C6_PR_DISABLE           0   //                  disable

#define HW_C6_PR_4KB               0x16 // Region size  4KByte
#define HW_C6_PR_8KB               0x18 //              8KB
#define HW_C6_PR_16KB              0x1a //             16KB
#define HW_C6_PR_32KB              0x1c //             32KB
#define HW_C6_PR_64KB              0x1e //             64KB
#define HW_C6_PR_128KB             0x20 //             128KB
#define HW_C6_PR_256KB             0x22 //             256KB
#define HW_C6_PR_512KB             0x24 //             512KB
#define HW_C6_PR_1MB               0x26 //               1MB
#define HW_C6_PR_2MB               0x28 //               2MB
#define HW_C6_PR_4MB               0x2a //               4MB
#define HW_C6_PR_8MB               0x2c //               8MB
#define HW_C6_PR_16MB              0x2e //              16MB
#define HW_C6_PR_32MB              0x30 //              32MB
#define HW_C6_PR_64MB              0x32 //              64MB
#define HW_C6_PR_128MB             0x34 //             128MB
#define HW_C6_PR_256MB             0x36 //             256MB
#define HW_C6_PR_512MB             0x38 //             512MB
#define HW_C6_PR_1GB               0x3a //               1GB
#define HW_C6_PR_2GB               0x3c //               2GB
#define HW_C6_PR_4GB               0x3e //               4GB


// Register  7.13 (Instruction cache prefetch)

#define HW_C7_ICACHE_PREFCHP_MASK  0xffffffe0   // Instruction cache prefetch address


// Registers 7.10, 7.14 (Cache index operation)

#define HW_C7_ICACHE_INDEX_MASK    0x00000fe0   // Instruction cache index
#define HW_C7_DCACHE_INDEX_MASK    0x000003e0   // Data cache index
#define HW_C7_CACHE_SET_NO_MASK    0xc0000000   // Cache set No.

#define HW_C7_CACHE_INDEX_SHIFT    5
#define HW_C7_CACHE_SET_NO_SHIFT   30


// Register 9.0 (cache lockdown)

#define HW_C9_LOCKDOWN_SET_NO_MASK 0x00000003   // Cache lockdown set No.

#define HW_C9_LOCKDOWN_SET_NO_SHIFT 0

#define HW_C9_LOCKDOWN_LOAD_MODE   0x80000000   // Cache lockdown load mode


// Register 9.1 (TCM base address / size)

#define HW_C9_TCMR_SIZE_MASK       0x0000003e   // TCM region size
#define HW_C9_TCMR_BASE_MASK       0xfffff000   //                  base address

#define HW_C9_TCMR_SIZE_SHIFT      1
#define HW_C9_TCMR_BASE_SHIFT      12

#define HW_C9_TCMR_4KB             0x06 // Region size  4KByte
#define HW_C9_TCMR_8KB             0x08 //              8KB
#define HW_C9_TCMR_16KB            0x0a //             16KB
#define HW_C9_TCMR_32KB            0x0c //             32KB
#define HW_C9_TCMR_64KB            0x0e //             64KB
#define HW_C9_TCMR_128KB           0x10 //            128KB
#define HW_C9_TCMR_256KB           0x12 //            256KB
#define HW_C9_TCMR_512KB           0x14 //            512KB
#define HW_C9_TCMR_1MB             0x16 //              1MB
#define HW_C9_TCMR_2MB             0x18 //              2MB
#define HW_C9_TCMR_4MB             0x1a //              4MB
#define HW_C9_TCMR_8MB             0x1c //              8MB
#define HW_C9_TCMR_16MB            0x1e //             16MB
#define HW_C9_TCMR_32MB            0x20 //             32MB
#define HW_C9_TCMR_64MB            0x22 //             64MB
#define HW_C9_TCMR_128MB           0x24 //            128MB
#define HW_C9_TCMR_256MB           0x26 //            256MB
#define HW_C9_TCMR_512MB           0x28 //            512MB
#define HW_C9_TCMR_1GB             0x2a //              1GB
#define HW_C9_TCMR_2GB             0x2c //              2GB
#define HW_C9_TCMR_4GB             0x2e //              4GB

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_HW_SYSTEMCONTROL_H_ */
#endif
