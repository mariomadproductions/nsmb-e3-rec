/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     g3imm.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: g3imm.h,v $
  Revision 1.61  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.60  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.59  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.58  2004/11/02 15:06:27  takano_makoto
  fix comments

  Revision 1.57  2004/08/02 07:29:28  takano_makoto
  Add G3*_MultTransMtx33

  Revision 1.56  2004/02/17 12:06:16  nishida_kenji
  Use parameter packing macros.

  Revision 1.55  2004/02/17 08:12:26  nishida_kenji
  small fix.

  Revision 1.54  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.53  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.52  2004/02/04 06:28:46  nishida_kenji
  Add comments.

  Revision 1.51  2004/01/29 12:23:43  nishida_kenji
  fix comments

  Revision 1.50  2004/01/27 11:13:58  nishida_kenji
  append 'static' to inline function prototypes.

  Revision 1.49  2004/01/19 07:22:49  nishida_kenji
  add comments

  Revision 1.48  2004/01/17 07:17:12  nishida_kenji
  remove external include guards

  Revision 1.47  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.46  2004/01/15 11:48:54  nishida_kenji
  adds asserts on G3*_TexCoord

  Revision 1.45  2004/01/15 09:09:40  nishida_kenji
  fix asserts for unit vectors

  Revision 1.44  2004/01/09 09:22:03  nishida_kenji
  fix comments

  Revision 1.43  2003/12/26 00:54:12  nishida_kenji
  minor fix

  Revision 1.42  2003/12/26 00:48:09  nishida_kenji
  change params for G3*_VectorTest

  Revision 1.41  2003/12/25 11:00:10  nishida_kenji
  converted by GX_APIChangeFrom031212-2.pl

  Revision 1.40  2003/12/25 06:25:02  nishida_kenji
  revise a part of geometry command APIs

  Revision 1.39  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.38  2003/12/17 09:10:12  nishida_kenji
  revise PolygonAttr(parameter type for light)

  Revision 1.37  2003/12/17 09:00:20  nishida_kenji
  Totally revised APIs.
  build/buildtools/GX_APIChangeFrom031212.pl would help you change your program to some extent.

  Revision 1.36  2003/12/17 08:50:33  nishida_kenji
  revise comments

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_G3IMM_H_
#define NITRO_G3IMM_H_

#include "nitro/hw/ARM9/mmap_global.h"
#include "nitro/gx/g3.h"
#include "nitro/fx/fx_const.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

static void G3_Direct0(int op);
static void G3_Direct1(int op, u32 param0);
static void G3_Direct2(int op, u32 param0, u32 param1);
static void G3_Direct3(int op, u32 param0, u32 param1, u32 param2);

static void G3_MtxMode(GXMtxMode mode);
static void G3_PushMtx(void);
static void G3_PopMtx(int num);
static void G3_StoreMtx(int num);
static void G3_RestoreMtx(int num);
static void G3_Identity(void);
void    G3_LoadMtx44(const MtxFx44 *m);
void    G3_LoadMtx43(const MtxFx43 *m);
void    G3_MultMtx44(const MtxFx44 *m);
void    G3_MultMtx43(const MtxFx43 *m);
void    G3_MultMtx33(const MtxFx33 *m);
void    G3_MultTransMtx33(const MtxFx33 *mtx, const VecFx32 *trans);
static void G3_Scale(fx32 x, fx32 y, fx32 z);
static void G3_Translate(fx32 x, fx32 y, fx32 z);
static void G3_Color(GXRgb rgb);
static void G3_Normal(fx16 x, fx16 y, fx16 z);
static void G3_TexCoord(fx32 s, fx32 t);
static void G3_Vtx(fx16 x, fx16 y, fx16 z);
static void G3_Vtx10(fx16 x, fx16 y, fx16 z);
static void G3_VtxXY(fx16 x, fx16 y);
static void G3_VtxXZ(fx16 x, fx16 z);
static void G3_VtxYZ(fx16 y, fx16 z);
static void G3_VtxDiff(fx16 x, fx16 y, fx16 z);
static void G3_PolygonAttr(int light, GXPolygonMode polyMode, GXCull cullMode, int polygonID, int alpha, int misc       // GXPolygonAttrMisc
    );
static void G3_TexImageParam(GXTexFmt texFmt,
                             GXTexGen texGen,
                             GXTexSizeS s,
                             GXTexSizeT t,
                             GXTexRepeat repeat, GXTexFlip flip, GXTexPlttColor0 pltt0, u32 addr);
