/*---------------------------------------------------------------------------*
  Project:  NitroSDK - OS - include
  File:     interrupt.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: interrupt.h,v $
  Revision 1.62  2006/07/05 09:13:49  yosizaki
  fix about include header.

  Revision 1.61  2006/01/18 02:11:19  kitase_hirotake
  do-indent

  Revision 1.60  2005/07/19 06:05:47  yada
  add irq stack check

  Revision 1.59  2005/03/01 01:57:00  yosizaki
  Revised copyright year

  Revision 1.58  2005/02/28 05:26:01  yosizaki
  do-indent.

  Revision 1.57  2004/12/02 07:16:44  yada
  OS_IE_USER_FLAG0, OS_IE_USER_FLAG1 become also available on ARM9

  Revision 1.56  2004/11/02 10:25:47  yada
  just fix comment

  Revision 1.55  2004/09/14 06:04:08  yada
  only fix comment

  Revision 1.54  2004/09/02 06:26:13  yada
  only change comment

  Revision 1.53  2004/08/16 04:22:59  yada
  in ARM9, no hook in VBlank interrupt

  Revision 1.52  2004/08/10 12:15:39  yada
  VBlank counter is in shared area

  Revision 1.51  2004/08/10 08:00:02  yada
  add OS_GetVBlankCount()
  fix comment

  Revision 1.50  2004/06/28 06:37:36  yada
  delete unused define

  Revision 1.49  2004/05/25 10:43:43  yada
  disable IME before touch IE or IF

  Revision 1.48  2004/05/24 04:48:29  yada
  OS_WaitIntr() -> OS_WaitInterrupt()

  Revision 1.47  2004/05/10 11:25:43  yada
  add #define guard to OSIrqMask

  Revision 1.46  2004/05/01 05:47:31  yada
  OS_WaitInterrupt->OS_WaitIrq, OS_WaitAnyInterrupt->OS_WaitAnyIrq

  Revision 1.45  2004/04/30 08:11:06  yada
  add OS_WaitAnyInterrupt

  Revision 1.44  2004/04/30 02:20:31  yada
  add OS_WaitInterrupt()

  Revision 1.43  2004/04/21 12:38:48  yasu
  add OS_IE_USER_FLAG0,1

  Revision 1.42  2004/04/15 12:50:34  yada
  divide OS_IrqHandler to 2 function

  Revision 1.41  2004/04/07 02:03:17  yada
  fix header comment

  Revision 1.40  2004/04/06 09:00:49  yada
  add OS_ClearIrqFlag(), OS_GetIrqFlag()
  add function comments

  Revision 1.39  2004/03/18 12:55:26  yada
  Changed the files to include from nitro.h to only the necessary ones.

  Revision 1.38  2004/03/16 07:08:38  yada
  Revised IRQ table. Added a dummy.

  Revision 1.37  2004/03/04 12:37:04  yasu
  add some aliases ARM7 to ARM9

  Revision 1.36  2004/02/28 11:51:20  yasu
  fix OS_DisableIrqMask

  Revision 1.35  2004/02/28 09:51:43  yasu
  expend ARM7 IRQ table

  Revision 1.34  2004/02/27 01:10:19  yasu
  merge ARM7's register list

  Revision 1.33  2004/02/13 01:29:19  yada
  Sorting include files accordingly for ARM9 and AMR7

  Revision 1.32  2004/02/05 07:09:03  yasu
  change SDK prefix iris -> nitro

  Revision 1.31  2004/02/03 11:19:37  yada
  Added OSi_EnterTimerCallback()

  Revision 1.30  2004/02/02 05:33:46  yada
  Changed variable and function names.

  Revision 1.29  2004/01/29 08:26:05  yada
  (none)

  Revision 1.28  2004/01/18 04:47:31  yada
  Reformed indents, etc.

  Revision 1.27  2004/01/17 11:44:20  yada
  Created Async mode for DMA transfers

  Revision 1.26  2004/01/17 02:28:38  nishida_kenji
  convert 'inline' to 'static inline' in header files

  Revision 1.25  2004/01/09 10:41:59  yada
  *** empty log message ***

  Revision 1.24  2004/01/09 10:38:42  yada
  Added interface for clearing the interrupt check flag

  Revision 1.23  2003/12/25 07:29:22  yada
  Changes as per unified type rules

  Revision 1.22  2003/12/25 00:19:29  nishida_kenji
  convert INLINE to inline

  Revision 1.21  2003/12/16 05:29:41  yasu
  Corrected number of interrupt vectors

  Revision 1.20  2003/12/11 05:29:01  yada
  Corrected return type of OS_ResetRequestIRQMask() from u32 to OS_IntrMask

  Revision 1.19  2003/12/08 12:12:12  yada
  Made changes to the file to include

  Revision 1.18  2003/11/30 04:18:22  yasu
  Put CPU CPSR settings-related description in cpsr.h

  Revision 1.17  2003/11/28 12:18:18  yasu
  Added 'define' for OS_IRQHandler size check

  Revision 1.16  2003/11/25 10:59:59  yada
  (none)

  Revision 1.15  2003/11/18 12:44:27  yada
  OS_GetRequestInterruptsMask -> OS_GetRequestInterruptMask  (deleted the 's')

  Revision 1.14  2003/11/14 04:58:11  yada
  Changed the register access macro from REG_XXX to reg_XXX

  Revision 1.13  2003/11/13 04:04:10  yada
  Removed SDK_ASSERT() and other definitions that are defined in misc.h

  Revision 1.12  2003/11/12 06:36:06  yada
  Corrected spelling errors. Especially the "Interrupt" error.

  Revision 1.11  2003/11/11 12:56:42  yada
  (none)

  Revision 1.10  2003/11/11 12:27:28  yada
  Moved some system call portions from interrupt.h to systemCall.h

  Revision 1.9  2003/11/11 05:47:24  yada
  Handle master interrupts with BOOL

  Revision 1.8  2003/11/10 04:15:12  yasu
  Interrupt bit to 0S_InterruptBit

  Revision 1.7  2003/11/10 02:33:00  yasu
  Added  'interrupt table'

  Revision 1.6  2003/11/07 07:51:46  yada
  Corrected OS_IME_DISABLE value

  Revision 1.5  2003/11/06 13:36:01  yasu
  Changed (u32)1 expression to 1UL

  Revision 1.4  2003/11/06 10:36:16  yada
  Corrected interrupt bit definition mistake

  Revision 1.3  2003/11/05 01:03:18  yada
  Made the cast more strict At least make it so no warnings appear.

  Revision 1.2  2003/11/04 09:08:43  yada
  (none)

  Revision 1.1  2003/10/31 04:12:03  yada
  Created initial version

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_OS_INTERRUPT_H_
#define NITRO_OS_INTERRUPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nitro/misc.h"
#include "nitro/types.h"
#include "nitro/memorymap.h"
#include "nitro/ioreg.h"
#include "nitro/os/common/thread.h"

//---- for DMA, TIMER
void    OSi_EnterDmaCallback(u32 dmaNo, void (*callback) (void *), void *arg);
void    OSi_EnterTimerCallback(u32 timerNo, void (*callback) (void *), void *arg);

//----------------------------------------------------------------------
//                  ENABLE/DISABLE flag for IME
//----------------------------------------------------------------------
#define OS_IME_DISABLE      (0UL << REG_OS_IME_IME_SHIFT)
#define OS_IME_ENABLE       (1UL << REG_OS_IME_IME_SHIFT)

//----------------------------------------------------------------------
//                  IE/IF flags
//----------------------------------------------------------------------
#define OS_IE_V_BLANK       (1UL << REG_OS_IE_VB_SHIFT) // VBlank
#define OS_IE_H_BLANK       (1UL << REG_OS_IE_HB_SHIFT) // HBlank
#define OS_IE_V_COUNT       (1UL << REG_OS_IE_VE_SHIFT) // VCounter
#define OS_IE_TIMER0        (1UL << REG_OS_IE_T0_SHIFT) // timer0
#define OS_IE_TIMER1        (1UL << REG_OS_IE_T1_SHIFT) // timer1
#define OS_IE_TIMER2        (1UL << REG_OS_IE_T2_SHIFT) // timer2
#define OS_IE_TIMER3        (1UL << REG_OS_IE_T3_SHIFT) // timer3
#define OS_IE_SIO           (1UL << 7                 ) // serial communication (will not occur)
#define OS_IE_DMA0          (1UL << REG_OS_IE_D0_SHIFT) // DMA0
#define OS_IE_DMA1          (1UL << REG_OS_IE_D1_SHIFT) // DMA1
#define OS_IE_DMA2          (1UL << REG_OS_IE_D2_SHIFT) // DMA2
#define OS_IE_DMA3          (1UL << REG_OS_IE_D3_SHIFT) // DMA3
#define OS_IE_KEY           (1UL << REG_OS_IE_K_SHIFT)  // key
#define OS_IE_CARTRIDGE     (1UL << REG_OS_IE_I_D_SHIFT)        // cartridge
#define OS_IE_SUBP          (1UL << REG_OS_IE_A7_SHIFT) // sub processor
#define OS_IE_SPFIFO_SEND   (1UL << REG_OS_IE_IFE_SHIFT)        // sub processor send FIFO empty
#define OS_IE_SPFIFO_RECV   (1UL << REG_OS_IE_IFN_SHIFT)        // sub processor receive FIFO not empty
#define OS_IE_CARD_DATA     (1UL << REG_OS_IE_MC_SHIFT) // card data transfer finish
#define OS_IE_CARD_IREQ     (1UL << REG_OS_IE_MI_SHIFT) // card IREQ

#ifdef SDK_ARM9
#define OS_IE_GXFIFO        (1UL << REG_OS_IE_GF_SHIFT) // geometry command FIFO
#define OS_IRQ_TABLE_MAX     22

#else  //SDK_ARM7
#define OS_IE_POWERMAN      (1UL << REG_OS_IE_PM_SHIFT) // Power Management IC
#define OS_IE_SPI           (1UL << REG_OS_IE_SPI_SHIFT)        // SPI data transfer
#define OS_IE_WIRELESS      (1UL << REG_OS_IE_WL_SHIFT) // Wireless module
#define OS_IRQ_TABLE_MAX     25

// Aliases to SUBP->MAINP
#define OS_IE_MAINP             OS_IE_SUBP
#define OS_IE_MPFIFO_SEND       OS_IE_SPFIFO_SEND
#define OS_IE_MPFIFO_RECV       OS_IE_SPFIFO_RECV
#define REG_OS_IE_A9_SHIFT      REG_OS_IE_A7_SHIFT
#endif

// Aliases to common naming
#define OS_IE_FIFO_SEND         OS_IE_SPFIFO_SEND
#define OS_IE_FIFO_RECV         OS_IE_SPFIFO_RECV

// Dummy irq check flag for user own use
#define OS_IE_USER_FLAG0_SHIFT  31
#define OS_IE_USER_FLAG1_SHIFT  30
#define OS_IE_USER_FLAG0        (1UL << OS_IE_USER_FLAG0_SHIFT) // user 0
#define OS_IE_USER_FLAG1        (1UL << OS_IE_USER_FLAG1_SHIFT) // user 1


//---- used for internal functions
#define OSi_IRQCALLBACK_NO_DMA0    0
#define OSi_IRQCALLBACK_NO_DMA1    1
#define OSi_IRQCALLBACK_NO_DMA2    2
#define OSi_IRQCALLBACK_NO_DMA3    3
#define OSi_IRQCALLBACK_NO_TIMER0  4
#define OSi_IRQCALLBACK_NO_TIMER1  5
#define OSi_IRQCALLBACK_NO_TIMER2  6
#define OSi_IRQCALLBACK_NO_TIMER3  7
#ifdef SDK_ARM7
#define OSi_IRQCALLBACK_NO_VBLANK  8
#endif
#ifdef SDK_ARM9
#define OSi_IRQCALLBACK_NUM       (7+1)
#else
#define OSi_IRQCALLBACK_NUM       (8+1)
#endif

//----------------------------------------------------------------
#define OS_IRQ_MAIN_BUFFER_SIZE         (0x200)


//---- interrupt handler type
typedef void (*OSIrqFunction) (void);

//---- for irq callback (internal use)
typedef struct
{
    void    (*func) (void *);
    u32     enable;
    void   *arg;
}
OSIrqCallbackInfo;

//---- irq factor type define
#ifndef OSi_OSIRQMASK_DEFINED
typedef u32 OSIrqMask;
#define OSi_OSIRQMASK_DEFINED
#endif

//---- table of irq functions
extern OSIrqFunction OS_IRQTable[];

//---- for DMA, TIMER, VBLANK(arm7) interrupt */
extern OSIrqCallbackInfo OSi_IrqCallbackInfo[OSi_IRQCALLBACK_NUM];


