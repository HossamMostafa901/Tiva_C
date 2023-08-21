/*
 * bitwise_operation.h
 *
 *  Created on: Aug 13, 2023
 *      Author: ZYZ
 */

#ifndef BITWISE_OPERATION_H_
#define BITWISE_OPERATION_H_

#define GET_BIT(REG,BIT)    ((REG >> BIT) & 1)
#define SET_BIT(REG,BIT)    (REG |=  (1 << BIT))
#define CLR_BIT(REG,BIT)    (REG &= ~(1 << BIT))
#define TGL_BIT(REG,BIT)    (REG ^=  (1 << BIT))

#endif /* BITWISE_OPERATION_H_ */