static void G3_TexPlttBase(u32 addr, GXTexFmt texfmt);
static void G3_MaterialColorDiffAmb(GXRgb diffuse, GXRgb ambient, BOOL IsSetVtxColor);
static void G3_MaterialColorSpecEmi(GXRgb specular, GXRgb emission, BOOL IsShininess);
static void G3_LightVector(GXLightId lightID, fx16 x, fx16 y, fx16 z);
static void G3_LightColor(GXLightId lightID, GXRgb rgb);
void    G3_Shininess(const u32 *table);
static void G3_Begin(GXBegin primitive);
static void G3_End(void);
static void G3_SwapBuffers(GXSortMode am, GXBufferMode zw);
static void G3_ViewPort(int x1, int y1, int x2, int y2);
static void G3_BoxTest(const GXBoxTestParam *box);
static void G3_PositionTest(fx16 x, fx16 y, fx16 z);
static void G3_VectorTest(fx16 x, fx16 y, fx16 z);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------


/*---------------------------------------------------------------------------*
  Name:         G3_Direct0

  Description:  Sends a geometry command with no parameters.

  Arguments:    op         A geometry command(GXOP_xxxxxxx)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Direct0(int op)
{
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = 0;
}


/*---------------------------------------------------------------------------*
  Name:         G3_Direct1

  Description:  Sends a geometry command with a parameter.

  Arguments:    op         A geometry command(GXOP_xxxxxxx)
                param0     A parameter

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Direct1(int op, u32 param0)
{
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = param0;
}


/*---------------------------------------------------------------------------*
  Name:         G3_Direct2

  Description:  Sends a geometry command with two parameters.

  Arguments:    op         A geometry command(GXOP_xxxxxxx)
                param0     A parameter
                param1     A parameter

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Direct2(int op, u32 param0, u32 param1)
{
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = param0;
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = param1;
}


/*---------------------------------------------------------------------------*
  Name:         G3_Direct3

  Description:  Sends a geometry command with three parameters.

  Arguments:    op         A geometry command(GXOP_xxxxxxx)
                param0     A parameter
                param1     A parameter
                param2     A parameter

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Direct3(int op, u32 param0, u32 param1, u32 param2)
{
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = param0;
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = param1;
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = param2;
}


/*---------------------------------------------------------------------------*
  Name:         G3_MtxMode

  Description:  Sets a matrix mode.

  Arguments:    mode       A matrix mode

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_MtxMode(GXMtxMode mode)
{
    GX_MTXMODE_ASSERT(mode);

    reg_G3_MTX_MODE = GX_PACK_MTXMODE_PARAM(mode);
}


/*---------------------------------------------------------------------------*
  Name:         G3_PushMtx

  Description:  Stores a current matrix to the top of the matrix stack,
                and increments the stack pointer

  Arguments:    none

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_PushMtx()
{
    reg_G3_MTX_PUSH = 0;
}


/*---------------------------------------------------------------------------*
  Name:         G3_PopMtx

  Description:  Pops the num'th matrix from the matrix stack pointer
                on the stack, and adds num to the pointer.

  Arguments:    num        an offset to the stack pointer

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_PopMtx(int num)
{
    GX_MTX_POP_NUM_ASSERT(num);

    reg_G3_MTX_POP = GX_PACK_POPMTX_PARAM(num);
}


/*---------------------------------------------------------------------------*
  Name:         G3_StoreMtx

  Description:  Stores a current matrix to the num'th matrix from the matrix
                stack pointer on the stack.

  Arguments:    num        an offset to the stack pointer

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_StoreMtx(int num)
{
    GX_MTX_STORE_NUM_ASSERT(num);

    reg_G3_MTX_STORE = GX_PACK_STOREMTX_PARAM(num);
}


/*---------------------------------------------------------------------------*
  Name:         G3_RestoreMtx

  Description:  Gets the num'th matrix from the matrix stack pointer
                on the stack.

  Arguments:    num        an offset to the stack pointer

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_RestoreMtx(int num)
{
    GX_MTX_RESTORE_NUM_ASSERT(num);

    reg_G3_MTX_RESTORE = GX_PACK_RESTOREMTX_PARAM(num);
}


/*---------------------------------------------------------------------------*
  Name:         G3_Identity

  Description:  Sets an identity matrix to the current matrix.

  Arguments:    none

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Identity()
{
    reg_G3_MTX_IDENTITY = 0;
}


/*---------------------------------------------------------------------------*
  Name:         G3_Scale

  Description:  Multiplies the current matrix by a scale matrix.

  Arguments:    x          X coordinate of a scale
                y          Y coordinate of a scale
                z          Z coordinate of a scale

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Scale(fx32 x, fx32 y, fx32 z)
{
    reg_G3_MTX_SCALE = (u32)x;
    reg_G3_MTX_SCALE = (u32)y;
    reg_G3_MTX_SCALE = (u32)z;
}


/*---------------------------------------------------------------------------*
  Name:         G3_Translate

  Description:  Multiplies the current matrix by a translation matrix.

  Arguments:    x          X coordinate of a translation vector
                y          Y coordinate of a translation vector
                z          Z coordinate of a translation vector

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Translate(fx32 x, fx32 y, fx32 z)
{
    reg_G3_MTX_TRANS = (u32)x;
    reg_G3_MTX_TRANS = (u32)y;
    reg_G3_MTX_TRANS = (u32)z;
}


/*---------------------------------------------------------------------------*
  Name:         G3_Color

  Description:  Sends a vertex color.

  Arguments:    rgb        a vertex color(R:5, G:5, B:5)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Color(GXRgb rgb)
{
    GXRGB_ASSERT(rgb);

    reg_G3_COLOR = GX_PACK_COLOR_PARAM(rgb);
}


/*---------------------------------------------------------------------------*
  Name:         G3_Normal

  Description:  Sends a normal vector.

  Arguments:    x          X coordinate of a normal vector
                y          Y coordinate of a normal vector
                z          Z coordinate of a normal vector

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Normal(fx16 x, fx16 y, fx16 z)
{
    SDK_MINMAX_ASSERT(x, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(y, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(z, -FX16_ONE, FX16_ONE - 1);

    reg_G3_NORMAL = GX_PACK_NORMAL_PARAM(x, y, z);
}


/*---------------------------------------------------------------------------*
  Name:         G3_TexCoord

  Description:  Sends a texture coordinate.

  Arguments:    s          an S of a texture coordinate
                t          a T of a texture coordinate

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_TexCoord(fx32 s, fx32 t)
{
    SDK_MINMAX_ASSERT(s, -2048 * FX32_ONE, 2048 * FX32_ONE - 1);
    SDK_MINMAX_ASSERT(t, -2048 * FX32_ONE, 2048 * FX32_ONE - 1);

    reg_G3_TEXCOORD = GX_PACK_TEXCOORD_PARAM(s, t);
}


/*---------------------------------------------------------------------------*
  Name:         G3_Vtx

  Description:  Sends a vertex as a fx16 vector.

  Arguments:    x          X coordinate of a vertex
                y          Y coordinate of a vertex
                z          Z coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Vtx(fx16 x, fx16 y, fx16 z)
{
    reg_G3_VTX_16 = GX_FX16PAIR(x, y);
    reg_G3_VTX_16 = (u32)(u16)z;
}

/*---------------------------------------------------------------------------*
  Name:         G3_Vtx10

  Description:  Sends a vertex as a s3.6 vector.

  Arguments:    x          X coordinate of a vertex
                y          Y coordinate of a vertex
                z          Z coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Vtx10(fx16 x, fx16 y, fx16 z)
{
    reg_G3_VTX_10 = GX_PACK_VTX10_PARAM(x, y, z);
}


/*---------------------------------------------------------------------------*
  Name:         G3_VtxXY

  Description:  Sends XY components of a vertex.
                The Z coordinate is the same to the vertex sent just before.

  Arguments:    x          X coordinate of a vertex
                y          Y coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_VtxXY(fx16 x, fx16 y)
{
    reg_G3_VTX_XY = GX_PACK_VTXXY_PARAM(x, y);
}


/*---------------------------------------------------------------------------*
  Name:         G3_VtxXZ

  Description:  Sends XZ components of a vertex.
                The Y coordinate is the same to the vertex sent just before.

  Arguments:    x          X coordinate of a vertex
                z          Z coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_VtxXZ(fx16 x, fx16 z)
{
    reg_G3_VTX_XZ = GX_PACK_VTXXZ_PARAM(x, z);
}


/*---------------------------------------------------------------------------*
  Name:         G3_VtxYZ

  Description:  Sends YZ components of a vertex.
                The X component is the same to the vertex sent just before.

  Arguments:    x          X coordinate of a vertex
                y          Y coordinate of a vertex

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_VtxYZ(fx16 y, fx16 z)
{
    reg_G3_VTX_YZ = GX_PACK_VTXYZ_PARAM(y, z);
}


/*---------------------------------------------------------------------------*
  Name:         G3_VtxDiff

  Description:  Sends a vector as an offset to the last vertex sent.

  Arguments:    x          X coordinate of an offset
                y          Y coordinate of an offset
                z          Z coordinate of an offset

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_VtxDiff(fx16 x, fx16 y, fx16 z)
{
    SDK_MINMAX_ASSERT(x, (fx16)0xfe00, (fx16)0x1ff);
    SDK_MINMAX_ASSERT(y, (fx16)0xfe00, (fx16)0x1ff);
    SDK_MINMAX_ASSERT(z, (fx16)0xfe00, (fx16)0x1ff);

    reg_G3_VTX_DIFF = GX_PACK_VTXDIFF_PARAM(x, y, z);
}


/*---------------------------------------------------------------------------*
  Name:         G3_PolygonAttr

  Description:  Sends attributes for polygons.

  Arguments:    light      a 4bits field specifying light enable/disable
                polyMode   a polygon mode
                cullMode   a cull mode
                polygonID  a polygon ID
                alpha      an alpha value
                misc       miscellaneous flags
  
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_PolygonAttr(int light, GXPolygonMode polyMode, GXCull cullMode, int polygonID, int alpha, int misc        // GXPolygonAttrMisc
    )
{
    GX_LIGHTMASK_ASSERT(light);
    GX_POLYGONMODE_ASSERT(polyMode);
    GX_CULL_ASSERT(cullMode);
    GX_POLYGON_ATTR_POLYGONID_ASSERT(polygonID);
    GX_POLYGON_ATTR_ALPHA_ASSERT(alpha);

    reg_G3_POLYGON_ATTR = GX_PACK_POLYGONATTR_PARAM(light,
                                                    polyMode, cullMode, polygonID, alpha, misc);
}


/*---------------------------------------------------------------------------*
  Name:         G3_TexImageParam

  Description:  Sends parameters for a texture.

  Arguments:    texFmt     format of a texture
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
static inline void G3_TexImageParam(GXTexFmt texFmt,
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

    reg_G3_TEXIMAGE_PARAM = GX_PACK_TEXIMAGE_PARAM(texFmt, texGen, s, t, repeat, flip, pltt0, addr);
}


/*---------------------------------------------------------------------------*
  Name:         G3_TexPlttBase

  Description:  Sends a base address of a texture palette.

  Arguments:    addr       the offset address in the texture palette slots
                texFmt     format of a texture
  
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_TexPlttBase(u32 addr, GXTexFmt texfmt)
{
    u32     param = GX_PACK_TEXPLTTBASE_PARAM(addr, texfmt);
    GX_TEXPLTTBASEPARAM_ASSERT(param);

    reg_G3_TEXPLTT_BASE = param;
}

/*---------------------------------------------------------------------------*
  Name:         G3_MaterialColorDiffAmb

  Description:  Sends diffuse and ambient.

  Arguments:    diffuse        a diffuse color
                ambient        an ambient color
                IsSetVtxColor  sets a diffuse color as a vertex color if TRUE
  
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_MaterialColorDiffAmb(GXRgb diffuse, GXRgb ambient, BOOL IsSetVtxColor)
{
    GXRGB_ASSERT(diffuse);
    GXRGB_ASSERT(ambient);

    reg_G3_DIF_AMB = GX_PACK_DIFFAMB_PARAM(diffuse, ambient, IsSetVtxColor);
}


/*---------------------------------------------------------------------------*
  Name:         G3_MaterialColorSpecEmi

  Description:  Sends specular and emission.

  Arguments:    specular       a specular color
                emission       an emission color
                IsShininess    use the shininess table to change a specular
                               color if TRUE

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_MaterialColorSpecEmi(GXRgb specular, GXRgb emission, BOOL IsShininess)
{
    GXRGB_ASSERT(specular);
    GXRGB_ASSERT(emission);

    reg_G3_SPE_EMI = GX_PACK_SPECEMI_PARAM(specular, emission, IsShininess);
}


/*---------------------------------------------------------------------------*
  Name:         G3_LightVector

  Description:  Sends a light vector.

  Arguments:    lightID    light ID
                x          X coordinate of a light vector
                y          Y coordinate of a light vector
                z          Z coordinate of a light vector

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_LightVector(GXLightId lightID, fx16 x, fx16 y, fx16 z)
{
    GX_LIGHTID_ASSERT(lightID);
    SDK_MINMAX_ASSERT(x, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(y, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(z, -FX16_ONE, FX16_ONE - 1);

    reg_G3_LIGHT_VECTOR = GX_PACK_LIGHTVECTOR_PARAM(lightID, x, y, z);
}


/*---------------------------------------------------------------------------*
  Name:         G3_LightColor

  Description:  Sends a light color.

  Arguments:    lightID    light ID
                rgb        a light color(R:5, G:5, B:5)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_LightColor(GXLightId lightID, GXRgb rgb)
{
    GX_LIGHTID_ASSERT(lightID);
    GXRGB_ASSERT(rgb);

    reg_G3_LIGHT_COLOR = GX_PACK_LIGHTCOLOR_PARAM(lightID, rgb);
}


/*---------------------------------------------------------------------------*
  Name:         G3_Begin

  Description:  Starts sending primitives.

  Arguments:    primitive  the type of primitives

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_Begin(GXBegin primitive)
{
    GX_BEGIN_ASSERT(primitive);

    reg_G3_BEGIN_VTXS = GX_PACK_BEGIN_PARAM(primitive);
}


/*---------------------------------------------------------------------------*
  Name:         G3_End

  Description:  Ends sending primitives.

  Arguments:    none

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_End()
{
    reg_G3_END_VTXS = 0;
}


/*---------------------------------------------------------------------------*
  Name:         G3_SwapBuffers

  Description:  Swaps the polygon list RAM, the vertex RAM, etc.

  Arguments:    am         auto sort/manual sort
                zw         Z buffer/W buffer

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_SwapBuffers(GXSortMode am, GXBufferMode zw)
{
    GX_SORTMODE_ASSERT(am);
    GX_BUFFERMODE_ASSERT(zw);

    reg_G3_SWAP_BUFFERS = GX_PACK_SWAPBUFFERS_PARAM(am, zw);
}


/*---------------------------------------------------------------------------*
  Name:         G3_ViewPort

  Description:  Specifies viewport.

  Arguments:    x1         the X coordinate of the lower left
                y1         the Y coordinate of the lower left
                x2         the X coordinate of the upper right
                y2         the Y coordinate of the upper right

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_ViewPort(int x1, int y1, int x2, int y2)
{
    GX_VIEWPORT_ASSERT(x1, y1, x2, y2);

    reg_G3_VIEWPORT = GX_PACK_VIEWPORT_PARAM(x1, y1, x2, y2);
}


/*---------------------------------------------------------------------------*
  Name:         G3_BoxTest

  Description:  Tests if a box is in the frustum or not.

  Arguments:    box        a pointer to GXBoxTestParam

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_BoxTest(const GXBoxTestParam *box)
{
    reg_G3_BOX_TEST = box->val[0];
    reg_G3_BOX_TEST = box->val[1];
    reg_G3_BOX_TEST = box->val[2];
}


/*---------------------------------------------------------------------------*
  Name:         G3_PositionTest

  Description:  Applies a position vector to the current clip matrix.

  Arguments:    x          X coordinate of a position
                y          Y coordinate of a position
                z          Z coordinate of a position

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_PositionTest(fx16 x, fx16 y, fx16 z)
{
    reg_G3_POS_TEST = GX_FX16PAIR(x, y);
    reg_G3_POS_TEST = (u32)(u16)z;
}


/*---------------------------------------------------------------------------*
  Name:         G3_VectorTest

  Description:  Applies a vector to the current vector matrix.

  Arguments:    x          X coordinate of a vector
                y          Y coordinate of a vector
                z          Z coordinate of a vector

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G3_VectorTest(fx16 x, fx16 y, fx16 z)
{
    SDK_MINMAX_ASSERT(x, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(y, -FX16_ONE, FX16_ONE - 1);
    SDK_MINMAX_ASSERT(z, -FX16_ONE, FX16_ONE - 1);

    reg_G3_VEC_TEST = GX_PACK_VECTORTEST_PARAM(x, y, z);
}



#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_G3IMM_H_ */
#endif
