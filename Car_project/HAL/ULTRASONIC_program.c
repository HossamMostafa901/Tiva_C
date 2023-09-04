#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h" // This header contains the GPIO_PIN_x constants for alternate function selection
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

#include "ULTRASONIC_interface.h"
#include <math.h>

volatile uint32_t Rise, Fall;
volatile uint8_t Interrupt_Entry=0; /*State that checks if i am going to read positive edge or negative edge*/
float Distance;
int Difference;
float Period = 0U;

void Ultrasonic_Init(void)
{
    Ultrasonic_GPIO_Init();
    Ultrasonic_Timer_Init();
}

void trigger_measurement(void)
{
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 1u);
    SysCtlDelay(160U);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,0u);
}

static void Ultrasonic_GPIO_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); /* Enable GPIOC Clock */
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5); /* PC5 as Output for TRIG */
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PC4_WT0CCP0);
    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_4); /* PC4 for timer for ECHO */
}

static void Ultrasonic_Timer_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0); /* Enable WTIMER0 Clock */
    TimerDisable(WTIMER0_BASE, TIMER_A);
    TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME); /* Timer A with Capture edge time mode */
    TimerControlEvent(WTIMER0_BASE, TIMER_A, TIMER_EVENT_BOTH_EDGES); /* Capture on rising edge */
    IntEnable(INT_WTIMER0A);
    TimerIntRegister(WTIMER0_BASE, TIMER_A, &Ultrasonic_Callback);
    TimerIntEnable(WTIMER0_BASE, TIMER_CAPA_EVENT);
    IntMasterEnable();
    TimerEnable(WTIMER0_BASE, TIMER_A); /* Enable Timer A */
}

void Ultrasonic_Callback(void)
{
    if (!Interrupt_Entry)
    {
        Rise = TimerValueGet(WTIMER0_BASE, TIMER_A);
        Interrupt_Entry = 1U;
    }
    /* TIMER_TAR 4244408905 (Decimal)    GPTM Timer A [Memory Mapped]*/
    else
    {
        Fall = TimerValueGet(WTIMER0_BASE, TIMER_A);
        Interrupt_Entry = 0U;
        Difference = abs(Rise - Fall);
        Period = Difference / 16000000.0;
        Distance = (Period * 34000U) / 2U;
    }
    TimerIntClear(WTIMER0_BASE, TIMER_CAPA_EVENT);

}
