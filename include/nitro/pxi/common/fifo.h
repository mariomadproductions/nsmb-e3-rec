/*---------------------------------------------------------------------------*
  Project:  NitroSDK - -include - PXI
  File:     pxi_fifo.c

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fifo.h,v $
  Revision 1.21  2007/02/20 00:28:11  kitase_hirotake
  indent source

  Revision 1.20  2006/05/22 07:01:44  okubata_ryoma
  PM synchronization function now runs even when interrupt is banned

  Revision 1.19  2006/05/01 01:14:54  yada
  add NITRO_FIFO_TAG_CTRDG_PHI

  Revision 1.18  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.17  2005/11/01 01:17:36  okubata_ryoma
  Added PXI_FIFO_TAG_CTRDG_Ex

  Revision 1.16  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.15  2004/12/20 00:42:41  terui
  Added TAG for WVR library

  Revision 1.14  2004/09/27 13:39:56  yada
  add PXI_FIFO_TAG_CARD

  Revision 1.13  2004/09/13 10:50:15  yada
  add PXI tag for CTRDG

  Revision 1.12  2004/09/01 04:24:35  yada
  add PXI_FIFO_TAG_OS tag

  Revision 1.11  2004/07/13 08:29:12  yada
  move PXI_IsArm7CallbackReady() and PXI_IsArm9CallbackReady()
  from pxi_fifo.c to this header as inline.

  Revision 1.10  2004/05/14 09:34:00  yasu
  add ARM9/ARM7 sync in PXI_Init

  Revision 1.9  2004/04/21 12:04:06  yasu
  change pxi tag id for FS

  Revision 1.8  2004/04/15 03:01:45  yasu
  add PXI_FIFO_TAG_FS

  Revision 1.7  2004/03/30 12:18:48  yasu
  change parameter of PXI_SetSendCallback

  Revision 1.6  2004/03/30 10:47:05  miya
  add send FIFO callback functions

  Revision 1.5  2004/03/17 02:51:35  yasu
  add some tags

  Revision 1.4  2004/03/05 06:43:36  ida
  add PXI_FIFO_TAG_SOUND

  Revision 1.3  2004/03/05 04:18:33  yasu
  PXI_MAX_FIFO_TAG=32 fixed

  Revision 1.2  2004/03/04 12:38:50  yasu
  change prefix, function name and macro

  Revision 1.1  2004/03/04 08:44:26  yasu
  add defines for fifo access

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PXI_COMMON_FIFO_H_
#define NITRO_PXI_COMMON_FIFO_H_

#include "nitro/types.h"
#include "nitro/memorymap.h"
#include "nitro/pxi/common/regname.h"


#ifdef __cplusplus
extern "C" {
#endif

/* TAG ID definition */
typedef enum
{
    PXI_FIFO_TAG_EX = 0,               // Extension format
    PXI_FIFO_TAG_USER_0,               // for application programmer, use it in free
    PXI_FIFO_TAG_USER_1,               // for application programmer, use it in free
    PXI_FIFO_TAG_SYSTEM,               // SDK inner usage
    PXI_FIFO_TAG_NVRAM,                // NVRAM
    PXI_FIFO_TAG_RTC,                  // RTC
    PXI_FIFO_TAG_TOUCHPANEL,           // Touch Panel
    PXI_FIFO_TAG_SOUND,                // Sound
    PXI_FIFO_TAG_PM,                   // Power Management
    PXI_FIFO_TAG_MIC,                  // Microphone
    PXI_FIFO_TAG_WM,                   // Wireless Manager
    PXI_FIFO_TAG_FS,                   // File System
    PXI_FIFO_TAG_OS,                   // OS
    PXI_FIFO_TAG_CTRDG,                // Cartridge
    PXI_FIFO_TAG_CARD,                 // Card
    PXI_FIFO_TAG_WVR,                  // Control driving wireless library
    PXI_FIFO_TAG_CTRDG_Ex,             // Cartridge Ex
    PXI_FIFO_TAG_CTRDG_PHI,            // Cartridge PHI

    PXI_MAX_FIFO_TAG = 32              // MAX FIFO TAG
}
PXIFifoTag;


