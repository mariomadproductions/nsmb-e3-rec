/*---------------------------------------------------------------------------*
  Project:  NitroSDK - MATH -
  File:     math/fft.h

  Copyright 2003-2007 Nintendo. All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: fft.h,v $
  Revision 1.4  2007/04/24 12:04:00  yosizaki
  Updated copyright.

  Revision 1.3  2007/04/20 09:59:46  yosizaki
  Fixed include dependency.

  Revision 1.2  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.1  2005/05/13 09:23:56  seiki_masashi
  Added FFT function

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_MATH_FFT_H_
#define NITRO_MATH_FFT_H_

#include "nitro/types.h"
#include "nitro/fx/fx.h"

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
// Type Definitions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Function Declarations
//----------------------------------------------------------------------------

/*---------------------------------------------------------------------------*
  Name:         MATH_MakeFFTSinTable

  Description:  Creates sine table used in fast Fourier transform.

  Arguments:    sinTable - Pointer to location storing 2^nShift * 3/4  sine table
                nShift - log2 of the number of data

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_MakeFFTSinTable(fx16 *sinTable, u32 nShift);

/*---------------------------------------------------------------------------*
  Name:         MATHi_FFT

  Description:  Internal function that performs fast Fourier transform.

  Arguments:    data - Data to transform, with even-numbered data being real and odd-numbered data being imaginary.
                       The transformation result will be returned overwritten.
                nShift - log2 of the number of data
                sinTable - Sine value table based on a circle divided into equal sections; the number of sections is the number of data

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATHi_FFT(fx32 *data, u32 nShift, const fx16 *sinTable);

/*---------------------------------------------------------------------------*
  Name:         MATHi_IFFT

  Description:  Internal function that reverses the fast Fourier transform.

  Arguments:    data - Data to transform, with even-numbered data being real and odd-numbered data being imaginary.
                       The transformation result will be returned overwritten.
                nShift - log2 of the number of data
                sinTable - Sine value table based on a circle divided into equal sections; the number of sections is the number of data

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATHi_IFFT(fx32 *data, u32 nShift, const fx16 *sinTable);

/*---------------------------------------------------------------------------*
  Name:         MATH_FFT

  Description:  Performs fast Fourier transform.

  Arguments:    data - Data to transform, with even-numbered data being real and odd-numbered data being imaginary.
                       The transformation result will be returned overwritten.
                nShift - log2 of the number of data
                sinTable - Sine value table based on a circle divided into equal sections; the number of sections is the number of data

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_FFT(fx32 *data, u32 nShift, const fx16 *sinTable);

/*---------------------------------------------------------------------------*
  Name:         MATH_IFFT

  Description:  Performs the inverse transformation of fast Fourier transform.

  Arguments:    data - Data to transform, with even-numbered data being real and odd-numbered data being imaginary.
                       The transformation result will be returned overwritten.
                nShift - log2 of the number of data
                sinTable - Sine value table based on a circle divided into equal sections; the number of sections is the number of data

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_IFFT(fx32 *data, u32 nShift, const fx16 *sinTable);

/*---------------------------------------------------------------------------*
  Name:         MATH_FFTReal

  Description:  Performs fast Fourier transform.

  Arguments:    data - Data that includes only real number data.
                       The transformation result will be returned overwritten.
                nShift - log2 of the number of data
                sinTable - Sine value table based on a circle divided into equal sections; the number of sections is the number of data

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_FFTReal(fx32 *data, u32 nShift, const fx16 *sinTable, const fx16 *sinTable2);

/*---------------------------------------------------------------------------*
  Name:         MATH_IFFTReal

  Description:  Performs the inverse transformation of fast Fourier transform.

  Arguments:    data - Data that includes only real number data.
                       The transformation result will be returned overwritten.
                nShift - log2 of the number of data
                sinTable - Sine value table based on a circle divided into equal sections; the number of sections is the number of data

  Returns:      None.
 *---------------------------------------------------------------------------*/
void    MATH_IFFTReal(fx32 *data, u32 nShift, const fx16 *sinTable, const fx16 *sinTable2);


#ifdef __cplusplus
}/* extern "C" */
#endif

/* NITRO_MATH_FFT_H_ */
#endif
