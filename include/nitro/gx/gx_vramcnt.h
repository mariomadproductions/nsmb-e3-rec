/*---------------------------------------------------------------------------*
  Project:  NitroSDK - GX -
  File:     gx_vramcnt.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: gx_vramcnt.h,v $
  Revision 1.42  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.41  2005/09/08 12:28:09  yasu
  Decision code using SDK_WIN32 has also been added to SDK_FROM_TOOL decision code.

  Revision 1.40  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.39  2005/02/15 08:10:02  terui
  Added GX_TrySetBankFor* functions

  Revision 1.38  2005/02/09 09:14:50  terui
  Changed VRAM ID definitions to match OS definitions

  Revision 1.37  2004/12/06 07:43:24  takano_makoto
  Made correction so that GX_VRAM_BG_NONE cannot be specified for the argument of GX_SetBankForBGEx

  Revision 1.36  2004/11/25 11:12:13  takano_makoto
  add GX_SetBankForBGEx

  Revision 1.35  2004/11/02 14:42:28  takano_makoto
  fix comments.

  Revision 1.34  2004/10/04 13:30:22  takano_makoto
  Add GX_VRAM_CLEARDEPTH_128_* to use clear depth without clear image.

  Revision 1.33  2004/06/07 00:52:46  takano_makoto
  modify GX_VRAM_SUB_OBJEXTPLTT_01_I to GX_VRAM_SUB_OBJEXTPLTT_0_I

  Revision 1.32  2004/06/02 13:06:17  takano_makoto
  Change EXTPLTT enum name.

  Revision 1.31  2004/05/14 11:52:57  takano_makoto
  Add #ifndef SDK_FROM_TOOL for VC or BCB.

  Revision 1.30  2004/04/23 05:37:08  takano_makoto
  replace flags

  Revision 1.29  2004/04/02 05:21:55  takano_makoto
  Add entry of GX_VRAM_ARM7_128_C

  Revision 1.28  2004/03/08 02:28:23  takano_makoto
  Sort enum entry in GXVRamBG.

  Revision 1.27  2004/03/04 13:43:18  takano_makoto
  Add GX_VRAM_BG_80_EF, GX_VRAM_BG_80_EG, GX_VRAM_OBJ_80_EF, GX_VRAM_OBJ_80_EG

  Revision 1.26  2004/02/17 08:12:26  nishida_kenji
  small fix.

  Revision 1.25  2004/02/17 05:31:57  nishida_kenji
  Add GX_VRAM_BG_256_AC, GX_VRAM_BG_256_AD, GX_VRAM_BG_256_BD,
        GX_VRAM_BG_384_ABD, GX_VRAM_BG_384_ACD.

  Revision 1.24  2004/02/12 08:11:59  nishida_kenji
  Add GX_VRAM_BG_16_G and GX_VRAM_OBJ_16_G.

  Revision 1.23  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.22  2004/02/03 11:56:15  nishida_kenji
  add GX_VRAM_OBJ_128_B.

  Revision 1.21  2004/02/02 12:43:57  nishida_kenji
  add GX_GetSizeOfXXXXX.

  Revision 1.19  2004/01/27 11:14:29  nishida_kenji
  adds APIs for the sub engine.

  Revision 1.18  2004/01/22 11:07:01  nishida_kenji
  adds APIs for Display B

  Revision 1.17  2004/01/19 07:22:49  nishida_kenji
  add comments

  Revision 1.16  2004/01/17 07:17:12  nishida_kenji
  remove external include guards

  Revision 1.15  2004/01/05 02:02:11  nishida_kenji
  add GX_GetBankForXXXX

  Revision 1.14  2003/12/25 11:00:10  nishida_kenji
  converted by GX_APIChangeFrom031212-2.pl

  Revision 1.13  2003/12/24 08:27:46  nishida_kenji
  move WRAM control to MI domain.

  Revision 1.12  2003/12/17 09:00:21  nishida_kenji
  Totally revised APIs.
  build/buildtools/GX_APIChangeFrom031212.pl would help you change your program to some extent.

  Revision 1.11  2003/12/17 08:50:33  nishida_kenji
  revise comments

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_GX_VRAMCNT_H_
#define NITRO_GX_VRAMCNT_H_

#include "nitro/gx/gxcommon.h"
#include "nitro/os/ARM9/vramExclusive.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type definition
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//    Parameters for VRAM
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_A = OS_VRAM_BANK_ID_A,     // VRAM-A
    GX_VRAM_B = OS_VRAM_BANK_ID_B,     // VRAM-B
    GX_VRAM_C = OS_VRAM_BANK_ID_C,     // VRAM-C
    GX_VRAM_D = OS_VRAM_BANK_ID_D,     // VRAM-D
    GX_VRAM_E = OS_VRAM_BANK_ID_E,     // VRAM-E
    GX_VRAM_F = OS_VRAM_BANK_ID_F,     // VRAM-F
    GX_VRAM_G = OS_VRAM_BANK_ID_G,     // VRAM-G
    GX_VRAM_H = OS_VRAM_BANK_ID_H,     // VRAM-H
    GX_VRAM_I = OS_VRAM_BANK_ID_I,     // VRAM-I
    GX_VRAM_ALL = OS_VRAM_BANK_ID_ALL
}
GXVRam;

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForLCDC etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_LCDC_NONE = 0x0000,
    GX_VRAM_LCDC_A = GX_VRAM_A,        // ARM9: HW_LCDC_VRAM_A  -->  HW_LCDC_VRAM_B
    GX_VRAM_LCDC_B = GX_VRAM_B,        // ARM9: HW_LCDC_VRAM_B  -->  HW_LCDC_VRAM_C
    GX_VRAM_LCDC_C = GX_VRAM_C,        // ARM9: HW_LCDC_VRAM_C  -->  HW_LCDC_VRAM_D
    GX_VRAM_LCDC_D = GX_VRAM_D,        // ARM9: HW_LCDC_VRAM_D  -->  HW_LCDC_VRAM_E
    GX_VRAM_LCDC_E = GX_VRAM_E,        // ARM9: HW_LCDC_VRAM_E  -->  HW_LCDC_VRAM_F
    GX_VRAM_LCDC_F = GX_VRAM_F,        // ARM9: HW_LCDC_VRAM_F  -->  HW_LCDC_VRAM_G
    GX_VRAM_LCDC_G = GX_VRAM_G,        // ARM9: HW_LCDC_VRAM_G  -->  HW_LCDC_VRAM_H
    GX_VRAM_LCDC_H = GX_VRAM_H,        // ARM9: HW_LCDC_VRAM_H  -->  HW_LCDC_VRAM_I
    GX_VRAM_LCDC_I = GX_VRAM_I,        // ARM9: HW_LCDC_VRAM_I  -->  HW_LCDC_VRAM_END

    GX_VRAM_LCDC_ALL = GX_VRAM_ALL     // ARM9: HW_LCDC_VRAM_A  -->  HW_LCDC_VRAM_END
}
GXVRamLCDC;

#define GX_VRAM_LCDC_ASSERT(x)             \
    SDK_MINMAX_ASSERT(x, GX_VRAM_LCDC_NONE, GX_VRAM_LCDC_ALL)

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForBG etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_BG_NONE = 0x0000,
    GX_VRAM_BG_16_F = GX_VRAM_F,       // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_F_SIZE
    GX_VRAM_BG_16_G = GX_VRAM_G,       // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_G_SIZE
    GX_VRAM_BG_32_FG = GX_VRAM_F | GX_VRAM_G,   // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_F_SIZE + HW_VRAM_G_SIZE
    GX_VRAM_BG_64_E = GX_VRAM_E,       // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_E_SIZE
    GX_VRAM_BG_80_EF = GX_VRAM_E | GX_VRAM_F,   // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_E_SIZE + HW_VRAM_F_SIZE
    GX_VRAM_BG_96_EFG = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G,      // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_E_SIZE + HW_VRAM_F_SIZE + HW_VRAM_G_SIZE
    GX_VRAM_BG_128_A = GX_VRAM_A,      // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_A_SIZE
    GX_VRAM_BG_128_B = GX_VRAM_B,      // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_B_SIZE
    GX_VRAM_BG_128_C = GX_VRAM_C,      // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_C_SIZE
    GX_VRAM_BG_128_D = GX_VRAM_D,      // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_D_SIZE
    GX_VRAM_BG_256_AB = GX_VRAM_A | GX_VRAM_B,  // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_A_SIZE + HW_VRAM_B_SIZE
    GX_VRAM_BG_256_BC = GX_VRAM_B | GX_VRAM_C,  // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_B_SIZE + HW_VRAM_C_SIZE
    GX_VRAM_BG_256_CD = GX_VRAM_C | GX_VRAM_D,  // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_C_SIZE + HW_VRAM_D_SIZE
    GX_VRAM_BG_384_ABC = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C,     // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_A_SIZE + HW_VRAM_B_SIZE + HW_VRAM_C_SIZE
    GX_VRAM_BG_384_BCD = GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,     // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_B_SIZE + HW_VRAM_C_SIZE + HW_VRAM_D_SIZE
    GX_VRAM_BG_512_ABCD = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,        // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_A_SIZE + HW_VRAM_B_SIZE + HW_VRAM_C_SIZE + HW_VRAM_D_SIZE

    // discontinuous on LCDC memory
    GX_VRAM_BG_80_EG = GX_VRAM_E | GX_VRAM_G,   // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_E_SIZE + HW_VRAM_G_SIZE
    GX_VRAM_BG_256_AC = GX_VRAM_A | GX_VRAM_C,  // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_A_SIZE + HW_VRAM_C_SIZE
    GX_VRAM_BG_256_AD = GX_VRAM_A | GX_VRAM_D,  // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_A_SIZE + HW_VRAM_D_SIZE
    GX_VRAM_BG_256_BD = GX_VRAM_B | GX_VRAM_D,  // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_B_SIZE + HW_VRAM_D_SIZE
    GX_VRAM_BG_384_ABD = GX_VRAM_A | GX_VRAM_B | GX_VRAM_D,     // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_A_SIZE + HW_VRAM_B_SIZE + HW_VRAM_D_SIZE
    GX_VRAM_BG_384_ACD = GX_VRAM_A | GX_VRAM_C | GX_VRAM_D      // ARM9: HW_BG_VRAM   -->   HW_BG_VRAM + HW_VRAM_A_SIZE + HW_VRAM_C_SIZE + HW_VRAM_D_SIZE
}
GXVRamBG;

#define GX_VRAM_BG_ASSERT(x)                  \
    SDK_ASSERT( (x) == GX_VRAM_BG_NONE     || \
                (x) == GX_VRAM_BG_16_F     || \
                (x) == GX_VRAM_BG_16_G     || \
                (x) == GX_VRAM_BG_32_FG    || \
                (x) == GX_VRAM_BG_64_E     || \
                (x) == GX_VRAM_BG_80_EF    || \
                (x) == GX_VRAM_BG_80_EG    || \
                (x) == GX_VRAM_BG_96_EFG   || \
                (x) == GX_VRAM_BG_128_A    || \
                (x) == GX_VRAM_BG_128_B    || \
                (x) == GX_VRAM_BG_128_C    || \
                (x) == GX_VRAM_BG_128_D    || \
                (x) == GX_VRAM_BG_256_AB   || \
                (x) == GX_VRAM_BG_256_BC   || \
                (x) == GX_VRAM_BG_256_CD   || \
                (x) == GX_VRAM_BG_384_ABC  || \
                (x) == GX_VRAM_BG_384_BCD  || \
                (x) == GX_VRAM_BG_512_ABCD || \
                (x) == GX_VRAM_BG_256_AC   || \
                (x) == GX_VRAM_BG_256_AD   || \
                (x) == GX_VRAM_BG_256_BD   || \
                (x) == GX_VRAM_BG_384_ABD  || \
                (x) == GX_VRAM_BG_384_ACD)

#define GX_VRAM_BG_ASSERT_EX_1(x)                  \
    SDK_ASSERT( (x) == GX_VRAM_BG_16_F     || \
                (x) == GX_VRAM_BG_16_G     || \
                (x) == GX_VRAM_BG_32_FG    || \
                (x) == GX_VRAM_BG_64_E     || \
                (x) == GX_VRAM_BG_80_EF    || \
                (x) == GX_VRAM_BG_80_EG    || \
                (x) == GX_VRAM_BG_96_EFG )

#define GX_VRAM_BG_ASSERT_EX_2(x)                  \
    SDK_ASSERT( (x) == GX_VRAM_BG_NONE     || \
                (x) == GX_VRAM_BG_128_A    || \
                (x) == GX_VRAM_BG_128_B    || \
                (x) == GX_VRAM_BG_128_C    || \
                (x) == GX_VRAM_BG_128_D    || \
                (x) == GX_VRAM_BG_256_AB   || \
                (x) == GX_VRAM_BG_256_BC   || \
                (x) == GX_VRAM_BG_256_CD   || \
                (x) == GX_VRAM_BG_384_ABC  || \
                (x) == GX_VRAM_BG_384_BCD  || \
                (x) == GX_VRAM_BG_256_AC   || \
                (x) == GX_VRAM_BG_256_AD   || \
                (x) == GX_VRAM_BG_256_BD   || \
                (x) == GX_VRAM_BG_384_ABD  || \
                (x) == GX_VRAM_BG_384_ACD )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForOBJ etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_OBJ_NONE = 0x0000,
    GX_VRAM_OBJ_16_F = GX_VRAM_F,      // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_F_SIZE
    GX_VRAM_OBJ_16_G = GX_VRAM_G,      // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_G_SIZE
    GX_VRAM_OBJ_32_FG = GX_VRAM_F | GX_VRAM_G,  // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_F_SIZE + HW_VRAM_G_SIZE
    GX_VRAM_OBJ_64_E = GX_VRAM_E,      // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_E_SIZE
    GX_VRAM_OBJ_80_EF = GX_VRAM_E | GX_VRAM_F,  // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_E_SIZE + HW_VRAM_F_SIZE
    GX_VRAM_OBJ_80_EG = GX_VRAM_E | GX_VRAM_G,  // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_E_SIZE + HW_VRAM_G_SIZE
    GX_VRAM_OBJ_96_EFG = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G,     // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_E_SIZE + HW_VRAM_F_SIZE + HW_VRAM_G_SIZE
    GX_VRAM_OBJ_128_A = GX_VRAM_A,     // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_A_SIZE
    GX_VRAM_OBJ_128_B = GX_VRAM_B,     // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_B_SIZE
    GX_VRAM_OBJ_256_AB = GX_VRAM_A | GX_VRAM_B  // ARM9: HW_OBJ_VRAM  -->   HW_OBJ_VRAM + HW_VRAM_A_SIZE + HW_VRAM_B_SIZE
}
GXVRamOBJ;

#define GX_VRAM_OBJ_ASSERT(x)                \
    SDK_ASSERT( (x) == GX_VRAM_OBJ_NONE   || \
                (x) == GX_VRAM_OBJ_16_F   || \
                (x) == GX_VRAM_OBJ_16_G   || \
                (x) == GX_VRAM_OBJ_32_FG  || \
                (x) == GX_VRAM_OBJ_64_E   || \
                (x) == GX_VRAM_OBJ_80_EF  || \
                (x) == GX_VRAM_OBJ_80_EG  || \
                (x) == GX_VRAM_OBJ_96_EFG || \
                (x) == GX_VRAM_OBJ_128_A  || \
                (x) == GX_VRAM_OBJ_128_B  || \
                (x) == GX_VRAM_OBJ_256_AB )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForARM7 etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_ARM7_NONE = 0x0000,
    GX_VRAM_ARM7_128_C = GX_VRAM_C,    // ARM7: 0x06000000   -->   0x06020000
    GX_VRAM_ARM7_128_D = GX_VRAM_D,    // ARM7: 0x06000000   -->   0x06020000
    GX_VRAM_ARM7_256_CD = GX_VRAM_C | GX_VRAM_D // ARM7: 0x06000000   -->   0x06040000
}
GXVRamARM7;

#define GX_VRAM_ARM7_ASSERT(x)               \
    SDK_ASSERT( (x) == GX_VRAM_ARM7_NONE  || \
                (x) == GX_VRAM_ARM7_128_C || \
                (x) == GX_VRAM_ARM7_128_D || \
                (x) == GX_VRAM_ARM7_256_CD )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForTex etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_TEX_NONE = 0x0000,         // none
    GX_VRAM_TEX_0_A = GX_VRAM_A,       // TextureImageSlot 0
    GX_VRAM_TEX_0_B = GX_VRAM_B,       // TextureImageSlot 0
    GX_VRAM_TEX_0_C = GX_VRAM_C,       // TextureImageSlot 0
    GX_VRAM_TEX_0_D = GX_VRAM_D,       // TextureImageSlot 0
    GX_VRAM_TEX_01_AB = GX_VRAM_A | GX_VRAM_B,  // TextureImageSlot 01
    GX_VRAM_TEX_01_BC = GX_VRAM_B | GX_VRAM_C,  // TextureImageSlot 01
    GX_VRAM_TEX_01_CD = GX_VRAM_C | GX_VRAM_D,  // TextureImageSlot 01
    GX_VRAM_TEX_012_ABC = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C,    // TextureImageSlot 012
    GX_VRAM_TEX_012_BCD = GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,    // TextureImageSlot 012
    GX_VRAM_TEX_0123_ABCD = GX_VRAM_A | GX_VRAM_B | GX_VRAM_C | GX_VRAM_D,      // TextureImageSlot 0123

    // discontinuous on LCDC memory
    GX_VRAM_TEX_01_AC = GX_VRAM_A | GX_VRAM_C,  // TextureImageSlot 01
    GX_VRAM_TEX_01_AD = GX_VRAM_A | GX_VRAM_D,  // TextureImageSlot 01
    GX_VRAM_TEX_01_BD = GX_VRAM_B | GX_VRAM_D,  // TextureImageSlot 01
    GX_VRAM_TEX_012_ABD = GX_VRAM_A | GX_VRAM_B | GX_VRAM_D,    // TextureImageSlot 012
    GX_VRAM_TEX_012_ACD = GX_VRAM_A | GX_VRAM_C | GX_VRAM_D     // TextureImageSlot 012
}
GXVRamTex;

#define GX_VRAM_TEX_ASSERT(x)                   \
    SDK_ASSERT( (x) == GX_VRAM_TEX_NONE      || \
                (x) == GX_VRAM_TEX_0_A       || \
                (x) == GX_VRAM_TEX_0_B       || \
                (x) == GX_VRAM_TEX_0_C       || \
                (x) == GX_VRAM_TEX_0_D       || \
                (x) == GX_VRAM_TEX_01_AB     || \
                (x) == GX_VRAM_TEX_01_BC     || \
                (x) == GX_VRAM_TEX_01_CD     || \
                (x) == GX_VRAM_TEX_012_ABC   || \
                (x) == GX_VRAM_TEX_012_BCD   || \
                (x) == GX_VRAM_TEX_0123_ABCD || \
                (x) == GX_VRAM_TEX_01_AC     || \
                (x) == GX_VRAM_TEX_01_AD     || \
                (x) == GX_VRAM_TEX_01_BD     || \
                (x) == GX_VRAM_TEX_012_ABD   || \
                (x) == GX_VRAM_TEX_012_ACD )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForClearImage etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_CLEARIMAGE_NONE = 0x0000,
    GX_VRAM_CLEARIMAGE_256_AB = GX_VRAM_A | GX_VRAM_B,
    GX_VRAM_CLEARIMAGE_256_CD = GX_VRAM_C | GX_VRAM_D,  // TextureImageSlot 23
    GX_VRAM_CLEARDEPTH_128_A = GX_VRAM_A,
    GX_VRAM_CLEARDEPTH_128_B = GX_VRAM_B,
    GX_VRAM_CLEARDEPTH_128_C = GX_VRAM_C,
    GX_VRAM_CLEARDEPTH_128_D = GX_VRAM_D
}
GXVRamClearImage;

#define GX_VRAM_CLRIMG_ASSERT(x)                    \
    SDK_ASSERT( (x) == GX_VRAM_CLEARIMAGE_NONE   || \
                (x) == GX_VRAM_CLEARIMAGE_256_AB || \
                (x) == GX_VRAM_CLEARIMAGE_256_CD || \
                (x) == GX_VRAM_CLEARDEPTH_128_A  || \
                (x) == GX_VRAM_CLEARDEPTH_128_B  || \
                (x) == GX_VRAM_CLEARDEPTH_128_C  || \
                (x) == GX_VRAM_CLEARDEPTH_128_D )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForTexPltt etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_TEXPLTT_NONE = 0x0000,
    GX_VRAM_TEXPLTT_0_F = GX_VRAM_F,   // TexturePltt 0
    GX_VRAM_TEXPLTT_0_G = GX_VRAM_G,   // TexturePltt 0
    GX_VRAM_TEXPLTT_01_FG = GX_VRAM_F | GX_VRAM_G,      // TexturePltt 01
    GX_VRAM_TEXPLTT_0123_E = GX_VRAM_E, // TexturePltt 0-3
    GX_VRAM_TEXPLTT_01234_EF = GX_VRAM_E | GX_VRAM_F,   // TexturePltt 0-3.4
    GX_VRAM_TEXPLTT_012345_EFG = GX_VRAM_E | GX_VRAM_F | GX_VRAM_G      // TexturePltt 0-3,45
}
GXVRamTexPltt;

#define GX_VRAM_TEXPLTT_ASSERT(x)                    \
    SDK_ASSERT( (x) == GX_VRAM_TEXPLTT_NONE       || \
                (x) == GX_VRAM_TEXPLTT_0_F        || \
                (x) == GX_VRAM_TEXPLTT_0_G        || \
                (x) == GX_VRAM_TEXPLTT_01_FG      || \
                (x) == GX_VRAM_TEXPLTT_0123_E     || \
                (x) == GX_VRAM_TEXPLTT_01234_EF   || \
                (x) == GX_VRAM_TEXPLTT_012345_EFG )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForBGExtPltt etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_BGEXTPLTT_NONE = 0x0000,
    GX_VRAM_BGEXTPLTT_01_F = GX_VRAM_F, // BGExtPltt 0-1 <--- Caution
    GX_VRAM_BGEXTPLTT_23_G = GX_VRAM_G, // BGExtPltt 2-3 <--- Caution
    GX_VRAM_BGEXTPLTT_0123_E = GX_VRAM_E,       // BGExtPltt 0-3
    GX_VRAM_BGEXTPLTT_0123_FG = GX_VRAM_F | GX_VRAM_G   // BGExtPltt 0-1,2-3
}
GXVRamBGExtPltt;

#define GX_VRAM_BGEXTPLTT_ASSERT(x)                 \
    SDK_ASSERT( (x) == GX_VRAM_BGEXTPLTT_NONE    || \
                (x) == GX_VRAM_BGEXTPLTT_01_F    || \
                (x) == GX_VRAM_BGEXTPLTT_23_G    || \
                (x) == GX_VRAM_BGEXTPLTT_0123_E  || \
                (x) == GX_VRAM_BGEXTPLTT_0123_FG )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForOBJExtPltt etc.
//----------------------------------------------------------------------------
#define GX_VRAM_OBJEXTPLTT_8_F    GX_VRAM_OBJEXTPLTT_0_F
#define GX_VRAM_OBJEXTPLTT_8_G    GX_VRAM_OBJEXTPLTT_0_G

typedef enum
{
    GX_VRAM_OBJEXTPLTT_NONE = 0,
    GX_VRAM_OBJEXTPLTT_0_F = GX_VRAM_F, // OBJExtPltt
    GX_VRAM_OBJEXTPLTT_0_G = GX_VRAM_G // OBJExtPltt
}
GXVRamOBJExtPltt;

#define GX_VRAM_OBJEXTPLTT_ASSERT(x)              \
    SDK_ASSERT( (x) == GX_VRAM_OBJEXTPLTT_NONE || \
                (x) == GX_VRAM_OBJEXTPLTT_0_F  || \
                (x) == GX_VRAM_OBJEXTPLTT_0_G )

//----------------------------------------------------------------------------
//    Parameters for GXS_SetBankForSubBG etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_SUB_BG_NONE = 0x0000,
    GX_VRAM_SUB_BG_128_C = GX_VRAM_C,
    GX_VRAM_SUB_BG_32_H = GX_VRAM_H,
    GX_VRAM_SUB_BG_48_HI = GX_VRAM_H | GX_VRAM_I
}
GXVRamSubBG;

#define GX_VRAM_SUB_BG_ASSERT(x)               \
    SDK_ASSERT( (x) == GX_VRAM_SUB_BG_NONE  || \
                (x) == GX_VRAM_SUB_BG_128_C || \
                (x) == GX_VRAM_SUB_BG_32_H  || \
                (x) == GX_VRAM_SUB_BG_48_HI )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForSubOBJ etc.
//----------------------------------------------------------------------------
typedef enum
{
    GX_VRAM_SUB_OBJ_NONE = 0x0000,
    GX_VRAM_SUB_OBJ_128_D = GX_VRAM_D,
    GX_VRAM_SUB_OBJ_16_I = GX_VRAM_I
}
GXVRamSubOBJ;

#define GX_VRAM_SUB_OBJ_ASSERT(x)               \
    SDK_ASSERT( (x) == GX_VRAM_SUB_OBJ_NONE  || \
                (x) == GX_VRAM_SUB_OBJ_128_D || \
                (x) == GX_VRAM_SUB_OBJ_16_I )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForSubBGExtPltt etc.
//----------------------------------------------------------------------------

#define GX_VRAM_SUB_BGEXTPLTT_32_H GX_VRAM_SUB_BGEXTPLTT_0123_H

typedef enum
{
    GX_VRAM_SUB_BGEXTPLTT_NONE = 0x0000,
    GX_VRAM_SUB_BGEXTPLTT_0123_H = GX_VRAM_H
}
GXVRamSubBGExtPltt;

#define GX_VRAM_SUB_BGEXTPLTT_ASSERT(x)              \
    SDK_ASSERT( (x) == GX_VRAM_SUB_BGEXTPLTT_NONE || \
                (x) == GX_VRAM_SUB_BGEXTPLTT_0123_H )

//----------------------------------------------------------------------------
//    Parameters for GX_SetBankForSubOBJExtPltt etc.
//----------------------------------------------------------------------------

#define GX_VRAM_SUB_OBJEXTPLTT_16_I GX_VRAM_SUB_OBJEXTPLTT_0_I

typedef enum
{
    GX_VRAM_SUB_OBJEXTPLTT_NONE = 0x0000,
    GX_VRAM_SUB_OBJEXTPLTT_0_I = GX_VRAM_I
}
GXVRamSubOBJExtPltt;

#define GX_VRAM_SUB_OBJEXTPLTT_ASSERT(x)              \
    SDK_ASSERT( (x) == GX_VRAM_SUB_OBJEXTPLTT_NONE || \
                (x) == GX_VRAM_SUB_OBJEXTPLTT_0_I )



/* if include from Other Environment for exsample VC or BCB, */
/* please define SDK_FROM_TOOL                               */
#if !(defined(SDK_WIN32) || defined(SDK_FROM_TOOL))

