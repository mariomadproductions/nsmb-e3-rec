/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SPI - include
  File:     config.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: config.h,v $
  Revision 1.18  2005/04/12 10:49:15  terui
  Made alterations to support Chinese language

  Revision 1.17  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.16  2004/10/01 02:54:29  terui
  Added the offset definition to the wireless use permitted channel in NVRAM

  Revision 1.15  2004/09/13 05:49:56  yasu
  merged with NitroSDK_2_00pr6_branch

  Revision 1.14.2.1  2004/09/13 05:43:02  yasu
  Support SDK_NVRAM_FORMAT

  Revision 1.14  2004/09/03 11:48:54  yasu
  fix typo

  Revision 1.13  2004/09/03 04:29:15  terui
  Revised according to structure definition adjustments relating to user information in NVRAM.

  Revision 1.12  2004/09/02 02:24:36  terui
  Added wireless MAC address storage location to definition.

  Revision 1.11  2004/08/31 09:46:16  yosiokat
  Changed SDK_SMALL_BUILD to SDK_NCD_LOCAL_USE.

  Revision 1.10  2004/08/27 12:39:04  yosiokat
  Changed IPL2_BUILD_ to SDK_SMALL_BUILD

  Revision 1.9  2004/08/25 09:21:50  terui
  Brought the userInfo definition to a different file, and changed to switch at TS_VERSION.

  Revision 1.8  2004/07/27 11:04:17  yasu
  Add #pragma  warn_padding off for SDK_TEG

  Revision 1.7  2004/07/27 07:00:10  yasu
  Add padding explicitly

  Revision 1.6  2004/06/30 10:36:18  terui
  Changed the user info format definition in TS

  Revision 1.5  2004/06/30 09:12:11  terui
  Changed the definition to use an offset to facilitate search of user info in NVRAM with TS

  Revision 1.4  2004/05/21 07:57:30  terui
  User info address can now be a fixed value.
  Expanded touch panel calibration data field to 12 bytes.

  Revision 1.3  2004/05/21 05:52:30  yosiokat
  Revised so that this file is not included with IPl2 build.

  Revision 1.2  2004/05/20 10:31:33  takano_makoto
  Corrected bugs that caused compilation problems with C++

  Revision 1.1  2004/05/20 09:41:06  terui
  Added user info offset address definitions etc.

  Revision 1.2  2004/05/19 08:25:28  yosiokat
  Added update log.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_SPI_COMMON_CONFIG_H_
#define NITRO_SPI_COMMON_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include "nitro/types.h"
#include "nitro/memorymap.h"
#include "nitro/spec.h"

// userInfo definition
#ifdef  SDK_TS
#if ( SDK_TS_VERSION >= 200 || SDK_NVRAM_FORMAT >= 100 )
#if ( SDK_NVRAM_FORMAT >= 300 )
#include "nitro/spi/common/userInfo_ts_300.h"
#else
#include "nitro/spi/common/userInfo_ts_200.h"
#endif
#else
#include "nitro/spi/common/userInfo_ts_0.h"
#endif
#else
#include "nitro/spi/common/userInfo_teg.h"
#endif

// userInfo store place in NVRAM
#ifdef  SDK_TS
#undef  NVRAM_CONFIG_CONST_ADDRESS     // User info position is obtained from header offset
#else
#define NVRAM_CONFIG_CONST_ADDRESS     // User information position is made a fixed address
#endif

#ifdef  NVRAM_CONFIG_CONST_ADDRESS
#define NVRAM_CONFIG_DATA_ADDRESS_DUMMY     0x3fe00
#else
#define NVRAM_CONFIG_DATA_OFFSET_ADDRESS    0x0020
#define NVRAM_CONFIG_DATA_OFFSET_SIZE       2
#define NVRAM_CONFIG_DATA_OFFSET_SHIFT      3
#endif

#define NVRAM_CONFIG_SAVE_COUNT_MAX         0x0080      // Max. value of NitroConfigData.saveCount
#define NVRAM_CONFIG_SAVE_COUNT_MASK        0x007f      // Masks the range of NitroConfigData.saveCount values. (0x00-0x7f)

// MAC address storage location in NVRAM
#define NVRAM_CONFIG_MACADDRESS_ADDRESS     0x00036
#define NVRAM_CONFIG_ENABLECHANNEL_ADDRESS  0x0003c

/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_SPI_COMMON_CONFIG_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
