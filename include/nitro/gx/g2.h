/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     g2.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: g2.h,v $
  Revision 1.59  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.58  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.57  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.56  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.55  2004/12/27 04:45:05  takano_makoto
  Added Getter function of register

  Revision 1.54  2004/11/02 17:06:20  takano_makoto
  fix comments.

  Revision 1.53  2004/08/19 01:09:03  takano_makoto
  Fix bugs in G2*_SetBGMosaicSize(), G2*_SetOBJMosaicSize().

  Revision 1.52  2004/05/14 11:52:57  takano_makoto
  Add #ifndef SDK_FROM_TOOL for VC or BCB.

  Revision 1.51  2004/02/18 02:12:09  nishida_kenji
  Remove magic numbers.

  Revision 1.50  2004/02/17 08:12:26  nishida_kenji
  small fix.

  Revision 1.49  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.48  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.47  2004/02/01 23:57:59  nishida_kenji
  Y coordinates of a window must be between 0 and 192

  Revision 1.46  2004/01/27 11:13:58  nishida_kenji
  append 'static' to inline function prototypes.

  Revision 1.45  2004/01/26 12:47:18  nishida_kenji
  adds APIs for the sub engine.

  Revision 1.43  2004/01/18 07:45:41  nishida_kenji
  small bug fix

  Revision 1.42  2004/01/17 07:17:12  nishida_kenji
  remove external include guards

  Revision 1.41  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.40  2003/12/26 00:54:16  nishida_kenji
  minor fix

  Revision 1.39  2003/12/25 11:00:10  nishida_kenji
  converted by GX_APIChangeFrom031212-2.pl

  Revision 1.38  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.37  2003/12/17 09:00:20  nishida_kenji
  Totally revised APIs.
  build/buildtools/GX_APIChangeFrom031212.pl would help you change your program to some extent.

  Revision 1.36  2003/12/17 08:50:33  nishida_kenji
  revise comments

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_G2_H_
#define NITRO_G2_H_

#include "nitro/gx/gxcommon.h"
#include "nitro/hw/ARM9/ioreg_G2.h"
#include "nitro/hw/ARM9/ioreg_G2S.h"
#include "nitro/hw/ARM9/ioreg_GX.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

typedef struct
{
    u8      planeMask:5;
    u8      effect:1;
    u8      _reserve:2;
}
GXWndPlane;

typedef enum
{
    GX_WND_PLANEMASK_NONE = 0x0000,
    GX_WND_PLANEMASK_BG0 = 0x0001,
    GX_WND_PLANEMASK_BG1 = 0x0002,
    GX_WND_PLANEMASK_BG2 = 0x0004,
    GX_WND_PLANEMASK_BG3 = 0x0008,
    GX_WND_PLANEMASK_OBJ = 0x0010
}
GXWndPlaneMask;

#define GX_WND_PLANEMASK_ASSERT(x)                                   \
    SDK_MINMAX_ASSERT(x,                                             \
                      GX_WND_PLANEMASK_NONE,                         \
                      (GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | \
                       GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | \
                       GX_WND_PLANEMASK_OBJ))


typedef enum
{
    GX_BLEND_PLANEMASK_NONE = 0x0000,
    GX_BLEND_PLANEMASK_BG0 = 0x0001,
    GX_BLEND_PLANEMASK_BG1 = 0x0002,
    GX_BLEND_PLANEMASK_BG2 = 0x0004,
    GX_BLEND_PLANEMASK_BG3 = 0x0008,
    GX_BLEND_PLANEMASK_OBJ = 0x0010,
    GX_BLEND_PLANEMASK_BD = 0x0020
}
GXBlendPlaneMask;

#define GX_BLEND_PLANEMASK_ASSERT(x) \
    SDK_MINMAX_ASSERT(x, GX_BLEND_PLANEMASK_NONE, 0x3f)

#define GX_MOSAICSIZE_ASSERT(x) SDK_MINMAX_ASSERT(x, 0, 15)


/* if include from Other Environment for exsample VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------


//
// Main 2D engine
//
static void G2_SetBG0Offset(int hOffset, int vOffset);
static void G2_SetBG1Offset(int hOffset, int vOffset);
static void G2_SetBG2Offset(int hOffset, int vOffset);
static void G2_SetBG3Offset(int hOffset, int vOffset);

// mtx->_00 = A, mtx->_01 = B, mtx->_10 = C, mtx->_11 = D in the programming manual
static void G2_SetBG2Affine(const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1);
static void G2_SetBG3Affine(const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1);

static void G2_SetWnd0InsidePlane(int wnd /* GXWndPlaneMask */ , BOOL effect);
static void G2_SetWnd1InsidePlane(int wnd /* GXWndPlaneMask */ , BOOL effect);
static void G2_SetWndOutsidePlane(int wnd /* GXWndPlaneMask */ , BOOL effect);
static void G2_SetWndOBJInsidePlane(int wnd /* GXWndPlaneMask */ , BOOL effect);
static void G2_SetWnd0Position(int x1, int y1, int x2, int y2);
static void G2_SetWnd1Position(int x1, int y1, int x2, int y2);

