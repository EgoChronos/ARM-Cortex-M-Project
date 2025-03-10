/*
 * SysTick.c
 *
 *  Created on: 29 Jul 2024
 *      Author: ahmed
 */

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include"SysTick.h"
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

/*******************************************************************************
 *                             PreProcessor Macros                             *
 *******************************************************************************/
#define SYS_FREQ                            16000000
#define SYSTICK_COUNT_FLAG_BIT_MASK         0x00010000
#define SYSTICK_CLEAR_CTRL_BITS_MASK        0xFFFFFFF8
#define SYSTICK_ENABLE_WITH_SYSTEM_CLK      0x05
#define SYSTICK_ENABLE_WITH_INT_SYSTEM_CLK  0x07
#define SYSTICK_INITIAL_VALUE               0
#define SYSTICK_ENABLE_DISABLE_BIT_POS      0
/*******************************************************************************
 *                          Private Global Variables                           *
 *******************************************************************************/
/*variable to hold the callback fcn address*/
static volatile void (*callbackFcn_ptr) (void);

/*******************************************************************************
 *                         Public Functions Definitions                        *
 *******************************************************************************/

/*********************************************************************
 *   Service Name: SysTick_Init
 *  Sync/Async: Asynchronous
 *  Reentrancy: Non-reentrant
 *  Parameters (in): a_TimeInMilliSeconds - time of interrupt in mili-seconds
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Initialize the SysTick timer to generate intterrupt every specified
    time in milliseconds
 **********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    /*  1. Program reload value.
        2. Clear current value.
        3. Program Control and Status register */

    SYSTICK_RELOAD_REG = (((SYS_FREQ / 1000) * a_TimeInMilliSeconds) - 1);
    SYSTICK_CURRENT_REG = SYSTICK_INITIAL_VALUE;
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG |= SYSTICK_ENABLE_WITH_INT_SYSTEM_CLK;
}

/*********************************************************************
 *   Service Name: SysTick_StartBusyWait
 *  Sync/Async: Synchronous
 *  Reentrancy: non-reentrant
 *  Parameters (in): a_TimeInMilliSeconds - time of interrupt in mili-seconds
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Initialize the SysTick timer with the specified time in milliseconds
    using polling or busy-wait technique.
 **********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    /*  1. Program reload value.
        2. Clear current value.
        3. Program Control and Status register */

    SYSTICK_RELOAD_REG = (((SYS_FREQ / 1000) * a_TimeInMilliSeconds) - 1);
    SYSTICK_CURRENT_REG = SYSTICK_INITIAL_VALUE;
    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG = (SYSTICK_CTRL_REG &  SYSTICK_CLEAR_CTRL_BITS_MASK) | (SYSTICK_ENABLE_WITH_SYSTEM_CLK);

    /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value
     * COUNT flag is cleared after read the CTRL register value */
    while (!(SYSTICK_CTRL_REG & SYSTICK_COUNT_FLAG_BIT_MASK));

    /*stops the timer*/
    CLEAR_BIT(SYSTICK_CTRL_REG, SYSTICK_ENABLE_DISABLE_BIT_POS);
}

/*********************************************************************
 *   Service Name: SysTick_Handler
 *  Sync/Async: Synchronous
 *  Reentrancy: non-reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Handler for SysTick interrupt use to call the call-back function
 **********************************************************************/
void SysTick_Handler(void)
{
    (*callbackFcn_ptr)();
}

/*********************************************************************
 *   Service Name: SysTick_SetCallBack
 *  Sync/Async: Synchronous
 *  Reentrancy: non-reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to setup the SysTick Timer call back to be
    executed in SysTick Handler
 **********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{
    callbackFcn_ptr = Ptr2Func;
}

/*********************************************************************
 *   Service Name: SysTick_Stop
 *  Sync/Async: Synchronous
 *  Reentrancy: non-reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Stop the SysTick timer
 **********************************************************************/
void SysTick_Stop(void)
{
    CLEAR_BIT(SYSTICK_CTRL_REG, SYSTICK_ENABLE_DISABLE_BIT_POS);
}

/*********************************************************************
 * Service Name: SysTick_Start
 *  Sync/Async: Synchronous
 *  Reentrancy: non-reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Start/Resume the SysTick timer
 **********************************************************************/
void SysTick_Start(void)
{
    SET_BIT(SYSTICK_CTRL_REG, SYSTICK_ENABLE_DISABLE_BIT_POS);
}
/*********************************************************************
 *   Service Name: SysTick_DeInit
 *  Sync/Async: Synchronous
 *  Reentrancy: non-reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to De-initialize the SysTick Timer
 **********************************************************************/
void SysTick_DeInit(void)
{
    /*  1. Clear Control and Status register
     *  2. Clear current value. */

    /* Clear the SysTick Control Register
     * Disable the SysTick Timer (ENABLE = 0)
     * Disable SysTick Interrupt (INTEN = 0) */
      SYSTICK_CTRL_REG &= SYSTICK_CLEAR_CTRL_BITS_MASK;

    /*Clear the current Value register*/
    SYSTICK_CURRENT_REG = SYSTICK_INITIAL_VALUE;

    /*read the count flag to clear it*/
    if (SYSTICK_CTRL_REG & SYSTICK_COUNT_FLAG_BIT_MASK);
}
