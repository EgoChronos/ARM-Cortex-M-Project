/*
 * SysTick.h
 *
 *  Created on: 29 Jul 2024
 *      Author: ahmed
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                             PreProcessor Macros                             *
 *******************************************************************************/


/*******************************************************************************
 *                         User Defined Data Types                             *
 *******************************************************************************/


/*******************************************************************************
 *                            Functions Prototypes                             *
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
void SysTick_Init(uint16 a_TimeInMilliSeconds);

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
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

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
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));

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
void SysTick_Stop(void);

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
void SysTick_Start(void);

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
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
