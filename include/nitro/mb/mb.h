/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MB - include
  File:     mb.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: mb.h,v $
  Revision 1.13  2006/01/18 02:11:29  kitase_hirotake
  do-indent

  Revision 1.12  2005/08/17 01:13:34  yosizaki
  add MB_GetMultiBootDownloadParameter().

  Revision 1.11  2005/05/20 03:11:07  yosizaki
  add MBGameRegistry::userParam.

  Revision 1.10  2005/04/11 03:37:16  yosizaki
  fix comment.

  Revision 1.9  2005/04/11 01:46:10  yosizaki
  add MB_SetLifeTime().
  add MB_SetPowerSaveMode().

  Revision 1.8  2005/03/14 07:09:33  sato_masaki
  Added MB_GetGameEntryBitmap() function.

  Revision 1.7  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.6  2005/02/28 05:26:24  yosizaki
  do-indent.

  Revision 1.5  2004/11/24 05:14:43  yosizaki
  rename MB_StartParentEx/MB_EndEx..

  Revision 1.4  2004/11/22 12:58:17  takano_makoto
  comments added

  Revision 1.3  2004/11/18 07:34:05  takano_makoto
  Got rid of the argument for setting child transfer size in MB_SetParentCommSize, MB_SetParentCommParam

  Revision 1.2  2004/11/11 11:54:44  yosizaki
  add MB_SEGMENT_BUFFER_MIN.
  increase MB_SYSTEM_BUF_SIZE for task-system. (+0x1000)

  Revision 1.1  2004/11/10 13:12:47  takano_makoto
  Moved file position

  Revision 1.54  2004/10/26 08:10:34  takano_makoto
  Added MB_DisconnectChild

  Revision 1.53  2004/10/18 11:46:12  yosizaki
  add MB_StartParentEx, MB_EndEx.

  Revision 1.52  2004/10/05 14:42:50  yosizaki
  export some MB_COMM_P_* range consts.

  Revision 1.51  2004/10/04 13:40:25  terui
  Standardized game group IDs as type u32.

  Revision 1.50  2004/10/01 07:39:11  sato_masaki
  Added MB_COMM_PSTATE_WAIT_TO_SEND state.

  Revision 1.49  2004/09/22 12:17:56  sato_masaki
  add function MB_SetParentCommParam()

  Revision 1.48  2004/09/21 01:39:31  sato_masaki
  Standardized errors that originate in WM to MB_ERRCODE_WM_FAILURE. Abolished MB_ERRCODE_MP_SENT_FAILURE.

  Revision 1.47  2004/09/20 13:16:07  sato_masaki
  - Changed MB_MAX_FILE to 16.
  - Removed MB_ERROR definition.
  - Removed the level member from the MBErrorStatus structure (abolished error level)
  - Moved error definitions from the MBError enumerator to the MBErrCode enumerator.

  Revision 1.46  2004/09/17 05:08:10  sato_masaki
  small fix

  Revision 1.45  2004/09/17 04:43:09  sato_masaki
  add function MB_ReadMultiBootParentBssDesc()

  Revision 1.44  2004/09/16 12:46:56  sato_masaki
  Changed functions defined as MBi_*** to MB_***.

  Revision 1.43  2004/09/15 06:27:34  sato_masaki
  add function MBi_SetParentCommSize, MBi_GetTgid

  Revision 1.42  2004/09/15 05:08:20  miya
  Added error codes.

  Revision 1.41  2004/09/14 14:23:19  yosiokat
  - Moved constant definitions that can only be used in mb_gameinfo.c to mb_gameinfo.c.

  Revision 1.40  2004/09/14 13:20:13  sato_masaki
  Changed to send request data in fragments.

  Revision 1.39  2004/09/14 06:06:24  sato_masaki
  Made MB_CommBootRequest**, MB_CommStartSending** in-line.

  Revision 1.38  2004/09/13 13:03:32  yosiokat
  - Changed MB_GAME_NAME_LENGTH to "48".
  - ChangedMB_GAME_INTRO_LENGTH to "96".

  Revision 1.37  2004/09/13 08:18:54  sato_masaki
  - add MB_COMM_PSTATE_ERROR to MBCommPState
  - add MBiErrorStatus, MBiError

  Revision 1.36  2004/09/13 03:01:14  sato_masaki
  Added MBi_Init(). (for backward compatibility)
  Changed MB_GetParentSystemBufSize to MBi_GetParentSystemBufSize.

  Revision 1.35  2004/09/11 11:23:57  sato_masaki
  - Changed the value of MB_SYSTEM_BUF_SIZE.
  - Added member to MBCommResponseRequestType type.
  - Added MB_GetParentSystemBufSize().

  Revision 1.34  2004/09/10 07:40:51  yosizaki
  add MBCommRequestData.

  Revision 1.33  2004/09/10 06:30:29  sato_masaki
  Added comment.

  Revision 1.32  2004/09/10 02:42:10  sato_masaki
  Changed number definitions related to playerNo in the MBUserInfo structure.
  (Old: Parent 15, Child 0-14 -> New: Parent 0, Child 1-15)

  Revision 1.31  2004/09/08 04:39:54  sato_masaki
  Revised comment.

  Revision 1.30  2004/09/08 04:39:13  sato_masaki
  Added MB_CommBootRequestAll() function. This function has features that are compatible with the MB_CommBootRequest() that existed before the change.

  Revision 1.29  2004/09/07 11:56:05  sato_masaki
  - Changed MB_CommBootRequest() so that it specifies AID.
  - Name change: MB_COMM_PSTATE_CANCEL to MB_COMM_PSTATE_END.
    MB_COMM_PSTATE_END is now the only MB library end callback.

  Revision 1.28  2004/09/07 04:41:14  sato_masaki
  Added MB_COMM_PSTATE_WM_EVENT to the MBCommPState enumerators.

  Revision 1.27  2004/09/06 12:26:43  sato_masaki
  Corrected comments

  Revision 1.26  2004/09/06 12:02:33  sato_masaki
  - Added tgid as an argument for the MB_Init() function.

  Revision 1.25  2004/09/04 09:51:35  sato_masaki
  Revised description. Removed remaining definitions related to child API and types.

  Revision 1.24  2004/09/04 06:46:49  sato_masaki
  Added a callback state for when the number of members is exceeded (MB_COMM_*STATE_MEMBER_FULL).

  Revision 1.23  2004/09/03 07:11:15  sato_masaki
  Removed API code for controlling children.

  Revision 1.22  2004/09/02 11:55:58  sato_masaki
  Added child AID to MB_CommStartSending() as an argument.
  Changed to use MB_CommStartSendingAll() when batch sending to all children that have entered.
  and NNS_G2dResetMCCellAnimationAll().

  Revision 1.21  2004/09/02 09:59:44  sato_masaki
  Name change: MB_DeleteFile() to MB_UnregisterFile().

  Revision 1.20  2004/09/02 09:45:56  sato_masaki
  Added function for deregistering a file: MB_DeleteFile().

  Revision 1.19  2004/08/27 04:04:43  sato_masaki
  Added MB_COMM_CSTATE_AUTHENTICATION_FAILED to MBCommCState.

  Revision 1.18  2004/08/26 09:59:54  sato_masaki
  Added MB_COMM_PSTATE_REQUESTED.
  Added MB_CommResponseRequest function.

  Revision 1.17  2004/08/25 03:15:18  sato_masaki
  Added MB_CommStartSending function.

  Revision 1.16  2004/08/19 14:54:44  yosiokat
  Revised MB_BEACON_FIXED_DATA_SIZE in line with structure change.

  Revision 1.15  2004/08/19 07:42:26  sato_masaki
  Changed definition of MB_ROM_HEADER_ADDRESS to HW_ROM_HEADER_BUF.

  Revision 1.14  2004/08/19 02:42:14  yosizaki
  change type of MBUserInfo.

  Revision 1.13  2004/08/16 13:08:02  sato_masaki
  Added RomHeader storage address, MB_ROM_HEADER_ADDRESS.

  Revision 1.12  2004/08/14 12:19:56  sato_masaki
  Removed gameInfoLength member from MBParentBssDesc.

  Revision 1.11  2004/08/13 13:16:10  sato_masaki
  Added MB_COMM_PSTATE_DISCONNECTED.

  Revision 1.10  2004/08/12 12:05:18  sato_masaki
  Changed ordering in MBCommCState.

  Revision 1.9  2004/08/12 09:56:28  yosiokat
  Changed MBGameRegistry icon data specification to a pointer to a file path.

  Revision 1.8  2004/08/12 09:14:11  yosiokat
  - Added MB_SCAN_LOCK_SEC.
  - Added MB_COMM_CSTATE_CONNECT_FAILED and MB_COMM_CSTATE_DISCONNECTED_BY_PARENT to MBCommCState.
  - Added internally used function MB_DeleteRecvGameInfo.

  Revision 1.7  2004/08/12 09:11:11  yosiokat
  - Changed the MB_BSSDESC_SIZE definition to sizeof(MBParentBssDesc).
  - Changed the MB_BSSDESC_ADDRESS definition to 0x023fe800.

  Revision 1.6  2004/08/10 12:07:55  sato_masaki
  Changed parent and child state definitions. Added the functions MB_CommBootRequest, MB_CommIsBootable.

  Revision 1.5  2004/08/09 14:56:09  yosizaki
  format all the symbol for API

  Revision 1.4  2004/08/09 07:08:49  sato_masaki
  Changed the value of the MB_BSSDESC_ADDRESS definition.

  Revision 1.3  2004/08/08 23:42:14  yosizaki
  change some names.

  Revision 1.2  2004/08/07 15:03:12  yosizaki
  merge all the diff. (-2004/08/07)

  Revision 1.1  2004/08/07 07:03:27  yosizaki
  (none)

  $NoKeywords: $
 *---------------------------------------------------------------------------*/


