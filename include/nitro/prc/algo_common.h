/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PRC - include
  File:     prc/algo_common.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: algo_common.h,v $
  Revision 1.12  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.11  2005/03/04 12:45:07  seiki_masashi
  Changed so that PRC_InitPrototypeDB and PRC_InitInputPattern return whether create succeeded or failed.

  Revision 1.10  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.9  2004/11/10 01:00:25  seiki_masashi
  Added a union so that access is possible with normalizeSize and regularizeSize

  Revision 1.8  2004/11/04 07:59:53  seiki_masashi
  Revised regularize to normalize

  Revision 1.7  2004/07/19 06:52:06  seiki_masashi
  Arrangement of identifier names

  Revision 1.6  2004/07/01 09:05:31  seiki_masashi
  Minor fixes

  Revision 1.5  2004/06/29 02:13:28  seiki_masashi
  remove lineSegmentRatioToWholeArray

  Revision 1.4  2004/06/28 13:18:22  seiki_masashi
  Addition of PRC_GetInputPatternStrokes

  Revision 1.3  2004/06/28 11:10:41  seiki_masashi
  Added regularizeSize to the sample pattern list
  Organized all types of parameters

  Revision 1.2  2004/06/25 03:03:39  seiki_masashi
  Deleted bufferSize specification from various functions
  Addition of GetRecognitionBufferSize*
  Changed functions that only call other functions to inline

  Revision 1.1  2004/06/24 07:03:10  seiki_masashi
  Partitioned and arranged header file

  Revision 1.1  2004/06/23 12:00:29  seiki_masashi
  add 'PRC*' to SDK

  Revision 1.3  2004/06/22 11:19:00  seiki_masashi
  Operable Version (simple only)

  Revision 1.2  2004/06/17 08:14:52  seiki_masashi
  PRC_GetPrototypeDBBufferSizeEx

  Revision 1.1  2004/06/17 02:30:29  seiki_masashi
  In order to allow easy replacement of the recognition algorithm, divided at prc_algo_*

  Revision 1.2  2004/06/17 00:52:36  seiki_masashi
  PRC_InitPrototypeDBEX, PRC_InitInputPatternEX

  Revision 1.1  2004/06/16 23:56:09  seiki_masashi
  Renamed ptrcg to prc.

  Revision 1.3  2004/06/15 08:10:55  seiki_masashi
  Sample programs made operable with the dummy library

  Revision 1.2  2004/06/15 05:55:09  seiki_masashi
  Interface improvements

  Revision 1.1  2004/06/15 00:54:42  seiki_masashi
  Interface design


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PRC_ALGO_COMMON_H_
#define NITRO_PRC_ALGO_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/prc/types.h"
#include "nitro/prc/common.h"


/*===========================================================================*
  Macros
 *===========================================================================*/

//--- For Get*BufferSize
#define PRCi_ARRAY_SIZE(type, size, dummy) \
    sizeof(type) * (size)

//--- For Set*BufferInfo
#define PRCi_ALLOC_ARRAY(dst, type, size, base, offset) \
    (dst) = (type*)((u8*)(base) + (offset)); \
    (offset) += sizeof(type) * (size)


/*===========================================================================*
  Constant Definitions
 *===========================================================================*/

#define PRC_RESAMPLE_DEFAULT_METHOD_COMMON PRC_RESAMPLE_METHOD_RECURSIVE
#define PRC_RESAMPLE_DEFAULT_THRESHOLD_COMMON 5

/*===========================================================================*
  Type Definitions
 *===========================================================================*/

/*---------------------------------------------------------------------------*
  Parameters for Sample DB Expansion
 *---------------------------------------------------------------------------*/
typedef struct PRCPrototypeDBParam_Common
{
    int     dummy;
}
PRCPrototypeDBParam_Common;

/*---------------------------------------------------------------------------*
  Parameters for Input Pattern Interpretation
    normalizeSize       Normalize Size
    resampleMethod      type of algorithm used for normalization
    resampleThreshold   post-normalization resample threshold
 *---------------------------------------------------------------------------*/
typedef struct PRCInputPatternParam_Common
{
    union
    {
        int     normalizeSize;
        int     regularizeSize;        // Old name
    };
    PRCResampleMethod resampleMethod;
    int     resampleThreshold;
}
PRCInputPatternParam_Common;

/*---------------------------------------------------------------------------*
  Common Parts of Sample DB Origin and Input Origin Recognition Pattern
 *---------------------------------------------------------------------------*/
typedef struct PRCiPatternData_Common
{
    u16     strokeCount;               // Duplicate information to entry
    u16     pointCount;                // Duplicate information to entry
    const PRCPoint *pointArray;
    int    *strokes;
    int    *strokeSizes;
    fx32   *lineSegmentLengthArray;
    fx16   *lineSegmentRatioToStrokeArray;
//    fx16                        *lineSegmentRatioToWholeArray;
    u16    *lineSegmentAngleArray;
    fx32   *strokeLengths;
    fx16   *strokeRatios;
    fx32    wholeLength;
    PRCBoundingBox *strokeBoundingBoxes;
    PRCBoundingBox wholeBoundingBox;
}
PRCiPatternData_Common;

