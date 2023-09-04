/*
 * LDR_Interface.h
 *
 *  Created on: Aug 31, 2023
 *      Author: DELL
 */

#ifndef LDR_INTERFACE_H_
#define LDR_INTERFACE_H_

typedef enum {
    FWD,
    LEFT,
    RIGHT,
}DIR_t;

void LDR_Rightinit(void);
void LDR_RightRead(uint32_t * Copy_Parmeter);
void LDR_Leftinit(void);
void LDR_LeftRead(uint32_t * Copy_Parmeter);
DIR_t LDR_Compare (void);

#endif /* LDR_INTERFACE_H_ */
