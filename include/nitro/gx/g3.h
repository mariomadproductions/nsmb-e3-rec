/*---------------------------------------------------------------------------*
  Project: NitroSDK - GX -
  File: g3.h

  Copyright 2003-2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: g3.h,v $
  Revision 1.74  2007/06/14 01:00:47  okubata_ryoma
  Copyright fix

  Revision 1.73  2007/06/11 00:35:48  okubata_ryoma
  Fixed a macro in which the arguments were not surrounded by parentheses.

  Revision 1.72  2006/04/10 02:30:08  kitase_hirotake
  Added the G3OP_DUMMY_COMMAND command.

  Revision 1.71  2006/03/13 05:59:06  okubata_ryoma
  Minor revisions to macro.

  Revision 1.70  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.69  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.68  2005/07/26 04:39:06  takano_makoto
  Added 'const' modifier to G3_GetDLStart, G3_GetDLLength, G3_GetDLSize arguments

  Revision 1.67  2005/03/15 02:42:48  takano_makoto
  Fixed bug that caused G3_GetDLSize to return size that was too big by 4.

  Revision 1.66  2005/03/01 01:57:00  yosizaki
  Revised copyright year.

  Revision 1.65  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.64  2004/11/02 18:52:02  takano_makoto
  Fixed comments.

  Revision 1.63  2004/08/30 11:34:30  takano_makoto
  Added code for hardware bug in packed geometry command.

  Revision 1.62  2004/05/14 11:52:57  takano_makoto
  Added #ifndef SDK_FROM_TOOL for VC or BCB.

  Revision 1.61  2004/02/27 01:16:55  nishida_kenji
  Small fix

  Revision 1.60  2004/02/18 02:38:34  nishida_kenji
  Added comments.

  Revision 1.57  2004/02/12 10:56:04  yasu
  New location of include files ARM9/ARM7

  Revision 1.56  2004/02/05 07:09:03  yasu
  Changed SDK prefix iris -> nitro

  Revision 1.55  2004/02/04 12:07:58  nishida_kenji
  Added GX_PACK_OP.

  Revision 1.54  2004/02/04 01:23:33  nishida_kenji
  Added GX_COMP4x4_PLTT_IDX and macros for static display lists(GX_PACK_XXXXX_PARAM).

  Revision 1.53  2004/02/02 08:32:12  nishida_kenji
  GX_TEXFMT_ALPHA is obsolete. Use GX_TEXFMT_A5I3 instead.

  Revision 1.52  2004/01/27 11:13:58  nishida_kenji
  Appended 'static' to inline function prototypes.

  Revision 1.51  2004/01/27 07:52:35  nishida_kenji
  Small fix

  Revision 1.50  2004/01/27 00:00:33  nishida_kenji
  Fixed GX_FX16PAIR(suppress sign extend).

  Revision 1.49  2004/01/19 07:22:49  nishida_kenji
  Added comments.

  Revision 1.48  2004/01/18 11:37:46  nishida_kenji
  Small bug fix

  Revision 1.46  2004/01/17 07:17:12  nishida_kenji
  Removed external include guards.

  Revision 1.45  2004/01/17 02:28:38  nishida_kenji
  Converted 'inline' to 'static inline' in header files.

  Revision 1.44  2004/01/15 09:09:53  nishida_kenji
  Removed GX_TEXFMT_PLTT2.

  Revision 1.43  2004/01/13 07:38:08  nishida_kenji
  APIs for making display lists dynamically.

  Revision 1.42  2003/12/25 11:00:10  nishida_kenji
  Converted by GX_APIChangeFrom031212-2.pl.

  Revision 1.41  2003/12/25 06:25:02  nishida_kenji
  Revised a part of geometry command APIs.

  Revision 1.40  2003/12/25 00:19:29  nishida_kenji
  Converted INLINE to inline.

  Revision 1.39  2003/12/18 00:19:51  nishida_kenji
  Revised macros.

  Revision 1.38  2003/12/17 09:10:12  nishida_kenji
  Revised PolygonAttr(parameter type for light).

  Revision 1.37  2003/12/17 09:00:20  nishida_kenji
  Totally revised APIs.
  build/buildtools/GX_APIChangeFrom031212.pl would help you change your program to some extent.

  Revision 1.36  2003/12/17 08:50:33  nishida_kenji
  Revised comments.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_G3_H_
#define NITRO_G3_H_

#include "nitro/gx/gxcommon.h"
#include "nitro/hw/ARM9/ioreg_G3.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Definition of Geometry Commands
//----------------------------------------------------------------------------
                                                           /* Command Name   */