static void G2_SetBGMosaicSize(int hSize, int vSize);
static void G2_SetOBJMosaicSize(int hSize, int vSize);

// BLDCNT, BLDALPHA, BLDY are packaged by them.
static void G2_BlendNone(void);
static void G2_SetBlendAlpha(int plane1,        // GXBlendPlaneMask
                             int plane2,        // GXBlendPlaneMask
                             int ev1, int ev2);
// brightness takes -16 to +16, the mode of BLDCNT changes corresponding to the sign.
static void G2_SetBlendBrightness(int plane,    // GXBlendPlaneMask
                                  int brightness);
static void G2_SetBlendBrightnessExt(int plane1,        // GXBlendPlaneMask
                                     int plane2,        // GXBlendPlaneMask
                                     int ev1, int ev2, int brightness);

static void G2_ChangeBlendAlpha(int ev1, int ev2);
static void G2_ChangeBlendBrightness(int brightness);

//
// Sub 2D engine
//
static void G2S_SetBG0Offset(int hOffset, int vOffset);
static void G2S_SetBG1Offset(int hOffset, int vOffset);
static void G2S_SetBG2Offset(int hOffset, int vOffset);
static void G2S_SetBG3Offset(int hOffset, int vOffset);

// mtx->_00 = A, mtx->_01 = B, mtx->_10 = C, mtx->_11 = D in the programming manual
static void G2S_SetBG2Affine(const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1);
static void G2S_SetBG3Affine(const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1);

static void G2S_SetWnd0InsidePlane(int wnd /* GXWndPlaneMask */ , BOOL effect);
static void G2S_SetWnd1InsidePlane(int wnd /* GXWndPlaneMask */ , BOOL effect);
static void G2S_SetWndOutsidePlane(int wnd /* GXWndPlaneMask */ , BOOL effect);
static void G2S_SetWndOBJInsidePlane(int wnd /* GXWndPlaneMask */ , BOOL effect);
static void G2S_SetWnd0Position(int x1, int y1, int x2, int y2);
static void G2S_SetWnd1Position(int x1, int y1, int x2, int y2);

static void G2S_SetBGMosaicSize(int hSize, int vSize);
static void G2S_SetOBJMosaicSize(int hSize, int vSize);

// BLDCNT, BLDALPHA, BLDY are packaged by them.
static void G2S_BlendNone(void);
static void G2S_SetBlendAlpha(int plane1,       // GXBlendPlaneMask
                              int plane2,       // GXBlendPlaneMask
                              int ev1, int ev2);
// brightness takes -16 to +16, the mode of BLDCNT changes corresponding to the sign.
static void G2S_SetBlendBrightness(int plane,   // GXBlendPlaneMask
                                   int brightness);
static void G2S_SetBlendBrightnessExt(int plane1,       // GXBlendPlaneMask
                                      int plane2,       // GXBlendPlaneMask
                                      int ev1, int ev2, int brightness);

static void G2S_ChangeBlendAlpha(int ev1, int ev2);
static void G2S_ChangeBlendBrightness(int brightness);


//----------------------------------------------------------------------------
// Internal use only
//----------------------------------------------------------------------------
void    G2x_SetBGyAffine_(u32 addr, const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1);
void    G2x_SetBlendAlpha_(u32 addr, int plane1, int plane2, int ev1, int ev2);
void    G2x_SetBlendBrightness_(u32 addr, int plane, int brightness);
void    G2x_SetBlendBrightnessExt_(u32 addr, int plane1, int plane2, int ev1, int ev2,
                                   int brightness);
void    G2x_ChangeBlendBrightness_(u32 addr, int brightness);


//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
// Display A(Main Display)
//
//----------------------------------------------------------------------------


