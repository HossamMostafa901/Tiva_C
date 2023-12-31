

/**
 * main.c
 */

#include"tm4c123gh6pm.h"
#include "lcd.h"
#include"KPD_Interface.h"

int main(void)
{
    __asm ("    CPSIE I");// to enable NVIC
    KPD_INt();// function of keypad
    LCD_init();//function to iniliaze lcd
    Portinterput_int();//function int for interrput
    LCD_clearScreen();
    GPIO_PORTE_DATA_R=0x1E;
    char c='o';
    int a[5]={0},o[5]={0},asci[5];//array to put number ||aray to put piroity of operationand array to put operant like +-/*
    int volatile total=0,n=0,num,index=0,op_index=0,min=999,x,y,asci_index=0,flag=0,m_flag=0;//flags
    char op_flag=0,equal_flag=0,op=0,min_index=0,first_time=1;//flag


    while(1)
    {
        while(equal_flag==0)
        {   //delay_ms(250);
            c=keypad_getkey();// to get the key that is pressed

            if(c!=0xff) //value if c is not pressed
            {
                LCD_displayCharacter(c);//display the key
            }


            if(c=='+')//if operator =+
            {
                op_flag=1;
                op=2;
                o[op_index]=op;//put piorty of operator in array
                op_index++;//increase index
                asci[asci_index]=c;//put opertor in array
                asci_index++;//increase index
            }
            else if(c=='-')
            {
                op_flag=1;
                op=2;
                o[op_index]=op;//put piorty of operator in array
                op_index++;//increase index
                asci[asci_index]=c;//put opertor in array
                asci_index++;//increase index
            }
            else if(c=='/')
            {
                op_flag=1;
                op=1;
                o[op_index]=op;//put piorty of operator in array
                op_index++;//increase index
                asci[asci_index]=c;//put opertor in array
                asci_index++;//increase index
            }
            else if(c=='*')
            {
                op_flag=1;
                op=1;
                o[op_index]=op;//put piorty of operator in array
                asci[asci_index]=c;//put opertor in array
                op_index++;//increase index
                asci_index++;//increase index

            }
            else if(c=='=')
            {
                equal_flag=1;
                for(x=0;x<=(op_index);x++)
                {
                    for(y=op_index-1;y>=0;y--)//to get min in piority and see which come first from left to right if we have two in same piroty
                    {
                        if(o[y]==0)
                            continue;
                        if(min>=o[y]||min==999)

                        {   if(index>1)
                            {
                            min=o[y];
                            min_index=y;
                              }
                        else   {
                            min=o[0];
                            min_index=0;
                                 }
                          }
                    }

                    if(min==2&&asci[min_index]=='+')//add
                    {
                        if(index>1)
                            total=a[min_index]+a[min_index+1];
                        else
                            total=a[0]+a[1];
                    }
                    else if(min==2&&asci[min_index]=='-')//sub
                    {
                        if(index>1)
                            total=a[min_index]-a[min_index+1];
                        else
                            total=a[0]-a[1];
                    }
                    else if(min==1&&asci[min_index]=='/')//div
                    {
                        if(index>1)
                            total=a[min_index]/ a[min_index+1];
                        else
                            total=a[0]/a[1];
                    }
                    else if(min==1&&asci[min_index]=='*')//mul
                    {  if(index>1)
                        total=a[min_index]*a[min_index+1];
                    else
                        total=a[0]*a[1];
                    }
                    //flag=0;
                    if(index>1)
                    {

                        for(int z=min_index;z<5-1;z++)//to sort and decrease size of array of number by 1
                        {
                            a[z]=a[z+1];

                        }
                        for(int z=min_index;z<5-1;z++)//to sort and decrease size of array of number by 1
                        {
                            o[z]=o[z+1];
                            asci[z]=asci[z+1];

                        }
                    }

                    index--;
                    op_index--;
                    min=999;
                    a[min_index]=total;//put total into array of number to make on it second ooeration
                    //o[min_index]=999;
                    //m_flag=0;
                }
                //LCD_u32_Write_Number(total);

            }

            if(op_flag!=1)
            {
                num=c-'0';//to get number by convert charc to decimal;
                n=n*10+num;//equation to get full number until it press an operaation
                a[index]=n;
            }
            else
            {
                op_flag=0;
                index++;
                n=0;
            }
            if(equal_flag==1)
            {
                LCD_u32_Write_Number(total);//write answer
                delay_ms(500);

            }
        }

    }
    return 0;
}
/*   if you want to restart again the operation
                equal_flag=0;
                LCD_clearScreen();
                for(int i=0;i<index;i++)
                {
                    a[i]=0;
                    o[i]=0;
                }

                index=0;
                total=0;
                n=0;
                num=0;
                op_index=0;
                min=999;
                x=0;
                y=0;
 */
