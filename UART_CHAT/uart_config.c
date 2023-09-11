/*
 * uart_config.c
 *
 *  Created on: Sep 2, 2023
 *      Author: Mohamed Abdelazez
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "uart_config.h"

//extern volatile uint8_t count;

void UART_init(void)
{
    /* Set the clocking to run directly from the external crystal/oscillator */
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    /*
         Enable the peripherals used by this example.
         The UART itself needs to be enabled, as well as the GPIO port
         containing the pins that will be used.
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);


    /* Configure the GPIO pin muxing for the UART function.
    // This is only necessary if your part supports GPIO pin function muxing.
    // Study the data sheet to see which functions are allocated per pin.
    */
    GPIOPinConfigure(GPIO_PC6_U3RX);
    GPIOPinConfigure(GPIO_PC7_U3TX);

    /*
    // Since GPIO A0 and A1 are used for the UART function, they must be
    // configured for use as a peripheral function (instead of GPIO).
    */
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    /*
    // Configure the UART for 9600, 8-N-1 operation.
    // This function uses SysCtlClockGet() or ui32SysClock to get the system clock
    // frequency.  This could be also be a variable or hard coded value
    // instead of a function call.
    */
    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTFIFODisable(UART3_BASE);
}

void UART_initTerminal(void)
{
    /* Set the clocking to run directly from the external crystal/oscillator */
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    /*
         Enable the peripherals used by this example.
         The UART itself needs to be enabled, as well as the GPIO port
         containing the pins that will be used.
     */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);


    /* Configure the GPIO pin muxing for the UART function.
    // This is only necessary if your part supports GPIO pin function muxing.
    // Study the data sheet to see which functions are allocated per pin.
    */
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    /*
    // Since GPIO A0 and A1 are used for the UART function, they must be
    // configured for use as a peripheral function (instead of GPIO).
    */
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /*
    // Configure the UART for 9600, 8-N-1 operation.
    // This function uses SysCtlClockGet() or ui32SysClock to get the system clock
    // frequency.  This could be also be a variable or hard coded value
    // instead of a function call.
    */
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8_t *Str , uint32_t uartUsed)
{
    uint8_t i = 0;

    /* Send the whole string */
    while(Str[i] != '#')
    {
        UARTCharPut(uartUsed , Str[i]);
        i++;
    }
    UARTCharPut(uartUsed , '#');
}
/*
 * Description :
 * Receive the required string until the '\n' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8_t *Str , uint32_t uartUsed)
{
    uint8_t i = 0;

    /* Receive the first byte */
    //Str[i] = UARTCharGet(uartUsed);
    if(uartUsed == TERMINAL_UART)
    {
        UARTCharPut(TERMINAL_UART , Str[i]);
    }

    /* Receive the whole string until the '#' */
    while(Str[i] != '#')
    {
        i++;
        Str[i] = UARTCharGet(uartUsed);


        if(uartUsed == TERMINAL_UART)
        {    if(Str[i]!='#')
            UARTCharPut(TERMINAL_UART , Str[i]);
        }
    }
}


void UART_OFF(void)
{
	UARTDisable(UART0_BASE);
    UARTDisable(UART3_BASE);
}
void UART_ON(void)
{
	 UARTEnable(UART0_BASE);
     UARTEnable(UART3_BASE);
}

