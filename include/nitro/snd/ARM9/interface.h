/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     interface.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: interface.h,v $
  Revision 1.11  2006/03/20 01:58:27  ida
  added the SND_SetMuteTrackEx function

  Revision 1.10  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.9  2005/04/14 06:51:49  ida
  Added SND_PrepareSeq function

  Revision 1.8  2005/03/24 04:35:33  ida
  sound patch for NITRO-System 2005/03/28

  Revision 1.16  2005/03/17 02:11:24  ida
  added the SNDi_SkipSeq function

  Revision 1.15  2005/03/01 02:20:53  ida
  Added the SND_SetTrackPanRange function

  Revision 1.14  2005/02/16 07:47:40  ida
  Added functions to obtain driver information

  Revision 1.13  2005/01/06 04:07:49  ida
  Updated copyright year notation

  Revision 1.12  2005/01/05 06:48:57  ida
  Added SND_SetTrackAllocatableChannel function

  Revision 1.11  2004/10/21 02:14:29  ida
  fix argument name

  Revision 1.10  2004/10/05 06:21:16  ida
  add SND_SetMasterPan

  Revision 1.9  2004/08/10 02:29:41  ida
  add SND_StopUnlockedChannel

  Revision 1.8  2004/08/02 05:36:06  ida
  add SND_SetupChannelPsg

  Revision 1.7  2004/07/13 05:45:40  ida
  SND_SetTrackAllocatableChannel become private

  Revision 1.6  2004/07/09 06:50:21  ida
  add SND_SetTrackAllocatableChannel

  Revision 1.5  2004/07/05 06:32:36  ida
  SNDCaptureId -> SNDCapture

  Revision 1.4  2004/06/28 07:14:52  ida
  change function interface

  Revision 1.3  2004/06/23 06:32:18  ida
  change interface

  Revision 1.2  2004/06/21 01:18:44  ida
  change function interface

  Revision 1.1  2004/06/11 01:54:03  ida
  command.h -> interface.h

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_INTERFACE_H_
#define NITRO_SND_INTERFACE_H_

#include "nitro/types.h"
#include "nitro/snd/common/capture.h"  // for SNDCapture and SNDCaptureFormat
#include "nitro/snd/common/channel.h"  // for SNDWaveFormat
#include "nitro/snd/common/global.h"   // for SNDChannelMix and SNDOutput
#include "nitro/snd/common/alarm.h"    // for SNDAlarmHandler
#include "nitro/snd/common/seq.h"      // for SNDSeqMute

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
    structure declaration
 ******************************************************************************/

struct SNDBankData;
struct SNDSharedWork;
struct SNDSpCallback;
struct SNDDriverInfo;

/******************************************************************************
    public function declaration
 ******************************************************************************/

//-----------------------------------------------------------------------------
// sequence

void    SND_StartSeq(int playerNo, const void *base, u32 offset, const struct SNDBankData *bank);
void    SND_PrepareSeq(int playerNo, const void *base, u32 offset, const struct SNDBankData *bank);
void    SND_StartPreparedSeq(int playerNo);
void    SND_StopSeq(int playerNo);

void    SND_StopSeq(int playerNo);
void    SND_PauseSeq(int playerNo, BOOL flag);

//-----------------------------------------------------------------------------
// player

void    SND_SetPlayerTempoRatio(int playerNo, int ratio);
void    SND_SetPlayerVolume(int playerNo, int volume);
void    SND_SetPlayerChannelPriority(int playerNo, int prio);
void    SND_SetPlayerLocalVariable(int playerNo, int varNo, s16 var);
void    SND_SetPlayerGlobalVariable(int varNo, s16 var);

//-----------------------------------------------------------------------------
// track

void    SND_SetTrackMute(int playerNo, u32 trackBitMask, BOOL flag);
void    SND_SetTrackMuteEx(int playerNo, u32 trackBitMask, SNDSeqMute mute);
void    SND_SetTrackVolume(int playerNo, u32 trackBitMask, int volume);
void    SND_SetTrackPitch(int playerNo, u32 trackBitMask, int pitch);
void    SND_SetTrackPan(int playerNo, u32 trackBitMask, int pan);
void    SND_SetTrackPanRange(int playerNo, u32 trackBitMask, int panRange);
void    SND_SetTrackModDepth(int playerNo, u32 trackBitMask, int depth);
void    SND_SetTrackModSpeed(int playerNo, u32 trackBitMask, int speed);
void    SND_SetTrackAllocatableChannel(int playerNo, u32 trackBitMask, u32 chBitMask);

//-----------------------------------------------------------------------------
// timer

void    SND_StartTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
void    SND_StopTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);

//-----------------------------------------------------------------------------
// channel

void    SND_LockChannel(u32 chBitMask, u32 flags);
void    SND_UnlockChannel(u32 chBitMask, u32 flags);
void    SND_StopUnlockedChannel(u32 chBitMask, u32 flags);

void    SND_SetupChannelPcm(int chNo,
                            SNDWaveFormat format,
                            const void *dataAddr,
                            SNDChannelLoop loop,
                            int loopStart,
                            int dataLen, int volume, SNDChannelDataShift shift, int timer, int pan);
void    SND_SetupChannelPsg(int chNo,
                            SNDDuty duty,
                            int volume, SNDChannelDataShift shift, int timer, int pan);
void    SND_SetupChannelNoise(int chNo, int volume, SNDChannelDataShift shift, int timer, int pan);

void    SND_SetChannelVolume(u32 chBitMask, int volume, SNDChannelDataShift shift);
void    SND_SetChannelTimer(u32 chBitMask, int timer);
void    SND_SetChannelPan(u32 chBitMask, int pan);

//-----------------------------------------------------------------------------
// capture

void    SND_SetupCapture(SNDCapture capture,
                         SNDCaptureFormat format,
                         void *buffer_p,
                         u32 length, BOOL loopFlag, SNDCaptureIn in, SNDCaptureOut out);

//-----------------------------------------------------------------------------
// alarm

void    SND_SetupAlarm(int alarmNo, u32 tick, u32 period, SNDAlarmHandler handler, void *arg);

//-----------------------------------------------------------------------------
// global setting

void    SND_SetMasterVolume(int volume);

void    SND_SetOutputSelector(SNDOutput left,
                              SNDOutput right, SNDChannelOut channel1, SNDChannelOut channel3);

void    SND_SetMasterPan(int pan);
void    SND_ResetMasterPan(void);

//-----------------------------------------------------------------------------
// invalidate data

void    SND_InvalidateSeqData(const void *start, const void *end);
void    SND_InvalidateBankData(const void *start, const void *end);
void    SND_InvalidateWaveData(const void *start, const void *end);

//-----------------------------------------------------------------------------
// driver info

void    SND_ReadDriverInfo(struct SNDDriverInfo *info);

/******************************************************************************
    private function declaration
 ******************************************************************************/

void    SNDi_SetPlayerParam(int playerNo, u32 offset, u32 data, int size);
void    SNDi_SetTrackParam(int playerNo, u32 trackBitMask, u32 offset, u32 data, int size);
void    SNDi_SkipSeq(int playerNo, u32 tick);
void    SNDi_SetSurroundDecay(int decay);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_INTERFACE_H_ */
