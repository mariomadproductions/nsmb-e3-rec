/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     gx.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: gx.h,v $
  Revision 1.107  2007/11/26 08:14:56  okubata_ryoma
  Strengthened restrictions on the GX_SetVCount function

  Revision 1.106  2007/10/19 05:11:01  yosizaki
  Fixed warning in GX_SetVCount().

  Revision 1.105  2007/10/18 12:16:14  seiki_masashi
  Improved condition checks in the GX_SetVCount function.

  Revision 1.104  2007/02/23 04:34:45  okubata_ryoma
  Added controls to the GX_SetVCount function

  Revision 1.103  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.102  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.101  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.100  2005/02/03 00:43:41  takano_makoto
  Bug fix. GX_GetOBJVRamModeBmp function return value was wrong type.

  Revision 1.99  2005/01/11 07:53:17  takano_makoto
  Fixed copyright header.

  Revision 1.98  2005/01/05 23:58:30  takano_makoto
  Eliminated warning.

  Revision 1.97  2004/12/27 04:45:05  takano_makoto
  Added get function for register

  Revision 1.96  2004/11/02 14:43:33  takano_makoto
  Fixed comments.

  Revision 1.95  2004/10/21 13:45:07  yasu
  Added GX_GetVCountEqVal( )
  Made aliases for GX_*VCounter* <-> GX_*VCount*

  Revision 1.94  2004/10/08 12:52:33  takano_makoto
  Added GX_IsDispOn (merge to NitroSDK_2_00rc1_branch)

  Revision 1.93.14.1  2004/10/08 12:22:25  takano_makoto
  Added GX_IsDispOn

  Revision 1.93  2004/08/27 09:46:48  takano_makoto
  Minor fixes.

  Revision 1.92  2004/08/27 07:32:51  takano_makoto
  Changed GX_DMAID to variable for compatibility.

  Revision 1.91  2004/08/24 10:14:46  takano_makoto
  Added comment.

  Revision 1.90  2004/08/18 05:08:14  takano_makoto
  Added inline to GX_InitEx() and GX_GetDefaultDMA().

  Revision 1.89  2004/08/10 12:49:22  takano_makoto
  Made GX_DMA_NOT_USE available to use.

  Revision 1.88  2004/08/10 09:33:07  takano_makoto
  Minor revisions.

  Revision 1.87  2004/08/10 09:26:00  takano_makoto
  Removed GX_PowerLCD(), GX_PowerLCDTop(), GX_PowerLCDBot()

  Revision 1.86  2004/08/10 01:05:21  yada
  Changed GX_PowerLCD to GXi_PowerLCD

  Revision 1.85  2004/08/04 07:49:48  takano_makoto
  Added comment that indicates removal of GX_POWER_LCD_TOP, GX_POWER_LCD_BOT in near future.

  Revision 1.84  2004/08/03 10:17:02  takano_makoto
  Added GXS_OBJVRAMMODE_CHAR_ASSERT

  Revision 1.83  2004/08/03 02:42:18  takano_makoto
  Modified to not include nitro/mi.h if SDK_FROM_TOOL is defined.

  Revision 1.82  2004/07/28 12:29:15  takano_makoto
  Corrected ASSERT of GX_InitEx

  Revision 1.81  2004/07/28 12:23:16  takano_makoto
  Added ASSERT

  Revision 1.79  2004/07/27 10:32:16  takano_makoto
  Fixed bugs in GX_PowerGeometry() and GX_Power3D().

  Revision 1.78  2004/06/02 11:00:08  takano_makoto
  Reversed the logic of main LCD and sub-LCD

  Revision 1.77  2004/05/21 09:35:28  kitani_toshikazu
  Fixed GXOBJVRamModeChar definition to avoid VC7 warning.

  Revision 1.76  2004/05/21 04:33:38  takano_makoto
  Added GX_LCD_SIZE_X and GX_LCD_SIZE_Y

  Revision 1.75  2004/05/14 11:52:57  takano_makoto
  Added #ifndef SDK_FROM_TOOL for VC or BCB.

  Revision 1.74  2004/04/01 10:27:32  takano_makoto
  Fixed GX(S)_HBlankOBJProc().

  Revision 1.73  2004/02/18 07:04:10  nishida_kenji
  Removed magic numbers.

  Revision 1.72  2004/02/17 08:12:26  nishida_kenji
  Minor fixes.

  Revision 1.71  2004/02/12 10:56:04  yasu
  New location of include files ARM9/ARM7

  Revision 1.70  2004/02/05 07:09:03  yasu
  Changed SDK prefix iris -> nitro

  Revision 1.69  2004/01/29 02:16:00  nishida_kenji
  GX_DISPMODE_OFF for GX_SetGraphicsMode is now obsolete.
  Use of GX_DispOff instead.

  Revision 1.68  2004/01/29 01:15:23  nishida_kenji
  Added GX_DispOn, GX_DispOff, GXS_DispOn, GXS_DispOff.
  Also, GX_BlankScr is now obsolete, please use GX_DispOn/GX_DispOff instead.

  Revision 1.67  2004/01/27 11:13:58  nishida_kenji
  Appended 'static' to inline function prototypes.

  Revision 1.66  2004/01/26 13:33:34  nishida_kenji
  Added GX_HBlankOBJProc

  Revision 1.65  2004/01/26 10:33:39  nishida_kenji
  Fixed GX_SetOBJVRamModeBmp

  Revision 1.64  2004/01/26 04:28:16  nishida_kenji
  Revised GXOBJVRamModeBmp

  Revision 1.63  2004/01/26 02:38:08  nishida_kenji
  Added APIs for the sub 2D engine, and revised GX_SetPower.

  Revision 1.59  2004/01/18 06:46:26  nishida_kenji
  Changed GX_SetOBJVRAMModeChar to GX_SetOBJVRamModeChar
  Changed GX_SetOBJVRAMModeBmp to GX_SetOBJVRmaModeBmp

  Revision 1.58  2004/01/17 07:17:12  nishida_kenji
  Removed external include guards

  Revision 1.57  2004/01/17 02:28:38  nishida_kenji
  Converted 'inline' to 'static inline' in header files

  Revision 1.56  2004/01/14 11:23:55  nishida_kenji
  Fixed comments

  Revision 1.55  2004/01/10 08:49:38  nishida_kenji
  Added GX_GetPower()

  Revision 1.54  2003/12/26 00:55:09  nishida_kenji
  Minor fix

  Revision 1.53  2003/12/25 11:00:10  nishida_kenji
  Converted with GX_APIChangeFrom031212-2.pl

  Revision 1.52  2003/12/25 00:19:29  nishida_kenji
  Converted INLINE to inline

  Revision 1.51  2003/12/24 10:47:12  nishida_kenji
  Minor fix

  Revision 1.50  2003/12/24 10:35:50  nishida_kenji
  Revised APIs for interrupt requirement generation

  Revision 1.49  2003/12/24 08:12:55  nishida_kenji
  Revised GX_SetVCount

  Revision 1.48  2003/12/17 09:00:20  nishida_kenji
  Totally revised APIs.
  build/buildtools/GX_APIChangeFrom031212.pl would help you change your program to some extent.

  Revision 1.47  2003/12/17 08:50:33  nishida_kenji
  Revised comments

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_GX_GX_H_
#define NITRO_GX_GX_H_

