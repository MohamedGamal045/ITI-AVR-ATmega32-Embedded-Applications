/*
 * main.c
 *
 * Created on: Sep 12, 2025
 * Author: MG
 */

//UART_Send_Keypad

// LIB: Libraries
#include "STD_TYPES.h"
#include <util/delay.h>

// MCAL: Microcontroller Abstraction Layer
#include "DIO_interface.h"
#include "USART_interface.h"

// HAL: Hardware Abstraction Layer
#include "Keypad_interface.h"


int main(void) {
	// Configure DIO for Keypad (Keypad_init() handles this)
	// Keypad is on PORTC as per Keypad_config.h
	Keypad_voidInit();

	// Configure DIO for USART
	DIO_SetPinDirection(_PORTD, PIN0, PIN_INPUT);  // RX Pin
	DIO_SetPinDirection(_PORTD, PIN1, PIN_OUTPUT); // TX Pin

	// Initialize USART
	USART_Init();

	u8 pressedKey;

	while (1) {
		// Get the pressed key from the keypad
		pressedKey = Keypad_u8GetPressedKey();

		// Check if a valid key was pressed
		if (pressedKey != NO_PRESSED_KEY) {
			// Send the numerical value of the pressed key via USART
			USART_Poll_voidSendData(pressedKey);

			// Small delay to debounce and prevent multiple transmissions from one press
			_delay_ms(100);
		}
	}

	return 0;
}
