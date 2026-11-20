/*
 * DIO_program.c
 *
 *  Created on: Aug 24, 2025
 *      Author: MG
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_register.h"
#include "DIO_config.h"
#include "DIO_private.h"
#include "DIO_interface.h"




u8 DIO_SetPinDirection(u8 port_name , u8 pin_number, u8 pin_value)
{
   u8 status = 1;

   if(port_name > _PORTD || port_name < _PORTA)
   {
	 return status = 0;
   }

   if (pin_number > PIN7 || pin_number < PIN0)
   {
	  return status = 0;
   }

   if (pin_value > OUTPUT || pin_value < INPUT)
   {
	  return status = 0;
   }

   switch(port_name)
   {
   case _PORTA:
	   if(pin_value == OUTPUT)
	   {
		   SET_BIT(DDRA , pin_number);
	   }
	   else if (pin_value == INPUT)
	   {

		   CLR_BIT(DDRA , pin_number);
	   }

   break;


   case _PORTB:
	   if(pin_value == OUTPUT)
	   {
		   SET_BIT(DDRB , pin_number);
	   }
	   else if (pin_value == INPUT)
	   {

		   CLR_BIT(DDRB , pin_number);
	   }

   break;

   case _PORTC:

	   if(pin_value == OUTPUT)
	   {
		   SET_BIT(DDRC , pin_number);
	   }
	   else if (pin_value == INPUT)
	   {
		   CLR_BIT(DDRC , pin_number);
	   }


   break;


   case _PORTD:

	   if(pin_value == OUTPUT)
	   {
		   SET_BIT(DDRD , pin_number);
	   }
	   else if (pin_value == INPUT)
	   {

		   CLR_BIT(DDRD , pin_number);
	   }


   break;
   }


   return status;
}



u8 DIO_SetPinValue(u8 port_name,u8 pin_number ,u8 pin_status)
{
	 u8 status = 1;

	   if(port_name > _PORTD || port_name < _PORTA)
	   {
		 return status = 0;
	   }

	   if (pin_number > PIN7 || pin_number < PIN0)
	   {
		  return status = 0;
	   }

	   if (pin_status > HIGH || pin_status < LOW)
	   {
		  return status = 0;
	   }

	   switch(port_name)
	   {
	   case _PORTA:
		   if(pin_status == HIGH)
		   {
			   SET_BIT(PORTA , pin_number);
		   }
		   else if (pin_status == LOW)
		   {

			   CLR_BIT(PORTA , pin_number);
		   }

	   break;


	   case _PORTB:
		   if(pin_status == HIGH)
		   {
			   SET_BIT(PORTB , pin_number);
		   }
		   else if (pin_status == LOW)
		   {

			   CLR_BIT(PORTB , pin_number);
		   }

	   break;

	   case _PORTC:

		   if(pin_status == HIGH)
		   {
			   SET_BIT(PORTC , pin_number);
		   }
		   else if (pin_status == LOW)
		   {
			   CLR_BIT(PORTC, pin_number);
		   }


	   break;


	   case _PORTD:

		   if(pin_status == HIGH)
		   {
			   SET_BIT(PORTD , pin_number);
		   }
		   else if (pin_status == LOW)
		   {

			   CLR_BIT(PORTD , pin_number);
		   }


	   break;
	   }


	   return status;

}



u8 DIO_SetPortDirection(u8 port_name , u8 port_direction_value)
{
	u8 status = 1;

	if(port_name> _PORTD  || port_name < _PORTA)
	{
		return 0;
	}

	switch(port_name)
	{
	case _PORTA: DDRA = port_direction_value;   break;
	case _PORTB: DDRB = port_direction_value;   break;
	case _PORTC: DDRC = port_direction_value;   break;
	case _PORTD: DDRD = port_direction_value;   break;

	}



	return status;
}



u8 DIO_SetPortvalue(u8 port_name , u8 port_status_value)
{
	u8 status = 1;

	if(port_name> _PORTD  || port_name < _PORTA)
	{
		return 0;
	}

	switch(port_name)
	{
	case _PORTA: PORTA = port_status_value;   break;
	case _PORTB: PORTB = port_status_value;   break;
	case _PORTC: PORTC = port_status_value;   break;
	case _PORTD: PORTD = port_status_value;   break;

	}



    return status;

}


u8 DIO_GetPinValue(u8 port_name , u8 pin_number)
{

    u8 status = 0;

	if(port_name> _PORTD  || port_name < _PORTA)
	{
		return 2;
	}

	if (pin_number > PIN7 || pin_number < PIN0)
	 {
		  return 2;
	 }


	switch(port_name)
	{
	case _PORTA: status = GET_BIT(PINA,pin_number);   break;
	case _PORTB: status = GET_BIT(PINB,pin_number);    break;
	case _PORTC: status = GET_BIT(PINC,pin_number);   break;
	case _PORTD: status = GET_BIT(PIND,pin_number);   break;

	}

	return status;
}


u8 DIO_GetPortValue(u8 port_name)
{
	u8 P_Val;
	switch(port_name)
			{
			case _PORTA:
				P_Val=PINA;
				break;
			case _PORTB:
				P_Val=PINB;
					break;
			case _PORTC:
				P_Val=PINC;
					break;
			case _PORTD:
				P_Val=PIND;
					break;

			}
	return P_Val;
}

u8 DIO_TogglePin(u8 port_name , u8 pin_number)
{
    u8 status = 0;

	if(port_name> _PORTD  || port_name < _PORTA)
	{
		return 2;
	}

	if (pin_number > PIN7 || pin_number < PIN0)
	 {
		  return 2;
	 }


	switch(port_name)
	{
	case _PORTA:  TOG_BIT(PORTA,pin_number);   break;
	case _PORTB:  TOG_BIT(PORTB,pin_number);    break;
	case _PORTC:  TOG_BIT(PORTC,pin_number);   break;
	case _PORTD:  TOG_BIT(PORTD,pin_number);   break;

	}

	return status;

}