void    OS_IrqDummy(void);
void    OS_IrqHandler(void);
void    OS_IrqHandler_ThreadSwitch(void);

//================================================================================
//              IRQ MASTER ENABLE
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_EnableIrq

  Description:  enable master enable

  Arguments:    None

  Returns:      previous state of master enable.
                OS_IME_ENABLE or OS_IME_DISABLE.
 *---------------------------------------------------------------------------*/
static inline BOOL OS_EnableIrq(void)
{
    u16     prep = reg_OS_IME;
    reg_OS_IME = OS_IME_ENABLE;
    return (BOOL)prep;
}

/*---------------------------------------------------------------------------*
  Name:         OS_DisableIrq

  Description:  disable master enable

  Arguments:    None

  Returns:      previous status of master enable.
                OS_IME_ENABLE or OS_IME_DISABLE.
 *---------------------------------------------------------------------------*/
static inline BOOL OS_DisableIrq(void)
{
    u16     prep = reg_OS_IME;
    reg_OS_IME = OS_IME_DISABLE;
    return (BOOL)prep;
}

/*---------------------------------------------------------------------------*
  Name:         OS_RestoreIrq

  Description:  set master enable.
                this function is mainly used for restore previous state
                from OS_EnableIrq() or OS_DisableIrq().

  Arguments:    enable    OS_IME_ENABLE or OS_IME_DISABLE

  Returns:      previous state of master enable
  
 *---------------------------------------------------------------------------*/
