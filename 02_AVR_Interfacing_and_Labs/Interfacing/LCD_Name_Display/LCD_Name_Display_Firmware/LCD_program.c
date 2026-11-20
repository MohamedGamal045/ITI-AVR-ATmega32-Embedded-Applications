/*
 * LCD_program.c
 *
 *  Created on: Aug 26, 2025
 *      Author: Mohammed Gamal
 */


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include  <util/delay.h>

#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_Interface.h"



void _voidSetPins(void)
{
	DIO_SetPortDirection(DATA_PORT, 0xff);// portA , out
	DIO_SetPinDirection(CONTROL_PORT,RS_PIN, OUTPUT);// PORTB , RS, out
	DIO_SetPinDirection(CONTROL_PORT, RW_PIN, OUTPUT);// PORTB , Rw, out
	DIO_SetPinDirection(CONTROL_PORT, E_PIN, OUTPUT);// PORTB , E, out

}

void _voidLCDSendCommend(u8 Command)// functoin set
{
	// RS --> 0 RW --> 0
	DIO_SetPinValue(CONTROL_PORT, RS_PIN, PIN_LOW);
	DIO_SetPinValue(CONTROL_PORT, RW_PIN, PIN_LOW);
	// Data ---> Data port
	DIO_SetPortvalue(DATA_PORT, Command);
	// enable  pulse
	DIO_SetPinValue(CONTROL_PORT, E_PIN, PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(CONTROL_PORT, E_PIN, PIN_LOW);
}

void LCD_voidInit(void)
{

	_voidSetPins();
	_delay_ms(40);//30ms
	_voidLCDSendCommend(0b00111000);// function set n, line desblay --> 1 f, font size 5*7--> 0 XX--> 00
	_delay_ms(1);//39micros
	_voidLCDSendCommend(0b00001100);// display ON Curser OFF blink off
	_delay_ms(1);//39micros
	_voidLCDSendCommend(0b00000001);// Display Clear
	_delay_ms(2);// 1ms
	_voidLCDSendCommend(0b00000110);//Entry Mode ,NO shift , AC increment
}

void LCD_voidSendCharacter(u8 Copy_u8char )
{
	// RS --> 0 RW --> 0
	DIO_SetPinValue(CONTROL_PORT, RS_PIN, PIN_HIGH);
	DIO_SetPinValue(CONTROL_PORT, RW_PIN, PIN_LOW);
	// Data ---> Data port
	DIO_SetPortvalue(DATA_PORT, Copy_u8char);
	// enable  pulse
	DIO_SetPinValue(CONTROL_PORT, E_PIN, PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(CONTROL_PORT, E_PIN, PIN_LOW);


}
void LCD_voidSendString(u8* pu8_String)
{

	while ( *pu8_String != '\0')
	{
		LCD_voidSendCharacter(*pu8_String);
		pu8_String ++;
	}

}


void LCD_voidSendNumber(u32 Copy_u32Number)
{

	u8 arr[10];
	u8 i = 0;


	if (Copy_u32Number == 0)
	{
		LCD_voidSendCharacter('0');
		return;
	}

	while (Copy_u32Number > 0)
	{
		arr[i++] = (Copy_u32Number % 10) + '0';
		Copy_u32Number /= 10;
	}


	while (i > 0)
	{
		LCD_voidSendCharacter(arr[--i]);
	}

}



void LCD_voidGotoXY(u8 Copy_u8Colume ,u8 Copy_u8Row)
{

	u8 finalAddress;
	if(Copy_u8Row == 0)
	{
		finalAddress = 0x00+ Copy_u8Colume ;
	}
	else if (Copy_u8Row == 1)
	{
		finalAddress = 0x40 + Copy_u8Colume;

		// 0b10000000 = 128

	}

	_voidLCDSendCommend(128 + finalAddress);



}

void LCD_voidClearDisplay(void)
{

	_voidLCDSendCommend(0x01);
	_delay_ms(1);
}
