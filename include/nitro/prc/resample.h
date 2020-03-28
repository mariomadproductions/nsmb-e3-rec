/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PRC - include
  File:     prc_resample.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: resample.h,v $
  Revision 1.6  2006/01/18 02:12:28  kitase_hirotake
  do-indent

  Revision 1.5  2005/03/04 13:37:05  seiki_masashi
  Changed so that PRC_ResampleStrokes_* returns whether create succeeded or failed.

  Revision 1.4  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.3  2004/07/19 06:52:06  seiki_masashi
  Arrangement of identifier names

  Revision 1.2  2004/07/09 00:13:15  seiki_masashi
  PRCi_Resample* -> PRC_Resample*

  Revision 1.1  2004/06/24 07:03:10  seiki_masashi
  Partitioned and arranged header file

  Revision 1.1  2004/06/23 12:00:29  seiki_masashi
  add 'PRC*' to SDK

  Revision 1.1  2004/06/22 11:19:00  seiki_masashi
  Operable Version (simple only)


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PRC_RESAMPLE_H_
#define NITRO_PRC_RESAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/prc/common.h"
#include "nitro/prc/types.h"

/*===========================================================================*
  Constant Definitions
 *===========================================================================*/

/*===========================================================================*
  Type Definitions
 *===========================================================================*/



/*---------------------------------------------------------------------------*
  Name:         PRC_ResampleStrokes_None

  Description:  Does not resample.

  Arguments:    selectedPoints, pSelectedPointNum pointer with result return
                maxPointCount       upper limit of input points (includes pen up marker)
                maxStrokeCount      upper limit of stroke count
                strokes             raw input coordinate value before forming
                threshold           resample threshold
                buffer              work area (sizeof(int)*maxPointCount required)

  Returns:      TRUE if resampling succeeded.
 *---------------------------------------------------------------------------*/
BOOL
 
 PRC_ResampleStrokes_None(u16 *selectedPoints,
                          int *pSelectedPointNum,
                          int maxPointCount,
                          int maxStrokeCount,
                          const PRCStrokes *strokes, int threshold, void *buffer);

/*---------------------------------------------------------------------------*
  Name:         PRC_ResampleStrokes_Distance

  Description:  Resamples based on city block distance

  Arguments:    selectedPoints, pSelectedPointNum pointer with result return
                maxPointCount       upper limit of input points (includes pen up marker)
                maxStrokeCount      upper limit of stroke count
                strokes             raw input coordinate value before forming
                threshold           resample threshold
                buffer              work area (sizeof(int)*maxPointCount required)

  Returns:      TRUE if resampling succeeded.
 *---------------------------------------------------------------------------*/
BOOL
 
 PRC_ResampleStrokes_Distance(u16 *selectedPoints,
                              int *pSelectedPointNum,
                              int maxPointCount,
                              int maxStrokeCount,
                              const PRCStrokes *strokes, int threshold, void *buffer);

/*---------------------------------------------------------------------------*
  Name:         PRC_ResampleStrokes_Angle

  Description:  Resamples based on angle.

  Arguments:    selectedPoints, pSelectedPointNum pointer with result return
                maxPointCount       upper limit of input points (includes pen up marker)
                maxStrokeCount      upper limit of stroke count
                strokes             raw input coordinate value before forming
                threshold           resample threshold
                buffer              work area (sizeof(int)*maxPointCount required)

  Returns:      TRUE if resampling succeeded.
 *---------------------------------------------------------------------------*/
BOOL
 
 PRC_ResampleStrokes_Angle(u16 *selectedPoints,
                           int *pSelectedPointNum,
                           int maxPointCount,
                           int maxStrokeCount,
                           const PRCStrokes *strokes, int threshold, void *buffer);

/*---------------------------------------------------------------------------*
  Name:         PRC_ResampleStrokes_Recursive

  Description:  Resample with recursive method.

  Arguments:    selectedPoints, pSelectedPointNum pointer with result return
                maxPointCount       upper limit of input points (includes pen up marker)
                maxStrokeCount      upper limit of stroke count
                strokes             raw input coordinate value before forming
                threshold           resample threshold
                buffer              work area (sizeof(int)*maxPointCount required)

  Returns:      TRUE if resampling succeeded.
 *---------------------------------------------------------------------------*/
BOOL
 
 PRC_ResampleStrokes_Recursive(u16 *selectedPoints,
                               int *pSelectedPointNum,
                               int maxPointCount,
                               int maxStrokeCount,
                               const PRCStrokes *strokes, int threshold, void *buffer);


/*===========================================================================*
  Inline Functions
 *===========================================================================*/

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PRC_RESAMPLE_H_ */
#endif