/*---------------------------------------------------------------------------*
  Buffer Information for forming pattern dynamically during input.
  It is possible each recognition algorithm is expanding based on this so
  when changing you need to verify the -BufferInfo_* for each algorithm.
 *---------------------------------------------------------------------------*/
typedef struct PRCiPatternBufferInfo_Common
{
    PRCPoint *pointArray;
    int    *strokes;
    int    *strokeSizes;
    fx32   *lineSegmentLengthArray;
    fx16   *lineSegmentRatioToStrokeArray;
//    fx16                        *lineSegmentRatioToWholeArray;
    u16    *lineSegmentAngleArray;
    fx32   *strokeLengths;
    fx16   *strokeRatios;
    PRCBoundingBox *strokeBoundingBoxes;
}
PRCiPatternBufferInfo_Common;

/*---------------------------------------------------------------------------*
  Sample DB Origin Recognition Pattern
 *---------------------------------------------------------------------------*/
typedef struct PRCiPrototypeEntry_Common
{
    PRCiPatternData_Common data;
    const PRCPrototypeEntry *entry;
}
PRCiPrototypeEntry_Common;

/*---------------------------------------------------------------------------*
  Recognition Pattern of Input Origin
 *---------------------------------------------------------------------------*/
typedef struct PRCInputPattern_Common
{
    PRCiPatternData_Common data;
    union
    {
        int     normalizeSize;
        int     regularizeSize;        // Old name
    };

    void   *buffer;
    u32     bufferSize;
}
PRCInputPattern_Common;

/*---------------------------------------------------------------------------*
  Buffer Information for forming sample DB dynamically during input.
  It is possible each recognition algorithm is expanding based on this so
  when changing you need to verify the -BufferInfo_* for each algorithm.
 *---------------------------------------------------------------------------*/
typedef struct PRCiPrototypeListBufferInfo_Common
{
    PRCiPrototypeEntry_Common *patterns;
    fx32   *lineSegmentLengthArray;
    fx16   *lineSegmentRatioToStrokeArray;
//    fx16                        *lineSegmentRatioToWholeArray;
    u16    *lineSegmentAngleArray;
    int    *strokeArray;
    int    *strokeSizeArray;
    fx32   *strokeLengthArray;
    fx16   *strokeRatioArray;
    PRCBoundingBox *strokeBoundingBoxArray;
}
PRCiPrototypeListBufferInfo_Common;

/*---------------------------------------------------------------------------*
  Sample DB Expanded in Memory
 *---------------------------------------------------------------------------*/
typedef struct PRCPrototypeDB_Common
{
    PRCiPrototypeEntry_Common *patterns;
    int     patternCount;

    fx32   *lineSegmentLengthArray;
    fx16   *lineSegmentRatioToStrokeArray;
//    fx16                        *lineSegmentRatioToWholeArray;
    u16    *lineSegmentAngleArray;
    int     wholePointCount;

    int    *strokeArray;
    int    *strokeSizeArray;
    fx32   *strokeLengthArray;
    fx16   *strokeRatioArray;
    PRCBoundingBox *strokeBoundingBoxArray;
    int     wholeStrokeCount;

    int     maxPointCount;
    int     maxStrokeCount;

    union
    {
        int     normalizeSize;
        int     regularizeSize;        // Old name
    };

    const PRCPrototypeList *prototypeList;
    void   *buffer;
    u32     bufferSize;
}
PRCPrototypeDB_Common;


/*---------------------------------------------------------------------------*
  Name:         PRC_Init_Common

  Description:  Initializes pattern recognition API.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void PRC_Init_Common(void)
{
    PRCi_Init();
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetPrototypeDBBufferSizeEx_Common

  Description:  Calculates the work area size required for expanding sample DB.

  Arguments:    prototypeList           sample pattern list
                kindMask                mask for type specification
                ignoreDisabledEntries   Whether or not sample DB entries with the enabled flag FALSE are ever expanded.
                                        
                param                   parameters for sample DB expansion

  Returns:      required memory capacity for expanding sample DB
 *---------------------------------------------------------------------------*/
u32
 
 
PRC_GetPrototypeDBBufferSizeEx_Common(const PRCPrototypeList *prototypeList,
                                      u32 kindMask,
                                      BOOL ignoreDisabledEntries,
                                      const PRCPrototypeDBParam_Common *param);

/*---------------------------------------------------------------------------*
  Name:         PRC_GetPrototypeDBBufferSize_Common

  Description:  Calculates the work area size required for expanding sample DB.

  Arguments:    prototypeList   sample pattern list

  Returns:      required memory capacity for expanding sample DB
 *---------------------------------------------------------------------------*/
