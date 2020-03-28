/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     protectionRegion.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: protectionRegion.h,v $
  Revision 1.16  2006/02/10 02:06:11  yosizaki
  fix typo (HW_C5_PRn_SHIFT to HW_C5_PRn_SFT)

  Revision 1.15  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.14  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.13  2005/01/11 07:53:35  takano_makoto
  fix copyright header.

  Revision 1.12  2005/01/05 02:20:01  yada
  just fix comment

  Revision 1.11  2004/11/02 11:05:14  yada
  fix a little

  Revision 1.10  2004/11/02 10:40:48  yada
  add definition about protection region for convinience

  Revision 1.9  2004/09/30 00:12:04  yada
  fix typo

  Revision 1.8  2004/09/02 06:28:04  yada
  only change comment

  Revision 1.7  2004/07/08 02:29:57  yada
  consider for protection region enable flag

  Revision 1.6  2004/06/11 06:23:41  yada
  close SDK_BB support

  Revision 1.5  2004/05/28 11:04:33  yada
  fix comment. change function name about set up protection region and get setting

  Revision 1.4  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.3  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.2  2004/01/16 07:57:15  yada
  Description of protectionUnit

  Revision 1.1  2003/12/08 12:22:34  yada
  Initial release.


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_PROTECTIONREGION_H_
#define NITRO_OS_PROTECTIONREGION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"

#define OS_PR0_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR0_SFT)
#define OS_PR0_ACCESS_NA     (HW_C5_PERMIT_NA   << HW_C5_PR0_SFT)
#define OS_PR0_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR0_SFT)
#define OS_PR0_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR0_SFT)

#define OS_PR1_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR1_SFT)
#define OS_PR1_ACCESS_NA     (HW_C5_PERMIT_NA   << HW_C5_PR1_SFT)
#define OS_PR1_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR1_SFT)
#define OS_PR1_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR1_SFT)

#define OS_PR2_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR2_SFT)
#define OS_PR2_ACCESS_NA     (HW_C5_PERMIT_NA   << HW_C5_PR2_SFT)
#define OS_PR2_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR2_SFT)
#define OS_PR2_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR2_SFT)

#define OS_PR3_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR3_SFT)
#define OS_PR3_ACCESS_NA     (HW_C5_PERMIT_NA   << HW_C5_PR3_SFT)
#define OS_PR3_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR3_SFT)
#define OS_PR3_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR3_SFT)

#define OS_PR4_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR4_SFT)
#define OS_PR4_ACCESS_NA     (HW_C5_PERMIT_NA   << HW_C5_PR4_SFT)
#define OS_PR4_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR4_SFT)
#define OS_PR4_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR4_SFT)

#define OS_PR5_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR5_SFT)
#define OS_PR5_ACCESS_NA     (HW_C5_PERMIT_NA   << HW_C5_PR5_SFT)
#define OS_PR5_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR5_SFT)
#define OS_PR5_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR5_SFT)

#define OS_PR6_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR6_SFT)
#define OS_PR6_ACCESS_NA     (HW_C5_PERMIT_NA   << HW_C5_PR6_SFT)
#define OS_PR6_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR6_SFT)
#define OS_PR6_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR6_SFT)

#define OS_PR7_ACCESS_MASK   (HW_C5_PERMIT_MASK << HW_C5_PR7_SFT)
#define OS_PR7_ACCESS_NA     (HW_C5_PERMIT_NA   << HW_C5_PR7_SFT)
#define OS_PR7_ACCESS_RW     (HW_C5_PERMIT_RW   << HW_C5_PR7_SFT)
#define OS_PR7_ACCESS_RO     (HW_C5_PERMIT_RO   << HW_C5_PR7_SFT)

//================================================================================
//               Instruction Cache for each protection region
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_EnableICacheForProtectionRegion
                OS_DisableICacheForProtectionRegion

  Description:  enable/disable instruction cache for each protection region

  Arguments:    flags:  Each bit shows the region to be enable/disable.
                           bit0(LSB) ... protection region 0
                           bit1      ... protection region 1
                             :                  :
                           bit7      ... protection region 7

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_EnableICacheForProtectionRegion(register u32 flags);
void    OS_DisableICacheForProtectionRegion(register u32 flags);


