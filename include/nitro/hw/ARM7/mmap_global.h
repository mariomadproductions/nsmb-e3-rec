/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include/sp - HW
  File:     mmap_global.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mmap_global.h,v $
  Revision 1.13  2005/02/28 05:26:27  yosizaki
  do-indent.

  Revision 1.12  2004/06/11 06:17:48  yada
  close SDK_BB support

  Revision 1.11  2004/04/06 06:38:30  yasu
  small fix for WRAM address

  Revision 1.10  2004/04/05 10:33:49  takano_makoto
  Small modyfy at indent.

  Revision 1.9  2004/04/05 10:32:34  takano_makoto
  Add HW_EXT_WRAM

  Revision 1.8  2004/03/25 01:29:45  yada
  only added comment

  Revision 1.7  2004/03/23 07:41:29  yada
  Consideration for ARM-exclusive WRAM when not TEG

  Revision 1.6  2004/02/17 08:22:07  yada
  Reshaped tab

  Revision 1.5  2004/02/13 10:40:18  yada
  (none)

  Revision 1.4  2004/02/12 13:32:25  yasu
  change include guards

  Revision 1.3  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.2  2003/12/22 14:08:52  yasu
  Corrected include guard

  Revision 1.1  2003/12/16 10:56:38  yasu
  Moved from spcode

  Revision 1.2  2003/12/16 06:29:41  ida
  Delete description of DTCM
  Add description of internal work RAM.

  Revision 1.1  2003/12/11 05:38:05  yasu
  Copy ARM9 version

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_ARM7_HW_MMAP_GLOBAL_H_
#define NITRO_ARM7_HW_MMAP_GLOBAL_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// GLOBAL MEMORY MAP
//---------------------------------------------------------------------------

//------------------------------------------------
//  Physical Address
//
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

//----------------------------- PRV-WRAMs
#define HW_PRV_WRAM             0x03800000
// TEG   : ARM7 WRAM == 32KB
// TS    : ARM7 WRAM == 64KB
#if  defined(SDK_TEG)
#define HW_PRV_WRAM_END         0x03808000
#else
#define HW_PRV_WRAM_END         0x03810000
#endif
#define HW_PRV_WRAM_SIZE        (HW_PRV_WRAM_END-HW_PRV_WRAM)

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

#define HW_EXT_WRAM             0x06000000
#define HW_EXT_WRAM_END         0x06040000
#define HW_EXT_WRAM_SIZE        (HW_EXT_WRAM_END-HW_EXT_WRAM)

#define HW_BG_VRAM              0x06000000
#define HW_BG_VRAM_END          0x06080000
#define HW_BG_VRAM_SIZE         (HW_BG_VRAM_END-HW_BG_VRAM)

#define HW_OBJ_VRAM             0x06400000
#define HW_OBJ_VRAM_END         0x06440000
#define HW_OBJ_VRAM_SIZE        (HW_OBJ_VRAM_END-HW_OBJ_VRAM)

#define HW_LCDC_VRAM            0x06800000
#define HW_LCDC_VRAM_END        0x06898000
#define HW_LCDC_VRAM_SIZE       (HW_LCDC_VRAM_END-HW_LCDC_VRAM)

#define HW_OAM                  0x07000000
#define HW_OAM_END              0x07000400
#define HW_OAM_SIZE             (HW_OAM_END-HW_OAM)

//----------------------------- Cartridge Bus
#define HW_CTRDG_ROM            0x08000000
#define HW_CTRDG_ROM_END        0x0a000000
#define HW_CTRDG_RAM            0x0a000000
#define HW_CTRDG_RAM_END        0x0a010000

//----------------------------- System ROM
#define HW_BIOS                 0xffff0000
#define HW_BIOS_END             0xffff8000

#define HW_RESET_VECTOR         0xffff0000

#ifdef __cplusplus
} /* extern "C" */
#endif
/* NITRO_ARM7_HW_MMAP_GLOBAL_H_ */
#endif
