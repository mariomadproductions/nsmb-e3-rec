/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     seq.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: seq.h,v $
  Revision 1.27  2006/03/20 01:58:27  ida
  added the SND_SetMuteTrackEx function

  Revision 1.26  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.25  2005/06/06 01:59:11  ida
  Deleted invalid function declarations

  Revision 1.24  2005/04/14 06:51:49  ida
  Added SND_PrepareSeq function

  Revision 1.23  2005/03/24 04:35:33  ida
  sound patch for NITRO-System 2005/03/28

  Revision 1.18  2005/03/17 02:10:29  ida
  Added SND_SkipSeq function

  Revision 1.17  2005/03/01 02:15:53  ida
  Added pan_range member

  Revision 1.16  2005/01/06 04:07:49  ida
  Updated copyright year notation

  Revision 1.15  2005/01/05 07:09:09  ida
  Added SND_MmlPrintEnable function

  Revision 1.14  2004/07/13 05:44:11  ida
  SND_SetTrackAllocatableChannel become private

  Revision 1.13  2004/07/09 06:50:02  ida
  add SNDTrack::channel_mask

  Revision 1.12  2004/07/05 06:34:07  ida
  add macros

  Revision 1.11  2004/06/23 06:35:15  ida
  channel -> exchannel

  Revision 1.10  2004/05/10 01:58:38  ida
  add volume2(expression) command

  Revision 1.9  2004/05/07 07:38:06  ida
  change struct SNDTrack & SNDPlayer

  Revision 1.8  2004/05/06 04:47:32  ida
  workaround SNDSharedWork

  Revision 1.7  2004/05/06 04:00:44  ida
  add comments

  Revision 1.6  2004/05/06 01:42:01  ida
  use doPeriodicProc flag

  Revision 1.5  2004/05/06 00:45:53  ida
  add comments

  Revision 1.4  2004/04/26 02:26:54  ida
  add SND_Invalidate*()

  Revision 1.3  2004/04/15 05:55:53  ida
  change channel external pan range

  Revision 1.2  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.15  2004/03/25 10:00:04  ida
  workaround loop command

  Revision 1.14  2004/03/24 06:20:46  ida
  add SNDi_SetPlayerParam

  Revision 1.13  2004/03/17 08:47:07  ida
  change porta_time command

  Revision 1.12  2004/03/12 06:43:48  ida
  modify porta command

  Revision 1.11  2004/03/12 05:26:13  ida
  add sweep command

  Revision 1.10  2004/03/12 04:53:31  ida
  add porta_time command

  Revision 1.9  2004/03/12 02:15:32  ida
  add note_finish_wait mode

  Revision 1.8  2004/03/11 02:32:12  ida
  PausePlayer -> PauseSeq

  Revision 1.7  2004/03/10 06:32:58  ida
  SND_Snd -> SND_
  workaround sequence command

  Revision 1.6  2004/03/08 05:40:33  ida
  rename files

  Revision 1.5  2004/02/25 04:15:31  ida
  workaround extVolume

  Revision 1.4  2004/02/25 02:31:55  ida
  remove fadeOut argument
  add SetMasterVolume

  Revision 1.3  2004/02/24 08:08:16  ida
  workaround recv port

  Revision 1.2  2004/02/19 07:19:44  ida
  NNS_ -> SND_

  Revision 1.1  2004/02/19 07:07:58  ida
  add NITRO System snd libraries

  Revision 1.1  2004/02/13 01:44:10  ida
  initial version
  
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_SEQ_H_
#define NITRO_SND_COMMON_SEQ_H_

#include "nitro/types.h"

#include "nitro/snd/common/exchannel.h" // for SNDLfoParam

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
	macro definition
 ******************************************************************************/

#define SND_PLAYER_NUM 16
#define SND_PLAYER_MIN  0
#define SND_PLAYER_MAX 15

#define SND_TRACK_NUM 32
#define SND_TRACK_MIN  0
#define SND_TRACK_MAX 31

#define SND_TRACK_NUM_PER_PLAYER 16

#define SND_INVALID_TRACK_INDEX 0xff

