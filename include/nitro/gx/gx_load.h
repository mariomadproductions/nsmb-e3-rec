/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     gx_load.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: gx_load.h,v $
  Revision 1.9  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.8  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.7  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.6  2004/03/23 07:08:53  takano_makoto
  Change GX*_LoadBGXScr to GX*_LoadBGXBmp.

  Revision 1.5  2004/02/20 07:22:16  nishida_kenji
  Add GX_LoadTexEx and GX_LoadTexPlttEx.

  Revision 1.4  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.3  2004/01/28 07:55:59  nishida_kenji
  add APIs for the sub 2D engine.

  Revision 1.2  2004/01/17 07:17:12  nishida_kenji
  remove external include guards

  Revision 1.1  2003/12/25 11:53:32  nishida_kenji
  new

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_GX_LOAD_H_
#define NITRO_GX_LOAD_H_

#include "nitro/gx/gxcommon.h"
#include "nitro/gx/gx_vramcnt.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

//
// Main 2D engine
//
void    GX_LoadBGPltt(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadOBJPltt(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadOAM(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadOBJ(const void *pSrc, u32 offset, u32 szByte);

void    GX_LoadBG0Scr(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadBG1Scr(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadBG2Scr(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadBG3Scr(const void *pSrc, u32 offset, u32 szByte);

void    GX_LoadBG0Char(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadBG1Char(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadBG2Char(const void *pSrc, u32 offset, u32 szByte);
void    GX_LoadBG3Char(const void *pSrc, u32 offset, u32 szByte);

void    GX_BeginLoadBGExtPltt(void);
void    GX_LoadBGExtPltt(const void *pSrc, u32 destSlotAddr, u32 szByte);
void    GX_EndLoadBGExtPltt(void);

void    GX_BeginLoadOBJExtPltt(void);
void    GX_LoadOBJExtPltt(const void *pSrc, u32 destSlotAddr, u32 szByte);
void    GX_EndLoadOBJExtPltt(void);

//
// Sub 2D engine
//
void    GXS_LoadBGPltt(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadOBJPltt(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadOAM(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadOBJ(const void *pSrc, u32 offset, u32 szByte);

void    GXS_LoadBG0Scr(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadBG1Scr(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadBG2Scr(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadBG3Scr(const void *pSrc, u32 offset, u32 szByte);

void    GXS_LoadBG0Char(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadBG1Char(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadBG2Char(const void *pSrc, u32 offset, u32 szByte);
void    GXS_LoadBG3Char(const void *pSrc, u32 offset, u32 szByte);

void    GXS_BeginLoadBGExtPltt(void);
void    GXS_LoadBGExtPltt(const void *pSrc, u32 destSlotAddr, u32 szByte);
void    GXS_EndLoadBGExtPltt(void);

void    GXS_BeginLoadOBJExtPltt(void);
void    GXS_LoadOBJExtPltt(const void *pSrc, u32 destSlotAddr, u32 szByte);
void    GXS_EndLoadOBJExtPltt(void);

//
// 3D engine
//
void    GX_BeginLoadTex(void);
void    GX_LoadTex(const void *pSrc, u32 destSlotAddr, u32 szByte);
void    GX_EndLoadTex(void);
void    GX_LoadTexEx(GXVRamTex tex, const void *pSrc, u32 destSlotAddr, u32 szByte);

void    GX_BeginLoadTexPltt(void);
void    GX_LoadTexPltt(const void *pSrc, u32 destSlotAddr, u32 szByte);
void    GX_EndLoadTexPltt(void);
void    GX_LoadTexPlttEx(GXVRamTexPltt texPltt, const void *pSrc, u32 destSlotAddr, u32 szByte);

void    GX_BeginLoadClearImage(void);
void    GX_LoadClearImageColor(const void *pSrc, u32 szByte);
void    GX_LoadClearImageDepth(const void *pSrc, u32 szByte);
void    GX_EndLoadClearImage(void);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         GX_LoadBG2Bmp

  Description:  Transfers bitmap data to BG #2 bitmap area for the MAIN 2D engine.
                pSrc, offset, and szByte must be 2-bytes aligned.

  Arguments:    pSrc             a pointer to the source of the BG screen data
                offset           an offset to the start address of BG #2 bitmap area
                szByte           the size of the source

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_LoadBG2Bmp(const void *pSrc, u32 offset, u32 szByte)
{
    GX_LoadBG2Scr(pSrc, offset, szByte);
}

/*---------------------------------------------------------------------------*
  Name:         GX_LoadBG3Bmp

  Description:  Transfers bitmap data to BG #3 bitmap area for the MAIN 2D engine.
                pSrc, offset, and szByte must be 2-bytes aligned.

  Arguments:    pSrc             a pointer to the source of the BG screen data
                offset           an offset to the start address of BG #3 bitmap area
                szByte           the size of the source

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_LoadBG3Bmp(const void *pSrc, u32 offset, u32 szByte)
{
    GX_LoadBG3Scr(pSrc, offset, szByte);
}

/*---------------------------------------------------------------------------*
  Name:         GXS_LoadBG2Bmp

  Description:  Transfers bitmap data to BG #2 bitmap area for the SUB 2D engine.
                pSrc, offset, and szByte must be 2-bytes aligned.

  Arguments:    pSrc             a pointer to the source of the BG screen data
                offset           an offset to the start address of BG #2 bitmap area
                szByte           the size of the source

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_LoadBG2Bmp(const void *pSrc, u32 offset, u32 szByte)
{
    GXS_LoadBG2Scr(pSrc, offset, szByte);
}

/*---------------------------------------------------------------------------*
  Name:         GXS_LoadBG3Bmp

  Description:  Transfers bitmap data to BG #3 bitmap area for the SUB 2D engine.
                pSrc, offset, and szByte must be 2-bytes aligned.

  Arguments:    pSrc             a pointer to the source of the BG screen data
                offset           an offset to the start address of BG #3 bitmap area
                szByte           the size of the source

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_LoadBG3Bmp(const void *pSrc, u32 offset, u32 szByte)
{
    GXS_LoadBG3Scr(pSrc, offset, szByte);
}


#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
