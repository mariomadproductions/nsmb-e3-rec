/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CP - include
  File:     context.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: context.h,v $
  Revision 1.9  2007/02/20 00:28:12  kitase_hirotake
  indent source

  Revision 1.8  2006/08/09 06:40:52  takano_makoto
  Changed CP_RestoreContext to wait for the divider's state restoration to complete

  Revision 1.7  2006/01/18 02:11:20  kitase_hirotake
  do-indent

  Revision 1.6  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.5  2005/02/28 05:26:03  yosizaki
  do-indent.

  Revision 1.4  2004/09/02 07:45:26  yada
  only change comment

  Revision 1.3  2004/06/02 13:11:21  yasu
  Fix ifdef conditions with SDK_CP_NO_SAFE

  Revision 1.2  2004/05/06 10:45:13  takano_makoto
  Modify include file.

  Revision 1.1  2004/05/06 02:55:23  takano_makoto
  Initial Update.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CP_CONTEXT_H_
#define NITRO_CP_CONTEXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/ioreg.h"
#include "nitro/cp/divider.h"

//----------------------------------------------------------------
typedef struct CPContext
{
    u64     div_numer;
    u64     div_denom;
    u64     sqrt;
    u16     div_mode;
    u16     sqrt_mode;
}
CPContext;

/*---------------------------------------------------------------------------*
  Name:         CP_SaveContext

  Description:  Save current context into specified memory

  Arguments:    context   pointer to the memory to be stored the current context

  Returns:      None
 *---------------------------------------------------------------------------*/
void    CP_SaveContext(CPContext *context);


/*---------------------------------------------------------------------------*
  Name:         CP_RestoreContext

  Description:  Reload specified context as current context

  Arguments:    context   pointer to the memory to switch to the context

  Returns:      None
 *---------------------------------------------------------------------------*/
void    CPi_RestoreContext(const CPContext *context);
static inline void CP_RestoreContext(const CPContext *context)
{
    CPi_RestoreContext(context);
    CP_WaitDiv();
}



#ifdef __cplusplus
} /* extern "C" */
#endif


/* NITRO_CP_CONTEXT_H_ */
#endif
