/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     work.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: work.h,v $
  Revision 1.19  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.18  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.17  2005/04/12 06:15:15  ida
  Moved SND to NITRO-SDK

  Revision 1.20  2005/04/12 00:54:11  ida
  for SDK_FROM_TOOL

  Revision 1.19  2005/02/28 04:12:11  ida
  Added prgNo member

  Revision 1.18  2005/02/23 06:59:15  ida
  Corrected code so the size of SNDDriverInfo is 32 times larger.

  Revision 1.17  2005/02/17 07:51:33  ida
  Changed function name Get to Read

  Revision 1.16  2005/02/16 07:48:10  ida
  Added functions to obtain driver information

  Revision 1.15  2005/01/06 04:07:49  ida
  Updated copyright year notation

  Revision 1.14  2005/01/05 07:08:44  ida
  Added SNDSpReg structure

  Revision 1.13  2004/08/02 05:37:07  ida
  add capture status

  Revision 1.12  2004/07/05 06:34:43  ida
  workaround shared work

  Revision 1.11  2004/06/28 07:17:37  ida
  add alarm work area

  Revision 1.10  2004/06/23 06:35:59  ida
  workaround shared work

  Revision 1.9  2004/06/21 01:20:15  ida
  change function interface

  Revision 1.8  2004/06/08 00:56:27  ida
  add reserved area

  Revision 1.7  2004/05/10 05:29:29  ida
  add tickCounter

  Revision 1.6  2004/05/10 04:58:47  ida
  add SND_SetPlayerVariable & SND_SetGlobalVariable

  Revision 1.5  2004/05/07 07:38:46  ida
  variable type u8 -> s16

  Revision 1.4  2004/05/06 04:47:32  ida
  workaround SNDSharedWork

  Revision 1.3  2004/05/06 00:46:06  ida
  add SNDi_SharedWork

  Revision 1.2  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.6  2004/03/24 06:17:36  ida
  SNDi_Snd -> SNDi_

  Revision 1.5  2004/03/22 02:04:45  ida
  remove static_channel

  Revision 1.4  2004/03/10 06:28:21  ida
  seqCache snd_work.c -> snd_seq.c

  Revision 1.3  2004/03/08 05:40:33  ida
  rename files

  Revision 1.2  2004/02/19 07:19:44  ida
  NNS_ -> SND_

  Revision 1.1  2004/02/19 07:07:58  ida
  add NITRO System snd libraries

  Revision 1.2  2004/02/16 06:22:13  ida
  (none)

  Revision 1.1  2004/02/13 01:44:10  ida
  initial version
  
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_WORK_H_
#define NITRO_SND_COMMON_WORK_H_

#include "nitro/snd/common/exchannel.h"
#include "nitro/snd/common/seq.h"
#include "nitro/snd/common/capture.h"

#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#include "nitro/snd/common/alarm.h"
#endif // SDK_FROM_TOOL

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
    macro definition
 ******************************************************************************/

#define SND_DEFAULT_VARIABLE -1

/******************************************************************************
    structure definition
 ******************************************************************************/

typedef struct SNDWork
{
    SNDExChannel channel[SND_CHANNEL_NUM];
    SNDPlayer player[SND_PLAYER_NUM];
    SNDTrack track[SND_TRACK_NUM];
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
    SNDAlarm alarm[SND_ALARM_NUM];
#endif                                 // SDK_FROM_TOOL
}
SNDWork;                               // must be 32 byte boundary

typedef struct SNDSharedWork
{
    vu32    finishCommandTag;
    vu32    playerStatus;
    vu16    channelStatus;
    vu16    captureStatus;
    vu32    padding[5];
    struct
    {
        vs16    variable[SND_PLAYER_VARIABLE_NUM];
        vu32    tickCounter;
    }
    player[SND_PLAYER_NUM];
    vs16    globalVariable[SND_GLOBAL_VARIABLE_NUM];
}
SNDSharedWork;                         // must be 32 byte boundary

typedef struct SNDSpReg
{
    u32     chCtrl[SND_CHANNEL_NUM];
}
SNDSpReg;

typedef struct SNDDriverInfo
{
    SNDWork work;
    u32     chCtrl[SND_CHANNEL_NUM];
    SNDWork *workAddress;
    u32     lockedChannels;
    u32     padding[6];
}
SNDDriverInfo;                         // must be 32 byte boundary

typedef struct SNDChannelInfo
{
    BOOL    activeFlag:1;
    BOOL    lockFlag:1;

    u16     volume;
    u8      pan;
    u8      pad_;

    SNDEnvStatus envStatus;
}
SNDChannelInfo;

typedef struct SNDPlayerInfo
{
    BOOL    activeFlag:1;
    BOOL    pauseFlag:1;

    u16     trackBitMask;
    u16     tempo;
    u8      volume;
    u8      pad_;
    u16     pad2_;
}
SNDPlayerInfo;

typedef struct SNDTrackInfo
{
    u16     prgNo;
    u8      volume;
    u8      volume2;
    s8      pitchBend;
    u8      bendRange;
    u8      pan;
    s8      transpose;
    u8      pad_;
    u8      chCount;
    u8      channel[SND_CHANNEL_NUM];
}
SNDTrackInfo;

/******************************************************************************
    private variable declaration
 ******************************************************************************/

extern SNDSharedWork *SNDi_SharedWork;

#ifdef SDK_ARM7

extern SNDWork SNDi_Work;

#endif /* SDK_ARM7 */

/******************************************************************************
    public function declaration
 ******************************************************************************/

s16     SND_GetPlayerLocalVariable(int playerNo, int varNo);
s16     SND_GetPlayerGlobalVariable(int varNo);
u32     SND_GetPlayerTickCounter(int playerNo);

u32     SND_GetPlayerStatus(void);
u32     SND_GetChannelStatus(void);
u32     SND_GetCaptureStatus(void);

BOOL    SND_ReadChannelInfo(const SNDDriverInfo * driverInfo, int chNo, SNDChannelInfo * chInfo);
BOOL    SND_ReadPlayerInfo(const SNDDriverInfo * driverInfo, int playerNo,
                           SNDPlayerInfo * playerInfo);
BOOL    SND_ReadTrackInfo(const SNDDriverInfo * driverInfo, int playerNo, int trackNo,
                          SNDTrackInfo * trackInfo);

#ifdef SDK_ARM7

void    SND_SetPlayerLocalVariable(int playerNo, int varNo, s16 var);
void    SND_SetPlayerGlobalVariable(int varNo, s16 var);
void    SND_UpdateSharedWork(void);

#endif /* SDK_ARM7 */

/******************************************************************************
    private function declaration
 ******************************************************************************/

u32     SNDi_GetFinishedCommandTag(void);

#ifdef SDK_ARM9

void    SNDi_InitSharedWork(SNDSharedWork *work);

#endif /* SDK_ARM9 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_WORK_H_ */
