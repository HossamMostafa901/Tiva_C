

/**
 * main.c
 */
#include"tm4c123gh6pm.h"

#define BIT_Band GPIO_PORTF_DATA_BITS_R
#define SW1  (1<<0)
#define SW2  (1<<4)
#define RED_Led (1<<1)
#define Blue_Led (1<<2)
#define Green_Led (1<<3)


int main(void)
{
    SYSCTL_RCGCGPIO_R|=0X00000020;
        while((SYSCTL_PRGPIO_R &0X00000020)==0); //register&(1<<4)
        GPIO_PORTF_LOCK_R=0X4C4F434B;
        GPIO_PORTF_CR_R=0X1F;
        GPIO_PORTF_DIR_R=0X0E;
        GPIO_PORTF_PUR_R=0X11;
        GPIO_PORTF_DEN_R=0X1F;
        while(1)
        {
            /*if(!(BIT_Band[SW1]==SW1)||!(BIT_Band[SW2]==SW2))
                    {
                     BIT_Band[RED_Led|Blue_Led|Green_Led]=RED_Led|Blue_Led|Green_Led;
                    }
            else
                {
                BIT_Band[RED_Led|Blue_Led|Green_Led]=!(RED_Led|Blue_Led|Green_Led);
                }*/
            BIT_Band[RED_Led|Blue_Led|Green_Led]=0x00;

            if(   (*(BIT_Band + (SW1))) ==0 )
            {
                *(BIT_Band + (1<<1))=RED_Led ;
            }

        }

	return 0;
}
