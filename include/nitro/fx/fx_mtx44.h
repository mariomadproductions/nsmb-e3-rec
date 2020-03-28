/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FX - 
  File:     fx_mtx44.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fx_mtx44.h,v $
  Revision 1.21  2007/07/30 02:11:29  yosizaki
  Fix related to headerfiles.

  Revision 1.20  2007/05/14 00:29:04  yosizaki
  Removed references to GX

  Revision 1.19  2007/04/24 04:27:47  yosizaki
  Added instances of projection-matrix functions.

  Revision 1.18  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.17  2005/11/14 05:10:03  okubata_ryoma
  Added support for SDK_INLINE

  Revision 1.16  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.15  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.14  2004/06/21 10:31:41  takano_makoto
  Added MTX_PerspectiveW(), MTX_FrustumW(), MTX_OrthoW().

  Revision 1.13  2004/04/27 01:17:11  takano_makoto
  Added MTX_Frustum, MTX_Perspective, MTX_Ortho.

  Revision 1.12  2004/02/12 01:36:02  nishida_kenji
  Workaround to optimize simple matrix functions.

  Revision 1.11  2004/02/10 08:39:02  nishida_kenji
  Workaround to optimize simple matrix functions.

  Revision 1.10  2004/02/10 06:04:22  nishida_kenji
  Added MTX_TransApply44.

  Revision 1.9  2004/02/05 07:09:03  yasu
  Changed SDK prefix iris -> nitro

  Revision 1.8  2004/01/17 07:17:21  nishida_kenji
  Removed external include guards

  Revision 1.7  2003/12/11 09:18:24  nishida_kenji
  Fixed comments

  Revision 1.6  2003/12/11 06:20:31  nishida_kenji
  (none)

  Revision 1.5  2003/12/11 06:12:50  nishida_kenji
  Added MTX_Concat

  Revision 1.4  2003/12/09 11:26:54  nishida_kenji
  Improved asserts and comments

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_FX_MTX44_H_
#define NITRO_FX_MTX44_H_

#include "nitro/fx/fx.h"
#include "nitro/fx/fx_const.h"
#include "nitro/mi/memory.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type Definitions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Function Declarations
//----------------------------------------------------------------------------

SDK_DECL_INLINE void MTX_Identity44(MtxFx44 *pDst);
SDK_DECL_INLINE void MTX_Copy44To33(const MtxFx44 *pSrc, MtxFx33 *pDst);
SDK_DECL_INLINE void MTX_Copy44To43(const MtxFx44 *pSrc, MtxFx43 *pDst);
SDK_DECL_INLINE void MTX_Transpose44(const MtxFx44 *pSrc, MtxFx44 *pDst);
void    MTX_TransApply44(const MtxFx44 *pSrc, MtxFx44 *pDst, fx32 x, fx32 y, fx32 z);
SDK_DECL_INLINE void MTX_Scale44(MtxFx44 *pDst, fx32 x, fx32 y, fx32 z);
void    MTX_ScaleApply44(const MtxFx44 *pSrc, MtxFx44 *pDst, fx32 x, fx32 y, fx32 z);
SDK_DECL_INLINE void MTX_RotX44(MtxFx44 *pDst, fx32 sinVal, fx32 cosVal);
SDK_DECL_INLINE void MTX_RotY44(MtxFx44 *pDst, fx32 sinVal, fx32 cosVal);
SDK_DECL_INLINE void MTX_RotZ44(MtxFx44 *pDst, fx32 sinVal, fx32 cosVal);
void    MTX_RotAxis44(MtxFx44 *pDst, const VecFx32 *vec, fx32 sinVal, fx32 cosVal);
void    MTX_Concat44(const MtxFx44 *a, const MtxFx44 *b, MtxFx44 *ab);
void    MTX_FrustumW(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, fx32 scaleW, MtxFx44 *mtx);
void    MTX_PerspectiveW(fx32 fovySin, fx32 fovyCos, fx32 aspect, fx32 n, fx32 f, fx32 scaleW, MtxFx44 *mtx);
void    MTX_OrthoW(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, fx32 scaleW, MtxFx44 *mtx);

void    MTX_Identity44_(register MtxFx44 *pDst);
void    MTX_Copy44To33_(register const MtxFx44 *pSrc, register MtxFx33 *pDst);
void    MTX_Copy44To43_(register const MtxFx44 *pSrc, register MtxFx43 *pDst);
void    MTX_Transpose44_(register const MtxFx44 *pSrc, register MtxFx44 *pDst);
void    MTX_Scale44_(register MtxFx44 *pDst, register fx32 x, register fx32 y, register fx32 z);
void    MTX_RotX44_(register MtxFx44 *pDst, register fx32 sinVal, register fx32 cosVal);
void    MTX_RotY44_(register MtxFx44 *pDst, register fx32 sinVal, register fx32 cosVal);
void    MTX_RotZ44_(register MtxFx44 *pDst, register fx32 sinVal, register fx32 cosVal);