#define G3OP_NOP                0x00   /* Nop            */

#define G3OP_MTX_MODE           0x10   /* MatrixMode     */
#define G3OP_MTX_PUSH           0x11   /* PushMatrix     */
#define G3OP_MTX_POP            0x12   /* PopMatrix      */
#define G3OP_MTX_STORE          0x13   /* StoreMatrix    */
#define G3OP_MTX_RESTORE        0x14   /* RestoreMatrix  */
#define G3OP_MTX_IDENTITY       0x15   /* Identity       */
#define G3OP_MTX_LOAD_4x4       0x16   /* LoadMatrix44   */
#define G3OP_MTX_LOAD_4x3       0x17   /* LoadMatrix43   */
#define G3OP_MTX_MULT_4x4       0x18   /* MultMatrix44   */
#define G3OP_MTX_MULT_4x3       0x19   /* MultMatrix43   */
#define G3OP_MTX_MULT_3x3       0x1a   /* MultMatrix33   */
#define G3OP_MTX_SCALE          0x1b   /* Scale          */
#define G3OP_MTX_TRANS          0x1c   /* Translate      */

#define G3OP_COLOR              0x20   /* Color          */
#define G3OP_NORMAL             0x21   /* Normal         */
#define G3OP_TEXCOORD           0x22   /* TexCoord       */
#define G3OP_VTX_16             0x23   /* Vertex         */
#define G3OP_VTX_10             0x24   /* VertexShort    */
#define G3OP_VTX_XY             0x25   /* VertexXY       */
#define G3OP_VTX_XZ             0x26   /* VertexXZ       */
#define G3OP_VTX_YZ             0x27   /* VertexYZ       */
#define G3OP_VTX_DIFF           0x28   /* VertexDiff     */
#define G3OP_POLYGON_ATTR       0x29   /* PolygonAttr    */
#define G3OP_TEXIMAGE_PARAM     0x2a   /* TexImageParam  */
#define G3OP_TEXPLTT_BASE       0x2b   /* TexPlttBase    */

#define G3OP_DIF_AMB            0x30   /* MaterialColor0 */
#define G3OP_SPE_EMI            0x31   /* MaterialColor1 */
#define G3OP_LIGHT_VECTOR       0x32   /* LightVector    */
#define G3OP_LIGHT_COLOR        0x33   /* LightColor     */
#define G3OP_SHININESS          0x34   /* Shininess      */

#define G3OP_BEGIN              0x40   /* Begin          */
#define G3OP_END                0x41   /* End            */

#define G3OP_SWAP_BUFFERS       0x50   /* SwapBuffers    */

#define G3OP_VIEWPORT           0x60   /* Viewport       */

#define G3OP_BOX_TEST           0x70   /* BoxTest        */
#define G3OP_POS_TEST           0x71   /* PositionTest   */
#define G3OP_VEC_TEST           0x72   /* VectorTest     */

#define G3OP_DUMMY_COMMAND      0xFF   /* Dummy command */

//----------------------------------------------------------------------------
// The number of the parameters of the commands
//----------------------------------------------------------------------------
                                                           /* Command Name   */
#define G3OP_NOP_NPARAMS                0       /* Nop            */

#define G3OP_MTX_MODE_NPARAMS           1       /* MatrixMode     */
#define G3OP_MTX_PUSH_NPARAMS           0       /* PushMatrix     */
#define G3OP_MTX_POP_NPARAMS            1       /* PopMatrix      */
#define G3OP_MTX_STORE_NPARAMS          1       /* StoreMatrix    */
#define G3OP_MTX_RESTORE_NPARAMS        1       /* RestoreMatrix  */
#define G3OP_MTX_IDENTITY_NPARAMS       0       /* Identity       */
#define G3OP_MTX_LOAD_4x4_NPARAMS       16      /* LoadMatrix44   */
#define G3OP_MTX_LOAD_4x3_NPARAMS       12      /* LoadMatrix43   */
#define G3OP_MTX_MULT_4x4_NPARAMS       16      /* MultMatrix44   */
#define G3OP_MTX_MULT_4x3_NPARAMS       12      /* MultMatrix43   */
#define G3OP_MTX_MULT_3x3_NPARAMS       9       /* MultMatrix33   */
#define G3OP_MTX_SCALE_NPARAMS          3       /* Scale          */
#define G3OP_MTX_TRANS_NPARAMS          3       /* Translate      */

