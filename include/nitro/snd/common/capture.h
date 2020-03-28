/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     capture.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: capture.h,v $
  Revision 1.17  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.16  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.15  2005/04/12 06:15:07  ida
  Moved SND to NITRO-SDK

  Revision 1.13  2005/04/12 00:52:11  ida
  for SDK_FROM_TOOL

  Revision 1.12  2005/02/02 05:31:58  ida
  Updated copyright year notation

  Revision 1.11  2005/02/02 05:10:47  ida
  for SDK_FROM_TOOL

  Revision 1.10  2004/08/19 06:53:42  ida
  for LR sync

  Revision 1.9  2004/07/13 05:42:22  ida
  SND_CAPTURE_0_CHANNEL -> SND_CAPTURE_0_OUT_CHANNEL

  Revision 1.8  2004/07/06 07:45:41  ida
  change function argument

  Revision 1.7  2004/07/05 06:27:54  ida
  SNDCaptureId -> SNDCapture

  Revision 1.6  2004/06/29 06:49:04  ida
  SOUND -> CHANNEL

  Revision 1.5  2004/06/23 06:32:48  ida
  hwcapture.h -> capture.h

  Revision 1.3  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.2  2004/03/30 00:49:51  ida
  for CaptureLen bug in TEG

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.5  2004/03/26 04:26:27  ida
  FORMAT_8BIT -> FORMAT_PCM8

  Revision 1.4  2004/03/25 09:52:34  ida
  SND_CAP -> SND_CAPTURE

  Revision 1.3  2004/03/22 02:16:50  ida
  for TEG pan bug

  Revision 1.2  2004/03/10 06:34:25  ida
  Capture -> HwCapture

  Revision 1.1  2004/03/08 05:40:33  ida
  rename files

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_CAPTURE_H_
#define NITRO_SND_COMMON_CAPTURE_H_

#include "nitro/types.h"

#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#ifdef SDK_ARM7

#include "nitro/hw/ARM7/ioreg_SND.h"

#endif /* SDK_ARM7 */
#endif /* SDK_FROM_TOOL */

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
    macro definition
 ******************************************************************************/

#define SND_CAPTURE_NUM 2

#ifndef SDK_TEG

#define SND_CAPTURE_0_OUT_CHANNEL 1
#define SND_CAPTURE_1_OUT_CHANNEL 3

#define SND_CAPTURE_0_IN_CHANNEL 0
#define SND_CAPTURE_1_IN_CHANNEL 2

#define SND_CAPTURE_LEN_MAX  0xffff

#else

#define SND_CAPTURE_0_OUT_CHANNEL 3
#define SND_CAPTURE_1_OUT_CHANNEL 1

#define SND_CAPTURE_0_IN_CHANNEL 2
#define SND_CAPTURE_1_IN_CHANNEL 0

#define SND_CAPTURE_LEN_MAX  0x0fff

#endif

#define SND_CAPTURE_DAD_MASK 0x07fffffc

#define SND_CAPTURE_REG_OFFSET 0x8

/******************************************************************************
    enum definition
 ******************************************************************************/

#ifndef SDK_TEG
typedef enum
{
    SND_CAPTURE_0,
    SND_CAPTURE_1
}
SNDCapture;
#else
typedef enum
{
    SND_CAPTURE_1,
    SND_CAPTURE_0
}
SNDCapture;
#endif

typedef enum
{
    SND_CAPTURE_FORMAT_PCM16,
    SND_CAPTURE_FORMAT_PCM8
}
SNDCaptureFormat;

typedef enum
{
    SND_CAPTURE_REPEAT_YES,
    SND_CAPTURE_REPEAT_NO
}
SNDCaptureRepeat;

typedef enum
{
    SND_CAPTURE_IN_MIXER,
    SND_CAPTURE_IN_CHANNEL,

    SND_CAPTURE_IN_MIXER_L = SND_CAPTURE_IN_MIXER,
    SND_CAPTURE_IN_MIXER_R = SND_CAPTURE_IN_MIXER,
    SND_CAPTURE_IN_CHANNEL0 = SND_CAPTURE_IN_CHANNEL,
    SND_CAPTURE_IN_CHANNEL2 = SND_CAPTURE_IN_CHANNEL
}
SNDCaptureIn;

typedef enum
{
    SND_CAPTURE_OUT_NORMAL,
    SND_CAPTURE_OUT_CHANNEL_MIX,

    SND_CAPTURE_OUT_CHANNEL0_MIX = SND_CAPTURE_OUT_CHANNEL_MIX,
    SND_CAPTURE_OUT_CHANNEL2_MIX = SND_CAPTURE_OUT_CHANNEL_MIX
}
SNDCaptureOut;

/******************************************************************************
    inline function
 ******************************************************************************/

#ifdef SDK_ARM7
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

/*---------------------------------------------------------------------------*
  Name:         SND_StartCapture

  Description:  Start capture

  Arguments:    capture     : target capture

  Returns:      None
 *---------------------------------------------------------------------------*/
static  inline void SND_StartCapture(SNDCapture capture)
{
    REGType8v *reg = (REGType8v *)(REG_SNDCAP0CNT_ADDR + capture);

    *reg |= REG_SND_SNDCAP0CNT_E_MASK;
}

/*---------------------------------------------------------------------------*
  Name:         SND_StartCaptureBoth

  Description:  Start capture

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
static  inline void SND_StartCaptureBoth(void)
{
    reg_SND_SNDCAPCNT |= REG_SND_SNDCAPCNT_CAP0_E_MASK | REG_SND_SNDCAPCNT_CAP1_E_MASK;
}

/*---------------------------------------------------------------------------*
  Name:         SND_StopCapture

  Description:  Stop capture

  Arguments:    capture     : target capture

  Returns:      None
 *---------------------------------------------------------------------------*/
static  inline void SND_StopCapture(SNDCapture capture)
{
    (*(REGType8v *)(REG_SNDCAP0CNT_ADDR + capture)) = 0;
}

#else

void    SND_StartCapture(SNDCapture capture);
void    SND_StartCaptureBoth(void);
void    SND_StopCapture(SNDCapture capture);

#endif /* SDK_FROM_TOOL */

#endif /* SDK_ARM7 */

/******************************************************************************
    public function declaration
 ******************************************************************************/

#ifdef SDK_ARM7

void    SND_SetupCapture(SNDCapture capture,
                         SNDCaptureFormat format,
                         void *buffer_addr,
                         int length, BOOL repeat, SNDCaptureIn in, SNDCaptureOut out);

BOOL    SND_IsCaptureActive(SNDCapture capture);

#endif /* SDK_ARM7 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_CAPTURE_H_ */
