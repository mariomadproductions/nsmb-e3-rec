/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     channel.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: channel.h,v $
  Revision 1.22  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.21  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.20  2005/04/12 06:15:07  ida
  Moved SND to NITRO-SDK

  Revision 1.24  2005/04/12 00:52:11  ida
  for SDK_FROM_TOOL

  Revision 1.23  2005/02/16 07:51:09  ida
  Added register macro for ARM9

  Revision 1.22  2005/02/02 05:10:47  ida
  for SDK_FROM_TOOL

  Revision 1.21  2005/01/06 04:07:49  ida
  Updated copyright year notation

  Revision 1.20  2005/01/05 06:47:34  ida
  Added SND_GetChannelControl function

  Revision 1.19  2004/10/07 05:55:49  ida
  add SND_CHANNEL_PAN_CENTER

  Revision 1.18  2004/10/07 04:42:11  ida
  for compatibility

  Revision 1.17  2004/10/07 02:56:03  ida
  fix typo SND_CHANNEL_LOOP_REPEAT

  Revision 1.16  2004/10/05 06:20:32  ida
  add SND_SetMasterPan

  Revision 1.15  2004/08/19 06:55:15  ida
  SND_StopChannel become non-inline

  Revision 1.14  2004/08/02 05:36:39  ida
  add surround decay

  Revision 1.13  2004/07/09 06:48:40  ida
  add SND_*_CHANNEL_MASK

  Revision 1.12  2004/06/28 07:16:16  ida
  SND_CHANNEL_CLOCK -> SND_TIMER_CLOCK

  Revision 1.11  2004/06/23 06:33:02  ida
  hwchannel.h -> channel.h

  Revision 1.5  2004/06/21 01:20:02  ida
  change function interface

  Revision 1.4  2004/06/08 00:56:03  ida
  add volatile

  Revision 1.3  2004/05/18 01:46:13  ida
  use HW_CPU_CLOCK_ARM7

  Revision 1.2  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.3  2004/03/25 09:53:08  ida
  Channel -> HwChannel

  Revision 1.2  2004/03/10 06:33:58  ida
  SND_IsChannelActive -> SND_IsHwChannelActive

  Revision 1.1  2004/03/08 05:40:33  ida
  rename files

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_CHANNEL_H_
#define NITRO_SND_COMMON_CHANNEL_H_

#include "nitro/types.h"

#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#include "nitro/misc.h"
#include "nitro/hw/common/armArch.h"   // for HW_CPU_CLOCK_ARM7

#ifdef SDK_ARM7
#include "nitro/hw/ARM7/ioreg_SND.h"
#endif /* SDK_ARM7 */

#else

#define HW_CPU_CLOCK_ARM7           33513982

#endif /* SDK_FROM_TOOL */

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
	macro definition
 ******************************************************************************/

#define SND_TIMER_CLOCK ( HW_CPU_CLOCK_ARM7 / 2 )

#define SND_CHANNEL_NUM 16
#define SND_CHANNEL_MIN  0
#define SND_CHANNEL_MAX 15

#define SND_PSG_CHANNEL_MIN  8
#define SND_PSG_CHANNEL_MAX 13
#define SND_PSG_CHANNEL_NUM ( SND_PSG_CHANNEL_MAX - SND_PSG_CHANNEL_MIN + 1 )

#define SND_NOISE_CHANNEL_MIN 14
#define SND_NOISE_CHANNEL_MAX 15
#define SND_NOISE_CHANNEL_NUM ( SND_NOISE_CHANNEL_MAX - SND_NOISE_CHANNEL_MIN + 1 )

#define SND_CHANNEL_PAN_MIN             0
#define SND_CHANNEL_PAN_CENTER         64
#define SND_CHANNEL_PAN_MAX          0x7f

#define SND_CHANNEL_VOLUME_MIN          0
#define SND_CHANNEL_VOLUME_MAX       0x7f

#define SND_CHANNEL_TIMER_MIN        0x10
#define SND_CHANNEL_TIMER_MAX      0xffff

#define SND_CHANNEL_LOOP_START_MAX 0xffff
#define SND_CHANNEL_LOOP_LEN_MAX 0x3fffff

#define SND_CHANNEL_SAD_MASK   0x07fffffc

#define SND_PCM_CHANNEL_MASK    0xffff
#define SND_PSG_CHANNEL_MASK    0x3f00
#define SND_NOISE_CHANNEL_MASK  0xc000
#define SND_CAPIN_CHANNEL_MASK  0x0005
#define SND_CAPOUT_CHANNEL_MASK 0x000a

#define SND_CHANNEL_STOP_HOLD ( 1 << 0 )

#define SND_CHANNEL_REG_OFFSET( ch ) ( (ch) << 4 )

#ifdef SDK_ARM9

#define REG_SND_SOUND0CNT_E_SHIFT                          31
#define REG_SND_SOUND0CNT_E_SIZE                           1
#define REG_SND_SOUND0CNT_E_MASK                           0x80000000

#define REG_SND_SOUND0CNT_FORMAT_SHIFT                     29
#define REG_SND_SOUND0CNT_FORMAT_SIZE                      2
#define REG_SND_SOUND0CNT_FORMAT_MASK                      0x60000000

#define REG_SND_SOUND0CNT_REPEAT_SHIFT                     27
#define REG_SND_SOUND0CNT_REPEAT_SIZE                      2
#define REG_SND_SOUND0CNT_REPEAT_MASK                      0x18000000

