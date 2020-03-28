/*---------------------------------------------------------------------------*
  Project:  NitroSDK - WM - include
  File:     wm.h

  Copyright 2003-2007 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: wm.h,v $
  Revision 1.172  2007/11/09 13:08:09  seiki_masashi
  Added a function to initialize wireless system in a state that allows only radio signal reception.

  Revision 1.171  2007/05/02 08:42:57  seiki_masashi
  Changed the WM_StartMPEx function so that the effect of its additional setting parameters is temporary.

  Revision 1.170  2007/02/20 00:28:08  kitase_hirotake
  Indented source

  Revision 1.169  2006/07/06 12:53:18  seiki_masashi
  Added platform to the WMGameInfo structure, and changed the version to 2

  Revision 1.168  2006/07/06 11:46:30  okubata_ryoma
  undo

  Revision 1.166  2006/02/20 06:47:38  seiki_masashi
  Added WM_GAMEINFO_LENGTH_MIN

  Revision 1.165  2006/02/20 02:24:45  seiki_masashi
  Removed WMGameInfo.version and added magicNumber and ver
  Changed name of WMGameInfo.gameNameCount_attribute to attribute
  Removed support for WM_GAMEINFO_TYPE_OLD

  Revision 1.164  2006/01/18 02:12:39  kitase_hirotake
  do-indent

  Revision 1.163  2005/12/01 15:06:09  seiki_masashi
  Added the maxSend/RecvDataSize structure field to the WMPortSend/RecvCallback structure.
  Added the parent/childSize field to the WMStartParent/ConnectCallback structure.

  Revision 1.162  2005/12/01 13:43:37  seiki_masashi
  Added maxFrequency and ignoreSizePrecheckMode to the WMMPParam structure.

  Revision 1.161  2005/11/25 13:04:32  seiki_masashi
  Added WMStatus.mp_parentInterval, mp_childInterval, mp_parentSize, and mp_childSize

  Revision 1.160  2005/11/25 03:01:58  seiki_masashi
  Moved the location defined for mp_ackAlarm from WMStatus to the WMSPWork structure.

  Revision 1.159  2005/11/25 02:34:26  seiki_masashi
  Moved the location defined for the VAlarm structure from WMArm7Buf to the WMSPWork structure.

  Revision 1.158  2005/11/25 00:46:31  seiki_masashi
  Moved mask to within the WMMPParam structure

  Revision 1.157  2005/11/24 13:04:17  seiki_masashi
  Added limits to parentVCount and childVCount.

  Revision 1.156  2005/11/24 12:21:23  seiki_masashi
  Changed the contents of WM_MP_PARAM_MUST_SET_BEFORE_MP.

  Revision 1.155  2005/11/24 03:58:15  seiki_masashi
  Added the WMStatus.mp_parentVCount and mp_childVCount fields.

  Revision 1.154  2005/11/24 03:02:19  seiki_masashi
  Added definitions related to the WM_SetMPParameter function

  Revision 1.153  2005/11/11 04:23:45  terui
  Fixed comments.

  Revision 1.152  2005/11/02 01:31:37  ooe
  Added APIID (WM_APIID_START_TESTRXMODE, WM_APIID_STOP_TESTRXMODE) in relation to WM_StartTestRxMode and WM_StopTestRxMode.
  
  Added statecode APIID(WM_APIID_START_TESTRXMODE,WM_APIID_STOP_TESTRXMODE).
  Added request argument structure (WMStartTestRxModeReq).
  Added callback argument structure (WMStopTestRxModeCallback).

  Revision 1.151  2005/11/01 08:59:06  seiki_masashi
  Added WMPortRecvCallback.connectedAidBitmap.
  Added WMArm9Buf.myAid, connectedAidBitmap.
  Deleted WM_INDBUF_SIZE.

  Revision 1.150  2005/10/31 07:01:45  ooe
  Added WMStartTestModeCallback.

  Revision 1.149  2005/10/28 11:21:07  seiki_masashi
  Added the constant WM_STATECODE_DISCONNECTED_FROM_MYSELF.
  Added the constant WM_STATECODE_PORT_INIT.
  Added the enumerator type WMDisconnectReason.
  Added the macAddress member to the MWStartConnectCallback structure.
  Added the aidBitmap union and reason to members of the WMPortRecvCallback structure.

  Revision 1.148  2005/09/08 02:54:59  terui
  Adjusted the order and type of members in the structures WMScanExParam and WMStartScanExReq.

  Revision 1.147  2005/09/08 00:42:07  terui
  Added the constant WM_SCANTYPE_*_CUSTOM

  Revision 1.146  2005/09/08 00:38:06  terui
  Added the ssidMatchLength member to the WMStartScanExReq structure.

  Revision 1.145  2005/09/08 00:36:18  terui
  Revised code so that the improved WMScanExParam structure could be controlled using compile switches.

  Revision 1.144  2005/09/08 00:21:31  terui
  Added the ssidMatchLength member to the WMScanExParam structure.

  Revision 1.143  2005/09/01 01:15:29  ooe
  Added wlStatus to the WMStartConnectCallback structure.

  Revision 1.142  2005/07/29 04:00:48  seiki_masashi
  Minor fixes.

  Revision 1.141  2005/07/27 07:46:41  seiki_masashi
  Added WM_STATECODE_INFORMATION

  Revision 1.140  2005/07/27 06:53:28  ooe
  Added WM_APIID_SET_PS_MODE.

  Revision 1.139  2005/06/08 08:40:29  seiki_masashi
  Added WMStatus.mp_limitCount

  Revision 1.138  2005/06/07 05:44:19  seiki_masashi
  Reduced special treatment related to Key Sharing

  Revision 1.137  2005/03/18 01:39:22  terui
  Added WM_NUM_MAX_AP_AID constant

  Revision 1.136  2005/03/17 05:08:48  ooe
  Defined maximum number of otherElement (WM_SCAN_OTHER_ELEMENT_MAX).
  Added otherElementCount member to WMBssDesc structure.
  Added the WMBssDescWMOtherElements structure.

  Revision 1.135  2005/03/08 06:44:18  terui
  Added pwrMgtMode member to WMStatus structure.

  Revision 1.134  2005/03/04 08:51:19  seiki_masashi
  Changed so can also reference even length in the size field of WMPortSendCallback.

  Revision 1.133  2005/03/03 14:44:37  seiki_masashi
  Changed levels in send queue from 64 to 32.
  Added restBitmap, etc to the WMPortSendQueueData structure.
  Added WM_DISABLE_KEYSHARING switch
  Added resume related mp_resumeFlag and others to WMStatus
  Added destBitmap and others to the WMPortSendCallback structure

  Revision 1.132  2005/02/28 05:26:35  yosizaki
  do-indent.

  Revision 1.131  2005/02/24 14:25:29  seiki_masashi
  Added constant WMi_DISCONNECT_REASON_*

  Revision 1.130  2005/02/14 13:39:42  seiki_masashi
  Added WM_STATECODE_UNKNOWN

  Revision 1.129  2005/02/08 06:45:05  ooe
  Revisions due to WM_StartScanEx specification change

  Revision 1.128  2005/02/07 06:52:57  terui
  Added beaconIndicateFlag member to WMStatus structure.
  Changed the position of the wepKeyId member in the WMStatus structure.

  Revision 1.127  2005/02/03 11:41:25  ooe
  Revisions due to addition of WM_SetWEPKeyEx

  Revision 1.126  2005/01/26 05:31:58  takano_makoto
  WMArm9Buf contained 32 bytes of useless padding. Deleted.

  Revision 1.125  2005/01/26 01:36:15  seiki_masashi
  Established WMARM9Buf.scanOnlyFlag

  Revision 1.124  2005/01/18 13:00:26  seiki_masashi
  Added WM_PACKED_PACKET_MAX

  Revision 1.123  2005/01/17 01:07:32  ooe
  Added AUTH mode definition for argument in WM_StartConnectEx.
  Added constant for specifying MaData transfer size.
  Added powerSave and authMode to API argument structure WMStartConnectReq.

  Revision 1.122  2005/01/11 07:54:58  takano_makoto
  Fixed copyright header.

  Revision 1.121  2005/01/07 11:04:47  terui
  Expanded the buffer size for ARM7 and secured buffer for internally issuing requests asynchronously.

  Revision 1.120  2004/12/27 09:06:21  ooe
  Deleted WM_WEPMODE_232BIT that did not actually exist.

  Revision 1.119  2004/12/27 05:30:41  terui
  Added WM_API_REQUEST_ACCEPTED definition.

  Revision 1.118  2004/11/10 13:02:51  takano_makoto
  Revised the include file

  Revision 1.117  2004/11/09 02:45:23  seiki_masashi
  Implemented timeout on NULL response
  Changed so that VAlarm process waits do not concurrently accumulate in the wireless execution queue.

  Revision 1.116  2004/11/08 04:16:46  terui
  Added the linkLevel member to the MWStartScanExCallback structure.

  Revision 1.115  2004/11/04 12:14:28  terui
  Added a channel member to WMStartScanExCallback.

  Revision 1.114  2004/11/02 09:12:56  seiki_masashi
  Made changes to use the macro constant WM_DS_DATA_SIZE_252 for the switch.

  Revision 1.113  2004/11/02 07:28:42  terui
  Comments revised.

  Revision 1.112  2004/10/30 04:31:02  yasu
  comment out '#undef WM_ENABLE_TESTMODE'

  Revision 1.111  2004/10/27 04:29:57  ooe
  Changed the callback argument of StartScanEx.

  Revision 1.110  2004/10/26 08:23:39  ooe
  Added WM_StartScanEx. Defined WM_SIZE_SCAN_EX_BUF.

  Revision 1.109  2004/10/26 00:53:57  terui
  Newly added the WMDisconnectCallback structure.

  Revision 1.108  2004/10/22 09:31:58  seiki_masashi
  Added the variable APIID for Resume to use

  Revision 1.107  2004/10/22 01:54:42  seiki_masashi
  Expanded the maximum size for data sharing from 252 bytes to 508 bytes.

  Revision 1.106  2004/10/05 09:45:29  terui
  Standardized MAC addresses as type u8 arrays.

  Revision 1.105  2004/10/04 13:40:25  terui
  Standardized game group IDs as type u32.

  Revision 1.104  2004/10/04 11:43:54  terui
  Updated the WM_SIZE_MP_DATA_MAX definition

  Revision 1.103  2004/10/04 00:51:47  terui
  Changed WM_SIZE_MP_DATA_MAX: 510 -> 508. (514-header(2)-footer(4))

  Revision 1.102  2004/10/03 07:52:54  ooe
  Merged with ipl_branch. Added support for ignoreFatalError flag and Flash error.

  Revision 1.101  2004/10/01 13:22:26  seiki_masashi
  Changed the calculation process of LinkLevel

  Revision 1.100  2004/10/01 04:11:23  terui
  Newly added the WM_ENABLE_TESTMODE switch. Default setting is undef.
  Added a switch for switching the feature that precalculates the wireless communication permitted channel

  Revision 1.99  2004/09/24 08:22:31  seiki_masashi
  Fixed comment

  Revision 1.98  2004/09/24 04:52:16  seiki_masashi
  Added WM_STATECODE_FIFO_ERROR
  Added reason to WMIndCallback

  Revision 1.97  2004/09/24 01:22:42  ooe
  Added errBitmap to WMMpRecvHeader (WL-2.05.00 and higher)

  Revision 1.96  2004/09/23 12:17:05  ooe
  Added AutoDisconnect.
  Also added the WMStatus member "curr.tgid" required for AutoDisconnect.

  Revision 1.95  2004/09/23 09:40:39  seiki_masashi
  Added a state field to WMDataSharingInfo

  Revision 1.94  2004/09/20 10:30:39  ooe
  Added WM_APIID_SET_BEACON_PERIOD.

  Revision 1.93  2004/09/17 06:36:40  seiki_masashi
  Added ssid and myAid fields to WMPortRecvCallback.

  Revision 1.92  2004/09/15 07:33:50  seiki_masashi
  Added WMStatus.mp_bufferEmptyFlag.

  Revision 1.91  2004/09/15 06:38:31  seiki_masashi
  Added WMStatus.mp_ping*.

  Revision 1.90  2004/09/15 05:40:27  ooe
  Added gameInfo and gameInfoLength to WMBeaconRecvIndCallback's members.
  

  Revision 1.89  2004/09/13 04:22:06  seiki_masashi
  Minor fixes.

  Revision 1.88  2004/09/13 04:09:16  seiki_masashi
  Added WM_SetMPFrequency.

  Revision 1.87  2004/09/10 12:04:37  seiki_masashi
  Changed it so the number of bytes sent for key sharing is concealed in the library.

  Revision 1.86  2004/09/09 12:39:45  seiki_masashi
  Added WM_HEADER_SIZE.

  Revision 1.85  2004/09/09 07:24:11  seiki_masashi
  Added WM_SetMPDataToPortEx.

  Revision 1.84  2004/09/09 02:00:57  terui
  Deleted unused Indication buffer.
  Changed part of APIID name.
  Added WM_STATE_READY (before WM_Enable) in internal state.

  Revision 1.83  2004/09/08 04:25:54  terui
  Changed WMApiid definitions. Added IDs for Enable, Disable, Idlize, and Stop.
  Changed padding size in WMArm9Buf.

  Revision 1.82  2004/09/03 04:36:41  seiki_masashi
  Added WM_ERRCODE_SEND_FAILED.
  Added WMStatus.mp_readyBitmap.

  Revision 1.81  2004/09/02 08:39:28  terui
  Added WM_SIZE_MP_DATA_MAX definition.

  Revision 1.80  2004/09/01 07:00:36  terui
  Added WM_STATE_MAX in WMState enumerated type.

  Revision 1.79  2004/08/31 09:26:07  seiki_masashi
  Added WMStatus.mp_setDataFlag, mp_sentDataFlag, and WM_ERRCODE_NO_DATA.

  Revision 1.78  2004/08/30 08:37:39  seiki_masashi
  Added WMStatus.mp_dataSettingFlag and mp_isPolledFlag.
  Added WM_ERRCODE_INVALID_POLLBITMAP.

  Revision 1.77  2004/08/30 01:58:59  seiki_masashi
  Consolidated WM_STATECODE_CHILD_CONNECTED in WM_STATECODE_CONNECTED.

  Revision 1.76  2004/08/30 00:53:51  terui
  Add definition about LinkLevel

  Revision 1.75  2004/08/27 08:17:18  terui
  Change pass to version_wl.h

  Revision 1.74  2004/08/27 06:46:33  seiki_masashi
  Added WMStatus.mp_newFrameFlag, mp_fixFreqMode and mp_defaultRetryCount.
  Added WMSendQueueData.retryCount.

  Revision 1.73  2004/08/26 09:42:35  ooe
  Added argument to BeaconRecv callback.

  Revision 1.72  2004/08/26 07:02:41  terui
  Include NITRO_WL_VERSION.

  Revision 1.71  2004/08/25 08:18:24  seiki_masashi
  Added status->mp_minPollBmpMode and mp_singlePacketMode

  Revision 1.70  2004/08/25 05:51:25  terui
  Rename parentRssi to lastRssi.

  Revision 1.69  2004/08/24 13:19:32  terui
  Added parentRssi member to WMStatus.

  Revision 1.68  2004/08/23 04:39:43  ooe
  Changed WM_StartConnect() specifications.

  Revision 1.67  2004/08/21 11:08:41  ooe
  Support for WL-1.71.00

  Revision 1.66  2004/08/21 06:56:01  ooe
  Created WMStartConnectReq type.

  Revision 1.65  2004/08/21 06:14:52  ooe
  Added ssid and ssidLength to WMStartParentCallback arguments.

  Revision 1.64  2004/08/20 04:29:17  terui
  Added WM_ERRCODE_OVER_MAX_ENTRY to error code.

  Revision 1.63  2004/08/19 16:24:19  miya
  switch GAMEINFO_TYPE

  Revision 1.62  2004/08/19 14:53:04  miya
  bug fix

  Revision 1.61  2004/08/19 11:14:14  miya
  add GAMEINFO_VERSION

  Revision 1.60  2004/08/19 06:37:34  seiki_masashi
  Fixed DataSharingInfo structure for Key Sharing so that it matches 32-Byte align.

  Revision 1.59  2004/08/19 02:41:36  terui
  Added APIID form automatic disconnection by Entry availability.
  Added error code for when child is denied entry.

  Revision 1.58  2004/08/18 13:12:01  yosiokat
  Defined WM_GAMEINFO_TYPE_OLD.

  Revision 1.57  2004/08/18 09:01:38  miya
  modified WMGameInfo format

  Revision 1.56  2004/08/18 06:34:34  terui
  Added APIID for WM_SetEntry.
  Added allowedChannel member to WMStatus structure (replaced some padding).

  Revision 1.55  2004/08/18 00:24:15  seiki_masashi
  Moved some constants from wm_private.h.

  Revision 1.54  2004/08/17 12:50:45  seiki_masashi
  Changed send buffer so as to use the one specified by user program.
  Added status->maxReceiveSize

  Revision 1.53  2004/08/16 06:50:50  ooe
  Added WMBeaconRecvIndCallback.

  Revision 1.52  2004/08/12 14:28:11  seiki_masashi
  Added WM_ERRCODE_FRAME_GAP etc.

  Revision 1.51  2004/08/11 04:26:45  seiki_masashi
  Added doubleMode field to WMDataSharingInfo.

  Revision 1.50  2004/08/11 00:19:42  terui
  Added reservation to port.

  Revision 1.49  2004/08/10 09:10:57  terui
  Extracted ARM9 dedicated function group definitions to wm_api.h.

  Revision 1.48  2004/08/10 04:12:13  seiki_masashi
  Added a macAddress field to WMPortRecvCallback for notifying connect and disconnect.

  Revision 1.47  2004/08/09 10:19:47  seiki_masashi
  Implemented exclusion control so that senqQueue will not be reset until sending is finished.

  Revision 1.46  2004/08/07 14:15:44  seiki_masashi
  Added a start process function for continuous WMSP_SendMaMP, SendMaKeyData.

  Revision 1.45  2004/08/07 10:19:46  seiki_masashi
  Save seq number of DataSet to WMDataSharingInfo.

  Revision 1.44  2004/08/07 08:45:49  seiki_masashi
  32-byte aligned DataSharing's send data.

  Revision 1.43  2004/08/07 07:04:40  seiki_masashi
  Changed WM_StepDataSharing argument.

  Revision 1.42  2004/08/07 04:06:44  seiki_masashi
  Added receivedBitmap field to WMDataSet.

  Revision 1.41  2004/08/07 02:55:56  terui
  Moved callback exclusion control flag to shared region.

  Revision 1.40  2004/08/07 01:22:47  seiki_masashi
  Added WMStatus.sendQueueMutex.

  Revision 1.39  2004/08/07 00:23:10  seiki_masashi
  Added dataSharing.

  Revision 1.38  2004/08/06 05:10:44  seiki_masashi
  Small fix

  Revision 1.37  2004/08/05 11:59:16  ooe
  Support for more GetWirelessCounter items.

  Revision 1.36  2004/08/05 10:03:13  seiki_masashi
  Changed so that SetMPDataToPort() does not receive tmptt.

  Revision 1.35  2004/08/05 08:26:14  seiki_masashi
  Changes due to implementation of sendQueue.

  Revision 1.34  2004/08/04 06:57:03  seiki_masashi
  Added portSeqNo to WMStatus.

  Revision 1.33  2004/08/04 06:48:04  seiki_masashi
  Preparation for implementing send queue.
  Changed WM_STATUS_BUF_SIZE from 512 to 2048

  Revision 1.32  2004/08/04 06:21:33  ooe
  Added InitWirelessCounter and GetWirelessCounter.

  Revision 1.31  2004/08/04 02:29:39  seiki_masashi
  Added WMPortSendQueue structure definition.

  Revision 1.30  2004/08/04 01:44:30  seiki_masashi
  Preparation for introducing port.

  Revision 1.29  2004/08/03 12:22:28  ooe
  Support for WL TestMode command changes.

  Revision 1.28  2004/08/03 00:52:58  yosiokat
  Revised WM_SIZE_SYSTEM_GAMEINFO to "40". (stopgap fix)

  Revision 1.27  2004/08/02 06:29:15  terui
  Standardized: WMbssDesc -> WMBssDesc
  Standardized: WMstatus -> WMStatus

  Revision 1.26  2004/08/02 05:42:46  ooe
  Small fix

  Revision 1.25  2004/08/02 05:34:49  ooe
  Added member for MPACK to the WMstartMPCallback structure.

  Revision 1.24  2004/08/02 02:52:32  terui
  Standardized structure names based on naming conventions.

  Revision 1.23  2004/07/31 09:03:41  sato_masaki
  To allocate the userGameInfo member in the WMgameInfo structure by 4-byte alignment

  Revision 1.22  2004/07/30 05:20:57  ooe
  Additional changes related to MeasureChannel.

  Revision 1.21  2004/07/29 12:11:00  ooe
  Added WM_MeasureChannel.

  Revision 1.20  2004/07/29 07:54:19  ikedae
  Added reasonCode for when disconnected.

  Revision 1.19  2004/07/29 07:38:46  miya
  modified callback table size

  Revision 1.18  2004/07/29 06:50:08  miya
  modified WMarm9Buf size

  Revision 1.17  2004/07/29 05:43:00  miya
  modified callback table size

  Revision 1.16  2004/07/29 04:21:38  miya
  added SetLifeTime function

  Revision 1.15  2004/07/28 07:35:20  terui
  Removed WM_EndConnect function definition.

  Revision 1.14  2004/07/28 04:23:18  miya
  added functions about ggid & tgid

  Revision 1.13  2004/07/28 02:54:16  terui
  Revised structure padding.
  Added type names to enum.
  Changed WM_APIID_* to enum type.
  Moved WMState definition from wm_private.h.

  Revision 1.12  2004/07/27 07:32:24  yasu
  Added #pragma  warn_padding off

  Revision 1.11  2004/07/27 07:17:41  yasu
  Fixed alignment 32 on WMpparam

  Revision 1.10  2004/07/20 01:24:34  terui
  Added STATECODE for indicate.
  Added callback vector storage variable for indicate.
  Added maximum connected children member to parent information.
  Removed scan_continue, scanning_ch members.
  Removed WM_getIndBuf function.
  Changed WM_SetGameInfo function specifications.
  Standardized functions to const if they take an argument with a pointer as src.

  Revision 1.9  2004/07/14 09:42:50  ooe
  Revisions due to StartScan argument changes

  Revision 1.8  2004/07/11 02:59:30  ooe
  Added WM_SetBeaconIndication()

  Revision 1.7  2004/07/10 12:52:39  miya
  Added beacon system

  Revision 1.6  2004/07/10 12:45:08  terui
  Modified comments.

  Revision 1.5  2004/07/10 09:30:30  ooe
  Added #define WM_APIID_VALARM_MP 23

  Revision 1.4  2004/07/08 09:50:35  terui
  Changes due to beginning of WM7 revision

  Revision 1.17  2004/07/06 08:04:27  Ooe
  Support for WL-1.56.00

  Revision 1.16  2004/07/06 05:49:05  Ooe
  Returned FIFO buffer size to 256 Bytes

  Revision 1.15  2004/07/06 02:08:24  Ooe
  Added WM_ATTR_FLAG_CS definition

  Revision 1.14  2004/07/06 01:51:28  Ooe
  Changed FIFO buffer size

  Revision 1.13  2004/07/05 13:01:47  Ooe
  Added ( ) to SYSTEM_BUF_SIZE

  Revision 1.12  2004/07/03 07:28:43  Ooe
  Changed definitions of size, etc

  Revision 1.11  2004/07/02 04:51:46  Miya
  Revised cache control size

  Revision 1.10  2004/06/29 06:50:27  Ooe
  Revised BssDesc structure

  Revision 1.9  2004/06/29 06:41:43  Miya
  Made the hard coding of data size to macros as much as possible

  Revision 1.8  2004/06/25 06:18:27  Ooe
  Added argument (pollbmp) to WM_SetMPData()

  Revision 1.7  2004/06/25 02:15:27  Ooe
  Fixed the DMA-related bug that was exposed by implementation of WM_SetGameInfo()

  Revision 1.6  2004/06/24 10:02:44  Ooe
  Added WM_SetGameInfo()

  Revision 1.5  2004/06/21 06:39:42  Ooe
  (none)

  Revision 1.4  2004/06/19 05:56:58  Miya
  modified header file reference

  Revision 1.3  2004/06/19 04:03:08  miya
  ver. up Marionea-1.48.00

  Revision 1.2  2004/06/02 04:18:40  miya
  (none)

  Revision 1.1  2004/05/26 08:47:17  terui
  Additions accompanying incorporation of wireless communication

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#ifndef NITRO_WM_COMMON_WM_H_
#define NITRO_WM_COMMON_WM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro_wl/common/version_wl.h"


/*---------------------------------------------------------------------------*
    Constant definitions
 *---------------------------------------------------------------------------*/

