/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     g2_oam.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: g2_oam.h,v $
  Revision 1.26  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.25  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.24  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.23  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.22  2004/12/27 04:45:05  takano_makoto
  Added Getter function of register

  Revision 1.21  2004/11/02 17:06:20  takano_makoto
  fix comments.

  Revision 1.20  2004/06/09 05:21:35  takano_makoto
  Add inline functions G2_GetOBJXX().

  Revision 1.19  2004/05/17 00:02:36  takano_makoto
  Add include file, "<nitro/fx/fx_const.h"".

  Revision 1.18  2004/05/14 11:52:57  takano_makoto
  Add #ifndef SDK_FROM_TOOL for VC or BCB.

  Revision 1.17  2004/04/07 00:48:00  takano_makoto
  Bug fix at G2_SetOBJAttr()

  Revision 1.16  2004/04/05 10:26:20  takano_makoto
  Modify G2_SetOBJAttr() to use macro.

  Revision 1.15  2004/04/01 13:12:40  takano_makoto
  Fix  G2S_SetOBJAttr()

  Revision 1.14  2004/02/18 02:30:14  nishida_kenji
  Add comments.

  Revision 1.10  2004/02/12 10:56:04  yasu
  new location of include files ARM9/ARM7

  Revision 1.9  2004/02/12 09:28:47  nishida_kenji
  G2_SetOBJColor->G2_SetOBJColorMode and GXOamColor->GXOamColorMode.

  Revision 1.8  2004/02/12 08:59:30  nishida_kenji
  Add G2_SetOBJColor.
  Warning if both GX_OAM_COLOR_256 and GX_OAM_MODE_BITMAPOBJ are specified.

  Revision 1.7  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.6  2004/01/27 11:13:58  nishida_kenji
  append 'static' to inline function prototypes.

  Revision 1.5  2004/01/19 07:22:49  nishida_kenji
  add comments

  Revision 1.4  2004/01/17 07:17:12  nishida_kenji
  remove external include guards

  Revision 1.3  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.2  2004/01/14 11:23:42  nishida_kenji
  add G2_OBJMosaic,
  remove GXOamMosaic

  Revision 1.1  2003/12/25 12:13:39  nishida_kenji
  renamed

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_G2_OAM_H_
#define NITRO_G2_OAM_H_

#include "nitro/hw/ARM9/mmap_global.h"
#include "nitro/gx/gxcommon.h"
#include "nitro/fx/fx_const.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------
#ifdef SDK_ADS
typedef struct
{
    u32     attr01;
    u16     attr2;
    u16     _3;
}
GXOamAttr;
#else
typedef struct
{
    union
    {
        u32     attr01;
        struct
        {
            u16     attr0;
            u16     attr1;
        };
        struct
        {
            u32     y:8;
            u32     rsMode:2;
            u32     objMode:2;
            u32     mosaic:1;
            u32     colorMode:1;
            u32     shape:2;

            u32     x:9;
            u32     rsParam:5;
            u32     size:2;
        };
        struct
        {
            u32     _0:28;
            u32     flipH:1;
            u32     flipV:1;
            u32     _1:2;
        };
    };
    union
    {
        struct
        {
            u16     attr2;
            u16     _3;
        };
        u32     attr23;
        struct
        {
            u32     charNo:10;
            u32     priority:2;
            u32     cParam:4;
            u32     _2:16;
        };
    };
}
GXOamAttr;
#endif

typedef struct
{
    u16     _0;
    u16     _1;
    u16     _2;
    s16     PA;
    u16     _4;
    u16     _5;
    u16     _6;
    s16     PB;
    u16     _8;
    u16     _9;
    u16     _10;
    s16     PC;
    u16     _12;
    u16     _13;
    u16     _14;
    s16     PD;
}
GXOamAffine;


#define GX_OAM_ATTR01_Y_SHIFT                             0
#define GX_OAM_ATTR01_Y_SIZE                              8
#define GX_OAM_ATTR01_Y_MASK                              0x000000ff

#define GX_OAM_ATTR01_RSENABLE_SHIFT                      8
#define GX_OAM_ATTR01_RSENABLE_SIZE                       2
#define GX_OAM_ATTR01_RSENABLE_MASK                       0x00000300

