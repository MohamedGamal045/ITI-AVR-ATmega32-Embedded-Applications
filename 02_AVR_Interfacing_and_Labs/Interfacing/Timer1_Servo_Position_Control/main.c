/*
 * main.c
 *
 * Created on: Sep 12, 2025
 * Author: MG
 * Description: Main program to control a servo motor using Timer1.
 */

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "Timer_Interface.h"
#include "Servo_Interface.h"
#include <avr/delay.h>

int main(void) {
	// Initialize the servo motor driver.
	Servo_Init();

	while (1) {
		// Loop to move the servo from 0 to 180 degrees in 10-degree increments.
		for (u8 angle = 0; angle <= 180; angle += 10) {
			// Set the servo to the current angle.
			Servo_SetAngle(angle);

			// Wait for 1 second before moving to the next angle.
			_delay_ms(1000);
		}

		_delay_ms(1000); // Wait for 1 seconds at 180 before returning
		Servo_SetAngle(0);
		_delay_ms(1000); // Wait for 1 second at 0 before starting the loop again
	}

	return 0;
}