#define G3OP_COLOR_NPARAMS              1       /* Color          */
#define G3OP_NORMAL_NPARAMS             1       /* Normal         */
#define G3OP_TEXCOORD_NPARAMS           1       /* TexCoord       */
#define G3OP_VTX_16_NPARAMS             2       /* Vertex         */
#define G3OP_VTX_10_NPARAMS             1       /* VertexShort    */
#define G3OP_VTX_XY_NPARAMS             1       /* VertexXY       */
#define G3OP_VTX_XZ_NPARAMS             1       /* VertexXZ       */
#define G3OP_VTX_YZ_NPARAMS             1       /* VertexYZ       */
#define G3OP_VTX_DIFF_NPARAMS           1       /* VertexDiff     */
#define G3OP_POLYGON_ATTR_NPARAMS       1       /* PolygonAttr    */
#define G3OP_TEXIMAGE_PARAM_NPARAMS     1       /* TexImageParam  */
#define G3OP_TEXPLTT_BASE_NPARAMS       1       /* TexPlttBase    */

#define G3OP_DIF_AMB_NPARAMS            1       /* MaterialColor0 */
#define G3OP_SPE_EMI_NPARAMS            1       /* MaterialColor1 */
#define G3OP_LIGHT_VECTOR_NPARAMS       1       /* LightVector    */
#define G3OP_LIGHT_COLOR_NPARAMS        1       /* LightColor     */
#define G3OP_SHININESS_NPARAMS          32      /* Shininess      */

#define G3OP_BEGIN_NPARAMS              1       /* Begin          */
#define G3OP_END_NPARAMS                0       /* End            */

#define G3OP_SWAP_BUFFERS_NPARAMS       1       /* SwapBuffers    */

#define G3OP_VIEWPORT_NPARAMS           1       /* Viewport       */

#define G3OP_BOX_TEST_NPARAMS           3       /* BoxTest        */
#define G3OP_POS_TEST_NPARAMS           2       /* PositionTest   */
#define G3OP_VEC_TEST_NPARAMS           1       /* VectorTest     */

// Notice that this assert is not perfect
#define GX_VALID_OPCODE_ASSERT(x)       SDK_ASSERT((x == 0xFF) || ((x >= 0) && (x <= 0x72)))

//----------------------------------------------------------------------------
//    Parameters for G3_MtxMode
//----------------------------------------------------------------------------
typedef enum
{
    GX_MTXMODE_PROJECTION = 0,
    GX_MTXMODE_POSITION = 1,
    GX_MTXMODE_POSITION_VECTOR = 2,
    GX_MTXMODE_TEXTURE = 3
}
GXMtxMode;

#define GX_MTXMODE_ASSERT(x)                    \
    SDK_MINMAX_ASSERT(x, GX_MTXMODE_PROJECTION, GX_MTXMODE_TEXTURE)


//----------------------------------------------------------------------------
//    Parameters for G3_PopMtx
//----------------------------------------------------------------------------

#define GX_MTX_POP_NUM_ASSERT(x) SDK_MINMAX_ASSERT(x, -30, 31)

//----------------------------------------------------------------------------
//    Parameters for G3_StoreMtx
//----------------------------------------------------------------------------

#define GX_MTX_STORE_NUM_ASSERT(x) SDK_MINMAX_ASSERT(x, 0, 30)

//----------------------------------------------------------------------------
//    Parameters for G3_RestoreMtx
//----------------------------------------------------------------------------
#define GX_MTX_RESTORE_NUM_ASSERT(x) SDK_MINMAX_ASSERT(x, 0, 30)

//----------------------------------------------------------------------------
//    Parameters for G3_Begin
//----------------------------------------------------------------------------
typedef enum
{
    GX_BEGIN_TRIANGLES = 0,
    GX_BEGIN_QUADS = 1,
    GX_BEGIN_TRIANGLE_STRIP = 2,
    GX_BEGIN_QUAD_STRIP = 3
}
GXBegin;

#define GX_BEGIN_ASSERT(x)                   \
    SDK_MINMAX_ASSERT(x, GX_BEGIN_TRIANGLES, GX_BEGIN_QUAD_STRIP)

//----------------------------------------------------------------------------
//    Parameters for G3_SwapBuffers
//----------------------------------------------------------------------------
typedef enum
{
    GX_SORTMODE_AUTO = 0,
    GX_SORTMODE_MANUAL = 1
}
GXSortMode;