#undef WM_GAMEINFO_TYPE_OLD            // Removed support for old version of WMGameInfo

// Switch that sets Data Sharing maximum size to 252 bytes. This makes the WMDataSharingInfo structure slimmer.
//#define WM_DS_DATA_SIZE_252

// TEST mode enable switch
//#define WM_ENABLE_TESTMODE

// Compile switch that precalculates the usable channels.
#if ( SDK_VERSION_WL >= 15600 )
#ifdef  SDK_TEG
#undef  WM_PRECALC_ALLOWEDCHANNEL
#else
#define WM_PRECALC_ALLOWEDCHANNEL
#endif
#else
#undef  WM_PRECALC_ALLOWEDCHANNEL
#endif

#define WM_SSID_MASK_CUSTOMIZE  1


// WM API related ===========================================================================

// ID for each API
typedef enum WMApiid
{
    WM_APIID_INITIALIZE = 0,           //  0 : WM_Initialize()
    WM_APIID_RESET,                    //  1 : WM_Reset()
    WM_APIID_END,                      //  2 : WM_End()

    WM_APIID_ENABLE,                   //  3 : WM_Enable()
    WM_APIID_DISABLE,                  //  4 : WM_Disable()
    WM_APIID_POWER_ON,                 //  5 : WM_PowerOn()
    WM_APIID_POWER_OFF,                //  6 : WM_PowerOff()

    WM_APIID_SET_P_PARAM,              //  7 : WM_SetParentParameter()
    WM_APIID_START_PARENT,             //  8 : WM_StartParent()
    WM_APIID_END_PARENT,               //  9 : WM_EndParent()
    WM_APIID_START_SCAN,               // 10 : WM_StartScan()
    WM_APIID_END_SCAN,                 // 11 : WM_EndScan()
    WM_APIID_START_CONNECT,            // 12 : WM_StartConnect()
    WM_APIID_DISCONNECT,               // 13 : WM_Disconnect()
    WM_APIID_START_MP,                 // 14 : WM_StartMP()
    WM_APIID_SET_MP_DATA,              // 15 : WM_SetMPData()
    WM_APIID_END_MP,                   // 16 : WM_EndMP()
    WM_APIID_START_DCF,                // 17 : WM_StartDCF()
    WM_APIID_SET_DCF_DATA,             // 18 : WM_SetDCFData()
    WM_APIID_END_DCF,                  // 19 : WM_EndDCF()
    WM_APIID_SET_WEPKEY,               // 20 : WM_SetWEPKey()
    WM_APIID_START_KS,                 // 21 : WM_StartKeySharing() Kept for the downward compatibility
    WM_APIID_END_KS,                   // 22 : WM_EndKeySharing()   Kept for the downward compatibility
    WM_APIID_GET_KEYSET,               // 23 : WM_GetKeySet()
    WM_APIID_SET_GAMEINFO,             // 24 : WM_SetGameInfo()
    WM_APIID_SET_BEACON_IND,           // 25 : WM_SetBeaconIndication()
    WM_APIID_START_TESTMODE,           // 26 : WM_StartTestMode()
    WM_APIID_STOP_TESTMODE,            // 27 : WM_StopTestMode()
    WM_APIID_VALARM_MP,                // 28 : For starting up MP from VAlarm in ARM7 (special)
    WM_APIID_SET_LIFETIME,             // 29 : WM_SetLifeTime()
    WM_APIID_MEASURE_CHANNEL,          // 30 : WM_MeasureChannel()
    WM_APIID_INIT_W_COUNTER,           // 31 : WM_InitWirelessCounter()
    WM_APIID_GET_W_COUNTER,            // 32 : WM_GetWirelessCounter()
    WM_APIID_SET_ENTRY,                // 33 : WM_SetEntry()
    WM_APIID_AUTO_DEAUTH,              // 34 : For starting up automatic disconnection from indicate in ARM7. (special)
    WM_APIID_SET_MP_PARAMETER,         // 35 : WM_SetMPParameter()
    WM_APIID_SET_BEACON_PERIOD,        // 36 : WM_SetBeaconPeriod()
    WM_APIID_AUTO_DISCONNECT,          // 37 : For starting up automatic disconnection from indicate in ARM7. (special)
    WM_APIID_START_SCAN_EX,            // 38 : WM_StartScanEx()
    WM_APIID_SET_WEPKEY_EX,            // 39 : WM_SetWEPKeyEx()
    WM_APIID_SET_PS_MODE,              // 40 : WM_SetPowerSaveMode()
    WM_APIID_START_TESTRXMODE,         // 41 : WM_StartTestRxMode()
    WM_APIID_STOP_TESTRXMODE,          // 42 : WM_StopTestRxMode()

    WM_APIID_KICK_MP_PARENT,           // 43 : For starting up MP (ARM7 internal use)
    WM_APIID_KICK_MP_CHILD,            // 44 : For starting up MP (ARM7 internal use)
    WM_APIID_KICK_MP_RESUME,           // 45 : For starting up MP (ARM7 internal use)

    WM_APIID_ASYNC_KIND_MAX,           // 46 : Type of asynchronous process

    WM_APIID_INDICATION = 128,         // 128 : For indication callback
    WM_APIID_PORT_SEND,                // 129 : Notification to port of data being sent
    WM_APIID_PORT_RECV,                // 130 : Notification to port of data being received
    WM_APIID_READ_STATUS,              // 131 : WM_ReadStatus()

    WM_APIID_UNKNOWN = 255             // 255 : Value returned from ARM7 at unknown command number
}
WMApiid;

