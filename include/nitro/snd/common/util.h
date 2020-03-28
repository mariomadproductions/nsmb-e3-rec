/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     util.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: util.h,v $
  Revision 1.16  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.15  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.14  2005/03/24 04:35:33  ida
  sound patch for NITRO-System 2005/03/28

  Revision 1.11  2005/03/08 05:45:01  ida
  SDK_FROM_TOOL support

  Revision 1.10  2005/02/02 05:31:58  ida
  Updated copyright year notation

  Revision 1.9  2005/02/02 05:10:47  ida
  for SDK_FROM_TOOL

  Revision 1.8  2004/10/04 06:33:03  ida
  Fixed backslashes at end of line.

  Revision 1.11  2004/09/14 01:59:57  yasu
  Fixed backslashes at end of line.

  Revision 1.10  2004/08/02 08:22:59  ida
  update NitroSystem modules

  Revision 1.7  2004/07/05 06:34:27  ida
  SND_CalcRandom become ARM7 only

  Revision 1.6  2004/06/23 06:35:39  ida
  remove SND_CopyMemory16

  Revision 1.5  2004/05/17 04:05:07  ida
  fix SND_SinIdx wrong return type

  Revision 1.4  2004/05/07 07:38:16  ida
  add SND_CalcRandom

  Revision 1.3  2004/05/06 00:00:41  ida
  add comments

  Revision 1.2  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.7  2004/03/11 01:51:26  ida
  SND_CopyMemory -> SND_CopyMemory16

  Revision 1.6  2004/03/10 06:28:50  ida
  SND_SndCopyMemory -> SND_CopyMemory

  Revision 1.5  2004/03/08 05:48:27  ida
  merged snd_util.h

  Revision 1.2  2004/02/25 04:25:56  ida
  snd_util.c ARM7 -> common

  Revision 1.1  2004/02/13 00:16:47  ida
  ARM7 -> common
  
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_UTIL_H_
#define NITRO_SND_COMMON_UTIL_H_

#include "nitro/types.h"

#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#include "nitro/misc.h"
#else
#define SDK_MINMAX_ASSERT(exp, min, max)           ((void) 0)
#endif /* SDK_FROM_TOOL */

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
    macro definition
 ******************************************************************************/

#define SND_PITCH_DIVISION_BIT     6   // Semitone resolution (bit count)
#define SND_PITCH_DIVISION_RANGE ( 1 << SND_PITCH_DIVISION_BIT )        // Semitone resolution

#define SND_PITCH_TABLE_SIZE     ( 12 * SND_PITCH_DIVISION_RANGE )      // Pitch calculation table size
#define SND_PITCH_TABLE_BIAS       0x10000
#define SND_PITCH_TABLE_SHIFT     16

#define SND_VOLUME_DB_MIN        (-723) // -72.3dB = -inf
#define SND_VOLUME_DB_MAX         0
#define SND_VOLUME_TABLE_SIZE ( SND_VOLUME_DB_MAX - SND_VOLUME_DB_MIN + 1 )

#define SND_CALC_DECIBEL_SCALE_MAX    127

#define SND_DECIBEL_TABLE_SIZE        128
#define SND_DECIBEL_SQUARE_TABLE_SIZE 128

#define SND_SIN_TABLE_SIZE 32
#define SND_SIN_PERIOD ( SND_SIN_TABLE_SIZE * 4 )

/******************************************************************************
    private variable declaration
 ******************************************************************************/

extern const s16 SNDi_DecibelTable[SND_DECIBEL_TABLE_SIZE];
extern const s16 SNDi_DecibelSquareTable[SND_DECIBEL_SQUARE_TABLE_SIZE];

/******************************************************************************
    inline function definition
 ******************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         SND_CalcDecibel

  Description:  Calculate decibel from scale factor

  Arguments:    scale      scale factor

  Returns:      decibel
 *---------------------------------------------------------------------------*/
#ifndef _MSC_VER
static  inline
#else
__inline
#endif
s16 SND_CalcDecibel(int scale)
{
    SDK_MINMAX_ASSERT(scale, 0, SND_CALC_DECIBEL_SCALE_MAX);

    return SNDi_DecibelTable[scale];
}

/*---------------------------------------------------------------------------*
  Name:         SND_CalcDecibelSquare

  Description:  Calculate decibel from square scale factor

  Arguments:    scale      square scale factor

  Returns:      decibel
 *---------------------------------------------------------------------------*/
#ifndef _MSC_VER
static  inline
#else
__inline
#endif
s16 SND_CalcDecibelSquare(int scale)
{
    SDK_MINMAX_ASSERT(scale, 0, SND_CALC_DECIBEL_SCALE_MAX);

    return SNDi_DecibelSquareTable[scale];
}

/******************************************************************************
    public function declaration
 ******************************************************************************/

u16     SND_CalcTimer(int orgTimer, int pitch);
u16     SND_CalcChannelVolume(int dB);

#ifdef SDK_ARM7

u16     SND_CalcRandom(void);
s8      SND_SinIdx(int index);

#endif /* SDK_ARM7 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_UTIL_H_ */
