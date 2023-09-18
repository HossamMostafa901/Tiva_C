/*
 * main.c
 *
 *  Created on: Sep 2, 2023
 *      Author: DELL
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"

#include "uart_config.h"
/*in this project we have three state one no uart second listiening or reciveing third is chat*/
#define ARRAY_SIZE   200
/*we choose here one to be sender or reciver in 2nd state that do one job second code in another computer will be the ooposite choice*/
#define SENDER_ECU
/* Function declaration */
void DIO_init(void);
void GPIOF_Handler(void);
volatile uint8_t count;

/* Main function */
int main(void)
{
    uint8_t dataString[ARRAY_SIZE];
    uint8_t flag=1, flag2=1;
    DIO_init();
    UART_init();
    UART_initTerminal();

    /*#ifdef SENDER_ECU
         UART_sendString("Start Typing ...#" , TERMINAL_UART);
         UARTCharPut(TERMINAL_UART , '\r');
          UARTCharPut(TERMINAL_UART , '\n');
          #endif

        #ifdef RECEIVER_ECU
        UART_sendString("Waiting for message ...#" , TERMINAL_UART);
          UARTCharPut(TERMINAL_UART , '\r');
          UARTCharPut(TERMINAL_UART , '\n');
              #endif
     */

    /* infinity loop */
    /**to konw in which state led will be change in every state/
    while(1)
    {
        if(count==0)
        {

            if(flag==1)
            {
                UART_sendString("OFF State ...#" , TERMINAL_UART);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,GPIO_PIN_1);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0u);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0u);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');
                flag=0;
                flag2=1;
            }

        }
        else if(count==1)
        {
            if (UARTCharsAvail(TIVA_UART))
            {
                UARTCharGet(TIVA_UART);
            }

#ifdef RECEIVER_ECU
            if(flag == 0)
            {
                UART_sendString("RECIVE State ...#" , TERMINAL_UART);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0u);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0u);
                flag = 1;
            }
#endif
#ifdef SENDER_ECU
            if (flag == 0)
            {
                UART_sendString("SENDER State ...#" , TERMINAL_UART);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0u);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0u);
            }
            flag = 1;

#endif

#ifdef RECEIVER_ECU
            if(UARTCharsAvail(TIVA_UART))
            {
                UART_receiveString(dataString, TIVA_UART);
                UART_sendString(dataString, TERMINAL_UART);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');
            }
#endif
#ifdef SENDER_ECU
            if(UARTCharsAvail(TERMINAL_UART))
            {
                UART_receiveString(dataString, TERMINAL_UART);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');
                UART_sendString(dataString, TIVA_UART);
            }
#endif

        }
        else if(count==2)
        {
            if(flag2 == 1)
            {
            UART_sendString("CHAT State ...#" , TERMINAL_UART);
            UARTCharPut(TERMINAL_UART , '\r');
            UARTCharPut(TERMINAL_UART , '\n');

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0u);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0u);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            }
            flag2 = 0;

#ifdef SENDER_ECU
            if(UARTCharsAvail(TERMINAL_UART))
            {
                UART_receiveString(dataString, TERMINAL_UART);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');
                UART_sendString(dataString, TIVA_UART);

                UART_receiveString(dataString, TIVA_UART);
                UART_sendString(dataString, TERMINAL_UART);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');
            }

#endif

#ifdef RECEIVER_ECU
            if(UARTCharsAvail(TIVA_UART))
            {
                UART_receiveString(dataString, TIVA_UART);
                UART_sendString(dataString, TERMINAL_UART);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');

                UART_receiveString(dataString, TERMINAL_UART);
                UARTCharPut(TERMINAL_UART , '\r');
                UARTCharPut(TERMINAL_UART , '\n');
                UART_sendString(dataString, TIVA_UART);
            }

#endif	
        }

    }
}

void DIO_init(void)
{
    /* Enable the GPIO port that is used for the on-board LED */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    /* Check if the peripheral access is enabled */
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}

    /* Enable the GPIO pins for the LEDs (PF1,PF2PF3).  Set the direction as output, and enable the GPIO pins for digital 
function */
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    /* Turn off the LEDs initially */
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);

    /*enable interrput*/
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);

    GPIOIntRegister(GPIO_PORTF_BASE, &GPIOF_Handler);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
    IntEnable(INT_GPIOF);
}
void GPIOF_Handler(void)
{
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);/*clear interput flag*/

    switch(count)
    {
    case 0:
        count =1;break;
    case 1:
        count =2;break;
    case 2:
        count=0;break;
    }
}

