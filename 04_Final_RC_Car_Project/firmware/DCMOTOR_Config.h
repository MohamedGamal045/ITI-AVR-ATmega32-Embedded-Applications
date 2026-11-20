/*
 * DCMOTOR_Config.h
 *
 *  Created on: Sep 15, 2025
 *      Author: Omar
 */

#ifndef HAL_DCMOTOR_CONFIG_H_
#define HAL_DCMOTOR_CONFIG_H_

#include "DIO_interface.h"

/* ====== DC Motor Configuration ======
 * Motor A Direction Pins
 */
#define DCMOTOR_A_PORT    _PORTA
#define DCMOTOR_A_IN1     PIN0
#define DCMOTOR_A_IN2     PIN1

// Motor B Direction Pins
#define DCMOTOR_B_PORT    _PORTA
#define DCMOTOR_B_IN1     PIN2
#define DCMOTOR_B_IN2     PIN3

// Motor C Direction Pins

#define DCMOTOR_C_PORT    _PORTA
#define DCMOTOR_C_IN1     PIN4
#define DCMOTOR_C_IN2     PIN5

// Motor D Direction Pins
#define DCMOTOR_D_PORT    _PORTA
#define DCMOTOR_D_IN1     PIN6
#define DCMOTOR_D_IN2     PIN7



#endif /* HAL_DCMOTOR_CONFIG_H_ */