#ifndef NITRO_MB_MB_H_
#define NITRO_MB_MB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/types.h"
#include "nitro/misc.h"
#include "nitro/fs/file.h"
#include "nitro/wm.h"


/* ---------------------------------------------------------------------

        Constant

   ---------------------------------------------------------------------*/

#define MB_MAX_CHILD                    WM_NUM_MAX_CHILD

/* Number of characters in file name */
#define MB_FILENAME_SIZE_MAX            (10)

/* Maximum files in parent */
#define MB_MAX_FILE                     (16)

/* Size of multiboot work */
#define MB_SYSTEM_BUF_SIZE              (0xC000)

/* Possible size setting range for parent communication */
#define MB_COMM_PARENT_SEND_MIN         256
#define MB_COMM_PARENT_SEND_MAX         510

#define MB_COMM_PARENT_RECV_MIN         8
#define MB_COMM_PARENT_RECV_MAX         16

/* Minimum buffer size required for MB_ReadSegment() */
#define MB_SEGMENT_BUFFER_MIN           0x10000

/* MB API result type */
#define MB_SUCCESS                      MB_ERRCODE_SUCCESS      // Back compatible

/* Definition value that specifies that the TGID value for MB_Init() should be automatically set */
#define	MB_TGID_AUTO	0x10000

