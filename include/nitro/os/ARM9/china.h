/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     china.h

  Copyright 2005,2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: china.h,v $
  Revision 1.4  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.3  2005/05/27 08:57:52  yosizaki
  add OS_ShowAttentionChina.

  Revision 1.2  2005/05/14 01:11:28  terui
  Added parameter specifying ISBN string to OS_InitChina function

  Revision 1.1  2005/04/25 08:23:53  terui
  Added header for official support of Chinese version

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_ARM9_CHINA_H_
#define NITRO_OS_ARM9_CHINA_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#define OS_BURY_STRING_FORCHINA         "[SDK+NINTENDO:FORCHINA]"
#define OS_BUSY_STRING_LEN_FORCHINA     23


/*---------------------------------------------------------------------------*
  Name:         OS_InitChina

  Description:  Initializes SDK's OS library.
                For applications having China as the place of destination.
                Use this function instead of OS_Init function.

  Arguments:    isbn    -   Specifies character string array about the ISBN number etc.
                            {
                                char    ISBN[ 13 ] ,
                                char    Joint registration code  [ 12 ] ,
                                char    New output sound pipe (left)[ 4 ] ,
                                char    New output sound pipe (right) [ 4 ] ,
                            }

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_InitChina(const char **isbn);

/*---------------------------------------------------------------------------*
  Name:         OS_ShowAttentionChina

  Description:  Displays logo for China and warning screen for prescribed time.
                This function can be redefined in the user application.

  Arguments:    isbn    -   Character string array about the ISBN number etc.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_ShowAttentionChina(const char **isbn);


/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_OS_ARM9_CHINA_H_ */

/*---------------------------------------------------------------------------*
    End of file
 *---------------------------------------------------------------------------*/