#define SND_BASE_TEMPO    240
#define SND_DEFAULT_TEMPO 120

#define SND_TRACK_CALL_STACK_DEPTH 3

// Caution: this affects the size of SNDSharedWork 
#define SND_PLAYER_VARIABLE_NUM 16
#define SND_GLOBAL_VARIABLE_NUM 16

/******************************************************************************
	enum definition
 ******************************************************************************/

typedef enum
{
    SND_SEQ_MUTE_OFF,
    SND_SEQ_MUTE_NO_STOP,
    SND_SEQ_MUTE_RELEASE,
    SND_SEQ_MUTE_STOP
}
SNDSeqMute;

/******************************************************************************
	structure declaration
 ******************************************************************************/

struct SNDBankData;

/******************************************************************************
	structure definition
 ******************************************************************************/

typedef struct SNDPlayer
{
    u8      active_flag:1;
    u8      prepared_flag:1;
    u8      pause_flag:1;
    u8      pad_:5;

    u8      myNo;
    u8      pad2_;
    u8      pad3_;

    u8      prio;
    u8      volume;
    s16     extFader;

    u8      tracks[SND_TRACK_NUM_PER_PLAYER];

    u16     tempo;
    u16     tempo_ratio;
    u16     tempo_counter;
    u16     pad__;

    struct SNDBankData *bank;
}
SNDPlayer;

typedef struct SNDTrack
{
    u8      active_flag:1;
    u8      note_wait:1;
    u8      mute_flag:1;
    u8      tie_flag:1;
    u8      note_finish_wait:1;
    u8      porta_flag:1;
    u8      cmp_flag:1;
    u8      channel_mask_flag:1;

    u8      pan_range;

    u16     prgNo;

    u8      volume;
    u8      volume2;
    s8      pitch_bend;
    u8      bend_range;

    s8      pan;
    s8      ext_pan;
    s16     extFader;
    s16     ext_pitch;

    u8      attack;
    u8      decay;
    u8      sustain;
    u8      release;

    u8      prio;
    s8      transpose;
    u8      porta_key;
    u8      porta_time;
    s16     sweep_pitch;

    struct SNDLfoParam mod;
    u16     channel_mask;

    s32     wait;

    const u8 *base;                    // Note: MainMemory pointer
    const u8 *cur;                     // Note: MainMemory pointer

    const u8 *call_stack[SND_TRACK_CALL_STACK_DEPTH];
    u8      loop_count[SND_TRACK_CALL_STACK_DEPTH];
    u8      call_stack_depth;

    struct SNDExChannel *channel_list;
}
SNDTrack;

/******************************************************************************
	public function declaration
 ******************************************************************************/

#ifdef SDK_ARM7

void    SND_SeqInit(void);
void    SND_SeqMain(BOOL doPeriodicProc);

void    SND_StartSeq(int playerNo, const void *seqBase, u32 seqOffset, struct SNDBankData *bank_p);
void    SND_StopSeq(int playerNo);
void    SND_PrepareSeq(int playerNo, const void *seqBase, u32 seqOffset,
                       struct SNDBankData *bank_p);
void    SND_StartPreparedSeq(int playerNo);
void    SND_PauseSeq(int playerNo, BOOL flag);
void    SND_SkipSeq(int playerNo, u32 tick);

void    SND_SetTrackMute(int playerNo, u32 trackBitMask, SNDSeqMute mute);
void    SND_SetTrackAllocatableChannel(int playerNo, u32 trackBitMask, u32 chBitMask);

void    SND_InvalidateSeq(const void *start, const void *end);
void    SND_InvalidateBank(const void *start, const void *end);

void    SND_MmlPrintEnable(BOOL enble);

#endif /* SDK_ARM7 */

/******************************************************************************
	private function declaration
 ******************************************************************************/

#ifdef SDK_ARM7

void    SNDi_SetPlayerParam(int playerNo, u32 offset, u32 data, int size);
void    SNDi_SetTrackParam(int playerNo, u32 trackBitMask, u32 offset, u32 data, int size);

#endif /* SDK_ARM7 */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_SEQ_H_ */
