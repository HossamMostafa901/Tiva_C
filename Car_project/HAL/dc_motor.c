/*
 * dc_motor.c
 *
 *  Created on: Apr 6, 2023
 *      Author: Mohamed Abdelazez
 */
#include "dc_motor.h"
#include "DIO.h"
#include "driverlib/pin_map.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"

/* ***************************************************************
 *                      Function definition
 * ***************************************************************/

/* motor pins initialization */
void DcMotor_init(void)
{
    uint8 i;

    DIO_init(MOTORS_PORT , 0x00 , 0x0F);                /* initialize direction pins */

	for(i = 0 ; i < NUMBER_OF_MOTORS * 2 ; i += 2)
	{
	    /* stop motors initially */
	    DIO_WritePin(MOTORS_PORT , i   , LOGIC_LOW);
	    DIO_WritePin(MOTORS_PORT , i+1 , LOGIC_LOW);
	}

}

/* set the state of a specific motor */
void DcMotor_rotate(motorPositionType motor, DcMotorStateType state)
{
	switch(state)
	{
		case FORWARD_DIRECTION:
		    /* write high on cw pin and low on acw pin */
			DIO_WritePin(MOTORS_PORT , motor   , LOGIC_HIGH);
			DIO_WritePin(MOTORS_PORT , motor+1 , LOGIC_LOW);
			break;

		case BACKWARD_DIRECTION:
		    /* write high on acw pin and low on cw pin */
			DIO_WritePin(MOTORS_PORT , motor   , LOGIC_LOW);
		    DIO_WritePin(MOTORS_PORT , motor+1 , LOGIC_HIGH);
			break;

		case STOP:
		    /* write low on cw pin and low on acw pin */
		    DIO_WritePin(MOTORS_PORT , motor   , LOGIC_LOW);
		    DIO_WritePin(MOTORS_PORT , motor+1 , LOGIC_LOW);
			break;
	}
}

/* MARCO: pwm initialization */
void PWM_init(uint32 speed)
{
    //clock the PWM peripheral
    SysCtlPeripheralEnable(SYSCTL_PWM_PERIPH);
    //wait for the peripheral to start
    while(!SysCtlPeripheralReady(SYSCTL_PWM_PERIPH)){}

    //clock the GPIOF
    SysCtlPeripheralEnable(SYSCTL_MOTOR_PERIPH);
    //wait for the peripheral to start
    while(!SysCtlPeripheralReady(SYSCTL_MOTOR_PERIPH)){}

    //Set the clock
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //start the PWM
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    //select PWM alternative function
    GPIOPinTypePWM(GPIO_PORT_BASE, LEFT_MOTORS | RIGHT_MOTORS);
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);

    //configure PWM generator (PWM1 Generator2)
    PWMGenConfigure(PWM_BASE, PWM_GEN_RIGHT, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM_BASE, PWM_GEN_LEFT, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //Period set for generator of left motor
    PWMGenPeriodSet(PWM_BASE, PWM_GEN_LEFT, 100);
    //Period set for generator of right motor
    PWMGenPeriodSet(PWM_BASE, PWM_GEN_RIGHT, 100);
    //pulse width
    PWMPulseWidthSet(PWM_BASE, LEFT_OUT, speed);
    //pulse width
    PWMPulseWidthSet(PWM_BASE, RIGHT_OUT, speed+7);

    //enable the generator
    PWMGenEnable(PWM_BASE, PWM_GEN_RIGHT);
    PWMGenEnable(PWM_BASE, PWM_GEN_LEFT);

    //enable the output
    PWMOutputState(PWM_BASE, LEFT_OUT_BIT , true);
    PWMOutputState(PWM_BASE, RIGHT_OUT_BIT , true);
}
