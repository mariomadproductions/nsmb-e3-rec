/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CARD - include
  File:     rom.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: rom.h,v $
  Revision 1.17  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.16  2005/11/29 01:21:00  yosizaki
  fix comments and indent.

  Revision 1.15  2005/03/18 06:52:57  yosizaki
  add CARDRomHeader.

  Revision 1.14  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.13  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.12  2004/12/08 08:53:06  yosizaki
  delete CARDi_ReadRomID()
  add comments.

  Revision 1.11  2004/11/02 10:07:30  yosizaki
  fix comment.

  Revision 1.10  2004/09/06 13:44:31  yosizaki
  move CARD_(Lock/Unlock)Backup

  Revision 1.9  2004/09/03 07:19:12  yosizaki
  fix include directives.

  Revision 1.8  2004/09/03 06:50:43  yosizaki
  add CARD_GetRomRegionOVT.

  Revision 1.7  2004/07/23 08:32:14  yosizaki
  small fix.

  Revision 1.6  2004/07/19 13:10:47  yosizaki
  change interface.

  Revision 1.5  2004/07/10 10:20:47  yosizaki
  add CARD_LockBackup()

  Revision 1.4  2004/07/09 08:40:13  yosizaki
  change implement of synchronous mode.

  Revision 1.3  2004/07/08 13:47:42  yosizaki
  change CARD_ReadRom (for fs_rom)

  Revision 1.2  2004/07/05 08:10:41  yosizaki
  add comment.
  include card/common.h

  Revision 1.1  2004/06/28 01:55:02  yosizaki
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/


#if	!defined(NITRO_CARD_ROM_H_)
#define NITRO_CARD_ROM_H_


