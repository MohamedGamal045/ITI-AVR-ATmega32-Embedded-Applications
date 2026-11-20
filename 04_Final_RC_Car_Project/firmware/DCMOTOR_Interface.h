


#ifndef HAL_DCMOTOR_INTERFACE_H_
#define HAL_DCMOTOR_INTERFACE_H_

#include "STD_TYPES.h"

/* Direction options for motors */
#define DCMOTOR_CW    0
#define DCMOTOR_CCW   1
#define DCMOTOR_STOP  2

void DCMOTOR_voidInit(void);
void DCMOTOR_voidRotateMotorA(u8 Copy_u8Direction);
void DCMOTOR_voidRotateMotorB(u8 Copy_u8Direction);
void DCMOTOR_voidRotateMotorC(u8 Copy_u8Direction);
void DCMOTOR_voidRotateMotorD(u8 Copy_u8Direction);

#endif /* HAL_DCMOTOR_INTERFACE_H_ */

