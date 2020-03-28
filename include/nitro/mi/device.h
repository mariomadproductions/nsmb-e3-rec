/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MI - include
  File:     device.h

  Copyright 2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
#ifndef	NITRO_MI_DEVICE_H_
#define	NITRO_MI_DEVICE_H_


#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/platform.h"


#ifdef __cplusplus
extern  "C"
{
#endif


/*---------------------------------------------------------------------------*/
/* Declarations */

/* Device access function prototype */
typedef int (*MIDeviceReadFunction)(void *userdata, void *buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void *userdata, const void *buffer, u32 offset, u32 length);

/* Device access structure */
typedef struct MIDevice
{
    void                   *userdata;
    MIDeviceReadFunction    Read;
    MIDeviceWriteFunction   Write;
}
MIDevice;


/*---------------------------------------------------------------------------*/
/* Functions */

/*---------------------------------------------------------------------------*
  Name:         MI_InitDevice

  Description:  Initializes the device.

  Arguments:    device           The MIDevice structure to be initialized.
                userdata         Any user-defined argument.
                read             Pointer to device read function.
                write            Pointer to device write function.

  Returns:      None.
 *---------------------------------------------------------------------------*/
PLATFORM_ATTRIBUTE_INLINE
void MI_InitDevice(MIDevice *device, void *userdata,
                   MIDeviceReadFunction read,
                   MIDeviceWriteFunction write)
{
    device->userdata = userdata;
    device->Read = read;
    device->Write = write;
}

/*---------------------------------------------------------------------------*
  Name:         MI_ReadDevice

  Description:  Reads from the device.

  Arguments:    device           The MIDevice structure.
                buffer           The transfer target memory.
                offset           The transfer source offset.
                length           The transfer size.

  Returns:      Returns a value of 0 or higher if successful; a negative number otherwise.
 *---------------------------------------------------------------------------*/
PLATFORM_ATTRIBUTE_INLINE
int MI_ReadDevice(MIDevice *device, void *buffer, u32 offset, u32 length)
{
    return device->Read(device->userdata, buffer, offset, length);
}

/*---------------------------------------------------------------------------*
  Name:         MI_WriteDevice

  Description:  Writes to the device.

  Arguments:    device           The MIDevice structure.
                buffer           The transfer source memory.
                offset           The transfer target offset.
                length           The transfer size.

  Returns:      Returns a value of 0 or higher if successful; a negative number otherwise.
 *---------------------------------------------------------------------------*/
PLATFORM_ATTRIBUTE_INLINE
int MI_WriteDevice(MIDevice *device, const void *buffer, u32 offset, u32 length)
{
    return device->Write(device->userdata, buffer, offset, length);
}


/*---------------------------------------------------------------------------*/


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* NITRO_MI_DEVICE_H_ */
/*---------------------------------------------------------------------------*
  $Log: device.h,v $
  Revision 1.1  2007/04/11 08:04:56  yosizaki
  Initial upload.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