/*---------------------------------------------------------------------------*
  Name:         OS_GetICacheEnableFlagsForProtectionRegion

  Description:  get instruction cache status for each protection region

  Arguments:    None

  Returns:      instruction cache status.
                bit for each protection region, means 1... enable, 0... disable

                           bit0(LSB) ... protection region 0
                           bit1      ... protection region 1
                             :                  :
                           bit7      ... protection region 7

 *---------------------------------------------------------------------------*/
u32     OS_GetICacheEnableFlagsForProtectionRegion(void);

/*---------------------------------------------------------------------------*
  Name:         OS_SetIPermissionsForProtectionRegion

  Description:  set instruction access limitation for each protection region

  Arguments:    setMask : set mask bit, which is or-ed by mask.
                flags   : flag bit, which is or-ed by access limitation.

                   (mask)
                          OS_PRn_ACCESS_MASK (n=0-7)

                   (access limitation)
                          OS_PRn_ACCESS_NA    no permission to access
                          OS_PRn_ACCESS_RW    read and write permission
                          OS_PRn_ACCESS_RO    read only permission
                          (n=0-7)

                ex.
                    In case to set region3 readonly and region6 no permission, call
                    OS_SetIPermissionsForProtectionRegion(
                             OS_PR3_ACCESS_MASK | OS_PR6_ACCESS_MASK,
                             OS_PR3_ACCESS_RO | OS_PR6_ACCESS_NA );

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SetIPermissionsForProtectionRegion(u32 setMask, u32 flags);

/*---------------------------------------------------------------------------*
  Name:         OS_GetIPermissionsForProtectionRegion

  Description:  get instruction access limitation for each protection region

  Arguments:    None

  Returns:      Return value & OS_PRn_ACCESS_MASK (n=0-7) shows access limitation.

                   (access limitation)
                          OS_PRn_ACCESS_NA    no permission to access
                          OS_PRn_ACCESS_RW    read and write permission
                          OS_PRn_ACCESS_RO    read only permission
                          (n=0-7)

 *---------------------------------------------------------------------------*/
u32     OS_GetIPermissionsForProtectionRegion(void);


//================================================================================
//               Data Cache for each protection region
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_EnableDCacheForProtectionRegion
                OS_DisableDCacheForProtectionRegion

  Description:  enable/disable data cache for each protection region

  Arguments:    flags :  Each bit shows the region to be enable/disable.
                           bit0(LSB) ... protection region 0
                           bit1      ... protection region 1
                             :                  :
                           bit7      ... protection region 7

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_EnableDCacheForProtectionRegion(u32 flags);
void    OS_DisableDCacheForProtectionRegion(u32 flags);

/*---------------------------------------------------------------------------*
  Name:         OS_GetDCacheEnableFlagsForProtectionRegion

  Description:  get data cache status for each protection region

  Arguments:    None

  Returns:      data cache status.
                bit for each protection region, means 1... enable, 0... disable

                           bit0(LSB) ... protection region 0
                           bit1      ... protection region 1
                             :                  :
                           bit7      ... protection region 7

 *---------------------------------------------------------------------------*/
u32     OS_GetDCacheEnableFlagsForProtectionRegion(u32 flags);

/*---------------------------------------------------------------------------*
  Name:         OS_SetDPermissionsForProtectionRegion

  Description:  set data access limitation for each protection region

  Arguments:    setMask : set mask bit, which is or-ed by mask.
                flags   : flag bit, which is or-ed by access limitation.

                   (mask)
                          OS_PRn_ACCESS_MASK (n=0-7)

                   (access limitation)
                          OS_PRn_ACCESS_NA    no permission to access
                          OS_PRn_ACCESS_RW    read and write permission
                          OS_PRn_ACCESS_RO    read only permission
                          (n=0-7)

                ex.
                    In case to set region3 readonly and region6 no permission, call
                    OS_SetDPermissionsForProtectionRegion(
                             OS_PR3_ACCESS_MASK | OS_PR6_ACCESS_MASK,
                             OS_PR3_ACCESS_RO | OS_PR6_ACCESS_NA );

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SetDPermissionsForProtectionRegion(u32 setMask, u32 flags);

/*---------------------------------------------------------------------------*
  Name:         OS_GetDPermissionsForProtectionRegion

  Description:  get data access limitation for each protection region

  Arguments:    None

  Returns:      Return value & OS_PRn_ACCESS_MASK (n=0-7) shows access limitation.

                   (access limitation)
                          OS_PRn_ACCESS_NA    no permission to access
                          OS_PRn_ACCESS_RW    read and write permission
                          OS_PRn_ACCESS_RO    read only permission
                          (n=0-7)

 *---------------------------------------------------------------------------*/