// for backward compatibility
//#define WM_APIID_SET_MP_FREQ    WM_APIID_SET_MP_PARAMETER

// Flag for completion of receiving the API requests on ARM7 side.
#define WM_API_REQUEST_ACCEPTED 0x8000

// WEP mode
#define WM_WEPMODE_NO           0
#define WM_WEPMODE_40BIT        1
#define WM_WEPMODE_104BIT       2
#define WM_WEPMODE_128BIT       3

// AUTH mode (used by WM_StartConnectEx)
#define WM_AUTHMODE_OPEN_SYSTEM 0
#define WM_AUTHMODE_SHARED_KEY  1

// ScanType
#define WM_SCANTYPE_ACTIVE      0
#define WM_SCANTYPE_PASSIVE     1

#if WM_SSID_MASK_CUSTOMIZE
#define WM_SCANTYPE_ACTIVE_CUSTOM   2
#define WM_SCANTYPE_PASSIVE_CUSTOM  3
#endif

// Maximum number of children that can connect in one BSS
#define WM_NUM_MAX_CHILD        15     // The max. value possible for the AssociationID provided by the NITRO parent
#define WM_NUM_MAX_AP_AID       2007   // The max. value possible for the AssociationID provided by the wireless router

// port number
#define WM_NUM_OF_PORT          16     // Number of ports
#define WM_NUM_OF_SEQ_PORT      8      // Number of ports that perform sequential processing
typedef enum WMPort
{
    // Group of ports that do not perform sequential control
    WM_PORT_RAWDATA = 0,               // Port for downward compatibility
    WM_PORT_BT = 1,                    // Port for block transfer
    WM_PORT_RESERVE_02 = 2,            // Reserved
    WM_PORT_RESERVE_03 = 3,            // Reserved

    // Group of ports that perform sequential control
    WM_PORT_RESERVE_10 = 8,            // Reserved
    WM_PORT_RESERVE_11 = 9,            // Reserved
    WM_PORT_RESERVE_12 = 10,           // Reserved
    WM_PORT_RESERVE_13 = 11            // Reserved
}
WMPort;

// Send queue related
#define WM_SEND_QUEUE_NUM       32     // Total 32 level queue list
#define WM_SEND_QUEUE_END       ((u16)0xffff)   // Value that indicates tail
#define WM_PRIORITY_LEVEL       4      // 4 priority levels
typedef enum WMPriorityLevel
{
    WM_PRIORITY_URGENT = 0,
    WM_PRIORITY_HIGH,
    WM_PRIORITY_NORMAL,
    WM_PRIORITY_LOW
}
WMPriorityLevel;

