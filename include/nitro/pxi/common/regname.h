/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include - PXI
  File:     regname.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: regname.h,v $
  Revision 1.3  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.2  2004/05/14 09:34:00  yasu
  add ARM9/ARM7 sync in PXI_Init

  Revision 1.1  2004/03/04 08:44:26  yasu
  add defines for fifo access

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PXI_COMMON_REGNAME_H_
#define NITRO_PXI_COMMON_REGNAME_H_

#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Register rename
typedef enum
{
    PXI_PROC_ARM9 = 0,
    PXI_PROC_ARM7 = 1
}
PXIProc;

#ifdef	SDK_ARM9

#define	PXI_PROC_ARM			 PXI_PROC_ARM9

#define reg_PXI_FIFO_CNT                 reg_PXI_SUBP_FIFO_CNT
#define REG_PXI_FIFO_CNT_ERR_MASK        REG_PXI_SUBP_FIFO_CNT_ERR_MASK
#define REG_PXI_FIFO_CNT_SEND_CL_MASK    REG_PXI_SUBP_FIFO_CNT_SEND_CL_MASK
#define REG_PXI_FIFO_CNT_SEND_FULL_MASK  REG_PXI_SUBP_FIFO_CNT_SEND_FULL_MASK
#define REG_PXI_FIFO_CNT_SEND_TI_MASK    REG_PXI_SUBP_FIFO_CNT_SEND_TI_MASK
#define REG_PXI_FIFO_CNT_RECV_RI_MASK    REG_PXI_SUBP_FIFO_CNT_RECV_RI_MASK
#define REG_PXI_FIFO_CNT_RECV_EMP_MASK   REG_PXI_SUBP_FIFO_CNT_RECV_EMP_MASK
#define REG_PXI_FIFO_CNT_E_MASK          REG_PXI_SUBP_FIFO_CNT_E_MASK

#define reg_PXI_INTF                     reg_PXI_SUBPINTF
#define	REG_PXI_INTF_I_MASK		 REG_PXI_SUBPINTF_I_MASK
#define REG_PXI_INTF_IREQ_MASK		 REG_PXI_SUBPINTF_IREQ_MASK
#define	REG_PXI_INTF_SEND_MASK		 REG_PXI_SUBPINTF_A9STATUS_MASK
#define	REG_PXI_INTF_SEND_SHIFT		 REG_PXI_SUBPINTF_A9STATUS_SHIFT
#define	REG_PXI_INTF_RECV_MASK		 REG_PXI_SUBPINTF_A7STATUS_MASK
#define	REG_PXI_INTF_RECV_SHIFT		 REG_PXI_SUBPINTF_A7STATUS_SHIFT

#else  // SDK_ARM7

#define	PXI_PROC_ARM			 PXI_PROC_ARM7

#define reg_PXI_FIFO_CNT                 reg_PXI_MAINP_FIFO_CNT
#define REG_PXI_FIFO_CNT_ERR_MASK        REG_PXI_MAINP_FIFO_CNT_ERR_MASK
#define REG_PXI_FIFO_CNT_SEND_CL_MASK    REG_PXI_MAINP_FIFO_CNT_SEND_CL_MASK
#define REG_PXI_FIFO_CNT_SEND_FULL_MASK  REG_PXI_MAINP_FIFO_CNT_SEND_FULL_MASK
#define REG_PXI_FIFO_CNT_SEND_TI_MASK    REG_PXI_MAINP_FIFO_CNT_SEND_TI_MASK
#define REG_PXI_FIFO_CNT_RECV_RI_MASK    REG_PXI_MAINP_FIFO_CNT_RECV_RI_MASK
#define REG_PXI_FIFO_CNT_RECV_EMP_MASK   REG_PXI_MAINP_FIFO_CNT_RECV_EMP_MASK
#define REG_PXI_FIFO_CNT_E_MASK          REG_PXI_MAINP_FIFO_CNT_E_MASK

#define reg_PXI_INTF                     reg_PXI_MAINPINTF
#define	REG_PXI_INTF_I_MASK		 REG_PXI_MAINPINTF_I_MASK
#define REG_PXI_INTF_IREQ_MASK		 REG_PXI_MAINPINTF_IREQ_MASK
#define	REG_PXI_INTF_SEND_MASK		 REG_PXI_MAINPINTF_A9STATUS_MASK
#define	REG_PXI_INTF_SEND_SHIFT		 REG_PXI_MAINPINTF_A9STATUS_SHIFT
#define	REG_PXI_INTF_RECV_MASK		 REG_PXI_MAINPINTF_A7STATUS_MASK
#define	REG_PXI_INTF_RECV_SHIFT		 REG_PXI_MAINPINTF_A7STATUS_SHIFT

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* NITRO_PXI_COMMON_REGNAME_H_ */
#endif