/*
 * Parent game information for multiboot
 */

#define MB_ICON_COLOR_NUM               16      // Number of icon colors
#define MB_ICON_PALETTE_SIZE            (MB_ICON_COLOR_NUM * 2) // Icon data size (16 bit color x number of colors)
#define MB_ICON_DATA_SIZE               512     // Icon data size (32x32 dots, 16 colors)
#define MB_GAME_NAME_LENGTH             48      // Game name length (2-byte units)   Note: Specify to fit within the number of characters shown to the left and within a width of 185 dots.
#define MB_GAME_INTRO_LENGTH            96      // Game description length (2-byte units)   Note: Specify to fit within the number of characters shown to the left and within a width of 199 dots x 2.
#define MB_USER_NAME_LENGTH             10      // User name length (2-byte units)
#define MB_MEMBER_MAX_NUM               15      // Maximum number of communicating members
#define MB_FILE_NO_MAX_NUM              64      // When MbGameInfo.fileNo is carried on the beacon it becomes 6-bit. Therefore the maximum number is 64.
#define MB_GAME_INFO_RECV_LIST_NUM      16      // Number of lists that receive game information on the child side.

/* Boot type */
#define MB_TYPE_ILLEGAL                 0       /* Exception status */
#define MB_TYPE_NORMAL                  1       /* Start from ROM */
#define MB_TYPE_MULTIBOOT               2       /* Multiboot child */

#define MB_BSSDESC_SIZE                 (sizeof(MBParentBssDesc))
#define MB_DOWNLOAD_PARAMETER_SIZE      HW_DOWNLOAD_PARAMETER_SIZE