/* for Compatibility */
#define	PXI_FIFO_DEVICE_TEST		PXI_FIFO_TAG_USR_0
#define	PXI_FIFO_DEVICE_FLASH		PXI_FIFO_TAG_NVRAM
#define	PXI_FIFO_DEVICE_RTC		PXI_FIFO_TAG_RTC
#define	PXI_FIFO_DEVICE_TOUCHPANEL	PXI_FIFO_TAG_TOUCHPANEL
#define PXI_MAX_DEVICES			PXI_MAX_FIFO_TAG


/* PXI_FIFO return code */
typedef enum
{
    PXI_FIFO_SUCCESS = 0,
    PXI_FIFO_FAIL_SEND_ERR = -1,
    PXI_FIFO_FAIL_SEND_FULL = -2,
    PXI_FIFO_FAIL_RECV_ERR = -3,
    PXI_FIFO_FAIL_RECV_EMPTY = -4,
    PXI_FIFO_NO_CALLBACK_ENTRY = -5
}
PXIFifoStatus;


/* type definition */
#define	PXI_FIFOMESSAGE_BITSZ_TAG	5
#define	PXI_FIFOMESSAGE_BITSZ_ERR	1
#define	PXI_FIFOMESSAGE_BITSZ_DATA	26
typedef union
{
    struct
    {
        u32     tag:PXI_FIFOMESSAGE_BITSZ_TAG;
        u32     err:PXI_FIFOMESSAGE_BITSZ_ERR;
        u32     data:PXI_FIFOMESSAGE_BITSZ_DATA;
    }
    e;
    u32     raw;

}
PXIFifoMessage;


// type definition
typedef void (*PXIFifoCallback) (PXIFifoTag tag, u32 data, BOOL err);
typedef void (*PXIFifoEmtpyCallback) (void);


/*---------------------------------------------------------------------------*
  Name:         PXI_IsFifoError

  Description:  Check if error on fifo?

  Arguments:    status  Status

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline BOOL PXI_IsFifoError(PXIFifoStatus status)
{
    return PXI_FIFO_SUCCESS == status;
}


/*---------------------------------------------------------------------------*
  Name:         PXI_InitFifo

  Description:  initialize FIFO system

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    PXI_InitFifo(void);


/*---------------------------------------------------------------------------*
  Name:         PXI_SetFifoRecvCallback

  Description:  set callback function when data arrive via FIFO

  Arguments:    device_no    DEVICE NO.
                callback   callback function to be called

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    PXI_SetFifoRecvCallback(int fifotag, PXIFifoCallback callback);


/*---------------------------------------------------------------------------*
  Name:         PXI_IsCallbackReady
                PXI_IsArm7CallbackReady
                PXI_IsArm9CallbackReady

  Description:  check if callback is ready

  Arguments:    fifotag    fifo tag NO (0-31)
                proc       processor name PXI_PROC_ARM9 or PXI_PROC_ARM7
  
  Returns:      TRUE if callback is ready
 *---------------------------------------------------------------------------*/
BOOL    PXI_IsCallbackReady(int fifotag, PXIProc proc);

static inline BOOL PXI_IsArm7CallbackReady(int fifotag)
{
    return PXI_IsCallbackReady(fifotag, PXI_PROC_ARM7);
}

static inline BOOL PXI_IsArm9CallbackReady(int fifotag)
{
    return PXI_IsCallbackReady(fifotag, PXI_PROC_ARM9);
}


/*---------------------------------------------------------------------------*
  Name:         PXI_SetFifoSendCallback

  Description:  set callback function when data is sent via FIFO

  Arguments:    callback   callback function to be called

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    PXI_SetFifoSendCallback(PXIFifoEmtpyCallback callback);


/*---------------------------------------------------------------------------*
  Name:         PXI_SendWordByFifo

  Description:  Send 32bit-word to another CPU via FIFO

  Arguments:    device_no    DEVICE NO.
                data         data(26-bit) which is sent

  Returns:      if error occurred, returns minus value
 *---------------------------------------------------------------------------*/
int     PXI_SendWordByFifo(int fifotag, u32 data, BOOL err);


//======================================================================
//              Interrupt handler called when RECV FIFO not empty
//======================================================================
void    PXIi_HandlerRecvFifoNotEmpty(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_PXI_COMMON_FIFO_H_ */