static inline BOOL OS_RestoreIrq(BOOL enable)
{
    u16     prep = reg_OS_IME;
    reg_OS_IME = (u16)enable;
    return (BOOL)prep;
}


//================================================================================
//              IRQ FACTORS
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_SetIrqMask

  Description:  set irq factor

  Arguments:    intr        irq factor

  Returns:      previous factors
 *---------------------------------------------------------------------------*/
OSIrqMask OS_SetIrqMask(OSIrqMask intr);

/*---------------------------------------------------------------------------*
  Name:         OS_GetIrqMask

  Description:  get irq factor

  Arguments:    None

  Returns:      irq factor which is set now
 *---------------------------------------------------------------------------*/
static inline OSIrqMask OS_GetIrqMask(void)
{
    return reg_OS_IE;
}

/*---------------------------------------------------------------------------*
  Name:         OS_EnableIrqMask

  Description:  set specified irq factor

  Arguments:    intr        irq factor

  Returns:      previous factors
 *---------------------------------------------------------------------------*/
OSIrqMask OS_EnableIrqMask(OSIrqMask intr);

/*---------------------------------------------------------------------------*
  Name:         OS_DisableIrqMask

  Description:  unset specified irq factor

  Arguments:    intr        irq factor

  Returns:      previous factors
 *---------------------------------------------------------------------------*/
