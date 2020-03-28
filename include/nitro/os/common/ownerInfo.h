/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     ownerInfo.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: ownerInfo.h,v $
  Revision 1.17  2007/02/20 00:28:10  kitase_hirotake
  indent source

  Revision 1.16  2006/10/25 04:46:45  kitase_hirotake
  Changed OSOwnerInfo

  Revision 1.15  2006/10/17 05:27:43  okubata_ryoma
  Supports Korean IPL

  Revision 1.14  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.13  2005/05/14 03:03:13  terui
  Corrected to define Chinese language code only when SDK_NVRAM_FORMAT is 300 and over

  Revision 1.12  2005/04/26 08:01:54  terui
  Fix comment

  Revision 1.11  2005/04/18 12:28:10  terui
  Deleted OSi_CheckOwnerInfo function

  Revision 1.10  2005/04/12 10:49:15  terui
  Made alterations to support Chinese language

  Revision 1.9  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.8  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.7  2004/10/07 10:19:39  yosizaki
  add favorite color API.

  Revision 1.6  2004/09/13 05:49:56  yasu
  merged with NitroSDK_2_00pr6_branch

  Revision 1.5.2.1  2004/09/13 05:43:02  yasu
  Support SDK_NVRAM_FORMAT

  Revision 1.5  2004/09/03 08:43:07  terui
  Only fix comment.

  Revision 1.4  2004/09/03 08:00:53  terui
  Added the OS_GetOwnerRtcOffset function.

  Revision 1.3  2004/09/03 04:35:21  yasu
  Add "#include "nitro/spec.h""

  Revision 1.2  2004/09/03 04:29:15  terui
  Revised according to structure definition adjustments relating to user information in NVRAM.

  Revision 1.1  2004/09/02 06:20:49  terui
  Initial upload

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_COMMON_OWNERINFO_H_
#define NITRO_OS_COMMON_OWNERINFO_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include "nitro/types.h"
#include "nitro/spec.h"
#include "nitro/spi/common/config.h"
#include "nitro/hw/common/mmap_shared.h"
#include "nitro/mi/memory.h"

#include "nitro/gx/gxcommon.h"



/* DS information: Favorite color definition (0-15) */
#define	OS_FAVORITE_COLOR_GRAY         0x00
#define	OS_FAVORITE_COLOR_BROWN        0x01
#define	OS_FAVORITE_COLOR_RED          0x02
#define	OS_FAVORITE_COLOR_PINK         0x03
#define	OS_FAVORITE_COLOR_ORANGE       0x04
#define	OS_FAVORITE_COLOR_YELLOW       0x05
#define	OS_FAVORITE_COLOR_LIME_GREEN   0x06
#define	OS_FAVORITE_COLOR_GREEN        0x07
#define	OS_FAVORITE_COLOR_DARK_GREEN   0x08
#define	OS_FAVORITE_COLOR_SEA_GREEN    0x09
#define	OS_FAVORITE_COLOR_TURQUOISE    0x0A
#define	OS_FAVORITE_COLOR_BLUE         0x0B
#define	OS_FAVORITE_COLOR_DARK_BLUE    0x0C
#define	OS_FAVORITE_COLOR_PURPLE       0x0D
#define	OS_FAVORITE_COLOR_VIOLET       0x0E
#define	OS_FAVORITE_COLOR_MAGENTA      0x0F
#define	OS_FAVORITE_COLOR_BITMASK      0x0F
#define	OS_FAVORITE_COLOR_MAX          0x10

/* DS information: Favorite color constant (GXRgb) */
#define	OS_FAVORITE_COLOR_VALUE_GRAY         GX_RGB(12,16,19)
#define	OS_FAVORITE_COLOR_VALUE_BROWN        GX_RGB(23, 9, 0)
#define	OS_FAVORITE_COLOR_VALUE_RED          GX_RGB(31, 0, 3)
#define	OS_FAVORITE_COLOR_VALUE_PINK         GX_RGB(31,17,31)
#define	OS_FAVORITE_COLOR_VALUE_ORANGE       GX_RGB(31,18, 0)
#define	OS_FAVORITE_COLOR_VALUE_YELLOW       GX_RGB(30,28, 0)
#define	OS_FAVORITE_COLOR_VALUE_LIME_GREEN   GX_RGB(21,31, 0)
#define	OS_FAVORITE_COLOR_VALUE_GREEN        GX_RGB( 0,31, 0)
#define	OS_FAVORITE_COLOR_VALUE_DARK_GREEN   GX_RGB( 0,20, 7)
#define	OS_FAVORITE_COLOR_VALUE_SEA_GREEN    GX_RGB( 9,27,17)
#define	OS_FAVORITE_COLOR_VALUE_TURQUOISE    GX_RGB( 6,23,30)
#define	OS_FAVORITE_COLOR_VALUE_BLUE         GX_RGB( 0,11,30)
#define	OS_FAVORITE_COLOR_VALUE_DARK_BLUE    GX_RGB( 0, 0,18)
#define	OS_FAVORITE_COLOR_VALUE_PURPLE       GX_RGB(17, 0,26)
#define	OS_FAVORITE_COLOR_VALUE_VIOLET       GX_RGB(26, 0,29)
#define	OS_FAVORITE_COLOR_VALUE_MAGENTA      GX_RGB(31, 0,18)


