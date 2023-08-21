/*
 * GPIO_NVIC_program.c
 *
 *  Created on: Aug 17, 2023
 *      Author: DELL
 */
# define LED (1<<1)
#include"GPIO_NIvic_Interface.h"
#include"tm4c123gh6pm.h"
#include"Bitwise_operation.h"
void Portf_int(void)
{
    SYSCTL_RCGCGPIO_R|=0X00000020;
        while((SYSCTL_PRGPIO_R &0X00000020)==0); //register&(1<<4)
        GPIO_PORTF_LOCK_R=0X4C4F434B;
        GPIO_PORTF_CR_R=0X1F;
        GPIO_PORTF_DIR_R=0X0E;
        GPIO_PORTF_PUR_R=0X11;
        GPIO_PORTF_DEN_R=0X1F;
        GPIO_PORTF_DATA_R|=LED;
}
void Portinterput_int(void)
{
    GPIO_PORTF_IS_R=0x0;
    GPIO_PORTF_IBE_R=0x0;
    GPIO_PORTF_IEV_R=0x0;
    GPIO_PORTF_IM_R|=0x11;
    NVIC_EN0_R|=(1<<30);
}




