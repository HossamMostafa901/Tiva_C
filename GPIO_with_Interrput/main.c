

/**
 * main.c
 */
#include"GPIO_NIvic_Interface.h"
#include"tm4c123gh6pm.h"
#include"Bitwise_operation.h"
unsigned char flag=0;
int main(void)
{ unsigned char prev='R';
Portf_int();
Portinterput_int();

__asm ("    CPSIE I");
while(1)
{
    //__asm ("    wfi");
    if(flag==1&&prev=='R')
    {
        GPIO_PORTF_DATA_R=(1<<2);
        flag=0;
        prev='B';
    }
    else if(flag==1&&prev=='B')
    {
        GPIO_PORTF_DATA_R=(1<<3);
        flag=0;
        prev='G';
    }
    else if(flag==1&&prev=='G')
    {
        GPIO_PORTF_DATA_R=(1<<1);
        flag=0;
        prev='R';
    }
    if(flag==2&&prev=='R')
    {
        GPIO_PORTF_DATA_R=(1<<3);
        flag=0;
        prev='G';
    }
    else if(flag==2&&prev=='G')
    {
        GPIO_PORTF_DATA_R=(1<<2);
        flag=0;
        prev='B';
    }
    else if(flag==2&&prev=='B')
    {
        GPIO_PORTF_DATA_R=(1<<1);
        flag=0;
        prev='R';
    }

}
return 0;
}
void PortFHandler()
{
    int i;
    for (i=0;i<10000;i++);

    if(get_bit(GPIO_PORTF_RIS_R,0)==1)
    {
        GPIO_PORTF_ICR_R|=0x01;
        flag=1;

    }


    if(get_bit(GPIO_PORTF_RIS_R,4)==1)
    {
        GPIO_PORTF_ICR_R|=0x10;
        flag=2;

    }
}