#ifdef  SDK_TS
#if ( SDK_TS_VERSION >= 200 || SDK_NVRAM_FORMAT >= 100 )

/*---------------------------------------------------------------------------*
    constant definitions
 *---------------------------------------------------------------------------*/
// Language code
typedef enum OSLanguage
{
    OS_LANGUAGE_JAPANESE = NVRAM_CONFIG_LANG_JAPANESE,  // 0: Japanese
    OS_LANGUAGE_ENGLISH = NVRAM_CONFIG_LANG_ENGLISH,    // 1: English
    OS_LANGUAGE_FRENCH = NVRAM_CONFIG_LANG_FRENCH,      // 2: France
    OS_LANGUAGE_GERMAN = NVRAM_CONFIG_LANG_GERMAN,      // 3: German
    OS_LANGUAGE_ITALIAN = NVRAM_CONFIG_LANG_ITALIAN,    // 4: Italian
    OS_LANGUAGE_SPANISH = NVRAM_CONFIG_LANG_SPANISH,    // 5: Spanish
#if ( SDK_NVRAM_FORMAT >= 300 )
    OS_LANGUAGE_CHINESE = NVRAM_CONFIG_LANG_CHINESE,    // 6: Chinese
    OS_LANGUAGE_HANGUL = NVRAM_CONFIG_LANG_HANGUL,      // 7: Korean
#endif
    OS_LANGUAGE_CODE_MAX = NVRAM_CONFIG_LANG_CODE_MAX
}
OSLanguage;


// Maximum character string lengths
#define     OS_OWNERINFO_NICKNAME_MAX       NVRAM_CONFIG_NICKNAME_LENGTH
#define     OS_OWNERINFO_COMMENT_MAX        NVRAM_CONFIG_COMMENT_LENGTH


/*---------------------------------------------------------------------------*
    structure definitions
 *---------------------------------------------------------------------------*/
// Birthday information
typedef struct OSBirthday
{
    u8      month;                     // Month (1 to 12)
    u8      day;                       // Day (1 to 31)

}
OSBirthday;

// Owner Information
typedef struct OSOwnerInfo
{
    u8      language;                  // Language code
    u8      favoriteColor;             // Favorite color (0 to 15)
    OSBirthday birthday;               // Birthdate
    u16     nickName[OS_OWNERINFO_NICKNAME_MAX + 1];
    // Nickname (Max. 10 characters of Unicode(UTF16), no terminal code)
    u16     nickNameLength;            // Number of characters in nickname (0 to 10)
    u16     comment[OS_OWNERINFO_COMMENT_MAX + 1];
    // Comment (Max. 26 characters of Unicode(UTF16), no terminal code)
    u16     commentLength;             // Number of characters in comment (0 to 28)

}
OSOwnerInfo;


/*---------------------------------------------------------------------------*
    function definitions
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         OS_GetOwnerInfo

  Description:  Gets the owner information.

  Arguments:    info    -   Pointer to the buffer getting the owner information.
                            Data gets written to this buffer.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_GetOwnerInfo(OSOwnerInfo *info);

#endif

/*---------------------------------------------------------------------------*
  Name:         OS_GetOwnerRtcOffset

  Description:  Gets the offset (in units of seconds) to use to increase
                or decrease the value every time the owner changes the RTC setting.
                Time gets added if RTC is set to a time in the future relative to
                the RTC prior to being reset. Time gets subtracted if the RTC is set back in the past relative to the RTC prior to being reset.

  Arguments:    None.

  Returns:      s64 -   Returns the offset value for RTC settings.
 *---------------------------------------------------------------------------*/
s64     OS_GetOwnerRtcOffset(void);

#endif

/*---------------------------------------------------------------------------*
  Name:         OS_GetMacAddress

  Description:  Gets the MAC address of the wireless hardware.

  Arguments:    macAddress  -   Pointer to the buffer getting the MAC address.
                                Six bytes of data get written to this buffer.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_GetMacAddress(u8 *macAddress);

/*---------------------------------------------------------------------------*
  Name:         OS_GetFavoriteColorTable

  Description:  Obtains a pointer to the "Favorite Color" array that corresponds to the favoriteColor
                member of the OSOwnerInfo structure.

  Arguments:    None.

  Returns:      Pointer to the GXRg type constant array that stores corresponding color value.
 *---------------------------------------------------------------------------*/
const GXRgb *OS_GetFavoriteColorTable(void);

/*---------------------------------------------------------------------------*
  Name:         OS_GetMacAddress

  Description:  Obtains "Favorite Color" that corresponds to the specified number.

  Arguments:    index  -   Number for "Favorite Color" to specify
                           This index is masked by 16 colors (4 bits) that are the total
                           number of "Favorite Colors."

  Returns:      GXRgb type color value that corresponds to the specified number
 *---------------------------------------------------------------------------*/
static inline GXRgb OS_GetFavoriteColor(int index)
{
    return OS_GetFavoriteColorTable()[index & OS_FAVORITE_COLOR_BITMASK];
}

/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_OS_COMMON_OWNERINFO_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