// Default V Count value to start the MP send operation on the ARM7 side.
#define WM_VALARM_COUNT_CHILD_MP  240  // Child MP operation
#define WM_VALARM_COUNT_PARENT_MP 260  // Parent MP operation
#define WM_VALARM_COUNT_RANGE_TOP    220        // Highest limit on possible settings for parentVCount and childVCount (220 - 262, 0 - 190)
#define WM_VALARM_COUNT_RANGE_BOTTOM 190        // Lowest limit on possible settings for parentVCount and childVCount.

// Send interval
#define WM_MP_FREQ_CONT         16     // Send frequency that becomes continuous send
#define WM_MP_COUNT_LIMIT       256    // Upper limit of the counter for the number of sends remaining.
#define WM_DEFAULT_MP_FREQ_LIMIT 6     // Default upper limit for MP frequency
#define WM_DEFAULT_MP_PARENT_INTERVAL 1000      // Default parent MP interval (in microseconds)
#define WM_DEFAULT_MP_CHILD_INTERVAL  0 // Default child MP interval (in microseconds)

// Size of each type of data (bytes)
#define WM_SIZE_BSSID           6
#define WM_SIZE_SSID            32

#define WM_SIZE_GAMEINFO        128    // Maximum size

#define WM_SIZE_SCAN_EX_BUF     1024   // Buffer size for StartScanEx

#define WM_GAMEINFO_LENGTH_MIN  16     // Minimum size of valid GameInfo
#define WM_GAMEINFO_MAGIC_NUMBER 0x0001 // DS GameInfo magic number for identification purposes
#define WM_GAMEINFO_VERSION_NUMBER 1   // GameInfo version number
#define WM_GAMEINFO_PLATFORM_ID_NITRO       0   // Parent device is a DS
#define WM_GAMEINFO_PLATFORM_ID_REVOLUTION  8   // Parent device is a Wii
#define WM_SIZE_SYSTEM_GAMEINFO 16     // size up to userGameInfoLength
#define WM_SIZE_USER_GAMEINFO   112    // Maximum user area size for GameInfo

#define WM_SIZE_SCAN_PARAM      32

#define WM_PARENT_PARAM_SIZE    64
#define WM_SIZE_USERNAME        8
#define WM_SIZE_GAMENAME        16
#define WM_SIZE_GGID            4

#define WM_SIZE_WL_VERSION      8
#define WM_SIZE_BBP_VERSION     4
#define WM_SIZE_MACADDR         6
#define WM_SIZE_WEPKEY          80

#define WM_SIZE_CHILD_SSID      24

#if ( SDK_VERSION_WL >= 21100 )
#define WM_SIZE_MP_DATA_MAX     512
#else
#define WM_SIZE_MP_DATA_MAX     508
#endif

#define WM_SIZE_MADATA_HEADER   44

// number of bytes needed between packets when parent puts multiple packets in one MP communication
#define WM_SIZE_MP_PARENT_PADDING   (WM_HEADER_SIZE + WM_HEADER_PARENT_MAX_SIZE)
// number of bytes needed between packets when child puts multiple packets in one MP communication
#define WM_SIZE_MP_CHILD_PADDING    (WM_HEADER_SIZE + WM_HEADER_CHILD_MAX_SIZE)

#define WM_SIZE_DS_PARENT_HEADER    4
#define WM_SIZE_KS_PARENT_DATA  (2*16+WM_SIZE_DS_PARENT_HEADER)
#define WM_SIZE_KS_CHILD_DATA   2

// Attribute flags

#define WM_ATTR_ENTRY_SHIFT     0
#define WM_ATTR_MB_SHIFT        1
#define WM_ATTR_KS_SHIFT        2
#define WM_ATTR_CS_SHIFT        3

#define WM_ATTR_FLAG_ENTRY      (1 << WM_ATTR_ENTRY_SHIFT)
#define WM_ATTR_FLAG_MB         (1 << WM_ATTR_MB_SHIFT)
#define WM_ATTR_FLAG_KS         (1 << WM_ATTR_KS_SHIFT)
#define WM_ATTR_FLAG_CS         (1 << WM_ATTR_CS_SHIFT)

// For callback exclusive control
#define WM_EXCEPTION_CB_MASK    0x0001

// wmHeader
#define WM_HEADER_SIZE          2      // number of bytes of shared parent/child wmHeader

//#define WM_HEADER_MP        0x0001
#define WM_HEADER_KS        0x4000
#define WM_HEADER_VSYNC     0x8000

// packetHeader
#define WM_HEADER_PARENT_MAX_SIZE   4  // maximum number of bytes that can be added as header (excluding the 2 bytes of wmHeader)
                                        // At present there are cases where Sequence Number and Destination Bitmap are added.

#define WM_HEADER_CHILD_MAX_SIZE    2  // maximum number of bytes that can be added as header (excluding the 2 bytes of wmHeader)
                                        // At present there are cases where Sequence Number is added.

#define WM_HEADER_PORT_MASK     0x0f00
#define WM_HEADER_PORT_SHIFT    8
#define WM_HEADER_SEQ_FLAG      0x0800
#define WM_HEADER_DEST_BITMAP   0x1000
#define WM_HEADER_LENGTH_MASK   0x00ff
#define WM_HEADER_LENGTH_SCALE  2

#define WM_SEQ_PORT_FLAG        0x0008
#define WM_SEQ_PORT_MASK        0x0007

// packetHeader Seq No Field (second byte)
#define WM_HEADER_SEQ_RETRY     0x8000
#define WM_HEADER_SEQ_NUM_MASK  0x7fff

// Maximum number of packets that can be packed into one envelope. (>= WM_SIZE_MP_DATA_MAX/WM_SIZE_MP_PARENT_PADDING + 1)
#define WM_PACKED_PACKET_MAX    128


// API result codes
typedef enum WMErrCode
{
    WM_ERRCODE_SUCCESS = 0,
    WM_ERRCODE_FAILED = 1,
    WM_ERRCODE_OPERATING = 2,
    WM_ERRCODE_ILLEGAL_STATE = 3,
    WM_ERRCODE_WM_DISABLE = 4,
    WM_ERRCODE_NO_KEYSET = 5,
    WM_ERRCODE_NO_DATASET = 5,         // Same value as NO_KEYSET
    WM_ERRCODE_INVALID_PARAM = 6,
    WM_ERRCODE_NO_CHILD = 7,
    WM_ERRCODE_FIFO_ERROR = 8,
    WM_ERRCODE_TIMEOUT = 9,
    WM_ERRCODE_SEND_QUEUE_FULL = 10,
    WM_ERRCODE_NO_ENTRY = 11,
    WM_ERRCODE_OVER_MAX_ENTRY = 12,
    WM_ERRCODE_INVALID_POLLBITMAP = 13,
    WM_ERRCODE_NO_DATA = 14,
    WM_ERRCODE_SEND_FAILED = 15,

    WM_ERRCODE_DCF_TEST,               // For debugging
    WM_ERRCODE_WL_INVALID_PARAM,       // For debugging (can delete)
    WM_ERRCODE_WL_LENGTH_ERR,          // For debugging (can delete)

    WM_ERRCODE_FLASH_ERROR,            // WL flash parameter error (freezes because it is fatal)
    WM_ERRCODE_MAX
}
WMErrCode;

// State codes returned by the API's callback
typedef enum WMStateCode
{
    WM_STATECODE_PARENT_START = 0,     // For StartParent. Started parent operation
    WM_STATECODE_BEACON_SENT = 2,      // For StartParent. Beacon send completed

    WM_STATECODE_SCAN_START = 3,       // For StartScan. Started Scan operation
    WM_STATECODE_PARENT_NOT_FOUND = 4, // For StartScan. Cannot find parent
    WM_STATECODE_PARENT_FOUND = 5,     // For StartScan. Found parent

    WM_STATECODE_CONNECT_START = 6,    // For StartConnect. Started connect process
    WM_STATECODE_BEACON_LOST = 8,      // For StartConnect. Lost parent's beacon

    WM_STATECODE_CONNECTED = 7,        // For StartParent and StartConnect, connection complete for port.
    WM_STATECODE_CHILD_CONNECTED = 7,  // same value as WM_STATECODE_CONNECTED
    WM_STATECODE_DISCONNECTED = 9,     // Notification of disconnection for StartParent and StartConnect port.
    WM_STATECODE_DISCONNECTED_FROM_MYSELF = 26, // Notification of disconnection from self for StartParent and StartConnect port.

    WM_STATECODE_MP_START = 10,        // For StartMP. Started MP communication mode.
    WM_STATECODE_MPEND_IND = 11,       // For StartMP. Parent MP sequence complete (receive)
    WM_STATECODE_MP_IND = 12,          // For StartMP. Child MP receive
    WM_STATECODE_MPACK_IND = 13,       // For StartMP. Child MPACK receive

    WM_STATECODE_DCF_START = 14,       // For StartDCF. Started DCF communication mode.
    WM_STATECODE_DCF_IND = 15,         // For StartDCF. Received DCF data

    WM_STATECODE_BEACON_RECV = 16,     // Indicate beacon received
    WM_STATECODE_DISASSOCIATE = 17,    // Indicate disconnection
    WM_STATECODE_REASSOCIATE = 18,     // Indicate reconnection
    WM_STATECODE_AUTHENTICATE = 19,    // Indicate confirmed authentication

    WM_STATECODE_PORT_INIT = 25,       // Initialize port
    WM_STATECODE_PORT_SEND = 20,       // Send data to port
    WM_STATECODE_PORT_RECV = 21,       // Receive data from port

    WM_STATECODE_FIFO_ERROR = 22,      // FIFO error occurrence notification in ARM7
    WM_STATECODE_INFORMATION = 23,     // Notification of information
    WM_STATECODE_UNKNOWN = 24,         // Unspecified notification

    WM_STATECODE_MAX = 27
}
WMStateCode;

// WM state codes
typedef enum WMState
{
    WM_STATE_READY = 0,                // READY state (before Init, LED normal lighting state)
    WM_STATE_STOP,                     // STOP state (Before Initialize, LED blinking state)
    WM_STATE_IDLE,                     // IDLE state (After Initialize. After Reset, etc)
    WM_STATE_CLASS1,                   // CLASS1 state
    WM_STATE_TESTMODE,                 // TESTMODE (for applying)
    WM_STATE_SCAN,                     // During StartScan
    WM_STATE_CONNECT,                  // During StartConnect
    WM_STATE_PARENT,                   // During StartParent
    WM_STATE_CHILD,                    // Child after connect complete
    WM_STATE_MP_PARENT,                // Parent after StartMP
    WM_STATE_MP_CHILD,                 // Child after StartMP
    WM_STATE_DCF_CHILD,                // Child after StartDCF
    WM_STATE_TESTMODE_RX,              // TESTMODE_RX
    WM_STATE_MAX
}
WMState;

// link strength
typedef enum WMLinkLevel
{
    WM_LINK_LEVEL_0 = 0,
    WM_LINK_LEVEL_1,
    WM_LINK_LEVEL_2,
    WM_LINK_LEVEL_3,
    WM_LINK_LEVEL_MAX
}
WMLinkLevel;

