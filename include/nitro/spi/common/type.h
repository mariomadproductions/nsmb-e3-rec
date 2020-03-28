/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SPI - include
  File:     type.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: type.h,v $
  Revision 1.23  2006/01/18 02:12:38  kitase_hirotake
  do-indent

  Revision 1.22  2005/12/14 02:04:23  yada
  add SPI_PXI_COMMAND_PM_REG4VALUE for PMIC2

  Revision 1.21  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.20  2005/01/11 07:54:25  takano_makoto
  fix copyright header.

  Revision 1.19  2005/01/07 12:29:33  terui
  Added SPI_PXI_COMMAND_MIC_AUTO_ADJUST definition.

  Revision 1.18  2004/12/29 02:09:22  takano_makoto
  Removed retry parameter in SetStability function

  Revision 1.17  2004/12/28 12:34:32  takano_makoto
  Changed the default value of chattering parameter

  Revision 1.16  2004/12/03 05:40:03  terui
  Complied with the added feature that explicitly indicates the data that was left out during the MIC auto sampling.

  Revision 1.15  2004/10/20 06:34:10  terui
  Deleted the line number definition of LCD

  Revision 1.14  2004/10/07 06:49:34  terui
  Made correction due to the addition of commands for the NVRAM made by a different manufacturer.

  Revision 1.13  2004/09/29 06:39:01  takano_makoto
  Changed value of SPI_TP_DEFAULT_STABILITY_RANGE and SPI_TP_DEFAULT_STABILITY_RETRY.

  Revision 1.12  2004/08/26 08:19:13  yada
  add definition for get LED status

  Revision 1.11  2004/08/23 08:10:03  yada
  add some SPI_PXI_COMMAND_PM_XXXX definition

  Revision 1.10  2004/08/09 13:25:12  takano_makoto
  Added SPI_MIC_SAMPLING_TYPE_MIX_TP_XXX.

  Revision 1.9  2004/08/05 06:06:37  yada
  PRE_SLEEP_START -> SYNC

  Revision 1.8  2004/08/03 08:41:18  yada
  fix a little

  Revision 1.7  2004/08/02 06:08:31  yada
  standby->sleep

  Revision 1.6  2004/08/02 00:49:35  yada
  sleep->standby

  Revision 1.5  2004/07/29 09:01:28  yada
  add pxi command about PM

  Revision 1.4  2004/07/13 09:21:21  terui
  Changes reflecting addition of signed sampling types

  Revision 1.3  2004/05/31 08:39:48  terui
  Added definitions relating to protocol

  Revision 1.2  2004/05/28 09:23:11  terui
  Changed TP max. number of samples (16->4)

  Revision 1.1  2004/05/28 08:49:32  terui
  Removed definitions from library's local header

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_SPI_COMMON_TYPE_H_
#define NITRO_SPI_COMMON_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

/*---------------------------------------------------------------------------*
    constant definitions
 *---------------------------------------------------------------------------*/
// Definitions related to PXI communications protocol
#define SPI_PXI_START_BIT                   0x02000000  // Contiguous packet start bit
#define SPI_PXI_END_BIT                     0x01000000  // Contiguous packet completion bit
#define SPI_PXI_INDEX_MASK                  0x000f0000  // Defines bit arrangement that indicates
#define SPI_PXI_INDEX_SHIFT                 16  //  contiguous packet data
#define SPI_PXI_DATA_MASK                   0x0000ffff  // Defines bit arrangement that indicates
#define SPI_PXI_DATA_SHIFT                  0   //  contiguous packet data
#define SPI_PXI_RESULT_COMMAND_BIT          0x00008000  // Bit that indicates response
#define SPI_PXI_RESULT_COMMAND_MASK         0x00007f00  // Defines bit arrangement of
#define SPI_PXI_RESULT_COMMAND_SHIFT        8   //  response command result
#define SPI_PXI_RESULT_DATA_MASK            0x000000ff  // Defines bit arrangement of
#define SPI_PXI_RESULT_DATA_SHIFT           0   //  response command result
#define SPI_PXI_CONTINUOUS_PACKET_MAX       16  // Maximum number of contiguity in a contiguous packet