#ifdef __cplusplus
extern "C"
{
#endif


#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/memorymap.h"
#include "nitro/mi/dma.h"
#include "nitro/mi/exMemory.h"
#include "nitro/os.h"

#include "nitro/card/common.h"


/*****************************************************************************/
/* declarations */

/* ROM header area information structure */
typedef struct
{
    u32     offset;
    u32     length;
}
CARDRomRegion;

/* ROM header structure */
typedef struct
{

    /* 0x000-0x020 [System reserve environment] */
    char    game_name[12];             /* Software title name */
    u32     game_code;                 /* initial code */
    u16     maker_code;                /* maker code */
    u8      product_id;                /* system code */
    u8      device_type;               /* Device type */
    u8      device_size;               /* device capacity */
    u8      reserved_A[9];             /* system reserve A */
    u8      game_version;              /* software version */
    u8      property;                  /* internal use flag */

    /* 0x020-0x040 [parameter for permanent modules] */
    void   *main_rom_offset;           /* ARM9 transfer source ROM offset */
    void   *main_entry_address;        /* ARM9 execution start address (un-mounted) */
    void   *main_ram_address;          /* ARM9 transfer destination RAM offset */
    u32     main_size;                 /* ARM9 distribution size */
    void   *sub_rom_offset;            /* ARM7 transfer source ROM offset */
    void   *sub_entry_address;         /* ARM7 execution start address (un-mounted) */
    void   *sub_ram_address;           /* ARM7 transfer destination RAM offset */
    u32     sub_size;                  /* ARM7 distribution size */

    /* 0x040-0x050 [parameters for the file table] */
    CARDRomRegion fnt;                 /* File Name Table */
    CARDRomRegion fat;                 /* File allocation table. */

    /* 0x050-0x060 [parameters for the overlay header table] */
    CARDRomRegion main_ovt;            /* ARM9 overlay header table */
    CARDRomRegion sub_ovt;             /* ARM7 overlay header table */

    /* 0x060-0x070 [System reserve environment] */
    u8      rom_param_A[8];            /* Mask ROM control parameter A */
    u32     banner_offset;             /* Banner file ROM offset */
    u16     secure_crc;                /* Secure environment CRC */
    u8      rom_param_B[2];            /* Mask ROM control parameter B */

    /* 0x070-0x078 [Auto load parameters] */
    void   *main_autoload_done;        /* ARM9 auto load hook address */
    void   *sub_autoload_done;         /* ARM7 auto load hook address */

    /* 0x078-0x0C0 [System reserve environment] */
    u8      rom_param_C[8];            /* Mask ROM control parameter C */
    u32     rom_size;                  /* Application final ROM offset */
    u32     header_size;               /* ROM header size */
    u8      reserved_B[0x38];          /* System reserve B */

    /* 0x0C0-0x160 [System reserve environment] */
    u8      logo_data[0x9C];           /* NINTENDO logo image data */
    u16     logo_crc;                  /* NINTENDO logo CRC */
    u16     header_crc;                /* ROM internal register data CRC */

}
CARDRomHeader;


/*****************************************************************************/
/* constants */

/* ROM area size */
#define CARD_ROM_PAGE_SIZE	512


/*****************************************************************************/
/* functions */

/*---------------------------------------------------------------------------*
  Name:         CARD_GetRomRegionFNT

  Description:  Obtains the FNT region information of ROM header.

  Arguments:    None.

  Returns:      Pointer to the FNT region information of ROM header.
 *---------------------------------------------------------------------------*/
static inline const CARDRomRegion *CARD_GetRomRegionFNT(void)
{
    return (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x40);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_GetRomRegionFAT

  Description:  Obtains the FAT region information of ROM header.

  Arguments:    None.

  Returns:      Pointer to the FAT region information of ROM header.
 *---------------------------------------------------------------------------*/
static inline const CARDRomRegion *CARD_GetRomRegionFAT(void)
{
    return (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x48);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_GetRomRegionOVT

  Description:  Obtains the OVT region information of ROM header.

  Arguments:    None.

  Returns:      Pointer to the OVT region information of ROM header.
 *---------------------------------------------------------------------------*/
static inline const CARDRomRegion *CARD_GetRomRegionOVT(MIProcessor target)
{
    return (target == MI_PROCESSOR_ARM9) ?
        (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x50) :
        (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x58);
}

/*
 *	The following functions provide low level access to the device on the card.
 *	When using them, make sure you self-manage the settings of the predefined bus.
 *
 *	The access target is changed to the cartridge internally
 *	in the TEG and cartridge environment so the same processing is
 *	possible excluding operating characteristics.
 *
 *	CARD_LockRom() / CARD_UnlockRom() /
 *	CARD_LockBackup() / CARD_UnlockBackup() determine dynamically if
 *	OS_LockCard() or OS_LockCartridge() should be used
 *	and call the appropriate function.
 *	To prevent access at same time to ROM and backup, exclusive access
 *	control is carried out internally.
 */

#if	defined(SDK_TEG)
static inline BOOL CARDi_IsTrueRom(void)
{
    return (OS_GetConsoleType() & OS_CONSOLE_DEV_CARD) != 0;
}
#endif


/*---------------------------------------------------------------------------*
  Name:         CARD_LockRom

  Description:  lock the CARD-bus before ROM operation.

  Arguments:    lock id.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CARD_LockRom(u16 lock_id);

/*---------------------------------------------------------------------------*
  Name:         CARD_UnlockRom

  Description:  unlock the CARD-bus after ROM operation.

  Arguments:    lock id which is used by CARD_LockRom().

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CARD_UnlockRom(u16 lock_id);

/*
 *	The following are the synchronized/asynchronized that read access ROM.
 *	Control of the hardware in the function is as follows:
 *
 *	- If DMA is specified, use after explicitly stopping with MI_StopDma().
 *	- Use CPU transfer if DMA is specified outside of range.
 *	- If previous access is not complete, block until done.
 *
 *	The card transfer speed is a maximum of 5.94[MB/s], but
 *	with the actual API a certain amount of overhead is included.
 *	With synchronized transfer by the CPU, around 100% speed can be realized.
 *	Although 90 to 95% levels are reached during asynchronous transfer using DMA,
 *	the CPU can execute in parallel for much of the time during transfer.
 *	This maximum value is limited to situations in which the transfer conditions are ideal.
 */
/*---------------------------------------------------------------------------*
  Name:         CARDi_ReadRom

  Description:  basic function of ROM read

  Arguments:    dma        DMA channel to use
                src        Transfer source offset
                dst        Transfer destination memory address.
                len        Transfer size
                callback   Completion callback (NULL if not used)
                arg        Argument of completion callback (ignored if not used)
                is_async   If set to asynchronous mode: TRUE

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    CARDi_ReadRom(u32 dma,
                      const void *src, void *dst, u32 len,
                      MIDmaCallback callback, void *arg, BOOL is_async);

/*---------------------------------------------------------------------------*
  Name:         CARD_TryWaitRomAsync

  Description:  check if asynchronous ROM operation has been completed.

  Arguments:    None.

  Returns:      if operation has been completed, TRUE.
 *---------------------------------------------------------------------------*/
BOOL    CARD_TryWaitRomAsync(void);

/*---------------------------------------------------------------------------*
  Name:         CARD_WaitRomAsync

  Description:  wait for completion of current asynchronous ROM operation.

  Arguments:    None.

  Returns:      if the newest operation is successful, TRUE.
 *---------------------------------------------------------------------------*/
void    CARD_WaitRomAsync(void);

/*---------------------------------------------------------------------------*
  Name:         CARD_ReadRom Async

  Description:  Asynchronous ROM read

  Arguments:    dma        DMA channel to use
                src        Transfer source offset
                dst        Transfer destination memory address.
                len        Transfer size
                callback   Completion callback (NULL if not used)
                arg        Argument of completion callback (ignored if not used)

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void CARD_ReadRomAsync(u32 dma,
                                     const void *src, void *dst, u32 len,
                                     MIDmaCallback callback, void *arg)
{
    CARDi_ReadRom(dma, src, dst, len, callback, arg, TRUE);
}

/*---------------------------------------------------------------------------*
  Name:         CARD_ReadRom

  Description:  Synchronous ROM read

  Arguments:    dma        DMA channel to use
                src        Transfer source offset
                dst        Transfer destination memory address.
                len        Transfer size

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void CARD_ReadRom(u32 dma, const void *src, void *dst, u32 len)
{
    CARDi_ReadRom(dma, src, dst, len, NULL, NULL, FALSE);
}


/* internal function */
u32     CARDi_ReadRomID(void);


/* I/O processor ************************************************************/

#if	defined(SDK_TEG) && defined(SDK_ARM7)

void    CARDi_CreatePxiRecvThread(u32 priority);

#endif /* defined(SDK_TEG) && defined(SDK_ARM7) */


#ifdef __cplusplus
} /* extern "C" */
#endif


/* NITRO_CARD_ROM_H_ */
#endif
