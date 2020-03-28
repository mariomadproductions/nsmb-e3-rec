/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     command.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: command.h,v $
  Revision 1.9  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.8  2005/04/14 06:52:03  ida
  Added SND_COMMAND_PREPARE_SEQ command

  Revision 1.7  2005/03/24 04:35:33  ida
  sound patch for NITRO-System 2005/03/28

  Revision 1.15  2005/03/17 02:11:01  ida
  Added SND_COMMAND_SKIP_SEQ command

  Revision 1.14  2005/03/01 02:14:22  ida
  Added SND_COMMAND_IMMEDIATE flag

  Revision 1.13  2005/02/16 07:47:40  ida
  Added functions to obtain driver information

  Revision 1.12  2005/01/06 04:07:49  ida
  Updated copyright year notation

  Revision 1.11  2005/01/05 07:09:29  ida
  Added SND_COMMAND_COPY_REGISTER

  Revision 1.10  2004/10/05 06:21:16  ida
  add SND_SetMasterPan

  Revision 1.9  2004/08/10 02:29:41  ida
  add SND_StopUnlockedChannel

  Revision 1.8  2004/08/02 05:36:52  ida
  add surround decay

  Revision 1.7  2004/07/13 05:45:28  ida
  change function interface

  Revision 1.6  2004/07/09 06:49:01  ida
  remove SND_COMMAND_CHANNEL_HOLD

  Revision 1.5  2004/07/05 06:33:19  ida
  change symbol name

  Revision 1.4  2004/06/29 06:44:57  ida
  remove SND_GetCurrentCommandList

  Revision 1.3  2004/06/28 07:15:30  ida
  change function interface

  Revision 1.2  2004/06/21 01:18:56  ida
  change function interface

  Revision 1.1  2004/06/11 01:54:24  ida
  port.h -> command.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_COMMAND_H_
#define NITRO_SND_COMMON_COMMAND_H_

#include "nitro/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
	macro definition
 ******************************************************************************/

#define SND_COMMAND_NOBLOCK     0
#define SND_COMMAND_BLOCK     ( 1 << 0 )
#define SND_COMMAND_IMMEDIATE ( 1 << 1 )

/******************************************************************************
	enum definition
 ******************************************************************************/

typedef enum SNDCommandID
{
    SND_COMMAND_START_SEQ,
    SND_COMMAND_STOP_SEQ,
    SND_COMMAND_PREPARE_SEQ,
    SND_COMMAND_START_PREPARED_SEQ,
    SND_COMMAND_PAUSE_SEQ,
    SND_COMMAND_SKIP_SEQ,
    SND_COMMAND_PLAYER_PARAM,
    SND_COMMAND_TRACK_PARAM,
    SND_COMMAND_MUTE_TRACK,
    SND_COMMAND_ALLOCATABLE_CHANNEL,
    SND_COMMAND_PLAYER_LOCAL_VAR,
    SND_COMMAND_PLAYER_GLOBAL_VAR,
    SND_COMMAND_START_TIMER,
    SND_COMMAND_STOP_TIMER,
    SND_COMMAND_SETUP_CHANNEL_PCM,
    SND_COMMAND_SETUP_CHANNEL_PSG,
    SND_COMMAND_SETUP_CHANNEL_NOISE,
    SND_COMMAND_SETUP_CAPTURE,
    SND_COMMAND_SETUP_ALARM,
    SND_COMMAND_CHANNEL_TIMER,
    SND_COMMAND_CHANNEL_VOLUME,
    SND_COMMAND_CHANNEL_PAN,
    SND_COMMAND_SURROUND_DECAY,
    SND_COMMAND_MASTER_VOLUME,
    SND_COMMAND_MASTER_PAN,
    SND_COMMAND_OUTPUT_SELECTOR,
    SND_COMMAND_LOCK_CHANNEL,
    SND_COMMAND_UNLOCK_CHANNEL,
    SND_COMMAND_STOP_UNLOCKED_CHANNEL,
    SND_COMMAND_SHARED_WORK,
    SND_COMMAND_INVALIDATE_SEQ,
    SND_COMMAND_INVALIDATE_BANK,
    SND_COMMAND_INVALIDATE_WAVE,
    SND_COMMAND_READ_DRIVER_INFO
}
SNDCommandID;

/******************************************************************************
	structure definition
 ******************************************************************************/

typedef struct SNDCommand
{
    struct SNDCommand *next;
    SNDCommandID id;
    u32     arg[4];
}
SNDCommand;

/******************************************************************************
	public function declaration
 ******************************************************************************/

void    SND_CommandInit(void);

#ifdef SDK_ARM9

struct SNDCommand *SND_AllocCommand(u32 flags);
void    SND_PushCommand(struct SNDCommand *command);

const SNDCommand *SND_RecvCommandReply(u32 flags);

BOOL    SND_FlushCommand(u32 flags);

void    SND_WaitForCommandProc(u32 tag);
void    SND_WaitForFreeCommand(int count);

u32     SND_GetCurrentCommandTag(void);
BOOL    SND_IsFinishedCommandTag(u32 tag);


int     SND_CountFreeCommand(void);
int     SND_CountReservedCommand(void);
int     SND_CountWaitingCommand(void);

#else  /* SDK_ARM7 */

void    SND_CommandProc(void);

#endif /* SDK_ARM9 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_COMMAND_H_ */
