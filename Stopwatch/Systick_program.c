/*
 * Systick.program.c
 *
 *  Created on: Aug 24, 2023
 *      Author: DELL
 */
#include"tm4c123gh6pm.h"
#include"Bitwise_operation.h"
#include"Systick_Interfce.h"
#include"std_types.h"
void Systick_Init(void)
{ NVIC_ST_CURRENT_R=0;
    // select clk source for systick
            #if (CLK_SRC_SEL == SYS_CLOCK)
                        {
                            Set_Bit(NVIC_ST_CTRL_R, CLK_SRC);
                        }
            #elif (CLK_SRC_SEL == PIOSC_4)
                        {
                            Clear_bit(NVIC_ST_CTRL_R, CLK_SRC);
                        }
            #endif

           // disable interupts initially
                        Clear_Bit(NVIC_ST_CTRL_R,Systick_Intern);
           // disable timer intitially
                        Clear_Bit(NVIC_ST_CTRL_R,Systick_Enable);

}
void Systick_SetBusyWait(sint32 mSecs)
{  // disable interput

    Clear_Bit(NVIC_ST_CTRL_R,Systick_Intern);
    // load time into reload register
    NVIC_ST_RELOAD_R=(mSecs*16*1000)-1;
    // enable timer
    Set_Bit(NVIC_ST_CTRL_R,Systick_Enable);
    // poll for the count flag
    while(get_bit(NVIC_ST_CTRL_R,Systick_count)==0);
    // disable timer
    Clear_Bit(NVIC_ST_CTRL_R,Systick_Enable);

}
void systick_interput(sint32 mSecs)
{   // enable interput
    Set_Bit(NVIC_ST_CTRL_R,Systick_Intern);
    // load time into reload register
        NVIC_ST_RELOAD_R=(mSecs*16*1000)-1;
        // enable timer
       Set_Bit(NVIC_ST_CTRL_R,Systick_Enable);

}




