/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     profile.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: profile.h,v $
  Revision 1.8  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.7  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.6  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.5  2004/05/18 05:44:40  yada
  consider for #define NITRO_PROFILE_XXX

  Revision 1.4  2004/05/12 11:26:57  yada
  undef->define  about OS_NO_FUNCTIONCOST

  Revision 1.3  2004/05/12 08:03:01  yada
  fix include guard

  Revision 1.2  2004/05/12 05:09:03  yada
  modify SDK_XXX / OS_XXX option

  Revision 1.1  2004/05/10 11:38:37  yada
  first release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

//================================================================
#ifndef NITRO_OS_PROFILE_H_
#define NITRO_OS_PROFILE_H_

#ifdef __cplusplus
extern "C" {
#endif

//---- if available CallTrace
#ifdef SDK_PROFILE_CALLTRACE
#  define OS_PROFILE_AVAILABLE
#  define OS_PROFILE_CALL_TRACE
#endif

//---- if available FunctionCost
#ifdef SDK_PROFILE_FUNCTIONCOST
#  define OS_PROFILE_AVAILABLE
#  define OS_PROFILE_FUNCTION_COST
#endif

//================================================================
#ifdef OS_PROFILE_AVAILABLE

//---- check OS_PROFILE_XXX define
#if defined( OS_PROFILE_CALL_TRACE ) && defined( OS_PROFILE_FUNCTION_COST )
*** ERROR:cannot specify both options of OS_PROFILE_CALL_TRACE and OS_PROFILE_FUNCTION_COST at a same
    time.
#endif
//---- if FINALROM, never be available CallTrace and FunctionCost.
#ifdef SDK_FINALROM
#  define OS_NO_CALLTRACE
#  define OS_NO_FUNCTIONCOST
#endif // ifdef SDK_FINALROM
#endif // ifdef OS_PROFILE_AVAILABLE
//---- prototype
void    __PROFILE_ENTRY(void);
void    __PROFILE_EXIT(void);


//----------------------------------------------------------------
#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_PROFILE_H_ */
#endif