u32     OS_GetDPermissionsForProtectionRegion(void);


//================================================================================
//               Write buffer for each protection region
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_EnableWriteBufferForProtectionRegion
                OS_DisableWriteBufferForProtectionRegion

  Description:  enable/disable write buffer for each protection region

  Arguments:    flags :  Each bit shows the region to be enable/disable.
                           bit0(LSB) ... protection region 0
                           bit1      ... protection region 1
                             :                  :
                           bit7      ... protection region 7

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_EnableWriteBufferForProtectionRegion(u32 flags);
void    OS_DisableWriteBufferForProtectionRegion(u32 flags);

/*---------------------------------------------------------------------------*
  Name:         OS_GetWriteBufferEnableFlagsForProtectionRegion

  Description:  get write buffer status for each protection region

  Arguments:    None

  Returns:      write buffer status.
                bit for each protection region, means 1... enable, 0... disable

                           bit0(LSB) ... protection region 0
                           bit1      ... protection region 1
                             :                  :
                           bit7      ... protection region 7

 *---------------------------------------------------------------------------*/
u32     OS_GetWriteBufferEnableFlagsForProtectionRegion(u32 flags);



//================================================================================
//          protection region
//================================================================================

typedef enum
{
    OSi_PR_BASE_MASK_4KB = 0xfffff000,
    OSi_PR_BASE_MASK_8KB = 0xffffe000,
    OSi_PR_BASE_MASK_16KB = 0xffffc000,
    OSi_PR_BASE_MASK_32KB = 0xffff8000,
    OSi_PR_BASE_MASK_64KB = 0xffff0000,
    OSi_PR_BASE_MASK_128KB = 0xfffe0000,
    OSi_PR_BASE_MASK_256KB = 0xfffc0000,
    OSi_PR_BASE_MASK_512KB = 0xfff80000,
    OSi_PR_BASE_MASK_1MB = 0xfff00000,
    OSi_PR_BASE_MASK_2MB = 0xffe00000,
    OSi_PR_BASE_MASK_4MB = 0xffc00000,
    OSi_PR_BASE_MASK_8MB = 0xff800000,
    OSi_PR_BASE_MASK_16MB = 0xff000000,
    OSi_PR_BASE_MASK_32MB = 0xfe000000,
    OSi_PR_BASE_MASK_64MB = 0xfc000000,
    OSi_PR_BASE_MASK_128MB = 0xf8000000,
    OSi_PR_BASE_MASK_256MB = 0xf0000000,
    OSi_PR_BASE_MASK_512MB = 0xe0000000,
    OSi_PR_BASE_MASK_1GB = 0xc0000000,
    OSi_PR_BASE_MASK_2GB = 0x80000000,
    OSi_PR_BASE_MASK_4GB = 0x00000000
}
OSiProtectionRegionBaseMask;

static inline u32 OSi_CalcPRParam(u32 address, u32 size, OSiProtectionRegionBaseMask mask)
{
#ifdef SDK_DEBUG
    SDK_ASSERT((address & mask) == address);
#endif
    return ((address & mask) | size);
}

/*---------------------------------------------------------------------------*
  Name:         OS_SetProtectionRegion

  Description:  set up parameter of protection region

  Arguments:    regionNo :   region number
                address  :   base address
                sizeStr  :   string that stands for size

               regionNo must be immidiate number, from 0 to 7.
               address can be valiable
               sizeStr is 4KB or 8KB or 16KB or ... 4GB

               ex. OSi_SetProtectionRegion( 3, 0x2000000, 4KB );

  Returns:      None
 *---------------------------------------------------------------------------*/
