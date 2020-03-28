/*---------------------------------------------------------------------------*
  Project:  NitroSDK - FX -
  File:     fx_vec.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fx_vec.h,v $
  Revision 1.22  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.21  2005/11/14 05:10:03  okubata_ryoma
  Added support for SDK_INLINE

  Revision 1.20  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.19  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.18  2004/06/09 04:18:00  takano_makoto
  Added VEC_Set() and VEC_Fx16Set

  Revision 1.17  2004/02/16 23:50:35  nishida_kenji
  Add VEC_Fx16Distance.

  Revision 1.16  2004/02/16 08:11:23  nishida_kenji
  Add VEC_MultAdd, VEC_MultSubtract, VEC_Distance.

  Revision 1.15  2004/02/16 02:45:47  nishida_kenji
  Add APIs for VecFx16.

  Revision 1.14  2004/02/12 11:21:26  nishida_kenji
  VEC_Add, VEC_Subtract in .c file.

  Revision 1.13  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.12  2004/01/27 11:15:10  nishida_kenji
  appends 'static' to inline function prototypes.

  Revision 1.11  2004/01/17 07:17:21  nishida_kenji
  remove external include guards

  Revision 1.10  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.9  2004/01/09 09:12:07  nishida_kenji
  fix comments

  Revision 1.8  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.7  2003/12/11 09:18:24  nishida_kenji
  fix comments

  Revision 1.6  2003/12/09 11:26:54  nishida_kenji
  improve asserts and comments
  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_FX_VEC_H_
#define NITRO_FX_VEC_H_

#include "nitro/fx/fx.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

void    VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
void    VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
fx32    VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
void    VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb);
fx32    VEC_Mag(const VecFx32 *v);
fx32    VEC_Distance(const VecFx32 *v1, const VecFx32 *v2);
void    VEC_Normalize(const VecFx32 *pSrc, VecFx32 *pDst);
void    VEC_MultAdd(fx32 a, const VecFx32 *v1, const VecFx32 *v2, VecFx32 *pDest);
void    VEC_MultSubtract(fx32 a, const VecFx32 *v1, const VecFx32 *v2, VecFx32 *pDest);


void    VEC_Fx16Add(const VecFx16 *a, const VecFx16 *b, VecFx16 *ab);
void    VEC_Fx16Subtract(const VecFx16 *a, const VecFx16 *b, VecFx16 *ab);
fx32    VEC_Fx16DotProduct(const VecFx16 *a, const VecFx16 *b);
void    VEC_Fx16CrossProduct(const VecFx16 *a, const VecFx16 *b, VecFx16 *axb);
fx32    VEC_Fx16Mag(const VecFx16 *v);
fx32    VEC_Fx16Distance(const VecFx16 *v1, const VecFx16 *v2);
void    VEC_Fx16Normalize(const VecFx16 *pSrc, VecFx16 *pDst);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         VEC_Set

  Description:  Set values to VecFx32

  Arguments:    x, y, z :   set values

  Returns:      a       :   pointer of VecFx32 for set values.
 *---------------------------------------------------------------------------*/
SDK_INLINE void VEC_Set(VecFx32 *a, fx32 x, fx32 y, fx32 z)
{
    SDK_NULL_ASSERT(a);

    a->x = x;
    a->y = y;
    a->z = z;
}

/*---------------------------------------------------------------------------*
  Name:         VEC_Fx16Set

  Description:  Set values to VecFx16

  Arguments:    x, y, z :   set values

  Returns:      a       :   pointer of VecFx16 for set values.
 *---------------------------------------------------------------------------*/
SDK_INLINE void VEC_Fx16Set(VecFx16 *a, fx16 x, fx16 y, fx16 z)
{
    SDK_NULL_ASSERT(a);

    a->x = x;
    a->y = y;
    a->z = z;
}



#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
