/*
 * Servo_Interface.h
 *
 * Created on: Sep 12, 2025
 * Author: MG
 * Description: Header file for the Servo motor driver.
 */

#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

#include "STD_TYPES.h"
#include "DIO_interface.h"

#define SERVO_PORT     _PORTD
#define SERVO_PIN      PIN5


void Servo_Init(void);


void Servo_SetAngle(u8 angle);

#endif /* SERVO_INTERFACE_H_ */
