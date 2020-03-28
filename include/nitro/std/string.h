/*---------------------------------------------------------------------------*
  Project:  NitroSDK - STD - include
  File:     string.h

  Copyright 2005-2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: string.h,v $
  Revision 1.14  2007/04/24 12:05:14  yosizaki
  Updated copyright.

  Revision 1.13  2007/04/20 09:45:52  yosizaki
  Added STD_TSPrintf.

  Revision 1.12  2006/06/06 09:09:37  kitase_hirotake
  Changed the STD_CopyLStringZeroFill function's return value

  Revision 1.10  2006/01/18 02:12:29  kitase_hirotake
  do-indent

  Revision 1.9  2005/10/21 08:44:16  yosizaki
  Added STD_TSScanf().

  Revision 1.8  2005/09/27 05:19:39  yada
  Simply arranged src list

  Revision 1.7  2005/09/26 08:48:53  okubata_ryoma
  Added STD_CompareNString, STD_CompareLString

  Revision 1.6  2005/09/26 05:06:24  okubata_ryoma
  Revisions

  Revision 1.5  2005/09/26 04:55:42  okubata_ryoma
  Added STD_CompareLString

  Revision 1.4  2005/09/06 01:25:40  yasu
  Converted the STD_GetStringLength return value to int type

  Revision 1.3  2005/09/05 01:20:47  yada
  Added some functions

  Revision 1.2  2005/08/24 02:51:22  yada
  Added STD_SearchStringInString()

  Revision 1.1  2005/08/19 11:01:05  yada
  Initial release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_STD_STRING_H_
#define NITRO_STD_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"

//---- aliases
#define STD_StrCpy          STD_CopyString
#define STD_StrLCpy         STD_CopyLString
#define STD_StrStr          STD_SearchString
#define STD_StrLen          STD_GetStringLength
#define STD_StrCat          STD_ConcatenateString
#define STD_StrCmp          STD_CompareString
#define STD_StrNCmp         STD_CompareNString
#define STD_StrLCmp         STD_CompareLString

/*---------------------------------------------------------------------------*
  Name:         STD_CopyString

  Description:  same to strcpy

  Arguments:    destp : destination pointer
                srcp : src pointer

  Returns:      pointer to destination
 *---------------------------------------------------------------------------*/
extern char *STD_CopyString(char *destp, const char *srcp);

/*---------------------------------------------------------------------------*
  Name:         STD_CopyLStringZeroFill

  Description:  do not correspond with strlcpy

  Arguments:    destp : destination pointer
                srcp : src pointer
                n: copy size + 1

  Returns:      size of src
 *---------------------------------------------------------------------------*/
extern int STD_CopyLStringZeroFill(char *destp, const char *srcp, int n);

/*---------------------------------------------------------------------------*
  Name:         STD_CopyLString

  Description:  same to strlcpy

  Arguments:    destp : destination pointer
                srcp : src pointer
                siz   : copy size + 1

  Returns:      size of src
 *---------------------------------------------------------------------------*/
extern int STD_CopyLString(char *destp, const char *srcp, int siz);

/*---------------------------------------------------------------------------*
  Name:         STD_SearchString

  Description:  same to strstr

  Arguments:    srcp : src string
                str: string to search from src pointer

  Returns:      pointer to destination
 *---------------------------------------------------------------------------*/
extern char *STD_SearchString(const char *srcp, const char *str);

/*---------------------------------------------------------------------------*
  Name:         STD_GetStringLength

  Description:  get string length. same to strlen

  Arguments:    str: string

  Returns:      string length
 *---------------------------------------------------------------------------*/
extern int STD_GetStringLength(const char *str);

/*---------------------------------------------------------------------------*
  Name:         STD_ConcatenateString

  Description:  concatenate strings. same to strcat

  Arguments:    str1 : original string
                str2 : string to concatenate

  Returns:      concatenated string
 *---------------------------------------------------------------------------*/
extern char *STD_ConcatenateString(char *str1, const char *str2);

/*---------------------------------------------------------------------------*
  Name:         STD_CompareString

  Description:  compare strings. same to strcmp

  Arguments:    str1, str2 : strings

  Returns:      0 if same
 *---------------------------------------------------------------------------*/
extern int STD_CompareString(const char *str1, const char *str2);