#define GX_OAM_ATTR01_MODE_SHIFT                          10
#define GX_OAM_ATTR01_MODE_SIZE                           2
#define GX_OAM_ATTR01_MODE_MASK                           0x00000c00

#define GX_OAM_ATTR01_MOSAIC_SHIFT                        12
#define GX_OAM_ATTR01_MOSAIC_SIZE                         1
#define GX_OAM_ATTR01_MOSAIC_MASK                         0x00001000

#define GX_OAM_ATTR01_CM_SHIFT                            13
#define GX_OAM_ATTR01_CM_SIZE                             1
#define GX_OAM_ATTR01_CM_MASK                             0x00002000

#define GX_OAM_ATTR01_SHAPE_SHIFT                         14
#define GX_OAM_ATTR01_SHAPE_SIZE                          2
#define GX_OAM_ATTR01_SHAPE_MASK                          0x0000c000

#define GX_OAM_ATTR01_X_SHIFT                             16
#define GX_OAM_ATTR01_X_SIZE                              9
#define GX_OAM_ATTR01_X_MASK                              0x01ff0000

#define GX_OAM_ATTR01_RS_SHIFT                            25
#define GX_OAM_ATTR01_RS_SIZE                             5
#define GX_OAM_ATTR01_RS_MASK                             0x3e000000
#define GX_OAM_ATTR01_FLIP_MASK                           0x30000000

#define GX_OAM_ATTR01_HF_SHIFT                            28
#define GX_OAM_ATTR01_HF_SIZE                             1
#define GX_OAM_ATTR01_HF_MASK                             0x10000000

#define GX_OAM_ATTR01_VF_SHIFT                            29
#define GX_OAM_ATTR01_VF_SIZE                             1
#define GX_OAM_ATTR01_VF_MASK                             0x20000000

#define GX_OAM_ATTR01_SIZE_SHIFT                          30
#define GX_OAM_ATTR01_SIZE_SIZE                           2
#define GX_OAM_ATTR01_SIZE_MASK                           0xc0000000


#define GX_OAM_ATTR2_NAME_SHIFT                           0
#define GX_OAM_ATTR2_NAME_SIZE                            10
#define GX_OAM_ATTR2_NAME_MASK                            0x03ff

#define GX_OAM_ATTR2_PRIORITY_SHIFT                       10
#define GX_OAM_ATTR2_PRIORITY_SIZE                        2
#define GX_OAM_ATTR2_PRIORITY_MASK                        0x0c00

#define GX_OAM_ATTR2_CPARAM_SHIFT                         12
#define GX_OAM_ATTR2_CPARAM_SIZE                          4
#define GX_OAM_ATTR2_CPARAM_MASK                          0xf000

#define GX_OAM_OBJNUM_ASSERT(obj)                         SDK_MINMAX_ASSERT(obj, 0, 127)
#define GX_OAM_CPARAM_ASSERT(x)                           SDK_MINMAX_ASSERT(x, 0, 15)
#define GX_OAM_RSPARAM_ASSERT(x)                          SDK_MINMAX_ASSERT(x, 0, 31)
#define GX_OAM_CHARNAME_ASSERT(x)                         SDK_MINMAX_ASSERT(x,  0, 1023)


