/*---------------------------------------------------------------------------*
  Project:  NitroSDK - PRC - include
  File:     prc/algo_superfine.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: algo_superfine.h,v $
  Revision 1.6  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.5  2005/03/04 12:45:07  seiki_masashi
  Changed so that PRC_InitPrototypeDB and PRC_InitInputPattern return whether create succeeded or failed.

  Revision 1.4  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.3  2004/11/04 07:59:53  seiki_masashi
  Revised regularize to normalize

  Revision 1.2  2004/07/19 06:52:06  seiki_masashi
  Arrangement of identifier names

  Revision 1.1  2004/06/30 08:49:45  seiki_masashi
  algo_simple -> algo_light
  algo_standard -> algo_fine
  algo_accurate -> algo_superfine
  Addition of new algo_standard

  Revision 1.5  2004/06/28 13:18:22  seiki_masashi
  Addition of PRC_GetInputPatternStrokes

  Revision 1.4  2004/06/28 11:10:41  seiki_masashi
  Added regularizeSize to the sample pattern list
  Organized all types of parameters

  Revision 1.3  2004/06/25 13:32:01  seiki_masashi
  Addition of recognition algorithm "Standard"

  Revision 1.2  2004/06/25 03:03:39  seiki_masashi
  Deleted bufferSize specification from various functions
  Addition of GetRecognitionBufferSize*
  Changed functions that only call other functions to inline

  Revision 1.1  2004/06/24 08:10:04  seiki_masashi
  Added recognition algorithm "Superfine"


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_PRC_ALGO_SUPERFINE_H_
#define NITRO_PRC_ALGO_SUPERFINE_H_

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

#define PRC_LENGTH_FILTER_DEFAULT_THRESHOLD_SUPERFINE    normalizeSize
#define PRC_LENGTH_FILTER_DEFAULT_RATIO_SUPERFINE        3

/*===========================================================================*
  Type Definitions
 *===========================================================================*/

/*---------------------------------------------------------------------------*
  Parameters for Sample DB Expansion
    normalizeSize       Normalize Size
    resampleThreshold   post-normalization resample threshold
 *---------------------------------------------------------------------------*/
typedef PRCPrototypeDBParam_Common PRCPrototypeDBParam_Superfine;

/*---------------------------------------------------------------------------*
  Parameters for Input Pattern Interpretation
    normalizeSize       Normalize Size
    resampleThreshold   post-normalization resample threshold
 *---------------------------------------------------------------------------*/
typedef PRCInputPatternParam_Common PRCInputPatternParam_Superfine;

/*---------------------------------------------------------------------------*
  Recognition Pattern of Input Origin
 *---------------------------------------------------------------------------*/
typedef PRCInputPattern_Common PRCInputPattern_Superfine;

/*---------------------------------------------------------------------------*
  Sample DB Expanded in Memory
 *---------------------------------------------------------------------------*/
typedef PRCPrototypeDB_Common PRCPrototypeDB_Superfine;

/*---------------------------------------------------------------------------*
  Parameters for Recognition Processing
 *---------------------------------------------------------------------------*/
typedef struct PRCRecognizeParam_Superfine
{
    int     lengthFilterThreshold;
    int     lengthFilterRatio;
}
PRCRecognizeParam_Superfine;



/*---------------------------------------------------------------------------*
  Name:         PRC_Init_Superfine

  Description:  Initializes pattern recognition API.

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void PRC_Init_Superfine(void)
{
    PRC_Init_Common();
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetPrototypeDBBufferSize_Superfine

  Description:  Calculates the work area size required for expanding sample DB.

  Arguments:    prototypeList   sample pattern list

  Returns:      required memory capacity for expanding sample DB
 *---------------------------------------------------------------------------*/