OSIrqMask OS_DisableIrqMask(OSIrqMask intr);

//================================================================================
//              IF
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_ResetRequestIrqMask

  Description:  reset IF bit
                (setting bit causes to clear bit for interrupt)

  Arguments:    intr        irq factor

  Returns:      previous factors
 *---------------------------------------------------------------------------*/
OSIrqMask OS_ResetRequestIrqMask(OSIrqMask intr);

/*---------------------------------------------------------------------------*
  Name:         OS_GetReuestIrqMask

  Description:  get IF bit

  Arguments:    None

  Returns:      value of IF
 *---------------------------------------------------------------------------*/
static inline OSIrqMask OS_GetRequestIrqMask(void)
{
    return reg_OS_IF;
}

//================================================================================
//              IRQ HANDLER
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_InitIrqTable

  Description:  initialize irq table

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_InitIrqTable(void);

/*---------------------------------------------------------------------------*
  Name:         OS_SetIrqFunction

  Description:  set irq handler for specified interrupt

  Arguments:    intrBit    irq factor
                function   irq handler for specified interrupt

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_SetIrqFunction(OSIrqMask intrBit, OSIrqFunction function);


/*---------------------------------------------------------------------------*
  Name:         OS_GetIrqFunction

  Description:  get irq handler for specified interrupt

  Arguments:    intrBit    irq factor

  Returns:      irq handler for specified interrupt
 *---------------------------------------------------------------------------*/
OSIrqFunction OS_GetIrqFunction(OSIrqMask intrBit);


//================================================================================
//              IRQ CHECK BUFFER
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_SetIrqCheckFlag

  Description:  set irq flag to check being called

  Arguments:    irq factors to be set

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void OS_SetIrqCheckFlag(OSIrqMask intr)
{
    *(vu32 *)HW_INTR_CHECK_BUF |= (u32)intr;
}

