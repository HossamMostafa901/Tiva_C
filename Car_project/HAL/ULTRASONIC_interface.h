/*Author:      Mohamed Gamal Roushdy                                                                      
  Version:     0.1                                                                       
  Date:        31/08/2023                                                                             
  Description: ULTRASONIC driver interface file      
*/
#ifndef _ULTRASONIC_INTERFACE_H
#define _ULTRASONIC_INTERFACE_H

#define F_CPU 16000000UL

void Ultrasonic_Init(void);
void Ultrasonic_Callback(void);
static void Ultrasonic_Timer_Init(void);
static void Ultrasonic_GPIO_Init(void);
void trigger_measurement(void);


#endif
