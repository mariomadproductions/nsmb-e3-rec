/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     tcm.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: tcm.h,v $
  Revision 1.13  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.12  2005/02/28 05:26:02  yosizaki
  do-indent.

  Revision 1.11  2005/02/17 11:39:00  yosizaki
  add OS_GetITCMAddress.

  Revision 1.10  2004/06/11 06:23:03  yada
  and remove OS_SetITCMAddress

  Revision 1.9  2004/06/08 12:21:52  yada
  change names
  ParamDTCM->DTCMParam, ParamITCM->ITCMParam

  Revision 1.8  2004/06/02 12:13:02  yada
  fix comment.
  add function to get address of tcm beginning address.

  Revision 1.7  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.6  2004/02/10 12:11:49  yada
  Moved OS_GetDTCMAddress, OS_GetITCMAddress from system.h

  Revision 1.5  2004/02/05 07:27:19  yada
  Returned the parts that were IRIS in the history string from NITRO to IRIS.

  Revision 1.4  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.3  2004/01/16 01:17:55  yasu
  Support SDK_BB

  Revision 1.2  2004/01/15 02:40:01  yada
  changed IRIS_BB  to -> SDK_BB

  Revision 1.1  2003/12/08 12:22:34  yada
  Initial release.


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_TCM_H_
#define NITRO_OS_TCM_H_

#ifdef __cplusplus
extern "C" {
#endif


//=======================================================================
//           ITCM
//=======================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_EnableITCM

  Description:  enable ITCM

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_EnableITCM(void);

/*---------------------------------------------------------------------------*
  Name:         OS_DisableITCM

  Description:  disable ITCM

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_DisableITCM(void);

/*---------------------------------------------------------------------------*
  Name:         OS_SetITCMParam

  Description:  set parameter to ITCM

  Arguments:    param :  parameter to be set to ITCM

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_SetITCMParam(u32 param);

/*---------------------------------------------------------------------------*
  Name:         OS_GetITCMParam

  Description:  get parameter to ITCM

  Arguments:    None

  Returns:      parameter about ITCM
 *---------------------------------------------------------------------------*/
u32     OS_GetITCMParam(void);

/*---------------------------------------------------------------------------*
  Name:         OS_GetITCMAddress

  Description:  Get start address of ITCM
                this function always returns HW_ITCM.

  Arguments:    None.

  Returns:      start address of ITCM
 *---------------------------------------------------------------------------*/
static inline u32 OS_GetITCMAddress(void)
{
    return (u32)HW_ITCM;
}


//=======================================================================
//           DTCM
//=======================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_EnableDTCM

  Description:  enable DTCM

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_EnableDTCM(void);

/*---------------------------------------------------------------------------*
  Name:         OS_DisableDTCM

  Description:  disable DTCM

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_DisableDTCM(void);

/*---------------------------------------------------------------------------*
  Name:         OS_SetDTCMParam

  Description:  set parameter to DTCM

  Arguments:    param :  parameter to be set to DTCM

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_SetDTCMParam(u32 param);

/*---------------------------------------------------------------------------*
  Name:         OS_GetDTCMParam

  Description:  get parameter to DTCM

  Arguments:    None

  Returns:      parameter about DTCM
 *---------------------------------------------------------------------------*/
u32     OS_GetDTCMParam(void);



//================================================================================
//          SET TCM ADDRESS
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_SetDTCMAddress

  Description:  Set start address of DTCM

  Arguments:    start address of DTCM

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    OS_SetDTCMAddress(u32 address);



//================================================================================
//          GET TCM ADDRESS
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_GetDTCMAddress

  Description:  Get start address of DTCM

  Arguments:    None.

  Returns:      start address of DTCM
 *---------------------------------------------------------------------------*/
u32     OS_GetDTCMAddress(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_TCM_H_ */
#endif
