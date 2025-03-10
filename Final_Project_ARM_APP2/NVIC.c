/*
 * NVIC.c
 *
 *  Created on: 29 Jul 2024
 *      Author: ahmed
 */

#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"

#define NVIC_PRI0_REG_ADD                (uint32*)0xE000E400
#define NVIC_MICRO_TOTAL_INT_NUM                138
#define NVIC_SYS_IRQ_TOTAL_NUM                  16
#define NVIC_NUMBER_OF_INT_PRI_PER_REG          4
#define FIRST_INT_PRI_BIT_POS                   5
#define NUM_OF_BITS_BETWEEN_TWO_PRI_POS         8
#define MASK_3_BITS                             0x00000007

/*******************************************************************************
 *                         Public Functions Definitions                        *
 *******************************************************************************/

/*******************************************************************************
 * Interrupt Control Functions:
 * functions to enable, disable, and set the priority of interrupts. These
 * functions take IRQ number (Interrupt num from target vector table) as input
 *******************************************************************************/

/*********************************************************************
* Service Name: NVIC_EnableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable Interrupt request for this specific IRQ.
**********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{

   /*Each register can control 32 interrupt/ so we can use this switch case
    * to find the right register to change and then set the corresponding bit */
    if (IRQ_Num < 32)
    {
        NVIC_EN0_REG = (1<<IRQ_Num);

    }
    else if (IRQ_Num < 64)
    {
        NVIC_EN1_REG = (1<< (IRQ_Num - 32));
    }
    else if (IRQ_Num < 96)
    {
        NVIC_EN2_REG = (1<< (IRQ_Num - 64));
    }
    else if (IRQ_Num < 128)
    {
        NVIC_EN3_REG = (1<< (IRQ_Num - 96));
    }
    else if (IRQ_Num < 139)
    {
        NVIC_EN4_REG = (1<< (IRQ_Num - 128));
    }
    else
    {
        /*WRONG IRQ_NUM DO NOTHING*/
    }
}

/*********************************************************************
* Service Name: NVIC_DisableIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable Interrupt request for this specific IRQ.
**********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{

    /*Each register can control 32 interrupt/ so we can use this switch case
     * to find the right register to change and then set the corresponding bit */
    if (IRQ_Num < 32)
    {
        NVIC_DIS0_REG = (1<<IRQ_Num);
    }
    else if (IRQ_Num < 64)
    {
        NVIC_DIS1_REG = (1<< (IRQ_Num - 32));
    }
    else if (IRQ_Num < 96)
    {
        NVIC_DIS2_REG = (1<< (IRQ_Num - 64));
    }
    else if (IRQ_Num < 128)
    {
        NVIC_DIS3_REG = (1<< (IRQ_Num - 96));
    }
    else if (IRQ_Num < 139)
    {
        NVIC_DIS4_REG = (1<< (IRQ_Num - 128));
    }
    else
    {
        /*WRONG IRQ_NUM DO NOTHING*/
    }
}

/*********************************************************************
* Service Name: NVIC_SetPriorityIRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): IRQ_Num - Number of the IRQ from the target vector table / IRQ_Priority - priority of the IRQ
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the priority value for specific IRQ
**********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    if (IRQ_Num > NVIC_MICRO_TOTAL_INT_NUM || IRQ_Priority > 7)
    {
        /*WRONG IRQ_NUM DO NOTHING*/ /*or wrong priority num*/
    }
    else
    {
        /*calculate priority register number*/
        uint8 pri_registerNum = IRQ_Num / NVIC_NUMBER_OF_INT_PRI_PER_REG;
        /*calculate the NVIC priority register address for this IRQ*/
        volatile uint32* NVIC_pri_reg_address = (uint32*) ((NVIC_PRI0_REG_ADD) + (pri_registerNum));

        /*every register has 4 interrupts, we know which number is this interrupt from 0 to 3*/
        uint8 pos_of_int_in_pri_reg = IRQ_Num % NVIC_NUMBER_OF_INT_PRI_PER_REG;
        /*Calculate the bit pos of the interrupt*/
        uint8 pos_of_int_bit_int_pri_reg = FIRST_INT_PRI_BIT_POS + pos_of_int_in_pri_reg * NUM_OF_BITS_BETWEEN_TWO_PRI_POS;
        /*clear the interrupt priority bits and set the new priority*/
        (*NVIC_pri_reg_address) &= ~(MASK_3_BITS << pos_of_int_bit_int_pri_reg);
        (*NVIC_pri_reg_address) |= (IRQ_Priority << pos_of_int_bit_int_pri_reg);
    }

}