#define GX_SORTMODE_ASSERT(x)           \
    SDK_MINMAX_ASSERT(x, GX_SORTMODE_AUTO, GX_SORTMODE_MANUAL)

typedef enum
{
    GX_BUFFERMODE_Z = 0,
    GX_BUFFERMODE_W = 1
}
GXBufferMode;

#define GX_BUFFERMODE_ASSERT(x)           \
    SDK_MINMAX_ASSERT(x, GX_BUFFERMODE_Z, GX_BUFFERMODE_W)

//----------------------------------------------------------------------------
//    Parameters for G3_ViewPort
//----------------------------------------------------------------------------
#define GX_VIEWPORT_ASSERT(x1, y1, x2, y2)     \
    SDK_ASSERT( (x1) < (x2) && (y1) < (y2) &&  \
                (x1) >= 0 && (x2) < 256 &&     \
                (y1) >= 0 && (y2) < 192 )

//----------------------------------------------------------------------------
//    Parameters for G3_PolygonAttr
//----------------------------------------------------------------------------
#define GX_POLYGON_ATTR_POLYGONID_ASSERT(x) GX_POLYGONID_ASSERT(x)
#define GX_POLYGON_ATTR_ALPHA_ASSERT(x) GX_ALPHA_ASSERT(x)

typedef enum
{
    GX_LIGHTMASK_NONE = 0,
    GX_LIGHTMASK_0 = 1,
    GX_LIGHTMASK_1 = 2,
    GX_LIGHTMASK_01 = 3,
    GX_LIGHTMASK_2 = 4,
    GX_LIGHTMASK_02 = 5,
    GX_LIGHTMASK_12 = 6,
    GX_LIGHTMASK_012 = 7,
    GX_LIGHTMASK_3 = 8,
    GX_LIGHTMASK_03 = 9,
    GX_LIGHTMASK_13 = 10,
    GX_LIGHTMASK_013 = 11,
    GX_LIGHTMASK_23 = 12,
    GX_LIGHTMASK_023 = 13,
    GX_LIGHTMASK_123 = 14,
    GX_LIGHTMASK_0123 = 15
}
GXLightMask;

#define GX_LIGHTMASK_ASSERT(x) SDK_MINMAX_ASSERT(x, 0, 15)


typedef enum
{
    GX_POLYGONMODE_MODULATE = 0,
    GX_POLYGONMODE_DECAL = 1,
    GX_POLYGONMODE_TOON = 2,
    GX_POLYGONMODE_SHADOW = 3
}
GXPolygonMode;

#define GX_POLYGONMODE_ASSERT(x)                  \
    SDK_MINMAX_ASSERT(x, GX_POLYGONMODE_MODULATE, GX_POLYGONMODE_SHADOW)


typedef enum
{
    GX_CULL_ALL = 0,
    GX_CULL_FRONT = 1,
    GX_CULL_BACK = 2,
    GX_CULL_NONE = 3
}
GXCull;

#define GX_CULL_ASSERT(x)             \
    SDK_MINMAX_ASSERT(x, GX_CULL_ALL, GX_CULL_NONE)


typedef enum
{
    GX_POLYGON_ATTR_MISC_NONE = 0,
    GX_POLYGON_ATTR_MISC_XLU_DEPTH_UPDATE = 1 << REG_G3_POLYGON_ATTR_XL_SHIFT,
    GX_POLYGON_ATTR_MISC_FAR_CLIPPING = 1 << REG_G3_POLYGON_ATTR_FC_SHIFT,
    GX_POLYGON_ATTR_MISC_DISP_1DOT = 1 << REG_G3_POLYGON_ATTR_D1_SHIFT,
    GX_POLYGON_ATTR_MISC_DEPTHTEST_DECAL = 1 << REG_G3_POLYGON_ATTR_DT_SHIFT,
    GX_POLYGON_ATTR_MISC_FOG = 1 << REG_G3_POLYGON_ATTR_FE_SHIFT
}
GXPolygonAttrMisc;

//----------------------------------------------------------------------------
//    Parameters for G3_TexImageParam
//----------------------------------------------------------------------------
typedef enum
{
    GX_TEXREPEAT_NONE = 0,
    GX_TEXREPEAT_S = 1,
    GX_TEXREPEAT_T = 2,
    GX_TEXREPEAT_ST = 3
}
GXTexRepeat;

