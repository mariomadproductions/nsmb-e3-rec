/*---------------------------------------------------------------------------*
  Project:  NitroSDK - screenshot test - Ext
  File:     ext_keycontrol.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: ext_keycontrol.h,v $
  Revision 1.3  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.2  2005/02/28 05:26:07  yosizaki
  do-indent.

  Revision 1.1  2004/05/27 09:16:12  takano_makoto
  Initial Upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef EXT_KEYCONTROL_H_
#define EXT_KEYCONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    u16     key;                       // Key status
    u16     count;                     // The time period to maintain key status. 0 will be considered a termination.
}
EXTKeys;

void    EXT_AutoKeys(const EXTKeys *sequence, u16 *cont, u16 *trig);


#ifdef __cplusplus
}/* extern "C" */
#endif

#endif /* EXT_KEYCONTROL_H_ */
