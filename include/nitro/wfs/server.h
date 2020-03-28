/*---------------------------------------------------------------------------*
  Project:  NitroSDK - WFS - include
  File:     server.h

  Copyright 2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef	NITRO_WFS_SERVER_H_
#define	NITRO_WFS_SERVER_H_


#include "nitro/wfs/format.h"
#include "nitro/mi/device.h"
#include "nitro/fs.h"


#ifdef __cplusplus
extern  "C"
{
#endif


/*---------------------------------------------------------------------------*/
/* Constants */

/* The total number of transfer lock handles (sufficient if there are enough for the maximum number of clients that can be connected at the same time) */
#define	WFS_LOCK_HANDLE_MAX	    15


/*---------------------------------------------------------------------------*/
/* Declarations */

/* The information structure notified at a WFS_EVENT_SERVER_SEGMENT_REQUEST event */
typedef struct WFSSegmentBuffer
{
    u32     offset;
    u32     length;
    void   *buffer;
}
WFSSegmentBuffer;

/* The transfer lock range information structure */
typedef struct WFSLockInfo
{
    WBTBlockInfoList info;
    int     ref;        /* Reference count */
    u32     offset;     /* Starting ROM address */
    u32     length;     /* ROM read size */
    u32     ack_seq;    /* The sequence number that should be returned next */
}
WFSLockInfo;

/* The WFS server information structure */
typedef struct WFSServerContext
{
    void               *userdata;
    WFSEventCallback    callback;

    /* Internal thread information */
    void               *thread_work;
    void (*thread_hook)(void *thread, void *argument);

    /* The list managing the locked regions */
    int                 use_bitmap;
    WFSLockInfo         list[WFS_LOCK_HANDLE_MAX];

    /* The ROM file table */
    WFSTableFormat      table[1];
    WBTBlockInfoList    table_info[1];
    MIAllocator        *allocator;

    /* The client status management member */
    int                 all_bitmap;     /* Connecting */
    int                 busy_bitmap;    /* Accessing */
    int                 sync_bitmap;    /* Synchronizing */
    int                 ack_bitmap;     /* Waiting for a response from the server */
    WFSMessageFormat    recv_msg[16];   /* The latest message */

    /* Member related to dynamically changing packet sizes */
    BOOL                is_changing;    /* Flag indicating change is expected */
    int                 new_packet;     /* Packet size after the change */
    int                 deny_bitmap;	/* Denied response target during change */

    /* WBT-related member */
    u8                  cache_hit_buf[512];
    WBTContext          wbt[1];
    WBTCommandList      wbt_list[2];
    BOOL                msg_busy;       /* Sending response */
}
WFSServerContext;


/*---------------------------------------------------------------------------*/
/* Functions */

/*---------------------------------------------------------------------------*
  Name:         WFS_InitServer

  Description:  Initializes the WFS server context.

  Arguments:    context:          The WFSServerContext structure.
                userdata:         Any user-defined value associated with the context.
                callback:         The system event notification callback.
                                 Specify NULL if not needed.
                allocator:        The allocator used internally.
                packet:           The parent's initial packet size.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_InitServer(WFSServerContext *context,
                    void *userdata, WFSEventCallback callback,
                    MIAllocator *allocator, int packet);

/*---------------------------------------------------------------------------*
  Name:         WFS_EndServer

  Description:  Deallocates the WFS server context.

  Arguments:    context:          The WFSServerContext structure.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_EndServer(WFSServerContext *context);

/*---------------------------------------------------------------------------*
  Name:         WFS_RegisterServerTable

  Description:  Loads the ROM file table from the device and registers it to the server.

  Arguments:    context:          The WFSServerContext structure.
                device:           The device storing the NTR binary.
                fatbase:          The offset within the device wherein the NTR binary is located.
                overlay:          The offset within the device wherein is located the NTR binary containing the overlay to be merged
                                  
                                 (If not merging multiple ROM file tables, this value is identical to "fatbase".)
                                   

  Returns:      TRUE when the ROM file table is correctly loaded and registered.
 *---------------------------------------------------------------------------*/
BOOL WFS_RegisterServerTable(WFSServerContext *context,
                             MIDevice *device, u32 fatbase, u32 overlay);

/*---------------------------------------------------------------------------*
  Name:         WFS_CallServerConnectHook

  Description:  Server-side connection notification.

  Arguments:    context:          The WFSServerContext structure.
                peer:             Information for the connected client.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_CallServerConnectHook(WFSServerContext *context, const WFSPeerInfo *peer);

/*---------------------------------------------------------------------------*
  Name:         WFS_CallServerDisconnectHook

  Description:  Disconnect notification on the server side.

  Arguments:    context:          The WFSServerContext structure.
                peer:             Information for the disconnected client.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_CallServerDisconnectHook(WFSServerContext *context, const WFSPeerInfo *peer);

/*---------------------------------------------------------------------------*
  Name:         WFS_CallServerPacketSendHook

  Description:  Notification of timing when it is possible to send packets on the server side.

  Arguments:    context:          The WFSServerContext structure.
                packet:           Send packet settings.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_CallServerPacketSendHook(WFSServerContext *context, WFSPacketBuffer *packet);

/*---------------------------------------------------------------------------*
  Name:         WFS_CallServerPacketRecvHook

  Description:  Server-side packet receipt notification.

  Arguments:    context:          The WFSServerContext structure.
                packet:           Sender packet information.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_CallServerPacketRecvHook(WFSServerContext *context, const WFSPacketBuffer *packet);

/*---------------------------------------------------------------------------*
  Name:         WFS_GetServerConnectedBitmap

  Description:  Gets bitmaps for clients currently connected to the server.

  Arguments:    context:          The WFSServerContext structure.

  Returns:      The clients currently connected to the server.
 *---------------------------------------------------------------------------*/