//----------------------------------------------------------------------------
// Declaration of function
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
// Main engine
//
//----------------------------------------------------------------------------
void    GX_SetBankForBG(GXVRamBG bg);
BOOL    GX_TrySetBankForBG(GXVRamBG bg);
void    GX_SetBankForBGEx(GXVRamBG bg1, GXVRamBG bg2);
BOOL    GX_TrySetBankForBGEx(GXVRamBG bg1, GXVRamBG bg2);
void    GX_SetBankForOBJ(GXVRamOBJ obj);
BOOL    GX_TrySetBankForOBJ(GXVRamOBJ obj);
void    GX_SetBankForBGExtPltt(GXVRamBGExtPltt bgExtPltt);
BOOL    GX_TrySetBankForBGExtPltt(GXVRamBGExtPltt bgExtPltt);
void    GX_SetBankForOBJExtPltt(GXVRamOBJExtPltt objExtPltt);
BOOL    GX_TrySetBankForOBJExtPltt(GXVRamOBJExtPltt objExtPltt);
void    GX_SetBankForTex(GXVRamTex tex);
BOOL    GX_TrySetBankForTex(GXVRamTex tex);
void    GX_SetBankForTexPltt(GXVRamTexPltt texPltt);
BOOL    GX_TrySetBankForTexPltt(GXVRamTexPltt texPltt);
void    GX_SetBankForClearImage(GXVRamClearImage clrImg);
BOOL    GX_TrySetBankForClearImage(GXVRamClearImage clrImg);