/*---------------------------------------------------------------------------*
  Name:         STD_CompareNString

  Description:  same to strncmp

  Arguments:    str1, str2 : strings
                len    : max length

  Returns:      0 if same
 *---------------------------------------------------------------------------*/
extern int STD_CompareNString(const char *str1, const char *str2, int len);

/*---------------------------------------------------------------------------*
  Name:         STD_CompareLString

  Description:  same to strlcmp

  Arguments:    str1, str2 : strings

  Returns:      0 if same
 *---------------------------------------------------------------------------*/
extern int STD_CompareLString(const char *str1, const char *str2);

/*---------------------------------------------------------------------------*
  Name:         STD_TSScanf

  Description:  sscanf with size reduced.
                Supports basic format specifications "%(*?)([lh]{,2})([diouxXpn])".

  Arguments:    src           Input string
                fmt           Format control string

  Returns:      Total number of substituted values.
                Returns -1 if the function ends without a substitution or an error is detected.
 *---------------------------------------------------------------------------*/
extern int STD_TSScanf(const char *src, const char *fmt, ...);

/*---------------------------------------------------------------------------*
  Name:         STD_TVSScanf

  Description:  This version supports va_list used with STD_TSScanf.
                Supports basic format specification "%(*?)([lh]{,2})[diouxX]".

  Arguments:    src           Input string
                fmt           Format control string
                vlist         Parameters

  Returns:      Total number of substituted values.
                Returns -1 if the function ends without a substitution or an error is detected.
 *---------------------------------------------------------------------------*/
extern int STD_TVSScanf(const char *src, const char *fmt, va_list vlist);

/*---------------------------------------------------------------------------*
  Name:         STD_TSPrintf

  Description:  With the exception of the format of the arguments, identical to STD_TVSNPrintf.

  Arguments:    dst           The buffer that will store the result
                fmt           Format control string

  Returns:      Identical to STD_VSNPrintf.
 *---------------------------------------------------------------------------*/
extern int STD_TSPrintf(char *dst, const char *fmt, ...);

/*---------------------------------------------------------------------------*
  Name:         STD_TVSPrintf

  Description:  With the exception of the format of the arguments, identical to STD_TVSNPrintf.

  Arguments:    dst           The buffer that will store the result
                fmt           Format control string
                vlist         Parameters

  Returns:      Identical to STD_VSNPrintf.
 *---------------------------------------------------------------------------*/
extern int STD_TVSPrintf(char *dst, const char *fmt, va_list vlist);

/*---------------------------------------------------------------------------*
  Name:         STD_TSNPrintf

  Description:  With the exception of the format of the arguments, identical to STD_TVSNPrintf.

  Arguments:    dst           The buffer that will store the result
                len           Buffer length
                fmt           Format control string
 
  Returns:      Identical to STD_VSNPrintf.
 *---------------------------------------------------------------------------*/
extern int STD_TSNPrintf(char *dst, u32 len, const char *fmt, ...);

/*---------------------------------------------------------------------------*
  Name:         STD_TVSNPrintf

  Description:  sprintf redone to save on size.
                Supports basic format specifications.
                %([-+# ]?)([0-9]*)(\.?)([0-9]*)([l|ll|h||hh]?)([diouxXpncs%])

  Note:         As with the behavior of CodeWarrior's MSL sprintf(), '+' and '#' are invalidated.
                
                { // exsample
                  char buf[5];
                  sprintf(buf, "%-i\n", 45);  // "45"  (OK)
                  sprintf(buf, "%0i\n", 45);  // "45"  (OK)
                  sprintf(buf, "% i\n", 45);  // " 45" (OK)
                  sprintf(buf, "%+i\n", 45);  // "%+i" ("+45" expected)
                  sprintf(buf, "%#x\n", 45);  // "%#x" ("0x2d" expected)
                  // but, this works correctly!
                  sprintf(buf, "% +i\n", 45); // "+45" (OK)
                }

  Arguments:    dst           The buffer that will store the result
                len           Buffer length
                fmt           Format control string
                vlist         Parameters

  Returns:      Returns the number of characters (exclusive of '\0') when the format string is output correctly.
                When the buffer size is sufficient, all text is output and a terminator is provided.
                When the buffer size is not enough, termination occurs at dst[len-1].
                Nothing happens when len is 0.

 *---------------------------------------------------------------------------*/
extern int STD_TVSNPrintf(char *dst, u32 len, const char *fmt, va_list vlist);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_STD_STRING_H_ */
#endif
