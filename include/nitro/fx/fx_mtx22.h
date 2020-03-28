/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FX -
  File:     fx_mtx22.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fx_mtx22.h,v $
  Revision 1.9  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.8  2005/11/14 05:10:03  okubata_ryoma
  Added support for SDK_INLINE

  Revision 1.7  2005/03/03 13:08:04  takano_makoto
  Removed unneeded asm notation

  Revision 1.6  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.5  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.4  2004/05/17 09:22:42  takano_makoto
  Add FX_Scale22() and FX_ScaleApply22().

  Revision 1.3  2004/04/15 06:20:34  takano_makoto
  fix a head define statement.

  Revision 1.2  2004/04/15 06:03:55  takano_makoto
  Fix MTX_Rot22

  Revision 1.1  2004/04/15 05:57:49  takano_makoto
  Initial Upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_FX_MTX22_H_
#define NITRO_FX_MTX22_H_

#include "nitro/fx/fx.h"
#include "nitro/mi/memory.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

SDK_DECL_INLINE void MTX_Identity22(MtxFx22 *pDst);
SDK_DECL_INLINE void MTX_Copy22(const MtxFx22 *pSrc, MtxFx22 *pDst);
SDK_DECL_INLINE void MTX_Transpose22(const MtxFx22 *pSrc, MtxFx22 *pDst);
SDK_DECL_INLINE void MTX_Rot22(MtxFx22 *pDst, fx32 sinVal, fx32 cosVal);
int     MTX_Inverse22(const MtxFx22 *pSrc, MtxFx22 *pDst);
void    MTX_Concat22(const MtxFx22 *a, const MtxFx22 *b, MtxFx22 *ab);
void    MTX_ScaleApply22(const MtxFx22 *pSrc, MtxFx22 *pDst, fx32 x, fx32 y);

void    MTX_Identity22_(register MtxFx22 *pDst);
void    MTX_Transpose22_(const register MtxFx22 *pSrc, register MtxFx22 *pDst);
void    MTX_Scale22_(register MtxFx22 *pDst, register fx32 x, register fx32 y);
void    MTX_Rot22_(register MtxFx22 *pDst, register fx32 sinVal, register fx32 cosVal);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         MTX_Identity22

  Description:  Sets a matrix to identity.

  Arguments:    pDst         a pointer to a 2x2 matrix

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Identity22(MtxFx22 *pDst)
{
    SDK_NULL_ASSERT(pDst);
    MTX_Identity22_(pDst);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_Copy22

  Description:  Copies a 2x2 matrix to a 2x2 matrix.

  Arguments:    pSrc         a pointer to a 2x2 matrix
                pDst         a pointer to a 2x2 matrix

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Copy22(const MtxFx22 *pSrc, MtxFx22 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);
    MI_Copy16B(pSrc, pDst);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Transpose22

  Description:  Computes the transpose of a 2x2 matrix.

  Arguments:    pSrc         a pointer to a 2x2 matrix
                pDst         a pointer to a 2x2 matrix

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Transpose22(const MtxFx22 *pSrc, MtxFx22 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);
    MTX_Transpose22_(pSrc, pDst);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Scale22

  Description:  Sets a scaling matrix.

  Arguments:    pDst         a pointer to a 2x2 matrix
                x            x scale factor
                y            y scale factor
  
  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Scale22(MtxFx22 *pDst, fx32 x, fx32 y)
{
    SDK_NULL_ASSERT(pDst);
    MTX_Scale22_(pDst, x, y);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Rot22

  Description:  Sets a rotation matrix.

  Arguments:    pDst         a pointer to a 2x2 matrix
                sinVal       sine of an angle of rotation
                cosVal       cosine of an angle of rotation
  
  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Rot22(MtxFx22 *pDst, fx32 sinVal, fx32 cosVal)
{
    SDK_NULL_ASSERT(pDst);
    MTX_Rot22_(pDst, sinVal, cosVal);
}


#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