#include "nitro/gx/gxcommon.h"
#include "nitro/hw/ARM9/ioreg_GX.h"
#include "nitro/hw/ARM9/ioreg_GXS.h"

#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))
#include "nitro/mi.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type Definitions
//----------------------------------------------------------------------------

#define     GX_LCD_SIZE_X       256
#define     GX_LCD_SIZE_Y       192


//----------------------------------------------------------------------------
//    Parameters for GX_SetGraphicsMode
//----------------------------------------------------------------------------
// Display control register (MAIN engine).
typedef union
{
    u32     raw;
    struct
    {
        u32     bgMode:3;
        u32     bg0_2d3d:1;
        u32     objMapChar:1;
        u32     objMapBmp:2;
        u32     blankScr:1;
        u32     visiblePlane:5;
        u32     visibleWnd:3;
        u32     dispMode:4;
        u32     extObjMapChar:2;
        u32     extObjMapBmp:1;
        u32     hBlankObjProc:1;
        u32     bgCharOffset:3;
        u32     bgScrOffset:3;
        u32     bgExtPltt:1;
        u32     objExtPltt:1;
    };
}
GXDispCnt;

// Display control register (SUB engine).
typedef union
{
    u32     raw;
    struct
    {
        u32     bgMode:3;
        u32     _reserve1:1;
        u32     objMapChar:1;
        u32     objMapBmp:2;
        u32     blankScr:1;
        u32     visiblePlane:5;
        u32     visibleWnd:3;
        u32     dispMode:1;
        u32     _reserve2:3;
        u32     extObjMapChar:2;
        u32     _reserve3:1;
        u32     hBlankObjProc:1;
        u32     _reserve4:6;
        u32     bgExtPltt:1;
        u32     objExtPltt:1;
    };
}
GXSDispCnt;


typedef enum
{
    GX_BGMODE_0 = 0,
    GX_BGMODE_1 = 1,
    GX_BGMODE_2 = 2,
    GX_BGMODE_3 = 3,
    GX_BGMODE_4 = 4,
    GX_BGMODE_5 = 5,
    GX_BGMODE_6 = 6
}
GXBGMode;

#define GX_BGMODE_ASSERT(x)           \
    SDK_MINMAX_ASSERT(x, GX_BGMODE_0, GX_BGMODE_6)

typedef enum
{
    GX_BG0_AS_2D = 0,
    GX_BG0_AS_3D = 1
}
GXBG0As;

#define GX_BG0_AS_ASSERT(x)            \
    SDK_MINMAX_ASSERT(x, GX_BG0_AS_2D, GX_BG0_AS_3D)

typedef enum
{
    GX_DISPMODE_GRAPHICS = 0x01,
    GX_DISPMODE_VRAM_A = 0x02,
    GX_DISPMODE_VRAM_B = 0x06,
    GX_DISPMODE_VRAM_C = 0x0a,
    GX_DISPMODE_VRAM_D = 0x0e,
    GX_DISPMODE_MMEM = 0x03
}
GXDispMode;

// GX_DISPMODE_OFF is obsolete, use GX_DispOff instead.
#define GX_DISPMODE_OFF  ((GXDispMode)0x00)

#define GX_DISPMODE_ASSERT(x)                  \
    SDK_ASSERT( (x) == GX_DISPMODE_OFF      || \
                (x) == GX_DISPMODE_GRAPHICS || \
                (x) == GX_DISPMODE_VRAM_A   || \
                (x) == GX_DISPMODE_VRAM_B   || \
                (x) == GX_DISPMODE_VRAM_C   || \
                (x) == GX_DISPMODE_VRAM_D   || \
                (x) == GX_DISPMODE_MMEM )