#define REG_SND_SOUND0CNT_DUTY_SHIFT                       24
#define REG_SND_SOUND0CNT_DUTY_SIZE                        3
#define REG_SND_SOUND0CNT_DUTY_MASK                        0x07000000

#define REG_SND_SOUND0CNT_PAN_SHIFT                        16
#define REG_SND_SOUND0CNT_PAN_SIZE                         7
#define REG_SND_SOUND0CNT_PAN_MASK                         0x007f0000

#define REG_SND_SOUND0CNT_HOLD_SHIFT                       15
#define REG_SND_SOUND0CNT_HOLD_SIZE                        1
#define REG_SND_SOUND0CNT_HOLD_MASK                        0x00008000

#define REG_SND_SOUND0CNT_SHIFT_SHIFT                      8
#define REG_SND_SOUND0CNT_SHIFT_SIZE                       2
#define REG_SND_SOUND0CNT_SHIFT_MASK                       0x00000300

#define REG_SND_SOUND0CNT_VOLUME_SHIFT                     0
#define REG_SND_SOUND0CNT_VOLUME_SIZE                      7
#define REG_SND_SOUND0CNT_VOLUME_MASK                      0x0000007f

#endif /* SDK_ARM9 */

/******************************************************************************
	enum definition
 ******************************************************************************/

typedef enum
{
    SND_CHANNEL_0,
    SND_CHANNEL_1,
    SND_CHANNEL_2,
    SND_CHANNEL_3,
    SND_CHANNEL_4,
    SND_CHANNEL_5,
    SND_CHANNEL_6,
    SND_CHANNEL_7,
    SND_CHANNEL_8,
    SND_CHANNEL_9,
    SND_CHANNEL_10,
    SND_CHANNEL_11,
    SND_CHANNEL_12,
    SND_CHANNEL_13,
    SND_CHANNEL_14,
    SND_CHANNEL_15
}
SNDChannelId;

typedef enum
{
    SND_WAVE_FORMAT_PCM8,
    SND_WAVE_FORMAT_PCM16,
    SND_WAVE_FORMAT_ADPCM,
    SND_WAVE_FORMAT_PSG,
    SND_WAVE_FORMAT_NOISE = SND_WAVE_FORMAT_PSG
}
SNDWaveFormat;

typedef enum
{
    SND_CHANNEL_LOOP_MANUAL,
    SND_CHANNEL_LOOP_REPEAT,
    SND_CHANNEL_LOOP_1SHOT
}
SNDChannelLoop;

#define SND_CHANNEL_LOOP_REPAET SND_CHANNEL_LOOP_REPEAT // for compatibility

typedef enum
{
    SND_DUTY_1_8,
    SND_DUTY_2_8,
    SND_DUTY_3_8,
    SND_DUTY_4_8,
    SND_DUTY_5_8,
    SND_DUTY_6_8,
    SND_DUTY_7_8
}
SNDDuty;

typedef enum
{
    SND_CHANNEL_DATASHIFT_NONE,
    SND_CHANNEL_DATASHIFT_1BIT,
    SND_CHANNEL_DATASHIFT_2BIT,
    SND_CHANNEL_DATASHIFT_4BIT
}
SNDChannelDataShift;

/******************************************************************************
	inline function
 ******************************************************************************/

#ifdef SDK_ARM7
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

/*---------------------------------------------------------------------------*
  Name:         SND_StartChannel

  Description:  Start channel

  Arguments:    chNo      channel number

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void SND_StartChannel(int chNo)
{
    SDK_MINMAX_ASSERT(chNo, SND_CHANNEL_MIN, SND_CHANNEL_MAX);

    *((REGType8v *)(REG_SOUND0CNT_8_ADDR + SND_CHANNEL_REG_OFFSET(chNo)))
        |= REG_SND_SOUND0CNT_8_E_MASK;
}

#else

void    SND_StartChannel(int chNo);

#endif /* SDK_FROM_TOOL */

#endif /* SDK_ARM7 */

/******************************************************************************
	public function declaration
 ******************************************************************************/

#ifdef SDK_ARM7

void    SND_SetupChannelPcm(int chNo,
                            const void *dataaddr,
                            SNDWaveFormat format,
                            SNDChannelLoop loop,
                            int loopStart,
                            int loopLen, int volume, SNDChannelDataShift shift, int timer, int pan);
void    SND_SetupChannelPsg(int chNo,
                            SNDDuty duty,
                            int volume, SNDChannelDataShift shift, int timer, int pan);
void    SND_SetupChannelNoise(int chNo, int volume, SNDChannelDataShift shift, int timer, int pan);

void    SND_StopChannel(int chNo, s32 flags);

void    SND_SetChannelVolume(int chNo, int volume, SNDChannelDataShift shift);
void    SND_SetChannelTimer(int chNo, int timer);
void    SND_SetChannelPan(int chNo, int pan);

BOOL    SND_IsChannelActive(int chNo);

void    SND_SetMasterPan(int pan);

u32     SND_GetChannelControl(int chNo);

#endif /* SDK_ARM7 */

/******************************************************************************
	private function declaration
 ******************************************************************************/

#ifdef SDK_ARM7

void    SNDi_SetSurroundDecay(int decay);

#endif /* SDK_ARM7 */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_CHANNEL_H_ */