#define GX_TEXREPEAT_ASSERT(x)              \
    SDK_MINMAX_ASSERT(x, GX_TEXREPEAT_NONE, GX_TEXREPEAT_ST)


typedef enum
{
    GX_TEXFLIP_NONE = 0,
    GX_TEXFLIP_S = 1,
    GX_TEXFLIP_T = 2,
    GX_TEXFLIP_ST = 3
}
GXTexFlip;

#define GX_TEXFLIP_ASSERT(x)                     \
    SDK_MINMAX_ASSERT(x, GX_TEXFLIP_NONE,GX_TEXFLIP_ST)


typedef enum
{
    GX_TEXSIZE_S8 = 0,
    GX_TEXSIZE_S16 = 1,
    GX_TEXSIZE_S32 = 2,
    GX_TEXSIZE_S64 = 3,
    GX_TEXSIZE_S128 = 4,
    GX_TEXSIZE_S256 = 5,
    GX_TEXSIZE_S512 = 6,
    GX_TEXSIZE_S1024 = 7
}
GXTexSizeS;

#define GX_TEXSIZE_S_ASSERT(x)          \
    SDK_MINMAX_ASSERT(x, GX_TEXSIZE_S8, GX_TEXSIZE_S1024)


typedef enum
{
    GX_TEXSIZE_T8 = 0,
    GX_TEXSIZE_T16 = 1,
    GX_TEXSIZE_T32 = 2,
    GX_TEXSIZE_T64 = 3,
    GX_TEXSIZE_T128 = 4,
    GX_TEXSIZE_T256 = 5,
    GX_TEXSIZE_T512 = 6,
    GX_TEXSIZE_T1024 = 7
}
GXTexSizeT;

#define GX_TEXSIZE_T_ASSERT(x)          \
    SDK_MINMAX_ASSERT(x, GX_TEXSIZE_T8, GX_TEXSIZE_T1024)


typedef enum
{
    GX_TEXFMT_NONE = 0,
    GX_TEXFMT_A3I5 = 1,
    GX_TEXFMT_PLTT4 = 2,
    GX_TEXFMT_PLTT16 = 3,
    GX_TEXFMT_PLTT256 = 4,
    GX_TEXFMT_COMP4x4 = 5,
    GX_TEXFMT_A5I3 = 6,
    GX_TEXFMT_DIRECT = 7
}
GXTexFmt;

#define GX_TEXFMT_ALPHA ((GXTexFmt)GX_TEXFMT_A5I3)      // Obsolete name

#define GX_TEXFMT_ASSERT(x)              \
    SDK_MINMAX_ASSERT(x, GX_TEXFMT_NONE, GX_TEXFMT_DIRECT)


typedef enum
{
    GX_TEXPLTTCOLOR0_USE = 0,
    GX_TEXPLTTCOLOR0_TRNS = 1
}
GXTexPlttColor0;

#define GX_TEXPLTTCOLOR0_ASSERT(x)             \
    SDK_MINMAX_ASSERT(x, GX_TEXPLTTCOLOR0_USE, GX_TEXPLTTCOLOR0_TRNS)


typedef enum
{
    GX_TEXGEN_NONE = 0,
    GX_TEXGEN_TEXCOORD = 1,
    GX_TEXGEN_NORMAL = 2,
    GX_TEXGEN_VERTEX = 3
}
GXTexGen;

#define GX_TEXGEN_ASSERT(x)              \
    SDK_MINMAX_ASSERT(x, GX_TEXGEN_NONE, GX_TEXGEN_VERTEX)


#define GX_TEXIMAGE_PARAM_ADDR_ASSERT(addr) \
    SDK_ASSERT(((addr) & 0x7) == 0 && (addr) >= 0 && (addr) < 0x80000)


//----------------------------------------------------------------------------
// Light ID
//----------------------------------------------------------------------------
typedef enum
{
    GX_LIGHTID_0 = 0,
    GX_LIGHTID_1 = 1,
    GX_LIGHTID_2 = 2,
    GX_LIGHTID_3 = 3
}
GXLightId;

#define GX_LIGHTID_ASSERT(x)           \
    SDK_MINMAX_ASSERT(x, GX_LIGHTID_0, GX_LIGHTID_3)

//----------------------------------------------------------------------------
// Structure for BoxTest command
//----------------------------------------------------------------------------
#ifdef SDK_ADS
typedef struct
{
    u32     val[3];
}
GXBoxTestParam;
#else
typedef union
{
    u32     val[3];
    struct
    {
        fx16    x;
        fx16    y;
        fx16    z;
        fx16    width;
        fx16    height;
        fx16    depth;
    };
}
GXBoxTestParam;
#endif

