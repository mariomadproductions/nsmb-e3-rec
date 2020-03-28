/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MB - include
  File:     mb_child.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mb_child.h,v $
  Revision 1.5  2005/09/02 08:29:14  yosizaki
  add compatible symbol 'MB_COMM_CSTATE_CANCELED'

  Revision 1.4  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.3  2005/02/28 05:26:24  yosizaki
  do-indent.

  Revision 1.2  2004/11/24 23:46:03  takano_makoto
  Added MB_COMM_CSTATE_FAKE_END.

  Revision 1.1  2004/11/22 12:57:34  takano_makoto
  Initial update.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/


#ifndef NITRO_MB_MB_CHILD_H_
#define NITRO_MB_MB_CHILD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/types.h"
#include "nitro/mb/mb.h"

/* ---------------------------------------------------------------------

        Type Definitions

   ---------------------------------------------------------------------*/

//---------------------------------------------------------
// Child's download state
//---------------------------------------------------------

typedef enum
{
    MB_COMM_CSTATE_NONE,               // State before initialization
    MB_COMM_CSTATE_INIT_COMPLETE,      // State when MB child initialization has completed.
    MB_COMM_CSTATE_CONNECT,            // State when connection to parent has completed.
    MB_COMM_CSTATE_CONNECT_FAILED,     // State when connection to parent has failed.
    MB_COMM_CSTATE_DISCONNECTED_BY_PARENT,      // State when cut off by parent
    MB_COMM_CSTATE_REQ_ENABLE,         // State when MP is established and data requests are possible.
    MB_COMM_CSTATE_REQ_REFUSED,        // State when kicked from the parent in response to a request
    MB_COMM_CSTATE_DLINFO_ACCEPTED,    // State when a request has been accepted by a parent
    MB_COMM_CSTATE_RECV_PROCEED,       // State when download data receipt has commenced
    MB_COMM_CSTATE_RECV_COMPLETE,      // State when download data receipt has completed
    MB_COMM_CSTATE_BOOTREQ_ACCEPTED,   // State when a boot request from a parent has been received
    MB_COMM_CSTATE_BOOT_READY,         // State when communication with a parent is disconnected and boot is complete
    MB_COMM_CSTATE_CANCELED,           // State when canceled midway, and disconnect from parent is complete
    MB_COMM_CSTATE_CANCELLED = MB_COMM_CSTATE_CANCELED,
    MB_COMM_CSTATE_AUTHENTICATION_FAILED,       // 
    MB_COMM_CSTATE_MEMBER_FULL,        // State when the number of entries to the parent has exceeded capacity
    MB_COMM_CSTATE_GAMEINFO_VALIDATED, // State when parent beacon is received
    MB_COMM_CSTATE_GAMEINFO_INVALIDATED,        // Case in which a parent beacon that has already been obtained is in an imperfect state.
    MB_COMM_CSTATE_GAMEINFO_LOST,      // Notification of a state in which the parent's beacon has been lost
    MB_COMM_CSTATE_GAMEINFO_LIST_FULL, // Notification that child can no longer obtain a parent
    MB_COMM_CSTATE_ERROR,              // State in which an error was generated halfway

    MB_COMM_CSTATE_FAKE_END,           // Fake child completion notification (state switched to only when using mb_fake_child)

    /*  Internally used enumerated value.
       Cannot transition to this state. */
    MB_COMM_CSTATE_WM_EVENT = 0x80000000
}
MBCommCState;

#define MBCommCStateCallback    MBCommCStateCallbackFunc
/*  Child event notification callback type */
typedef void (*MBCommCStateCallbackFunc) (u32 status, void *arg);


#ifdef __cplusplus
}
#endif


#endif // NITRO_MB_MB_CHILD_H_