GXVRamBG GX_GetBankForBG(void);
GXVRamOBJ GX_GetBankForOBJ(void);
GXVRamBGExtPltt GX_GetBankForBGExtPltt(void);
GXVRamOBJExtPltt GX_GetBankForOBJExtPltt(void);
GXVRamTex GX_GetBankForTex(void);
GXVRamTexPltt GX_GetBankForTexPltt(void);
GXVRamClearImage GX_GetBankForClearImage(void);

GXVRamBG GX_ResetBankForBG(void);
GXVRamOBJ GX_ResetBankForOBJ(void);
GXVRamBGExtPltt GX_ResetBankForBGExtPltt(void);
GXVRamOBJExtPltt GX_ResetBankForOBJExtPltt(void);
GXVRamTex GX_ResetBankForTex(void);
GXVRamTexPltt GX_ResetBankForTexPltt(void);
GXVRamClearImage GX_ResetBankForClearImage(void);

GXVRamBG GX_DisableBankForBG(void);
GXVRamOBJ GX_DisableBankForOBJ(void);
GXVRamBGExtPltt GX_DisableBankForBGExtPltt(void);
GXVRamOBJExtPltt GX_DisableBankForOBJExtPltt(void);
GXVRamTex GX_DisableBankForTex(void);
GXVRamTexPltt GX_DisableBankForTexPltt(void);
GXVRamClearImage GX_DisableBankForClearImage(void);