//----------------------------------------------------------------------------
// Structure for G3BS, G3B, G3CS, G3C
//----------------------------------------------------------------------------
typedef struct
{
    u8     *curr_cmd;
    u32    *curr_param;
    u32    *bottom;
    u32     length;
    BOOL    param0_cmd_flg;
}
GXDLInfo;

/* Types for TexCoord */
typedef u32 GXSt;
/* Types for G3*_TexPlttBaseImm */
typedef u32 GXTexPlttBaseParam;
#define GX_TEXPLTTBASEPARAM_ASSERT(x)     SDK_ASSERT((x) < 0xe000)

//----------------------------------------------------------------------------
// 3D vector of s3.6 fixed point
//----------------------------------------------------------------------------
typedef u32 VecVtx10;
#define GX_VTX10_SHIFT                 6
#define GX_VTX10_INT_SIZE              3
#define GX_VTX10_DEC_SIZE              6

#define GX_VTX10_INT_MASK              0x01c0
#define GX_VTX10_DEC_MASK              0x003f
#define GX_VTX10_SIGN_MASK             0x0200
#define GX_VTX10_MASK                  (GX_VTX10_INT_MASK | GX_VTX10_DEC_MASK | GX_VTX10_SIGN_MASK)

#define GX_VTX10_MAX                   ((fx32)(0x00007fc0))
#define GX_VTX10_MIN                   ((fx32)(0xffff8000))

#define GX_VEC_VTX10_X_SHIFT           0
#define GX_VEC_VTX10_Y_SHIFT           10
#define GX_VEC_VTX10_Z_SHIFT           20

//----------------------------------------------------------------------------
//   For parameters of G3OP_VTX_XY, G3OP_VTX_XZ, G3OP_VTX_YZ
//----------------------------------------------------------------------------
#define GX_FX16PAIR(a, b)              ((u32)((u32)(u16)(a) | ((u32)(u16)(b) << 16)))

//----------------------------------------------------------------------------
//   To generate a parameter of G3*_Vtx10
//   x: fx32/16, y : fx32/16, z : fx32/16
//----------------------------------------------------------------------------
#define GX_VECVTX10(x, y, z) \
    ((VecVtx10) (((((x) >> (FX32_DEC_SIZE - GX_VTX10_DEC_SIZE)) & GX_VTX10_MASK) << GX_VEC_VTX10_X_SHIFT) | \
                 ((((y) >> (FX32_DEC_SIZE - GX_VTX10_DEC_SIZE)) & GX_VTX10_MASK) << GX_VEC_VTX10_Y_SHIFT) | \
                 ((((z) >> (FX32_DEC_SIZE - GX_VTX10_DEC_SIZE)) & GX_VTX10_MASK) << GX_VEC_VTX10_Z_SHIFT)))


//----------------------------------------------------------------------------
// 3D vector of s0.0009 fixed point
//----------------------------------------------------------------------------
typedef u32 VecVtxDiff;
#define GX_VTXDIFF_MASK                0x03ff

#define GX_VTXDIFF_MAX                 ((fx32)(0x000001ff))
#define GX_VTXDIFF_MIN                 ((fx32)(0xfffffe00))

#define GX_VEC_VTXDIFF_X_SHIFT         0
#define GX_VEC_VTXDIFF_Y_SHIFT         10
#define GX_VEC_VTXDIFF_Z_SHIFT         20

#define GX_VECVTXDIFF(x, y, z) \
    ((VecVtxDiff) ((((x) & GX_VTXDIFF_MASK) << GX_VEC_VTXDIFF_X_SHIFT) | \
                   (((y) & GX_VTXDIFF_MASK) << GX_VEC_VTXDIFF_Y_SHIFT) | \
                   (((z) & GX_VTXDIFF_MASK) << GX_VEC_VTXDIFF_Z_SHIFT)))

//----------------------------------------------------------------------------
// TexCoord
//----------------------------------------------------------------------------

#define GX_FX16ST(x)                   ((s16)((x) >> 8))
// s: fx32/fx16, t: fx32/fx16
#define GX_ST(s, t)                    ((GXSt)((u16)GX_FX16ST(s) | ((u16)GX_FX16ST(t) << 16)))