/* Parent download status */
typedef enum
{
    MB_COMM_PSTATE_NONE,
    MB_COMM_PSTATE_INIT_COMPLETE,
    MB_COMM_PSTATE_CONNECTED,
    MB_COMM_PSTATE_DISCONNECTED,
    MB_COMM_PSTATE_KICKED,
    MB_COMM_PSTATE_REQ_ACCEPTED,
    MB_COMM_PSTATE_SEND_PROCEED,
    MB_COMM_PSTATE_SEND_COMPLETE,
    MB_COMM_PSTATE_BOOT_REQUEST,
    MB_COMM_PSTATE_BOOT_STARTABLE,
    MB_COMM_PSTATE_REQUESTED,
    MB_COMM_PSTATE_MEMBER_FULL,
    MB_COMM_PSTATE_END,
    MB_COMM_PSTATE_ERROR,
    MB_COMM_PSTATE_WAIT_TO_SEND,

    /*  Internally used enumerated value.
       Will not transition to this value's state. */
    MB_COMM_PSTATE_WM_EVENT = 0x80000000
}
MBCommPState;


/* Responses to connection request from child */
typedef enum
{
    MB_COMM_RESPONSE_REQUEST_KICK,     /* Reject child's entry request */
    MB_COMM_RESPONSE_REQUEST_ACCEPT,   /* Accept child's entry request */
    MB_COMM_RESPONSE_REQUEST_DOWNLOAD, /* Notifiy child of commencement of download */
    MB_COMM_RESPONSE_REQUEST_BOOT      /* Notifiy child of commencement of boot */
}
MBCommResponseRequestType;


/*  Parent event notification callback type */
typedef void (*MBCommPStateCallback) (u16 child_aid, u32 status, void *arg);


typedef struct
{
    u16     errcode;
}
MBErrorStatus;

typedef enum
{
    /* Value that indicates success */
    MB_ERRCODE_SUCCESS = 0,

    MB_ERRCODE_INVALID_PARAM,          /* Argument error */
    MB_ERRCODE_INVALID_STATE,          /* Inconsistent call state conditions */

    /* The following errors are only for children */
    MB_ERRCODE_INVALID_DLFILEINFO,     /* Invalid download information */
    MB_ERRCODE_INVALID_BLOCK_NO,       /* Received block number invalid */
    MB_ERRCODE_INVALID_BLOCK_NUM,      /* Number of blocks in received file invalid */
    MB_ERRCODE_INVALID_FILE,           /* Received block from file that was not requested */
    MB_ERRCODE_INVALID_RECV_ADDR,      /* Receive address invalid */

    /* The following errors are caused by WM errors */
    MB_ERRCODE_WM_FAILURE,             /* Error in WM callback */

    /** The following are for when communication connect is not possible. (Must re-initialize WM) **/
    MB_ERRCODE_FATAL,

    MB_ERRCODE_MAX
}
MBErrCode;

/* ---------------------------------------------------------------------

        structures

   ---------------------------------------------------------------------*/

/*
 * Multiboot game registration information structure
 */
typedef struct
{
    /* File path to program binary */
    const char *romFilePathp;
    /* Pointer to game name character string */
    u16    *gameNamep;
    /* Pointer to game content description character string */
    u16    *gameIntroductionp;
    /* Icon character data file path */
    const char *iconCharPathp;
    /* The file path of the icon palette data */
    const char *iconPalettePathp;
    /* Game group ID */
    u32     ggid;
    /* The maximum number of players */
    u8      maxPlayerNum;
    u8      pad[3];
    /* User definition extended parameters (32BYTE) */
    u8      userParam[MB_DOWNLOAD_PARAMETER_SIZE];
}
MBGameRegistry;


/*
 * Icon data structure
 * An icon is 16 color palette + 32 dots * 32 dots.
 */
typedef struct
{
    /* Palette data (32 BYTE) */
    u16     palette[MB_ICON_COLOR_NUM];
    u16     data[MB_ICON_DATA_SIZE / 2];
    /* Character data (512 bytes) */
}
MBIconInfo;                            /* 544 bytes */


/*
 * User information structure
 */
typedef struct
{
    /* Favorite color data (color set number) */
    u8      favoriteColor:4;
    /* Player number (Parent=0, Children = 1-15) */
    u8      playerNo:4;
    /* Nickname Length */
    u8      nameLength;
    /* Nickname */
    u16     name[MB_USER_NAME_LENGTH];
}
MBUserInfo;                            /* 22 bytes */


/*
 * Multiboot parent information
 * (with gameInfo[128] excluded from WMbssDesc)
 */
