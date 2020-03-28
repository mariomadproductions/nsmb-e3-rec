/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     message.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: message.h,v $
  Revision 1.12  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.11  2005/07/20 09:41:31  yada
  add OS_IsMessageQueueFull()

  Revision 1.10  2005/07/20 09:36:30  yada
  add OS_GetMessageCount()

  Revision 1.9  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.8  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.7  2004/03/12 12:09:51  yada
  only fix comment

  Revision 1.6  2004/03/12 08:41:14  yada
  changed name from OS_PeepMessage() -> OS_ReadMessage()

  Revision 1.5  2004/03/12 02:39:12  yada
  added OS_PeepMessage()

  Revision 1.4  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.3  2004/01/18 04:47:31  yada
  Reformed indents, etc.

  Revision 1.2  2003/12/25 07:29:33  yada
  Changes as per unified type rules

  Revision 1.1  2003/11/26 01:51:38  yada
  Initial release.


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_MESSAGE_H_
#define NITRO_OS_MESSAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------------
//---- type definition about message
typedef struct OSMessageQueue OSMessageQueue;
typedef void *OSMessage;

//---- structure of message queue
#pragma  warn_padding off
struct OSMessageQueue
{
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage *msgArray;
    s32     msgCount;
    s32     firstIndex;
    s32     usedCount;
};
#pragma  warn_padding reset

//---- Flags to turn blocking on/off when sending/receiving message
#define  OS_MESSAGE_NOBLOCK   0
#define  OS_MESSAGE_BLOCK     1



/*---------------------------------------------------------------------------*
  Name:         OS_InitMessageQueue

  Description:  initialize message queue

  Arguments:    mq          message queue
                msgArray    buffer for message queue
                msgCount    max massage size for buffer

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_InitMessageQueue(OSMessageQueue *mq, OSMessage *msgArray, s32 msgCount);


/*---------------------------------------------------------------------------*
  Name:         OS_SendMessage

  Description:  send message to message queue

  Arguments:    mq          message queue
                msg         massage which is sent
                flags       whether wait or not when queue is full

  Returns:      TRUE if send
                
 *---------------------------------------------------------------------------*/
BOOL    OS_SendMessage(OSMessageQueue *mq, OSMessage msg, s32 flags);


/*---------------------------------------------------------------------------*
  Name:         OS_ReceiveMessage

  Description:  receive message from message queue

  Arguments:    mq          message queue
                msg         message which is received
                flags       whether wait or not when queue is empty

  Returns:      TRUE if receive
                
 *---------------------------------------------------------------------------*/
BOOL    OS_ReceiveMessage(OSMessageQueue *mq, OSMessage *msg, s32 flags);


/*---------------------------------------------------------------------------*
  Name:         OS_JamMessage

  Description:  send message to message queue, cutting in the top of the queue

  Arguments:    mq          message queue
                msg         massage which is sent
                flags       whether wait or not when queue is empty

  Returns:      TRUE if send
                
 *---------------------------------------------------------------------------*/
BOOL    OS_JamMessage(OSMessageQueue *mq, OSMessage msg, s32 flags);


/*---------------------------------------------------------------------------*
  Name:         OS_ReadMessageMessage

  Description:  read message at message queue. no change to queue
                not occur to switch threads.

  Arguments:    mq          message queue
                msg         message which is received
                flags       whether wait or not when queue is empty

  Returns:      TRUE if read
                
 *---------------------------------------------------------------------------*/
BOOL    OS_ReadMessage(OSMessageQueue *mq, OSMessage *msg, s32 flags);


/*---------------------------------------------------------------------------*
  Name:         OS_GetMessageCount

  Description:  get message count of message queue.

  Arguments:    mq          message queue

  Returns:      message count
                
 *---------------------------------------------------------------------------*/
static inline s32 OS_GetMessageCount(OSMessageQueue *mq)
{
    SDK_ASSERT(mq);
    return mq->msgCount;
}


/*---------------------------------------------------------------------------*
  Name:         OS_IsMessageQueueFull

  Description:  get whether message queue is full or not

  Arguments:    mq          message queue

  Returns:      TRUE if full
                
 *---------------------------------------------------------------------------*/
static inline BOOL OS_IsMessageQueueFull(OSMessageQueue *mq)
{
    SDK_ASSERT(mq);
    return (mq->usedCount >= mq->msgCount);
}


//--------------------------------------------------------------------------------
#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_MESSAGE_H_ */
#endif