//----------------------------------------------------------------------------
// 4x4COMP Pltt index address(offset) computation
//----------------------------------------------------------------------------

#define GX_COMP4x4_PLTT_IDX(image) \
    ((u32)(0x20000 + (((image) & 0x1ffff) >> 1) + (((image) & 0x40000) >> 2)))

//----------------------------------------------------------------------------
// Parameter packing macros (for static display lists)
//----------------------------------------------------------------------------

#define GX_PACK_OP(op1, op2, op3, op4) \
    ((u32)((op1) | ((op2) << 8) | ((op3) << 16) | ((op4) << 24)))
#define GX_PACK_SWAPBUFFERS_PARAM(am, zw) \
    ((u32) (((am) << REG_G3_SWAP_BUFFERS_XS_SHIFT) | \
            ((zw) << REG_G3_SWAP_BUFFERS_DP_SHIFT)))
#define GX_PACK_MTXMODE_PARAM(mode)    ((u32) ((mode) << REG_G3_MTX_MODE_M_SHIFT))
#define GX_PACK_POPMTX_PARAM(num)      ((u32) (num))
#define GX_PACK_STOREMTX_PARAM(num)    ((u32) (num))
#define GX_PACK_RESTOREMTX_PARAM(num)  ((u32) (num))
#define GX_PACK_LIGHTVECTOR_PARAM(lightID, x, y, z)        \
    ((u32)GX_VECFX10((x), (y), (z))                      | \
     ((u32)(lightID) << REG_G3_LIGHT_VECTOR_LNUM_SHIFT))
#define GX_PACK_LIGHTCOLOR_PARAM(lightID, rgb)                   \
    ((u32)((rgb)                                               | \
           ((u32)(lightID) << REG_G3_LIGHT_COLOR_LNUM_SHIFT)))
#define GX_PACK_DIFFAMB_PARAM(diffuse, ambient, IsSetVtxColor)   \
    ((u32)((diffuse)                                           | \
           ((ambient) << REG_G3_DIF_AMB_AMBIENT_RED_SHIFT)     | \
           (((IsSetVtxColor) != FALSE) << REG_G3_DIF_AMB_C_SHIFT)))
#define GX_PACK_SPECEMI_PARAM(specular, emission, IsShininess)   \
    ((u32)((specular)                                          | \
           ((emission) << REG_G3_SPE_EMI_EMISSION_RED_SHIFT)   | \
           (((IsShininess) != FALSE) << REG_G3_SPE_EMI_S_SHIFT)))
#define GX_PACK_POLYGONATTR_PARAM(light, polyMode, cullMode, polygonID, alpha, misc) \
    ((u32)(((light) << REG_G3_POLYGON_ATTR_LE_SHIFT)     | \
           ((polyMode) << REG_G3_POLYGON_ATTR_PM_SHIFT)  | \
           ((cullMode) << REG_G3_POLYGON_ATTR_BK_SHIFT)  | \
           (misc)                                        | \
           ((polygonID) << REG_G3_POLYGON_ATTR_ID_SHIFT) | \
           ((alpha) << REG_G3_POLYGON_ATTR_ALPHA_SHIFT)))
#define GX_PACK_BEGIN_PARAM(primitive)                 \
    ((u32)((primitive) << REG_G3_BEGIN_VTXS_TYPE_SHIFT))
#define GX_PACK_COLOR_PARAM(rgb)       ((u32)(rgb))
#define GX_PACK_NORMAL_PARAM(x, y, z)  ((u32)GX_VECFX10((x), (y), (z)))
#define GX_PACK_VTX10_PARAM(x, y, z)   ((u32)GX_VECVTX10((x), (y), (z)))
#define GX_PACK_VTXXY_PARAM(x, y)      (GX_FX16PAIR((x), (y)))
#define GX_PACK_VTXXZ_PARAM(x, z)      (GX_FX16PAIR((x), (z)))
#define GX_PACK_VTXYZ_PARAM(y, z)      (GX_FX16PAIR((y), (z)))
#define GX_PACK_VTXDIFF_PARAM(x, y, z) (GX_VECVTXDIFF((x), (y), (z)))
#define GX_PACK_TEXCOORD_PARAM(s, t)   (GX_ST((s), (t)))
#define GX_PACK_TEXIMAGE_PARAM(texFmt, texGen, s, t, repeat, flip, pltt0, addr) \
    ((u32)(((addr) >> 3)                                    | \
           ((texFmt) << REG_G3_TEXIMAGE_PARAM_TEXFMT_SHIFT) | \
           ((texGen) << REG_G3_TEXIMAGE_PARAM_TGEN_SHIFT)   | \
           ((s) << REG_G3_TEXIMAGE_PARAM_V_SIZE_SHIFT)      | \
           ((t) << REG_G3_TEXIMAGE_PARAM_T_SIZE_SHIFT)      | \
           ((repeat) << REG_G3_TEXIMAGE_PARAM_RS_SHIFT)     | \
           ((flip) << REG_G3_TEXIMAGE_PARAM_FS_SHIFT)       | \
           ((pltt0) << REG_G3_TEXIMAGE_PARAM_TR_SHIFT)))