// Data Sharing's internal state
typedef enum WMDataSharingState
{
    WM_DS_STATE_READY = 0,             // Before WM_StartDataSharing
    WM_DS_STATE_START,                 // During WM_StepDataSharing
    WM_DS_STATE_PAUSING,               // While changing to the pause state
    WM_DS_STATE_PAUSED,                // Immediately after WM_StartDataSharing or during pause
    WM_DS_STATE_RETRY_SEND,            // Resend required because of SEND_QUEUE_FULL
    WM_DS_STATE_ERROR                  // Error generated
}
WMDataSharingState;

// reason code for disconnect
typedef enum WMDisconnectReason
{
    // reason value for disconnect due to external cause.
    WM_DISCONNECT_REASON_RESERVED = 0, // Reserved
    WM_DISCONNECT_REASON_UNSPECIFIED = 1,       // Unspecifiable error
    WM_DISCONNECT_REASON_PREV_AUTH_INVALID = 2, // The last authentication is no longer valid.
    WM_DISCONNECT_REASON_DEAUTH_LEAVING = 3,    // Deauthenticate because unit has left the BSS.
    WM_DISCONNECT_REASON_INACTIVE = 4, // Released connection due to inactivity.
    WM_DISCONNECT_REASON_UNABLE_HANDLE = 5,     // Released connection due to lack of sufficient resources for AP.
    WM_DISCONNECT_REASON_RX_CLASS2_FROM_NONAUTH_STA = 6,        // A Class2 frame was received from an unauthenticated STA.
    WM_DISCONNECT_REASON_RX_CLASS3_FROM_NONASSOC_STA = 7,       // A Class3 frame was received from an unconnected STA.
    WM_DISCONNECT_REASON_DISASSOC_LEAVING = 8,  // Released association because unit has left the BSS.
    WM_DISCONNECT_REASON_ASSOC_STA_NOTAUTHED = 9,       // An STA which has requested connection has not yet undergone authentication
    // reason values specific to local DS communications
    WM_DISCONNECT_REASON_NO_ENTRY = 19, // DS parent is not currently accepting entries.
    // A reason value related to auto disconnect from inside the library
    WM_DISCONNECT_REASON_MP_LIFETIME = 0x8001,  // MP communication lifetime has run out.
    WM_DISCONNECT_REASON_TGID_CHANGED = 0x8002, // TGID changed during receive beacon
    WM_DISCONNECT_REASON_FATAL_ERROR = 0x8003,  // An unrecoverable error has occurred in the library.
    // Reason values relating to disconnect due to library.
    WM_DISCONNECT_REASON_FROM_MYSELF = 0xf001   // Self-initiated disconnect using the WM API has been performed.
}
WMDisconnectReason;

// Notifications
typedef enum WMInfoCode
{
    WM_INFOCODE_NONE = 0,
    WM_INFOCODE_FATAL_ERROR            // Notification regarding occurrence of Fatal Error
}
WMInfoCode;

// Constant for the WM_SetMPParameter function's mask
#define WM_MP_PARAM_MIN_FREQUENCY              0x0001
#define WM_MP_PARAM_FREQUENCY                  0x0002
#define WM_MP_PARAM_MAX_FREQUENCY              0x0004
#define WM_MP_PARAM_PARENT_SIZE                0x0008
#define WM_MP_PARAM_CHILD_SIZE                 0x0010
#define WM_MP_PARAM_PARENT_INTERVAL            0x0020
#define WM_MP_PARAM_CHILD_INTERVAL             0x0040
#define WM_MP_PARAM_PARENT_VCOUNT              0x0080
#define WM_MP_PARAM_CHILD_VCOUNT               0x0100
#define WM_MP_PARAM_DEFAULT_RETRY_COUNT        0x0200
#define WM_MP_PARAM_MIN_POLL_BMP_MODE          0x0400
#define WM_MP_PARAM_SINGLE_PACKET_MODE         0x0800
#define WM_MP_PARAM_IGNORE_FATAL_ERROR_MODE    0x1000
#define WM_MP_PARAM_IGNORE_SIZE_PRECHECK_MODE  0x2000

// List of parameters that cannot be set during MP communications
#define WM_MP_PARAM_MUST_SET_BEFORE_MP      (WM_MP_PARAM_MIN_POLL_BMP_MODE|WM_MP_PARAM_SINGLE_PACKET_MODE|WM_MP_PARAM_IGNORE_SIZE_PRECHECK_MODE)

// Constants for WMMPTmpParam.mask
#define WM_MP_TMP_PARAM_MIN_FREQUENCY              0x0001
#define WM_MP_TMP_PARAM_FREQUENCY                  0x0002
#define WM_MP_TMP_PARAM_MAX_FREQUENCY              0x0004
#define WM_MP_TMP_PARAM_DEFAULT_RETRY_COUNT        0x0200
#define WM_MP_TMP_PARAM_MIN_POLL_BMP_MODE          0x0400
#define WM_MP_TMP_PARAM_SINGLE_PACKET_MODE         0x0800
#define WM_MP_TMP_PARAM_IGNORE_FATAL_ERROR_MODE    0x1000

// Maximum parameter value
#define WM_MP_PARAM_INTERVAL_MAX 10000 // The value specified for interval must be 10000us or lower.

// miscFlags constants
#define WM_MISC_FLAG_LISTEN_ONLY               0x0001
#define WM_MISC_FLAG_NO_BLINK                  0x0002

// WM API callback type
typedef void (*WMcallbackFunc) (void *arg);     // WM API callback type
typedef void (*WMCallbackFunc) (void *arg);     // WM API callback type

// Buffer size =======================================================================

//  --------------------
// | WM9 variable       | 512
// |--------------------|
// | WM7 variable       | 256 + 512
// |--------------------|
// | WM status          | 2048
// |--------------------|
// | FIFO buf (9 -> 7)  | 256
// |--------------------|
// | FIFO buf (9 <- 7)  | 256
//  ---------------------

// Size of the buffer used with WM -------------------

#define WM_ARM9WM_BUF_SIZE      512    // Size of the WM variable area on ARM9 side
#define WM_ARM7WM_BUF_SIZE      ( 256 + 512 )   // Size of the WM variable area on ARM7 side
#define WM_STATUS_BUF_SIZE      2048   // Size of the WM status area
#define WM_FIFO_BUF_SIZE        256    // Size of the FIFO command buffer between ARM9 and ARM7

// Size of the buffer allocated by the user -------------
//   Size of all buffers used by WM system 512 + 256 + 512 + 2048 + 256 + 256 = 0xf00 (Notice that this is FIFO_BIF * 2)
#define WM_SYSTEM_BUF_SIZE      (WM_ARM9WM_BUF_SIZE + WM_ARM7WM_BUF_SIZE + WM_STATUS_BUF_SIZE + WM_FIFO_BUF_SIZE + WM_FIFO_BUF_SIZE)
#define WM_BSS_DESC_SIZE        192    // Size of the buffer for storing parent information passed by WM_StartScan()

#define WM_DCF_MAX_SIZE         1508   // Maximum size that can be received with DCF
#define WM_KEYSET_SIZE          36     // Size of KeySet
#define WM_KEYDATA_SIZE         2      // Size of KeyData

#define WM_DS_HEADER_SIZE       4

#ifdef WM_DS_DATA_SIZE_252             // When it is OK to set 252 for WM_DS_DATA_SIZE
#define WM_DS_DATA_SIZE         252
#else  // When WM_DS_DATA_SIZE == 508 (default)
#define WM_DS_DATA_SIZE         508    // Maximum data size of one WMDataSet (512-4)
                                       // WM_DS_DATA_SIZE+WM_DS_HEADER_SIZE needs to be multiples of 32
#endif

#define WM_DS_DATASET_NUM       4      // How many WMDataSet to be kept in WMDataSetBuf (fixed value)
#define WM_DS_INFO_SIZE         (sizeof(WMDataSharingInfo))     // DataSharing buffer size

#define WM_SCAN_EX_PARENT_MAX   16     // Maximum number of parent devices that can be found with one ScanEx
#define WM_SCAN_OTHER_ELEMENT_MAX 16   // Maximum number of otherElement that can be acknowledged

/*---------------------------------------------------------------------------*
    Structure definitions
 *---------------------------------------------------------------------------*/

// Buffer structure =======================================================================

// Data set structure
typedef struct WMDataSet
{
//    u16 seqNum;                 // data set sequential number
    u16     aidBitmap;
    u16     receivedBitmap;            // Bit map of receive status
    u16     data[WM_DS_DATA_SIZE / sizeof(u16)];        // Shared data

}
WMDataSet;

// DataSharing information structure
typedef struct WMDataSharingInfo
{
    WMDataSet ds[WM_DS_DATASET_NUM];
    u16     seqNum[WM_DS_DATASET_NUM]; // Sequential Number
    u16     writeIndex;                // Next Index to write
    u16     sendIndex;                 // Index currently being sent
    u16     readIndex;                 // Next Index to read
    u16     aidBitmap;                 // bitmap of data sharing group (including self)
    u16     dataLength;                // Amount of shared data per unit
    u16     stationNumber;             // Number of units sharing data (number of bits set to 1 in aidBitmap)
    u16     dataSetLength;             // dataLength * stationNumber
    u16     port;                      // Port being used (number 8 or above)
    u16     doubleMode;                // In mode for alternately sending/receiving each frame?
    u16     currentSeqNum;             // SeqNum of the DataSet read most recently
    u16     state;                     // Current DataSharing state (WMDataSharingState)
    u16     reserved[1];               // for 32Byte Alignment
}
WMDataSharingInfo;

// Key set structure
typedef struct WMKeySet
{
    u16     seqNum;                    // Key set's sequential number
    u16     rsv;
    u16     key[16];                   // Key data

}
WMKeySet, WMkeySet;

// Ring buffer for saving key set
typedef WMDataSharingInfo WMKeySetBuf, WMkeySetBuf;

//---------------------------------------
// Parent/Child shared MP port send queue structure
typedef struct
{
    u16     next;
    u16     port;
    u16     destBitmap;
    u16     restBitmap;
    u16     sentBitmap;
    u16     sendingBitmap;
    u16     padding;
    u16     size;
    u16     seqNo;
    u16     retryCount;
    const u16 *data;
    WMCallbackFunc callback;
    void   *arg;
}
WMPortSendQueueData;

typedef struct
{
    u16     head;
    u16     tail;
}
WMPortSendQueue;

//---------------------------------------
// Child MP receive buffer structure
typedef struct WMMpRecvBuf
{
    u16     rsv1[3];
    u16     length;

    u16     rsv2[1];
    u16     ackTimeStamp;
    u16     timeStamp;
    u16     rate_rssi;
    u16     rsv3[2];

    u16     rsv4[2];
    u8      destAdrs[6];
    u8      srcAdrs[6];
    u16     rsv5[3];
    u16     seqCtrl;

    u16     txop;
    u16     bitmap;
    u16     wmHeader;
    u16     data[2];

}
WMMpRecvBuf, WMmpRecvBuf;

//---------------------------------------
// Parent MP receive buffer structure
typedef struct WMMpRecvData
{
    u16     length;
    u16     rate_rssi;
    u16     aid;
    u16     noResponse;
    u16     wmHeader;
    u16     cdata[1];

}
WMMpRecvData, WMmpRecvData;

