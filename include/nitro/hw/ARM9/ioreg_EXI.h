/*---------------------------------------------------------------------------*
  Project:  NitroSDK - IO Register List - 
  File:     nitro/hw/ARM9/ioreg_EXI.h

  Copyright 2003-2004 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
//
//  I was generated automatically, don't edit me directly!!!
//
#ifndef NITRO_HW_ARM9_IOREG_EXI_H_
#define NITRO_HW_ARM9_IOREG_EXI_H_

#ifndef SDK_ASM
#include "nitro/types.h"
#include "nitro/hw/ARM9/mmap_global.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definition of Register offsets, addresses and variables.
 */


/* SIODATA32 */

#define REG_SIODATA32_OFFSET                               0x120
#define REG_SIODATA32_ADDR                                 (HW_REG_BASE + REG_SIODATA32_OFFSET)
#define reg_EXI_SIODATA32                                  (*( REGType32v *) REG_SIODATA32_ADDR)

/* SIOCNT */

#define REG_SIOCNT_OFFSET                                  0x128
#define REG_SIOCNT_ADDR                                    (HW_REG_BASE + REG_SIOCNT_OFFSET)
#define reg_EXI_SIOCNT                                     (*( REGType16v *) REG_SIOCNT_ADDR)

/* SIOSEL */

#define REG_SIOSEL_OFFSET                                  0x12c
#define REG_SIOSEL_ADDR                                    (HW_REG_BASE + REG_SIOSEL_OFFSET)
#define reg_EXI_SIOSEL                                     (*( REGType16v *) REG_SIOSEL_ADDR)


/*
 * Definitions of Register fields
 */


/* SIODATA32 */

#define REG_EXI_SIODATA32_H_SHIFT                          16
#define REG_EXI_SIODATA32_H_SIZE                           16
#define REG_EXI_SIODATA32_H_MASK                           0xffff0000

#define REG_EXI_SIODATA32_L_SHIFT                          0
#define REG_EXI_SIODATA32_L_SIZE                           16
#define REG_EXI_SIODATA32_L_MASK                           0x0000ffff

#ifndef SDK_ASM
#define REG_EXI_SIODATA32_FIELD( h, l ) \
    (u32)( \
    ((u32)(h) << REG_EXI_SIODATA32_H_SHIFT) | \
    ((u32)(l) << REG_EXI_SIODATA32_L_SHIFT))
#endif


/* SIOCNT */

#define REG_EXI_SIOCNT_TSEND_SHIFT                         3
#define REG_EXI_SIOCNT_TSEND_SIZE                          1
#define REG_EXI_SIOCNT_TSEND_MASK                          0x0008

#define REG_EXI_SIOCNT_TRECV_SHIFT                         2
#define REG_EXI_SIOCNT_TRECV_SIZE                          1
#define REG_EXI_SIOCNT_TRECV_MASK                          0x0004

#ifndef SDK_ASM
#define REG_EXI_SIOCNT_FIELD( tsend, trecv ) \
    (u16)( \
    ((u32)(tsend) << REG_EXI_SIOCNT_TSEND_SHIFT) | \
    ((u32)(trecv) << REG_EXI_SIOCNT_TRECV_SHIFT))
#endif


/* SIOSEL */

#define REG_EXI_SIOSEL_SEL_SHIFT                           0
#define REG_EXI_SIOSEL_SEL_SIZE                            1
#define REG_EXI_SIOSEL_SEL_MASK                            0x0001

#ifndef SDK_ASM
#define REG_EXI_SIOSEL_FIELD( sel ) \
    (u16)( \
    ((u32)(sel) << REG_EXI_SIOSEL_SEL_SHIFT))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_HW_ARM9_IOREG_EXI_H_ */
#endif