typedef struct
{
    u16     length;                    // 2
    u16     rssi;                      // 4
    u16     bssid[3];                  // 10
    u16     ssidLength;                // 12
    u8      ssid[32];                  // 44
    u16     capaInfo;                  // 46
    struct
    {
        u16     basic;                 // 48
        u16     support;               // 50
    }
    rateSet;
    u16     beaconPeriod;              // 52
    u16     dtimPeriod;                // 54
    u16     channel;                   // 56
    u16     cfpPeriod;                 // 58
    u16     cfpMaxDuration;            // 60
}
MBParentBssDesc;


/* Structure that holds parent information for mulitboot child */
typedef struct
{
    u16     boot_type;
    MBParentBssDesc parent_bss_desc;
}
MBParam;


/* Data type received when entry request comes from child */
typedef struct
{
    u32     ggid;                      //  4B
    MBUserInfo userinfo;               // 22B
    u16     version;                   //  2B
    u8      fileid;                    //  1B
    u8      pad[3];                    // Total is 29B
}
MBCommRequestData;


/* ---------------------------------------------------------------------

        Multiboot library (MB) API - For parent

   ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
  Name:         MB_Init

  Description:  Initialize MB library

  Arguments:    work   - Pointer to memory that is allocated for managing internal MB status.
                         This size must be at least MB_SYSTEM_BUF_SIZE bytes
                         In the case of dynamic allocation
                         also possible to acquire size with the MB_GetParentSystemBufSize function.
                         companies files as well.
                         The allocated memory is used internally until the MB_End is called.
                         

                user   - Pointer to the structure that holds user data.
                         Content pointed to by this pointer can only be referenced from inside the MB_Init function.
                         

                ggid   - Specifies a GGID.

                tgid   - Value of TGID (Use a value generated by a decision method that follows WM guidelines)
                         
                         When MB_TGID_AUTO is specified, internally an appropriate value is automatically set.
                         

                dma    - DMA channel that is allocated for managing internal MB processes
                         This DMA channel is used internally until the MB_End function is called.
                          
  
  Returns:      Returns MB_SUCCESS if the initialization completes successfully.
 *---------------------------------------------------------------------------*/

int     MB_Init(void *work, const MBUserInfo *user, u32 ggid, u32 tgid, u32 dma);


/*---------------------------------------------------------------------------*
  Name:         MB_GetParentSystemBufSize

  Description:  Acquires the size of the work memory used by MB.

  Arguments:    None.
  
  Returns:      The size of the work memory used by MB.
 *---------------------------------------------------------------------------*/
int     MB_GetParentSystemBufSize(void);


/*---------------------------------------------------------------------------*
  Name:         MB_SetParentCommSize

  Description:  Sets the size of the parent's communication data that is used for MB communication.
                Use this between the time MB_Init is started and MB_StartParent is called.
                Buffer size cannot be changed after communications begins.

  Arguments:    sendSize - The size of data that is sent from a parent to each child.
  
  Returns:      If changing the size of the send/receive data succeeds, returns TRUE.
                Otherwise returns FALSE.
 *---------------------------------------------------------------------------*/

BOOL    MB_SetParentCommSize(u16 sendSize);

/*---------------------------------------------------------------------------*
  Name:         MB_SetParentCommParam

  Description:  Sets the size of the parent's communication data that is used for MB communication, and the maximum number of children that can connect.
                Use this between the time MB_Init is started and MB_StartParent is called.
                Buffer size cannot be changed after communications begins.

  Arguments:    sendSize    - The size of data that is sent from a parent to each child.
                maxChildren - Maximum number of connected children
  
  Returns:      If changing the size of the send/receive data succeeds, returns TRUE.
                Otherwise returns FALSE.
 *---------------------------------------------------------------------------*/

BOOL    MB_SetParentCommParam(u16 sendSize, u16 maxChildren);

/*---------------------------------------------------------------------------*
  Name:         MB_GetTgid

  Description:  Uses the MB library, to acquire the TGID used by WM.

  Arguments:    None.
  
  Returns:      Returns the TGID used by WM.
 *---------------------------------------------------------------------------*/

u16     MB_GetTgid(void);


/*---------------------------------------------------------------------------*
  Name:         MB_End

  Description:  Ends the MB library.

  Arguments:    None.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/

void    MB_End(void);


/*---------------------------------------------------------------------------*
  Name:         MB_EndToIdle

  Description:  Ends the MB library.
                However the WM library will be maintained in IDLE state.

  Arguments:    None.
  
  Returns:      None.
 *---------------------------------------------------------------------------*/

