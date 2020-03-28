/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     struct_2d.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: struct_2d.h,v $
  Revision 1.5  2006/01/18 02:12:29  kitase_hirotake
  do-indent

  Revision 1.4  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.3  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.2  2004/02/18 09:06:07  nishida_kenji
  small fix.

  Revision 1.1  2004/02/13 09:14:10  nishida_kenji
  Initial check in.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_STRUCT_2D_H_
#define NITRO_STRUCT_2D_H_

#include "nitro/gx/gxcommon.h"





//----------------------------------------------------------------------------
//
// Typedefs, basic structure definitions, and macro definitions
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// A typedef and macros for text screen data format
//----------------------------------------------------------------------------
typedef u16 GXScrFmtText;
#define GX_SCRFMT_TEXT_CHARNAME_SHIFT                      (0)
#define GX_SCRFMT_TEXT_CHARNAME_MASK                       (0x03ff)
#define GX_SCRFMT_TEXT_HF_SHIFT                            (10)
#define GX_SCRFMT_TEXT_HF_MASK                             (0x0400)
#define GX_SCRFMT_TEXT_VF_SHIFT                            (11)
#define GX_SCRFMT_TEXT_VF_MASK                             (0x0800)
#define GX_SCRFMT_TEXT_COLORPLTT_SHIFT                     (12)
#define GX_SCRFMT_TEXT_COLORPLTT_MASK                      (0xf000)
#define GX_SCRFMT_TEXT(pltt, vf, hf, name)              \
    ((u16)(((name) << GX_SCRFMT_TEXT_CHARNAME_SHIFT) |  \
           ((hf) << GX_SCRFMT_TEXT_HF_SHIFT)         |  \
           ((vf) << GX_SCRFMT_TEXT_VF_SHIFT)         |  \
           ((pltt) << GX_SCRFMT_TEXT_COLORPLTT_SHIFT)))

//----------------------------------------------------------------------------
// A typedef and macros for affine screen data format
//----------------------------------------------------------------------------
typedef u8 GXScrFmtAffine;
#define GX_SCRFMT_AFFINE_CHARNAME_SHIFT                    (0)
#define GX_SCRFMT_AFFINE_CHARNAME_MASK                     (0xff)

//----------------------------------------------------------------------------
// A typedef and macros for bitmap screen data format
//----------------------------------------------------------------------------
typedef u8 GXScrFmt256Bmp;
#define GX_SCRFMT_256BMP_COLORNO_SHIFT                     (0)
#define GX_SCRFMT_256BMP_COLORNO_MASK                      (0xff)

//----------------------------------------------------------------------------
// A structure corresponding to a character in 16 color mode
//----------------------------------------------------------------------------
typedef union
{
    // 32 bytes
    // 4bit/pixel
    u32     data32[8];
    u16     data16[16];
    u8      data8[32];
}
GXCharFmt16;

//----------------------------------------------------------------------------
// A structure corresponding to a character in 256 color mode
//----------------------------------------------------------------------------
typedef union
{
    // 64 bytes
    // 8bit/pixel
    u32     data32[16];
    u16     data16[32];
    u8      data8[64];
}
GXCharFmt256;

//----------------------------------------------------------------------------
// A structure corresponding to a 16 colors BG palette
//----------------------------------------------------------------------------
typedef union
{
    // 32 bytes
    u16     data16[16];
    u32     data32[8];
    GXRgb   rgb[16];
}
GXBGPltt16;

// GXBGPltt16 and GXOBJPltt16 are the same.
typedef GXBGPltt16 GXOBJPltt16;

//----------------------------------------------------------------------------
// A structure corresponding to a 256 colors BG palette
//----------------------------------------------------------------------------
typedef union
{
    // 512 bytes
    u16     data16[256];
    u32     data32[128];
    GXRgb   rgb[256];
}
GXBGPltt256;

// GXBGPltt256 and GXOBJPltt256 are the same.
typedef GXBGPltt256 GXOBJPltt256;





//----------------------------------------------------------------------------
//
// Structure definitions for BG screen
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// A structure corresponding to 32x32 text screen
//----------------------------------------------------------------------------
typedef union
{
    // 2K bytes
    u16     data16[32 * 32];
    u32     data32[32 * 32 / 2];
    GXScrFmtText scr[32][32];
}
GXScrText32x32;

//----------------------------------------------------------------------------
// A structure corresponding to 64x32 text screen
//----------------------------------------------------------------------------
typedef union
{
    // 4K bytes
    u16     data16[64 * 32];
    u32     data32[64 * 32 / 2];
    GXScrFmtText scr[64][32];
}
GXScrText64x32;

//----------------------------------------------------------------------------
// A structure corresponding to 32x64 text screen
//----------------------------------------------------------------------------
typedef union
{
    // 4K bytes
    u16     data16[32 * 64];
    u32     data32[32 * 64 / 2];
    GXScrFmtText scr[32][64];
}
GXScrText32x64;

//----------------------------------------------------------------------------
// A structure corresponding to 64x64 text screen
//----------------------------------------------------------------------------
typedef union
{
    // 8K bytes
    u16     data16[64 * 64];
    u32     data32[64 * 64 / 2];
    GXScrFmtText scr[64][64];
}
GXScrText64x64;

//----------------------------------------------------------------------------
// A structure corresponding to 16x16 affine screen
//----------------------------------------------------------------------------
typedef union
{
    // 256 bytes
    u8      data8[16 * 16];
    u32     data32[16 * 16 / 4];
    GXScrFmtAffine scr[16][16];
}
GXScrAffine16x16;

