/*---------------------------------------------------------------------------*
  Project:  NitroSDK - WFS - include
  File:     client.h

  Copyright 2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef	NITRO_WFS_CLIENT_H_
#define	NITRO_WFS_CLIENT_H_


#include "nitro/wfs/format.h"
#include "nitro/fs.h"


#ifdef __cplusplus
extern  "C"
{
#endif


/*---------------------------------------------------------------------------*/
/* Constants */

/* The maximum file size (set at 4 MB) the child device can receive */
#define	WFS_FILE_SIZE_MAX	(4 * 1024 * 1024)


/*---------------------------------------------------------------------------*/
/* Declarations */

/* ROM read request completion callback */
struct WFSClientContext;
typedef void (*WFSRequestClientReadDoneCallback)(struct WFSClientContext *context, BOOL succeeded, void *arg);

/* WBT client context structure */
typedef struct WFSClientContext
{
    /* Basic settings */
    void                   *userdata;
    WFSEventCallback        callback;
    MIAllocator            *allocator;
    u32                     fat_ready:1;
    u32                     flags:31;
    /* WBT management */
    WBTContext              wbt[1];
    WBTCommandList          wbt_list[2];
    WBTRecvBufTable         recv_buf_table;
    WBTPacketBitmapTable    recv_buf_packet_bmp_table;
    WBTBlockInfoTable       block_info_table;
    WBTBlockInfo            block_info[16];
    /* Receive bit set management */
    u32                    *recv_pkt_bmp_buf;
    u32                     max_file_size;
    /* FAT management */
    WFSTableFormat          table[1];
    /* Request management */
    u32                     block_id;
    CARDRomRegion           request_region;
    void                   *request_buffer;
    WFSRequestClientReadDoneCallback request_callback;
    void                   *request_argument;
    u8                      padding[12];
}
WFSClientContext;


/*---------------------------------------------------------------------------*/
/* Functions */

/*---------------------------------------------------------------------------*
  Name:         WFS_InitClient

  Description:  Initializes the WFS client context.

  Arguments:    context          The WFSClientContext structure.
                userdata         Any user-defined value associated with the context.
                callback         The system event notification callback.
                                 Specify NULL if not needed.
                allocator        The allocator used internally.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_InitClient(WFSClientContext *context,
                    void *userdata, WFSEventCallback callback,
                    MIAllocator *allocator);

/*---------------------------------------------------------------------------*
  Name:         WFS_StartClient

  Description:  Starts the WFS client context communication.

  Arguments:    context          The WFSClientContext structure.
                peer             The device's connection information.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_StartClient(WFSClientContext *context, const WFSPeerInfo *peer);

/*---------------------------------------------------------------------------*
  Name:         WFS_EndClient

  Description:  Deallocates the WFS client context.

  Arguments:    context          The WFSClientContext structure.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_EndClient(WFSClientContext *context);

/*---------------------------------------------------------------------------*
  Name:         WFS_CallClientConnectHook

  Description:  Connection notification on the client side.

  Arguments:    context          The WFSClientContext structure.
                peer             Information for the connected client.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_CallClientConnectHook(WFSClientContext *context, const WFSPeerInfo *peer);

/*---------------------------------------------------------------------------*
  Name:         WFS_CallClientDisconnectHook

  Description:  Disconnect notification on the client side.

  Arguments:    context          The WFSClientContext structure.
                peer             Information for the disconnected client.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_CallClientDisconnectHook(WFSClientContext *context, const WFSPeerInfo *peer);

/*---------------------------------------------------------------------------*
  Name:         WFS_CallClientPacketSendHook

  Description:  Notification of timing when it is possible to send packets on the client side.

  Arguments:    context          The WFSClientContext structure.
                packet           Send packet settings.

  Returns:      The actual packet size.
 *---------------------------------------------------------------------------*/
void WFS_CallClientPacketSendHook(WFSClientContext *context, WFSPacketBuffer *packet);

/*---------------------------------------------------------------------------*
  Name:         WFS_CallClientPacketRecvHook

  Description:  Notification of timing when it is possible to receive packets on the client side.

  Arguments:    context          The WFSClientContext structure.
                packet           Sender packet information.

  Returns:      The actual packet size.
 *---------------------------------------------------------------------------*/
void WFS_CallClientPacketRecvHook(WFSClientContext *context, const WFSPacketBuffer *packet);

/*---------------------------------------------------------------------------*
  Name:         WFS_IsClientReady

  Description:  Determine whether client-side preparations have completed.
                Returns TRUE after a WFS_EVENT_CLIENT_READY notification.

  Arguments:    context          The WFSClientContext structure.

  Returns:      TRUE if client-side preparations are complete.
 *---------------------------------------------------------------------------*/
PLATFORM_ATTRIBUTE_INLINE
BOOL WFS_IsClientReady(const WFSClientContext *context)
{
    return context->fat_ready ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------*
  Name:         WFS_GetTableFormat

  Description:  Gets the ROM file table received from the server.
                Only gets a valid value after a WFS_EVENT_CLIENT_READY notification.

  Arguments:    context          The WFSClientContext structure.

  Returns:      Either the ROM file table or NULL.
 *---------------------------------------------------------------------------*/
PLATFORM_ATTRIBUTE_INLINE
const WFSTableFormat *WFS_GetTableFormat(const WFSClientContext *context)
{
    return WFS_IsClientReady(context) ? context->table : NULL;
}

/*---------------------------------------------------------------------------*
  Name:         WFS_RequestClientRead

  Description:  Begins a ROM image read request from the server.

  Arguments:    context          The WFSClientContext structure.
                buffer           Memory where the read data will be stored.
                offset           Starting position for the device read.
                length           The read size.
                callback         Read completion callback
                                 NULL if not necessary.
                arg              Argument passed to the read completion callback
  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_RequestClientRead(WFSClientContext *context, void *buffer, u32 offset,
                           u32 length, WFSRequestClientReadDoneCallback callback,
                           void *arg);

/*---------------------------------------------------------------------------*
  Name:         WFS_GetClientReadProgress

  Description:  Gets the progress of the ROM image read request.

  Arguments:    context          The WFSClientContext structure.
                current          Variable that gets the number of received packets.
                total            Variable that gets the total expected number of packets.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_GetClientReadProgress(WFSClientContext *context, int *current, int *total);

/*---------------------------------------------------------------------------*
  Name:         WFS_ReplaceRomArchive

  Description:  Mount the WFS ROM file table on the "rom" archive.

  Arguments:    context          The WFSClientContext structure.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WFS_ReplaceRomArchive(WFSClientContext *context);


/*---------------------------------------------------------------------------*/


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* NITRO_WFS_CLIENT_H_ */
/*---------------------------------------------------------------------------*
  $Log: client.h,v $
  Revision 1.3  2007/08/22 05:22:32  yosizaki
  Fixed dependencies.

  Revision 1.2  2007/06/11 09:02:30  yosizaki
  Added some functions.

  Revision 1.1  2007/04/13 04:14:18  yosizaki
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
