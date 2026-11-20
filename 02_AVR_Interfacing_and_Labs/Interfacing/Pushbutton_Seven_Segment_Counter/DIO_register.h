/*
 * DIO_register.h
 *
 *  Created on: Aug 24, 2025
 *      Author: MG
 */

#ifndef DIO_REGISTER_H_
#define DIO_REGISTER_H_

#define DDRA         *((volatile u8*)(0x3A))// Data Direction Register  ---pinMode (pin,INPUT/OUTPUT)
#define PORTA        *((volatile u8*)(0x3B))// Input Pins Address----------> digitalWrite(pin,HIGH/LOW)
#define PINA         *((volatile u8*)(0x39))// Data Register----------> digitalRead(pin)

#define DDRB         *((volatile u8*)(0x37))
#define PORTB        *((volatile u8*)(0x38))
#define PINB         *((volatile u8*)(0x36))


#define DDRC         *((volatile u8*)(0x34))
#define PORTC        *((volatile u8*)(0x35))
#define PINC         *((volatile u8*)(0x33))


#define DDRD         *((volatile u8*)(0x31))
#define PORTD        *((volatile u8*)(0x32))
#define PIND         *((volatile u8*)(0x30))

#endif /* DIO_REGISTER_H_ */