//----------------------------------------------------------------------------
// Inline Function Implementation
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         MTX_Identity44

  Description:  Sets a matrix to identity.

  Arguments:    pDst         a pointer to a 4x4 matrix

  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Identity44(MtxFx44 *pDst)
{
    SDK_NULL_ASSERT(pDst);
    MTX_Identity44_(pDst);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_Copy44

  Description:  Copies a 4x4 matrix to a 4x4 matrix.

  Arguments:    pSrc         a pointer to a 4x4 matrix
                pDst         a pointer to a 4x4 matrix

  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Copy44(const MtxFx44 *pSrc, MtxFx44 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);

    MI_Copy64B(pSrc, pDst);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Copy44To33

  Description:  Copies a 4x4 matrix to a 3x3 matrix.

  Arguments:    pSrc         a pointer to a 4x4 matrix
                pDst         a pointer to a 3x3 matrix

  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Copy44To33(const MtxFx44 *pSrc, MtxFx33 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);

    MTX_Copy44To33_(pSrc, pDst);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Copy44To43

  Description:  Copies a 4x4 matrix to a 4x3 matrix.

  Arguments:    pSrc         a pointer to a 4x4 matrix
                pDst         a pointer to a 4x3 matrix

  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Copy44To43(const MtxFx44 *pSrc, MtxFx43 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);

    MTX_Copy44To43_(pSrc, pDst);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_Transpose44

  Description:  Computes the transpose of a 4x4 matrix.

  Arguments:    pSrc         a pointer to a 4x4 matrix
                pDst         a pointer to a 4x4 matrix

  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Transpose44(const MtxFx44 *pSrc, MtxFx44 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);

    MTX_Transpose44_(pSrc, pDst);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_Scale44

  Description:  Sets a scaling matrix.

  Arguments:    pDst         a pointer to a 4x4 matrix
                x            x scale factor
                y            y scale factor
                z            z scale factor
  
  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Scale44(MtxFx44 *pDst, fx32 x, fx32 y, fx32 z)
{
    SDK_NULL_ASSERT(pDst);
    MTX_Scale44_(pDst, x, y, z);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_RotX44

  Description:  Sets a rotation matrix about the x-axis.

  Arguments:    pDst         a pointer to a 4x4 matrix
                sinVal       sine of an angle of rotation
                cosVal       cosine of an angle of rotation
  
  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_RotX44(MtxFx44 *pDst, fx32 sinVal, fx32 cosVal)
{
    SDK_NULL_ASSERT(pDst);
    MTX_RotX44_(pDst, sinVal, cosVal);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_RotY44

  Description:  Sets a rotation matrix about the y-axis.

  Arguments:    pDst         a pointer to a 4x4 matrix
                sinVal       sine of an angle of rotation
                cosVal       cosine of an angle of rotation
  
  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_RotY44(MtxFx44 *pDst, fx32 sinVal, fx32 cosVal)
{
    SDK_NULL_ASSERT(pDst);
    MTX_RotY44_(pDst, sinVal, cosVal);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_RotZ44

  Description:  Sets a rotation matrix about the z-axis.

  Arguments:    pDst         a pointer to a 4x4 matrix
                sinVal       sine of an angle of rotation
                cosVal       cosine of an angle of rotation
  
  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_RotZ44(MtxFx44 *pDst, fx32 sinVal, fx32 cosVal)
{
    SDK_NULL_ASSERT(pDst);
    MTX_RotZ44_(pDst, sinVal, cosVal);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Frustum

  Description:  Computes a 4x4 perspective projection matrix from a specified
                view volume.

  Arguments:    t            top coordinate of view volume at the near clipping plane
                b            bottom coordinate of view volume at the near clipping plane
                l            left coordinate of view volume at near clipping plane
                r            right coordinate of view volume at near clipping plane
                n            positive distance from camera to near clipping plane
                f            positive distance from camera to far clipping plane
                mtx          4x4 matrix to be set

  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Frustum(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, MtxFx44 *mtx)
{
    MTX_FrustumW(t, b, l, r, n, f, FX32_ONE, mtx);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Perspective

  Description:  Computes a 4x4 perspective projection matrix from field of
                view and aspect ratio.

  Arguments:    fovySin      sine value of fovy
                fovyCos      cosine value of fovy
                aspect       ratio of view window width:height (X / Y)
                n            positive distance from camera to near clipping plane
                f            positive distance from camera to far clipping plane
                mtx          4x4 matrix to be set

  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE
    void MTX_Perspective(fx32 fovySin, fx32 fovyCos, fx32 aspect, fx32 n, fx32 f, MtxFx44 *mtx)
{
    MTX_PerspectiveW(fovySin, fovyCos, aspect, n, f, FX32_ONE, mtx);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Ortho

  Description:  Computes a 4x4 orthographic projection matrix.

  Arguments:    t            top coordinate of parallel view volume
                b            bottom coordinate of parallel view volume
                l            left coordinate of parallel view volume
                r            right coordinate of parallel view volume
                n            positive distance from camera to near clipping plane
                f            positive distance from camera to far clipping plane
                mtx          4x4 matrix to be set if not NULL

  Returns:      None
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Ortho(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f, MtxFx44 *mtx)
{
    MTX_OrthoW(t, b, l, r, n, f, FX32_ONE, mtx);
}


#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