void    MB_EndToIdle(void);

/*---------------------------------------------------------------------------*
  Name:         MB_DisconnectChild

  Description:  Disconnects a child.

  Arguments:    aid              aid of the child to disconnect.
  
  Returns:      Returns MB_SUCCESS if start succeeds.
 *---------------------------------------------------------------------------*/

void    MB_DisconnectChild(u16 aid);


/*---------------------------------------------------------------------------*
  Name:         MB_StartParent

  Description:  Parent parameter setting & start

  Arguments:    channel - Channel used for communicating as a parent
  
  Returns:      Returns MB_SUCCESS if start succeeds.
 *---------------------------------------------------------------------------*/

int     MB_StartParent(int channel);


/*---------------------------------------------------------------------------*
  Name:         MB_StartParentFromIdle

  Description:  Parent parameter setting & start
                However, the WM library must be in IDLE state.

  Arguments:    channel - Channel used for communicating as a parent
  
  Returns:      Returns MB_SUCCESS if start succeeds.
 *---------------------------------------------------------------------------*/

int     MB_StartParentFromIdle(int channel);

/*---------------------------------------------------------------------------*
  Name:         MB_CommGetChildrenNumber

  Description:  Acquires the total number of children that are currently entered.

  Arguments:    None.

  Returns:      Returns the total number of children that the parent currently recognizes.
 *---------------------------------------------------------------------------*/

u8      MB_CommGetChildrenNumber(void);


/*---------------------------------------------------------------------------*
  Name:         MB_CommGetChildUser

  Description:  Acquires information belonging to a child that has a specified aid.

  Arguments:    child_aid - aid that specifies the child for which status is being acquired
  
  Returns:      Returns MB_SUCCESS if start succeeds.
 *---------------------------------------------------------------------------*/

const MBUserInfo *MB_CommGetChildUser(u16 child_aid);


/*---------------------------------------------------------------------------*
  Name:         MB_CommGetParentState

  Description:  Acquires the state of a parent with respect to a child that has a specified aid.

  Arguments:    child_aid - aid that specifies the child for which status is being acquired
  
  Returns:      Returns one of the states indicated by MBCommPState.
 *---------------------------------------------------------------------------*/

int     MB_CommGetParentState(u16 child);


/*---------------------------------------------------------------------------*
  Name:         MB_CommSetParentStateCallback

  Description:  Sets the parent state notification callback.

  Arguments:    callback - Pointer to the callback function that causes the notification of the parent's state
  
  Returns:      None.
 *---------------------------------------------------------------------------*/

void    MB_CommSetParentStateCallback(MBCommPStateCallback callback);


/*---------------------------------------------------------------------------*
  Name:         MB_GetSegmentLength

  Description:  Acquires the length of the segment buffer that is required for the specified binary file.

  Arguments:    file - FSFile structure that points to a binary file
  
  Returns:      Returns a positive value if it can properly acquire size. Otherwise returns 0.
 *---------------------------------------------------------------------------*/

u32     MB_GetSegmentLength(FSFile *file);


/*---------------------------------------------------------------------------*
  Name:         MB_ReadSegment

  Description:  Reads the required segment data from the specified binary file.

  Arguments:    file - FSFile structure that points to a binary file
                buf  - Buffer for reading segment data
                len  - Size of buf
  
  Returns:      Returns TRUE if it properly reads segment data. Otherwise returns FALSE.
 *---------------------------------------------------------------------------*/

BOOL    MB_ReadSegment(FSFile *file, void *buf, u32 len);


/*---------------------------------------------------------------------------*
  Name:         MB_RegisterFile

  Description:  Registers the specified file in the download list.

  Arguments:    game_reg - Information on the game to be registered is stored.
                           This is a pointer to the MBGameRegistry structure that holds it.
                buf      - Pointer to the memory that holds extracted segment information
                           The MB_ReadSegment function acquires this segment information.
  
  Returns:      Returns TRUE if it properly registers a file.
                Otherwise returns FALSE.
 *---------------------------------------------------------------------------*/

BOOL    MB_RegisterFile(const MBGameRegistry *game_reg, const void *buf);


