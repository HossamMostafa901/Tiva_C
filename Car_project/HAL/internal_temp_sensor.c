/*****************************************************************************
 * internal_temp_sensor.c
 *
 *  Created on: Aug 31, 2023
 *      Author: Mohamed Abdelazez
 *
NOTE: The internal temperature sensor is not calibrated.  This example
just takes the raw temperature sensor sample and converts it using the
equation found in the device datasheet for the TM4C123GH6PM.  This equation
applies to all TM4C devices with an internal temperature sensor.

- ADC0 peripheral

Configure ADC0 for the temperature sensor input with a single sample.  Once
 the sample is done, an interrupt flag will be set, and the data will be
 read then displayed on LCD
*******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "internal_temp_sensor.h"


/****************************************************************************
 * Function Definitions
 * *************************************************************************/
void internalTempSensor_init(void)
{
    /*
     * Configure step 0 on sequence 3.  Sample the temperature sensor (ADC_CTL_TS)
     * and configure the interrupt flag (ADC_CTL_IE) to be set when the sample is done.
     * Tell the ADC logic that this is the last conversion on sequence 3 (ADC_CTL_END).
     * Sequence 3 has only one programmable step.
     */

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);                                        /* The ADC0 peripheral must be enabled for use */
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);                      /* Enable sample sequence 3 with a processor signal trigger */
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);  /* comment in description */
    ADCSequenceEnable(ADC0_BASE, 3);                                                   /* Since sample sequence 3 is now configured, it must be enabled. */
    ADCIntClear(ADC0_BASE, 3);                                                         /* Clear the interrupt status flag */
}

uint32_t internalTempSensor_GetReading(void)
{
    uint32_t pui32ADC0Value[1];                                          /* store the data read from the ADC FIFO */
    uint32_t ui32TempValueC;                                             /* store the temperature conversions for Celsius. */

    ADCProcessorTrigger(ADC0_BASE, 3);                                   /* Trigger the ADC conversion */
    while(!ADCIntStatus(ADC0_BASE, 3, false)){}                          /* Wait for conversion to be completed */
    ADCIntClear(ADC0_BASE, 3);                                           /* Clear the ADC interrupt flag */
    ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);                    /* Read ADC Value */
    ui32TempValueC = 147.5 - ((75 * 3.3 * pui32ADC0Value[0]) / 4096);    /* Use non-calibrated conversion provided in the data sheet */
    SysCtlDelay(SysCtlClockGet() / 12);                                  /* The function delay (in cycles) = 3 * parameter.  Delay 250ms arbitrarily.*/

    return ui32TempValueC;
}




