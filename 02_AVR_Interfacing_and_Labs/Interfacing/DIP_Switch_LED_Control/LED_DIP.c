/*
 * LED_DIP.c
 *
 *  Created on: Sep 2, 2025
 *      Author: MG
 */
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_register.h"
#include "DIO_config.h"
#include "DIO_private.h"
#include "DIO_interface.h"

int main(void) {

	DIO_SetPortDirection(_PORTB,PORT_OUTPUT);
	DIO_SetPortDirection(_PORTA,PORT_INPUT);
	DIO_SetPortvalue(_PORTA,PORT_HIGH);
	u8 DIP = DIO_GetPortValue(_PORTA);

	while (1)
	{
		DIP = DIO_GetPortValue(_PORTA);
		DIO_SetPortvalue(_PORTB,DIP);
	}
	return 0;
}

