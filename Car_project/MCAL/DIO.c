/*
 * DIO.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Mohamed Abdelazez
 */
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "std_types.h"
#include "DIO.h"

void DIO_init(uint8 port , uint8 inputPins , uint8 outputPins)
{
    uint8 usedPins = inputPins | outputPins;

    SET_BIT(SYSCTL_RCGCGPIO_R,port);                   /* Activate PORT clock */
    while(GET_BIT(SYSCTL_RCGCGPIO_R,port) == 0);       /* Check if PORT clock is activated */

    switch(port)
    {
    /* ......... PORTA ............*/
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

    /* ......... PORTB ............*/
    case (PORTB):

    GPIO_PORTB_LOCK_R = 0x4C4F434B;                    /* Unlock PORTB pins */
    GPIO_PORTB_CR_R = usedPins;                        /* Enable changes on PORTB used pins */

    if(outputPins != 0)
    {
        GPIO_PORTB_DIR_R = outputPins;                 /* set output pins direction */
    }
    GPIO_PORTB_PUR_R = inputPins;                      /* Pull up input pins */
    GPIO_PORTB_DEN_R = usedPins;                       /* Digital Enable PORTB used pins */
    break;

    /* ......... PORTC ............*/
    case (PORTC):
    GPIO_PORTC_LOCK_R = 0x4C4F434B;                    /* Unlock PORTC pins */
    GPIO_PORTC_CR_R = usedPins;                        /* Enable changes on PORTC used pins */

    if(outputPins != 0)
    {
        GPIO_PORTC_DIR_R = outputPins;                 /* set output pins direction */
    }
    GPIO_PORTC_PUR_R = inputPins;                      /* Pull up input pins */
    GPIO_PORTC_DEN_R = usedPins;                       /* Digital Enable PORTC used pins */
    break;

    /* ......... PORTD ............*/
    case (PORTD):
    GPIO_PORTD_LOCK_R = 0x4C4F434B;                    /* Unlock PORTD pins */
    GPIO_PORTD_CR_R = usedPins;                        /* Enable changes on PORTD used pins */

    if(outputPins != 0)
    {
       GPIO_PORTD_DIR_R = outputPins;                  /* set output pins direction */
    }
    GPIO_PORTD_PUR_R = inputPins;                      /* Pull up input pins */
    GPIO_PORTD_DEN_R = usedPins;                       /* Digital Enable PORTD used pins */
    break;

    /* ......... PORTE ............*/
    case (PORTE):
    GPIO_PORTE_LOCK_R = 0x4C4F434B;                    /* Unlock PORTE pins */
    GPIO_PORTE_CR_R = usedPins;                        /* Enable changes on PORTE used pins */

    if(outputPins != 0)
    {
        GPIO_PORTE_DIR_R = outputPins;                 /* set output pins direction */
    }
    GPIO_PORTE_PUR_R = inputPins;                      /* Pull up input pins */
    GPIO_PORTE_DEN_R = usedPins;                       /* Digital Enable PORTE used pins */
    break;

    /* ......... PORTF ............*/
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

void DIO_PinDirection(uint8 port , uint8 pin , directionType direction)
{
    if(direction == outputPin)
    {
        switch(port)
        {
        case (PORTA):
                                        SET_BIT(GPIO_PORTA_DIR_R,pin);
        break;
        case (PORTB):
                                        SET_BIT(GPIO_PORTB_DIR_R,pin);
        break;
        case (PORTC):
                                        SET_BIT(GPIO_PORTC_DIR_R,pin);
        break;
        case (PORTD):
                                        SET_BIT(GPIO_PORTD_DIR_R,pin);
        break;
        case (PORTE):
                                        SET_BIT(GPIO_PORTE_DIR_R,pin);
        break;
        case (PORTF):
                                        SET_BIT(GPIO_PORTF_DIR_R,pin);
        break;

        default:
            break;
        }
    }
    else if(direction == inputPin)
    {
        switch(port)
        {
        case (PORTA):
                                        CLR_BIT(GPIO_PORTA_DIR_R,pin);
        break;
        case (PORTB):
                                        CLR_BIT(GPIO_PORTB_DIR_R,pin);
        break;
        case (PORTC):
                                        CLR_BIT(GPIO_PORTC_DIR_R,pin);
        break;
        case (PORTD):
                                        CLR_BIT(GPIO_PORTD_DIR_R,pin);
        break;
        case (PORTE):
                                        CLR_BIT(GPIO_PORTE_DIR_R,pin);
        break;
        case (PORTF):
                                        CLR_BIT(GPIO_PORTF_DIR_R,pin);
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

void DIO_EnableInterrupt(uint8 port , uint8 pin , detectType detectInput , triggerType triggerInput)
{
    switch(port)
    {
    /* .......... PORTA ..........*/
    case (PORTA):

            if(detectInput == level)
            {
                SET_BIT(GPIO_PORTA_IS_R,pin);
                if(triggerInput == bothTriggers)
                {
                    SET_BIT(GPIO_PORTA_IBE_R , pin);
                }
                else
                {
                    CLR_BIT(GPIO_PORTA_IBE_R , pin);
                    if(triggerInput == risingHigh)
                    {
                        SET_BIT(GPIO_PORTA_IEV_R , pin);
                    }
                    else if(triggerInput == failingLow)
                    {
                        CLR_BIT(GPIO_PORTA_IEV_R , pin);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
            else if(detectInput == edge)
            {
                CLR_BIT(GPIO_PORTA_IS_R,pin);
                if(triggerInput == bothTriggers)
                {
                    SET_BIT(GPIO_PORTA_IBE_R , pin);
                }
                else
                {
                    CLR_BIT(GPIO_PORTA_IBE_R , pin);
                    if(triggerInput == risingHigh)
                    {
                        SET_BIT(GPIO_PORTA_IEV_R , pin);
                    }
                    else if(triggerInput == failingLow)
                    {
                        CLR_BIT(GPIO_PORTA_IEV_R , pin);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
            else
            {
                /* Do nothing */
            }
    SET_BIT(GPIO_PORTA_IM_R,pin);                   /* Enable interrupt for PORTA pin */
    SET_BIT(NVIC_EN0_R , INT_GPIOA - 16);
    break;

    /* .......... PORTB ..........*/
    case (PORTB):

                if(detectInput == level)
                {
                    SET_BIT(GPIO_PORTB_IS_R,pin);
                    if(triggerInput == bothTriggers)
                    {
                        SET_BIT(GPIO_PORTB_IBE_R , pin);
                    }
                    else
                    {
                        CLR_BIT(GPIO_PORTB_IBE_R , pin);
                        if(triggerInput == risingHigh)
                        {
                            SET_BIT(GPIO_PORTB_IEV_R , pin);
                        }
                        else if(triggerInput == failingLow)
                        {
                            CLR_BIT(GPIO_PORTB_IEV_R , pin);
                        }
                        else
                        {
                            /* Do nothing */
                        }
                    }
                }
                else if(detectInput == edge)
                {
                    CLR_BIT(GPIO_PORTB_IS_R,pin);
                    if(triggerInput == bothTriggers)
                    {
                        SET_BIT(GPIO_PORTB_IBE_R , pin);
                    }
                    else
                    {
                        CLR_BIT(GPIO_PORTB_IBE_R , pin);
                        if(triggerInput == risingHigh)
                        {
                            SET_BIT(GPIO_PORTB_IEV_R , pin);
                        }
                        else if(triggerInput == failingLow)
                        {
                            CLR_BIT(GPIO_PORTB_IEV_R , pin);
                        }
                        else
                        {
                            /* Do nothing */
                        }
                    }
                }
                else
                {
                    /* Do nothing */
                }
     SET_BIT(GPIO_PORTB_IM_R,pin);                   /* Enable interrupt for PORTB pin */
     SET_BIT(NVIC_EN0_R , INT_GPIOB - 16);
     break;
    /* .......... PORTC ..........*/
    case (PORTC):

            if(detectInput == level)
            {
                SET_BIT(GPIO_PORTC_IS_R,pin);
                if(triggerInput == bothTriggers)
                {
                    SET_BIT(GPIO_PORTC_IBE_R , pin);
                }
                else
                {
                    CLR_BIT(GPIO_PORTC_IBE_R , pin);
                    if(triggerInput == risingHigh)
                    {
                        SET_BIT(GPIO_PORTC_IEV_R , pin);
                    }
                    else if(triggerInput == failingLow)
                    {
                        CLR_BIT(GPIO_PORTC_IEV_R , pin);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
            else if(detectInput == edge)
            {
                CLR_BIT(GPIO_PORTC_IS_R,pin);
                if(triggerInput == bothTriggers)
                {
                    SET_BIT(GPIO_PORTC_IBE_R , pin);
                }
                else
                {
                    CLR_BIT(GPIO_PORTC_IBE_R , pin);
                    if(triggerInput == risingHigh)
                    {
                        SET_BIT(GPIO_PORTC_IEV_R , pin);
                    }
                    else if(triggerInput == failingLow)
                    {
                        CLR_BIT(GPIO_PORTC_IEV_R , pin);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
            else
            {
                /* Do nothing */
            }
    SET_BIT(GPIO_PORTC_IM_R,pin);                   /* Enable interrupt for PORTC pin */
    SET_BIT(NVIC_EN0_R , INT_GPIOC - 16);
    break;

    /* .......... PORTD ..........*/
    case (PORTD):

            if(detectInput == level)
            {
                SET_BIT(GPIO_PORTD_IS_R,pin);
                if(triggerInput == bothTriggers)
                {
                    SET_BIT(GPIO_PORTD_IBE_R , pin);
                }
                else
                {
                    CLR_BIT(GPIO_PORTD_IBE_R , pin);
                    if(triggerInput == risingHigh)
                    {
                        SET_BIT(GPIO_PORTD_IEV_R , pin);
                    }
                    else if(triggerInput == failingLow)
                    {
                        CLR_BIT(GPIO_PORTD_IEV_R , pin);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
            else if(detectInput == edge)
            {
                CLR_BIT(GPIO_PORTF_IS_R,pin);
                if(triggerInput == bothTriggers)
                {
                    SET_BIT(GPIO_PORTD_IBE_R , pin);
                }
                else
                {
                    CLR_BIT(GPIO_PORTD_IBE_R , pin);
                    if(triggerInput == risingHigh)
                    {
                        SET_BIT(GPIO_PORTD_IEV_R , pin);
                    }
                    else if(triggerInput == failingLow)
                    {
                        CLR_BIT(GPIO_PORTD_IEV_R , pin);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
            else
            {
                /* Do nothing */
            }
            SET_BIT(GPIO_PORTD_IM_R,pin);                   /* Enable interrupt for PORTD pin */
            SET_BIT(NVIC_EN0_R , INT_GPIOD - 16);
            break;
                   
    /* .......... PORTE ..........*/
    case (PORTE):

        if(detectInput == level)
            {
                SET_BIT(GPIO_PORTE_IS_R,pin);
                if(triggerInput == bothTriggers)
                {
                    SET_BIT(GPIO_PORTE_IBE_R , pin);
                }
                else
                {
                    CLR_BIT(GPIO_PORTE_IBE_R , pin);
                    if(triggerInput == risingHigh)
                    {
                        SET_BIT(GPIO_PORTE_IEV_R , pin);
                    }
                    else if(triggerInput == failingLow)
                    {
                        CLR_BIT(GPIO_PORTE_IEV_R , pin);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
            else if(detectInput == edge)
            {
                CLR_BIT(GPIO_PORTE_IS_R,pin);
                if(triggerInput == bothTriggers)
                {
                    SET_BIT(GPIO_PORTE_IBE_R , pin);
                }
                else
                {
                    CLR_BIT(GPIO_PORTE_IBE_R , pin);
                    if(triggerInput == risingHigh)
                    {
                        SET_BIT(GPIO_PORTE_IEV_R , pin);
                    }
                    else if(triggerInput == failingLow)
                    {
                        CLR_BIT(GPIO_PORTE_IEV_R , pin);
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
            else
            {
                /* Do nothing */
            }
            SET_BIT(GPIO_PORTE_IM_R,pin);                   /* Enable interrupt for PORTE pin */
            SET_BIT(NVIC_EN0_R , INT_GPIOE - 16);
            break;

    /* .......... PORTF ..........*/
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
            else
            {
                /* Do nothing */
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
            else
            {
                /* Do nothing */
            }
        }
    }
    else
    {
        /* Do nothing */
    }
    SET_BIT(GPIO_PORTF_IM_R,pin);                   /* Enable interrupt for PORTF pin */
    SET_BIT(NVIC_EN0_R , INT_GPIOF - 16);
    break;
    }
}