// Instruction group issued by ARM9 via PXI (The one with 0x10 bit set to 1 are the notification command from ARM7)
#define SPI_PXI_COMMAND_TP_SAMPLING         0x0000
#define SPI_PXI_COMMAND_TP_AUTO_ON          0x0001
#define SPI_PXI_COMMAND_TP_AUTO_OFF         0x0002
#define SPI_PXI_COMMAND_TP_SETUP_STABILITY  0x0003
#define SPI_PXI_COMMAND_TP_AUTO_SAMPLING    0x0010      // for notifying the course of auto sampling

#define SPI_PXI_COMMAND_NVRAM_WREN          0x0020
#define SPI_PXI_COMMAND_NVRAM_WRDI          0x0021
#define SPI_PXI_COMMAND_NVRAM_RDSR          0x0022
#define SPI_PXI_COMMAND_NVRAM_READ          0x0023
#define SPI_PXI_COMMAND_NVRAM_FAST_READ     0x0024
#define SPI_PXI_COMMAND_NVRAM_PW            0x0025
#define SPI_PXI_COMMAND_NVRAM_PP            0x0026
#define SPI_PXI_COMMAND_NVRAM_PE            0x0027
#define SPI_PXI_COMMAND_NVRAM_SE            0x0028
#define SPI_PXI_COMMAND_NVRAM_DP            0x0029
#define SPI_PXI_COMMAND_NVRAM_RDP           0x002a
#define SPI_PXI_COMMAND_NVRAM_CE            0x002b
#define SPI_PXI_COMMAND_NVRAM_RSI           0x002c
#define SPI_PXI_COMMAND_NVRAM_SR            0x002d

#define SPI_PXI_COMMAND_MIC_SAMPLING        0x0040
#define SPI_PXI_COMMAND_MIC_AUTO_ON         0x0041
#define SPI_PXI_COMMAND_MIC_AUTO_OFF        0x0042
#define SPI_PXI_COMMAND_MIC_AUTO_ADJUST     0x0043
#define SPI_PXI_COMMAND_MIC_BUFFER_FULL     0x0051

// for PM
#define SPI_PXI_COMMAND_PM_SYNC             0x0060
#define SPI_PXI_COMMAND_PM_SLEEP_START      0x0061
#define SPI_PXI_COMMAND_PM_SLEEP_END        0x0062
#define SPI_PXI_COMMAND_PM_UTILITY          0x0063
#define SPI_PXI_COMMAND_PM_REG_WRITE        0x0064
#define SPI_PXI_COMMAND_PM_REG_READ         0x0065
#define SPI_PXI_COMMAND_PM_SELF_BLINK       0x0066
#define SPI_PXI_COMMAND_PM_GET_BLINK        0x0067
#define SPI_PXI_COMMAND_PM_REG0VALUE        0x0070
#define SPI_PXI_COMMAND_PM_REG1VALUE        0x0071
#define SPI_PXI_COMMAND_PM_REG2VALUE        0x0072
#define SPI_PXI_COMMAND_PM_REG3VALUE        0x0073
#define SPI_PXI_COMMAND_PM_REG4VALUE        0x0074

    // *********************************************
    // ****** Additional PMIC definitions **********
    // *********************************************

// Responses returned by ARM7 via PXI
#define SPI_PXI_RESULT_SUCCESS              0x0000      // Succeeded
#define SPI_PXI_RESULT_INVALID_COMMAND      0x0001      // Instruction is abnormal
#define SPI_PXI_RESULT_INVALID_PARAMETER    0x0002      // Parameter is abnormal
#define SPI_PXI_RESULT_ILLEGAL_STATUS       0x0003      // State that cannot receive instructions
#define SPI_PXI_RESULT_EXCLUSIVE            0x0004      // SPI device is excluded.

