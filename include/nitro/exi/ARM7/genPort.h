/*---------------------------------------------------------------------------*
  Project:  NitroSDK - EXI
  File:     genPort.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: genPort.h,v $
  Revision 1.6  2006/01/18 02:11:21  kitase_hirotake
  do-indent

  Revision 1.5  2005/02/28 05:26:13  yosizaki
  do-indent.

  Revision 1.4  2004/06/11 11:27:53  terui
  Add EXI_GPIO_PADFOLD definition.

  Revision 1.3  2004/03/16 13:03:15  takano_makoto
  Add EXI_GPIO_PADDEBUG for DEBUG button.

  Revision 1.2  2004/02/28 09:50:22  yasu
  add EXI GPIO access API for ARM7

  Revision 1.1  2004/02/18 01:21:00  yada
  firstRelease


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_EXI_GENPORT_H_
#define NITRO_EXI_GENPORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/types.h"
#include "nitro/memorymap.h"

// GPIO I/F mode (RCNT0_L:d15,d14)
typedef enum
{
    EXI_GPIOIF_SERIAL = 0x0000,
    EXI_GPIOIF_UNDEF = REG_EXI_RCNT0_L_RE0_MASK,
    EXI_GPIOIF_GPIO = REG_EXI_RCNT0_L_RE1_MASK,
    EXI_GPIOIF_JOY = REG_EXI_RCNT0_L_RE1_MASK | REG_EXI_RCNT0_L_RE0_MASK
}
EXIGpioIF;

#define EXI_GPIOIF_MASK (REG_EXI_RCNT0_L_RE1_MASK|REG_EXI_RCNT0_L_RE0_MASK)

// Port assign for GPIO RCNT0 & 1
#define EXI_GPIO_PADX       REG_EXI_RCNT0_H_DATA_R0_MASK
#define EXI_GPIO_PADY       REG_EXI_RCNT0_H_DATA_R1_MASK
#define EXI_GPIO_PADDEBUG   REG_EXI_RCNT0_H_DATA_R3_MASK
#define EXI_GPIO_TOUCHPANEL REG_EXI_RCNT0_H_DATA_R6_MASK
#define EXI_GPIO_GPCOMM_DAT REG_EXI_RCNT0_H_DATA_R7_MASK
#define EXI_GPIO_GPCOMM_CLK REG_EXI_RCNT1_DATA_RB_MASK

#if	defined( SDK_TEG )
#define	EXI_GPIO_PADFOLD	REG_EXI_RCNT0_H_DATA_R2_MASK
#elif	defined( SDK_TS )
#define	EXI_GPIO_PADFOLD	REG_EXI_RCNT0_H_DATA_R7_MASK
#endif

void    EXIi_SelectRcnt(EXIGpioIF type);
void    EXIi_SetBitRcnt0L(u16 mask, u16 data);
void    EXIi_SetBitRcnt0H(u16 mask, u16 data);
void    EXIi_SetBitRcnt1(u16 mask, u16 data);
u16     EXIi_GetBitRcnt0L(u16 mask);
u16     EXIi_GetBitRcnt0H(u16 mask);
u16     EXIi_GetBitRcnt1(u16 mask);
void    EXIi_SendBitRcnt0L(u16 mask, u16 data);
void    EXIi_SendBitRcnt0H(u16 mask, u16 data);
void    EXIi_SendBitRcnt1(u16 mask, u16 data);
u16     EXIi_RecvBitRcnt0L(u16 mask);
u16     EXIi_RecvBitRcnt0H(u16 mask);
u16     EXIi_RecvBitRcnt1(u16 mask);


/*---------------------------------------------------------------------------*
  Name:         EXIi_SetRcnt0L

  Description:  Set value RCNT0_L register

  Arguments:    value to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void EXIi_SetRcnt0L(u16 val)
{
    *(REGType16 *)REG_RCNT0_L_ADDR = val;
}

/*---------------------------------------------------------------------------*
  Name:         EXIi_SetRcnt0H

  Description:  Set value RCNT0_H register

  Arguments:    value to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void EXIi_SetRcnt0H(u16 val)
{
    *(REGType16 *)REG_RCNT0_H_ADDR = val;
}

/*---------------------------------------------------------------------------*
  Name:         EXIi_SetRcnt1

  Description:  Set value RCNT1 register

  Arguments:    value to set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void EXIi_SetRcnt1(u16 val)
{
    *(REGType16 *)REG_RCNT1_ADDR = val;
}

/*---------------------------------------------------------------------------*
  Name:         EXIi_GetRcnt0L

  Description:  Get value from RCNT0_L register

  Arguments:    none

  Returns:      read value
 *---------------------------------------------------------------------------*/
static inline u16 EXIi_GetRcnt0L(void)
{
    return *(REGType16 *)REG_RCNT0_L_ADDR;
}

/*---------------------------------------------------------------------------*
  Name:         EXIi_GetRcnt0H

  Description:  Get value from RCNT0_H register

  Arguments:    none

  Returns:      read value
 *---------------------------------------------------------------------------*/
static inline u16 EXIi_GetRcnt0H(void)
{
    return *(REGType16 *)REG_RCNT0_H_ADDR;
}

/*---------------------------------------------------------------------------*
  Name:         EXIi_GetRcnt1

  Description:  Get value from RCNT1 register

  Arguments:    none

  Returns:      read value
 *---------------------------------------------------------------------------*/
static inline u16 EXIi_GetRcnt1(void)
{
    return *(REGType16 *)REG_RCNT1_ADDR;
}



#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_EXI_GENPORT_H_ */
#endif
