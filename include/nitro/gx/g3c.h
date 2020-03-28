/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     g3c.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: g3c.h,v $
  Revision 1.57  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.56  2005/09/16 01:16:35  yasu
  Corrected mistake in the macro name _cplusplus

  Revision 1.55  2005/09/09 09:05:05  yasu
  Support for inline notation in VC.net

  Revision 1.54  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.53  2005/09/08 11:18:01  yasu
  Switched from SDK_WIN32 to SDK_FROM_TOOL.

  Revision 1.52  2005/09/08 10:06:01  yasu
  Support for variable length VC.net macros in SDK_WIN32

  Revision 1.51  2005/08/10 08:57:36  yasu
  Corrected g3b.c and g3c.c so that they can be compiled on a PC.

  Revision 1.50  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.49  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.48  2004/11/02 15:06:27  takano_makoto
  fix comments

  Revision 1.47  2004/08/02 07:29:28  takano_makoto
  Add G3*_MultTransMtx33

  Revision 1.46  2004/02/17 12:32:54  nishida_kenji
  Use parameter packing macros.

  Revision 1.45  2004/02/17 08:12:26  nishida_kenji
  small fix.

  Revision 1.44  2004/02/09 06:34:31  nishida_kenji
  G3CS_Direct[0-3] not inlined to avoid byte write problem in thumb mode.

  Revision 1.43  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.42  2004/02/04 06:28:46  nishida_kenji
  Add comments.

  Revision 1.41  2004/01/28 00:28:13  nishida_kenji
  G3C_xxxx not inlined.

  Revision 1.40  2004/01/17 07:17:12  nishida_kenji
  remove external include guards

  Revision 1.39  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.38  2004/01/15 11:48:54  nishida_kenji
  adds asserts on G3*_TexCoord

  Revision 1.37  2004/01/15 09:09:40  nishida_kenji
  fix asserts for unit vectors

  Revision 1.36  2003/12/26 00:48:09  nishida_kenji
  change params for G3*_VectorTest

  Revision 1.35  2003/12/25 11:00:10  nishida_kenji
  converted by GX_APIChangeFrom031212-2.pl

  Revision 1.34  2003/12/25 06:25:02  nishida_kenji
  revise a part of geometry command APIs

  Revision 1.33  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.32  2003/12/17 09:10:12  nishida_kenji
  revise PolygonAttr(parameter type for light)

  Revision 1.31  2003/12/17 09:00:20  nishida_kenji
  Totally revised APIs.
  build/buildtools/GX_APIChangeFrom031212.pl would help you change your program to some extent.

  Revision 1.30  2003/12/17 08:50:33  nishida_kenji
  revise comments

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_G3C_H_
#define NITRO_G3C_H_

#include "nitro/gx/g3.h"
#include "nitro/fx/fx_const.h"

