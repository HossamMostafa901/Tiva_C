#include <lcd.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include"LDR_Interface.h"
#include"delay.h"

uint32_t READ_R;
uint32_t READ_L;

int main(void)
{  /*init LDR*/
    DIR_t Dir;
    LCD_init();
    LDR_Right();
    LDR_Left();

    while(1)
    {
        READ_Right(&READ_R);
        READ_LEFT(&READ_L);
        LCD_writeNumber(READ_R, 0, 0);
        _delay_ms(250);
       // LCD_clearScreen();
        LCD_writeNumber(READ_L, 1, 0);
        _delay_ms(250);
        Dir = CMP();
        LCD_writeNumber(Dir, 1, 7);
        _delay_ms(250);
        LCD_clearScreen();
    }
}