u32     GX_GetSizeOfBG(void);
u32     GX_GetSizeOfOBJ(void);
u32     GX_GetSizeOfBGExtPltt(void);
u32     GX_GetSizeOfOBJExtPltt(void);
u32     GX_GetSizeOfTex(void);
u32     GX_GetSizeOfTexPltt(void);
u32     GX_GetSizeOfClearImage(void);

//----------------------------------------------------------------------------
// Sub engine
//----------------------------------------------------------------------------
void    GX_SetBankForSubBG(GXVRamSubBG sub_bg);
BOOL    GX_TrySetBankForSubBG(GXVRamSubBG sub_bg);
void    GX_SetBankForSubOBJ(GXVRamSubOBJ sub_obj);
BOOL    GX_TrySetBankForSubOBJ(GXVRamSubOBJ sub_obj);
void    GX_SetBankForSubBGExtPltt(GXVRamSubBGExtPltt sub_bgExtPltt);
BOOL    GX_TrySetBankForSubBGExtPltt(GXVRamSubBGExtPltt sub_bgExtPltt);
void    GX_SetBankForSubOBJExtPltt(GXVRamSubOBJExtPltt sub_objExtPltt);
BOOL    GX_TrySetBankForSubOBJExtPltt(GXVRamSubOBJExtPltt sub_objExtPltt);