#ifdef __cplusplus
extern "C" {
#endif

// no assert on win32
#if (defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#define SDK_ASSERT(exp)                         ((void) 0)
#define SDK_ALIGN4_ASSERT(exp)                  ((void) 0)
#define SDK_MINMAX_ASSERT(exp, min, max)        ((void) 0)
#define SDK_NULL_ASSERT(exp)                    ((void) 0)
#if (defined(_MSC_VER) && !defined(__cplusplus))
#define inline __inline
#endif
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

// G3CS_*
void    G3CS_Direct0(GXDLInfo *info, int op);
void    G3CS_Direct1(GXDLInfo *info, int op, u32 param0);
void    G3CS_Direct2(GXDLInfo *info, int op, u32 param0, u32 param1);
void    G3CS_Direct3(GXDLInfo *info, int op, u32 param0, u32 param1, u32 param2);
void    G3CS_DirectN(GXDLInfo *info, int op, int nParams, const u32 *params);

static void G3CS_Nop(GXDLInfo *info);
static void G3CS_MtxMode(GXDLInfo *info, GXMtxMode mode);
static void G3CS_PushMtx(GXDLInfo *info);
static void G3CS_PopMtx(GXDLInfo *info, int num);
static void G3CS_StoreMtx(GXDLInfo *info, int num);
static void G3CS_RestoreMtx(GXDLInfo *info, int num);
static void G3CS_Identity(GXDLInfo *info);
void    G3CS_LoadMtx44(GXDLInfo *info, const MtxFx44 *m);
void    G3CS_LoadMtx43(GXDLInfo *info, const MtxFx43 *m);
void    G3CS_MultMtx44(GXDLInfo *info, const MtxFx44 *m);
void    G3CS_MultMtx43(GXDLInfo *info, const MtxFx43 *m);
void    G3CS_MultMtx33(GXDLInfo *info, const MtxFx33 *m);
void    G3CS_MultTransMtx33(GXDLInfo *info, const MtxFx33 *mtx, const VecFx32 *trans);
static void G3CS_Scale(GXDLInfo *info, fx32 x, fx32 y, fx32 z);
static void G3CS_Translate(GXDLInfo *info, fx32 x, fx32 y, fx32 z);
static void G3CS_Color(GXDLInfo *info, GXRgb rgb);
static void G3CS_Normal(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
static void G3CS_TexCoord(GXDLInfo *info, fx32 s, fx32 t);
static void G3CS_Vtx(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
static void G3CS_Vtx10(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
static void G3CS_VtxXY(GXDLInfo *info, fx16 x, fx16 y);
static void G3CS_VtxXZ(GXDLInfo *info, fx16 x, fx16 z);
static void G3CS_VtxYZ(GXDLInfo *info, fx16 y, fx16 z);
static void G3CS_VtxDiff(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
static void G3CS_PolygonAttr(GXDLInfo *info, int light, GXPolygonMode polyMode, GXCull cullMode, int polygonID, int alpha, int misc     // GXPolygonAttrMisc
    );
static void G3CS_TexImageParam(GXDLInfo *info,
                               GXTexFmt texFmt,
                               GXTexGen texGen,
                               GXTexSizeS s,
                               GXTexSizeT t,
                               GXTexRepeat repeat, GXTexFlip flip, GXTexPlttColor0 pltt0, u32 addr);
static void G3CS_TexPlttBase(GXDLInfo *info, u32 addr, GXTexFmt texfmt);
static void G3CS_MaterialColorDiffAmb(GXDLInfo *info, GXRgb diffuse, GXRgb ambient,
                                      BOOL IsSetVtxColor);
static void G3CS_MaterialColorSpecEmi(GXDLInfo *info, GXRgb specular, GXRgb emission,
                                      BOOL IsShininess);
static void G3CS_LightVector(GXDLInfo *info, GXLightId lightID, fx16 x, fx16 y, fx16 z);
static void G3CS_LightColor(GXDLInfo *info, GXLightId lightID, GXRgb rgb);
static void G3CS_Shininess(GXDLInfo *info, const u32 *table);
static void G3CS_Begin(GXDLInfo *info, GXBegin primitive);
static void G3CS_End(GXDLInfo *info);
static void G3CS_SwapBuffers(GXDLInfo *info, GXSortMode am, GXBufferMode zw);
static void G3CS_ViewPort(GXDLInfo *info, int x1, int y1, int x2, int y2);
static void G3CS_BoxTest(GXDLInfo *info, const GXBoxTestParam *box);
static void G3CS_PositionTest(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
static void G3CS_VectorTest(GXDLInfo *info, fx16 x, fx16 y, fx16 z);

// G3C_*
void    G3C_UpdateGXDLInfo(GXDLInfo *info, int n);
void    G3C_Direct0(GXDLInfo *info, int op);
void    G3C_Direct1(GXDLInfo *info, int op, u32 param0);
void    G3C_Direct2(GXDLInfo *info, int op, u32 param0, u32 param1);
void    G3C_Direct3(GXDLInfo *info, int op, u32 param0, u32 param1, u32 param2);
void    G3C_DirectN(GXDLInfo *info, int op, int nParams, const u32 *params);

void    G3C_Nop(GXDLInfo *info);
void    G3C_MtxMode(GXDLInfo *info, GXMtxMode mode);
void    G3C_PushMtx(GXDLInfo *info);
void    G3C_PopMtx(GXDLInfo *info, int num);
void    G3C_StoreMtx(GXDLInfo *info, int num);
void    G3C_RestoreMtx(GXDLInfo *info, int num);
void    G3C_Identity(GXDLInfo *info);
void    G3C_LoadMtx44(GXDLInfo *info, const MtxFx44 *m);
void    G3C_LoadMtx43(GXDLInfo *info, const MtxFx43 *m);
void    G3C_MultMtx44(GXDLInfo *info, const MtxFx44 *m);
void    G3C_MultMtx43(GXDLInfo *info, const MtxFx43 *m);
void    G3C_MultMtx33(GXDLInfo *info, const MtxFx33 *m);
void    G3C_MultTransMtx33(GXDLInfo *info, const MtxFx33 *mtx, const VecFx32 *trans);
void    G3C_Scale(GXDLInfo *info, fx32 x, fx32 y, fx32 z);
void    G3C_Translate(GXDLInfo *info, fx32 x, fx32 y, fx32 z);
void    G3C_Color(GXDLInfo *info, GXRgb rgb);
void    G3C_Normal(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
void    G3C_TexCoord(GXDLInfo *info, fx32 s, fx32 t);
void    G3C_Vtx(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
void    G3C_Vtx10(GXDLInfo *info, fx16, fx16, fx16);
void    G3C_VtxXY(GXDLInfo *info, fx16 x, fx16 y);
void    G3C_VtxXZ(GXDLInfo *info, fx16 x, fx16 z);
void    G3C_VtxYZ(GXDLInfo *info, fx16 y, fx16 z);
void    G3C_VtxDiff(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
void    G3C_PolygonAttr(GXDLInfo *info, int light, GXPolygonMode polyMode, GXCull cullMode, int polygonID, int alpha, int misc  // GXPolygonAttrMisc
    );
void    G3C_TexImageParam(GXDLInfo *info,
                          GXTexFmt texFmt,
                          GXTexGen texGen,
                          GXTexSizeS s,
                          GXTexSizeT t,
                          GXTexRepeat repeat, GXTexFlip flip, GXTexPlttColor0 pltt0, u32 addr);
void    G3C_TexPlttBase(GXDLInfo *info, u32 addr, GXTexFmt texfmt);
void    G3C_MaterialColorDiffAmb(GXDLInfo *info, GXRgb diffuse, GXRgb ambient, BOOL IsSetVtxColor);
void    G3C_MaterialColorSpecEmi(GXDLInfo *info, GXRgb specular, GXRgb emission, BOOL IsShininess);
void    G3C_LightVector(GXDLInfo *info, GXLightId lightID, fx16 x, fx16 y, fx16 z);
void    G3C_LightColor(GXDLInfo *info, GXLightId lightID, GXRgb rgb);
void    G3C_Shininess(GXDLInfo *info, const u32 *table);
void    G3C_Begin(GXDLInfo *info, GXBegin primitive);
void    G3C_End(GXDLInfo *info);
void    G3C_SwapBuffers(GXDLInfo *info, GXSortMode am, GXBufferMode zw);
void    G3C_ViewPort(GXDLInfo *info, int x1, int y1, int x2, int y2);
void    G3C_BoxTest(GXDLInfo *info, const GXBoxTestParam *box);
void    G3C_PositionTest(GXDLInfo *info, fx16 x, fx16 y, fx16 z);
void    G3C_VectorTest(GXDLInfo *info, fx16 x, fx16 y, fx16 z);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

// G3CS_*




/*---------------------------------------------------------------------------*
  Name:         G3CS_Nop

  Description:  Makes a geometry command which does nothing on a display list.
                Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Nop(GXDLInfo *info)
{
    G3CS_Direct0(info, G3OP_NOP);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_MtxMode

  Description:  Makes a geometry command, which sets a matrix mode,
                on a display list. Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo
                mode       a matrix mode

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_MtxMode(GXDLInfo *info, GXMtxMode mode)
{
    GX_MTXMODE_ASSERT(mode);

    G3CS_Direct1(info, G3OP_MTX_MODE, GX_PACK_MTXMODE_PARAM(mode));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_PushMtx

  Description:  Makes a geometry command, which stores a current matrix to
                the top of the matrix stack and increments the stack pointer,
                on a display list. Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_PushMtx(GXDLInfo *info)
{
    G3CS_Direct0(info, G3OP_MTX_PUSH);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_PopMtx

  Description:  Makes a geometry command, which pops the num'th matrix
                from the matrix stack pointer on the stack,
                and adds num to the pointer. Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo
                num        an offset to the stack pointer

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_PopMtx(GXDLInfo *info, int num)
{
    GX_MTX_POP_NUM_ASSERT(num);

    G3CS_Direct1(info, G3OP_MTX_POP, GX_PACK_POPMTX_PARAM(num));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_StoreMtx

  Description:  Makes a geometry command, which stores a current matrix
                to the num'th matrix from the matrix stack pointer on the stack,
                on a display list. Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo
                num        an offset to the stack pointer

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_StoreMtx(GXDLInfo *info, int num)
{
    GX_MTX_STORE_NUM_ASSERT(num);

    G3CS_Direct1(info, G3OP_MTX_STORE, GX_PACK_STOREMTX_PARAM(num));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_RestoreMtx

  Description:  Makes a geometry command, which gets the num'th matrix from
                the matrix stack pointer on the stack, on a display list.
                Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo
                num        an offset to the stack pointer

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_RestoreMtx(GXDLInfo *info, int num)
{
    GX_MTX_RESTORE_NUM_ASSERT(num);

    G3CS_Direct1(info, G3OP_MTX_RESTORE, GX_PACK_RESTOREMTX_PARAM(num));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Identity

  Description:  Makes a geometry command, which sets an identity matrix
                to the current matrix, on a display list.
                Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Identity(GXDLInfo *info)
{
    G3CS_Direct0(info, G3OP_MTX_IDENTITY);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Scale

  Description:  Makes a geometry command, which multiplies the current matrix
                by a scale matrix. Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a scale
                y          Y coordinate of a scale
                z          Z coordinate of a scale

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Scale(GXDLInfo *info, fx32 x, fx32 y, fx32 z)
{
    G3CS_Direct3(info, G3OP_MTX_SCALE, (u32)x, (u32)y, (u32)z);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Translate

  Description:  Makes a geometry command, which multiplies the current matrix
                by a translation matrix. Note that the command is packed.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a translation vector
                y          Y coordinate of a translation vector
                z          Z coordinate of a translation vector

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Translate(GXDLInfo *info, fx32 x, fx32 y, fx32 z)
{
    G3CS_Direct3(info, G3OP_MTX_TRANS, (u32)x, (u32)y, (u32)z);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Color

  Description:  Makes a geometry command, which sends a vertex color.

  Arguments:    info       a pointer to GXDLInfo
                rgb        a vertex color(R:5, G:5, B:5)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Color(GXDLInfo *info, GXRgb rgb)
{
    GXRGB_ASSERT(rgb);

    G3CS_Direct1(info, G3OP_COLOR, GX_PACK_COLOR_PARAM(rgb));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Normal

  Description:  Makes a geometry command, which sends a normal vector.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a normal vector
                y          Y coordinate of a normal vector
                z          Z coordinate of a normal vector

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Normal(GXDLInfo *info, fx16 x, fx16 y, fx16 z)
{
    SDK_MINMAX_ASSERT(x, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(y, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(z, -FX16_ONE, FX16_ONE - 1);

    G3CS_Direct1(info, G3OP_NORMAL, GX_PACK_NORMAL_PARAM(x, y, z));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_TexCoord

  Description:  Makes a geometry command, which sends a texture coordinate.

  Arguments:    info       a pointer to GXDLInfo
                s          an S of a texture coordinate
                t          a T of a texture coordinate

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_TexCoord(GXDLInfo *info, fx32 s, fx32 t)
{
    SDK_MINMAX_ASSERT(s, -2048 * FX32_ONE, 2048 * FX32_ONE - 1);
    SDK_MINMAX_ASSERT(t, -2048 * FX32_ONE, 2048 * FX32_ONE - 1);

    G3CS_Direct1(info, G3OP_TEXCOORD, GX_PACK_TEXCOORD_PARAM(s, t));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Vtx

  Description:  Makes a geometry command, which sends a vertex as a fx16 vector.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a vertex
                y          Y coordinate of a vertex
                z          Z coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Vtx(GXDLInfo *info, fx16 x, fx16 y, fx16 z)
{
    G3CS_Direct2(info, G3OP_VTX_16, GX_FX16PAIR(x, y), (u32)(u16)z);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Vtx10

  Description:  Makes a geometry command, which sends a vertex as a s3.6 vector.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a vertex
                y          Y coordinate of a vertex
                z          Z coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Vtx10(GXDLInfo *info, fx16 x, fx16 y, fx16 z)
{
    G3CS_Direct1(info, G3OP_VTX_10, GX_PACK_VTX10_PARAM(x, y, z));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_VtxXY

  Description:  Makes a geometry command, which sends XY components of a vertex.
                The Z coordinate is the same to the vertex sent just before.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a vertex
                y          Y coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_VtxXY(GXDLInfo *info, fx16 x, fx16 y)
{
    G3CS_Direct1(info, G3OP_VTX_XY, GX_PACK_VTXXY_PARAM(x, y));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_VtxXZ

  Description:  Makes a geometry command, which sends XZ components of a vertex.
                The Y coordinate is the same to the vertex sent just before.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a vertex
                z          Z coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_VtxXZ(GXDLInfo *info, fx16 x, fx16 z)
{
    G3CS_Direct1(info, G3OP_VTX_XZ, GX_PACK_VTXXZ_PARAM(x, z));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_VtxYZ

  Description:  Makes a geometry command, which sends YZ components of a vertex.
                The X component is the same to the vertex sent just before.

  Arguments:    info       a pointer to GXDLInfo
                y          Y coordinate of a vertex
                z          Z coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_VtxYZ(GXDLInfo *info, fx16 y, fx16 z)
{
    G3CS_Direct1(info, G3OP_VTX_YZ, GX_PACK_VTXYZ_PARAM(y, z));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_VtxDiff

  Description:  Makes a geometry command, which sends a vector as an offset
                to the last vertex sent.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of an offset
                y          Y coordinate of an offset
                z          Z coordinate of an offset

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_VtxDiff(GXDLInfo *info, fx16 x, fx16 y, fx16 z)
{
    SDK_MINMAX_ASSERT(x, (fx16)0xfe00, (fx16)0x1ff);
    SDK_MINMAX_ASSERT(y, (fx16)0xfe00, (fx16)0x1ff);
    SDK_MINMAX_ASSERT(z, (fx16)0xfe00, (fx16)0x1ff);

    G3CS_Direct1(info, G3OP_VTX_DIFF, GX_PACK_VTXDIFF_PARAM(x, y, z));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_PolygonAttr

  Description:  Makes a geometry command, which sends attributes for polygons.

  Arguments:    info       a pointer to GXDLInfo
                light      a 4bits field specifying light enable/disable
                polyMode   a polygon mode
                cullMode   a cull mode
                polygonID  a polygon ID
                alpha      an alpha value
                misc       miscellaneous flags
  
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_PolygonAttr(GXDLInfo *info, int light, GXPolygonMode polyMode, GXCull cullMode, int polygonID, int alpha, int misc      // GXPolygonAttrMisc
    )
{
    GX_LIGHTMASK_ASSERT(light);
    GX_POLYGONMODE_ASSERT(polyMode);
    GX_CULL_ASSERT(cullMode);
    GX_POLYGON_ATTR_POLYGONID_ASSERT(polygonID);
    GX_POLYGON_ATTR_ALPHA_ASSERT(alpha);

    G3CS_Direct1(info,
                 G3OP_POLYGON_ATTR,
                 GX_PACK_POLYGONATTR_PARAM(light, polyMode, cullMode, polygonID, alpha, misc));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_TexImageParam

  Description:  Makes a geometry command, which sends parameters for a texture.

  Arguments:    info       a pointer to GXDLInfo
                texFmt     format of a texture
                texGen     selects the source of a texture coordinate
                s          the size of a texture in the direction of the S-axis
                t          the size of a texture in the direction of the T-axis
                repeat     repeat
                flip       flip
                pltt0      use/not use the color of pltt. 0
                addr       the offset address in the texture image slots
                           (shift 3bits internally)
  
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_TexImageParam(GXDLInfo *info,
                                      GXTexFmt texFmt,
                                      GXTexGen texGen,
                                      GXTexSizeS s,
                                      GXTexSizeT t,
                                      GXTexRepeat repeat,
                                      GXTexFlip flip, GXTexPlttColor0 pltt0, u32 addr)
{
    GX_TEXREPEAT_ASSERT(repeat);
    GX_TEXFLIP_ASSERT(flip);
    GX_TEXSIZE_S_ASSERT(s);
    GX_TEXSIZE_T_ASSERT(t);
    GX_TEXFMT_ASSERT(texFmt);
    GX_TEXPLTTCOLOR0_ASSERT(pltt0);
    GX_TEXGEN_ASSERT(texGen);
    GX_TEXIMAGE_PARAM_ADDR_ASSERT(addr);

    G3CS_Direct1(info,
                 G3OP_TEXIMAGE_PARAM,
                 GX_PACK_TEXIMAGE_PARAM(texFmt, texGen, s, t, repeat, flip, pltt0, addr));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_TexPlttBase

  Description:  Makes a geometry command, which sends a base address of
                a texture palette.

  Arguments:    info       a pointer to GXDLInfo
                addr       the offset address in the texture palette slots
                texFmt     format of a texture
  
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_TexPlttBase(GXDLInfo *info, u32 addr, GXTexFmt texfmt)
{
    u32     param = GX_PACK_TEXPLTTBASE_PARAM(addr, texfmt);
    GX_TEXPLTTBASEPARAM_ASSERT(param);

    G3CS_Direct1(info, G3OP_TEXPLTT_BASE, param);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_MaterialColorDiffAmb

  Description:  Makes a geometry command, which sends diffuse and ambient.

  Arguments:    info           a pointer to GXDLInfo
                diffuse        a diffuse color
                ambient        an ambient color
                IsSetVtxColor  sets a diffuse color as a vertex color if TRUE
  
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_MaterialColorDiffAmb(GXDLInfo *info,
                                             GXRgb diffuse, GXRgb ambient, BOOL IsSetVtxColor)
{
    GXRGB_ASSERT(diffuse);
    GXRGB_ASSERT(ambient);

    G3CS_Direct1(info, G3OP_DIF_AMB, GX_PACK_DIFFAMB_PARAM(diffuse, ambient, IsSetVtxColor));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_MaterialColorSpecEmi

  Description:  Makes a geometry command, which sends specular and emission.

  Arguments:    info           a pointer to GXDLInfo
                specular       a specular color
                emission       an emission color
                IsShininess    use the shininess table to change a specular
                               color if TRUE

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_MaterialColorSpecEmi(GXDLInfo *info,
                                             GXRgb specular, GXRgb emission, BOOL IsShininess)
{
    GXRGB_ASSERT(specular);
    GXRGB_ASSERT(emission);

    G3CS_Direct1(info, G3OP_SPE_EMI, GX_PACK_SPECEMI_PARAM(specular, emission, IsShininess));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_LightVector

  Description:  Makes a geometry command, which sends a light vector.

  Arguments:    info       a pointer to GXDLInfo
                lightID    light ID
                x          X coordinate of a light vector
                y          Y coordinate of a light vector
                z          Z coordinate of a light vector

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_LightVector(GXDLInfo *info, GXLightId lightID, fx16 x, fx16 y, fx16 z)
{
    GX_LIGHTID_ASSERT(lightID);
    SDK_MINMAX_ASSERT(x, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(y, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(z, -FX16_ONE, FX16_ONE - 1);

    G3CS_Direct1(info, G3OP_LIGHT_VECTOR, GX_PACK_LIGHTVECTOR_PARAM(lightID, x, y, z));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_LightColor

  Description:  Makes a geometry command, which sends a light color.

  Arguments:    info       a pointer to GXDLInfo
                lightID    light ID
                rgb        a light color(R:5, G:5, B:5)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_LightColor(GXDLInfo *info, GXLightId lightID, GXRgb rgb)
{
    GX_LIGHTID_ASSERT(lightID);
    GXRGB_ASSERT(rgb);

    G3CS_Direct1(info, G3OP_LIGHT_COLOR, GX_PACK_LIGHTCOLOR_PARAM(lightID, rgb));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Shininess

  Description:  Makes a geometry command, which sets up the shininess table.

  Arguments:    info       a pointer to GXDLInfo
                table      a pointer to the shininess data(32 words)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Shininess(GXDLInfo *info, const u32 *table)
{
    G3CS_DirectN(info, G3OP_SHININESS, 32, table);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_Begin

  Description:  Makes a geometry command, which starts sending primitives.

  Arguments:    info       a pointer to GXDLInfo
                primitive  the type of primitives

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_Begin(GXDLInfo *info, GXBegin primitive)
{
    GX_BEGIN_ASSERT(primitive);

    G3CS_Direct1(info, G3OP_BEGIN, GX_PACK_BEGIN_PARAM(primitive));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_End

  Description:  Makes a geometry command, which ends sending primitives.

  Arguments:    info       a pointer to GXDLInfo

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_End(GXDLInfo *info)
{
    G3CS_Direct0(info, G3OP_END);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_SwapBuffers

  Description:  Makes a geometry command, which swaps the polygon list RAM,
                the vertex RAM, etc.

  Arguments:    info       a pointer to GXDLInfo
                am         auto sort/manual sort
                zw         Z buffer/W buffer

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_SwapBuffers(GXDLInfo *info, GXSortMode am, GXBufferMode zw)
{
    GX_SORTMODE_ASSERT(am);
    GX_BUFFERMODE_ASSERT(zw);

    G3CS_Direct1(info, G3OP_SWAP_BUFFERS, GX_PACK_SWAPBUFFERS_PARAM(am, zw));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_ViewPort

  Description:  Makes a geometry command, which specifies viewport.

  Arguments:    info       a pointer to GXDLInfo
                x1         the X coordinate of the lower left
                y1         the Y coordinate of the lower left
                x2         the X coordinate of the upper right
                y2         the Y coordinate of the upper right

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_ViewPort(GXDLInfo *info, int x1, int y1, int x2, int y2)
{
    GX_VIEWPORT_ASSERT(x1, y1, x2, y2);

    G3CS_Direct1(info, G3OP_VIEWPORT, GX_PACK_VIEWPORT_PARAM(x1, y1, x2, y2));
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_BoxTest

  Description:  Makes a geometry command, which tests if a box is
                in the frustum or not.

  Arguments:    info       a pointer to GXDLInfo
                box        a pointer to GXBoxTestParam

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_BoxTest(GXDLInfo *info, const GXBoxTestParam *box)
{
    G3CS_Direct3(info, G3OP_BOX_TEST, box->val[0], box->val[1], box->val[2]);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_PositionTest

  Description:  Makes a geometry command, which applies a position vector
                to the current clip matrix.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a position
                y          Y coordinate of a position
                z          Z coordinate of a position

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_PositionTest(GXDLInfo *info, fx16 x, fx16 y, fx16 z)
{
    G3CS_Direct2(info, G3OP_POS_TEST, GX_FX16PAIR(x, y), (u32)(u16)z);
}


/*---------------------------------------------------------------------------*
  Name:         G3CS_VectorTest

  Description:  Makes a geometry command, which applies a vector
                to the current vector matrix.

  Arguments:    info       a pointer to GXDLInfo
                x          X coordinate of a vector
                y          Y coordinate of a vector
                z          Z coordinate of a vector

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3CS_VectorTest(GXDLInfo *info, fx16 x, fx16 y, fx16 z)
{
    SDK_MINMAX_ASSERT(x, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(y, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(z, -FX16_ONE, FX16_ONE - 1);

    G3CS_Direct1(info, G3OP_VEC_TEST, GX_PACK_VECTORTEST_PARAM(x, y, z));
}

#if (defined(_MSC_VER) && !defined(_cplusplus))
#undef inline
#endif

#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_G3C_H_ */
#endif