/*---------------------------------------------------------------------------*
  Name:         G2_SetBG0Offset

  Description:  Set the BG0 screen offset

  Arguments:    hOffset    H-offset(in dot)
                vOffset    V-offset(in dot)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBG0Offset(int hOffset, int vOffset)
{
    SDK_WARNING(0 == (reg_GX_DISPCNT & REG_GX_DISPCNT_BG02D3D_MASK),
                "BG0 is in 3D mode now. call \'G3X_SetHOffset\'\n");

    reg_G2_BG0OFS = (u32)(((hOffset << REG_G2_BG0OFS_HOFFSET_SHIFT) & REG_G2_BG0OFS_HOFFSET_MASK) |
                          ((vOffset << REG_G2_BG0OFS_VOFFSET_SHIFT) & REG_G2_BG0OFS_VOFFSET_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBG1Offset

  Description:  Set the BG1 screen offset

  Arguments:    hOffset    H-offset(in dot)
                vOffset    V-offset(in dot)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBG1Offset(int hOffset, int vOffset)
{
    reg_G2_BG1OFS = (u32)(((hOffset << REG_G2_BG1OFS_HOFFSET_SHIFT) & REG_G2_BG1OFS_HOFFSET_MASK) |
                          ((vOffset << REG_G2_BG1OFS_VOFFSET_SHIFT) & REG_G2_BG1OFS_VOFFSET_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBG2Offset

  Description:  Set the BG2 screen offset

  Arguments:    hOffset    H-offset(in dot)
                vOffset    V-offset(in dot)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBG2Offset(int hOffset, int vOffset)
{
#ifdef SDK_DEBUG
    {
        u32     tmp = (reg_GX_DISPCNT & REG_GX_DISPCNT_BGMODE_MASK) >> REG_GX_DISPCNT_BGMODE_SHIFT;
        SDK_WARNING((0 == tmp) || (1 == tmp) || (3 == tmp),
                    "G2_SetBG2Offset requires BG #2 to be text mode. Use G2_SetBG2Affine instead.");
    }
#endif
    reg_G2_BG2OFS = (u32)(((hOffset << REG_G2_BG2OFS_HOFFSET_SHIFT) & REG_G2_BG2OFS_HOFFSET_MASK) |
                          ((vOffset << REG_G2_BG2OFS_VOFFSET_SHIFT) & REG_G2_BG2OFS_VOFFSET_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBG3Offset

  Description:  Set the BG3 screen offset

  Arguments:    hOffset    H-offset(in dot)
                vOffset    V-offset(in dot)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBG3Offset(int hOffset, int vOffset)
{
#ifdef SDK_DEBUG
    {
        u32     tmp = (reg_GX_DISPCNT & REG_GX_DISPCNT_BGMODE_MASK) >> REG_GX_DISPCNT_BGMODE_SHIFT;
        SDK_WARNING(0 == tmp,
                    "G2_SetBG3Offset requires BG #3 to be text mode. Use G2_SetBG3Affine instead.");
    }
#endif
    reg_G2_BG3OFS = (u32)(((hOffset << REG_G2_BG3OFS_HOFFSET_SHIFT) & REG_G2_BG3OFS_HOFFSET_MASK) |
                          ((vOffset << REG_G2_BG3OFS_VOFFSET_SHIFT) & REG_G2_BG3OFS_VOFFSET_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetWnd0InsidePlane

  Description:  Select the planes inside the Window #0

  Arguments:    wnd      Set of the planes inside the Window #0
                effect   enable/disable blending/brightness effect

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetWnd0InsidePlane(int wnd, BOOL effect)
{
    u32     tmp;
    GX_WND_PLANEMASK_ASSERT(wnd);

    tmp = ((reg_G2_WININ & ~REG_G2_WININ_WIN0IN_MASK) | ((u32)wnd << REG_G2_WININ_WIN0IN_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2_WININ_WIN0IN_SHIFT);     // EFCT
    }

    reg_G2_WININ = (u16)tmp;
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetWnd0InsidePlane

  Description:  Get the planes inside the Window #0

  Arguments:    none.
  
  Returns:      structure of the plane mask and effect flag;
 *---------------------------------------------------------------------------*/