/*---------------------------------------------------------------------------*
  Name:         MB_UnregisterFile

  Description:  Deletes the specified file from the download list.

  Arguments:    game_reg - Information on the game to be deleted is stored.
                           This is a pointer to the MBGameRegistry structure that holds it.

  Returns:      Returns TRUE if it properly deletes a file.
                Otherwise returns FALSE.
 *---------------------------------------------------------------------------*/

void   *MB_UnregisterFile(const MBGameRegistry *game_reg);


/*---------------------------------------------------------------------------*
  Name:         MB_CommResponseRequest

  Description:  Specifies a response to a connect request from a child.

  Arguments:    child_aid - aid that specifies the child to send a response to
                ack       - Specifies a acknowledgement response result to a child.
                            Enumerator value of the MBCommResponseRequestType type

  Returns:      Returns TRUE if the specified child is waiting for a connect response,
                and if the specified response type is appropriate.
                Otherwise returns FALSE.
 *---------------------------------------------------------------------------*/

BOOL    MB_CommResponseRequest(u16 child_aid, MBCommResponseRequestType ack);


/*---------------------------------------------------------------------------*
  Name:         MB_CommStartSending

  Description:  Begins sending a boot image to a child that has a specified aid (and that has completed entry).

  Arguments:    child_aid - aid that specifies the child to begin sending a boot image to

  Returns:      Returns TRUE if the specified child has entered.
                otherwise returns FALSE.
 *---------------------------------------------------------------------------*/

static inline BOOL MB_CommStartSending(u16 child_aid)
{
    return MB_CommResponseRequest(child_aid, MB_COMM_RESPONSE_REQUEST_DOWNLOAD);
}


/*---------------------------------------------------------------------------*
  Name:         MB_CommStartSendingAll

  Description:  Begins sending a boot image to the children that have entered.

  Arguments:    None.

  Returns:      Returns TRUE if any entered children exist.
                otherwise returns FALSE.
 *---------------------------------------------------------------------------*/

static inline BOOL MB_CommStartSendingAll(void)
{
    u8      child, num;

    for (num = 0, child = 1; child <= WM_NUM_MAX_CHILD; child++)
    {
        if (TRUE == MB_CommStartSending(child))
        {
            num++;
        }
    }

    if (num == 0)
        return FALSE;

    return TRUE;
}


/*---------------------------------------------------------------------------*
  Name:         MB_CommIsBootable

  Description:  Determines whether a boot is possible.

  Arguments:    child_aid - AID of targeted child

  Returns:      yes - TRUE  no - FALSE
 *---------------------------------------------------------------------------*/

BOOL    MB_CommIsBootable(u16 child_aid);


/*---------------------------------------------------------------------------*
  Name:         MB_CommBootRequest

  Description:  Sends a boot request to a specified child that has completed download.

  Arguments:    child_aid - AID of targeted child

  Returns:      success - TRUE  failed - FALSE
 *---------------------------------------------------------------------------*/

static inline BOOL MB_CommBootRequest(u16 child_aid)
{
    return MB_CommResponseRequest(child_aid, MB_COMM_RESPONSE_REQUEST_BOOT);
}


/*---------------------------------------------------------------------------*
  Name:         MB_CommBootRequestAll

  Description:  Sends a boot request to children that have completed download.

  Arguments:    None.

  Returns:      success - TRUE  failed - FALSE
 *---------------------------------------------------------------------------*/

static inline BOOL MB_CommBootRequestAll(void)
{
    u8      child, num;

    for (num = 0, child = 1; child <= WM_NUM_MAX_CHILD; child++)
    {
        if (TRUE == MB_CommBootRequest(child))
        {
            num++;
        }
    }

    if (num == 0)
        return FALSE;

    return TRUE;
}


/*---------------------------------------------------------------------------*
  Name:         MB_GetGameEntryBitmap

  Description:  Obtains the AID bitmap being entered for the GameRegistry being distributed.
                Gets the AID bitmap for currently connected hosts.

  Arguments:    game_req      - Pointer to the target GameRegistry

  Returns:      AID bitmap being entered in the specified GameRegistry
                (Parent AID: 0, Child AID: 1-15)
                If a game is not being distributed, the return value is 0.
                (If a game is being distributed, parent AID:0 is always included in the entry members.)

 *---------------------------------------------------------------------------*/

u16     MB_GetGameEntryBitmap(const MBGameRegistry *game_reg);


