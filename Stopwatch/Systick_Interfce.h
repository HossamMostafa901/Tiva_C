/*
 * Systick_Interfce.h
 *
 *  Created on: Aug 24, 2023
 *      Author: DELL
 */

#ifndef SYSTICK_INTERFCE_H_
#define SYSTICK_INTERFCE_H_

#include"std_types.h"

#define SYS_CLOCK 0
#define PIOSC_4   1

#define Systick_Enable 0
#define Systick_Intern 1
#define CLK_SRC   2
#define Systick_count 16
/*
 * choose option:
 * 1-SYS_CLOCK
 * 2-PIOSC_4
 * */
#define CLK_SRC_SEL SYS_CLOCK

void Systick_Init(void);
void Systick_SetBusyWait(sint32 mSecs);
void systick_interput(sint32 mSecs);


#endif /* SYSTICK_INTERFCE_H_ */
