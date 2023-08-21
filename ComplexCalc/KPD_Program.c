/*
 * KPD_Program.c
 *
 *  Created on: Aug 18, 2023
 *      Author: DELL
 */
#include"tm4c123gh6pm.h"
#include"KPD_Interface.h"
#include"Bitwise_operation.h"
#include"lcd.h"
unsigned  char KPD[NumberofRows][Numberofcoloums]={{ '1', '2',  '3', '+'},//2d array for keypad
                                                   { '4', '5',  '6', '-'},
                                                   { '7', '8',  '9', '*'},
                                                   { '.', '0',  '=', '/'}};
unsigned  char flag1=0,flag2=0,flag3=0,flag4=0;
unsigned  char index,row=0;

void delay_ms(unsigned int n)//function for delay in ms
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<3180;j++)
        {};
}
void delay_us( unsigned int n)//function for delay in us
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<3;j++)
        {};

}
void KPD_INt(void)//function int to keypad we use portc and e
{
    SYSCTL_RCGCGPIO_R|=0x14;
    while((SYSCTL_PRGPIO_R &0x14)==0);
    GPIO_PORTE_LOCK_R=0X4C4F434B;
    GPIO_PORTC_LOCK_R=0X4C4F434B;
    GPIO_PORTC_CR_R=0XF0;
    GPIO_PORTE_CR_R=0X1E;
    GPIO_PORTE_DIR_R=0X1E;
    GPIO_PORTC_DIR_R=0X00;
    GPIO_PORTC_PUR_R=0XF0;
    GPIO_PORTC_DEN_R=0XF0;
    GPIO_PORTE_DEN_R=0X1E;

}
void Portinterput_int(void) //to inizalze interput for port c
{
    GPIO_PORTC_IS_R=0;
    GPIO_PORTC_IBE_R=0;
    GPIO_PORTC_IEV_R=0x00;
    GPIO_PORTC_IM_R=0xF0;
    NVIC_EN0_R|=(1<<2);

}

char keypad_getkey(void)
{
    char localpinstate=0xff;

while(!flag1)
{
    for(index = 1; index < 5; index++)    //Scan columns loop
    {
        GPIO_PORTC_IM_R &=0x00;//to disable interput to make it critical section
        GPIO_PORTE_DATA_R=~(1U << index);// to make row equal zero
        GPIO_PORTC_IM_R|=0xF0;//to resume interput
        while(!get_bit(GPIO_PORTC_DATA_R,4));/*to get second read to ensure that tere are no polling */
        while(!get_bit(GPIO_PORTC_DATA_R,5));/*you check that all rows are high so there no polling will hapen*/
        while(!get_bit(GPIO_PORTC_DATA_R,6));
        while(!get_bit(GPIO_PORTC_DATA_R,7));
        delay_us(250);
    }
}

delay_ms(1);
//while(!get_bit(GPIO_PORTC_DATA_R,flag2>>4));
switch(flag2)//to get which col is pressed
{
case 0x1:flag3=0;break;
case 0x2:flag3=1;break;
case 0x4:flag3=2;break;
case 0x8:flag3=3;break;
}
flag1=0;
localpinstate=KPD[row][flag3];

return (localpinstate);
}


void PortCHandler(void)
{

    delay_ms(200);
    row=index-1;//get row which is has pullup become falling edge

    flag2=(GPIO_PORTC_RIS_R>>4);//to get col shift the value to right by 4 because i start from c4->c7

    flag1=1;
    GPIO_PORTC_ICR_R = 0xF0;//clear flag

}


