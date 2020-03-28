/*---------------------------------------------------------------------------*
  Project:  NitroSDK - SPI - include
  File:     userInfo_ts_200.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: userInfo_ts_200.h,v $
  Revision 1.4  2006/01/18 02:12:38  kitase_hirotake
  do-indent

  Revision 1.3  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.2  2004/09/03 04:29:15  terui
  Revised according to structure definition adjustments relating to user information in NVRAM.

  Revision 1.1  2004/08/25 09:20:43  terui
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_SPI_COMMON_USERINFO_TS_200_H_
#define NITRO_SPI_COMMON_USERINFO_TS_200_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

/*---------------------------------------------------------------------------*
    constant definitions
 *---------------------------------------------------------------------------*/
// config setting data format version
#define NVRAM_CONFIG_DATA_VERSION           5

// various setting values in config
#define NVRAM_CONFIG_NICKNAME_LENGTH        10  // Nickname Length
#define NVRAM_CONFIG_COMMENT_LENGTH         26  // Comment Length
#define NVRAM_CONFIG_FAVORITE_COLOR_MAX     16  // Maximum number of favorite colors

// language setting codes
#define NVRAM_CONFIG_LANG_JAPANESE          0   // Japanese
#define NVRAM_CONFIG_LANG_ENGLISH           1   // English
#define NVRAM_CONFIG_LANG_FRENCH            2   // France
#define NVRAM_CONFIG_LANG_GERMAN            3   // German
#define NVRAM_CONFIG_LANG_ITALIAN           4   // Italian
#define NVRAM_CONFIG_LANG_SPANISH           5   // Spanish
#define NVRAM_CONFIG_LANG_CODE_MAX          6   // number of types of language setting codes

/*---------------------------------------------------------------------------*
    structure definitions
 *---------------------------------------------------------------------------*/
// birthday data (2 byte)
typedef struct NVRAMConfigDate
{
    u8      month;                     // Month:01 - 12
    u8      day;                       // Day:01 - 31

}
NVRAMConfigDate;

// Nickname (22byte)
typedef struct NVRAMConfigNickname
{
    u16     str[NVRAM_CONFIG_NICKNAME_LENGTH];  // Nickname  (Maximum of 10 characters in Unicode(UTF16), no terminal code)
    u8      length;                    // Number of characters
    u8      rsv;

}
NVRAMConfigNickname;

// Comment (54byte)
typedef struct NVRAMConfigComment
{
    u16     str[NVRAM_CONFIG_COMMENT_LENGTH];   //Comment  (A maximum of 26 characters in Unicode(UTF16), no terminal code)
    u8      length;                    // Number of characters
    u8      rsv;

}
NVRAMConfigComment;

// Owner Information (80byte)
typedef struct NVRAMConfigOwnerInfo
{
    u8      favoriteColor:4;           // Favorite color
    u8      rsv:4;                     // Reserved
    NVRAMConfigDate birthday;          // Birthdate
    u8      pad;
    NVRAMConfigNickname nickname;      // Nickname
    NVRAMConfigComment comment;        // Comment

}
NVRAMConfigOwnerInfo;


// Alarm clock data for IPL (6byte)
typedef struct NVRAMConfigAlarm
{
    u8      hour;                      // Alarm Hour:00 - 23
    u8      minute;                    // Alarm Minute:00 - 59
    u8      second;                    // Alarm Seconds:00 - 59
    u8      pad;
    u16     enableWeek:7;              // Flag for which day of the week the alarm is valid (bit0:Day bit1:Month..."1" is valid)
    u16     alarmOn:1;                 // Alarm ON,OFF (0:OFF, 1:ON)
    u16     rsv:8;                     // Reserved

}
NVRAMConfigAlarm;

// Touch Panel Calibration Data (12byte)
typedef struct NVRAMConfigTpCalibData
{
    u16     raw_x1;                    // TP obtained value X of the first calibration point
    u16     raw_y1;                    // TP obtained value Y of the first calibration point
    u8      dx1;                       // LCD coordinate X of the first calibration point
    u8      dy1;                       // LCD coordinate Y of the first calibration point
    u16     raw_x2;                    // TP obtained value X of the second calibration point
    u16     raw_y2;                    // TP obtained value Y of the second calibration point
    u8      dx2;                       // LCD coordinate X of the second calibration point
    u8      dy2;                       // LCD coordinate Y of the second calibration point

}
NVRAMConfigTpCalibData;

// option information (12 byte)
typedef struct NVRAMConfigOption
{
    u16     language:3;                // Language code
    u16     agbLcd:1;                  // Start up on which LCD when booting in AGB mode? (0:TOP,1:BOTTOM)
    u16     detectPullOutCardFlag:1;   // Flag that indicates that the card has been pulled out
    u16     detectPullOutCtrdgFlag:1;  // Flag that indicates that the Game Pak has been pulled out
    u16     autoBootFlag:1;            // Whether or not to automatically start up without stopping the menu on the startup sequence.
    u16     rsv:4;                     // reserved
    u16     input_favoriteColor:1;     // Was a favorite color input?
    u16     input_tp:1;                // Was the touch panel calibrated?
    u16     input_language:1;          // Was a language input?       (0:Not configured, 1:Configured)
    u16     input_rtc:1;               // Was the RTC configured?          (                                                  )
    u16     input_nickname:1;          // Was a nickname input? (                                                  )
    u8      timezone;                  // Time Zone  (Currently reserved)
    u8      rtcClockAdjust;            // RTC Clock adjustment value
    s64     rtcOffset;                 // Offset value when configuring the RTC (Each time the user changes the configuration of the RTC, this fluctuates in response to its value.)

}
NVRAMConfigOption;


// Each type of configuration data (112byte)
typedef struct NVRAMConfigData
{
    u8      version;                   // Flash storage data format version
    u8      pad;
    NVRAMConfigOwnerInfo owner;        // Owner Information
    NVRAMConfigAlarm alarm;            // Alarm clock data for IPL
    NVRAMConfigTpCalibData tp;         // Touch Panel Calibration Data
    NVRAMConfigOption option;          // Options

}
NVRAMConfigData;

// Format when saving the NVRAM for each type of NITRO configuration data (116byte)
typedef struct NVRAMConfig
{
    NVRAMConfigData ncd;               // Various type of configuration data for NITRO
    u16     saveCount;                 // Counts 0x00-0x7f by looping; the count value enables new data.
    u16     crc16;                     // 16bitCRC of various type of configuration data for NITRO

}
NVRAMConfig;


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_SPI_COMMON_USERINFO_TS_200_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
