/*---------------------------------------------------------------------------*
  Project:  NitroSDK - CARD - include
  File:     pullOut.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: pullOut.h,v $
  Revision 1.6  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.5  2005/06/01 07:09:52  yosizaki
  add CARD_CheckPulledOut().

  Revision 1.4  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.3  2004/09/27 13:48:08  yada
  change polling for card remove

  Revision 1.2  2004/09/16 04:20:33  yada
  add CARD_IsPulledOut

  Revision 1.1  2004/09/15 05:45:55  yada
  first release

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_CARD_PULLOUT_H_
#define NITRO_CARD_PULLOUT_H_


#if defined(__cplusplus)
extern  "C"
{
#endif

//---- callback type for card pulled out
    typedef BOOL (*CARDPulledOutCallback) (void);


/*---------------------------------------------------------------------------*
  Name:         CARD_InitPulledOutCallback

  Description:  set system callback for being pulled out card

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
    void    CARD_InitPulledOutCallback(void);

/*---------------------------------------------------------------------------*
  Name:         CARD_SetPulledOutCallback

  Description:  set user callback for being pulled out card

  Arguments:    callback : callback

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
    void    CARD_SetPulledOutCallback(CARDPulledOutCallback callback);
#endif

/*---------------------------------------------------------------------------*
  Name:         CARD_TerminateForPulledOut

  Description:  terminate for pulling out card
                send message to do termination to ARM7

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
    void    CARD_TerminateForPulledOut(void);
#endif

/*---------------------------------------------------------------------------*
  Name:         CARD_PulledOutCallbackProc

  Description:  callback for card pulled out

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
    void    CARD_PulledOutCallbackProc(void);
#endif

/*---------------------------------------------------------------------------*
  Name:         CARD_CheckPulledOut

  Description:  get whether system has detected pulled out card
                by comparing IPL cardID with current cardID
                (notice that once card pulled out, IDs are different absolutely)

  Arguments:    None

  Returns:      TRUE if current cardID is equal to IPL cardID
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM9
    void    CARD_CheckPulledOut(void);
#endif

/*---------------------------------------------------------------------------*
  Name:         CARD_IsPulledOut

  Description:  return whether card is pulled out

  Arguments:    None

  Returns:      TRUE if detect pulled out
 *---------------------------------------------------------------------------*/
    BOOL    CARD_IsPulledOut(void);

/*---------------------------------------------------------------------------*
  Name:         CARD_CheckPullOut_Polling

  Description:  polling that card is pulled out

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
#ifdef SDK_ARM7
    void    CARD_CheckPullOut_Polling(void);
#endif


#if defined(__cplusplus)
}                                      /* extern "C" */
#endif


/* NITRO_CARD_PULLOUT_H_ */
#endif
