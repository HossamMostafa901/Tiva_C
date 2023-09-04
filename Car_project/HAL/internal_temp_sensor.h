/*
 * internal_temp_sensor.h
 *
 *  Created on: Aug 31, 2023
 *      Author: ZYZ
 */

#ifndef INTERNAL_TEMP_SENSOR_H_
#define INTERNAL_TEMP_SENSOR_H_

#include <stdint.h>

/* *************************************************************
 * Functions Declaration
 * *************************************************************/
void internalTempSensor_init(void);

uint32_t internalTempSensor_GetReading(void);


#endif /* INTERNAL_TEMP_SENSOR_H_ */