u32 static inline PRC_GetPrototypeDBBufferSize_Common(const PRCPrototypeList *prototypeList)
{
    return PRC_GetPrototypeDBBufferSizeEx_Common(prototypeList, PRC_KIND_ALL, FALSE, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitPrototypeDBEx_Common

  Description:  Creates the PRCPrototypeDB structure.
                A buffer region larger than the size that PRC_GetPrototypeDBBufferSize
                returns needs to be set up in the buffer.
                Parameters during expansion can be specified with param.

  Arguments:    protoDB         sample DB structure to be initialized
                buffer          pointer to memory region used for sample DB expansion
                                (Return value of memory area size >=PRC_GetPrototypeDBBufferSize)
                prototypeList   sample pattern list
                kindMask        mask for type specification
                ignoreDisabledEntries   Whether or not sample DB entries with the enabled flag FALSE are ever expanded.

                param           parameters for sample DB expansion

  Returns:      TRUE if create succeeded.
 *---------------------------------------------------------------------------*/
BOOL
 
 PRC_InitPrototypeDBEx_Common(PRCPrototypeDB_Common *protoDB,
                              void *buffer,
                              const PRCPrototypeList *prototypeList,
                              u32 kindMask,
                              BOOL ignoreDisabledEntries, const PRCPrototypeDBParam_Common *param);

/*---------------------------------------------------------------------------*
  Name:         PRC_InitPrototypeDB_Common

  Description:  Creates the PRCPrototypeDB structure.
                A buffer region larger than the size that PRC_GetPrototypeDBBufferSize
                returns needs to be set up in the buffer.

  Arguments:    protoDB         sample DB structure to be initialized
                buffer          pointer to memory region used for sample DB expansion
                                (Return value of memory area size >=PRC_GetPrototypeDBBufferSize)
                prototypeList   sample pattern list

  Returns:      TRUE if create succeeded.
 *---------------------------------------------------------------------------*/
static inline BOOL
PRC_InitPrototypeDB_Common(PRCPrototypeDB_Common *protoDB,
                           void *buffer, const PRCPrototypeList *prototypeList)
{
    return PRC_InitPrototypeDBEx_Common(protoDB, buffer, prototypeList, PRC_KIND_ALL, FALSE, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetInputPatternBufferSize_Common

  Description:  Calculates work area required for expanding pattern data for
                comparison.

  Arguments:    maxPointCount   upper limit of input points (includes pen up marker)
                maxStrokeCount  upper limit of stroke count

  Returns:      memory capacity required for expanding pattern
 *---------------------------------------------------------------------------*/
u32     PRC_GetInputPatternBufferSize_Common(int maxPointCount, int maxStrokeCount);

/*---------------------------------------------------------------------------*
  Name:         PRC_InitInputPatternEx_Common

  Description:  Creates PRCInputPattern structure.
                Specification of parameters for input pattern interpretation can be done with param.

  Arguments:    pattern             pattern structure to be initialized
                buffer              pointer to memory region used for pattern expansion
                                    (Return value of area size >=PRC_GetInputPatternBufferSize)
                strokes             raw input coordinate value before forming
                maxPointCount       upper limit of input points (includes pen up marker)
                maxStrokeCount      upper limit of stroke count
                param               parameters for input pattern interpretation

  Returns:      TRUE if create succeeded.
 *---------------------------------------------------------------------------*/
BOOL
 
 PRC_InitInputPatternEx_Common(PRCInputPattern_Common *pattern,
                               void *buffer,
                               const PRCStrokes *strokes,
                               int maxPointCount,
                               int maxStrokeCount, const PRCInputPatternParam_Common *param);

/*---------------------------------------------------------------------------*
  Name:         PRC_InitInputPattern_Common

  Description:  Creates PRCInputPattern structure.

  Arguments:    pattern             pattern structure to be initialized
                buffer              pointer to memory region used for pattern expansion
                                    (Return value of area size >=PRC_GetInputPatternBufferSize)
                strokes             raw input coordinate value before forming
                maxPointCount       upper limit of input points (includes pen up marker)
                maxStrokeCount      upper limit of stroke count

  Returns:      TRUE if create succeeded.
 *---------------------------------------------------------------------------*/
static inline BOOL
PRC_InitInputPattern_Common(PRCInputPattern_Common *pattern,
                            void *buffer,
                            const PRCStrokes *strokes, int maxPointCount, int maxStrokeCount)
{
    return PRC_InitInputPatternEx_Common(pattern, buffer, strokes, maxPointCount, maxStrokeCount,
                                         NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetInputPatternStrokes_Common

  Description:  Obtains dot sequence data from PRCInputPattern structure.

  Arguments:    strokes         dot sequence data obtained
                                Overwriting is not permitted.
                input           input pattern

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    PRC_GetInputPatternStrokes_Common(PRCStrokes *strokes, const PRCInputPattern_Common *input);


// for debug
void    PRCi_PrintPatternData_Common(PRCiPatternData_Common *data);

/*===========================================================================*
  Inline Functions
 *===========================================================================*/

#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PRC_ALGO_COMMON_H_ */
#endif
