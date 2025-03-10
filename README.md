# ARM-Cortex-M-Project
SysTick Timer Driver, and NVIC Driver

Hallo, all.

This is a final project of my Embedded software advanced diploma at "EDGES for training"

A summery of the project: it is an implementaion of SysTick and NVIC drivers and testing them in 2 different applications:
  
    APP1 overview:
    Test the SysTick with interrupt technique and NVIC IRQ functionalities using the main application 1.
    
      Initialization Steps:
  
      After executing SW2_Init(), ensure that bit 30 in the NVIC_EN0_REG register is set. Also, configure the priority of the GPIO PORTF IRQ correctly in its       corresponding field in the NVIC_PRI7_REG register.
      
      After executing NVIC_ExceptionSetPriority(), ensure the priority of the SysTick system exception is correctly set in its field in the                     
      NVIC_SYSTEM_PRI3_REG register.
      
      Application Workflow:
      
      The application will perform a rolling action on the three LEDs, cycling every 1 second using the SysTick timer interrupt technique and a call-back 
      function.
      
      If Switch 2 is pressed:
      
      The SysTick timer will stop.
      
      All three LEDs will turn on and remain lit for 5 seconds.
      
      After 5 seconds, the SysTick timer will restart, and the rolling action on the LEDs will resume.
      
      Testing:
      
      Test the SysTick functionality using the busy-wait technique and NVIC system exceptions.

    APP2 overview:
    Test the SysTick with busy-wait technique and NVIC system exceptions functionalities using the main application 2.
      
      Steps:

      Test_Exceptions_Settings() Function:
      
      This function is responsible for enabling, disabling, and setting the priority for each system and fault exception.
      
      It ensures these settings are correct by using the assert macro. Make sure all conditions in the assert macro are true to avoid runtime errors.
      
      Application Workflow:
      
      The application performs a rolling action on the three LEDs, cycling every 1 second using the SysTick timer busy-wait technique.
    

•	Utilized: SysTick and NVIC Drivers.

•	Microcontroller: TM4C123GH6PM.

You can read the full requirements in the attached file.

Thank you.
