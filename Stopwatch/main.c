

/**
 * main.c
 */
#include"tm4c123gh6pm.h"
#include"Bitwise_operation.h"
#include"std_types.h"
#include"DIO.h"
#include"lcd.h"
#include"Systick_Interfce.h"

uint8 seconds=0;
uint8 min=0;
uint8 hour=0;
int main(void)
{    LCD_init();
Systick_Init();
DIO_init(PORTF, 0b00010001, 0b00001110);
DIO_WritePin(PORTF,RED_LED , LOGIC_HIGH);
DIO_EnableInterrupt(PORTF, SW_1,edge , failingLow);
DIO_EnableInterrupt(PORTF, SW_2,edge , failingLow);
//enable interupt for 1 secs
systick_interput(1000);
while(1)
{// to write hour
LCD_u32_Write_Number(hour/10,0,0);
LCD_u32_Write_Number(hour%10,0,1);
LCD_displayCharacter(':');
//to write min
LCD_u32_Write_Number(min/10,0,3);
LCD_u32_Write_Number(min%10,0,4);
LCD_displayCharacter(':');
//to write sec
LCD_u32_Write_Number(seconds/10,0,6);
LCD_u32_Write_Number(seconds%10,0,7);
/*DIO_WritePin(PORTF,RED_LED , LOGIC_HIGH);
             Systick_SetBusyWait(500);
             DIO_WritePin(PORTF,RED_LED , LOGIC_LOW);
             Systick_SetBusyWait(500);
 */
}




//NVIC_ST_CTRL_R=0x7;//enable systick &enable interput;
//NVIC_ST_RELOAD_R=(16000000)-1;
return 0;
}
void SysTickHandler(void)
{
    seconds++;
    if(seconds==60)
    {
        min++;
        seconds=0;
    }
    if(min==60)
    {
        hour=1;
        min=0;
        seconds=0;
    }
}
void PortFHandler(void)
{
    if(get_bit(GPIO_PORTF_RIS_R,0)==1)
    {   //clear interput
        GPIO_PORTF_ICR_R|=0x01;
        // disable interput
        Clear_Bit(NVIC_ST_CTRL_R,Systick_Intern);
        // disable timer
        Clear_Bit(NVIC_ST_CTRL_R,Systick_Enable);
    }
    if(get_bit(GPIO_PORTF_RIS_R,4)==1)
    {
        //clear interput
        GPIO_PORTF_ICR_R|=0x10;
        //enable Interput
        Set_Bit(NVIC_ST_CTRL_R,Systick_Intern);
        //enable Timer
        Set_Bit(NVIC_ST_CTRL_R,Systick_Enable);
    }


}
