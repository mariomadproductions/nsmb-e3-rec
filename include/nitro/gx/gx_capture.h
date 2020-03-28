/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     gx_capture.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: gx_capture.h,v $
  Revision 1.24  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.23  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.22  2005/01/11 07:53:17  takano_makoto
  fix copyright header.

  Revision 1.21  2005/01/05 06:30:15  takano_makoto
  Added GX_ResetCapture function

  Revision 1.20  2004/05/14 11:52:57  takano_makoto
  Add #ifndef SDK_FROM_TOOL for VC or BCB.

  Revision 1.19  2004/02/17 08:12:26  nishida_kenji
  small fix.

  Revision 1.18  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.17  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.16  2004/01/27 11:13:58  nishida_kenji
  append 'static' to inline function prototypes.

  Revision 1.15  2004/01/19 07:22:49  nishida_kenji
  add comments

  Revision 1.14  2004/01/17 07:17:12  nishida_kenji
  remove external include guards

  Revision 1.13  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.12  2003/12/25 11:00:10  nishida_kenji
  converted by GX_APIChangeFrom031212-2.pl

  Revision 1.11  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.10  2003/12/24 12:07:39  nishida_kenji
  minor fix

  Revision 1.9  2003/12/17 09:00:21  nishida_kenji
  Totally revised APIs.
  build/buildtools/GX_APIChangeFrom031212.pl would help you change your program to some extent.

  Revision 1.8  2003/12/17 08:50:33  nishida_kenji
  revise comments

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_GX_CAPTURE_H_
#define NITRO_GX_CAPTURE_H_

#include "nitro/gx/gxcommon.h"
#include "nitro/hw/ARM9/ioreg_GX.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//    Parameters for GX_SetCapture
//----------------------------------------------------------------------------
typedef enum
{
    GX_CAPTURE_DEST_VRAM_A_0x00000 = 0,
    GX_CAPTURE_DEST_VRAM_B_0x00000 = 1,
    GX_CAPTURE_DEST_VRAM_C_0x00000 = 2,
    GX_CAPTURE_DEST_VRAM_D_0x00000 = 3,

    GX_CAPTURE_DEST_VRAM_A_0x08000 = 4,
    GX_CAPTURE_DEST_VRAM_B_0x08000 = 5,
    GX_CAPTURE_DEST_VRAM_C_0x08000 = 6,
    GX_CAPTURE_DEST_VRAM_D_0x08000 = 7,

    GX_CAPTURE_DEST_VRAM_A_0x10000 = 8,
    GX_CAPTURE_DEST_VRAM_B_0x10000 = 9,
    GX_CAPTURE_DEST_VRAM_C_0x10000 = 10,
    GX_CAPTURE_DEST_VRAM_D_0x10000 = 11,

    GX_CAPTURE_DEST_VRAM_A_0x18000 = 12,
    GX_CAPTURE_DEST_VRAM_B_0x18000 = 13,
    GX_CAPTURE_DEST_VRAM_C_0x18000 = 14,
    GX_CAPTURE_DEST_VRAM_D_0x18000 = 15
}
GXCaptureDest;

#define GX_CAPTURE_DEST_ASSERT(x)                         \
    SDK_MINMAX_ASSERT(x, GX_CAPTURE_DEST_VRAM_A_0x00000, GX_CAPTURE_DEST_VRAM_D_0x18000)


typedef enum
{
    GX_CAPTURE_SIZE_128x128 = 0,
    GX_CAPTURE_SIZE_256x64 = 1,
    GX_CAPTURE_SIZE_256x128 = 2,
    GX_CAPTURE_SIZE_256x192 = 3
}
GXCaptureSize;

#define GX_CAPTURE_SIZE_ASSERT(x)                 \
    SDK_MINMAX_ASSERT(x, GX_CAPTURE_SIZE_128x128, GX_CAPTURE_SIZE_256x192)

