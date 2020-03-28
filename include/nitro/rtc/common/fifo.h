/*---------------------------------------------------------------------------*
  Project:  NitroSDK - RTC - include
  File:     fifo.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fifo.h,v $
  Revision 1.6  2005/02/28 05:26:08  yosizaki
  do-indent.

  Revision 1.5  2004/09/14 01:59:57  yasu
  Fixed backslashes at end of line.

  Revision 1.4  2004/05/31 08:42:49  terui
  Deleted RESULT for alarm interupt and added COMMAND.

  Revision 1.3  2004/05/17 11:02:51  terui
  Added FATAL_ERROR to process results

  Revision 1.2  2004/05/17 08:43:34  terui
  Added BUSY to process results

  Revision 1.1  2004/05/12 02:27:41  terui
  initial upload

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_RTC_COMMON_FIFO_H_
#define NITRO_RTC_COMMON_FIFO_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*===========================================================================*/

/*---------------------------------------------------------------------------*
    constant definitions
 *---------------------------------------------------------------------------*/
// Protocol-related definitions
#define RTC_PXI_COMMAND_MASK                0x00007f00  // Mask for command storage portion
#define RTC_PXI_COMMAND_SHIFT               8   // Position of command storage portion
#define RTC_PXI_RESULT_BIT_MASK             0x00008000  // Mask for portion indicating PXI's response
#define RTC_PXI_RESULT_MASK                 0x000000ff  // Mask for storage portion of processing result
#define RTC_PXI_RESULT_SHIFT                0   // Position of storage portion of processing result

// PXI command definitions
#define RTC_PXI_COMMAND_RESET               0x00        // Reset
#define RTC_PXI_COMMAND_SET_HOUR_FORMAT     0x01        // Set the time display format
#define RTC_PXI_COMMAND_READ_DATETIME       0x10        // Read date and time
#define RTC_PXI_COMMAND_READ_DATE           0x11        // Read date
#define RTC_PXI_COMMAND_READ_TIME           0x12        // Read time
#define RTC_PXI_COMMAND_READ_PULSE          0x13        // Read the pulse output setting value
#define RTC_PXI_COMMAND_READ_ALARM1         0x14        // Read the Alarm 1 setting value
#define RTC_PXI_COMMAND_READ_ALARM2         0x15        // Read the Alarm 2 setting value
#define RTC_PXI_COMMAND_READ_STATUS1        0x16        // Read the Status 1 register
#define RTC_PXI_COMMAND_READ_STATUS2        0x17        // Read the Status 2 register
#define RTC_PXI_COMMAND_READ_ADJUST         0x18        // Read frequency periodic interrupt register
#define RTC_PXI_COMMAND_READ_FREE           0x19        // Read the free register
#define RTC_PXI_COMMAND_WRITE_DATETIME      0x20        // Write the date and time
#define RTC_PXI_COMMAND_WRITE_DATE          0x21        // Write the date
#define RTC_PXI_COMMAND_WRITE_TIME          0x22        // Write the time
#define RTC_PXI_COMMAND_WRITE_PULSE         0x23        // Write the pulse output setting value
#define RTC_PXI_COMMAND_WRITE_ALARM1        0x24        // Write the Alarm 1 setting
#define RTC_PXI_COMMAND_WRITE_ALARM2        0x25        // Write the Alarm 2 setting
#define RTC_PXI_COMMAND_WRITE_STATUS1       0x26        // Write to the Status 1 register
#define RTC_PXI_COMMAND_WRITE_STATUS2       0x27        // Write to the Status 2 register
#define RTC_PXI_COMMAND_WRITE_ADJUST        0x28        // Write to frequency periodic interrupt register
#define RTC_PXI_COMMAND_WRITE_FREE          0x29        // Write to the free register
#define RTC_PXI_COMMAND_INTERRUPT           0x30        // To notify that an alarm interrupt has occurred

// Response definitions
typedef enum RTCPxiResult
{
    RTC_PXI_RESULT_SUCCESS = 0,        // Process successful.
    RTC_PXI_RESULT_INVALID_COMMAND,    // Invalid PXI command.
    RTC_PXI_RESULT_ILLEGAL_STATUS,     // Cannot process because of RTC status.
    RTC_PXI_RESULT_BUSY,               // Processing another request.
    RTC_PXI_RESULT_FATAL_ERROR,        // Process failed due to other error.
    RTC_PXI_RESULT_MAX
}
RTCPxiResult;


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_RTC_COMMON_FIFO_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