static inline u32 PRC_GetPrototypeDBBufferSize_Superfine(const PRCPrototypeList *prototypeList)
{
    return PRC_GetPrototypeDBBufferSize_Common(prototypeList);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetPrototypeDBBufferSizeEx_Superfine

  Description:  Calculates the work area size required for expanding sample DB.

  Arguments:    prototypeList           sample pattern list
                kindMask                mask for type specification
                ignoreDisabledEntries   Whether or not sample DB entries with the enabled flag FALSE are ever expanded.
                                        
                param                   parameters for sample DB expansion

  Returns:      required memory capacity for expanding sample DB
 *---------------------------------------------------------------------------*/
static inline u32
PRC_GetPrototypeDBBufferSizeEx_Superfine(const PRCPrototypeList *prototypeList,
                                         u32 kindMask,
                                         BOOL ignoreDisabledEntries,
                                         const PRCPrototypeDBParam_Superfine *param)
{
    return PRC_GetPrototypeDBBufferSizeEx_Common(prototypeList, kindMask, ignoreDisabledEntries,
                                                 param);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitPrototypeDB_Superfine

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
PRC_InitPrototypeDB_Superfine(PRCPrototypeDB_Superfine *protoDB,
                              void *buffer, const PRCPrototypeList *prototypeList)
{
    return PRC_InitPrototypeDB_Common(protoDB, buffer, prototypeList);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitPrototypeDBEx_Superfine

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
static inline BOOL
PRC_InitPrototypeDBEx_Superfine(PRCPrototypeDB_Superfine *protoDB,
                                void *buffer,
                                const PRCPrototypeList *prototypeList,
                                u32 kindMask,
                                BOOL ignoreDisabledEntries,
                                const PRCPrototypeDBParam_Superfine *param)
{
    return PRC_InitPrototypeDBEx_Common(protoDB, buffer, prototypeList, kindMask,
                                        ignoreDisabledEntries, param);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetInputPatternBufferSize_Superfine

  Description:  Calculates work area required for expanding pattern data for
                comparison.

  Arguments:    maxPointCount   upper limit of input points (includes pen up marker)
                maxStrokeCount  upper limit of stroke count

  Returns:      memory capacity required for expanding pattern
 *---------------------------------------------------------------------------*/
static inline u32 PRC_GetInputPatternBufferSize_Superfine(int maxPointCount, int maxStrokeCount)
{
    return PRC_GetInputPatternBufferSize_Common(maxPointCount, maxStrokeCount);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitInputPattern_Superfine

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
PRC_InitInputPattern_Superfine(PRCInputPattern_Superfine *pattern,
                               void *buffer,
                               const PRCStrokes *strokes, int maxPointCount, int maxStrokeCount)
{
    return PRC_InitInputPattern_Common(pattern, buffer, strokes, maxPointCount, maxStrokeCount);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_InitInputPatternEx_Superfine

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
PRC_InitInputPatternEx_Superfine(PRCInputPattern_Superfine *pattern,
                                 void *buffer,
                                 const PRCStrokes *strokes,
                                 int maxPointCount,
                                 int maxStrokeCount, const PRCInputPatternParam_Superfine *param)
{
    return PRC_InitInputPatternEx_Common(pattern, buffer, strokes, maxPointCount, maxStrokeCount,
                                         param);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognitionBufferSizeEx_Superfine

  Description:  Calculates the work area size required for recognition algorithm.
                comparison.

  Arguments:    maxPointCount   upper limit of input points (includes pen up marker)
                maxStrokeCount  upper limit of stroke count
                protoDB         sample DB
                param           parameters for recognition processing

  Returns:      required memory capacity for recognition algorithm
 *---------------------------------------------------------------------------*/
u32
 
 
PRC_GetRecognitionBufferSizeEx_Superfine(int maxPointCount,
                                         int maxStrokeCount,
                                         const PRCPrototypeDB_Superfine *protoDB,
                                         const PRCRecognizeParam_Superfine *param);

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognitionBufferSize_Superfine

  Description:  Calculates the work area size required for recognition algorithm.
                comparison.

  Arguments:    maxPointCount   upper limit of input points (includes pen up marker)
                maxStrokeCount  upper limit of stroke count
                protoDB         sample DB

  Returns:      required memory capacity for recognition algorithm
 *---------------------------------------------------------------------------*/
static inline u32
PRC_GetRecognitionBufferSize_Superfine(int maxPointCount,
                                       int maxStrokeCount, const PRCPrototypeDB_Superfine *protoDB)
{
    return PRC_GetRecognitionBufferSizeEx_Superfine(maxPointCount, maxStrokeCount, protoDB, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognizedEntriesEx_Superfine

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
 
 
PRC_GetRecognizedEntriesEx_Superfine(PRCPrototypeEntry **resultEntries,
                                     fx32 *resultScores,
                                     int numRanking,
                                     void *buffer,
                                     const PRCInputPattern_Superfine *input,
                                     const PRCPrototypeDB_Superfine *protoDB,
                                     u32 kindMask, const PRCRecognizeParam_Superfine *param);

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognizedEntries_Superfine

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
PRC_GetRecognizedEntries_Superfine(PRCPrototypeEntry **resultEntries,
                                   fx32 *resultScores,
                                   int numRanking,
                                   void *buffer,
                                   const PRCInputPattern_Superfine *input,
                                   const PRCPrototypeDB_Superfine *protoDB)
{
    return PRC_GetRecognizedEntriesEx_Superfine(resultEntries, resultScores, numRanking, buffer,
                                                input, protoDB, PRC_KIND_ALL, NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognizedEntryEx_Superfine

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
PRC_GetRecognizedEntryEx_Superfine(PRCPrototypeEntry **resultEntry,
                                   void *buffer,
                                   const PRCInputPattern_Superfine *input,
                                   const PRCPrototypeDB_Superfine *protoDB,
                                   u32 kindMask, const PRCRecognizeParam_Superfine *param)
{
    fx32    score;
    (void)PRC_GetRecognizedEntriesEx_Superfine(resultEntry, &score, 1, buffer, input, protoDB,
                                               kindMask, param);
    return score;
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetRecognizedEntry_Superfine

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
PRC_GetRecognizedEntry_Superfine(PRCPrototypeEntry **resultEntry,
                                 void *buffer,
                                 const PRCInputPattern_Superfine *input,
                                 const PRCPrototypeDB_Superfine *protoDB)
{
    return PRC_GetRecognizedEntryEx_Superfine(resultEntry, buffer, input, protoDB, PRC_KIND_ALL,
                                              NULL);
}

/*---------------------------------------------------------------------------*
  Name:         PRC_GetInputPatternStrokes_Superfine

  Description:  Obtains dot sequence data from PRCInputPattern structure.

  Arguments:    strokes         dot sequence data obtained
                                Overwriting is not permitted.
                input           input pattern

  Returns:      None.
 *---------------------------------------------------------------------------*/
static inline void
PRC_GetInputPatternStrokes_Superfine(PRCStrokes *strokes, const PRCInputPattern_Superfine *input)
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
#define PRC_DEFAULT_ALGORITHM "Superfine"

/*---------------------------------------------------------------------------*
  Parameters for Sample DB Expansion
 *---------------------------------------------------------------------------*/
typedef PRCPrototypeDBParam_Superfine PRCPrototypeDBParam;

/*---------------------------------------------------------------------------*
  Parameters for Input Pattern Interpretation
 *---------------------------------------------------------------------------*/
typedef PRCInputPatternParam_Superfine PRCInputPatternParam;

/*---------------------------------------------------------------------------*
  Recognition Pattern of Input Origin
 *---------------------------------------------------------------------------*/
typedef PRCInputPattern_Superfine PRCInputPattern;

/*---------------------------------------------------------------------------*
  Sample DB Expanded in Memory
 *---------------------------------------------------------------------------*/
typedef PRCPrototypeDB_Superfine PRCPrototypeDB;

/*---------------------------------------------------------------------------*
  Parameters for Recognition Processing
 *---------------------------------------------------------------------------*/
typedef PRCRecognizeParam_Superfine PRCRecognizeParam;


/*---------------------------------------------------------------------------*
  Functions
 *---------------------------------------------------------------------------*/
static inline void PRC_Init(void)
{
    PRC_Init_Superfine();
}

static inline u32 PRC_GetPrototypeDBBufferSize(const PRCPrototypeList *prototypeList)
{
    return PRC_GetPrototypeDBBufferSize_Superfine(prototypeList);
}

static inline u32
PRC_GetPrototypeDBBufferSizeEx(const PRCPrototypeList *prototypeList,
                               u32 kindMask,
                               BOOL ignoreDisabledEntries, const PRCPrototypeDBParam *param)
{
    return PRC_GetPrototypeDBBufferSizeEx_Superfine(prototypeList, kindMask, ignoreDisabledEntries,
                                                    param);
}

static inline BOOL
PRC_InitPrototypeDB(PRCPrototypeDB *protoDB, void *buffer, const PRCPrototypeList *prototypeList)
{
    return PRC_InitPrototypeDB_Superfine(protoDB, buffer, prototypeList);
}

static inline BOOL
PRC_InitPrototypeDBEx(PRCPrototypeDB *protoDB,
                      void *buffer,
                      const PRCPrototypeList *prototypeList,
                      u32 kindMask, BOOL ignoreDisabledEntries, const PRCPrototypeDBParam *param)
{
    return PRC_InitPrototypeDBEx_Superfine(protoDB, buffer, prototypeList, kindMask,
                                           ignoreDisabledEntries, param);
}

static inline u32 PRC_GetInputPatternBufferSize(int maxPointCount, int maxStrokeCount)
{
    return PRC_GetInputPatternBufferSize_Superfine(maxPointCount, maxStrokeCount);
}

static inline BOOL
PRC_InitInputPattern(PRCInputPattern *pattern,
                     void *buffer, const PRCStrokes *strokes, int maxPointCount, int maxStrokeCount)
{
    return PRC_InitInputPattern_Superfine(pattern, buffer, strokes, maxPointCount, maxStrokeCount);
}

static inline BOOL
PRC_InitInputPatternEx(PRCInputPattern *pattern,
                       void *buffer,
                       const PRCStrokes *strokes,
                       int maxPointCount, int maxStrokeCount, const PRCInputPatternParam *param)
{
    return PRC_InitInputPatternEx_Superfine(pattern, buffer, strokes, maxPointCount, maxStrokeCount,
                                            param);
}

static inline u32
PRC_GetRecognitionBufferSize(int maxPointCount,
                             int maxStrokeCount, const PRCPrototypeDB_Superfine *protoDB)
{
    return PRC_GetRecognitionBufferSize_Superfine(maxPointCount, maxStrokeCount, protoDB);
}

static inline u32
PRC_GetRecognitionBufferSizeEx(int maxPointCount,
                               int maxStrokeCount,
                               const PRCPrototypeDB_Superfine *protoDB,
                               const PRCRecognizeParam_Superfine *param)
{
    return PRC_GetRecognitionBufferSizeEx_Superfine(maxPointCount, maxStrokeCount, protoDB, param);
}

static inline fx32
PRC_GetRecognizedEntry(PRCPrototypeEntry **resultEntry,
                       void *buffer, const PRCInputPattern *input, const PRCPrototypeDB *protoDB)
{
    return PRC_GetRecognizedEntry_Superfine(resultEntry, buffer, input, protoDB);
}

static inline fx32
PRC_GetRecognizedEntryEx(PRCPrototypeEntry **resultEntry,
                         void *buffer,
                         const PRCInputPattern *input,
                         const PRCPrototypeDB *protoDB,
                         u32 kindMask, const PRCRecognizeParam *param)
{
    return PRC_GetRecognizedEntryEx_Superfine(resultEntry, buffer, input, protoDB, kindMask, param);
}

static inline int
PRC_GetRecognizedEntries(PRCPrototypeEntry **resultEntries,
                         fx32 *resultScores,
                         int numRanking,
                         void *buffer, const PRCInputPattern *input, const PRCPrototypeDB *protoDB)
{
    return PRC_GetRecognizedEntries_Superfine(resultEntries, resultScores, numRanking, buffer,
                                              input, protoDB);
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
    return PRC_GetRecognizedEntriesEx_Superfine(resultEntries, resultScores, numRanking, buffer,
                                                input, protoDB, kindMask, param);
}

static inline void PRC_GetInputPatternStrokes(PRCStrokes *strokes, const PRCInputPattern *input)
{
    PRC_GetInputPatternStrokes_Superfine(strokes, input);
}

#endif // PRC_DEFAULT_ALGORITHM




#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_PRC_ALGO_SUPERFINE_H_ */
#endif