//----------------------------------------------------------------------------
//    Parameters for GX_SetOBJVRamModeChar
//----------------------------------------------------------------------------
typedef enum
{
    GX_OBJVRAMMODE_CHAR_2D = (0 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (0 << REG_GX_DISPCNT_EXOBJ_SHIFT),
    GX_OBJVRAMMODE_CHAR_1D_32K =
        (1 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (0 << REG_GX_DISPCNT_EXOBJ_SHIFT),
    GX_OBJVRAMMODE_CHAR_1D_64K =
        (1 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (1 << REG_GX_DISPCNT_EXOBJ_SHIFT),
    GX_OBJVRAMMODE_CHAR_1D_128K =
        (1 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (2 << REG_GX_DISPCNT_EXOBJ_SHIFT),
    GX_OBJVRAMMODE_CHAR_1D_256K =
        (1 << REG_GX_DISPCNT_OBJMAP_SHIFT) | (3 << REG_GX_DISPCNT_EXOBJ_SHIFT)
}
GXOBJVRamModeChar;

#define GX_OBJVRAMMODE_CHAR_ASSERT(x)              \
    SDK_ASSERT(x == GX_OBJVRAMMODE_CHAR_2D      || \
               x == GX_OBJVRAMMODE_CHAR_1D_32K  || \
               x == GX_OBJVRAMMODE_CHAR_1D_64K  || \
               x == GX_OBJVRAMMODE_CHAR_1D_128K || \
               x == GX_OBJVRAMMODE_CHAR_1D_256K)

#define GXS_OBJVRAMMODE_CHAR_ASSERT(x)             \
    SDK_ASSERT(x == GX_OBJVRAMMODE_CHAR_2D      || \
               x == GX_OBJVRAMMODE_CHAR_1D_32K  || \
               x == GX_OBJVRAMMODE_CHAR_1D_64K  || \
               x == GX_OBJVRAMMODE_CHAR_1D_128K)


//----------------------------------------------------------------------------
//    Parameters for GX_SetOBJVRamModeBmp
//----------------------------------------------------------------------------
typedef enum
{
    GX_OBJVRAMMODE_BMP_2D_W128 =
        (0 << (REG_GX_DISPCNT_OBJMAP_SHIFT + 1)) | (0 << (REG_GX_DISPCNT_EXOBJ_SHIFT + 2)),
    GX_OBJVRAMMODE_BMP_2D_W256 =
        (1 << (REG_GX_DISPCNT_OBJMAP_SHIFT + 1)) | (0 << (REG_GX_DISPCNT_EXOBJ_SHIFT + 2)),
    GX_OBJVRAMMODE_BMP_1D_128K =
        (2 << (REG_GX_DISPCNT_OBJMAP_SHIFT + 1)) | (0 << (REG_GX_DISPCNT_EXOBJ_SHIFT + 2)),
    GX_OBJVRAMMODE_BMP_1D_256K =
        (2 << (REG_GX_DISPCNT_OBJMAP_SHIFT + 1)) | (1 << (REG_GX_DISPCNT_EXOBJ_SHIFT + 2))
}
GXOBJVRamModeBmp;


// OBSOLETE: These macros will be removed in the future release.
#define GX_OBJVRAMMODE_BMP_2D_W128_32K GX_OBJVRAMMODE_BMP_2D_W128
#define GX_OBJVRAMMODE_BMP_2D_W256_32K GX_OBJVRAMMODE_BMP_2D_W256

#define GX_OBJVRAMMODE_BMP_ASSERT(x)                  \
    SDK_ASSERT(x == GX_OBJVRAMMODE_BMP_2D_W128_32K || \
               x == GX_OBJVRAMMODE_BMP_2D_W256_32K || \
               x == GX_OBJVRAMMODE_BMP_1D_128K     || \
               x == GX_OBJVRAMMODE_BMP_1D_256K)

#define GXS_OBJVRAMMODE_BMP_ASSERT(x)             \
    SDK_ASSERT(x == GX_OBJVRAMMODE_BMP_2D_W128 || \
               x == GX_OBJVRAMMODE_BMP_2D_W256 || \
               x == GX_OBJVRAMMODE_BMP_1D_128K)

//----------------------------------------------------------------------------
//    Parameters for GX_SetVisiblePlane
//----------------------------------------------------------------------------
typedef enum
{
    GX_PLANEMASK_NONE = 0x00,
    GX_PLANEMASK_BG0 = 0x01,
    GX_PLANEMASK_BG1 = 0x02,
    GX_PLANEMASK_BG2 = 0x04,
    GX_PLANEMASK_BG3 = 0x08,
    GX_PLANEMASK_OBJ = 0x10
}
GXPlaneMask;

#define GX_PLANEMASK_ASSERT(x) SDK_MINMAX_ASSERT(x, GX_PLANEMASK_NONE, 0x1f)

//----------------------------------------------------------------------------
//    Parameters for GX_SetVisibleWnd
//----------------------------------------------------------------------------
typedef enum
{
    GX_WNDMASK_NONE = 0x00,
    GX_WNDMASK_W0 = 0x01,
    GX_WNDMASK_W1 = 0x02,
    GX_WNDMASK_OW = 0x04
}
GXWndMask;

#define GX_WNDMASK_ASSERT(x) SDK_MINMAX_ASSERT(x, GX_WNDMASK_NONE, 0x7)

//----------------------------------------------------------------------------
//    Parameters for GX_SetBGCharOffset
//----------------------------------------------------------------------------
typedef enum
{
    GX_BGCHAROFFSET_0x00000 = 0x00,
    GX_BGCHAROFFSET_0x10000 = 0x01,
    GX_BGCHAROFFSET_0x20000 = 0x02,
    GX_BGCHAROFFSET_0x30000 = 0x03,
    GX_BGCHAROFFSET_0x40000 = 0x04,
    GX_BGCHAROFFSET_0x50000 = 0x05,
    GX_BGCHAROFFSET_0x60000 = 0x06,
    GX_BGCHAROFFSET_0x70000 = 0x07
}
GXBGCharOffset;

#define GX_BGCHAROFFSET_ASSERT(x) \
    SDK_MINMAX_ASSERT(x, GX_BGCHAROFFSET_0x00000, GX_BGCHAROFFSET_0x70000)

//----------------------------------------------------------------------------
//    Parameters for GX_SetBGScrOffset
//----------------------------------------------------------------------------
typedef enum
{
    GX_BGSCROFFSET_0x00000 = 0x00,
    GX_BGSCROFFSET_0x10000 = 0x01,
    GX_BGSCROFFSET_0x20000 = 0x02,
    GX_BGSCROFFSET_0x30000 = 0x03,
    GX_BGSCROFFSET_0x40000 = 0x04,
    GX_BGSCROFFSET_0x50000 = 0x05,
    GX_BGSCROFFSET_0x60000 = 0x06,
    GX_BGSCROFFSET_0x70000 = 0x07
}
GXBGScrOffset;

#define GX_BGSCROFFSET_ASSERT(x) \
    SDK_MINMAX_ASSERT(x, GX_BGSCROFFSET_0x00000, GX_BGSCROFFSET_0x70000)

//----------------------------------------------------------------------------
//    Parameters for GX_SetPower
//----------------------------------------------------------------------------
typedef enum
{
    GX_POWER_OFF = 0,

    GX_POWER_2D_MAIN = 1 << REG_GX_POWCNT_E2DG_SHIFT,
    GX_POWER_2D_SUB = 1 << REG_GX_POWCNT_E2DGB_SHIFT,

    GX_POWER_RE = 1 << REG_GX_POWCNT_RE_SHIFT,
    GX_POWER_GE = 1 << REG_GX_POWCNT_GE_SHIFT,

    GX_POWER_2D = GX_POWER_2D_MAIN | GX_POWER_2D_SUB,
    GX_POWER_3D = GX_POWER_RE | GX_POWER_GE,

    GX_POWER_ALL = GX_POWER_2D | GX_POWER_3D
/*
    GX_POWER_LCD_TOP = 1 << REG_GX_POWCNT_LCD_SHIFT,        // Don't use. This will be removed in the near future.
    GX_POWER_LCD_BOT = 1 << REG_GX_POWCNT_LCDB_SHIFT,       // Don't use. This will be removed in the near future.
    GX_POWER_LCD     = GX_POWER_LCD_TOP | GX_POWER_LCD_BOT  // Don't use. This will be removed in the near future.
*/
}
GXPower;


#define GX_POWER_ASSERT(x) SDK_ASSERTMSG( ( ( (x) & ~GX_POWER_ALL ) == 0  ), \
                                          "GX_POWER_LCD is obsolete. please use PM_SetLCDPower()\n" )

//----------------------------------------------------------------------------
//    Parameters for GX_SetDispSelect, GX_GetDispSelect
//----------------------------------------------------------------------------
typedef enum
{
    GX_DISP_SELECT_SUB_MAIN = 0,
    GX_DISP_SELECT_MAIN_SUB = 1
}
GXDispSelect;

#define GX_DISP_SELECT_ASSERT(x) SDK_MINMAX_ASSERT(x, 0, 1)


/* If including from other environment, for example VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

//----------------------------------------------------------------------------
// Function Declarations
//----------------------------------------------------------------------------

// reg_GX_POWCNT
static void GX_SetPower(int gxbit_power /* GXPower */ );
static GXPower GX_GetPower(void);

static void GX_Power2DMain(BOOL enable);
static void GX_Power2DSub(BOOL enable);

static void GX_PowerRender(BOOL enable);
static void GX_PowerGeometry(BOOL enable);

static void GXi_PowerLCD(BOOL enable);
static void GX_Power2D(BOOL enable);
static void GX_Power3D(BOOL enable);

static void GX_SetDispSelect(GXDispSelect sel);
static GXDispSelect GX_GetDispSelect(void);

// reg_GX_DISPSTAT
static s32 GX_IsHBlank(void);
s32     GX_HBlankIntr(BOOL enable);
static s32 GX_IsVBlank(void);
s32     GX_VBlankIntr(BOOL enable);
static s32 GX_IsVCountEq(void);
static void GX_VCountEqIntr(BOOL enable);
void    GX_SetVCountEqVal(s32 val);
static s32 GX_GetVCountEqVal(void);

#define GX_IsVCounterEq     GX_IsVCountEq
#define GX_VCounterEqIntr   GX_VCountEqIntr
#define GX_SetVCounterEqVal GX_SetVCountEqVal
#define GX_GetVCounterEqVal GX_GetVCountEqVal

// reg_GX_VCOUNT
static s32 GX_GetVCount(void);
static void GX_SetVCount(s32 count);

void    GX_Init(void);
static void GX_InitEx(u32 dma_no);
u32     GX_SetDefaultDMA(u32 dma_no);
static u32 GX_GetDefaultDMA(void);

//
// Main 2D engine
//

// reg_GX_DISPCNT
void    GX_SetGraphicsMode(GXDispMode dispMode, GXBGMode bgMode, GXBG0As bg0_2d3d);
void    GX_DispOff(void);
void    GX_DispOn(void);
BOOL    GX_IsDispOn(void);

static void GX_SetVisiblePlane(int plane /* GXPlaneMask */ );
static void GX_SetVisibleWnd(int window /* GXWndMask */ );
static void GX_BlankScr(BOOL blank);

static GXBGScrOffset GX_GetBGScrOffset();
static void GX_SetBGScrOffset(GXBGScrOffset offset);

static GXBGCharOffset GX_GetBGCharOffset();
static void GX_SetBGCharOffset(GXBGCharOffset offset);

static void GX_SetOBJVRamModeChar(GXOBJVRamModeChar mode);
static void GX_SetOBJVRamModeBmp(GXOBJVRamModeBmp mode);

static void GX_HBlankOBJProc(BOOL proc);

// reg_GX_MASTER_BRIGHT
static void GX_SetMasterBrightness(int brightness);

//
// Sub 2D engine
//

void    GXS_SetGraphicsMode(GXBGMode bgMode);
static void GXS_DispOff(void);
static void GXS_DispOn(void);

static void GXS_SetVisiblePlane(int plane /* GXPlaneMask */ );
static void GXS_SetVisibleWnd(int window /* GXWndMask */ );

static void GXS_SetOBJVRamModeChar(GXOBJVRamModeChar mode);
static void GXS_SetOBJVRamModeBmp(GXOBJVRamModeBmp mode);

static void GXS_HBlankOBJProc(BOOL proc);

static void GXS_SetMasterBrightness(int brightness);

//
// Internal use
//
void    GXx_SetMasterBrightness_(vu16 *reg, int brightness);
int     GXx_GetMasterBrightness_(vu16 *reg);

//----------------------------------------------------------------------------
// Inline Function Implementation
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         GX_GetBGMode

  Description:  Gets the BG mode (MAIN engine).

  Arguments:    none

  Returns:      BG mode
 *---------------------------------------------------------------------------*/
static inline GXDispCnt GX_GetDispCnt(void)
{
    return *(const GXDispCnt *)REG_DISPCNT_ADDR;
}


/*---------------------------------------------------------------------------*
  Name:         GXS_GetBGMode

  Description:  Gets the BG mode (MAIN engine).

  Arguments:    none

  Returns:      BG mode
 *---------------------------------------------------------------------------*/
static inline GXSDispCnt GXS_GetDispCnt(void)
{
    return *(const GXSDispCnt *)REG_DB_DISPCNT_ADDR;
}


/*---------------------------------------------------------------------------*
  Name:         GX_GetBGScrOffset

  Description:  Gets the screen offset of BGs.

  Arguments:    none

  Returns:      Screen offset of BGs
 *---------------------------------------------------------------------------*/
static inline GXBGScrOffset GX_GetBGScrOffset()
{
    return (GXBGScrOffset)((reg_GX_DISPCNT & REG_GX_DISPCNT_BGSCREENOFFSET_MASK) >>
                           REG_GX_DISPCNT_BGSCREENOFFSET_SHIFT);
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetBGScrOffset

  Description:  Specifies the screen offset of BGs.

  Arguments:    offset:     Screen offset of BGs

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetBGScrOffset(GXBGScrOffset offset)
{
    GX_BGSCROFFSET_ASSERT(offset);
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~REG_GX_DISPCNT_BGSCREENOFFSET_MASK) |
                           (offset << REG_GX_DISPCNT_BGSCREENOFFSET_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         GX_GetBGCharOffset

  Description:  Gets the character offset of BGs.

  Arguments:    none

  Returns:      Character offset of BGs
 *---------------------------------------------------------------------------*/
static inline GXBGCharOffset GX_GetBGCharOffset()
{
    return (GXBGCharOffset)((reg_GX_DISPCNT & REG_GX_DISPCNT_BGCHAROFFSET_MASK)
                            >> REG_GX_DISPCNT_BGCHAROFFSET_SHIFT);
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetBGCharOffset

  Description:  Specifies the character offset of BGs.

  Arguments:    offset:     Character offset of BGs

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetBGCharOffset(GXBGCharOffset offset)
{
    GX_BGCHAROFFSET_ASSERT(offset);
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~REG_GX_DISPCNT_BGCHAROFFSET_MASK) |
                           (offset << REG_GX_DISPCNT_BGCHAROFFSET_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetVisiblePlane

  Description:  Specifies the planes to be visible (MAIN engine).

  Arguments:    plane:      set of visible planes

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetVisiblePlane(int plane)
{
    GX_PLANEMASK_ASSERT(plane);

    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~REG_GX_DISPCNT_DISPLAY_MASK) |
                           (plane << REG_GX_DISPCNT_DISPLAY_SHIFT));
}

/*---------------------------------------------------------------------------*
  Name:         GX_GetVisiblePlane

  Description:  Get the visible planes (MAIN engine).

  Arguments:    none

  Returns:      set of visible planes
 *---------------------------------------------------------------------------*/
static inline int GX_GetVisiblePlane(void)
{
    return (int)((reg_GX_DISPCNT & REG_GX_DISPCNT_DISPLAY_MASK) >> REG_GX_DISPCNT_DISPLAY_SHIFT);
}

/*---------------------------------------------------------------------------*
  Name:         GXS_SetVisiblePlane

  Description:  Specifies the planes to be visible (SUB engine).

  Arguments:    plane:      set of visible planes

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_SetVisiblePlane(int plane)
{
    GX_PLANEMASK_ASSERT(plane);

    reg_GXS_DB_DISPCNT = (u32)((reg_GXS_DB_DISPCNT & ~REG_GXS_DB_DISPCNT_DISPLAY_MASK) |
                               (plane << REG_GXS_DB_DISPCNT_DISPLAY_SHIFT));
}

/*---------------------------------------------------------------------------*
  Name:         GXS_GetVisiblePlane

  Description:  Get the visible planes (SUB engine).

  Arguments:    none

  Returns:      set of visible planes
 *---------------------------------------------------------------------------*/
static inline int GXS_GetVisiblePlane(void)
{
    return (int)((reg_GXS_DB_DISPCNT & REG_GXS_DB_DISPCNT_DISPLAY_MASK)
                 >> REG_GXS_DB_DISPCNT_DISPLAY_SHIFT);
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetVisibleWnd

  Description:  Specifies the windows to be visible (MAIN engine).

  Arguments:    plane:      set of visible windows

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetVisibleWnd(int window)
{
    GX_WNDMASK_ASSERT(window);

    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT &
                            ~(REG_GX_DISPCNT_W0_MASK |
                              REG_GX_DISPCNT_W1_MASK |
                              REG_GX_DISPCNT_OW_MASK)) | (window << REG_GX_DISPCNT_W0_SHIFT));
}

/*---------------------------------------------------------------------------*
  Name:         GX_GetVisibleWnd

  Description:  Get the visible windows (MAIN engine).

  Arguments:    None.

  Returns:      set of visible windows
 *---------------------------------------------------------------------------*/
static inline int GX_GetVisibleWnd(void)
{
    return (int)((reg_GX_DISPCNT & (REG_GX_DISPCNT_W0_MASK |
                                    REG_GX_DISPCNT_W1_MASK |
                                    REG_GX_DISPCNT_OW_MASK)) >> REG_GX_DISPCNT_W0_SHIFT);
}


/*---------------------------------------------------------------------------*
  Name:         GXS_SetVisibleWnd

  Description:  Specifies the windows to be visible (SUB engine).

  Arguments:    plane:      set of visible windows

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_SetVisibleWnd(int window)
{
    GX_WNDMASK_ASSERT(window);

    reg_GXS_DB_DISPCNT = (u32)((reg_GXS_DB_DISPCNT &
                                ~(REG_GXS_DB_DISPCNT_W0_MASK |
                                  REG_GXS_DB_DISPCNT_W1_MASK |
                                  REG_GXS_DB_DISPCNT_OW_MASK)) |
                               (window << REG_GXS_DB_DISPCNT_W0_SHIFT));
}

/*---------------------------------------------------------------------------*
  Name:         GXS_GetVisibleWnd

  Description:  Get the visible windows (SUB engine).

  Arguments:    None.

  Returns:      set of visible windows
 *---------------------------------------------------------------------------*/
static inline int GXS_GetVisibleWnd(void)
{
    return (int)((reg_GXS_DB_DISPCNT & (REG_GXS_DB_DISPCNT_W0_MASK |
                                        REG_GXS_DB_DISPCNT_W1_MASK |
                                        REG_GXS_DB_DISPCNT_OW_MASK))
                 >> REG_GXS_DB_DISPCNT_W0_SHIFT);
}



/*---------------------------------------------------------------------------*
  Name:         GX_SetOBJVRamModeChar

  Description:  Specifies the condition for OBJ-VRAM (ChrOBJ) (MAIN engine).

  Arguments:    mode:     select the size and the mapping mode for Character Object

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetOBJVRamModeChar(GXOBJVRamModeChar mode)
{
    GX_OBJVRAMMODE_CHAR_ASSERT(mode);

    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT &
                           ~(REG_GX_DISPCNT_EXOBJ_CH_MASK | REG_GX_DISPCNT_OBJMAP_CH_MASK)) | mode);
}

/*---------------------------------------------------------------------------*
  Name:         GX_GetOBJVRamModeChar

  Description:  Get the condition for OBJ-VRAM (ChrOBJ) (MAIN engine).

  Arguments:    None.
  
  Returns:      select the size and the mapping mode for Character Object
 *---------------------------------------------------------------------------*/
static inline GXOBJVRamModeChar GX_GetOBJVRamModeChar(void)
{
    return (GXOBJVRamModeChar)(reg_GX_DISPCNT &
                               (REG_GX_DISPCNT_EXOBJ_CH_MASK | REG_GX_DISPCNT_OBJMAP_CH_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         GXS_SetOBJVRamModeChar

  Description:  Specifies the condition for OBJ-VRAM (ChrOBJ) (SUB engine).

  Arguments:    mode:     select the size and the mapping mode for Character Object

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_SetOBJVRamModeChar(GXOBJVRamModeChar mode)
{
    GXS_OBJVRAMMODE_CHAR_ASSERT(mode);

    reg_GXS_DB_DISPCNT = (u32)((reg_GXS_DB_DISPCNT &
                               ~(REG_GXS_DB_DISPCNT_EXOBJ_CH_MASK |
                                 REG_GXS_DB_DISPCNT_OBJMAP_CH_MASK)) | mode);
}

/*---------------------------------------------------------------------------*
  Name:         GXS_GetOBJVRamModeChar

  Description:  Get the condition for OBJ-VRAM (ChrOBJ) (SUB engine).

  Arguments:    None.
  
  Returns:      select the size and the mapping mode for Character Object
 *---------------------------------------------------------------------------*/
static inline GXOBJVRamModeChar GXS_GetOBJVRamModeChar(void)
{
    return (GXOBJVRamModeChar)(reg_GXS_DB_DISPCNT &
                               (REG_GXS_DB_DISPCNT_EXOBJ_CH_MASK |
                                REG_GXS_DB_DISPCNT_OBJMAP_CH_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetOBJVRamModeBmp

  Description:  Specifies the condition for OBJ-VRAM (BitmapOBJ) (MAIN engine).

  Arguments:    mode:     select the size and the mapping mode for Bitmap Object

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetOBJVRamModeBmp(GXOBJVRamModeBmp mode)
{
    GX_OBJVRAMMODE_BMP_ASSERT(mode);

    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT &
                           ~(REG_GX_DISPCNT_EXOBJ_BM_MASK | REG_GX_DISPCNT_OBJMAP_BM_MASK)) | mode);
}


/*---------------------------------------------------------------------------*
  Name:         GX_GetOBJVRamModeBmp

  Description:  Get the condition for OBJ-VRAM (BitmapOBJ) (MAIN engine).

  Arguments:    None.
  
  Returns:      select the size and the mapping mode for Bitmap Object
 *---------------------------------------------------------------------------*/
static inline GXOBJVRamModeBmp GX_GetOBJVRamModeBmp(void)
{
    return (GXOBJVRamModeBmp)(reg_GX_DISPCNT &
                              (REG_GX_DISPCNT_EXOBJ_BM_MASK | REG_GX_DISPCNT_OBJMAP_BM_MASK));
}


/*---------------------------------------------------------------------------*
  Name:         GXS_SetOBJVRamModeBmp

  Description:  Specifies the condition for OBJ-VRAM (BitmapOBJ) (SUB engine).

  Arguments:    mode:     select the size and the mapping mode for Bitmap Object

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_SetOBJVRamModeBmp(GXOBJVRamModeBmp mode)
{
    GXS_OBJVRAMMODE_BMP_ASSERT(mode);

    reg_GXS_DB_DISPCNT = (u32)((reg_GXS_DB_DISPCNT & ~(REG_GXS_DB_DISPCNT_OBJMAP_BM_MASK)) | mode);
}


/*---------------------------------------------------------------------------*
  Name:         GXS_GetOBJVRamModeBmp

  Description:  Get the condition for OBJ-VRAM (BitmapOBJ) (SUB engine).

  Arguments:    None.
  
  Returns:      select the size and the mapping mode for Bitmap Object
 *---------------------------------------------------------------------------*/
static inline GXOBJVRamModeBmp GXS_GetOBJVRamModeBmp(void)
{
    return (GXOBJVRamModeBmp)(reg_GXS_DB_DISPCNT & REG_GXS_DB_DISPCNT_OBJMAP_BM_MASK);
}


/*---------------------------------------------------------------------------*
  Name:         GX_BlankScr

  Description:  Stops the MAIN 2D circuit.
                ******** THIS WILL BE REMOVED IN A FUTURE RELEASE. ********
                ******** USE GX_DispOn/GX_DispOff INSTEAD. ********

  Arguments:    blank:  if FALSE,  displays.
                       otherwise: the 2D graphics circuit doesn't access VRAM,
                                  and the LCD turns white.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_BlankScr(BOOL blank)
{
    SDK_WARNING((1 == 0), "GX_BlankScr is obsolete, please use GX_DispOn/GX_DispOff instead.");
    if (blank)
    {
        reg_GX_DISPCNT |= REG_GX_DISPCNT_BLANK_MASK;
    }
    else
    {
        reg_GX_DISPCNT &= ~REG_GX_DISPCNT_BLANK_MASK;
    }
}


/*---------------------------------------------------------------------------*
  Name:         GXS_DispOff

  Description:  Stops displaying the output of the SUB engine.

  Arguments:    none

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_DispOff(void)
{
    reg_GXS_DB_DISPCNT &= ~REG_GXS_DB_DISPCNT_MODE_MASK;
}


/*---------------------------------------------------------------------------*
  Name:         GXS_DispOn

  Description:  Starts displaying the output of the SUB engine.

  Arguments:    none

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_DispOn(void)
{
    reg_GXS_DB_DISPCNT |= REG_GXS_DB_DISPCNT_MODE_MASK;
}


/*---------------------------------------------------------------------------*
  Name:         GX_HBlankOBJProc

  Description:  if FALSE, do not process OBJs during H-Blank.
                Otherwise, process OBJs even during H-Blank (MAIN engine).

  Arguments:    proc:        FALSE / not FALSE (TRUE)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_HBlankOBJProc(BOOL proc)
{
    if (proc)
    {
        reg_GX_DISPCNT |= REG_GX_DISPCNT_OH_MASK;
    }
    else
    {
        reg_GX_DISPCNT &= ~REG_GX_DISPCNT_OH_MASK;
    }
}


/*---------------------------------------------------------------------------*
  Name:         GXS_HBlankOBJProc

  Description:  If FALSE, do not process OBJs during H-Blank.
                Otherwise, process OBJ even during H-Blank(SUB engine).

  Arguments:    proc:        FALSE / not FALSE (TRUE)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_HBlankOBJProc(BOOL proc)
{
    if (proc)
    {
        reg_GXS_DB_DISPCNT |= REG_GXS_DB_DISPCNT_OH_MASK;
    }
    else
    {
        reg_GXS_DB_DISPCNT &= ~REG_GXS_DB_DISPCNT_OH_MASK;
    }
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetMasterBrightness

  Description:  Set master brightness (MAIN engine).

  Arguments:    brightness:     master brightness control (-16 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetMasterBrightness(int brightness)
{
    GXx_SetMasterBrightness_(&reg_GX_MASTER_BRIGHT, brightness);
}

/*---------------------------------------------------------------------------*
  Name:         GX_GetMasterBrightness

  Description:  Get master brightness (MAIN engine).

  Arguments:    None.

  Returns:      master brightness control (-16 to 16)
 *---------------------------------------------------------------------------*/
static inline int GX_GetMasterBrightness(void)
{
    return GXx_GetMasterBrightness_(&reg_GX_MASTER_BRIGHT);
}


/*---------------------------------------------------------------------------*
  Name:         GXS_SetMasterBrightness

  Description:  Set master brightness (SUB engine).

  Arguments:    brightness:     master brightness control (-16 to 16)

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXS_SetMasterBrightness(int brightness)
{
    GXx_SetMasterBrightness_(&reg_GXS_DB_MASTER_BRIGHT, brightness);
}

/*---------------------------------------------------------------------------*
  Name:         GXS_GetMasterBrightness

  Description:  Get master brightness (SUB engine).

  Arguments:    None.

  Returns:      master brightness control (-16 to 16)
 *---------------------------------------------------------------------------*/
static inline int GXS_GetMasterBrightness(void)
{
    return GXx_GetMasterBrightness_(&reg_GXS_DB_MASTER_BRIGHT);
}


/*---------------------------------------------------------------------------*
  Name:         GX_IsHBlank

  Description:  Tests if H-Blank.

  Arguments:    none

  Returns:      0:           if not in H-Blank
                otherwise:   if in H-Blank
 *---------------------------------------------------------------------------*/
static inline s32 GX_IsHBlank(void)
{
    return (reg_GX_DISPSTAT & REG_GX_DISPSTAT_HBLK_MASK);
}


/*---------------------------------------------------------------------------*
  Name:         GX_IsVBlank

  Description:  Tests if V-Blank.

  Arguments:    none

  Returns:      0:           if not in V-Blank
                otherwise:   if in V-Blank
 *---------------------------------------------------------------------------*/
static inline s32 GX_IsVBlank(void)
{
    return (reg_GX_DISPSTAT & REG_GX_DISPSTAT_VBLK_MASK);
}


/*---------------------------------------------------------------------------*
  Name:         GX_IsVCountEq

  Description:  Tests if VCount is equal to GX_VCountEqVal().

  Arguments:    none

  Returns:      0:           if V-counter not equal to GX_VCountEqVal()
                otherwise:   if V-counter equal to GX_VCountEqVal()
 *---------------------------------------------------------------------------*/
static inline s32 GX_IsVCountEq(void)
{
    return (reg_GX_DISPSTAT & REG_GX_DISPSTAT_LYC_MASK);
}


/*---------------------------------------------------------------------------*
  Name:         GX_VCountEqIntr

  Description:  Enable/disable V-Counter equality interrupt.

  Arguments:    enable:      FALSE / not FALSE (TRUE)

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void GX_VCountEqIntr(BOOL enable)
{
    if (enable)
    {
        reg_GX_DISPSTAT |= REG_GX_DISPSTAT_VQI_MASK;
    }
    else
    {
        reg_GX_DISPSTAT &= ~REG_GX_DISPSTAT_VQI_MASK;
    }
}


/*---------------------------------------------------------------------------*
  Name:         GX_GetVCount

  Description:  Obtain the value of the current VCOUNTER register.

  Arguments:    none

  Returns:      the value of the current VCOUNTER register
 *---------------------------------------------------------------------------*/
static inline s32 GX_GetVCount()
{
    return reg_GX_VCOUNT;
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetVCount

  Description:  Sets the value of the current VCOUNTER register.

  Arguments:    count:       the value to be new VCOUNTER

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetVCount(s32 count)
{
    static vu32 vblank_count;

    if(count < 202 || count > 211)
    {
        SDK_TFATAL_ERROR("V Counter out of range(%d). it must be 202 to 211.", count);
    }
    else if(vblank_count == *(vu32 *)HW_VBLANK_COUNT_BUF)
    {
        SDK_TFATAL_ERROR("Set V Count once a frame.");
    }
    else
    {
        OSIntrMode intr_mode;
        s32 current_count;

        intr_mode = OS_DisableInterrupts();
        current_count = reg_GX_VCOUNT;

        // accept (current_count == 211)
        if(current_count < 202 || current_count > 211)
        {
            SDK_TFATAL_ERROR("Current V Counter out of range(%d). it must be 202 to 211.", current_count);
        }
        else if(count > current_count)
        {
            SDK_TFATAL_ERROR("Cannot advance the V Counter");
        }
        else
        {
            reg_GX_VCOUNT = (u16)count;
            vblank_count = *(vu32 *)HW_VBLANK_COUNT_BUF;
        }

        (void)OS_RestoreInterrupts(intr_mode);
    }
}

/*---------------------------------------------------------------------------*
  Name:         GX_GetVCountEqVal

  Description:  Get the V-counter agreement value.

  Arguments:    None

  Returns:      the value of V-counter to interrupt
 *---------------------------------------------------------------------------*/
static inline s32 GX_GetVCountEqVal(void)
{
    u16     val = reg_GX_DISPSTAT;
    return ((val >> 8) & 0x00ff) | ((val << 1) & 0x0100);
}

/*---------------------------------------------------------------------------*
  Name:         GX_SetPower

  Description:  Power Control

  Arguments:    gxbit_power:      specifies the modules to be enabled

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetPower(int gxbit_power)
{
    GX_POWER_ASSERT(gxbit_power);

    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~GX_POWER_ALL) | gxbit_power);
}


/*---------------------------------------------------------------------------*
  Name:         GX_GetPower

  Description:  Gets the state of power control.

  Arguments:    none

  Returns:      the state of power control
 *---------------------------------------------------------------------------*/
static inline GXPower GX_GetPower()
{
    return (GXPower)(reg_GX_POWCNT & GX_POWER_ALL);
}


/*---------------------------------------------------------------------------*
  Name:         GXi_PowerLCD

  Description:  Controls the power of LCDs.

  Arguments:    enable:       if FALSE, LCDs are off.
                             otherwise, LCDs are on.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GXi_PowerLCD(BOOL enable)
{
    if (enable)
    {
        reg_GX_POWCNT |= REG_GX_POWCNT_LCD_MASK;
    }
    else
    {
        reg_GX_POWCNT &= ~REG_GX_POWCNT_LCD_MASK;
    }
}


/*---------------------------------------------------------------------------*
 Removed function. if this functions was used, errors will occur at compile time.
 *---------------------------------------------------------------------------*/
// #define SDK_ERR() macro does not exist. It's for notification of modification.
#define GX_PowerLCD(x)    SDK_ERR("GX_PowerLCD() is discontinued. please use PM_SetLCDPower()\n")
#define GX_PowerLCDTop(x) SDK_ERR("GX_PowerLCDTop() is discontinued. please use PM_SetLCDPower()\n")
#define GX_PowerLCDBot(x) SDK_ERR("GX_PowerLCDBot() is discontinued. please use PM_SetLCDPower()\n")
#define GX_POWER_LCD_TOP  SDK_ERR("GX_POWER_LCD_TOP is discontinued. please use PM_SetLCDPower()\n")
#define GX_POWER_LCD_BOT  SDK_ERR("GX_POWER_LCD_BOT is discontinued. please use PM_SetLCDPower()\n")
#define GX_POWER_LCD      SDK_ERR("GX_POWER_LCD is discontinued. please use PM_SetLCDPower()\n")


/*---------------------------------------------------------------------------*
  Name:         GX_Power2D

  Description:  Controls the power of the 2D Graphics Engines.

  Arguments:    enable:       if FALSE, the 2D engines are off.
                             Otherwise, the 2D engines are on.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_Power2D(BOOL enable)
{
    if (enable)
    {
        reg_GX_POWCNT |= (REG_GX_POWCNT_E2DG_MASK | REG_GX_POWCNT_E2DGB_MASK);
    }
    else
    {
        reg_GX_POWCNT &= ~(REG_GX_POWCNT_E2DG_MASK | REG_GX_POWCNT_E2DGB_MASK);
    }
}


/*---------------------------------------------------------------------------*
  Name:         GX_Power2DMain

  Description:  Controls the power of the main 2D Graphics Engine.

  Arguments:    enable:       if FALSE, the main 2D engine is off.
                             Otherwise, the main 2D engine is on.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_Power2DMain(BOOL enable)
{
    if (enable)
    {
        reg_GX_POWCNT |= REG_GX_POWCNT_E2DG_MASK;
    }
    else
    {
        reg_GX_POWCNT &= ~REG_GX_POWCNT_E2DG_MASK;
    }
}


/*---------------------------------------------------------------------------*
  Name:         GX_Power2DSub

  Description:  Controls the power of the sub 2D Graphics Engine.

  Arguments:    enable:       if FALSE, the sub 2D engine is off.
                             Otherwise, the sub 2D engine is on.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_Power2DSub(BOOL enable)
{
    if (enable)
    {
        reg_GX_POWCNT |= REG_GX_POWCNT_E2DGB_MASK;
    }
    else
    {
        reg_GX_POWCNT &= ~REG_GX_POWCNT_E2DGB_MASK;
    }
}


/*---------------------------------------------------------------------------*
  Name:         GX_PowerRender

  Description:  Power Control of the Rendering Engine.

  Arguments:    enable:       if FALSE, the rendering engine is off.
                             Otherwise, the rendering engine is on.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_PowerRender(BOOL enable)
{
    if (enable)
    {
        reg_GX_POWCNT |= REG_GX_POWCNT_RE_MASK;
    }
    else
    {
        reg_GX_POWCNT &= ~REG_GX_POWCNT_RE_MASK;
    }
}


/*---------------------------------------------------------------------------*
  Name:         GX_PowerGeometry

  Description:  Power Control of the Geometry Engine.

  Arguments:    enable:       if FALSE, the geometry engine is off.
                             Otherwise, the geometry engine is on.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_PowerGeometry(BOOL enable)
{
    if (enable)
    {
        reg_GX_POWCNT |= REG_GX_POWCNT_GE_MASK;
    }
    else
    {
        reg_GX_POWCNT &= ~REG_GX_POWCNT_GE_MASK;
    }
}


/*---------------------------------------------------------------------------*
  Name:         GX_Power3D

  Description:  Power Control of the Geometry and Rendering Engine.

  Arguments:    enable:       if FALSE, the engines are off.
                             Otherwise, the engines are on.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_Power3D(BOOL enable)
{
    if (enable)
    {
        reg_GX_POWCNT |= (REG_GX_POWCNT_GE_MASK | REG_GX_POWCNT_RE_MASK);
    }
    else
    {
        reg_GX_POWCNT &= ~(REG_GX_POWCNT_GE_MASK | REG_GX_POWCNT_RE_MASK);
    }
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetDispSelect

  Description:  Selects the LCDs to output.

  Arguments:    sel:          TOP/main BOT/sub  if GX_DISP_SELECT_MAIN_SUB
                             TOP/sub  BOT/main if GX_DISP_SELECT_SUB_MAIN
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetDispSelect(GXDispSelect sel)
{
    GX_DISP_SELECT_ASSERT(sel);

    reg_GX_POWCNT = (u16)((reg_GX_POWCNT & ~REG_GX_POWCNT_DSEL_MASK) |
                          (sel << REG_GX_POWCNT_DSEL_SHIFT));
}


/*---------------------------------------------------------------------------*
  Name:         GX_GetDispSelect

  Description:  Gets the output switch set by GX_SetDispSelect.

  Arguments:    none
                
  Returns:      GX_DISP_SELECT_MAIN_SUB or GX_DISP_SELECT_SUB_MAIN
 *---------------------------------------------------------------------------*/
static inline GXDispSelect GX_GetDispSelect(void)
{
    return (GXDispSelect)((reg_GX_POWCNT & REG_GX_POWCNT_DSEL_MASK) >> REG_GX_POWCNT_DSEL_SHIFT);
}


/*---------------------------------------------------------------------------*
  Name:         GX_InitEx

  Description:  Initializes the registers for graphics (except 3D)
                with set default dmaNo.

  Arguments:    none
                
  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_InitEx(u32 dma_no)
{
    SDK_ASSERT(dma_no <= MI_DMA_MAX_NUM || dma_no == GX_DMA_NOT_USE);

    GXi_DmaId = dma_no;
    GX_Init();
}

/*---------------------------------------------------------------------------*
  Name:         GX_GetDefaultDMA

  Description:  Gets default DMA channel.

  Arguments:    None.

  Returns:      current DMA channel.
 *---------------------------------------------------------------------------*/
static inline u32 GX_GetDefaultDMA(void)
{
    return GXi_DmaId;
}

#endif // SDK_FROM_TOOL

#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_GX_GX_H_ */
#endif
