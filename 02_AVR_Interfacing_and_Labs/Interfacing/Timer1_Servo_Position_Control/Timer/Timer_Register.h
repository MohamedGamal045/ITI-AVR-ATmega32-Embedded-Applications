/*
 * Timer_Register.h
 *
 *  Created on: Sep 3, 2025
 *      Author: Dell
 */

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define Timer0_TCCR0          *((volatile u8*)(0x53))
#define Timer0_TCCR0_FOC      7
#define Timer0_TCCR0_WGM00    6
#define Timer0_TCCR0_COM01    5
#define Timer0_TCCR0_COM00    4
#define Timer0_TCCR0_WGM01    3
#define Timer0_TCCR0_CS02     2
#define Timer0_TCCR0_CS01     1
#define Timer0_TCCR0_CS00     0


#define Timer0_TCNT0           *((volatile u8*)(0x52))

#define Timer0_OCR0            *((volatile u8*)(0x5C))

#define TIMSK                  *((volatile u8*)(0x59))
#define TIMSK_TOIE0             0
#define TIMSK_OCIE0             1
#define TIMSK_TOIE1             2
#define TIMSK_OCIE1B            3
#define TIMSK_OCIE1A            4
#define TIMSK_TICIE1            5
#define TIMSK_TOIE2             6
#define TIMSk_OCIE2             7

#define TIFR                   *((volatile u8*)(0x58))
#define TIFR_TOV0              0
#define TIFR_OCF0              1
#define TIFR_TOV1              2
#define TIFR_OCF1B             3
#define TIFR_OCF1A             4
#define TIFR_ICF1              5
#define TIFR_TOV2              6
#define TIFR_OCF2              7



#define Timer1_TCCR1A         *((volatile u8*)(0x4F))
#define Timer1_TCCR1A_COM1A1   7
#define Timer1_TCCR1A_COM1A0   6
#define Timer1_TCCR1A_COM1B1   5
#define Timer1_TCCR1A_COM1B0   4
#define Timer1_TCCR1A_FOC1A    3
#define Timer1_TCCR1A_FOC1B    2
#define Timer1_TCCR1A_WGM11    1
#define Timer1_TCCR1A_WGM10    0


#define Timer1_TCCR1B        *((volatile u8*)(0x4E))
#define Timer1_TCCR1B_ICNC1    7
#define Timer1_TCCR1B_ICES1    6
#define Timer1_TCCR1B_WGM13    4
#define Timer1_TCCR1B_WGM12    3
#define Timer1_TCCR1B_CS12     2
#define Timer1_TCCR1B_CS11     1
#define Timer1_TCCR1B_CS10     0


#define Timer1_TCNT1         *((volatile u16*)(0x4C))

#define Timer1_OCR1A         *((volatile u16*)(0x4A))
#define Timer1_OCR1B         *((volatile u16*)(0x48))
#define Timer1_ICR           *((volatile u16*)(0x46))


#endif /* MCAL_TIMER_REGISTER_H_ */