static inline GXWndPlane G2_GetWnd0InsidePlane(void)
{
    return *(const GXWndPlane *)(REG_WININ_ADDR);
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetWnd1InsidePlane

  Description:  Select the planes inside the Window #1

  Arguments:    wnd      Set of the planes inside the Window #1
                effect   enable/disable blending/brightness effect

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetWnd1InsidePlane(int wnd, BOOL effect)
{
    u32     tmp;
    GX_WND_PLANEMASK_ASSERT(wnd);

    tmp = ((reg_G2_WININ & ~REG_G2_WININ_WIN1IN_MASK) | ((u32)wnd << REG_G2_WININ_WIN1IN_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2_WININ_WIN1IN_SHIFT);     // EFCT
    }

    reg_G2_WININ = (u16)tmp;
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetWnd1InsidePlane

  Description:  Get the planes inside the Window #1

  Arguments:    none.
  
  Returns:      structure of the plane mask and effect flag;
 *---------------------------------------------------------------------------*/
static inline GXWndPlane G2_GetWnd1InsidePlane(void)
{
    return *(const GXWndPlane *)(REG_WININ_ADDR + 1);
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetWndOutsidePlane

  Description:  Select the planes outside the Window #0, #1, OBJ

  Arguments:    wnd      Set of the planes outside the windows
                effect   enable/disable blending/brightness effect

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetWndOutsidePlane(int wnd, BOOL effect)
{
    u32     tmp;
    GX_WND_PLANEMASK_ASSERT(wnd);

    tmp = ((reg_G2_WINOUT & ~REG_G2_WINOUT_WINOUT_MASK) | ((u32)wnd << REG_G2_WINOUT_WINOUT_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2_WINOUT_WINOUT_SHIFT);    // EFCT
    }

    reg_G2_WINOUT = (u16)tmp;
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetWndOutsidePlane

  Description:  Get the planes outside the Window

  Arguments:    none.
  
  Returns:      structure of the plane mask and effect flag;
 *---------------------------------------------------------------------------*/
static inline GXWndPlane G2_GetWndOutsidePlane(void)
{
    return *(const GXWndPlane *)(REG_WINOUT_ADDR);
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetWndOBJInsidePlane

  Description:  Select the planes inside the OBJ window

  Arguments:    wnd      Set of the planes inside the OBJ window

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetWndOBJInsidePlane(int wnd, BOOL effect)
{
    u32     tmp;
    GX_WND_PLANEMASK_ASSERT(wnd);

    tmp = ((reg_G2_WINOUT & ~REG_G2_WINOUT_OBJWININ_MASK) |
           ((u32)wnd << REG_G2_WINOUT_OBJWININ_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2_WINOUT_OBJWININ_SHIFT);  // EFCT
    }

    reg_G2_WINOUT = (u16)tmp;
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetWndOBJInsidePlane

  Description:  Get the planes inside the OBJ Window

  Arguments:    none.
  
  Returns:      structure of the plane mask and effect flag;
 *---------------------------------------------------------------------------*/
static inline GXWndPlane G2_GetWndOBJInsidePlane(void)
{
    return *(const GXWndPlane *)(REG_WINOUT_ADDR + 1);
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetWnd0Position

  Description:  Specify the position of the Window #0

  Arguments:    x1        X coordinate of the upper left of the window
                y1        Y coordinate of the upper left of the window
                x2        X coordinate of the lower right of the window
                y2        Y coordinate of the lower right of the window

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetWnd0Position(int x1, int y1, int x2, int y2)
{
    SDK_MINMAX_ASSERT(y1, 0, 192);
    SDK_MINMAX_ASSERT(y2, 0, 192);

    // Note that the addresses of reg_G2_WIN0H and reg_G2_WIN0V are separate.
    reg_G2_WIN0H = (u16)(((x1 << REG_G2_WIN0H_LEFTX_SHIFT) & REG_G2_WIN0H_LEFTX_MASK) |
                         ((x2 << REG_G2_WIN0H_RIGHTX_SHIFT) & REG_G2_WIN0H_RIGHTX_MASK));

    reg_G2_WIN0V = (u16)(((y1 << REG_G2_WIN0V_UPY_SHIFT) & REG_G2_WIN0V_UPY_MASK) |
                         ((y2 << REG_G2_WIN0V_DOWNY_SHIFT) & REG_G2_WIN0V_DOWNY_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetWnd1Position

  Description:  Specify the position of the Window #1

  Arguments:    x1        X coordinate of the upper left of the window
                y1        Y coordinate of the upper left of the window
                x2        X coordinate of the lower right of the window
                y2        Y coordinate of the lower right of the window

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetWnd1Position(int x1, int y1, int x2, int y2)
{
    SDK_MINMAX_ASSERT(y1, 0, 192);
    SDK_MINMAX_ASSERT(y2, 0, 192);

    // Note that the addresses of reg_G2_WIN1H and reg_G2_WIN1V are separate.
    reg_G2_WIN1H = (u16)(((x1 << REG_G2_WIN1H_LEFTX_SHIFT) & REG_G2_WIN1H_LEFTX_MASK) |
                         ((x2 << REG_G2_WIN1H_RIGHTX_SHIFT) & REG_G2_WIN1H_RIGHTX_MASK));

    reg_G2_WIN1V = (u16)(((y1 << REG_G2_WIN1V_UPY_SHIFT) & REG_G2_WIN1V_UPY_MASK) |
                         ((y2 << REG_G2_WIN1V_DOWNY_SHIFT) & REG_G2_WIN1V_DOWNY_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBGMosaicSize

  Description:  Specify the size of the mosaic applied on BGs

  Arguments:    hSize     the size of the mosaic in horizontal direction
                vSize     the size of the mosaic in vertical direction

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBGMosaicSize(int hSize, int vSize)
{
    GX_MOSAICSIZE_ASSERT(hSize);
    GX_MOSAICSIZE_ASSERT(vSize);

    *((vu8 *)REG_MOSAIC_ADDR) = (u8)((hSize << REG_G2_MOSAIC_BGHSIZE_SHIFT) |
                                     (vSize << REG_G2_MOSAIC_BGVSIZE_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJMosaicSize

  Description:  Specify the size of the mosaic applied on OBJs

  Arguments:    hSize     the size of the mosaic in horizontal direction
                vSize     the size of the mosaic in vertical direction

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJMosaicSize(int hSize, int vSize)
{
    GX_MOSAICSIZE_ASSERT(hSize);
    GX_MOSAICSIZE_ASSERT(vSize);

    *((vu8 *)(REG_MOSAIC_ADDR + 1)) = (u8)((hSize << (REG_G2_MOSAIC_OBJHSIZE_SHIFT - 8)) |
                                           (vSize << (REG_G2_MOSAIC_OBJVSIZE_SHIFT - 8)));
}


/*---------------------------------------------------------------------------*
  Name:         G2_BlendNone

  Description:  No Blendings between the planes

  Arguments:    none

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_BlendNone()
{
    reg_G2_BLDCNT = 0;
}


/*---------------------------------------------------------------------------*
  Name:         G2_ChangeBlendAlpha

  Description:  Set blending coefficients directly

  Arguments:    ev1     blending coefficient1
                ev2     blending coefficient2

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_ChangeBlendAlpha(int ev1, int ev2)
{
    GX_ALPHA_ASSERT(ev1);
    GX_ALPHA_ASSERT(ev2);

    reg_G2_BLDALPHA = (u16)((ev1 << REG_G2_BLDALPHA_EVA_SHIFT) |
                            (ev2 << REG_G2_BLDALPHA_EVB_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBG2Affine

  Description:  Affine transform on BG2(MAIN engine).

  Arguments:    mtx          a pointer to a matrix
                centerX      center of rotation
                centerY      center of rotation
                x1           the upper left point before rotation
                y1           the upper left point before rotation

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBG2Affine(const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1)
{
    G2x_SetBGyAffine_((u32)&reg_G2_BG2PA, mtx, centerX, centerY, x1, y1);
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBG3Affine

  Description:  Affine transform on BG3(MAIN engine).

  Arguments:    mtx          a pointer to a matrix
                centerX      center of rotation
                centerY      center of rotation
                x1           the upper left point before rotation
                y1           the upper left point before rotation

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBG3Affine(const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1)
{
    G2x_SetBGyAffine_((u32)&reg_G2_BG3PA, mtx, centerX, centerY, x1, y1);
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBlendAlpha

  Description:  Alpha blending on plane1 and plane2(MAIN engine).

  Arguments:    plane1       a set of planes
                plane2       a set of planes
                ev1          coefficient of plane1's color(0 to 16)
                ev2          coefficient of plane2's color(0 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBlendAlpha(int plane1, int plane2, int ev1, int ev2)
{
    G2x_SetBlendAlpha_((u32)&reg_G2_BLDCNT, plane1, plane2, ev1, ev2);
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBlendBrightness

  Description:  Changes brightness of plane(MAIN engine).

  Arguments:    plane        a set of planes
                brightness   change of brightness(-16 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBlendBrightness(int plane, int brightness)
{
    G2x_SetBlendBrightness_((u32)&reg_G2_BLDCNT, plane, brightness);
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetBlendBrightnessExt

  Description:  Changes brightness of plane1,
                and alpha blending on plane1 and plane2(MAIN engine).

  Arguments:    plane1       a set of planes
                plane2       a set of planes
                ev1          coefficient of plane1's color(0 to 16)
                ev2          coefficient of plane1's color(0 to 16)
                brightness   change of brightness(-16 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetBlendBrightnessExt(int plane1,
                                            int plane2, int ev1, int ev2, int brightness)
{
    G2x_SetBlendBrightnessExt_((u32)&reg_G2_BLDCNT, plane1, plane2, ev1, ev2, brightness);
}


/*---------------------------------------------------------------------------*
  Name:         G2_ChangeBlendBrightness

  Description:  Change brightness parameter only(MAIN engine).

  Arguments:    brightness   change of brightness(-16 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_ChangeBlendBrightness(int brightness)
{
    G2x_ChangeBlendBrightness_((u32)&reg_G2_BLDCNT, brightness);
}



//----------------------------------------------------------------------------
//
// Display B(Sub Display)
//
//----------------------------------------------------------------------------
/*---------------------------------------------------------------------------*
  Name:         G2S_SetBG0Offset

  Description:  Set the BG0 screen offset

  Arguments:    hOffset    H-offset(in dot)
                vOffset    V-offset(in dot)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBG0Offset(int hOffset, int vOffset)
{
    reg_G2S_DB_BG0OFS =
        (u32)(((hOffset << REG_G2S_DB_BG0OFS_HOFFSET_SHIFT) & REG_G2S_DB_BG0OFS_HOFFSET_MASK) |
              ((vOffset << REG_G2S_DB_BG0OFS_VOFFSET_SHIFT) & REG_G2S_DB_BG0OFS_VOFFSET_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBG1Offset

  Description:  Set the BG1 screen offset

  Arguments:    hOffset    H-offset(in dot)
                vOffset    V-offset(in dot)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBG1Offset(int hOffset, int vOffset)
{
    reg_G2S_DB_BG1OFS =
        (u32)(((hOffset << REG_G2S_DB_BG1OFS_HOFFSET_SHIFT) & REG_G2S_DB_BG1OFS_HOFFSET_MASK) |
              ((vOffset << REG_G2S_DB_BG1OFS_VOFFSET_SHIFT) & REG_G2S_DB_BG1OFS_VOFFSET_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBG2Offset

  Description:  Set the BG2 screen offset

  Arguments:    hOffset    H-offset(in dot)
                vOffset    V-offset(in dot)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBG2Offset(int hOffset, int vOffset)
{
#ifdef SDK_DEBUG
    {
        u32     tmp =
            (reg_GXS_DB_DISPCNT & REG_GXS_DB_DISPCNT_BGMODE_MASK) >>
            REG_GXS_DB_DISPCNT_BGMODE_SHIFT;
        SDK_WARNING((0 == tmp) || (1 == tmp)
                    || (3 == tmp),
                    "G2S_SetBG2Offset requires BG #2 to be text mode. Use G2S_SetBG2Affine instead.");
    }
#endif

    reg_G2S_DB_BG2OFS =
        (u32)(((hOffset << REG_G2S_DB_BG2OFS_HOFFSET_SHIFT) & REG_G2S_DB_BG2OFS_HOFFSET_MASK) |
              ((vOffset << REG_G2S_DB_BG2OFS_VOFFSET_SHIFT) & REG_G2S_DB_BG2OFS_VOFFSET_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBG3Offset

  Description:  Set the BG3 screen offset

  Arguments:    hOffset    H-offset(in dot)
                vOffset    V-offset(in dot)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBG3Offset(int hOffset, int vOffset)
{
#ifdef SDK_DEBUG
    {
        u32     tmp =
            (reg_GXS_DB_DISPCNT & REG_GXS_DB_DISPCNT_BGMODE_MASK) >>
            REG_GXS_DB_DISPCNT_BGMODE_SHIFT;
        SDK_WARNING(0 == tmp,
                    "G2S_SetBG3Offset requires BG #3 to be text mode. Use G2S_SetBG3Affine instead.");
    }
#endif

    reg_G2S_DB_BG3OFS =
        (u32)(((hOffset << REG_G2S_DB_BG3OFS_HOFFSET_SHIFT) & REG_G2S_DB_BG3OFS_HOFFSET_MASK) |
              ((vOffset << REG_G2S_DB_BG3OFS_VOFFSET_SHIFT) & REG_G2S_DB_BG3OFS_VOFFSET_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetWnd0InsidePlane

  Description:  Select the planes inside the Window #0

  Arguments:    wnd      Set of the planes inside the Window #0
                effect   enable/disable blending/brightness effect

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetWnd0InsidePlane(int wnd, BOOL effect)
{
    u32     tmp;
    GX_WND_PLANEMASK_ASSERT(wnd);

    tmp = ((reg_G2S_DB_WININ & ~REG_G2S_DB_WININ_WIN0IN_MASK) |
           ((u32)wnd << REG_G2S_DB_WININ_WIN0IN_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2S_DB_WININ_WIN0IN_SHIFT); // EFCT
    }

    reg_G2S_DB_WININ = (u16)tmp;
}


/*---------------------------------------------------------------------------*
  Name:         G2S_GetWnd0InsidePlane

  Description:  Get the planes inside the Window #0(SUB engine).

  Arguments:    none.
  
  Returns:      structure of the plane mask and effect flag;
 *---------------------------------------------------------------------------*/
static inline GXWndPlane G2S_GetWnd0InsidePlane(void)
{
    return *(const GXWndPlane *)(REG_DB_WININ_ADDR);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetWnd1InsidePlane

  Description:  Select the planes inside the Window #1

  Arguments:    wnd      Set of the planes inside the Window #1
                effect   enable/disable blending/brightness effect

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetWnd1InsidePlane(int wnd, BOOL effect)
{
    u32     tmp;
    GX_WND_PLANEMASK_ASSERT(wnd);

    tmp = ((reg_G2S_DB_WININ & ~REG_G2S_DB_WININ_WIN1IN_MASK) |
           ((u32)wnd << REG_G2S_DB_WININ_WIN1IN_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2S_DB_WININ_WIN1IN_SHIFT); // EFCT
    }

    reg_G2S_DB_WININ = (u16)tmp;
}


/*---------------------------------------------------------------------------*
  Name:         G2S_GetWnd1InsidePlane

  Description:  Get the planes inside the Window #1(SUB engine).

  Arguments:    none.
  
  Returns:      structure of the plane mask and effect flag;
 *---------------------------------------------------------------------------*/
static inline GXWndPlane G2S_GetWnd1InsidePlane(void)
{
    return *(const GXWndPlane *)(REG_DB_WININ_ADDR + 1);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetWndOutsidePlane

  Description:  Select the planes outside the Window #0, #1, OBJ

  Arguments:    wnd      Set of the planes outside the windows
                effect   enable/disable blending/brightness effect

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetWndOutsidePlane(int wnd, BOOL effect)
{
    u32     tmp;
    GX_WND_PLANEMASK_ASSERT(wnd);

    tmp = ((reg_G2S_DB_WINOUT & ~REG_G2S_DB_WINOUT_WINOUT_MASK) |
           ((u32)wnd << REG_G2S_DB_WINOUT_WINOUT_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2S_DB_WINOUT_WINOUT_SHIFT);        // EFCT
    }

    reg_G2S_DB_WINOUT = (u16)tmp;
}


/*---------------------------------------------------------------------------*
  Name:         G2S_GetWndOutsidePlane

  Description:  Get the planes outside the Window(SUB engine).

  Arguments:    none.
  
  Returns:      structure of the plane mask and effect flag;
 *---------------------------------------------------------------------------*/
static inline GXWndPlane G2S_GetWndOutsidePlane(void)
{
    return *(const GXWndPlane *)(REG_DB_WINOUT_ADDR);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetWndOBJInsidePlane

  Description:  Select the planes inside the OBJ window

  Arguments:    wnd      Set of the planes inside the OBJ window

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetWndOBJInsidePlane(int wnd, BOOL effect)
{
    u32     tmp;
    GX_WND_PLANEMASK_ASSERT(wnd);

    tmp = ((reg_G2S_DB_WINOUT & ~REG_G2S_DB_WINOUT_OBJWININ_MASK) |
           ((u32)wnd << REG_G2S_DB_WINOUT_OBJWININ_SHIFT));

    if (effect)
    {
        tmp |= (0x20 << REG_G2S_DB_WINOUT_OBJWININ_SHIFT);      // EFCT
    }

    reg_G2S_DB_WINOUT = (u16)tmp;
}


/*---------------------------------------------------------------------------*
  Name:         G2S_GetWndOBJInsidePlane

  Description:  Get the planes inside the OBJ Window(SUB engine).

  Arguments:    none.
  
  Returns:      structure of the plane mask and effect flag;
 *---------------------------------------------------------------------------*/
static inline GXWndPlane G2S_GetWndOBJInsidePlane(void)
{
    return *(const GXWndPlane *)(REG_DB_WINOUT_ADDR + 1);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetWnd0Position

  Description:  Specify the position of the Window #0

  Arguments:    x1        X coordinate of the upper left of the window
                y1        Y coordinate of the upper left of the window
                x2        X coordinate of the lower right of the window
                y2        Y coordinate of the lower right of the window

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetWnd0Position(int x1, int y1, int x2, int y2)
{
    SDK_MINMAX_ASSERT(y1, 0, 192);
    SDK_MINMAX_ASSERT(y2, 0, 192);

    // Note that the addresses of reg_G2S_DB_WIN0H and reg_G2S_DB_WIN0V are separate.
    reg_G2S_DB_WIN0H = (u16)(((x1 << REG_G2S_DB_WIN0H_LEFTX_SHIFT) & REG_G2S_DB_WIN0H_LEFTX_MASK) |
                             ((x2 << REG_G2S_DB_WIN0H_RIGHTX_SHIFT) &
                              REG_G2S_DB_WIN0H_RIGHTX_MASK));

    reg_G2S_DB_WIN0V = (u16)(((y1 << REG_G2S_DB_WIN0V_UPY_SHIFT) & REG_G2S_DB_WIN0V_UPY_MASK) |
                             ((y2 << REG_G2S_DB_WIN0V_DOWNY_SHIFT) & REG_G2S_DB_WIN0V_DOWNY_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetWnd1Position

  Description:  Specify the position of the Window #1

  Arguments:    x1        X coordinate of the upper left of the window
                y1        Y coordinate of the upper left of the window
                x2        X coordinate of the lower right of the window
                y2        Y coordinate of the lower right of the window

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetWnd1Position(int x1, int y1, int x2, int y2)
{
    SDK_MINMAX_ASSERT(y1, 0, 192);
    SDK_MINMAX_ASSERT(y2, 0, 192);

    // Note that the addresses of reg_G2S_DB_WIN1H and reg_G2S_DB_WIN1V are separate.
    reg_G2S_DB_WIN1H = (u16)(((x1 << REG_G2S_DB_WIN1H_LEFTX_SHIFT) & REG_G2S_DB_WIN1H_LEFTX_MASK) |
                             ((x2 << REG_G2S_DB_WIN1H_RIGHTX_SHIFT) &
                              REG_G2S_DB_WIN1H_RIGHTX_MASK));

    reg_G2S_DB_WIN1V = (u16)(((y1 << REG_G2S_DB_WIN1V_UPY_SHIFT) & REG_G2S_DB_WIN1V_UPY_MASK) |
                             ((y2 << REG_G2S_DB_WIN1V_DOWNY_SHIFT) & REG_G2S_DB_WIN1V_DOWNY_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBGMosaicSize

  Description:  Specify the size of the mosaic applied on BGs

  Arguments:    hSize     the size of the mosaic in horizontal direction
                vSize     the size of the mosaic in vertical direction

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBGMosaicSize(int hSize, int vSize)
{
    GX_MOSAICSIZE_ASSERT(hSize);
    GX_MOSAICSIZE_ASSERT(vSize);

    *((vu8 *)REG_DB_MOSAIC_ADDR) = (u8)((hSize << REG_G2S_DB_MOSAIC_BGHSIZE_SHIFT) |
                                        (vSize << REG_G2S_DB_MOSAIC_BGVSIZE_SHIFT));

}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetOBJMosaicSize

  Description:  Specify the size of the mosaic applied on OBJs

  Arguments:    hSize     the size of the mosaic in horizontal direction
                vSize     the size of the mosaic in vertical direction

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetOBJMosaicSize(int hSize, int vSize)
{
    GX_MOSAICSIZE_ASSERT(hSize);
    GX_MOSAICSIZE_ASSERT(vSize);

    *((vu8 *)(REG_DB_MOSAIC_ADDR + 1)) = (u8)((hSize << (REG_G2S_DB_MOSAIC_OBJHSIZE_SHIFT - 8)) |
                                              (vSize << (REG_G2S_DB_MOSAIC_OBJVSIZE_SHIFT - 8)));

}


/*---------------------------------------------------------------------------*
  Name:         G2S_BlendNone

  Description:  No Blendings between the planes

  Arguments:    none

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_BlendNone()
{
    reg_G2S_DB_BLDCNT = 0;
}


/*---------------------------------------------------------------------------*
  Name:         G2S_ChangeBlendAlpha

  Description:  Set blending coefficients directly

  Arguments:    ev1     blending coefficient1
                ev2     blending coefficient2

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_ChangeBlendAlpha(int ev1, int ev2)
{
    GX_ALPHA_ASSERT(ev1);
    GX_ALPHA_ASSERT(ev2);

    reg_G2S_DB_BLDALPHA = (u16)((ev1 << REG_G2S_DB_BLDALPHA_EVA_SHIFT) |
                                (ev2 << REG_G2S_DB_BLDALPHA_EVB_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBG2Affine

  Description:  Affine transform on BG2(SUB engine).

  Arguments:    mtx          a pointer to a matrix
                centerX      center of rotation
                centerY      center of rotation
                x1           the upper left point before rotation
                y1           the upper left point before rotation

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBG2Affine(const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1)
{
    G2x_SetBGyAffine_((u32)&reg_G2S_DB_BG2PA, mtx, centerX, centerY, x1, y1);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBG3Affine

  Description:  Affine transform on BG3(SUB engine).

  Arguments:    mtx          a pointer to a matrix
                centerX      center of rotation
                centerY      center of rotation
                x1           the upper left point before rotation
                y1           the upper left point before rotation

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBG3Affine(const MtxFx22 *mtx, int centerX, int centerY, int x1, int y1)
{
    G2x_SetBGyAffine_((u32)&reg_G2S_DB_BG3PA, mtx, centerX, centerY, x1, y1);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBlendAlpha

  Description:  Alpha blending on plane1 and plane2(SUB engine).

  Arguments:    plane1       a set of planes
                plane2       a set of planes
                ev1          coefficient of plane1's color(0 to 16)
                ev2          coefficient of plane2's color(0 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBlendAlpha(int plane1, int plane2, int ev1, int ev2)
{
    G2x_SetBlendAlpha_((u32)&reg_G2S_DB_BLDCNT, plane1, plane2, ev1, ev2);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBlendBrightness

  Description:  Changes brightness of plane(SUB engine).

  Arguments:    plane        a set of planes
                brightness   change of brightness(-16 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBlendBrightness(int plane, int brightness)
{
    G2x_SetBlendBrightness_((u32)&reg_G2S_DB_BLDCNT, plane, brightness);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_SetBlendBrightnessExt

  Description:  Changes brightness of plane1,
                and alpha blending on plane1 and plane2(SUB engine).

  Arguments:    plane1       a set of planes
                plane2       a set of planes
                ev1          coefficient of plane1's color(0 to 16)
                ev2          coefficient of plane1's color(0 to 16)
                brightness   change of brightness(-16 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_SetBlendBrightnessExt(int plane1,
                                             int plane2, int ev1, int ev2, int brightness)
{
    G2x_SetBlendBrightnessExt_((u32)&reg_G2S_DB_BLDCNT, plane1, plane2, ev1, ev2, brightness);
}


/*---------------------------------------------------------------------------*
  Name:         G2S_ChangeBlendBrightness

  Description:  Change brightness parameter only(SUB engine).

  Arguments:    brightness   change of brightness(-16 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2S_ChangeBlendBrightness(int brightness)
{
    G2x_ChangeBlendBrightness_((u32)&reg_G2S_DB_BLDCNT, brightness);
}



#endif // SDK_FROM_TOOL


#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_G2_H_ */
#endif
