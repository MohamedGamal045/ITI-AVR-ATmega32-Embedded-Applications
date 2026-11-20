// Receiver Code   UART_Recieve_and_Send_PWM


// LIB: Libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL: Microcontroller Abstraction Layer

#include "DIO_interface.h"
#include "USART_interface.h"
#include "Timer_Register.h"
#include "Timer_Private.h"
#include "Timer_Config.h"
#include "Timer_Interface.h"

int main(void)
{
	u8 receivedData;

	// Configure DIO for USART
	DIO_SetPinDirection(_PORTD, PIN0, PIN_INPUT);  // RX Pin
	DIO_SetPinDirection(_PORTD, PIN1, PIN_OUTPUT); // TX Pin

	// Configure DIO for PWM output (OC0)
	// OC0 is on PORTB, PIN3 on ATmega32
	DIO_SetPinDirection(_PORTB, PIN3, PIN_OUTPUT);

	// Initialize USART
	USART_Init();

	// Initialize Timer0 for Fast PWM mode
	// Mode: Fast PWM
	// Flag: TIMER0_NOFLag (not using interrupts for this simple task)
	// CLK_SRC: TIMER_CLK_64 (you can adjust this for different frequencies)
	Timer0_Init(Fast_PWM, TIMER0_NOFLag, TIMER_CLK_64);

	// Set Timer0 Fast PWM mode to non-inverting
	// This means the PWM pin starts high and clears on compare match.
	Timer0_SetFastPWM_Mode(CLEAR_ON_COMPARE_SET_ON_TOP);

	while (1)
	{
		// Poll for a received byte from the first microcontroller
		receivedData = USART_Poll_u8RecieveData();

		// Set the duty cycle of the PWM based on the received value.
		// A value of 0 results in 0% duty cycle, a value of 255 results in 100% duty cycle.
		Timer0_SetOCR0(receivedData);
	}

	return 0;
}
