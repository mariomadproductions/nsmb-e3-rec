/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SND - include
  File:     bank.h

  Copyright 2004-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: bank.h,v $
  Revision 1.20  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.19  2005/09/15 00:57:19  ida
  Handling gcc warnings

  Revision 1.18  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.17  2005/08/18 04:33:09  ida
  Corrected tool orientation

  Revision 1.16  2005/05/10 01:51:09  ida
  Added SND_BANK_DISABLE_RELEASE

  Revision 1.15  2005/04/12 06:15:07  ida
  Moved SND to NITRO-SDK

  Revision 1.17  2005/04/12 00:51:22  ida
  Added SNDBankDataCallback

  Revision 1.16  2005/03/17 04:25:36  ida
  Added SND_INST_NULL

  Revision 1.15  2005/02/21 02:37:33  ida
  Warning measures

  Revision 1.14  2005/02/02 05:10:33  ida
  for SDK_FROM_TOOL

  Revision 1.13  2005/01/19 06:23:54  ida
  Added functions related to external reference waveform archive implementation

  Revision 1.12  2004/07/13 05:42:46  ida
  change API name

  Revision 1.11  2004/07/09 06:48:08  ida
  change SND_NoteOn interface

  Revision 1.10  2004/07/07 05:06:32  ida
  add SND_WriteInstData

  Revision 1.9  2004/07/06 07:46:44  ida
  workaround multi wave archive for one bank

  Revision 1.8  2004/07/05 06:32:59  ida
  change structure name

  Revision 1.7  2004/06/23 06:32:26  ida
  change interface

  Revision 1.6  2004/05/13 01:04:11  ida
  SNDBinaryHeader -> SNDBinaryFileHeader

  Revision 1.5  2004/05/12 06:39:58  ida
  modify data header structure

  Revision 1.4  2004/04/30 00:42:42  ida
  add comments

  Revision 1.3  2004/04/26 02:25:36  ida
  add bank and wave archive link

  Revision 1.2  2004/04/08 07:29:02  ida
  fix Project name

  Revision 1.1  2004/03/26 06:26:43  ida
  add SND-SDK header files

  Revision 1.7  2004/03/11 01:52:36  ida
  renumber SNDInstType

  Revision 1.6  2004/03/10 08:38:54  ida
  remove SNDHeader

  Revision 1.5  2004/03/10 06:35:14  ida
  SND_Snd -> SND_

  Revision 1.4  2004/03/08 05:40:33  ida
  rename files

  Revision 1.3  2004/03/08 03:04:33  ida
  SND_AssignWaveBank: port.h -> bank.h

  Revision 1.2  2004/02/19 07:19:44  ida
  NNS_ -> SND_

  Revision 1.1  2004/02/19 07:07:58  ida
  add NITRO System snd libraries

  Revision 1.1  2004/02/13 01:44:09  ida
  initial version
  
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_SND_COMMON_BANK_H_
#define NITRO_SND_COMMON_BANK_H_

#include "nitro/snd/common/exchannel.h" // for SNDWaveParam
#include "nitro/snd/common/data.h"     // for SNDBinaryFileHeader and SNDBinaryBlockHeader

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
	macro definition
 ******************************************************************************/

#define SND_INST_KEYSPLIT_MAX 8

#define SND_BANK_TO_WAVEARC_MAX 4

#define SND_BANK_DISABLE_RELEASE 255

/******************************************************************************
	structure declarations
 ******************************************************************************/

struct SNDWaveArc;
struct SNDExChannel;

/******************************************************************************
	enum definition
 ******************************************************************************/

typedef enum SNDInstType
{
    SND_INST_INVALID = 0,

    SND_INST_PCM = 0x01,
    SND_INST_PSG,
    SND_INST_NOISE,
    SND_INST_DIRECTPCM,
    SND_INST_NULL,

    SND_INST_DRUM_SET = 0x10,
    SND_INST_KEY_SPLIT
}
SNDInstType;

/******************************************************************************
	structure definition
 ******************************************************************************/

#ifdef _MSC_VER
#pragma warning( disable : 4200 )      // warning: zero-sized array in struct/union
#endif

typedef struct SNDWaveArcLink
{
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
}
SNDWaveArcLink;

typedef struct SNDWaveArc
{
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;

    struct SNDWaveArcLink *topLink;
    u32     reserved[7];
    u32     waveCount;
    u32     waveOffset[0];
}
SNDWaveArc;

typedef struct SNDWaveData
{
    struct SNDWaveParam param;
    u8      samples[0];
}
SNDWaveData;

typedef struct SNDBankData
{
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;

    struct SNDWaveArcLink waveArcLink[SND_BANK_TO_WAVEARC_MAX];
    u32     instCount;
    u32     instOffset[0];
}
SNDBankData;

typedef struct SNDInstParam
{
    u16     wave[2];
    u8      original_key;
    u8      attack;
    u8      decay;
    u8      sustain;
    u8      release;
    u8      pan;
}
SNDInstParam;                          // Total 10Bytes

typedef struct SNDInstData
{
    u8      type;                      // enum SNDInstType
    u8      padding_;

    struct SNDInstParam param;
}
SNDInstData;                           // Total 12Bytes

typedef struct SNDKeySplit
{
    u8      key[SND_INST_KEYSPLIT_MAX];
    struct SNDInstData instOffset[0];
}
SNDKeySplit;

typedef struct SNDDrumSet
{
    u8      min;
    u8      max;
    struct SNDInstData instOffset[0];
}
SNDDrumSet;

typedef struct SNDInstPos
{
    u32     prgNo;
    u32     index;
}
SNDInstPos;

#if defined(SDK_WIN32) || defined(SDK_FROM_TOOL)

struct SNDBankDataCallback;
typedef BOOL (__stdcall * SNDReadInstDataFunc) (const struct SNDBankDataCallback * bank, int prgNo,
                                                int key, struct SNDInstData *inst);

typedef struct SNDBankDataCallback
{
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;

    void   *arg;
    SNDReadInstDataFunc readInstDataFunc;
}
SNDBankDataCallback;

#endif

#ifdef _MSC_VER
#pragma warning( default : 4200 )      // warning: zero-sized array in struct/union
#endif

/******************************************************************************
	public functions
 ******************************************************************************/

void    SND_AssignWaveArc(struct SNDBankData *bank, int index, struct SNDWaveArc *waveArc);
void    SND_DestroyBank(struct SNDBankData *bank);
void    SND_DestroyWaveArc(struct SNDWaveArc *waveArc);

BOOL    SND_ReadInstData(const struct SNDBankData *bank, int prgNo, int key,
                         struct SNDInstData *inst);
BOOL    SND_WriteInstData(struct SNDBankData *bank, int prgNo, int key,
                          const struct SNDInstData *inst);

struct SNDInstPos SND_GetFirstInstDataPos(const struct SNDBankData *bank);
BOOL    SND_GetNextInstData(const struct SNDBankData *bank, struct SNDInstData *inst,
                            struct SNDInstPos *pos);

u32     SND_GetWaveDataCount(const struct SNDWaveArc *waveArc);
void    SND_SetWaveDataAddress(struct SNDWaveArc *waveArc, int index, const SNDWaveData *address);
const SNDWaveData *SND_GetWaveDataAddress(const struct SNDWaveArc *waveArc, int index);

#ifdef SDK_ARM7

BOOL    SND_NoteOn(struct SNDExChannel *ch_p,
                   int key,
                   int velocity,
                   s32 length, const struct SNDBankData *bank, const struct SNDInstData *inst);

#endif /* SDK_ARM7 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NITRO_SND_COMMON_BANK_H_ */
