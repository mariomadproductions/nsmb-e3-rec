/*---------------------------------------------------------------------------*
  Project:  NitroSDK - STD - include
  File:     unicode.h

  Copyright 2006,2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: unicode.h,v $
  Revision 1.4  2007/02/20 00:28:09  kitase_hirotake
  indent source

  Revision 1.3  2006/08/10 07:52:49  yosizaki
  add STDResult and change API interface.

  Revision 1.2  2006/07/24 13:16:42  yosizaki
  beautify indent.
  change of STD-API interface.

  Revision 1.1  2006/07/05 07:42:51  kitase_hirotake
  Added the sjis <-> unicode conversion library to std

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_STD_UNICODE_H_
#define NITRO_STD_UNICODE_H_

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************/
/* constant */

typedef enum STDResult
{
    STD_RESULT_SUCCESS,
    STD_RESULT_ERROR,
    STD_RESULT_INVALID_PARAM,
    STD_RESULT_CONVERSION_FAILED
}
STDResult;

/*****************************************************************************/
/* declaration */

//---- ConvertString callback
typedef STDResult(*STDConvertUnicodeCallback) (u16 *dst, int *dst_len, const char *src,
                                               int *src_len);
typedef STDResult(*STDConvertSjisCallback) (char *dst, int *dst_len, const u16 *src, int *src_len);


/*****************************************************************************/
/* function */

/*---------------------------------------------------------------------------*
  Name:         STD_IsSjisLeadByte

  Description:  Determines whether or not the specified character is the leading ShiftJIS byte.

  Arguments:    c                Character to determine.

  Returns:      TRUE if ShiftJIS leading byte
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL STD_IsSjisLeadByte(int c)
{
    return ((unsigned int)((((u8)c) ^ 0x20) - 0xA1) < 0x3C);
}

/*---------------------------------------------------------------------------*
  Name:         STD_IsSjisTrailByte

  Description:  Determines whether or not the specified character is the trailing ShiftJIS byte.

  Arguments:    c                Character to determine.

  Returns:      TRUE if ShiftJIS trailing byte
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL STD_IsSjisTrailByte(int c)
{
    return (c != 0x7F) && ((u8)(c - 0x40) <= (0xFC - 0x40));
}

/*---------------------------------------------------------------------------*
  Name:         STD_IsSjisCharacter

  Description:  Determines whether or not the specified character is a ShiftJIS character.

  Arguments:    s                Character to determine.

  Returns:      TRUE if ShiftJIS character
 *---------------------------------------------------------------------------*/
SDK_INLINE BOOL STD_IsSjisCharacter(const char *s)
{
    return STD_IsSjisLeadByte(s[0]) && STD_IsSjisTrailByte(s[1]);
}

/*---------------------------------------------------------------------------*
  Name:         STD_ConvertStringSjisToUnicode

  Description:  Converst a ShiftJIS character string to a Unicode character string.

  Arguments:    dst               Conversion destination buffer.
                                  The storage process is ignored if NULL is specified.
                dst_len           Pointer that stores and passes the maximum character count for the conversion destination buffer,
                                  and receives the number of characters actually stored.
                                  Ignored when NULL is given.
                src               Conversion source buffer.
                src_len           Pointer that stores and passes the maximum character count that should be converted,
                                  and receives the number of characters actually converted.
                                  The end-of-string position takes priority over this specification.
                                  When a negative value is stored and passed or NULL is given,
                                  the character count is revised to be the number of characters to the end of the string.
                callback          The callback called if there are any characters that can't be converted.
                                  When NULL is specified, the conversion process ends
                                  at the position of the character that cannot be converted.

  Returns:      Result of the conversion process.
 *---------------------------------------------------------------------------*/
STDResult STD_ConvertStringSjisToUnicode(u16 *dst, int *dst_len,
                                         const char *src, int *src_len,
                                         STDConvertUnicodeCallback callback);

/*---------------------------------------------------------------------------*
  Name:         STD_ConvertCharSjisToUnicode.

  Description:  Convertsa ShiftJIS character to a Unicode character.

  Arguments:    dst               Conversion destination buffer.
                src               Conversion source string.

  Returns:      The number of characters converted.
                Returns a -1 when conversion fails
 *---------------------------------------------------------------------------*/
SDK_INLINE int STD_ConvertCharSjisToUnicode(u16 *dst, const char *src)
{
    int     src_len = STD_IsSjisCharacter(src) ? 2 : 1;
    int     dst_len = 1;
    STDResult ret = STD_ConvertStringSjisToUnicode(dst, &dst_len, src, &src_len, NULL);
    return (ret == STD_RESULT_SUCCESS) ? dst_len : -1;
}

/*---------------------------------------------------------------------------*
  Name:         STD_ConvertStringUnicodeToSjis

  Description:  Converts a Unicode character string to a ShiftJIS character string.

  Arguments:    dst               Conversion destination buffer.
                                  The storage process is ignored if NULL is specified.
                dst_len           Pointer that stores and passes the maximum character count for the conversion destination buffer,
                                  and receives the number of characters actually stored.
                                  Ignored when NULL is given.
                src               Conversion source buffer.
                src_len           Pointer that stores and passes the maximum character count that should be converted,
                                  and receives the number of characters actually converted.
                                  The end-of-string position takes priority over this specification.
                                  When a negative value is stored and passed or NULL is given,
                                  the character count is revised to be the number of characters to the end of the string.
                callback          The callback called if there are any characters that can't be converted.
                                  When NULL is specified, the conversion process ends
                                  at the position of the character that cannot be converted.

  Returns:      Result of the conversion process.
 *---------------------------------------------------------------------------*/
STDResult STD_ConvertStringUnicodeToSjis(char *dst, int *dst_len,
                                         const u16 *src, int *src_len,
                                         STDConvertSjisCallback callback);

/*---------------------------------------------------------------------------*
  Name:         STD_ConvertCharUnicodeToSjis

  Description:  Converts a Unicode character string to a ShiftJIS character string.

  Arguments:    dst               Conversion destination buffer.
                                  Requires two bytes to be secured.
                src               Conversion source string.

  Returns:      The number of bytes converted.
                Returns a -1 when conversion fails
 *---------------------------------------------------------------------------*/
SDK_INLINE int STD_ConvertCharUnicodeToSjis(char *dst, u16 src)
{
    int     src_len = 1;
    int     dst_len = 2;
    STDResult ret = STD_ConvertStringUnicodeToSjis(dst, &dst_len, &src, &src_len, NULL);
    return (ret == STD_RESULT_SUCCESS) ? dst_len : -1;
}


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_STD_UNICODE_H_ */
#endif