typedef struct WMMpRecvHeader
{
    u16     bitmap;
#if SDK_VERSION_WL >= 20500
    u16     errBitmap;
#endif
    u16     count;
    u16     length;
    u16     txCount;
    WMMpRecvData data[1];

}
WMMpRecvHeader, WMmpRecvHeader;

//---------------------------------------
// Child DCF receive buffer structure
typedef struct WMDcfRecvBuf
{
    u16     frameID;
    u16     rsv1[2];
    u16     length;

    u16     rsv2[3];
    u16     rate_rssi;
    u16     rsv3[4];
    u8      destAdrs[6];
    u8      srcAdrs[6];
    u16     rsv4[4];

    u16     data[2];

}
WMDcfRecvBuf, WMdcfRecvBuf;

//---------------------------------------
// WM parent parameter structure
typedef struct WMParentParam
{
    u16    *userGameInfo;              // Pointer to data to set in user area
    u16     userGameInfoLength;        // Length of user area
    u16     padding;

    u32     ggid;
    u16     tgid;                      // Temporary GameID(generated each time a user becomes a parent)
    u16     entryFlag;                 // 1: Connect possible, 0: Connect not possible
    u16     maxEntry;                  // Number of child devices that can connect
    u16     multiBootFlag;             // 1: Multiboot possible, 0: Multiboot not possible
    u16     KS_Flag;                   // 1: KeySharing OK, 0: No KeySharing
    u16     CS_Flag;                   // 1: Continuous send, 0: Send in each frame
    u16     beaconPeriod;              // Beacon interval (ms)
    u16     rsv1[WM_SIZE_USERNAME / sizeof(u16)];       //
    u16     rsv2[WM_SIZE_GAMENAME / sizeof(u16)];       //
    u16     channel;                   // Channel
    u16     parentMaxSize;             // Maximum parent send size
    u16     childMaxSize;              // Maximum child send size

    u16     rsv[4];                    // For 32-byte alignment

}
WMParentParam, WMpparam;

//---------------------------------------
// WM GameInfo Structure

typedef struct WMGameInfo
{
    u16     magicNumber;               // == 0x0001
    u8      ver;                       // GameInfo Version 1
    u8      platform;                  // DS: 0, Wii: 8
    u32     ggid;
    u16     tgid;
    u8      userGameInfoLength;        // Length of user area
    union
    {
        // (CS_Flag):1, (KS_Flag):1, multibootFlag:1, entryFlag:1
        u8      gameNameCount_attribute;        // Old name for compatibility purposes
        u8      attribute;
    };
    u16     parentMaxSize;             //Maximum parent send size
    u16     childMaxSize;              //Maximum child send size
    union
    {
        u16     userGameInfo[WM_SIZE_USER_GAMEINFO / sizeof(u16)];      // User region (Maximum: 112 bytes (provisional))
        struct
        {
            u16     userName[WM_SIZE_USERNAME / sizeof(u16)];   // WM_SIZE_USERNAME -> 8
            u16     gameName[WM_SIZE_GAMENAME / sizeof(u16)];   // WM_SIZE_GAMENAME -> 16
            u16     padd1[44];         // pad -> 88 
        }
        old_type;                      // Total: 112 bytes
    };
}
WMGameInfo, WMgameInfo;

//---------------------------------------
// BSSDescription. Parent information structure (Acquired with Scan. Used for specifications in Connect)
#if SDK_VERSION_WL < 17100
typedef struct WMBssDesc
{
    u16     length;                    // 2
    u16     rssi;                      // 4
    u8      bssid[WM_SIZE_BSSID];      // 10
    u16     ssidLength;                // 12
    u8      ssid[WM_SIZE_SSID];        // 44
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
    u16     gameInfoLength;            // 62
    WMGameInfo gameInfo;               // 190
    u16     rsv;                       // 192

}
WMBssDesc, WMbssDesc;
#else
typedef struct WMBssDesc
{
    u16     length;                    // 2
    u16     rssi;                      // 4
    u8      bssid[WM_SIZE_BSSID];      // 10
    u16     ssidLength;                // 12
    u8      ssid[WM_SIZE_SSID];        // 44
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
    u16     gameInfoLength;            // 62
    u16     otherElementCount;         // 64
    WMGameInfo gameInfo;               // 192

}
WMBssDesc, WMbssDesc;
#endif

//---------------------------------------
// Extended element structure within WM beacon
typedef struct WMOtherElements
{
    u8      count;
    u8      rsv[3];
    struct
    {
        u8      id;
        u8      length;
        u8      rsv[2];
        u8     *body;
    }
    element[WM_SCAN_OTHER_ELEMENT_MAX];
}
WMOtherElements;

//---------------------------------------
// WM Scan parameter Structure
typedef struct WMScanParam
{
    WMBssDesc *scanBuf;                // Buffer that stores parent information
    u16     channel;                   // Channel which carries out Scan
    u16     maxChannelTime;            // Maximum Scan time
    u8      bssid[WM_SIZE_BSSID];      // MacAddress of Scan target parent (if 0xff, all parents are targets)
    u16     rsv[9];

}
WMScanParam, WMscanParam;

//---------------------------------------
// WM ScanEx parameter structure
typedef struct WMScanExParam
{
    WMBssDesc *scanBuf;                // Buffer that stores parent information
    u16     scanBufSize;               // Size of scanBuf
    u16     channelList;               // List of channels to do Scan for (Can specify multiple. Same format as the return value for WM_GetAllowedChannel)
    u16     maxChannelTime;            // Maximum Scan time
    u8      bssid[WM_SIZE_BSSID];      // MacAddress of Scan target parent (if 0xff, all parents are targets)
    u16     scanType;                  // Normally WM_SCANTYPE_PASSIVE. WM_SCANTYPE_ACTIVE during ActiveScan
    u16     ssidLength;                // SSID length of target parent (if 0, all parents are targets)
    u8      ssid[WM_SIZE_SSID];        // SSID of parent that is target of Scan
#if WM_SSID_MASK_CUSTOMIZE
    u16     ssidMatchLength;
    u16     rsv2[7];
#else
    u16     rsv2[8];
#endif

}
WMScanExParam, WMscanExParam;

//---------------------------------------
// WM SetMPParameter parameter structure
typedef struct WMMPParam
{
    u32     mask;                      // Which of the fields below is valid is set by bits.

    u16     minFrequency;              // Number of MP cycles with one picture frame (minimum value)(un-implemented)
    u16     frequency;                 // Number of MP cycles in one picture frame
    u16     maxFrequency;              // Number of MP cycles in one picture frame (upper limit value)
    u16     parentSize;                // Current parent send size
    u16     childSize;                 // Current child send size
    u16     parentInterval;            // If performed continuously, the parent MP communications interval within one frame (in microseconds)
    u16     childInterval;             // If performed continuously, the interval a child takes to prepare MP communications within one frame (in microseconds)
    u16     parentVCount;              // The starting V Count for parent processing when in frame synchronous communications
    u16     childVCount;               // The starting V Count for child processing when in frame synchronous communications
    u16     defaultRetryCount;         // Number of communications default retries in the Raw communications port
    u8      minPollBmpMode;            // mode that minimizes to fit the send target of the packet that sends PollBitmap
    u8      singlePacketMode;          // mode that only sends 1 packet in 1 MP
    u8      ignoreFatalErrorMode;      // Mode that ignores Fatal Error
    u8      ignoreSizePrecheckMode;    // Mode that ignores the preliminary check of the send / receive size when starting communications
}
WMMPParam;

//---------------------------------------
// Temporary parameter structure for WM StartMP
typedef struct WMMPTmpParam
{
    u32     mask;                      // Which of the fields below is valid is set by bits.

    u16     minFrequency;              // Number of MP cycles with one picture frame (minimum value)(un-implemented)
    u16     frequency;                 // Number of MP cycles in one picture frame
    u16     maxFrequency;              // Number of MP cycles in one picture frame (upper limit value)
    u16     defaultRetryCount;         // Number of communications default retries in the Raw communications port
    u8      minPollBmpMode;            // mode that minimizes to fit the send target of the packet that sends PollBitmap
    u8      singlePacketMode;          // mode that only sends 1 packet in 1 MP
    u8      ignoreFatalErrorMode;      // Mode that ignores Fatal Error
    u8      reserved[1];
}
WMMPTmpParam;