#define GX_PACK_TEXPLTTBASE_PARAM(addr, texFmt) \
    ((u32)((addr) >> (4 - ((texFmt) == GX_TEXFMT_PLTT4))))
#define GX_PACK_VIEWPORT_PARAM(x1, y1, x2, y2)                \
    ((u32)((x1) | ((y1) << 8) | ((x2) << 16) | ((y2) << 24)))
#define GX_PACK_VECTORTEST_PARAM(x, y, z) ((u32)GX_VECFX10((x), (y), (z)))




/* If include from Other Environment for example VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

void    G3_BeginMakeDL(GXDLInfo *info, void *ptr, u32 length);
u32     G3_EndMakeDL(GXDLInfo *info);
static void *G3_GetDLStart(const GXDLInfo *info);
static u32 G3_GetDLLength(const GXDLInfo *info);
static u32 G3_GetDLSize(const GXDLInfo *info);

static GXTexPlttBaseParam G3_MakeTexPlttBaseParam(u32 plttBaseAddr, GXTexFmt texfmt);


//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------


/*---------------------------------------------------------------------------*
  Name: G3_GetDLStart

  Description: Gets a pointer to a display list(command list) buffer.

  Arguments: info      a pointer to struct GXDLInfo

  Returns: a pointer to the display list

 *---------------------------------------------------------------------------*/
static inline void *G3_GetDLStart(const GXDLInfo *info)
{
    return (void *)info->bottom;
}


/*---------------------------------------------------------------------------*
  Name: G3_GetDLLength

  Description: Gets the length of a display list(command list) buffer.

  Arguments: info      a pointer to struct GXDLInfo

  Returns: the length of a display list(in bytes)
 *---------------------------------------------------------------------------*/
static inline u32 G3_GetDLLength(const GXDLInfo *info)
{
    return info->length;
}


/*---------------------------------------------------------------------------*
  Name: G3_GetDLSize

  Description: Gets the size of the display list generated.

  Arguments: info      a pointer to struct GXDLInfo

  Returns: the size of the display list
 *---------------------------------------------------------------------------*/
static inline u32 G3_GetDLSize(const GXDLInfo *info)
{
    SDK_ASSERT((u32)info->bottom < (u32)info->curr_param);
    if ((u32)info->curr_cmd & 3)
    {
        return (u32)((u32)info->curr_param - (u32)info->bottom);
    }
    else
    {
        return (u32)((u32)info->curr_cmd - (u32)info->bottom);
    }
}


/*---------------------------------------------------------------------------*
  Name: G3_MakeTexPlttBaseParam

  Description: Converts texture palette address to value set register.
                Function to shrink if texfmt is constant

  Arguments: plttBaseAddr    base address to put texture palette.
                texfmt          texture image format.

  Returns: base address set to reg_G3_TEXPLTT_BASE.
 *---------------------------------------------------------------------------*/
static inline GXTexPlttBaseParam G3_MakeTexPlttBaseParam(u32 plttBaseAddr, GXTexFmt texfmt)
{
    SDK_ASSERT(GX_TEXFMT_NONE != texfmt);

    if (GX_TEXFMT_PLTT4 == texfmt)
    {
        // If the format of the texture is GX_TEXFMT_PLTT4,
        // hardware shifts a parameter leftward by 3 bits.
        SDK_ASSERT((plttBaseAddr & 0x7) == 0);
        return (GXTexPlttBaseParam)(plttBaseAddr >> 3);
    }
    else
    {
        // Otherwise, shifts a parameter leftward by 4 bits.
        SDK_ASSERT((plttBaseAddr & 0xf) == 0);
        return (GXTexPlttBaseParam)(plttBaseAddr >> 4);
    }
}


#endif // SDK_FROM_TOOL

#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_G3_H_ */
#endif