//----------------------------------------------------------------------------
// A structure corresponding to 32x32 affine screen
//----------------------------------------------------------------------------
typedef union
{
    // 1K bytes
    u8      data8[32 * 32];
    u32     data32[32 * 32 / 4];
    GXScrFmtAffine scr[32][32];
}
GXScrAffine32x32;

//----------------------------------------------------------------------------
// A structure corresponding to 64x64 affine screen
//----------------------------------------------------------------------------
typedef union
{
    // 4K bytes
    u8      data8[64 * 64];
    u32     data32[64 * 64 / 4];
    GXScrFmtAffine scr[64][64];
}
GXScrAffine64x64;

//----------------------------------------------------------------------------
// A structure corresponding to 128x128 affine screen
//----------------------------------------------------------------------------
typedef union
{
    // 16K bytes
    u8      data8[128 * 128];
    u32     data32[128 * 128 / 4];
    GXScrFmtAffine scr[128][128];
}
GXScrAffine128x128;

//----------------------------------------------------------------------------
// A structure corresponding to 128x128 bitmap screen
//----------------------------------------------------------------------------
typedef union
{
    // 16K bytes
    u8      data8[128 * 128];
    u32     data32[128 * 128 / 4];
    GXScrFmt256Bmp scr[128][128];
}
GXScr256Bmp128x128;

//----------------------------------------------------------------------------
// A structure corresponding to 256x256 bitmap screen
//----------------------------------------------------------------------------
typedef union
{
    // 64K bytes
    u8      data8[256 * 256];
    u32     data32[256 * 256 / 4];
    GXScrFmt256Bmp scr[256][256];
}
GXScr256Bmp256x256;

//----------------------------------------------------------------------------
// A structure corresponding to 512x256 bitmap screen
//----------------------------------------------------------------------------
typedef union
{
    // 128K bytes
    u8      data8[512 * 256];
    u32     data32[512 * 256 / 4];
    GXScrFmt256Bmp scr[512][256];
}
GXScr256Bmp512x256;

//----------------------------------------------------------------------------
// A structure corresponding to 512x512 bitmap screen
//----------------------------------------------------------------------------
typedef union
{
    // 256K bytes
    u8      data8[512 * 512];
    u32     data32[512 * 512 / 4];
    GXScrFmt256Bmp scr[512][512];
}
GXScr256Bmp512x512;

//----------------------------------------------------------------------------
// A structure corresponding to 128x128 direct color bitmap screen
//----------------------------------------------------------------------------
typedef union
{
    // 32K bytes
    u16     data16[128 * 128];
    u32     data32[128 * 128 / 2];
    GXRgba  scr[128][128];
}
GXScrDCBmp128x128;

//----------------------------------------------------------------------------
// A structure corresponding to 256x256 direct color bitmap screen
//----------------------------------------------------------------------------
typedef union
{
    // 128K bytes
    u16     data16[256 * 256];
    u32     data32[256 * 256 / 2];
    GXRgba  scr[256][256];
}
GXScrDCBmp256x256;

//----------------------------------------------------------------------------
// A structure corresponding to 512x256 direct color bitmap screen
//----------------------------------------------------------------------------
typedef union
{
    // 256K bytes
    u16     data16[512 * 256];
    u32     data32[512 * 256 / 2];
    GXRgba  scr[512][256];
}
GXScrDCBmp512x256;

//----------------------------------------------------------------------------
// A structure corresponding to 512x512 direct color bitmap screen
//----------------------------------------------------------------------------
typedef union
{
    // 512K bytes
    u16     data16[512 * 512];
    u32     data32[512 * 512 / 2];
    GXRgba  scr[512][512];
}
GXScrDCBmp512x512;





//----------------------------------------------------------------------------
//
// Structure definitions for BG characters
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// A structure corresponding to characters in 16 colors mode
//----------------------------------------------------------------------------
typedef struct
{
    // 32K bytes
    GXCharFmt16 ch[1024];
}
GXCharBGText16;

//----------------------------------------------------------------------------
// A structure corresponding to characters in 256 colors mode(text BG)
//----------------------------------------------------------------------------
typedef struct
{
    // 64K bytes
    GXCharFmt256 ch[1024];
}
GXCharBGText256;

//----------------------------------------------------------------------------
// A structure corresponding to characters in 256 colors mode(affine BG)
//----------------------------------------------------------------------------
typedef struct
{
    // 16K bytes
    GXCharFmt256 ch[256];
}
GXCharBGAffine256;





//----------------------------------------------------------------------------
//
// Structure definitions for BG palettes
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// A structure corresponding to the standard BG palette
//----------------------------------------------------------------------------
typedef union
{
    // 512 bytes
    GXBGPltt256 pltt256;
    GXBGPltt16 pltt16[16];
}
GXBGStdPlttData;

//----------------------------------------------------------------------------
// A structure corresponding to the standard OBJ palette
//----------------------------------------------------------------------------
typedef union
{
    // 512 bytes
    GXOBJPltt256 pltt256;
    GXOBJPltt16 pltt16[16];
}
GXOBJStdPlttData;

//----------------------------------------------------------------------------
// A structure corresponding to the standard palette
//----------------------------------------------------------------------------
typedef struct
{
    // 1024 bytes
    GXBGStdPlttData bgPltt;
    GXOBJStdPlttData objPltt;
}
GXStdPlttData;

//----------------------------------------------------------------------------
// A structure corresponding to the BG extended palette
//----------------------------------------------------------------------------
typedef struct
{
    // 8K bytes
    GXBGPltt256 pltt256[16];
}
GXBGExtPlttData;

//----------------------------------------------------------------------------
// A structure corresponding to the OBJ extended palette
//----------------------------------------------------------------------------
typedef struct
{
    // 8K bytes
    GXOBJPltt256 pltt256[16];
}
GXOBJExtPlttData;

#endif
