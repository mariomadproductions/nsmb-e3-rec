/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FX -
  File:     fx_mtx33.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fx_mtx33.h,v $
  Revision 1.19  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.18  2005/11/14 05:10:03  okubata_ryoma
  Added support for SDK_INLINE

  Revision 1.17  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.16  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.15  2004/02/12 01:36:02  nishida_kenji
  Work around to optimization of simple matrix functions.

  Revision 1.14  2004/02/10 06:39:45  nishida_kenji
  Add MTX_Copy33.

  Revision 1.13  2004/02/10 06:31:49  nishida_kenji
  Work around to optimization of simple matrix functions.

  Revision 1.12  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.11  2004/01/17 07:17:21  nishida_kenji
  remove external include guards

  Revision 1.10  2004/01/17 07:06:41  nishida_kenji
  add MTX_MultVec33

  Revision 1.9  2003/12/11 09:18:24  nishida_kenji
  fix comments

  Revision 1.8  2003/12/11 06:19:59  nishida_kenji
  (none)

  Revision 1.7  2003/12/11 06:12:50  nishida_kenji
  add MTX_Concat

  Revision 1.6  2003/12/09 11:26:54  nishida_kenji
  improve asserts and comments

  Revision 1.5  2003/12/04 07:31:50  nishida_kenji
  MTX_Inverse33, MTX_Inverse43

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_FX_MTX33_H_
#define NITRO_FX_MTX33_H_

#include "nitro/fx/fx.h"
#include "nitro/fx/fx_vec.h"
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

SDK_DECL_INLINE void MTX_Identity33(MtxFx33 *pDst);
SDK_DECL_INLINE void MTX_Copy33(const MtxFx33 *pSrc, MtxFx33 *pDst);
SDK_DECL_INLINE void MTX_Copy33To43(const MtxFx33 *pSrc, MtxFx43 *pDst);
SDK_DECL_INLINE void MTX_Copy33To44(const MtxFx33 *pSrc, MtxFx44 *pDst);
SDK_DECL_INLINE void MTX_Transpose33(const MtxFx33 *pSrc, MtxFx33 *pDst);
SDK_DECL_INLINE void MTX_Scale33(MtxFx33 *pDst, fx32 x, fx32 y, fx32 z);
void    MTX_ScaleApply33(const MtxFx33 *pSrc, MtxFx33 *pDst, fx32 x, fx32 y, fx32 z);
SDK_DECL_INLINE void MTX_RotX33(MtxFx33 *pDst, fx32 sinVal, fx32 cosVal);
SDK_DECL_INLINE void MTX_RotY33(MtxFx33 *pDst, fx32 sinVal, fx32 cosVal);
SDK_DECL_INLINE void MTX_RotZ33(MtxFx33 *pDst, fx32 sinVal, fx32 cosVal);
void    MTX_RotAxis33(MtxFx33 *pDst, const VecFx32 *vec, fx32 sinVal, fx32 cosVal);
int     MTX_Inverse33(const MtxFx33 *pSrc, MtxFx33 *pDst);
void    MTX_Concat33(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
void    MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);

void    MTX_Identity33_(register MtxFx33 *pDst);
void    MTX_Copy33To43_(const register MtxFx33 *pSrc, register MtxFx43 *pDst);
void    MTX_Copy33To44_(const register MtxFx33 *pSrc, register MtxFx44 *pDst);
void    MTX_Transpose33_(const register MtxFx33 *pSrc, register MtxFx33 *pDst);
void    MTX_Scale33_(register MtxFx33 *pDst, register fx32 x, register fx32 y, register fx32 z);
void    MTX_RotX33_(register MtxFx33 *pDst, register fx32 sinVal, register fx32 cosVal);
void    MTX_RotY33_(register MtxFx33 *pDst, register fx32 sinVal, register fx32 cosVal);
void    MTX_RotZ33_(register MtxFx33 *pDst, register fx32 sinVal, register fx32 cosVal);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         MTX_Identity33

  Description:  Sets a matrix to identity.

  Arguments:    pDst         a pointer to a 3x3 matrix

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Identity33(MtxFx33 *pDst)
{
    SDK_NULL_ASSERT(pDst);
    MTX_Identity33_(pDst);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_Copy33

  Description:  Copies a 3x3 matrix to a 3x3 matrix.

  Arguments:    pSrc         a pointer to a 3x3 matrix
                pDst         a pointer to a 3x3 matrix

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Copy33(const MtxFx33 *pSrc, MtxFx33 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);
    MI_Copy36B(pSrc, pDst);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_Copy33To43

  Description:  Copies a 3x3 matrix to a 4x3 matrix.

  Arguments:    pSrc         a pointer to a 3x3 matrix
                pDst         a pointer to a 4x3 matrix

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Copy33To43(const MtxFx33 *pSrc, MtxFx43 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);
    MTX_Copy33To43_(pSrc, pDst);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Copy33To44

  Description:  Copies a 3x3 matrix to a 4x4 matrix.

  Arguments:    pSrc         a pointer to a 3x3 matrix
                pDst         a pointer to a 4x4 matrix

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Copy33To44(const MtxFx33 *pSrc, MtxFx44 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);
    MTX_Copy33To44_(pSrc, pDst);
}


/*---------------------------------------------------------------------------*
  Name:         MTX_Transpose33

  Description:  Computes the transpose of a 3x3 matrix.

  Arguments:    pSrc         a pointer to a 3x3 matrix
                pDst         a pointer to a 3x3 matrix

  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Transpose33(const MtxFx33 *pSrc, MtxFx33 *pDst)
{
    SDK_NULL_ASSERT(pSrc);
    SDK_NULL_ASSERT(pDst);
    MTX_Transpose33_(pSrc, pDst);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_Scale33

  Description:  Sets a scaling matrix.

  Arguments:    pDst         a pointer to a 3x3 matrix
                x            x scale factor
                y            y scale factor
                z            z scale factor
  
  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_Scale33(MtxFx33 *pDst, fx32 x, fx32 y, fx32 z)
{
    SDK_NULL_ASSERT(pDst);
    MTX_Scale33_(pDst, x, y, z);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_RotX33

  Description:  Sets a rotation matrix about the X axis.

  Arguments:    pDst         a pointer to a 3x3 matrix
                sinVal       sine of an angle of rotation
                cosVal       cosine of an angle of rotation
  
  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_RotX33(MtxFx33 *pDst, fx32 sinVal, fx32 cosVal)
{
    SDK_NULL_ASSERT(pDst);
    MTX_RotX33_(pDst, sinVal, cosVal);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_RotY33

  Description:  Sets a rotation matrix about the Y axis.

  Arguments:    pDst         a pointer to a 3x3 matrix
                sinVal       sine of an angle of rotation
                cosVal       cosine of an angle of rotation
  
  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_RotY33(MtxFx33 *pDst, fx32 sinVal, fx32 cosVal)
{
    SDK_NULL_ASSERT(pDst);
    MTX_RotY33_(pDst, sinVal, cosVal);
}

/*---------------------------------------------------------------------------*
  Name:         MTX_RotZ33

  Description:  Sets a rotation matrix about the Z axis.

  Arguments:    pDst         a pointer to a 3x3 matrix
                sinVal       sine of an angle of rotation
                cosVal       cosine of an angle of rotation
  
  Returns:      none
 *---------------------------------------------------------------------------*/
SDK_INLINE void MTX_RotZ33(MtxFx33 *pDst, fx32 sinVal, fx32 cosVal)
{
    SDK_NULL_ASSERT(pDst);
    MTX_RotZ33_(pDst, sinVal, cosVal);
}



#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
