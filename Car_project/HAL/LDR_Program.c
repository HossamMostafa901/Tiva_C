/*
 * LDR_Program.c
 *
 *  Created on: Aug 31, 2023
 *      Author: DELL
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "LDR_Interface.h"

extern uint32_t READ_R;
extern uint32_t READ_L;

void LDR_Rightinit(void)
{    /*to enable clock for portE */
    SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    /*****************************************************************************

     Configure ADC0 for a single-ended input and a single sample.  Once the
     sample is ready, an interrupt flag will be set.  Using a polling method,
     the data will be read then displayed on the console via UART0.

    *****************************************************************************/
        /*The ADC0 peripheral must be enabled for use. */
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
        /*GPIOE enabled*/
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        /*PIN3 became ADC0*/
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1);
        /*sequence configre 3,processor genrate trigger one sample*/
        ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
        /*sample sequencer config Sample channel 0 (ADC_CTL_CH0) in
         single-ended mode (default) and configure the interrupt flag
         (ADC_CTL_IE) to be set when the sample is done.  Tell the ADC logic
           that this is the last conversion on sequence 3 (ADC_CTL_END).*/
        ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);
        /*Since sample sequence 3 is now configured, it must be enabled.*/
        ADCSequenceEnable(ADC0_BASE, 1);
        /*interrupt flag is cleared before we sample.*/
            ADCIntClear(ADC0_BASE, 1);
}
void LDR_RightRead(uint32_t* Copy_Parmeter)
{
    /*Trigger the ADC conversion. */
    ADCProcessorTrigger(ADC0_BASE, 1);

      /*Wait for conversion to be completed.*/
            while(!ADCIntStatus(ADC0_BASE, 1, false))
            {
            }
            /*clear Interput flag*/
            ADCIntClear(ADC0_BASE, 1);
            /*Read ADC*/
            ADCSequenceDataGet(ADC0_BASE, 1, Copy_Parmeter);

}
void LDR_Leftinit(void)
{    /*to enable clock for portE */
    SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    /*****************************************************************************

     Configure ADC0 for a single-ended input and a single sample.  Once the
     sample is ready, an interrupt flag will be set.  Using a polling method,
     the data will be read then displayed on the console via UART0.

    *****************************************************************************/
        /*The ADC0 peripheral must be enabled for use. */
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
        /*GPIOE enabled*/
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        /*PIN3 became ADC0*/
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);
        /*sequence configre 3,processor genrate trigger one sample*/
        ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);
        /*sample sequencer config Sample channel 0 (ADC_CTL_CH0) in
         single-ended mode (default) and configure the interrupt flag
         (ADC_CTL_IE) to be set when the sample is done.  Tell the ADC logic
           that this is the last conversion on sequence 3 (ADC_CTL_END).*/
        ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
        /*Since sample sequence 2 is now configured, it must be enabled.*/
        ADCSequenceEnable(ADC0_BASE, 2);
        /*interrupt flag is cleared before we sample.*/
            ADCIntClear(ADC0_BASE, 2);
}
void LDR_LeftRead(uint32_t* Copy_Parmeter)
{
    /*Trigger the ADC conversion. */
    ADCProcessorTrigger(ADC0_BASE, 2);

      /*Wait for conversion to be completed.*/
            while(!ADCIntStatus(ADC0_BASE, 2, false))
            {
            }
            /*clear Interput flag*/
            ADCIntClear(ADC0_BASE, 2);
            /*Read ADC*/
            ADCSequenceDataGet(ADC0_BASE, 2, Copy_Parmeter);

}

DIR_t LDR_Compare(void)
{
    int32_t Val = READ_R - READ_L;
    DIR_t ret;

    if (Val <=150 && Val >=-150)
    {
        ret= FWD;
    }
    else if (Val <0)
    {
        ret= RIGHT;
    }
    else
    {
        ret = LEFT;
    }
    return ret;
}
