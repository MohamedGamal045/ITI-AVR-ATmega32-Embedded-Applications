/*
 * main.c
 *
 *  Created on: Sep 2, 2025
 *      Author: MG
 */
#include  <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_Interface.h"
void main()
{

     //Initialize LCD
	 LCD_voidInit();


    //-----------------------------------------------

    //ADC0
    DIO_SetPinDirection(_PORTA,PIN0,INPUT);


    //-----------------------------------------------
     //LED PINS
     DIO_SetPinDirection(_PORTB,PIN0,OUTPUT); //RED
     DIO_SetPinDirection(_PORTB,PIN1,OUTPUT); //Yellow


    //----------------------------------------------

    //Initialize ADC
    ADC_Init();

    u32 reading ;
    u32 millvolt;

    LCD_voidSendString("LDR_Light: ");
	while(1)
	{

		reading = ADC_reading_Poll(ADC0);
        millvolt = (reading*5000)/1023;
        LCD_voidGotoXY(11,0);

        if(millvolt < 2500)
        {
        	DIO_SetPinValue(_PORTB,PIN0,HIGH);
        	DIO_SetPinValue(_PORTB,PIN1,LOW);
        	LCD_voidSendString("Dark");
        }

        else if ( millvolt > 2500)
        {
        	DIO_SetPinValue(_PORTB,PIN0,LOW);
        	DIO_SetPinValue(_PORTB,PIN1,HIGH);
        	LCD_voidSendString("Light");
        }



	}


}