//---------------------------------------
// WM status buffer structure (ARM7 will rewrite; ARM9 can only read)
typedef struct WMStatus
{
    // State information (4Byte)
    u16     state;                     // WM state information
    u16     BusyApiid;                 // Busy APIID

    // Flag (32Byte) 36
    BOOL    apiBusy;                   // API executing flag (Flag prohibiting issuing API, attributable to FIFO)
    BOOL    scan_continue;             // Scan continue flag (As of 2004/07/19, not used)
    BOOL    mp_flag;                   // Flag that MP is in execution
    BOOL    dcf_flag;                  // Flag that DCF is in execution
    BOOL    ks_flag;                   // Flag that KeySharing is in execution
    BOOL    dcf_sendFlag;              // 'Waiting for DCF send' flag
    BOOL    VSyncFlag;                 // 'VBlank synch OK' flag

    // Version information (16Byte) 52
    u8      wlVersion[WM_SIZE_WL_VERSION];      // WL version
    u16     macVersion;                // MAC version
    u16     rfVersion;                 // RF version
    u16     bbpVersion[WM_SIZE_BBP_VERSION / sizeof(u16)];      // BBP version

    // MP related (106Byte) 158
    u16     mp_parentSize;             // send size in one MP communication transmission by the parent
    u16     mp_childSize;              // send size in one MP communication transmission by the child
    u16     mp_parentMaxSize;          // maximum send size in one MP communication transmission by the parent
    u16     mp_childMaxSize;           // maximum send size in one MP communication transmission by the child
    u16     mp_sendSize;               // maximum send size with current connection
    u16     mp_recvSize;               // maximum receive size with current connection
    u16     mp_maxSendSize;            // maximum send size with current connection (parentMaxSize+4 or childMaxSize+2)
    u16     mp_maxRecvSize;            // maximum receive size with current connection (childMaxSize+2 or parentMaxSize+4)
    u16     mp_parentVCount;           // MP operation start VCount on the parent side
    u16     mp_childVCount;            // MP operation start VCount on the child side
    u16     mp_parentInterval;         // MP communications interval used by the parent (us)
    u16     mp_childInterval;          // MP communications interval used by the child (us)

    OSTick  mp_parentIntervalTick;     // MP communications interval used by the parent (tick)
    OSTick  mp_childIntervalTick;      // MP communications interval used by the child (tick)

    u16     mp_minFreq;                // Number of MP cycles in one picture frame (minimum)(un-implemented)
    u16     mp_freq;                   // Number of MP cycles in one picture frame (standard value)
    u16     mp_maxFreq;                // Number of MP cycles in one picture frame (maximum value)

    u16     mp_vsyncOrderedFlag;       // Whether the next MP was instructed by the parent to synchronize to vsync
    u16     mp_vsyncFlag;              // Whether the next MP is performed by synchronizing to vsync
    s16     mp_count;                  // How many more MP cycles for the current picture frame?
    s16     mp_limitCount;             // How many more times it is okay to MP in the current picture frame, including resends
    u16     mp_resumeFlag;             // Flag that Resume is in execution
    u16     mp_prevPollBitmap;         // PollBitmap in MP immediately before
    u16     mp_prevWmHeader;           // wmHeader in MP immediately before
    u16     mp_prevTxop;               // txop in immediately previous MP
    u16     mp_prevDataLength;         // dataLength in immediately previous MP
    u16     mp_recvBufSel;             // 'MP receive buffer selection' flag
    u16     mp_recvBufSize;            // Size of MP Receive buffer
    WMMpRecvBuf *mp_recvBuf[2];        // Pointer to the MP receive buffer
    u32    *mp_sendBuf;                // Pointer to the MP send buffer
    u16     mp_sendBufSize;            // Size of the MP send buffer

    u16     mp_ackTime;                // MPACK estimated time of arrival
    u16     mp_waitAckFlag;            // Waiting for MPACK

    u16     mp_readyBitmap;            // Bitmap of children with MP preparations complete (for parent use)

    u16     mp_newFrameFlag;           // flag that becomes TRUE when a new picture frame comes
    u16     mp_setDataFlag;            // flag that reply data set is done (for child use)
    u16     mp_sentDataFlag;           // flag that reply data is sent (for child use)
    u16     mp_bufferEmptyFlag;        // 'reply data buffer is empty' flag (for child use)
    u16     mp_isPolledFlag;           // Was self polled in the last MP? (for child)

    u16     mp_minPollBmpMode;         // mode that minimizes to fit the send target of the packet that sends PollBitmap
    u16     mp_singlePacketMode;       // mode that only sends 1 packet in 1 MP
    u8      reserved_c[2];
    u16     mp_defaultRetryCount;      // default number of retries for communication on a port that does not do Seq control
    u16     mp_ignoreFatalErrorMode;   // Whether to ignore FatalError
    u16     mp_ignoreSizePrecheckMode; // Invalidates the preliminary check of the send / receive size when starting communications

    u16     mp_pingFlag;               // flag that is enabled with the same timing as ping
    u16     mp_pingCounter;            // counter of number of frames remaining until ping

    // DCF related (26Byte) 184
    u8      dcf_destAdr[WM_SIZE_MACADDR];       // DCF send destination MAC address
    u16    *dcf_sendData;              // DCF send data pointer
    u16     dcf_sendSize;              // DCF send data size
    u16     dcf_recvBufSel;            // DCF receive buffer select flag
    WMDcfRecvBuf *dcf_recvBuf[2];      // DCF receive buffer pointer
    u16     dcf_recvBufSize;           // DCF receive buffer size

    u16     curr_tgid;                 // TGID of the parent that is currently connected (used with BeaconRecv.Ind)

    // RSSI related (4Byte) 206
    u16     linkLevel;
    u16     minRssi;
    u16     rssiCounter;

    // Additional parameters
    u16     beaconIndicateFlag;        // Beacon-related notifications enable flag
    u16     wepKeyId;                  // WEP key ID (0-3)
    u16     pwrMgtMode;                // Power management mode
    u32     miscFlags;                 // miscellaneous flags

    u16     VSyncBitmap;               // Bitmap of children after V-Blank synchronization
    u16     valarm_queuedFlag;         // V-Alarm processes have accumulated in the run queue.

    // V-Blank sync related (14Byte) 218
    u32     v_tsf;                     // For V-Blank sync. V_TSF value
    u32     v_tsf_bak;                 // For V-Blank sync. Last acquired V_TSF value
    u32     v_remain;                  // For V-Blank sync. Remaining adjustment
    u16     valarm_counter;            // For V-Alarm interrupt occurrence counter

    // Read wait flag (2Byte) 220
//    u16             indbuf_read_wait;       // Indication buffer read wait flag

    u8      reserved_e[2];

    // Status of the self (8Byte) 228
    u8      MacAddress[WM_SIZE_MACADDR];
    u16     mode;                      // Parent: WL_CMDLABEL_MODE_PARENT, Child: WL_CMDLABEL_MODE_CHILD

    // Information to be used when it is parent (64 + 90 + 2 = 156Byte) 384
    WMParentParam pparam;              // Parent parameter
    u8      childMacAddress[WM_NUM_MAX_CHILD][WM_SIZE_MACADDR];
    u16     child_bitmap;              // Connection status of children (used as poll bitmap)

    // Information to be used when it is a child (14Byte) 398
    WMBssDesc *pInfoBuf;               // Pointer to the buffer that is used for storing scanned parent information. (given as an argument ARM9API)
    u16     aid;                       // Current AID
    u8      parentMacAddress[WM_SIZE_MACADDR];
    u16     scan_channel;              // Channel that is currently doing Scan

    u8      reserved_f[4];

    // WEP related (86Byte) 488
    u16     wepMode;                   // WEP mode (how many bits is WEP?)
    BOOL    wep_flag;                  // Indicates whether other party is requesting WEP
    u16     wepKey[WM_SIZE_WEPKEY / sizeof(u16)];       // WEP key (20Byte * 4)
    /* Placed wepKeyId about 40 lines above this. (2005/02/07 terui) */

    // Other (4Byte) 492
    u16     rate;                      // Utilization rate(WL_CMDLABEL_RATE_AUTO, 1M, 2M)
    u16     preamble;                  // Long:0, Short:1

    // Various parameters (4Byte) 496
    u16     tmptt;
    u16     retryLimit;

    // Usable channels (2Byte) 498
    u16     enableChannel;

    // Permitted channels (2Byte) 500
    u16     allowedChannel;

    // port related (1316+256+20+4+256 Bytes) 1816+256+20+4+256
    u16     portSeqNo[WM_NUM_MAX_CHILD + 1][WM_NUM_OF_SEQ_PORT];        // 16*8*2=256Byte

    WMPortSendQueueData sendQueueData[WM_SEND_QUEUE_NUM];       // 32*32=1024Byte
    WMPortSendQueue sendQueueFreeList; // 4Byte
    WMPortSendQueue sendQueue[WM_PRIORITY_LEVEL];       // 16Byte
    WMPortSendQueue readyQueue[WM_PRIORITY_LEVEL];      // 16Byte
    OSMutex sendQueueMutex;            // 20 byte
    BOOL    sendQueueInUse;            // MP send wait flag

    // Null Ack timeout ( 128 + 8 Byte )
    OSTick  mp_lastRecvTick[1 + WM_NUM_MAX_CHILD];
    OSTick  mp_lifeTimeTick;

    // MP settings values that are currently valid
    // In order to prevent the additional parameters specified in the WM_StartMPEx function from being persistent, the setting values here are kept twice: as the persistent values set in the WM_SetMPParameter function, and as the temporary values set in the WM_StartMPEx function.
    // 
    // 
    // 
    u16     mp_current_minFreq;                // Number of MP cycles in one picture frame (minimum)(un-implemented)
    u16     mp_current_freq;                   // Number of MP cycles in one picture frame (standard value)
    u16     mp_current_maxFreq;                // Number of MP cycles in one picture frame (maximum value)
    u16     mp_current_minPollBmpMode;         // mode that minimizes to fit the send target of the packet that sends PollBitmap
    u16     mp_current_singlePacketMode;       // mode that only sends 1 packet in 1 MP
    u16     mp_current_defaultRetryCount;      // default number of retries for communication on a port that does not do Seq control
    u16     mp_current_ignoreFatalErrorMode;   // Whether to ignore FatalError
    u8      reserved_g[2];
}
WMStatus, WMstatus;

//---------------------------------------
// Buffer structure for variable area on WM ARM7 side
typedef struct WMArm7Buf
{
    WMStatus *status;                  // WM status buffer
//    u32         *indbuf;        // Indication buffer pointer
    u8      reserved_a[4];
    u32    *fifo7to9;                  // Buffer pointer for FIFO(ARM7->9)
//    BOOL        *fifoFlag;      // ARM7->ARM9 FIFO send enable flag
    u8      reserved_b[4];

    WMBssDesc connectPInfo;            // Connection target parent information (190 bytes)

    // Buffer for requests issued from inside of ARM7.
    u32     requestBuf[512 / sizeof(u32)];

}
WMArm7Buf, WMarm7Buf;

//---------------------------------------
// Number of CallbackTable elements
#define WM_NUM_OF_CALLBACK      ( WM_APIID_ASYNC_KIND_MAX - 2 )
// Buffer structure for variable area on WM ARM9 side
typedef struct WMArm9Buf
{
    // Various pointers (20 bytes)
    WMArm7Buf *WM7;                    // ARM7 side WM variable area ( no access from ARM9)
    WMStatus *status;                  // WM status buffer (read only from ARM9)
    u32    *indbuf;                    // Indication buffer
    u32    *fifo9to7;                  // Buffer for FIFO(ARM9->7)
    u32    *fifo7to9;                  // Buffer for FIFO(ARM7->9)

    // Other (4 bytes)
    u16     dmaNo;                     // DMA number that WM uses
    u16     scanOnlyFlag;              // Scan only mode flag

    // Callback related (172 bytes)
    WMCallbackFunc CallbackTable[WM_NUM_OF_CALLBACK];   // Callback table (42*4 = 168 bytes)
    WMCallbackFunc indCallback;

    // port related (134 bytes)
    WMCallbackFunc portCallbackTable[WM_NUM_OF_PORT];   // 16*4 = 64 bytes
    void   *portCallbackArgument[WM_NUM_OF_PORT];       // 16*4 = 64 bytes
    u32     connectedAidBitmap;        // List of connection targets (allocate as u32 type since bitwise operations are used frequently)
    u16     myAid;                     // Current AID

    /* Total of 20+4+172+134 bytes */

    u8      reserved1[WM_ARM9WM_BUF_SIZE -
                      (20 + 4 + 4 * WM_NUM_OF_CALLBACK + 4 + (4 + 4) * WM_NUM_OF_PORT + 6)];

}
WMArm9Buf, WMarm9Buf;

//==========================================================================================

// API arguments
typedef struct WMStartScanReq
{
    u16     apiid;
    u16     channel;
    WMBssDesc *scanBuf;
    u16     maxChannelTime;
    u8      bssid[WM_SIZE_BSSID];

}
WMStartScanReq, WMstartScanReq;

typedef struct WMStartScanExReq
{
    u16     apiid;
    u16     channelList;
    WMBssDesc *scanBuf;
    u16     scanBufSize;
    u16     maxChannelTime;
    u8      bssid[WM_SIZE_BSSID];
    u16     scanType;
    u16     ssidLength;
    u8      ssid[WM_SIZE_SSID];
#if WM_SSID_MASK_CUSTOMIZE
    u16     ssidMatchLength;
    u16     rsv[2];
#else
    u16     rsv[3];
#endif
}
WMStartScanExReq, WMstartScanExReq;

typedef struct WMStartConnectReq
{
    u16     apiid;
    u16     reserved;
    WMBssDesc *pInfo;
    u8      ssid[WM_SIZE_CHILD_SSID];
    BOOL    powerSave;
    u16     reserved2;
    u16     authMode;

}
WMStartConnectReq, WMstartConnectReq;

