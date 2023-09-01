/*
 * DIO.h
 *
 *  Created on: Aug 13, 2023
 *      Author: Mohamed Abdelazez
 */

#ifndef DIO_H_
#define DIO_H_

#include "std_types.h"

#define MAX_PORT_PINS 8

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define SW_2      0
#define RED_LED   1
#define BLUE_LED 2
#define GREEN_LED  3
#define SW_1      4

typedef enum{
    edge , level
}detectType;

typedef enum{
    risingHigh , failingLow , bothTriggers
}triggerType;

typedef enum{
    inputPin , outputPin
}directionType;

void DIO_WritePin(uint8 port , uint8 pin , uint8 value);

uint8 DIO_ReadPin(uint8 port , uint8 pin);

void DIO_init(uint8 port , uint8 inputPins , uint8 outputPins);

void DIO_PinDirection(uint8 port , uint8 pin , directionType direction);

void DIO_EnableInterrupt(uint8 port , uint8 pin , detectType detectInput , triggerType triggerInput);

#endif /* DIO_H_ */
