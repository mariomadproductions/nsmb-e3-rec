/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     midiplayer.h

  Copyright 2004-2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: midiplayer.h,v $
  Revision 1.5  2007/05/17 10:04:44  okubata_ryoma
  Added padding

  Revision 1.4  2007/05/10 02:57:32  ida
  Support for RPN0

  Revision 1.3  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.2  2005/09/28 03:00:03  ida
  Added SND_MidiPlayerProgramChange.

  Revision 1.1  2005/04/12 06:15:07  ida
  Moved SND to NITRO-SDK

  Revision 1.1  2005/04/12 00:52:55  ida
  Added SNDMidiPlayer.

  Revision 1.1  2004/08/19 06:40:44  ida
  Initial version

  $NoKeywords: $
  *---------------------------------------------------------------------------*/
#ifndef NITRO_SND_COMMON_MIDI_PLAYER_H_
#define NITRO_SND_COMMON_MIDI_PLAYER_H_

#include "nitro/types.h"
#include "nitro/snd/common/channel.h"
#include "nitro/snd/common/exchannel.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
	Macro Definitions
 ******************************************************************************/

#define SND_MIDI_TRACK_NUM 16

/******************************************************************************
	Structure Definitions
 ******************************************************************************/

struct SNDBankData;

typedef struct SNDMidiChannel
{
    struct SNDExChannel *chp;
    u8      key;
    u8      pad1;
    u16     pad2;
}
SNDMidiChannel;

typedef struct SNDMidiTrack
{
    struct SNDMidiChannel channels[SND_CHANNEL_NUM];
    SNDLfoParam mod;

    s16     sweep_pitch;

    u16     prgNo;
    s8      pitchbend;

    u8      porta_time;
    u8      volume;
    s8      pan;
    u8      expression;
    s8      transpose;
    u8      prio;
    u8      bendrange;
    u8      porta_flag;
    u8      porta_key;
    u8      attack;
    u8      decay;
    u8      sustain;
    u8      release;

    u8      rpnLSB;
    u8      rpnMSB;
    u8      nrpnLSB;
    u8      nrpnMSB;
    u8      rpn_flag;
    u8      pad1;
    u16     pad2;
}
SNDMidiTrack;

typedef struct SNDMidiPlayer
{
    const struct SNDBankData *bank;
    SNDMidiTrack track[SND_MIDI_TRACK_NUM];

    u8      main_volume;
    u8      prio;
    u16     pad;
}
SNDMidiPlayer;

/******************************************************************************
	Public Function Declarations
 ******************************************************************************/

#ifdef SDK_ARM7

void    SND_MidiPlayerInit(SNDMidiPlayer * player);
void    SND_MidiPlayerMain(SNDMidiPlayer * player);
void    SND_MidiPlayerSetBank(SNDMidiPlayer * player, const struct SNDBankData *bank);
void    SND_MidiPlayerProgramChange(SNDMidiPlayer * player, int channel, int prgNo);
void    SND_MidiPlayerSendMessage(SNDMidiPlayer * player, u8 status, u8 data1, u8 data2);
void    SND_MidiPlayerReset(SNDMidiPlayer * player);

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_MIDI_PLAYER_H_ */