//
// Parameters for G2_SetOBJShape and G2_SetOBJAttr
//
typedef enum
{
    GX_OAM_SHAPE_8x8 = (0 << GX_OAM_ATTR01_SHAPE_SHIFT) | (0 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_16x16 = (0 << GX_OAM_ATTR01_SHAPE_SHIFT) | (1 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_32x32 = (0 << GX_OAM_ATTR01_SHAPE_SHIFT) | (2 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_64x64 = (0 << GX_OAM_ATTR01_SHAPE_SHIFT) | (3 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_16x8 = (1 << GX_OAM_ATTR01_SHAPE_SHIFT) | (0 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_32x8 = (1 << GX_OAM_ATTR01_SHAPE_SHIFT) | (1 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_32x16 = (1 << GX_OAM_ATTR01_SHAPE_SHIFT) | (2 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_64x32 = (1 << GX_OAM_ATTR01_SHAPE_SHIFT) | (3 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_8x16 = (2 << GX_OAM_ATTR01_SHAPE_SHIFT) | (0 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_8x32 = (2 << GX_OAM_ATTR01_SHAPE_SHIFT) | (1 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_16x32 = (2 << GX_OAM_ATTR01_SHAPE_SHIFT) | (2 << GX_OAM_ATTR01_SIZE_SHIFT),
    GX_OAM_SHAPE_32x64 = (2 << GX_OAM_ATTR01_SHAPE_SHIFT) | (3 << GX_OAM_ATTR01_SIZE_SHIFT)
}
GXOamShape;

#define GX_OAM_SHAPE_ASSERT(x)               \
    SDK_ASSERT( (x) == GX_OAM_SHAPE_8x8   || \
                (x) == GX_OAM_SHAPE_16x16 || \
                (x) == GX_OAM_SHAPE_32x32 || \
                (x) == GX_OAM_SHAPE_64x64 || \
                (x) == GX_OAM_SHAPE_16x8  || \
                (x) == GX_OAM_SHAPE_32x8  || \
                (x) == GX_OAM_SHAPE_32x16 || \
                (x) == GX_OAM_SHAPE_64x32 || \
                (x) == GX_OAM_SHAPE_8x16  || \
                (x) == GX_OAM_SHAPE_8x32  || \
                (x) == GX_OAM_SHAPE_16x32 || \
                (x) == GX_OAM_SHAPE_32x64 )


//
// Parameters for G2_SetOBJColorMode and G2_SetOBJAttr
//
typedef enum
{
    GX_OAM_COLORMODE_16 = 0,
    GX_OAM_COLORMODE_256 = 1
}
GXOamColorMode;

// OBSOLETE
typedef GXOamColorMode GXOamColor;
#define GX_OAM_COLOR_16      ((GXOamColorMode)GX_OAM_COLORMODE_16)
#define GX_OAM_COLOR_256     ((GXOamColorMode)GX_OAM_COLORMODE_256)


#define GX_OAM_COLORMODE_ASSERT(x)             \
    SDK_MINMAX_ASSERT(x, GX_OAM_COLORMODE_16, GX_OAM_COLORMODE_256)


//
// Parameters for G2_SetOBJEffect and G2_SetOBJAttr
//
typedef enum
{
    GX_OAM_EFFECT_NONE =
        (0 << GX_OAM_ATTR01_RSENABLE_SHIFT) | (0 << GX_OAM_ATTR01_HF_SHIFT) | (0 <<
                                                                               GX_OAM_ATTR01_VF_SHIFT),
    GX_OAM_EFFECT_FLIP_H =
        (0 << GX_OAM_ATTR01_RSENABLE_SHIFT) | (1 << GX_OAM_ATTR01_HF_SHIFT) | (0 <<
                                                                               GX_OAM_ATTR01_VF_SHIFT),
    GX_OAM_EFFECT_FLIP_V =
        (0 << GX_OAM_ATTR01_RSENABLE_SHIFT) | (0 << GX_OAM_ATTR01_HF_SHIFT) | (1 <<
                                                                               GX_OAM_ATTR01_VF_SHIFT),
    GX_OAM_EFFECT_FLIP_HV =
        (0 << GX_OAM_ATTR01_RSENABLE_SHIFT) | (1 << GX_OAM_ATTR01_HF_SHIFT) | (1 <<
                                                                               GX_OAM_ATTR01_VF_SHIFT),
    GX_OAM_EFFECT_AFFINE = (1 << GX_OAM_ATTR01_RSENABLE_SHIFT),
    GX_OAM_EFFECT_NODISPLAY = (2 << GX_OAM_ATTR01_RSENABLE_SHIFT),
    GX_OAM_EFFECT_AFFINE_DOUBLE = (3 << GX_OAM_ATTR01_RSENABLE_SHIFT)
}
GXOamEffect;

#define GX_OAM_EFFECT_ASSERT(x)                   \
    SDK_ASSERT( (x) == GX_OAM_EFFECT_NONE      || \
                (x) == GX_OAM_EFFECT_FLIP_H    || \
                (x) == GX_OAM_EFFECT_FLIP_V    || \
                (x) == GX_OAM_EFFECT_FLIP_HV   || \
                (x) == GX_OAM_EFFECT_AFFINE    || \
                (x) == GX_OAM_EFFECT_NODISPLAY || \
                (x) == GX_OAM_EFFECT_AFFINE_DOUBLE )


//
// Parameters for G2_SetOBJMode and G2_SetOBJAttr
//
typedef enum
{
    GX_OAM_MODE_NORMAL = 0,
    GX_OAM_MODE_XLU = 1,
    GX_OAM_MODE_OBJWND = 2,
    GX_OAM_MODE_BITMAPOBJ = 3
}
GXOamMode;

#define GX_OAM_MODE_ASSERT(x) \
    SDK_MINMAX_ASSERT(x, GX_OAM_MODE_NORMAL, GX_OAM_MODE_BITMAPOBJ)

#define GX_OAM_PRIORTY_ASSERT(x) \
    SDK_MINMAX_ASSERT(x, 0, 3)


#define GXOamAttrArray                     ((GXOamAttr*)HW_OAM)
#define GXOamAffineArray                   ((GXOamAffine*)HW_OAM)



/* if include from Other Environment for exsample VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))


//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

static void G2_SetOBJPosition(GXOamAttr *oam, int x, int y);
static void G2_SetOBJPriority(GXOamAttr *oam, int priority);
static void G2_SetOBJMode(GXOamAttr *oam, GXOamMode mode, int cParam);
static void G2_SetOBJEffect(GXOamAttr *oam, GXOamEffect effect, int rsParam);
static void G2_SetOBJShape(GXOamAttr *oam, GXOamShape shape);
static void G2_SetOBJCharName(GXOamAttr *oam, int name);
static void G2_SetOBJColorMode(GXOamAttr *oam, GXOamColorMode color);
static void G2_OBJMosaic(GXOamAttr *oam, BOOL enable);
static void G2_SetOBJAttr(GXOamAttr *oam,
                          int x,
                          int y,
                          int priority,
                          GXOamMode mode,
                          BOOL mosaic,
                          GXOamEffect effect,
                          GXOamShape shape,
                          GXOamColorMode color, int charName, int cParam, int rsParam);
static void G2_SetOBJAffine(GXOamAffine *oam, const MtxFx22 *mtx);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJPosition

  Description:  Sets the position for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                x         X coordinate
                y         Y coordinate

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJPosition(GXOamAttr *oam, int x, int y)
{
    oam->attr01 = ((oam->attr01 & ~(GX_OAM_ATTR01_Y_MASK | GX_OAM_ATTR01_X_MASK)) |
                   (y & GX_OAM_ATTR01_Y_MASK) |
                   ((x & (GX_OAM_ATTR01_X_MASK >> GX_OAM_ATTR01_X_SHIFT)) <<
                    GX_OAM_ATTR01_X_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJPosition

  Description:  Gets the position for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute

  Returns:      x         pointer to get X coordinate.
                y         pointer to get Y coordinate.
 *---------------------------------------------------------------------------*/
static inline void G2_GetOBJPosition(const GXOamAttr *oam, u32 *x, u32 *y)
{
    SDK_NULL_ASSERT(oam);
    SDK_NULL_ASSERT(x);
    SDK_NULL_ASSERT(y);

    *x = (oam->attr01 & GX_OAM_ATTR01_X_MASK) >> GX_OAM_ATTR01_X_SHIFT;
    *y = oam->attr01 & GX_OAM_ATTR01_Y_MASK;
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJPriority

  Description:  Sets the priority for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                priority  priority

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJPriority(GXOamAttr *oam, int priority)
{
    GX_OAM_PRIORTY_ASSERT(priority);

    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_PRIORITY_MASK) |
                       (priority << GX_OAM_ATTR2_PRIORITY_SHIFT));
}

/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJPriority

  Description:  Gets the priority for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute

  Returns:      priority of Object.
 *---------------------------------------------------------------------------*/
static inline int G2_GetOBJPriority(const GXOamAttr *oam)
{
    SDK_NULL_ASSERT(oam);

    return (oam->attr2 & GX_OAM_ATTR2_PRIORITY_MASK) >> GX_OAM_ATTR2_PRIORITY_SHIFT;
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJMode

  Description:  Sets the mode for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                mode      OBJ mode(normal/xlu/objwindow/bitmapobj)
                cParam    color parameter

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJMode(GXOamAttr *oam, GXOamMode mode, int cParam)
{
    GX_OAM_MODE_ASSERT(mode);
    GX_OAM_CPARAM_ASSERT(cParam);

    oam->attr01 = ((oam->attr01 & ~GX_OAM_ATTR01_MODE_MASK) | (mode << GX_OAM_ATTR01_MODE_SHIFT));

    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_CPARAM_MASK) |
                       (cParam << GX_OAM_ATTR2_CPARAM_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJMode

  Description:  Gets the mode for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute

  Returns:      OBJ mode(normal/xlu/objwindow/bitmapobj)
 *---------------------------------------------------------------------------*/
static inline GXOamMode G2_GetOBJMode(const GXOamAttr *oam)
{
    SDK_NULL_ASSERT(oam);

    return (GXOamMode)((oam->attr01 & GX_OAM_ATTR01_MODE_MASK) >> GX_OAM_ATTR01_MODE_SHIFT);
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJColorParam

  Description:  Gets the color parameter for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute

  Returns:      color parameter
 *---------------------------------------------------------------------------*/
static inline int G2_GetOBJColorParam(const GXOamAttr *oam)
{
    SDK_NULL_ASSERT(oam);

    return (oam->attr2 & GX_OAM_ATTR2_CPARAM_MASK) >> GX_OAM_ATTR2_CPARAM_SHIFT;
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJEffect

  Description:  Sets the effect for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                effect    specify an effect(none/flip/affine/nodisplay/affine double)
                rsParam   select an affine transformation(0-31) if affine effect specified

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJEffect(GXOamAttr *oam, GXOamEffect effect, int rsParam)
{
    GX_OAM_EFFECT_ASSERT(effect);
    GX_OAM_RSPARAM_ASSERT(rsParam);

    if (GX_OAM_EFFECT_AFFINE != effect && GX_OAM_EFFECT_AFFINE_DOUBLE != effect)
    {
        oam->attr01 = ((oam->attr01 & ~(GX_OAM_ATTR01_RSENABLE_MASK | GX_OAM_ATTR01_RS_MASK)) |
                       effect);
    }
    else
    {
        oam->attr01 = ((oam->attr01 & ~(GX_OAM_ATTR01_RSENABLE_MASK | GX_OAM_ATTR01_RS_MASK)) |
                       effect | (rsParam << GX_OAM_ATTR01_RS_SHIFT));
    }
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJEffect

  Description:  Gets the effect for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute

  Returns:      specify an effect(none/flip/affine/nodisplay/affine double)
 *---------------------------------------------------------------------------*/
static inline GXOamEffect G2_GetOBJEffect(const GXOamAttr *oam)
{
    GXOamEffect effect;

    SDK_NULL_ASSERT(oam);

    effect = (GXOamEffect)(oam->attr01 & GX_OAM_ATTR01_RSENABLE_MASK);

    if (effect == GX_OAM_EFFECT_AFFINE || effect == GX_OAM_EFFECT_AFFINE_DOUBLE)
    {
        return effect;
    }

    return (GXOamEffect)(effect | (oam->attr01 & GX_OAM_ATTR01_FLIP_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJShape

  Description:  Sets the size and shape for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                shape     specify size and shape of the Object

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJShape(GXOamAttr *oam, GXOamShape shape)
{
    GX_OAM_SHAPE_ASSERT(shape);

    oam->attr01 = ((oam->attr01 & ~(GX_OAM_ATTR01_SHAPE_MASK | GX_OAM_ATTR01_SIZE_MASK)) | shape);
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJShape

  Description:  Gets the size and shape for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute

  Returns:      shape     specify size and shape of the Object
 *---------------------------------------------------------------------------*/
static inline GXOamShape G2_GetOBJShape(const GXOamAttr *oam)
{
    SDK_NULL_ASSERT(oam);

    return (GXOamShape)(oam->attr01 & (GX_OAM_ATTR01_SHAPE_MASK | GX_OAM_ATTR01_SIZE_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJCharName

  Description:  Sets the character name for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                name      the head character name of an OBJ

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJCharName(GXOamAttr *oam, int name)
{
    GX_OAM_CHARNAME_ASSERT(name);

    oam->attr2 = (u16)((oam->attr2 & ~GX_OAM_ATTR2_NAME_MASK) | name);
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJCharName

  Description:  Gets the character name for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute

  Returns:      the head character name of an OBJ
 *---------------------------------------------------------------------------*/
static inline int G2_GetOBJCharName(const GXOamAttr *oam)
{
    SDK_NULL_ASSERT(oam);

    return oam->attr2 & GX_OAM_ATTR2_NAME_MASK;
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJColorMode

  Description:  Sets color mode for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                enable    color mode

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJColorMode(GXOamAttr *oam, GXOamColorMode color)
{
    GX_OAM_COLORMODE_ASSERT(color);
    SDK_WARNING(!(GX_OAM_COLORMODE_256 == color &&
                  (oam->attr01 & GX_OAM_ATTR01_MODE_MASK) == GX_OAM_ATTR01_MODE_MASK),
                "Only GX_OAM_COLORMODE_16 can be specified with GX_OAM_MODE_BITMAPOBJ.");

    oam->attr01 = ((oam->attr01 & ~GX_OAM_ATTR01_CM_MASK) | (color << GX_OAM_ATTR01_CM_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJColorMode

  Description:  Gets color mode for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute

  Returns:      color mode
 *---------------------------------------------------------------------------*/
static inline GXOamColorMode G2_GetOBJColorMode(const GXOamAttr *oam)
{
    SDK_NULL_ASSERT(oam);

    return (GXOamColorMode)((oam->attr01 & GX_OAM_ATTR01_CM_MASK) >> GX_OAM_ATTR01_CM_SHIFT);
}


/*---------------------------------------------------------------------------*
  Name:         G2_OBJMosaic

  Description:  Enable/Disable mosaic on an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                enable    enable/disable mosaic

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_OBJMosaic(GXOamAttr *oam, BOOL enable)
{
    if (enable)
    {
        oam->attr01 |= (1 << GX_OAM_ATTR01_MOSAIC_SHIFT);
    }
    else
    {
        oam->attr01 &= ~(1 << GX_OAM_ATTR01_MOSAIC_SHIFT);
    }
}


/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJAttr

  Description:  Sets a bunch of attributes for an OBJ.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                x         X coordinate
                y         Y coordinate
                priority  priority
                mode      OBJ mode(normal/xlu/objwindow/bitmapobj)
                mosaic    mosaic
                effect    specify an effect(none/flip/affine/nodisplay/affine double)
                shape     specify size and shape of the Object
                color     color mode
                charName  the head character name of an OBJ
                cParam    color parameter
                rsParam   select an affine transformation(0-31) if affine effect specified

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJAttr(GXOamAttr *oam,
                                 int x,
                                 int y,
                                 int priority,
                                 GXOamMode mode,
                                 BOOL mosaic,
                                 GXOamEffect effect,
                                 GXOamShape shape,
                                 GXOamColorMode color, int charName, int cParam, int rsParam)
{
// set rsParam or not
#define G2_SET_OBJ_ATTR_AFMODE_AFFINE_()  (rsParam << GX_OAM_ATTR01_RS_SHIFT) |
#define G2_SET_OBJ_ATTR_AFMODE_NORMAL_()

// set color or not
#define G2_SET_OBJ_ATTR_CLMODE_CHARACTOR_() (color << GX_OAM_ATTR01_CM_SHIFT) |
#define G2_SET_OBJ_ATTR_CLMODE_BITMAP_()

// af_t : AFFINE or NORMAL
// bm_t : CHARACTOR or BITMAP
#define G2_SET_OBJ_ATTR_(af_t, bm_t) \
    oam->attr01 = (u32) (G2_SET_OBJ_ATTR_AFMODE_##af_t##_() \
                         G2_SET_OBJ_ATTR_CLMODE_##bm_t##_() \
                         ((y & (GX_OAM_ATTR01_Y_MASK >> GX_OAM_ATTR01_Y_SHIFT)) << GX_OAM_ATTR01_Y_SHIFT) | \
                         (mode << GX_OAM_ATTR01_MODE_SHIFT)                                               | \
                         (mosaic << GX_OAM_ATTR01_MOSAIC_SHIFT)                                           | \
                         shape                                                                            | \
                         ((x & (GX_OAM_ATTR01_X_MASK >> GX_OAM_ATTR01_X_SHIFT)) << GX_OAM_ATTR01_X_SHIFT) | \
                         effect);


    GX_OAM_PRIORTY_ASSERT(priority);
    GX_OAM_MODE_ASSERT(mode);
    GX_OAM_EFFECT_ASSERT(effect);
    GX_OAM_SHAPE_ASSERT(shape);
    GX_OAM_COLORMODE_ASSERT(color);
    GX_OAM_CPARAM_ASSERT(cParam);
    SDK_ASSERT(mosaic == 0 || mosaic == 1);
    SDK_WARNING(!(mode == GX_OAM_MODE_BITMAPOBJ && color == GX_OAM_COLORMODE_256),
                "Only GX_OAM_COLORMODE_16 can be specified with GX_OAM_MODE_BITMAPOBJ.");

    // To be small code by optimization when constants specified, I hope.

    // Set color parameter then Character OBJ, and set affine parameter then affine mode
    if (GX_OAM_EFFECT_AFFINE == effect || GX_OAM_EFFECT_AFFINE_DOUBLE == effect)
    {
        if (GX_OAM_MODE_BITMAPOBJ == mode)
        {
            G2_SET_OBJ_ATTR_(AFFINE, BITMAP);
        }
        else
        {
            G2_SET_OBJ_ATTR_(AFFINE, CHARACTOR);
        }
    }
    else
    {
        if (GX_OAM_MODE_BITMAPOBJ == mode)
        {
            G2_SET_OBJ_ATTR_(NORMAL, BITMAP);
        }
        else
        {
            G2_SET_OBJ_ATTR_(NORMAL, CHARACTOR);
        }
    }

    oam->attr2 = (u16)((charName << GX_OAM_ATTR2_NAME_SHIFT) |
                       (priority << GX_OAM_ATTR2_PRIORITY_SHIFT) |
                       (cParam << GX_OAM_ATTR2_CPARAM_SHIFT));

#undef  G2_SET_OBJ_ATTR_AFMODE_AFFINE_
#undef  G2_SET_OBJ_ATTR_AFMODE_NORMAL_
#undef  G2_SET_OBJ_ATTR_CLMODE_CHARACTOR_
#undef  G2_SET_OBJ_ATTR_CLMODE_BITMAP_
#undef  G2_SET_OBJ_ATTR_
}

/*---------------------------------------------------------------------------*
  Name:         G2_SetOBJAffine

  Description:  Sets affine parameters.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                mtx       a pointer to a 2x2 matrix for affine transformation of OBJs

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_SetOBJAffine(GXOamAffine *oam, const MtxFx22 *mtx)
{
    SDK_MINMAX_ASSERT(mtx->_00, -128 * FX32_ONE, 128 * FX32_ONE - 1);
    SDK_MINMAX_ASSERT(mtx->_01, -128 * FX32_ONE, 128 * FX32_ONE - 1);
    SDK_MINMAX_ASSERT(mtx->_10, -128 * FX32_ONE, 128 * FX32_ONE - 1);
    SDK_MINMAX_ASSERT(mtx->_11, -128 * FX32_ONE, 128 * FX32_ONE - 1);

    // Affine transform parmeters (PA,PB,PC,PD) are in s7.8 format.
    // Since fx32 is in s19.12 format, shift them right by 4 bits.
    oam->PA = (s16)(mtx->_00 >> 4);
    oam->PB = (s16)(mtx->_01 >> 4);
    oam->PC = (s16)(mtx->_10 >> 4);
    oam->PD = (s16)(mtx->_11 >> 4);
}


/*---------------------------------------------------------------------------*
  Name:         G2_GetOBJAffine

  Description:  Get affine parameters.

  Arguments:    oam       pointer to (a mirror of) Object attribute
                mtx       a pointer to a 2x2 matrix for affine transformation of OBJs

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void G2_GetOBJAffine(const GXOamAffine *oam, MtxFx22 *mtx)
{
    // fx32 is in s19.12 format.
    // Since Affine transform parameters (PA,PB,PC,PD) are in s7.8 format, 
    // shift them leftward by 4 bits.
    mtx->_00 = (fx32)(oam->PA << 4);
    mtx->_01 = (fx32)(oam->PB << 4);
    mtx->_10 = (fx32)(oam->PC << 4);
    mtx->_11 = (fx32)(oam->PD << 4);
}



#endif // SDK_FROM_TOOL

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
