/*
 * DIO_interface.h
 *
 *  Created on: Aug 24, 2025
 *      Author: MG
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define _PORTA    1
#define _PORTB    2
#define _PORTC    3
#define _PORTD    4

#define PIN0      0
#define PIN1      1
#define PIN2      2
#define PIN3      3
#define PIN4      4
#define PIN5      5
#define PIN6      6
#define PIN7      7

#define  INPUT    0
#define  OUTPUT   1

#define PIN_INPUT   0
#define PIN_OUTPUT  1

#define HIGH   1
#define LOW    0

#define  PORT_INPUT    0x00
#define  PORT_OUTPUT   0xff

#define PIN_HIGH   1
#define PIN_LOW    0

#define PORT_HIGH   0xff
#define PORT_LOW    0x00

u8 DIO_SetPinDirection(u8 port_name , u8 pin_number, u8 pin_value);
u8 DIO_SetPinValue(u8 port_name,u8 pin_number ,u8 pin_status);
u8 DIO_SetPortDirection(u8 port_name , u8 port_direction_value);
u8 DIO_SetPortvalue(u8 port_name , u8 port_status_value);
u8 DIO_GetPinValue(u8 port_name , u8 pin_number);
u8 DIO_TogglePin(u8 port_name , u8 pin_number);
u8 DIO_GetPortValue(u8 port_name);

/*
 * u8 DIO_SetUpperBitDirection(u8 port_name);
 * u8 DIO_SetUpperBitValue(u8 port_name);
 * u8 DIO_SetMiddleTwoBitDirection(u8 port_name);
 * u8 DIO_SetMiddleTwoBitValue(u8 port_name);
 *
 *
 *
 *
 * */

#endif /* DIO_INTERFACE_H_ */