/*---------------------------------------------------------------------------*
  Name:         OS_ClearIrqCheckFlag

  Description:  clear irq flag stored in HW_INTR_CHECK_BUF

  Arguments:    irq factors to be cleared

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void OS_ClearIrqCheckFlag(OSIrqMask intr)
{
    *(vu32 *)HW_INTR_CHECK_BUF &= (u32)~intr;
}

/*---------------------------------------------------------------------------*
  Name:         OS_GetIrqCheckFlag

  Description:  get irq factors stored in HW_INTR_CHECK_BUF

  Arguments:    None

  Returns:      irq flags factors in HW_INTR_CHECK_BUG
 *---------------------------------------------------------------------------*/
static inline OSIrqMask OS_GetIrqCheckFlag(void)
{
    return *(OSIrqMask *)HW_INTR_CHECK_BUF;
}


//================================================================================
//              WAIT IRQ
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_WaitIrq

  Description:  wait specified interrupt
                the difference between OS_WaitIrq and OS_WaitInterrupt,
                in waiting interrupt
                OS_WaitIrq does switch thread,
                OS_WaitInterrupt doesn't switch thread.
                OS_WaitIrq wait by using OS_SleepThread() with threadQueue,
                OS_WaitInterrupt wait by using OS_Halt().
                if SDK_NO_THREAD defined, 2 functions become same.

  Arguments:    clear       TRUE if want to clear interrupt flag before wait
                            FALSE if not
                irqFlags    bit of interrupts to wait for

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_WaitIrq(BOOL clear, OSIrqMask irqFlags);

/*---------------------------------------------------------------------------*
  Name:         OS_WaitAnyIrq

  Description:  wait any interrupt
  
  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
void    OS_WaitAnyIrq(void);


//================================================================================
//              VBLANK COUNTER
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_GetVBlankCount

  Description:  get VBlankCount
  
  Arguments:    None

  Returns:      VBlankCount
 *---------------------------------------------------------------------------*/
static inline vu32 OS_GetVBlankCount(void)
{
    return *(vu32 *)HW_VBLANK_COUNT_BUF;
}

/*---------------------------------------------------------------------------*
  Name:         OSi_SetVBlankCount

  Description:  set VBlankCount
                *** internal function. don't use this.

  Arguments:    count : VBlankCount

  Returns:      None
 *---------------------------------------------------------------------------*/
static inline void OSi_SetVBlankCount(u32 count)
{
    *(u32 *)HW_VBLANK_COUNT_BUF = count;
}

//================================================================================
//              IRQ STACK CHECKER
//================================================================================
/*---------------------------------------------------------------------------*
  Name:         OS_SetIrqStackWarningOffset

  Description:  Set warning level for irq stack checker

  Arguments:    offset     offset from stack top. must be multiple of 4

  Returns:      None
 *---------------------------------------------------------------------------*/
extern void OS_SetIrqStackWarningOffset(u32 offset);

/*---------------------------------------------------------------------------*
  Name:         OS_GetIrqStackStatus

  Description:  check irq stack. check each CheckNUM.
                return result.

  Arguments:    None

  Returns:      0 (OS_STACK_NO_ERROR)        no error
                OS_STACK_OVERFLOW            overflow
                OS_STACK_ABOUT_TO_OVERFLOW   about to overflow
                OS_STACK_UNDERFLOW           underflow
 *---------------------------------------------------------------------------*/
extern OSStackStatus OS_GetIrqStackStatus(void);

/*---------------------------------------------------------------------------*
  Name:         OS_SetIrqStackChecker

  Description:  set irq stack check number to irq stack

  Arguments:    None

  Returns:      None
 *---------------------------------------------------------------------------*/
extern void OS_SetIrqStackChecker(void);

/*---------------------------------------------------------------------------*
  Name:         OS_CheckIrqStack

  Description:  check irq stack. check each CheckNum.
                if changed, display warning and halt.

  Arguments:    None

  Returns:      None.
                ( if error occurred, never return )
 *---------------------------------------------------------------------------*/
void    OSi_CheckIrqStack(char *file, int line);
#if !defined(SDK_FINALROM) && !defined(SDK_NO_MESSAGE)
#define  OS_CheckIrqStack()  OSi_CheckIrqStack( __FILE__, __LINE__ );
#else
#define  OS_CheckIrqStack()  ((void)0)
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

/* NITRO_OS_INTERRUPT_H_ */
#endif