// Touch panel related definitions
#define SPI_TP_SAMPLING_FREQUENCY_MAX       4           // The maximum value of auto sampling frequency
#define SPI_TP_DEFAULT_STABILITY_RANGE      20          // Output range difference that is permitted when the stability is determined. (initial value)
#define SPI_TP_VALARM_TAG                   0x54505641  // "TPVA" --tag for TP V alarm

// NVRAM (Flash ROM) related definitions
#define SPI_NVRAM_PAGE_SIZE                 256
#define SPI_NVRAM_SECTOR_SIZE               ( SPI_NVRAM_PAGE_SIZE * 256 )
#define SPI_NVRAM_ALL_SIZE                  ( SPI_NVRAM_SECTOR_SIZE * 8 )

// Microphone related definitions
#define SPI_MIC_SAMPLING_TYPE_8BIT          0x0000
#define SPI_MIC_SAMPLING_TYPE_12BIT         0x0001
#define SPI_MIC_SAMPLING_TYPE_S8BIT         0x0002
#define SPI_MIC_SAMPLING_TYPE_S12BIT        0x0003
#define SPI_MIC_SAMPLING_TYPE_FILTER_ON     0x0000
#define SPI_MIC_SAMPLING_TYPE_FILTER_OFF    0x0004
#define SPI_MIC_SAMPLING_TYPE_ADMODE_MASK   0x0007
#define SPI_MIC_SAMPLING_TYPE_BIT_MASK      0x0001
#define SPI_MIC_SAMPLING_TYPE_SIGNED_MASK   0x0002
#define SPI_MIC_SAMPLING_TYPE_FILTER_MASK   0x0004

#define SPI_MIC_SAMPLING_TYPE_LOOP_OFF      0x0000
#define SPI_MIC_SAMPLING_TYPE_LOOP_ON       0x0010
#define SPI_MIC_SAMPLING_TYPE_LOOP_MASK     0x0010

#define SPI_MIC_SAMPLING_TYPE_CORRECT_OFF   0x0000
#define SPI_MIC_SAMPLING_TYPE_CORRECT_ON    0x0020
#define SPI_MIC_SAMPLING_TYPE_CORRECT_MASK  0x0020

#define SPI_MIC_SAMPLING_TYPE_MIX_TP_OFF    0x0000
#define SPI_MIC_SAMPLING_TYPE_MIX_TP_ON     0x0040
#define SPI_MIC_SAMPLING_TYPE_MIX_TP_MASK   0x0040


/*---------------------------------------------------------------------------*
    structure definitions
 *---------------------------------------------------------------------------*/
// SPI-related device types
typedef enum SPIDeviceType
{
    SPI_DEVICE_TYPE_TP = 0,            // Touch panel
    SPI_DEVICE_TYPE_NVRAM,             // NVRAM (Flash ROM)
    SPI_DEVICE_TYPE_MIC,               // Microphone
    SPI_DEVICE_TYPE_PM,                // Power management IC
    SPI_DEVICE_TYPE_ARM7,
    SPI_DEVICE_TYPE_MAX
}
SPIDeviceType;

// Touch panel contact
typedef enum SPITpTouch
{
    SPI_TP_TOUCH_OFF = 0,
    SPI_TP_TOUCH_ON
}
SPITpTouch;

// Touch panel data validity
typedef enum SPITpValidity
{
    SPI_TP_VALIDITY_VALID = 0,
    SPI_TP_VALIDITY_INVALID_X,
    SPI_TP_VALIDITY_INVALID_Y,
    SPI_TP_VALIDITY_INVALID_XY
}
SPITpValidity;

// Touch panel input structure
typedef union SPITpData
{
    struct
    {
        u32     x:12;
        u32     y:12;
        u32     touch:1;
        u32     validity:2;
        u32     dummy:5;

    }
    e;
    u32     raw;
    u8      bytes[4];
    u16     halfs[2];

}
SPITpData;


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_SPI_COMMON_TYPE_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