PLATFORM_ATTRIBUTE_INLINE
int WFS_GetServerConnectedBitmap(const WFSServerContext *context)
{
    return context->all_bitmap;
}

/*---------------------------------------------------------------------------*
  Name:         WFS_GetServerBusyBitmap

  Description:  Gets bitmaps for clients currently accessing the server.

  Arguments:    context:          The WFSServerContext structure.

  Returns:      The clients currently accessing the server.
 *---------------------------------------------------------------------------*/
PLATFORM_ATTRIBUTE_INLINE
int WFS_GetServerBusyBitmap(const WFSServerContext *context)
{
    return context->busy_bitmap;
}

/*---------------------------------------------------------------------------*
  Name:         WFS_GetServerSyncBitmap

  Description:  Gets bitmaps for clients currently synchronously accessing the server.

  Arguments:    context:          The WFSServerContext structure.

  Returns:      The clients currently synchronously accessing the server.
 *---------------------------------------------------------------------------*/
PLATFORM_ATTRIBUTE_INLINE
int WFS_GetServerSyncBitmap(const WFSServerContext *context)
{
    return context->sync_bitmap;
}

/*---------------------------------------------------------------------------*
  Name:         WFS_GetServerPacketLength

  Description:  Obtain the size of packets sent by the server.

  Arguments:    context:          The WFSServerContext structure.

  Returns:      The currently specified packet size.
 *---------------------------------------------------------------------------*/
int WFS_GetServerPacketLength(const WFSServerContext *context);

/*---------------------------------------------------------------------------*
  Name:         WFS_SetServerPacketLength

  Description:  Sets the size of the server send packet.

  Arguments:    context:          The WFSServerContext structure.
                length:           The packet size to be set.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_SetServerPacketLength(WFSServerContext *context, int length);

/*---------------------------------------------------------------------------*
  Name:         WFS_SetServerSync

  Description:  Sets the clients that synchronously access the server.
                This function achieves highly efficient transfers by making full use of the characteristics of the WBT Library. It does this by synchronizing the responses to client groups which are clearly guaranteed to be accessing the same group of files in the same order.
                 
                 
                Note, however, that caution is required. If the synchronization start timing is not logically stable, the responses may slip out of synchronization and the system can deadlock.
                 

  Arguments:    context:          The WFSServerContext structure.
                bitmap:           The AID bitmap for the client to be synchronized.
                                 Synchronization will not occur when 0 (the default value) is specified.
                                 The last bit is always ignored.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_SetServerSync(WFSServerContext *context, int bitmap);

/*---------------------------------------------------------------------------*
  Name:         WFS_ExecuteRomServerThread

  Description:  Registers the specified ROM file to the WFS library so that it will be distributed, and internally automatically starts up the ROM access thread.
                 
                These threads are automatically destroyed in the WFS_EndServer function.

  Arguments:    context:          The WFSServerContext structure.
                file:             The SRL file that contains the file system to be distributed.
                                 Specify NULL for clone boot.
                sharedFS:         TRUE if the file system is to be shared by the parent and child.
                                 In such a case, a combined file system is distributed. For this combined file system, only the overlay held by "file"is extracted and appended to the file system of the parent device itself.
                                  
                                  
                                 If "file" is set to NULL, it specifies clone boot, so this argument is ignored. (It is interpreted as always TRUE.)
                                  


  Returns:      TRUE if ROM file registration and thread creation succeed.
 *---------------------------------------------------------------------------*/
BOOL WFS_ExecuteRomServerThread(WFSServerContext *context, FSFile *file, BOOL sharedFS);


/*---------------------------------------------------------------------------*/


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* NITRO_WFS_SERVER_H_ */
/*---------------------------------------------------------------------------*
  $Log: server.h,v $
  Revision 1.5  2007/08/22 05:22:32  yosizaki
  Fixed dependencies.

  Revision 1.4  2007/06/14 13:14:10  yosizaki
  Added WFS_ExecuteRomServerThread.

  Revision 1.3  2007/06/11 09:03:37  yosizaki
  Added WFS_GetServerPacketLength().

  Revision 1.2  2007/04/17 00:00:52  yosizaki
  Renamed some structures.

  Revision 1.1  2007/04/13 04:14:18  yosizaki
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

