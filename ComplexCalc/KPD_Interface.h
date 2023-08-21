/*
 * KPD_Interface.h
 *
 *  Created on: Aug 18, 2023
 *      Author: DELL
 */

#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_


#define NumberofRows 4
#define Numberofcoloums 4


void delay_ms(unsigned int n);
void delay_us( unsigned int n);
void KPD_INt(void);
void Portinterput_int(void);
char keypad_getkey(void);

#endif /* KPD_INTERFACE_H_ */