typedef struct WMMeasureChannelReq
{
    u16     apiid;
    u16     ccaMode;
    u16     edThreshold;
    u16     channel;
    u16     measureTime;

}
WMMeasureChannelReq, WMmeasureChannelReq;

typedef struct WMSetMPParameterReq
{
    u16     apiid;
    u16     reserved;

    WMMPParam param;
}
WMSetMPParameterReq;

typedef struct WMStartMPReq
{
    u16     apiid;
    u16     rsv1;
    u32    *recvBuf;
    u32     recvBufSize;
    u32    *sendBuf;
    u32     sendBufSize;

    WMMPParam param; // unused
    WMMPTmpParam tmpParam;
}
WMStartMPReq;

typedef struct WMStartTestModeReq
{
    u16     apiid;
    u16     control;
    u16     signal;
    u16     rate;
    u16     channel;
}
WMStartTestModeReq, WMstartTestModeReq;

typedef struct WMStartTestRxModeReq
{
    u16     apiid;
    u16     channel;
}
WMStartTestRxModeReq, WMstartTestRxModeReq;


//==========================================================================================

// Normal callback arguments
typedef struct WMCallback
{
    u16     apiid;
    u16     errcode;
    u16     wlCmdID;
    u16     wlResult;

}
WMCallback;

// WM_StartParent() callback arguments
typedef struct WMStartParentCallback
{
    u16     apiid;
    u16     errcode;
    u16     wlCmdID;
    u16     wlResult;
    u16     state;                     // PARENT_START, BEACON_SENT, CHILD_CONNECTED, DISCONNECTED
    u8      macAddress[WM_SIZE_MACADDR];        // MAC address of each child that was connected
    u16     aid;
    u16     reason;                    // reasonCode at disconnecting
    u8      ssid[WM_SIZE_CHILD_SSID];  // SSID (child information)
    u16     parentSize;
    u16     childSize;

}
WMStartParentCallback, WMstartParentCallback;

// WM_StartScan() callback arguments
typedef struct WMStartScanCallback
{
    u16     apiid;
    u16     errcode;
    u16     wlCmdID;
    u16     wlResult;
    u16     state;                     // SCAN_START, PARENT_NOT_FOUND, PARENT_FOUND
    u8      macAddress[WM_SIZE_MACADDR];        // MAC address of the parent that was found
    u16     channel;
    u16     linkLevel;
    u16     ssidLength;
    u16     ssid[WM_SIZE_SSID / sizeof(u16)];
    u16     gameInfoLength;
    WMGameInfo gameInfo;

}
WMStartScanCallback, WMstartScanCallback;

// Argument of WM_StartScanEx() callback
typedef struct WMStartScanExCallback
{
    u16     apiid;
    u16     errcode;
    u16     wlCmdID;
    u16     wlResult;
    u16     state;                     // SCAN_START, PARENT_NOT_FOUND, PARENT_FOUND
    u16     channelList;               // Scanned channel list, regardless of whether found or not.
    u8      reserved[2];               // padding
    u16     bssDescCount;              // Number of parents that were found
    WMBssDesc *bssDesc[WM_SCAN_EX_PARENT_MAX];  // Beginning address of the parent information
    u16     linkLevel[WM_SCAN_EX_PARENT_MAX];   // Reception signal strength

}
WMStartScanExCallback, WMstartScanExCallback;

// Argument of WM_StartConnect() callback
typedef struct WMStartConnectCallback
{
    u16     apiid;
    u16     errcode;                   // PARENT_NOT_FOUND(timeout)
    u16     wlCmdID;
    u16     wlResult;
    u16     state;                     // CONNECT_START, BEACON_LOST, CONNECTED, DISCONNECTED
    u16     aid;                       // Only when CONNECTED. AID assigned to self
    u16     reason;                    // reasonCode at disconnecting
    u16     wlStatus;
    u8      macAddress[WM_SIZE_MACADDR];
    u16     parentSize;
    u16     childSize;

}
WMStartConnectCallback, WMstartConnectCallback;

// Callback of WM_Disconnect() and WM_DisconnectChildren
typedef struct WMDisconnectCallback
{
    u16     apiid;
    u16     errcode;
    u16     wlCmdID;
    u16     wlResult;
    u16     tryBitmap;
    u16     disconnectedBitmap;
}
WMDisconnectCallback;

// WM_SetMPParameter() callback arguments
typedef struct WMSetMPParameterCallback
{
    u16     apiid;
    u16     errcode;
    u32     mask;
    WMMPParam oldParam;
}
WMSetMPParameterCallback;

// Argument of WM_StartMP() callback
typedef struct WMStartMPCallback
{
    u16     apiid;
    u16     errcode;
    u16     state;
    u8      reserved[2];               // for padding 4byte align
    WMMpRecvBuf *recvBuf;              // Receive buffer

    // The following only used for MPACK.Ind
    u16     timeStamp;
    u16     rate_rssi;
    u8      destAdrs[6];
    u8      srcAdrs[6];
    u16     seqNum;
    u16     tmptt;
    u16     pollbmp;
    u16     reserved2;
}
WMStartMPCallback, WMstartMPCallback;

// WM_StartDCF() callback arguments
typedef struct WMStartDCFCallback
{
    u16     apiid;
    u16     errcode;
    u16     state;
    u8      reserved[2];               // for padding 4byte align
    WMDcfRecvBuf *recvBuf;             // Receive buffer

}
WMStartDCFCallback, WMstartDCFCallback;

// WM_MeasureChannel() callback arguments
typedef struct WMMeasureChannelCallback
{
    u16     apiid;
    u16     errcode;
    u16     wlCmdID;
    u16     wlResult;
    u16     channel;
    u16     ccaBusyRatio;
}
WMMeasureChannelCallback, WMmeasureChannelCallback;

// WM_GetWirelessCounter() callback arguments
typedef struct WMGetWirelessCounterCallback
{
    u16     apiid;
    u16     errcode;
    u16     wlCmdID;
    u16     wlResult;
    u32     TX_Success;                // Number of successful sends
    u32     TX_Failed;                 // Number of failed sends
    u32     TX_Retry;                  // Number of resends
    u32     TX_AckError;               // Number of times desired ACK frame could not be received
    u32     TX_Unicast;                // Number of successfully sent Unicast addressed frames
    u32     TX_Multicast;              // Number of successfully sent Multicast addressed frames
    u32     TX_WEP;                    // Number of successfully sent encrypted frames
    u32     TX_Beacon;                 // Number of successfully sent Beacon frames
    u32     RX_RTS;                    // NOTE: Number of times of receiving RTS and then performing CTS response
    u32     RX_Fragment;               // Number of times fragmented frames received
    u32     RX_Unicast;                // Number of times Unicast addressed frames received
    u32     RX_Multicast;              // Number of times Multicast addressed frames received
    u32     RX_WEP;                    // Note: Number of times received encrypted frames that were successfully decrypted
    u32     RX_Beacon;                 // Number of times a Beacon frame was received
    u32     RX_FCSError;               // Note: Number of times an FCS error occurred
    u32     RX_DuplicateError;         // Note: Number of times redundant errors occurred
    u32     RX_MPDuplicateError;       // Note: Number of times an MP frame duplicate error occurred
    u32     RX_ICVError;               // Note: Number of times ICV errors occurred
    u32     RX_FrameCtrlError;         // Note: Number of times received frames that have illegal FrameCtrl
    u32     RX_LengthError;            // Note: Number of times received frames that are longer or shorter than the prescribed length
    u32     RX_PLCPError;              // Note: Number of times that PLCP CRC error occurred
    u32     RX_BufferOverflowError;    // Note: Number of times the receive buffer overflowed
    u32     RX_PathError;              // Note: Number of times receive block internal errors occurred
    u32     RX_RateError;              // Note: Number of times received frames that have an illegal receive rate
    u32     RX_FCSOK;                  // Note: Number of times received frames that have proper FCS
    u32     TX_MP;                     // Number of times MP frame sent
    u32     TX_KeyData;                // Number of times MP-KeyData frames sent
    u32     TX_NullKey;                // Number of times MP-NullKey frames sent
    u32     RX_MP;                     // Number of times proper MP frames received
    u32     RX_MPACK;                  // Number of times proper MPACK frames received
    u32     MPKeyResponseError[15];    // Number of times proper response not made to Key request
    /*
     *Note: Wireless hardware registers are sometimes cleared incorrectly, so the software counter that adds the hardware count registers may be lower than the actual total value.
     * 
     * Only affects counters with a "Note:".
     */
}
WMGetWirelessCounterCallback, WMgetWirelessCounterCallback;

// Indication callback arguments
typedef struct WMIndCallback
{
    u16     apiid;
    u16     errcode;
    u16     state;
    u16     reason;

}
WMIndCallback, WMindCallback;

// MP port communication send callback arguments
typedef struct WMPortSendCallback
{
    u16     apiid;
    u16     errcode;
    u16     wlCmdID;
    u16     wlResult;
    u16     state;
    u16     port;
    u16     destBitmap;
    u16     restBitmap;
    u16     sentBitmap;
    u16     rsv;
    const u16 *data;
    union
    {
        u16     size;
        u16     length;
    };
    u16     seqNo;
    WMCallbackFunc callback;
    void   *arg;
    u16     maxSendDataSize;
    u16     maxRecvDataSize;

}
WMPortSendCallback;

// MP port communication receive callback arguments
typedef struct WMPortRecvCallback
{
    u16     apiid;
    u16     errcode;
    u16     state;
    u16     port;                      // Port number
    WMMpRecvBuf *recvBuf;              // Receive buffer // For compatibility with WMStartMPCallback
    u16    *data;                      // Receive data (in the case of receive data addressed to port, reference this)
    u16     length;                    // Length of received data
    u16     aid;                       // Send source AID
    u8      macAddress[WM_SIZE_MACADDR];
    u16     seqNo;                     // seqNo
    void   *arg;                       // Argument passed to callback (append on WM9 side)
    u16     myAid;                     // One's own AID
    u16     connectedAidBitmap;        // AID Bitmap during connection
    u8      ssid[WM_SIZE_CHILD_SSID];  // SSID (child information)
    u16     reason;                    // reasonCode at disconnecting
    u16     rsv;                       // Reserved
    u16     maxSendDataSize;           // Current possible send size
    u16     maxRecvDataSize;           // Current possible receive size

}
WMPortRecvCallback;

// BeaconRecv.Ind callback arguments
typedef struct WMBeaconRecvIndCallback
{
    u16     apiid;
    u16     errcode;
    u16     state;
    u16     tgid;
    u16     wmstate;
    u16     gameInfoLength;
    WMGameInfo gameInfo;
}
WMBeaconRecvIndCallback;

// Argument of WM_StartTestMode() callback
typedef struct WMStartTestModeCallback
{
    u16     apiid;
    u16     errcode;
    u32     RFadr5;
    u32     RFadr6;
    u16     PllLockCheck;
    u16     RFMDflag;

}
WMStartTestModeCallback;

// Argument of WM_StopTestMode() callback
typedef struct WMStopTestRxModeCallback
{
    u16     apiid;
    u16     errcode;
    u32     fcsOk;
    u32     fcsErr;
}
WMStopTestRxModeCallback;

/*===========================================================================*/

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* NITRO_WM_COMMON_WM_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
