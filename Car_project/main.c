/*
 * main.c
 *
 *  Created on: Aug 31, 2023
 *      Author: Mohamed Abdelazez
 */
#include "internal_temp_sensor.h"
#include "lcd.h"
#include "delay.h"
#include "DIO.h"
#include "dc_motor.h"
#include "LDR_Interface.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ULTRASONIC_interface.h"

/* ************************************************
 *                Global variables
 * ************************************************/
uint32_t READ_R;
uint32_t READ_L;
extern float Distance;

/* *************************************************
 *                Main Function
 * *************************************************/
int main(void)
{
    /* initializations */
    LCD_init();
    internalTempSensor_init();
    DcMotor_init();
    PWM_init(45);
    LDR_Rightinit();
    LDR_Leftinit();
    Ultrasonic_Init();

    /* infinity loop */
    while(1)
    {
        LCD_displayStringRowColumn(0 , 0 , "Temp: ");
        LCD_writeNumber(internalTempSensor_GetReading() , 0 , 6);
        LCD_displayStringRowColumn(0 , 8 , " C");

        LCD_displayStringRowColumn(1 , 0 , "Distance: ");
        LCD_writeNumber(Distance , 1 , 10);
        LCD_displayStringRowColumn(1 , 14 , "cm");

        LDR_RightRead(&READ_R);
        LDR_LeftRead(&READ_L);

        trigger_measurement();

        if(Distance < 5)
        {
            DcMotor_rotate(FR_MOTOR, FORWARD_DIRECTION);
            DcMotor_rotate(FL_MOTOR, BACKWARD_DIRECTION);

            _delay_ms(500);

            DcMotor_rotate(FR_MOTOR, STOP);
            DcMotor_rotate(FL_MOTOR, STOP);

        }
        else
        {
            if(LDR_Compare() == RIGHT)
            {
                DcMotor_rotate(FR_MOTOR, STOP);
                DcMotor_rotate(FL_MOTOR, FORWARD_DIRECTION);
            }
            else if(LDR_Compare() == LEFT)
            {
                DcMotor_rotate(FR_MOTOR, FORWARD_DIRECTION);
                DcMotor_rotate(FL_MOTOR, STOP);
            }
            else
            {
                DcMotor_rotate(FR_MOTOR, STOP);
                DcMotor_rotate(FL_MOTOR, STOP);
            }
        }
    }
}



