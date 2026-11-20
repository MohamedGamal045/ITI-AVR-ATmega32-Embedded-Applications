/*
 * Servo_Program.c
 *
 * Created on: Sep 12, 2025
 * Author: MG
 * Description: Implementation file for the Servo motor driver.
 */

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "Timer_Interface.h"
#include "Timer_Private.h"
#include "Servo_Interface.h"

void Servo_Init(void) {
	DIO_SetPinDirection(SERVO_PORT, SERVO_PIN, PIN_OUTPUT);

	Timer1_Init();

	// 3. Set the PWM period to 20ms by setting the TOP value in the ICR1 register.
	//    With a prescaler of 8, each tick is 1 microsecond (8MHz / 8 = 1MHz).
	//    A 20ms period requires 20,000 ticks, so we set ICR1 to 19999 (since the counter starts from 0).
	Timer1_Set_ICR(19999);
}

void Servo_SetAngle(u8 angle) {
	// Ensure the angle is within a valid range (0-180 degrees)
	if (angle > 180) {
		angle = 180;
	}

	// Convert the angle to a corresponding PWM duty cycle value for OCR1A.
	// The range of OCR1A values is from 1000 (1ms) to 2000 (2ms).
	// The formula is: OCR_value = (angle * (2000 - 1000) / 180) + 1000
	u16 OCR_value = (u16) (((f32) angle * 1000.0 / 180.0) + 1000.0);
	Timer1_Set_OCR1A(OCR_value);
}