#define OS_SetProtectionRegion( regionNo, address, sizeStr )  \
  OSi_SetPR##regionNo##_param( OSi_CalcPRParam( address, HW_C6_PR_##sizeStr, OSi_PR_BASE_MASK_##sizeStr ) \
                              | HW_C6_PR_ENABLE )


/*---------------------------------------------------------------------------*
  Name:         OS_SetProtectionRegion*

  Description:  set up parameter of protection region

  Arguments:    regionNo :   region number
                param    :   parameter ( created from base address and size )

  Returns:      None
 *---------------------------------------------------------------------------*/
#define OS_SetProtectionRegionParam( regionNo, param )   OSi_SetPR##regionNo##_param( param )

#define OSi_SetPR0_param( param )  OS_SetProtectionRegion0( param )
#define OSi_SetPR1_param( param )  OS_SetProtectionRegion1( param )
#define OSi_SetPR2_param( param )  OS_SetProtectionRegion2( param )
#define OSi_SetPR3_param( param )  OS_SetProtectionRegion3( param )
#define OSi_SetPR4_param( param )  OS_SetProtectionRegion4( param )
#define OSi_SetPR5_param( param )  OS_SetProtectionRegion5( param )
#define OSi_SetPR6_param( param )  OS_SetProtectionRegion6( param )
#define OSi_SetPR7_param( param )  OS_SetProtectionRegion7( param )

void    OS_SetProtectionRegion0(u32 param);
void    OS_SetProtectionRegion1(u32 param);
void    OS_SetProtectionRegion2(u32 param);
void    OS_SetProtectionRegion3(u32 param);
void    OS_SetProtectionRegion4(u32 param);
void    OS_SetProtectionRegion5(u32 param);
void    OS_SetProtectionRegion6(u32 param);
void    OS_SetProtectionRegion7(u32 param);

/*---------------------------------------------------------------------------*
  Name:         OS_GetProtectionRegionParam

  Description:  get parameter of protection region

  Arguments:    regionNo :   region number

  Returns:      parameter of protection region ( created from base address and size )
 *---------------------------------------------------------------------------*/
#define OS_GetProtectionRegionParam( regionNo )       OSi_GetPR##regionNo##_param()

#define OSi_GetPR0_param()  OS_GetProtectionRegion0()
#define OSi_GetPR1_param()  OS_GetProtectionRegion1()
#define OSi_GetPR2_param()  OS_GetProtectionRegion2()
#define OSi_GetPR3_param()  OS_GetProtectionRegion3()
#define OSi_GetPR4_param()  OS_GetProtectionRegion4()
#define OSi_GetPR5_param()  OS_GetProtectionRegion5()
#define OSi_GetPR6_param()  OS_GetProtectionRegion6()
#define OSi_GetPR7_param()  OS_GetProtectionRegion7()

u32     OS_GetProtectionRegion0(void);
u32     OS_GetProtectionRegion1(void);
u32     OS_GetProtectionRegion2(void);
u32     OS_GetProtectionRegion3(void);
u32     OS_GetProtectionRegion4(void);
u32     OS_GetProtectionRegion5(void);
u32     OS_GetProtectionRegion6(void);
u32     OS_GetProtectionRegion7(void);

/*---------------------------------------------------------------------------*
  Name:         OS_GetProtectionRegionAddress

  Description:  get parameter of protection region

  Arguments:    regionNo :   region number

  Returns:      base address of protection region.
 *---------------------------------------------------------------------------*/
#define OS_GetProtectionRegionAddress( regionNo )  ( OS_GetProtectionRegion( regionNo ) & HW_C6_PR_BASE_MASK )

/*---------------------------------------------------------------------------*
  Name:         OS_GetProtectionRegionSize

  Description:  get parameter of protection region

  Arguments:    regionNo :   region number

  Returns:      size parameter of protection region.
                parameter is HW_C6_PR_SIZE_xxx, xxx is 4KB or 8KB or ... 4GB
 *---------------------------------------------------------------------------*/
#define OS_GetProtectionRegionSize( regionNo )  ( OS_GetProtectionRegion( regionNo ) & HW_C6_PR_SIZE_MASK )


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_PROTECTIONREGION_H_ */
#endif
