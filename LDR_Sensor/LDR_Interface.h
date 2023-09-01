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

void LDR_Right(void);
void READ_Right(uint32_t * Copy_Parmeter);
void LDR_Left(void);
void READ_LEFT(uint32_t * Copy_Parmeter);
DIR_t CMP (void);

#endif /* LDR_INTERFACE_H_ */