typedef enum
{
    GX_CAPTURE_SRCA_2D3D = 0,
    GX_CAPTURE_SRCA_3D = 1
}
GXCaptureSrcA;

#define GX_CAPTURE_SRCA_ASSERT(x)              \
    SDK_MINMAX_ASSERT(x, GX_CAPTURE_SRCA_2D3D, GX_CAPTURE_SRCA_3D)

typedef enum
{
    GX_CAPTURE_SRCB_VRAM_0x00000 = 0,
    GX_CAPTURE_SRCB_MRAM = 1,
    GX_CAPTURE_SRCB_VRAM_0x08000 = 2,
    GX_CAPTURE_SRCB_VRAM_0x10000 = 4,
    GX_CAPTURE_SRCB_VRAM_0x18000 = 6
}
GXCaptureSrcB;

#define GX_CAPTURE_SRCB_ASSERT(x)                      \
    SDK_ASSERT( (x) == GX_CAPTURE_SRCB_VRAM_0x00000 || \
                (x) == GX_CAPTURE_SRCB_MRAM         || \
                (x) == GX_CAPTURE_SRCB_VRAM_0x08000 || \
                (x) == GX_CAPTURE_SRCB_VRAM_0x10000 || \
                (x) == GX_CAPTURE_SRCB_VRAM_0x18000 )

typedef enum
{
    GX_CAPTURE_MODE_A = 0,
    GX_CAPTURE_MODE_B = 1,
    GX_CAPTURE_MODE_AB = 2
}
GXCaptureMode;

#define GX_CAPTURE_MODE_ASSERT(x) SDK_MINMAX_ASSERT(x, GX_CAPTURE_MODE_A, GX_CAPTURE_MODE_AB)


/* if include from Other Environment for exsample VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

// DISPCAPCNT
static void GX_SetCapture(GXCaptureSize sz,
                          GXCaptureMode mode,
                          GXCaptureSrcA a, GXCaptureSrcB b, GXCaptureDest dest, int eva, int evb);


//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         GX_SetCapture

  Description:  Specify attributes for display capture

  Arguments:    sz        capture size
                mode      capture mode
                a         capture data src A
                b         capture data src B
                dest      capture data dest
                eva       blending ratio of src A
                evb       blending ratio of src B

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetCapture(GXCaptureSize sz,
                                 GXCaptureMode mode,
                                 GXCaptureSrcA a,
                                 GXCaptureSrcB b, GXCaptureDest dest, int eva, int evb)
{
    GX_CAPTURE_DEST_ASSERT(dest);
    GX_CAPTURE_SIZE_ASSERT(sz);
    GX_CAPTURE_SRCA_ASSERT(a);
    GX_CAPTURE_SRCB_ASSERT(b);
    GX_CAPTURE_MODE_ASSERT(mode);
    SDK_MINMAX_ASSERT(eva, 0, 16);
    SDK_MINMAX_ASSERT(evb, 0, 16);

    reg_GX_DISPCAPCNT = (REG_GX_DISPCAPCNT_E_MASK |
                         (mode << REG_GX_DISPCAPCNT_MOD_SHIFT) |
                         (b << REG_GX_DISPCAPCNT_SRCB_SHIFT) |
                         (a << REG_GX_DISPCAPCNT_SRCA_SHIFT) |
                         (sz << REG_GX_DISPCAPCNT_WSIZE_SHIFT) |
                         (dest << REG_GX_DISPCAPCNT_DEST_SHIFT) |
                         (evb << REG_GX_DISPCAPCNT_EVB_SHIFT) |
                         (eva << REG_GX_DISPCAPCNT_EVA_SHIFT));
}

/*---------------------------------------------------------------------------*
  Name:         GX_ResetCapture

  Description:  Reset display capture

  Arguments:    none

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_ResetCapture(void)
{
    reg_GX_DISPCAPCNT &= ~REG_GX_DISPCAPCNT_E_MASK;
}


#endif // SDK_FROM_TOOL

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
