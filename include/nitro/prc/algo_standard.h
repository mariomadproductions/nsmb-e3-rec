/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PRC - include
  File:     prc/algo_standard.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: algo_standard.h,v $
  Revision 1.9  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.8  2005/03/04 12:45:07  seiki_masashi
  Changed so that PRC_InitPrototypeDB and PRC_InitInputPattern return whether create succeeded or failed.

  Revision 1.7  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.6  2004/11/04 07:59:53  seiki_masashi
  Revised regularize to normalize

  Revision 1.5  2004/07/19 06:52:06  seiki_masashi
  Arrangement of identifier names

  Revision 1.4  2004/06/30 08:49:45  seiki_masashi
  algo_simple -> algo_light
  algo_standard -> algo_fine
  algo_accurate -> algo_superfine
  Addition of new algo_standard

  Revision 1.3  2004/06/28 13:18:22  seiki_masashi
  Addition of PRC_GetInputPatternStrokes

  Revision 1.2  2004/06/25 03:03:39  seiki_masashi
  Deleted bufferSize specification from various functions
  Addition of GetRecognitionBufferSize*
  Changed functions that only call other functions to inline

  Revision 1.1  2004/06/24 07:03:10  seiki_masashi
  Partitioned and arranged header file

  Revision 1.1  2004/06/23 12:00:29  seiki_masashi
  add 'PRC*' to SDK

  Revision 1.3  2004/06/22 11:19:00  seiki_masashi
  Operable version (standard only)

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
#ifndef NITRO_PRC_ALGO_STANDARD_H_
#define NITRO_PRC_ALGO_STANDARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/prc/types.h"
#include "nitro/prc/common.h"
#include "nitro/prc/resample.h"
#include "nitro/prc/algo_common.h"

/*===========================================================================*
  Constant Definitions
 *===========================================================================*/

/*===========================================================================*
  Type Definitions
 *===========================================================================*/

/*---------------------------------------------------------------------------*
  Parameters for Sample DB Expansion
    normalizeSize       Normalize Size
    resampleThreshold   post-normalization resample threshold
 *---------------------------------------------------------------------------*/
typedef PRCPrototypeDBParam_Common PRCPrototypeDBParam_Standard;

/*---------------------------------------------------------------------------*
  Parameters for Input Pattern Interpretation
    normalizeSize       Normalize Size
    resampleThreshold   post-normalization resample threshold
 *---------------------------------------------------------------------------*/
typedef PRCInputPatternParam_Common PRCInputPatternParam_Standard;

/*---------------------------------------------------------------------------*
  Recognition Pattern of Input Origin
 *---------------------------------------------------------------------------*/
typedef PRCInputPattern_Common PRCInputPattern_Standard;

/*---------------------------------------------------------------------------*
  Sample DB Expanded in Memory
 *---------------------------------------------------------------------------*/
typedef PRCPrototypeDB_Common PRCPrototypeDB_Standard;

/*---------------------------------------------------------------------------*
  Parameters for Recognition Processing
 *---------------------------------------------------------------------------*/
typedef struct PRCRecognizeParam_Standard
{
    int     dummy;
}
PRCRecognizeParam_Standard;



/*---------------------------------------------------------------------------*
  Name:         PRC_Init_Standard

  Description:  Initializes pattern recognition API.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void PRC_Init_Standard(void)
{
    PRC_Init_Common();
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetPrototypeDBBufferSize_Standard

  Description:  Calculates the work area size required for expanding sample DB.

  Arguments:    prototypeList   sample pattern list

  Returns:      required memory capacity for expanding sample DB
 *---------------------------------------------------------------------------*/
