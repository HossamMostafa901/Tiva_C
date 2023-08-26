/*
 * GPT_program.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include"tm4c123gh6pm.h"
#include"std_types.h"
#include"Bitwise_operation.h"

void Timer0_periodic_Init(void)
{
    Set_Bit(SYSCTL_RCGCTIMER_R,0);//enable clock to timer 0
    Clear_Bit(TIMER0_CTL_R,8);//timer b disabled from counting or cptured
    Clear_Bit(TIMER0_CTL_R,0);//timer A disabled from counting or cptured
    TIMER0_TAMR_R=0x2;//periodic timer a enable
    TIMER0_TAILR_R=8000000;//time for half sec;
    Set_Bit(TIMER0_IMR_R,0);//enable interput for timer 0;
    Set_Bit(NVIC_EN0_R,19);//enable interupt from Nvic
    Set_Bit(TIMER0_CTL_R,0);//timer enable counting

}
void Portf_int(void)
{
    SYSCTL_RCGCGPIO_R|=0X00000020;//enable clock for portf
    while((SYSCTL_PRGPIO_R &0X00000020)==0); //check clock
    GPIO_PORTF_LOCK_R=0X4C4F434B;//unlock port
    GPIO_PORTF_CR_R=0X1F;//enable all pin
    GPIO_PORTF_DIR_R=0X0E;//make sw1&sw2 input led is output
    GPIO_PORTF_PUR_R=0X11;//make pullup for sw1&sw2
    GPIO_PORTF_DEN_R=0X1F;//enable all pin in port
}
void Timer1_PWM_INIT(void)
{
    Set_Bit(SYSCTL_RCGCTIMER_R,1);//enable clock to timer 1
    GPIO_PORTF_AFSEL_R=0x04;//make pin from Gpio to alternating function
    GPIO_PORTF_PCTL_R|= (0x07<<8);//to enable pwm in portf led_blue
    Clear_Bit(TIMER1_CTL_R,0);//timer A disabled from counting or cptured
    TIMER1_CFG_R=0x04;//enable pwm in timer 1
    TIMER1_TAMR_R=0x02;//periodic active
    Set_Bit(TIMER1_TAMR_R,3);//pwm mode active
    Clear_Bit(TIMER1_TAMR_R,2);//edge count mode
    Set_Bit(TIMER1_CTL_R,6);//output Inverted
    TIMER1_TAILR_R=16000;//for 1msec time 1000ms/1/16MHZ;
    Set_Bit(TIMER1_CTL_R,0);//enable timer

}
void Dutycycle(float32 pwm)
{
    TIMER1_TAMATCHR_R = 16000 - (pwm/100.0)*16000;
}
void Timer_0_Inputcapture(void)
{
    Set_Bit(SYSCTL_RCGCWTIMER_R,0);//enable clock to timer 0
    Clear_Bit(WTIMER0_CTL_R,0);//timer A disabled from counting or cptured
    WTIMER0_CFG_R=0x04;//enable Timer 32 bit mode
    WTIMER0_TAMR_R=0x03;//capture mode
    Set_Bit(WTIMER0_TAMR_R,2);//to make edge time
    Set_Bit(WTIMER0_TAMR_R,4);//count up
    WTIMER0_CTL_R|=0x04;//enable falling edge
   //TIMER0_TAILR_R= 240000000;
    Set_Bit(GPIO_PORTC_AFSEL_R,4);//make pin from Gpio to alternating function
        GPIO_PORTC_PCTL_R|= (0x07<<16);
    Set_Bit(WTIMER0_IMR_R ,2);//enable capture mode interrput
    Set_Bit(NVIC_EN2_R,30);//enable interupt from Nvic
    Set_Bit(WTIMER0_CTL_R,0);
}