GXVRamSubBG GX_GetBankForSubBG(void);
GXVRamSubOBJ GX_GetBankForSubOBJ(void);
GXVRamSubBGExtPltt GX_GetBankForSubBGExtPltt(void);
GXVRamSubOBJExtPltt GX_GetBankForSubOBJExtPltt(void);

GXVRamSubBG GX_ResetBankForSubBG(void);
GXVRamSubOBJ GX_ResetBankForSubOBJ(void);
GXVRamSubBGExtPltt GX_ResetBankForSubBGExtPltt(void);
GXVRamSubOBJExtPltt GX_ResetBankForSubOBJExtPltt(void);

GXVRamSubBG GX_DisableBankForSubBG(void);
GXVRamSubOBJ GX_DisableBankForSubOBJ(void);
GXVRamSubBGExtPltt GX_DisableBankForSubBGExtPltt(void);
GXVRamSubOBJExtPltt GX_DisableBankForSubOBJExtPltt(void);

u32     GX_GetSizeOfSubBG(void);
u32     GX_GetSizeOfSubOBJ(void);
u32     GX_GetSizeOfSubBGExtPltt(void);
u32     GX_GetSizeOfSubOBJExtPltt(void);

//----------------------------------------------------------------------------
// Others
//----------------------------------------------------------------------------
void    GX_SetBankForARM7(GXVRamARM7 arm7);
BOOL    GX_TrySetBankForARM7(GXVRamARM7 arm7);
void    GX_SetBankForLCDC(int lcdc);
BOOL    GX_TrySetBankForLCDC(int lcdc);

GXVRamARM7 GX_GetBankForARM7(void);
GXVRamLCDC GX_GetBankForLCDC(void);

GXVRamARM7 GX_ResetBankForARM7(void);

GXVRamARM7 GX_DisableBankForARM7(void);
GXVRamLCDC GX_DisableBankForLCDC(void);

u32     GX_GetSizeOfARM7(void);



#endif // SDK_FROM_TOOL

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