/*******************************************************************************
 * Sys_IRQ Control Functions:
 * functions to enable, disable, and set the priority of system and fault
 * exceptions for example Bus Fault or SysTick exceptions.
 * These functions take the exception number as input
 *******************************************************************************/
/*********************************************************************
* Service Name: NVIC_EnableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception_Num - Number of the Exception from enum type
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to enable specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    /*Set the enable bit of the Exception*/
    switch (Exception_Num)
    {
    /* EXCEPTION_RESET_TYPE, EXCEPTION_NMI_TYPE and EXCEPTION_HARD_FAULT_TYPE are always enabled */
    /* EXCEPTION_SVC_TYPE, EXCEPTION_DEBUG_MONITOR_TYPE, EXCEPTION_PEND_SV_TYPE, and EXCEPTION_SYSTICK_TYPE
    * have no enable or disable in NVIC*/

    case EXCEPTION_MEM_FAULT_TYPE:
       NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
       break;
    case EXCEPTION_BUS_FAULT_TYPE:
       NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
       break;
    case EXCEPTION_USAGE_FAULT_TYPE:
       NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
       break;
    default:
       /*DO NOTHING AS EXCEPTION NUM IS WRONG*/
       break;
    }
}

/*********************************************************************
* Service Name: NVIC_DisableException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception_Num - Number of the Exception from enum type
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to disable specific ARM system or fault exceptions.
**********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    /*Clear the enable bit of the Exception*/
    switch (Exception_Num)
    {
    /* EXCEPTION_RESET_TYPE, EXCEPTION_NMI_TYPE and EXCEPTION_HARD_FAULT_TYPE are always enabled */
    /* EXCEPTION_SVC_TYPE, EXCEPTION_DEBUG_MONITOR_TYPE, EXCEPTION_PEND_SV_TYPE, and EXCEPTION_SYSTICK_TYPE
    * have no enable or disable in NVIC*/

    case EXCEPTION_MEM_FAULT_TYPE:
    NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
    break;
    case EXCEPTION_BUS_FAULT_TYPE:
    NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
    break;
    case EXCEPTION_USAGE_FAULT_TYPE:
    NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
    break;
    default:
    /*DO NOTHING AS EXCEPTION NUM IS WRONG*/
    break;
    }
}

/*********************************************************************
* Service Name: NVIC_SetPriorityException
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Exception_Num - Number of the Exception from enum type - Exception_Priority - num of Exception priority
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the priority value for specific ARM system or fault
  exceptions.
**********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    if (Exception_Num > 15 || Exception_Priority > 7)
    {
        /*DO NOTHING THE EXCEPTION_NUM OR EXCEPTION_PRIORITY ARE WRONG*/
    }
    else
    {
        /*Set the priority of the Exception*/
        switch (Exception_Num)
        {
        /* EXCEPTION_RESET_TYPE, EXCEPTION_NMI_TYPE and EXCEPTION_HARD_FAULT_TYPE have fixed priority */

        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYSTEM_PRI1_REG =  (NVIC_SYSTEM_PRI1_REG & ~MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYSTEM_PRI1_REG =  (NVIC_SYSTEM_PRI1_REG & ~BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYSTEM_PRI1_REG =  (NVIC_SYSTEM_PRI1_REG & ~USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_SVC_TYPE:
            NVIC_SYSTEM_PRI2_REG =  (NVIC_SYSTEM_PRI2_REG & ~SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_DEBUG_MONITOR_TYPE:
            NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & ~DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_PEND_SV_TYPE:
            NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & ~PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_SYSTICK_TYPE:
            NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & ~SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
            break;
        }
    }
}


