/*
 * GPT_Interface.h
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */

#ifndef GPT_INTERFACE_H_
#define GPT_INTERFACE_H_


void Timer0_periodic_Init(void);
void Portf_int(void);
void Timer1_PWM_INIT(void);
void Dutycycle(float32 pwm);

#endif /* GPT_INTERFACE_H_ */