static inline u32 PRC_GetPrototypeDBBufferSize_Standard(const PRCPrototypeList *prototypeList)
{
    return PRC_GetPrototypeDBBufferSize_Common(prototypeList);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetPrototypeDBBufferSizeEx_Standard

  Description:  Calculates the work area size required for expanding sample DB.

  Arguments:    prototypeList           sample pattern list
                kindMask                mask for type specification
                ignoreDisabledEntries   Whether or not sample DB entries with the enabled flag FALSE are ever expanded.
                param                   parameters for sample DB expansion

  Returns:      required memory capacity for expanding sample DB
 *---------------------------------------------------------------------------*/
static inline u32
PRC_GetPrototypeDBBufferSizeEx_Standard(const PRCPrototypeList *prototypeList,
                                        u32 kindMask,
                                        BOOL ignoreDisabledEntries,
                                        const PRCPrototypeDBParam_Standard *param)
{
    return PRC_GetPrototypeDBBufferSizeEx_Common(prototypeList, kindMask, ignoreDisabledEntries,
                                                 param);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitPrototypeDB_Standard

  Description:  Creates the PRCPrototypeDB structure.
                A buffer region larger than the size that PRC_GetPrototypeDBBufferSize
                returns needs to be set up in the buffer.

  Arguments:    protoDB         sample DB structure to be initialized
                buffer          pointer to memory region used for sample DB expansion
                                (Return value of memory area size >=PRC_GetPrototypeDBBufferSize)
                prototypeList   sample pattern list

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline BOOL
PRC_InitPrototypeDB_Standard(PRCPrototypeDB_Standard *protoDB,
                             void *buffer, const PRCPrototypeList *prototypeList)
{
    return PRC_InitPrototypeDB_Common(protoDB, buffer, prototypeList);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitPrototypeDBEx_Standard

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

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline BOOL
PRC_InitPrototypeDBEx_Standard(PRCPrototypeDB_Standard *protoDB,
                               void *buffer,
                               const PRCPrototypeList *prototypeList,
                               u32 kindMask,
                               BOOL ignoreDisabledEntries,
                               const PRCPrototypeDBParam_Standard *param)
{
    return PRC_InitPrototypeDBEx_Common(protoDB, buffer, prototypeList, kindMask,
                                        ignoreDisabledEntries, param);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetInputPatternBufferSize_Standard

  Description:  Calculates work area required for expanding pattern data for
                comparison.

  Arguments:    maxPointCount   upper limit of input points (includes pen up marker)
                maxStrokeCount  upper limit of stroke count

  Returns:      memory capacity required for expanding pattern
 *---------------------------------------------------------------------------*/
static inline u32 PRC_GetInputPatternBufferSize_Standard(int maxPointCount, int maxStrokeCount)
{
    return PRC_GetInputPatternBufferSize_Common(maxPointCount, maxStrokeCount);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitInputPattern_Standard

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
PRC_InitInputPattern_Standard(PRCInputPattern_Standard *pattern,
                              void *buffer,
                              const PRCStrokes *strokes, int maxPointCount, int maxStrokeCount)
{
    return PRC_InitInputPattern_Common(pattern, buffer, strokes, maxPointCount, maxStrokeCount);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitInputPatternEx_Standard

  Description:  Creates PRCInputPattern structure.
                Specification of parameters for input pattern interpretation can be done with param.

  Arguments:    pattern             pattern structure to be initialized
                buffer              pointer to memory region used for pattern expansion
                                    (Return value of area size >=PRC_GetInputPatternBufferSize)
                strokes             raw input coordinate value before forming
                param               parameters for input pattern interpretation

  Returns:      TRUE if create succeeded.
 *---------------------------------------------------------------------------*/
static inline BOOL
PRC_InitInputPatternEx_Standard(PRCInputPattern_Standard *pattern,
                                void *buffer,
                                const PRCStrokes *strokes,
                                int maxPointCount,
                                int maxStrokeCount, const PRCInputPatternParam_Standard *param)
{
    return PRC_InitInputPatternEx_Common(pattern, buffer, strokes, maxPointCount, maxStrokeCount,
                                         param);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognitionBufferSizeEx_Standard

  Description:  Calculates the work area size required for recognition algorithm.
                comparison.

  Arguments:    maxPointCount   upper limit of input points (includes pen up marker)
                maxStrokeCount  upper limit of stroke count
                protoDB         sample DB
                param           parameters for recognition processing

  Returns:      required memory capacity for recognition algorithm
 *---------------------------------------------------------------------------*/
u32
 
 
PRC_GetRecognitionBufferSizeEx_Standard(int maxPointCount,
                                        int maxStrokeCount,
                                        const PRCPrototypeDB_Standard *protoDB,
                                        const PRCRecognizeParam_Standard *param);

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognitionBufferSize_Standard

  Description:  Calculates the work area size required for recognition algorithm.
                comparison.

  Arguments:    maxPointCount   upper limit of input points (includes pen up marker)
                maxStrokeCount  upper limit of stroke count
                protoDB         sample DB

  Returns:      required memory capacity for recognition algorithm
 *---------------------------------------------------------------------------*/
static inline u32
PRC_GetRecognitionBufferSize_Standard(int maxPointCount,
                                      int maxStrokeCount, const PRCPrototypeDB_Standard *protoDB)
{
    return PRC_GetRecognitionBufferSizeEx_Standard(maxPointCount, maxStrokeCount, protoDB, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognizedEntriesEx_Standard

  Description:  Compares and recognizes a specific kind entry and input pattern
                the top ranking of the result numRanking.

  Arguments:    resultEntries   Pointer to array that enters pointer to recognition result.
                                If only the less than the requested number could be recognized,
                                fill in remainder with NULL.
                resultScores    pointer to recognition result score array
                numRanking      number return to result*
                buffer          pointer to memory region used by recognition algorithm
                                (Return value of area size >=PRC_GetRecognitionBufferSize)
                input           input pattern
                protoDB         sample DB
                kindMask        Carry out logical multiplication of kind value for each sample DB entry.
                                If non-zero considered valid.
                param           parameters for recognition processing

  Returns:      Number of compared patterns in the sample DB
 *---------------------------------------------------------------------------*/
int
 
 
PRC_GetRecognizedEntriesEx_Standard(PRCPrototypeEntry **resultEntries,
                                    fx32 *resultScores,
                                    int numRanking,
                                    void *buffer,
                                    const PRCInputPattern_Standard *input,
                                    const PRCPrototypeDB_Standard *protoDB,
                                    u32 kindMask, const PRCRecognizeParam_Standard *param);

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognizedEntries_Standard

  Description:  Compares and recognizes sample DB and input pattern and returns
                the top ranking of the result numRanking.

  Arguments:    resultEntries   Pointer to array that enters pointer to recognition result.
                                If only the less than the requested number could be recognized,
                                fill in remainder with NULL.
                resultScores    pointer to recognition result score array
                numRanking      the number wanted returned by result*
                buffer          pointer to memory region used by recognition algorithm
                                (Return value of area size >=PRC_GetRecognitionBufferSize)
                input           input pattern
                protoDB         sample DB

  Returns:      Number of compared patterns in the sample DB
 *---------------------------------------------------------------------------*/
static inline int
PRC_GetRecognizedEntries_Standard(PRCPrototypeEntry **resultEntries,
                                  fx32 *resultScores,
                                  int numRanking,
                                  void *buffer,
                                  const PRCInputPattern_Standard *input,
                                  const PRCPrototypeDB_Standard *protoDB)
{
    return PRC_GetRecognizedEntriesEx_Standard(resultEntries, resultScores, numRanking, buffer,
                                               input, protoDB, PRC_KIND_ALL, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognizedEntryEx_Standard

  Description:  Compares and recognizes a specific kind entry and input pattern for the sample DB.

  Arguments:    resultEntry Pointer that receives pointer to recognized sample DB entry.
                            If cannot recognize, NULL is entered.
                buffer      pointer to memory region used by recognition algorithm
                            (Return value of area size >=PRC_GetRecognitionBufferSize)
                input           input pattern
                protoDB     sample DB
                kindMask    Carry out logical multiplication of kind value for each sample DB entry.
                            If non-zero considered valid.
                param       parameters for recognition processing

  Returns:      score value
 *---------------------------------------------------------------------------*/
static inline fx32
PRC_GetRecognizedEntryEx_Standard(PRCPrototypeEntry **resultEntry,
                                  void *buffer,
                                  const PRCInputPattern_Standard *input,
                                  const PRCPrototypeDB_Standard *protoDB,
                                  u32 kindMask, const PRCRecognizeParam_Standard *param)
{
    fx32    score;
    (void)PRC_GetRecognizedEntriesEx_Standard(resultEntry, &score, 1, buffer, input, protoDB,
                                              kindMask, param);
    return score;
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognizedEntry_Standard

  Description:  Compares and recognizes sample DB and input pattern.

  Arguments:    resultEntry Pointer that receives pointer to recognized sample DB entry.
                            If cannot recognize, NULL is entered.
                buffer      pointer to memory region used by recognition algorithm
                            (Return value of area size >=PRC_GetRecognitionBufferSize)
                input           input pattern
                protoDB     sample DB

  Returns:      score value
 *---------------------------------------------------------------------------*/
static inline fx32
PRC_GetRecognizedEntry_Standard(PRCPrototypeEntry **resultEntry,
                                void *buffer,
                                const PRCInputPattern_Standard *input,
                                const PRCPrototypeDB_Standard *protoDB)
{
    return PRC_GetRecognizedEntryEx_Standard(resultEntry, buffer, input, protoDB, PRC_KIND_ALL,
                                             NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetInputPatternStrokes_Standard

  Description:  Obtains dot sequence data from PRCInputPattern structure.

  Arguments:    strokes         dot sequence data obtained
                                Overwriting is not permitted.
                input           input pattern

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
PRC_GetInputPatternStrokes_Standard(PRCStrokes *strokes, const PRCInputPattern_Standard *input)
{
    PRC_GetInputPatternStrokes_Common(strokes, input);
}


/*===========================================================================*
  Inline Functions
 *===========================================================================*/




/*===========================================================================*
  Set as the standard function of the graphics recognition API
 *===========================================================================*/
#ifndef PRC_DEFAULT_ALGORITHM
#define PRC_DEFAULT_ALGORITHM "Standard"

/*---------------------------------------------------------------------------*
  Parameters for Sample DB Expansion
 *---------------------------------------------------------------------------*/
typedef PRCPrototypeDBParam_Standard PRCPrototypeDBParam;

/*---------------------------------------------------------------------------*
  Parameters for Input Pattern Interpretation
 *---------------------------------------------------------------------------*/
typedef PRCInputPatternParam_Standard PRCInputPatternParam;

/*---------------------------------------------------------------------------*
  Recognition Pattern of Input Origin
 *---------------------------------------------------------------------------*/
typedef PRCInputPattern_Standard PRCInputPattern;

/*---------------------------------------------------------------------------*
  Sample DB Expanded in Memory
 *---------------------------------------------------------------------------*/
typedef PRCPrototypeDB_Standard PRCPrototypeDB;

/*---------------------------------------------------------------------------*
  Parameters for Recognition Processing
 *---------------------------------------------------------------------------*/
typedef PRCRecognizeParam_Standard PRCRecognizeParam;


/*---------------------------------------------------------------------------*
  Functions
 *---------------------------------------------------------------------------*/
static inline void PRC_Init(void)
{
    PRC_Init_Standard();
}

static inline u32 PRC_GetPrototypeDBBufferSize(const PRCPrototypeList *prototypeList)
{
    return PRC_GetPrototypeDBBufferSize_Standard(prototypeList);
}

static inline u32
PRC_GetPrototypeDBBufferSizeEx(const PRCPrototypeList *prototypeList,
                               u32 kindMask,
                               BOOL ignoreDisabledEntries, const PRCPrototypeDBParam *param)
{
    return PRC_GetPrototypeDBBufferSizeEx_Standard(prototypeList, kindMask, ignoreDisabledEntries,
                                                   param);
}

static inline BOOL
PRC_InitPrototypeDB(PRCPrototypeDB *protoDB, void *buffer, const PRCPrototypeList *prototypeList)
{
    return PRC_InitPrototypeDB_Standard(protoDB, buffer, prototypeList);
}

static inline BOOL
PRC_InitPrototypeDBEx(PRCPrototypeDB *protoDB,
                      void *buffer,
                      const PRCPrototypeList *prototypeList,
                      u32 kindMask, BOOL ignoreDisabledEntries, const PRCPrototypeDBParam *param)
{
    return PRC_InitPrototypeDBEx_Standard(protoDB, buffer, prototypeList, kindMask,
                                          ignoreDisabledEntries, param);
}

static inline u32 PRC_GetInputPatternBufferSize(int maxPointCount, int maxStrokeCount)
{
    return PRC_GetInputPatternBufferSize_Standard(maxPointCount, maxStrokeCount);
}

static inline BOOL
PRC_InitInputPattern(PRCInputPattern *pattern,
                     void *buffer, const PRCStrokes *strokes, int maxPointCount, int maxStrokeCount)
{
    return PRC_InitInputPattern_Standard(pattern, buffer, strokes, maxPointCount, maxStrokeCount);
}

static inline BOOL
PRC_InitInputPatternEx(PRCInputPattern *pattern,
                       void *buffer,
                       const PRCStrokes *strokes,
                       int maxPointCount, int maxStrokeCount, const PRCInputPatternParam *param)
{
    return PRC_InitInputPatternEx_Standard(pattern, buffer, strokes, maxPointCount, maxStrokeCount,
                                           param);
}

static inline u32
PRC_GetRecognitionBufferSize(int maxPointCount,
                             int maxStrokeCount, const PRCPrototypeDB_Standard *protoDB)
{
    return PRC_GetRecognitionBufferSize_Standard(maxPointCount, maxStrokeCount, protoDB);
}

static inline u32
PRC_GetRecognitionBufferSizeEx(int maxPointCount,
                               int maxStrokeCount,
                               const PRCPrototypeDB_Standard *protoDB,
                               const PRCRecognizeParam_Standard *param)
{
    return PRC_GetRecognitionBufferSizeEx_Standard(maxPointCount, maxStrokeCount, protoDB, param);
}

static inline fx32
PRC_GetRecognizedEntry(PRCPrototypeEntry **resultEntry,
                       void *buffer, const PRCInputPattern *input, const PRCPrototypeDB *protoDB)
{
    return PRC_GetRecognizedEntry_Standard(resultEntry, buffer, input, protoDB);
}

static inline fx32
PRC_GetRecognizedEntryEx(PRCPrototypeEntry **resultEntry,
                         void *buffer,
                         const PRCInputPattern *input,
                         const PRCPrototypeDB *protoDB,
                         u32 kindMask, const PRCRecognizeParam *param)
{
    return PRC_GetRecognizedEntryEx_Standard(resultEntry, buffer, input, protoDB, kindMask, param);
}

static inline int
PRC_GetRecognizedEntries(PRCPrototypeEntry **resultEntries,
                         fx32 *resultScores,
                         int numRanking,
                         void *buffer, const PRCInputPattern *input, const PRCPrototypeDB *protoDB)
{
    return PRC_GetRecognizedEntries_Standard(resultEntries, resultScores, numRanking, buffer, input,
                                             protoDB);
}

static inline int
PRC_GetRecognizedEntriesEx(PRCPrototypeEntry **resultEntries,
                           fx32 *resultScores,
                           int numRanking,
                           void *buffer,
                           const PRCInputPattern *input,
                           const PRCPrototypeDB *protoDB,
                           u32 kindMask, const PRCRecognizeParam *param)
{
    return PRC_GetRecognizedEntriesEx_Standard(resultEntries, resultScores, numRanking, buffer,
                                               input, protoDB, kindMask, param);
}

static inline void PRC_GetInputPatternStrokes(PRCStrokes *strokes, const PRCInputPattern *input)
{
    PRC_GetInputPatternStrokes_Standard(strokes, input);
}

#endif // PRC_DEFAULT_ALGORITHM




#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PRC_ALGO_STANDARD_H_ */
#endif
