/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CP - include
  File:     sqrt.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: sqrt.h,v $
  Revision 1.22  2007/08/24 04:35:36  okubata_ryoma
  Fix related to headerfiles.

  Revision 1.21  2006/08/09 06:51:20  takano_makoto
  Deleted unused macro SDK_CP_NO_SAFE

  Revision 1.20  2006/01/18 02:12:29  kitase_hirotake
  do-indent

  Revision 1.19  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.18  2005/02/21 12:22:44  takano_makoto
  Fixed SDK_CP_NO_SAFE bug.

  Revision 1.17  2004/09/02 07:45:52  yada
  Only changed comments

  Revision 1.16  2004/05/06 10:45:13  takano_makoto
  Modified include file.

  Revision 1.15  2004/05/06 02:56:05  takano_makoto
  Change to thread safe.

  Revision 1.14  2004/04/07 02:03:17  yada
  Fixed header comment

  Revision 1.13  2004/02/05 08:38:44  yada
  Only modified comment

  Revision 1.12  2004/02/05 07:09:03  yasu
  Changed SDK prefix iris -> nitro

  Revision 1.11  2004/01/18 04:35:55  nishida_kenji
  Renames functions (e.g. CP_GetSqrtResult_8 -> CP_GetSqrtResult8)

  Revision 1.10  2004/01/18 01:24:13  nishida_kenji
  CP_IsSqrtBusy returns s32

  Revision 1.9  2004/01/17 02:28:38  nishida_kenji
  Converted 'inline' to 'static inline' in header files

  Revision 1.8  2003/12/25 00:19:29  nishida_kenji
  Converted INLINE to inline

  Revision 1.7  2003/12/08 12:09:56  yada
  Made changes to the includer file.

  Revision 1.6  2003/11/14 04:02:16  yada
  Changed the register access macro from REG_XXX to reg_XXX.

  Revision 1.5  2003/11/05 00:58:16  yada
  Made the cast more strict.

  Revision 1.4  2003/11/04 09:19:43  yada
  Added (u32) to some constants.

  Revision 1.3  2003/10/30 11:42:45  yada
  Decided to use REGTypexx in the register type.

  Revision 1.2  2003/10/30 04:59:49  yasu
  Register definition file change: below $IrisSDK/include/iris/hw.

  Revision 1.1  2003/10/30 00:37:52  yada
  Initial version created

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CP_SQRT_H_
#define NITRO_CP_SQRT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/cp/context.h"

//---- sqrt calculation mode
#define CP_SQRT_32BIT_MODE         (0UL << REG_CP_SQRTCNT_MODE_SHIFT)   // 32bit mode
#define CP_SQRT_64BIT_MODE         (1UL << REG_CP_SQRTCNT_MODE_SHIFT)   // 64bit mode


//================================================================================
//            sqrt control register setting
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         CP_SetSqrtControl

  Description:  Set value to sqrt control register.

  Arguments:    param: value to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void CP_SetSqrtControl(u16 param)
{
    reg_CP_SQRTCNT = param;
}


//================================================================================
//            sqrt parameter setting
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         CP_SetSqrtImm64_NS_
                CP_SetSqrtImm32_NS_

  Description:  Set value to sqrt parameter.
                Not set bit-mode.
                Not thread safe.

  Arguments:    param: parameter to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void CP_SetSqrtImm64_NS_(u64 param)
{
    *((REGType64 *)REG_SQRT_PARAM_ADDR) = param;
}
static inline void CP_SetSqrtImm32_NS_(u32 param)
{
    *((REGType32 *)REG_SQRT_PARAM_ADDR) = param;
}

/*---------------------------------------------------------------------------*
  Name:         CP_SetSqrtImm64
                CP_SetSqrtImm32

  Description:  Set value to sqrt parameter.
                Not set bit-mode.

  Arguments:    param: parameter to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void CP_SetSqrtImm64(u64 param)
{
    *((REGType64 *)REG_SQRT_PARAM_ADDR) = param;
}

static inline void CP_SetSqrtImm32(u32 param)
{
    *((REGType32 *)REG_SQRT_PARAM_ADDR) = param;
}

/*---------------------------------------------------------------------------*
  Name:         CP_SetSqrt64
                CP_SetSqrt32

  Description:  Set value to sqrt parameter.
                Set bit-mode.

  Arguments:    param: parameter to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void CP_SetSqrt64(u64 param)
{
    reg_CP_SQRTCNT = CP_SQRT_64BIT_MODE;
    CP_SetSqrtImm64_NS_(param);
}

static inline void CP_SetSqrt32(u32 param)
{
    reg_CP_SQRTCNT = CP_SQRT_32BIT_MODE;
    CP_SetSqrtImm32_NS_(param);
}


//================================================================================
//            wait to finish
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         CP_IsSqrtBusy

  Description:  Check sqrt calculation finished.

  Arguments:    None.

  Returns:      Non-0 if busy, 0 if finished.
 *---------------------------------------------------------------------------*/
static inline s32 CP_IsSqrtBusy(void)
{
    return (reg_CP_SQRTCNT & REG_CP_SQRTCNT_BUSY_MASK);
}

/*---------------------------------------------------------------------------*
  Name:         CP_WaitSqrt

  Description:  Wait till sqrt calculation is finished.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void CP_WaitSqrt(void)
{
    while (CP_IsSqrtBusy())
    {
    }
}

//================================================================================
//            getting result
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         CP_GetSqrtResultImm8 / 16 / 32

  Description:  Read result.
                Don't check first to see if finished.

  Arguments:    None.

  Returns:      Result
 *---------------------------------------------------------------------------*/
static inline u32 CP_GetSqrtResultImm32(void)
{
    return (u32)(*((REGType32 *)REG_SQRT_RESULT_ADDR));
}
static inline u16 CP_GetSqrtResultImm16(void)
{
    return (u16)(*((REGType16 *)REG_SQRT_RESULT_ADDR));
}
static inline u8 CP_GetSqrtResultImm8(void)
{
    return (u8)(*((REGType8 *)REG_SQRT_RESULT_ADDR));
}

/*---------------------------------------------------------------------------*
  Name:         CP_GetSqrtResult8 / 16 / 32

  Description:  Wait until finished, and read result.

  Arguments:    None.

  Returns:      Result
 *---------------------------------------------------------------------------*/
static inline u32 CP_GetSqrtResult32(void)
{
    CP_WaitSqrt();
    return CP_GetSqrtResultImm32();
}
static inline u16 CP_GetSqrtResult16(void)
{
    CP_WaitSqrt();
    return CP_GetSqrtResultImm16();
}
static inline u8 CP_GetSqrtResult8(void)
{
    CP_WaitSqrt();
    return CP_GetSqrtResultImm8();
}

#ifdef __cplusplus
} /* extern "C" */
#endif


/* NITRO_CP_SQRT_H_ */
#endif
