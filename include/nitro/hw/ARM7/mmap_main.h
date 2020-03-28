/*---------------------------------------------------------------------------*
  Project:  NitroSDK - include - HW
  File:     mmap_main.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mmap_main.h,v $
  Revision 1.9  2005/04/14 07:00:12  yasu
  Revised memory map diagram.

  Revision 1.8  2005/04/13 12:47:40  terui
  HW_MAIN_MEM_MAIN_SIZE 0x3C0000 -> 0x3E0000

  Revision 1.7  2005/02/28 05:26:27  yosizaki
  do-indent.

  Revision 1.6  2004/08/18 02:41:39  yada
  change HW_MAIN_MEM_SUB value

  Revision 1.5  2004/07/23 10:56:30  yada
  if TS, MainMemorySize = 0x3c0000

  Revision 1.4  2004/07/06 08:21:02  yada
  only arrange spacing

  Revision 1.3  2004/04/21 01:45:09  takano_makoto
  Add Comment.

  Revision 1.2  2004/03/22 02:05:20  takano_makoto
  small change at define of HW_MAIN_MEM_SUB_SIZE.

  Revision 1.1  2004/02/13 01:52:31  yada
  Added for ARM7 (temporary?)

  Revision 1.4  2004/02/05 12:21:14  yasu
  change SDK prefix iris -> nitro

  Revision 1.3  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.2  2003/12/17 06:05:39  yasu
  split mmap_reserved.h into mmap_tcm.h and mmap_shared.h

  Revision 1.1  2003/12/09 08:35:26  yasu
  Revamped the memory map and the related area

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_HW_ARM7_MMAP_MAIN_H_
#define NITRO_HW_ARM7_MMAP_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// MEMORY MAP of MAIN MEMORY
//---------------------------------------------------------------------------
//
//
//      Retail NITRO            Development NITRO 
//      +---------------+-------+---------------+--8.000M
//      | System Shared |       | System Shared |
//      +---------------+-------+---------------+
//      | User   Shared |       | User   Shared |
//      +---------------+-------+---------------+
//      | Sub Processor |       | Sub Processor |
//      | Reserved      |       | Reserved      |
//      +-+-------------+-------+---------------+--7.875M
//      |W|             |       |               |
//      |R|Main         |       | Debugger Work |
//      |A|Processor    |       |               |
//      |P|Reserved     |       +---------------+--7.000M
//      | |             |       |               |
//      |A|             |       | Main          |
//      |R|             |       | Processor     |
//      |O+-------------+--4M---+ Extra         +--4.000M
//      |U|System Shared|       | Reserved      |
//      |N+-------------+       |               |
//      |D|User   Shared|       |               |
//      | +-------------+       +               +
//      | |Sub Processor|       |               |
//      | |Reserved     |       |               |
//      +-+-------------+-------+---------------+--3.875M
//      |               |       |               |
//      | Main          |       | Main          |
//      | Processor     |       | Processor     |
//      | Reserved      |       | Reserved      |
//      |               |       |               |
//      |               |       |               |
//      |               |       |               |
//      +---------------+       +---------------+
//
//      Default setting for 4MB
//         MAIN  :3.875MB
//         SUB   :124KB
//         SHARED:  4KB
//         DTCM  :on top of SUB
//
#define HW_MAIN_MEM_SHARED_SIZE     0x001000

// HW_MAIN_MEM_MAIN_SIZE is able to change to these size,
// [ 0x200000, 0x300000, 0x380000, 0x3C0000, 0x3E0000, 0x3F0000, 0x3F8000, 0x3FC000 ]
#ifdef SDK_TS
#define HW_MAIN_MEM_MAIN_SIZE       0x3E0000
#else
#define HW_MAIN_MEM_MAIN_SIZE       0x380000
#endif
#define HW_MAIN_MEM_SUB_SIZE        (HW_MAIN_MEM_SIZE - HW_MAIN_MEM_MAIN_SIZE - HW_MAIN_MEM_SHARED_SIZE)

#define HW_MAIN_MEM_MAIN            (HW_MAIN_MEM)
#define HW_MAIN_MEM_MAIN_END        (HW_MAIN_MEM + HW_MAIN_MEM_MAIN_SIZE)
#define HW_MAIN_MEM_SUB             (HW_MAIN_MEM_MAIN_END + 0x400000)
#define HW_MAIN_MEM_SUB_END         (HW_MAIN_MEM_SUB + HW_MAIN_MEM_SUB_SIZE)

#define HW_MAIN_MEM_DEBUGGER_OFFSET 0x700000
#define HW_MAIN_MEM_DEBUGGER_SIZE   0x080000
#define HW_MAIN_MEM_DEBUGGER        (HW_MAIN_MEM + HW_MAIN_MEM_DEBUGGER_OFFSET)
#define HW_MAIN_MEM_DEBUGGER_END    (HW_MAIN_MEM_DEBUGGER + HW_MAIN_MEM_DEBUGGER_SIZE)

#define HW_MAIN_MEM_SHARED          (HW_MAIN_MEM_EX_END - HW_MAIN_MEM_SHARED_SIZE)
#define HW_MAIN_MEM_SHARED_END      (HW_MAIN_MEM_EX_END - HW_MAIN_MEM_SYSTEM_SIZE)

#define HW_MAIN_MEM_SYSTEM_END      (HW_MAIN_MEM_EX_END)

#ifdef __cplusplus
} /* extern "C" */
#endif
/* NITRO_HW_ARM7_MMAP_MAIN_H_ */
#endif