/* ---------------------------------------------------------------------

        Multiboot library (MB) API - For booted child

   ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
  Name:         MB_GetMultiBootParam

  Description:  Acquires a pointer to the location where parent information for a multiboot child is stored.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/

static inline const MBParam *MB_GetMultiBootParam(void)
{
    return (const MBParam *)HW_WM_BOOT_BUF;
}


/*---------------------------------------------------------------------------*
  Name:         MB_IsMultiBootChild

  Description:  Determines whether a device is a multiboot child.
                If TRUE, MB_GetMultiBootParentBssDesc() is valid.

  Arguments:    None.

  Returns:      TRUE if a multiboot child.
 *---------------------------------------------------------------------------*/

static inline BOOL MB_IsMultiBootChild(void)
{
    return MB_GetMultiBootParam()->boot_type == MB_TYPE_MULTIBOOT;
}


/*---------------------------------------------------------------------------*
  Name:         MB_GetMultiBootParentBssDesc

  Description:  If a multiboot child, returns a pointer to parent information.

  Arguments:    None.

  Returns:      Returns a valid pointer if the device is a multiboot child. Otherwise returns NULL.
 *---------------------------------------------------------------------------*/

static inline const MBParentBssDesc *MB_GetMultiBootParentBssDesc(void)
{
    return MB_IsMultiBootChild()? &MB_GetMultiBootParam()->parent_bss_desc : NULL;
}

/*---------------------------------------------------------------------------*
  Name:         MB_GetMultiBootDownloadParameter

  Description:  If a multiboot child, the user-defined extended parameter specified at download
                is returned.

  Arguments:    None.

  Returns:      Returns a valid pointer if the device is a multiboot child. Otherwise returns NULL.
 *---------------------------------------------------------------------------*/

static inline const u8 *MB_GetMultiBootDownloadParameter(void)
{
    return MB_IsMultiBootChild()? (const u8 *)HW_DOWNLOAD_PARAMETER : NULL;
}

/*---------------------------------------------------------------------------*
  Name:         MB_ReadMultiBootParentBssDesc

  Description:  Based on information inherited from the multiboot parent,
                sets data in the WMBssDesc structure that is used in the WM_StartConnect function.
                and sets it as GameSpy Status for this user.

  Arguments:    p_desc            pointer to destination WMBssDesc
                                    (must be aligned 32-bytes)
                parent_max_size   max packet length of parent in MP-protocol.
                                    (must be equal to parent's WMParentParam!)
                child_max_size    max packet length of child in MP-protocol.
                                    (must be equal to parent's WMParentParam!)
                ks_flag           if use key-sharing mode, TRUE.
                                    (must be equal to parent's WMParentParam!)
                cs_flag           if use continuous mode, TRUE.
                                    (must be equal to parent's WMParentParam!)

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MB_ReadMultiBootParentBssDesc(WMBssDesc *p_desc,
                                      u16 parent_max_size, u16 child_max_size, BOOL ks_flag,
                                      BOOL cs_flag);

/*---------------------------------------------------------------------------*
  Name:         MB_SetLifeTime

  Description:  Explicitly specifies the lifetime of the MB wireless driver.
                Default value: ( 0xFFFF, 40, 0xFFFF, 40 )..

  Arguments:    tableNumber     CAM table number that sets the lifetime.
                camLifeTime     Lifetime table of CAM
                frameLifeTime   Lifetime in frames
                mpLifeTime      MP communication lifetime

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MB_SetLifeTime(u16 tableNumber, u16 camLifeTime, u16 frameLifeTime, u16 mpLifeTime);

/*---------------------------------------------------------------------------*
  Name:         MB_SetPowerSaveMode

  Description:  Sets the machine to power-save mode.
                Power-save mode is enabled by default.
                This is an option for stable operation during scenes where power consumption is not a concern,
                and as long as the operating environment is not one that guarantees
                connection to a power source, in a typical game application
                this function should not be used.

  Arguments:    enable           To enable, TRUE; To disable, FALSE.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MB_SetPowerSaveMode(BOOL enable);



/*****************************************************************************/
/* obsolete interfaces */

#define MB_StartParentEx(channel)    SDK_ERR("MB_StartParentEx() is discontinued. please use MB_StartParentFromIdle()\n")
#define MB_EndEx()    SDK_ERR("MB_EndEx() is discontinued. please use MB_EndToIdle()\n")



#ifdef __cplusplus
} /* extern "C" */
#endif


#endif // NITRO_MB_MB_H_
