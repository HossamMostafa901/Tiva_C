/*
 * DIO.c
 *
 *  Created on: Aug 13, 2023
 *      Author: ZYZ
 */
#include "tm4c123gh6pm.h"
#include "bbitwise_operation.h"
#include "std_types.h"
#include "DIO.h"

void DIO_init(uint8 port , uint8 inputPins , uint8 outputPins)
{
    uint8 usedPins = inputPins | outputPins;

    SET_BIT(SYSCTL_RCGCGPIO_R,port);                   /* Activate PORT clock */
    while(GET_BIT(SYSCTL_RCGCGPIO_R,port) == 0);       /* Check if PORT clock is activated */

    switch(port)
    {
    case (PORTA):

    GPIO_PORTA_LOCK_R = 0x4C4F434B;                    /* Unlock PORTA pins */
    GPIO_PORTA_CR_R = usedPins;                        /* Enable changes on PORTA used pins */

    if(outputPins != 0)
    {
        GPIO_PORTA_DIR_R = outputPins;                 /* set output pins direction */
    }
    GPIO_PORTA_PUR_R = inputPins;                      /* Pull up input pins */
    GPIO_PORTA_DEN_R = usedPins;                       /* Digital Enable PORTA used pins */
    break;

    case (PORTB):

                break;

    case (PORTC):

                break;

    case (PORTD):

                break;

    case (PORTE):

                break;

    case (PORTF):

    GPIO_PORTF_LOCK_R = 0x4C4F434B;                     /* Unlock PORTF pins */
    GPIO_PORTF_CR_R = usedPins;                         /* Enable changes on PORTF used pins */

    if(outputPins != 0)
    {
        GPIO_PORTF_DIR_R = outputPins;                 /* set output pins direction */
    }
    GPIO_PORTF_PUR_R = inputPins;                      /* Pull up input pins */
    GPIO_PORTF_DEN_R = usedPins;                       /* Digital Enable PORTF used pins */
    break;

    default:
        break;
    }
}

void DIO_WritePin(uint8 port , uint8 pin , uint8 value)
{

    if(value == LOGIC_HIGH)
    {
        switch(port)
        {
        case (PORTA):
                            SET_BIT(GPIO_PORTA_DATA_R,pin);
        break;
        case (PORTB):
                            SET_BIT(GPIO_PORTB_DATA_R,pin);
        break;
        case (PORTC):
                            SET_BIT(GPIO_PORTC_DATA_R,pin);
        break;
        case (PORTD):
                            SET_BIT(GPIO_PORTD_DATA_R,pin);
        break;
        case (PORTE):
                            SET_BIT(GPIO_PORTE_DATA_R,pin);
        break;
        case (PORTF):
                            SET_BIT(GPIO_PORTF_DATA_R,pin);
        break;

        default:
            break;
        }
    }
    else if(value == LOGIC_LOW)
    {
        switch(port)
        {
        case (PORTA):
                            CLR_BIT(GPIO_PORTA_DATA_R,pin);
        break;
        case (PORTB):
                            CLR_BIT(GPIO_PORTB_DATA_R,pin);
        break;
        case (PORTC):
                            CLR_BIT(GPIO_PORTC_DATA_R,pin);
        break;
        case (PORTD):
                            CLR_BIT(GPIO_PORTD_DATA_R,pin);
        break;
        case (PORTE):
                            CLR_BIT(GPIO_PORTE_DATA_R,pin);
        break;
        case (PORTF):
                            CLR_BIT(GPIO_PORTF_DATA_R,pin);
        break;
        default:
            break;
        }
    }
    else
    {
        /* do nothing */
    }


}

uint8 DIO_ReadPin(uint8 port , uint8 pin)
{
    uint8 value;

    switch(port)
    {
    case (PORTA):
                        value = GET_BIT(GPIO_PORTA_DATA_R,pin);
    break;
    case (PORTB):
                        value = GET_BIT(GPIO_PORTB_DATA_R,pin);
    break;
    case (PORTC):
                        value = GET_BIT(GPIO_PORTC_DATA_R,pin);
    break;
    case (PORTD):
                        value = GET_BIT(GPIO_PORTD_DATA_R,pin);
    break;
    case (PORTE):
                        value = GET_BIT(GPIO_PORTE_DATA_R,pin);
    break;
    case (PORTF):
                        value = GET_BIT(GPIO_PORTF_DATA_R,pin);
    break;
    default:
        break;
    }

    return value;
}

void DIO_EnableInterrupt(uint8 port , uint8 pin , detectType detectInput , triggerType triggerInput)
{
    switch(port)
    {
    case (PORTA):

                            break;

    case (PORTB):

                            break;

    case (PORTC):

                            break;

    case (PORTD):

                            break;

    case (PORTE):

                            break;

    case (PORTF):

                if(detectInput == level)
                {
                    SET_BIT(GPIO_PORTF_IS_R,pin);
                    if(triggerInput == bothTriggers)
                    {
                        SET_BIT(GPIO_PORTF_IBE_R , pin);
                    }
                    else
                    {
                        CLR_BIT(GPIO_PORTF_IBE_R , pin);
                        if(triggerInput == risingHigh)
                        {
                            SET_BIT(GPIO_PORTF_IEV_R , pin);
                        }
                        else if(triggerInput == failingLow)
                        {
                            CLR_BIT(GPIO_PORTF_IEV_R , pin);
                        }
                    }
                }
                else if(detectInput == edge)
                {
                    CLR_BIT(GPIO_PORTF_IS_R,pin);
                    if(triggerInput == bothTriggers)
                    {
                        SET_BIT(GPIO_PORTF_IBE_R , pin);
                    }
                    else
                    {
                        CLR_BIT(GPIO_PORTF_IBE_R , pin);
                        if(triggerInput == risingHigh)
                        {
                            SET_BIT(GPIO_PORTF_IEV_R , pin);
                        }
                        else if(triggerInput == failingLow)
                        {
                            CLR_BIT(GPIO_PORTF_IEV_R , pin);
                        }
                    }
                }
    SET_BIT(GPIO_PORTF_IM_R,pin);                   /* Enable interrupt for PORTF pin */
    SET_BIT(NVIC_EN0_R , 30);
    break;
    }
}
