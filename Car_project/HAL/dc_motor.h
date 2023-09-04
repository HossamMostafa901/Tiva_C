/*
 * dc_motor.h
 *
 *  Created on: Apr 6, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/* *************************************************
 *            Definitions
 * ************************************************/
#define NUMBER_OF_MOTORS     4
#define MOTORS_PORT          PORTD

#define MOTOR_FR_CW_PIN      0
#define MOTOR_FR_ACW_PIN     1

#define MOTOR_FL_CW_PIN      2
#define MOTOR_FL_ACW_PIN     3

#define MOTOR_RR_CW_PIN      4
#define MOTOR_RR_ACW_PIN     5

#define MOTOR_RL_CW_PIN      6
#define MOTOR_RL_ACW_PIN     7

/* MARCO */
#define SYSCTL_PWM_PERIPH    SYSCTL_PERIPH_PWM1
#define SYSCTL_MOTOR_PERIPH  SYSCTL_PERIPH_GPIOF

#define GPIO_PORT_BASE       GPIO_PORTF_BASE
#define PWM_BASE             PWM1_BASE
#define PWM_GEN_RIGHT        PWM_GEN_2
#define PWM_GEN_LEFT         PWM_GEN_3

#define RIGHT_MOTORS         GPIO_PIN_1
#define LEFT_MOTORS          GPIO_PIN_2

#define LEFT_OUT             PWM_OUT_5
#define RIGHT_OUT            PWM_OUT_6

#define LEFT_OUT_BIT         PWM_OUT_5_BIT
#define RIGHT_OUT_BIT        PWM_OUT_6_BIT

/* ************************************************
 *                      Enums
 * ************************************************/
typedef enum
{
	STOP, FORWARD_DIRECTION, BACKWARD_DIRECTION
}DcMotorStateType;

typedef enum
{
    FR_MOTOR = MOTOR_FR_CW_PIN , FL_MOTOR = MOTOR_FL_CW_PIN , RR_MOTOR = MOTOR_RR_CW_PIN, RL_MOTOR = MOTOR_RL_CW_PIN
}motorPositionType;

/* ***************************************************************
 *                      Function declaration
 * ***************************************************************/
void DcMotor_init(void);

void DcMotor_rotate(motorPositionType motor, DcMotorStateType state);

void PWM_init(uint32 speed);

#endif /* DC_MOTOR_H_ */
