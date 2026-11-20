#include "util/delay.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"

#define MOTOR_PORT    _PORTB
#define MOTOR_PIN     PIN0

#define BUTTON_PORT   _PORTA
#define BUTTON_PIN    PIN0

int main() {
	u8 motorState = LOW;
	DIO_SetPinDirection(MOTOR_PORT, MOTOR_PIN, PIN_OUTPUT);
	DIO_SetPinDirection(BUTTON_PORT, BUTTON_PIN, PIN_INPUT);

	while (1) {
		if (DIO_GetPinValue(BUTTON_PORT, BUTTON_PIN) == HIGH) {
			_delay_ms(50);

			if (DIO_GetPinValue(BUTTON_PORT, BUTTON_PIN) == HIGH) {
				if (motorState == LOW) {
					motorState = HIGH;
				} else {
					motorState = LOW;
				}
				DIO_SetPinValue(MOTOR_PORT, MOTOR_PIN, motorState);

				while (DIO_GetPinValue(BUTTON_PORT, BUTTON_PIN) == HIGH)
					;
			}
		}
	}

	return 0;
}
