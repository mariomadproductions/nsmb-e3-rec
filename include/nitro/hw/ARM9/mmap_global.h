/*---------------------------------------------------------------------------*
  Project:  NitroSDK - HW - include
  File:     mmap_global.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mmap_global.h,v $
  Revision 1.16  2005/02/28 05:26:27  yosizaki
  do-indent.

  Revision 1.15  2004/08/03 03:16:00  yasu
  Fix error when assembler source code includes nitro.h

  Revision 1.14  2004/07/23 12:11:27  yada
  include types.h

  Revision 1.13  2004/07/23 10:59:46  yada
  if SDK_TS, DTCM address is given from SDK_AUTOLOAD_DTCM_START

  Revision 1.12  2004/05/19 09:06:00  yada
  fix HW_LCDC_VRAM_END. separate by TS or other

  Revision 1.11  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.10  2004/04/06 04:33:31  takano_makoto
  Add entry of HW_EXT_WRAM_ARM7.

  Revision 1.9  2004/02/17 08:22:07  yada
  Reshaped tab

  Revision 1.8  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.7  2004/02/02 00:25:37  nishida_kenji
  fix HW_DB_BG_PLTT and HW_DB_OBJ_PLTT.

  Revision 1.6  2004/01/22 08:40:38  nishida_kenji
  for the 2nd display

  Revision 1.5  2004/01/15 08:26:09  yada
  Set HW_ITCM_IMAGE

  Revision 1.4  2003/12/17 06:05:39  yasu
  split mmap_reserved.h into mmap_tcm.h and mmap_shared.h

  Revision 1.3  2003/12/09 08:35:26  yasu
  Revamped the memory map and the related area

  Revision 1.2  2003/12/08 12:18:31  yada
  Applied modification just so it would run. Required revisions.

  Revision 1.1  2003/12/08 09:08:53  yasu
  New memory map

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_HW_MMAP_GLOBAL_H_
#define NITRO_HW_MMAP_GLOBAL_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// GLOBAL MEMORY MAP
//---------------------------------------------------------------------------

//----------------------------- ITCM
#define HW_ITCM_IMAGE           0x01000000
#define HW_ITCM                 0x01ff8000
#define HW_ITCM_SIZE            0x8000
#define HW_ITCM_END             (HW_ITCM + HW_ITCM_SIZE)

//----------------------------- DTCM
#ifndef	SDK_ASM
#include "nitro/types.h"
extern u32 SDK_AUTOLOAD_DTCM_START[];
#define HW_DTCM                 ((u32)SDK_AUTOLOAD_DTCM_START)
#else
.extern SDK_AUTOLOAD_DTCM_START
#define HW_DTCM                 SDK_AUTOLOAD_DTCM_START
#endif
#define HW_DTCM_SIZE            0x4000
#define HW_DTCM_END             (HW_DTCM + HW_DTCM_SIZE)
//----------------------------- MAIN
#define HW_MAIN_MEM             0x02000000
#define HW_MAIN_MEM_SIZE        0x00400000
#define HW_MAIN_MEM_EX_SIZE     0x00800000
#define HW_MAIN_MEM_END         (HW_MAIN_MEM + HW_MAIN_MEM_SIZE)
#define HW_MAIN_MEM_EX_END      (HW_MAIN_MEM + HW_MAIN_MEM_EX_SIZE)
//----------------------------- WRAMs
#define HW_WRAM                 0x037f8000
#define HW_WRAM_END             0x03800000
#define HW_WRAM_SIZE            (HW_WRAM_END-HW_WRAM)
//----------------------------- IOs
#define HW_IOREG                0x04000000
#define HW_IOREG_END            0x05000000
#define HW_REG_BASE             HW_IOREG        // alias
//----------------------------- VRAMs
#define HW_BG_PLTT              0x05000000
#define HW_BG_PLTT_END          0x05000200
#define HW_BG_PLTT_SIZE         (HW_BG_PLTT_END-HW_BG_PLTT)
#define HW_OBJ_PLTT             0x05000200
#define HW_OBJ_PLTT_END         0x05000400
#define HW_OBJ_PLTT_SIZE        (HW_OBJ_PLTT_END-HW_OBJ_PLTT)
#define HW_PLTT                 HW_BG_PLTT
#define HW_PLTT_END             HW_OBJ_PLTT_END
#define HW_PLTT_SIZE            (HW_PLTT_END-HW_PLTT)
#define HW_DB_BG_PLTT           0x05000400
#define HW_DB_BG_PLTT_END       0x05000600
#define HW_DB_BG_PLTT_SIZE      (HW_DB_BG_PLTT_END-HW_DB_BG_PLTT)
#define HW_DB_OBJ_PLTT          0x05000600
#define HW_DB_OBJ_PLTT_END      0x05000800
#define HW_DB_OBJ_PLTT_SIZE     (HW_DB_OBJ_PLTT_END-HW_DB_OBJ_PLTT)
#define HW_DB_PLTT              HW_DB_BG_PLTT
#define HW_DB_PLTT_END          HW_DB_OBJ_PLTT_END
#define HW_DB_PLTT_SIZE         (HW_DB_PLTT_END-HW_DB_PLTT)
#define HW_BG_VRAM              0x06000000
#define HW_BG_VRAM_END          0x06080000
#define HW_BG_VRAM_SIZE         (HW_BG_VRAM_END-HW_BG_VRAM)
#define HW_DB_BG_VRAM           0x06200000
#define HW_DB_BG_VRAM_END       0x06220000
#define HW_DB_BG_VRAM_SIZE      (HW_DB_BG_VRAM_END-HW_DB_BG_VRAM)
#define HW_OBJ_VRAM             0x06400000
#define HW_OBJ_VRAM_END         0x06440000
#define HW_OBJ_VRAM_SIZE        (HW_OBJ_VRAM_END-HW_OBJ_VRAM)
#define HW_DB_OBJ_VRAM          0x06600000
#define HW_DB_OBJ_VRAM_END      0x06620000
#define HW_DB_OBJ_VRAM_SIZE     (HW_DB_OBJ_VRAM_END-HW_DB_OBJ_VRAM)
#define HW_LCDC_VRAM            0x06800000
#ifdef SDK_TS
#define HW_LCDC_VRAM_END        0x068A4000
#else
#define HW_LCDC_VRAM_END        0x06898000
#endif
#define HW_LCDC_VRAM_SIZE       (HW_LCDC_VRAM_END-HW_LCDC_VRAM)
#define HW_OAM                  0x07000000
#define HW_OAM_END              0x07000400
#define HW_OAM_SIZE             (HW_OAM_END-HW_OAM)
#define HW_DB_OAM               0x07000400
#define HW_DB_OAM_END           0x07000800
#define HW_DB_OAM_SIZE          (HW_DB_OAM_END-HW_DB_OAM)
//----------------------------- Cartridge Bus
#define HW_CTRDG_ROM            0x08000000
#define HW_CTRDG_ROM_END        0x0a000000
#define HW_CTRDG_RAM            0x0a000000
#define HW_CTRDG_RAM_END        0x0a010000
//----------------------------- System ROM
#define HW_BIOS                 0xffff0000
#define HW_BIOS_END             0xffff8000
#define HW_RESET_VECTOR         0xffff0000
//----------------------------- for request to ARM7
#define HW_EXT_WRAM_ARM7         0x06000000
#define HW_EXT_WRAM_ARM7_END     0x06040000
#define HW_EXT_WRAM_ARM7_SIZE    (HW_EXT_WRAM_ARM7_END-HW_EXT_WRAM_ARM7)
#ifdef __cplusplus
} /* extern "C" */
#endif
/* NITRO_HW_MMAP_GLOBAL_H_ */
#endif
