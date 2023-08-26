

/**
 * main.c
 */
#include"tm4c123gh6pm.h"
#include"std_types.h"
#include"Bitwise_operation.h"
#include"DIO.h"
#include"GPT_Interface.h"

uint8 time=250;
int main(void)
{
Portf_int();
DIO_init(PORTC, 0x10, 0);
Clear_Bit(GPIO_PORTF_DATA_R,1);
Clear_Bit(GPIO_PORTF_DATA_R,2);
Clear_Bit(GPIO_PORTF_DATA_R,3);

Timer_0_Inputcapture();
Timer0_periodic_Init();

while(1)
{
    if(time<5)
    {
        Clear_Bit(GPIO_PORTF_DATA_R,1);
        Clear_Bit(GPIO_PORTF_DATA_R,2);
        Clear_Bit(GPIO_PORTF_DATA_R,3);;
        Set_Bit(GPIO_PORTF_DATA_R,1);
    }
    else if(time<10)
    {
        Clear_Bit(GPIO_PORTF_DATA_R,1);
        Clear_Bit(GPIO_PORTF_DATA_R,2);
        Clear_Bit(GPIO_PORTF_DATA_R,3);
        Set_Bit(GPIO_PORTF_DATA_R,2);
    }
    else if(time<15)
    {
        Clear_Bit(GPIO_PORTF_DATA_R,1);
        Clear_Bit(GPIO_PORTF_DATA_R,2);
        Clear_Bit(GPIO_PORTF_DATA_R,3);
        Set_Bit(GPIO_PORTF_DATA_R,3);
    }
    else
    {
        /*Set_Bit(GPIO_PORTF_DATA_R,1);
        Set_Bit(GPIO_PORTF_DATA_R,2);
        Set_Bit(GPIO_PORTF_DATA_R,3);
        */
    }
}
}



void Timer0Handler(void)
{
    Set_Bit(TIMER0_ICR_R,0);
    Togle_Bit(GPIO_PORTF_DATA_R,1);//led red
    Togle_Bit(GPIO_PORTF_DATA_R,2);//led green
    Togle_Bit(GPIO_PORTF_DATA_R,3);//led blue
}
void WideTimer0Handler(void)
{

    static float32 x =0.0,y=0.0;
    Set_Bit(WTIMER0_ICR_R,2);
    x = (WTIMER0_TAR_R/16000000.0f);
    if(y)
    time = x - y;
    y = x;


 /*
  * if(count==0)
    {
        count++;
        x = (WTIMER0_TAR_R/16000000.0f);
    }
    else if(count==1)
    {
        count=0;
        y=(WTIMER0_TAR_R/16000000.0f);
        time=y-x;
    }

*/
}
