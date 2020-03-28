/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     mml.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mml.h,v $
  Revision 1.20  2006/04/05 01:46:26  yosizaki
  update copyright.

  Revision 1.19  2006/03/20 01:58:35  ida
  mute sequence command support

  Revision 1.18  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.17  2005/01/31 04:11:24  ida
  sound patch for NITRO-System 01/31/2005

  Revision 1.6  2005/01/06 04:07:49  ida
  Updated copyright year notation

  Revision 1.5  2005/01/05 06:48:16  ida
  Added printvar sequence command

  Revision 1.4  2004/05/10 01:58:38  ida
  add volume2(expression) command

  Revision 1.3  2004/05/07 07:37:25  ida
  add sequence command *_r *_v *_if ...

  Revision 1.2  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.11  2004/03/25 09:59:08  ida
  add loop command

  Revision 1.10  2004/03/24 06:18:51  ida
  add envelope command

  Revision 1.9  2004/03/17 08:47:07  ida
  change porta_time command

  Revision 1.8  2004/03/12 06:43:48  ida
  modify porta command

  Revision 1.7  2004/03/12 05:26:13  ida
  add sweep command

  Revision 1.6  2004/03/12 04:53:31  ida
  add porta_time command

  Revision 1.5  2004/03/10 06:33:23  ida
  renumbering sequence command

  Revision 1.4  2004/03/08 05:40:33  ida
  rename files

  Revision 1.3  2004/02/23 02:57:32  ida
  add mod_range command

  Revision 1.2  2004/02/19 07:19:44  ida
  NNS_ -> SND_

  Revision 1.1  2004/02/19 07:07:58  ida
  add NITRO System snd libraries

  Revision 1.1  2004/02/13 01:44:10  ida
  initial version
  
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_MML_H_
#define NITRO_SND_COMMON_MML_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
	macro definition
 ******************************************************************************/

#define SND_MML_WAIT        0x80
#define SND_MML_PRG         0x81

#define SND_MML_OPEN_TRACK  0x93
#define SND_MML_JUMP        0x94
#define SND_MML_CALL        0x95

#define SND_MML_RANDOM      0xa0
#define SND_MML_VARIABLE    0xa1
#define SND_MML_IF          0xa2

#define SND_MML_SETVAR      0xb0
#define SND_MML_ADDVAR      0xb1
#define SND_MML_SUBVAR      0xb2
#define SND_MML_MULVAR      0xb3
#define SND_MML_DIVVAR      0xb4
#define SND_MML_SHIFTVAR    0xb5
#define SND_MML_RANDVAR     0xb6

#define SND_MML_CMP_EQ      0xb8
#define SND_MML_CMP_GE      0xb9
#define SND_MML_CMP_GT      0xba
#define SND_MML_CMP_LE      0xbb
#define SND_MML_CMP_LT      0xbc
#define SND_MML_CMP_NE      0xbd

#define SND_MML_PAN         0xc0
#define SND_MML_VOLUME      0xc1
#define SND_MML_MAIN_VOLUME 0xc2
#define SND_MML_TRANSPOSE   0xc3
#define SND_MML_PITCH_BEND  0xc4
#define SND_MML_BEND_RANGE  0xc5
#define SND_MML_PRIO        0xc6
#define SND_MML_NOTE_WAIT   0xc7
#define SND_MML_TIE         0xc8
#define SND_MML_PORTA       0xc9
#define SND_MML_MOD_DEPTH   0xca
#define SND_MML_MOD_SPEED   0xcb
#define SND_MML_MOD_TYPE    0xcc
#define SND_MML_MOD_RANGE   0xcd
#define SND_MML_PORTA_SW    0xce
#define SND_MML_PORTA_TIME  0xcf
#define SND_MML_ATTACK      0xd0
#define SND_MML_DECAY       0xd1
#define SND_MML_SUSTAIN     0xd2
#define SND_MML_RELEASE     0xd3
#define SND_MML_LOOP_START  0xd4
#define SND_MML_VOLUME2     0xd5
#define SND_MML_PRINTVAR    0xd6
#define SND_MML_MUTE        0xd7

#define SND_MML_MOD_DELAY   0xe0
#define SND_MML_TEMPO       0xe1
#define SND_MML_SWEEP_PITCH 0xe3

#define SND_MML_LOOP_END    0xfc
#define SND_MML_RET         0xfd
#define SND_MML_ALLOC_TRACK 0xfe
#define SND_MML_FIN         0xff

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_MML_H_ */
