/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     gx_sp.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: gx_sp.h,v $
  Revision 1.7  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.6  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.5  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.4  2004/10/21 13:44:56  yasu
  Add  GX_GetVCountEqVal( )
  Make aliases for GX_*VCounter* <-> GX_*VCount*

  Revision 1.3  2004/05/21 04:33:38  takano_makoto
  Add GX_LCD_SIZE_X and Add GX_LCD_SIZE_Y

  Revision 1.2  2004/03/08 01:08:05  yasu
  DISP->GX

  Revision 1.1  2004/02/18 07:04:25  nishida_kenji
  Initial check in.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

//////////////////////////////////////////////////////////////////////////////
// Simple accessors for ARM7's DISPSTAT and VCOUNT.
// THIS FILE IS INCLUDED BY 'nitro_sp.h'.
//////////////////////////////////////////////////////////////////////////////

#ifndef NITRO_GX_SP_H_
#define NITRO_GX_SP_H_

#include "nitro/hw/ARM7/ioreg.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

#define     GX_LCD_SIZE_X       HW_LCD_WIDTH
#define     GX_LCD_SIZE_Y       HW_LCD_HEIGHT

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

// reg_GX_DISPSTAT
static s32 GX_IsHBlank(void);
static s32 GX_HBlankIntr(BOOL enable);
static s32 GX_IsVBlank(void);
static s32 GX_VBlankIntr(BOOL enable);
static s32 GX_IsVCountEq(void);
static void GX_VCountEqIntr(BOOL enable);
static void GX_SetVCountEqVal(s32 val);
static s32 GX_GetVCountEqVal(void);

#define	GX_IsVCounterEq		GX_IsVCountEq
#define	GX_VCounterEqIntr	GX_VCountEqIntr
#define	GX_SetVCounterEqVal	GX_SetVCountEqVal
#define	GX_GetVCounterEqVal	GX_GetVCountEqVal

// reg_GX_VCOUNT
static s32 GX_GetVCount(void);
static void GX_SetVCount(s32 count);

//----------------------------------------------------------------------------
// Implementation of inline function
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         GX_IsHBlank

  Description:  Tests if H-Blank.

  Arguments:    none

  Returns:      0           if not in H-Blank
                otherwise   if in H-Blank
 *---------------------------------------------------------------------------*/
static inline s32 GX_IsHBlank(void)
{
    return (reg_GX_DISPSTAT & REG_GX_DISPSTAT_HBLK_MASK);
}


/*---------------------------------------------------------------------------*
  Name:         GX_IsVBlank

  Description:  Tests if V-Blank.

  Arguments:    none

  Returns:      0           if not in V-Blank
                otherwise   if in V-Blank
 *---------------------------------------------------------------------------*/
static inline s32 GX_IsVBlank(void)
{
    return (reg_GX_DISPSTAT & REG_GX_DISPSTAT_VBLK_MASK);
}


/*---------------------------------------------------------------------------*
  Name:         GX_IsVCountEq

  Description:  Tests if VCounter is equal to GX_VCounterEqVal().

  Arguments:    none

  Returns:      0           if V-counter not equal to GX_VCountEqVal()
                otherwise   if V-counter equal to GX_VCountEqVal()
 *---------------------------------------------------------------------------*/
static inline s32 GX_IsVCountEq(void)
{
    return (reg_GX_DISPSTAT & REG_GX_DISPSTAT_LYC_MASK);
}


/*---------------------------------------------------------------------------*
  Name:         GX_VCountEqIntr

  Description:  Enable/disable V-Counter equality interrupt.

  Arguments:    enable      FALSE / not FALSE(TRUE)

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

  Arguments:    count       the value to be new VCOUNTER

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetVCount(s32 count)
{
    SDK_WARNING(reg_GX_VCOUNT >= 202 && reg_GX_VCOUNT <= 212,
                "V Counter out of range(%d). it must be 202 to 212.", reg_GX_VCOUNT);
    SDK_ASSERT(count >= 202 && count <= 212);

    reg_GX_VCOUNT = (u16)count;
}


/*---------------------------------------------------------------------------*
  Name:         GX_SetVCountEqVal

  Description:  Specifies the V-counter agreement value.

  Arguments:    val        the value of V-counter

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline void GX_SetVCountEqVal(s32 val)
{
    SDK_MINMAX_ASSERT(val, 0, HW_LCD_LINES - 1);
    reg_GX_DISPSTAT = (u16)((reg_GX_DISPSTAT & (REG_GX_DISPSTAT_VBLK_MASK |
                                                REG_GX_DISPSTAT_HBLK_MASK |
                                                REG_GX_DISPSTAT_LYC_MASK |
                                                REG_GX_DISPSTAT_VBI_MASK |
                                                REG_GX_DISPSTAT_HBI_MASK |
                                                REG_GX_DISPSTAT_VQI_MASK)) |
                            ((val & 0xff) << 8) | ((val & 0x100) >> 1));
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
  Name:         GX_HBlankIntr

  Description:  Enables/Disables the H-Blank interrupt generation.

  Arguments:    enable     disable if FALSE, enable otherwise.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline s32 GX_HBlankIntr(BOOL enable)
{
    s32     rval = (reg_GX_DISPSTAT & REG_GX_DISPSTAT_HBI_MASK);
    if (enable)
    {
        reg_GX_DISPSTAT |= REG_GX_DISPSTAT_HBI_MASK;
    }
    else
    {
        reg_GX_DISPSTAT &= ~REG_GX_DISPSTAT_HBI_MASK;
    }
    return rval;
}


/*---------------------------------------------------------------------------*
  Name:         GX_VBlankIntr

  Description:  Enables/Disables the V-Blank interrupt generation.

  Arguments:    enable     disable if FALSE, enable otherwise.

  Returns:      none
 *---------------------------------------------------------------------------*/
static inline s32 GX_VBlankIntr(BOOL enable)
{
    s32     rval = (reg_GX_DISPSTAT & REG_GX_DISPSTAT_VBI_MASK);
    if (enable)
    {
        reg_GX_DISPSTAT |= REG_GX_DISPSTAT_VBI_MASK;
    }
    else
    {
        reg_GX_DISPSTAT &= ~REG_GX_DISPSTAT_VBI_MASK;
    }
    return rval;
}




#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
