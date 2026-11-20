/*
 * Timer_Private.h
 *
 *  Created on: Sep 3, 2025
 *      Author: Dell
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define Normal_Mode            0    //0b00
#define PWM_PhaseCorrect       1    //0b01
#define CTC                    2    //0b10
#define Fast_PWM               3    //0b11

#define TIMER0_OVF             1
#define TIMER0_CTCF            2
#define TIMER0_NOFLag          3

#define CLEAR_ON_COMPARE_SET_ON_TOP      1
#define SET_ON_COMPARE_CLEAR_ON_TOP      2



#define TIMER_CLK_STOP        0b000
#define TIMER_CLK_SYSTEM      0b001
#define TIMER_CLK_8           0b010
#define TIMER_CLK_64          0b011
#define TIMER_CLK_256         0b100
#define TIMER_CLK_1024        0b101
#define TIMER_CLK_CLEAR_BITS   0b11111000


#define Falling_Edge       0
#define Rising_Edge        1


#endif /* MCAL_TIMER_PRIVATE_H_ */
