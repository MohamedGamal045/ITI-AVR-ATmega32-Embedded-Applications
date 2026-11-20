/*
 * Timer_Interface.h
 *
 *  Created on: Sep 3, 2025
 *      Author: Dell
 */

#ifndef MCAL_TIMER_INTERFACE_H_
#define MCAL_TIMER_INTERFACE_H_


void Timer0_Init(u8 Mode, u8 Flag, u8 CLK_SRC);


void Timer0_SetFastPWM_Mode(u8 Mode); // only use in Fast PWM

void Timer0_EnableOverFlowInterrupt();

void Timer0_DisableOverFlowInterrupt();

void Timer0_EnableCompareMatchInterrupt();

void Timer0_DisableCompareMatchInterrupt();

void Timer0_SetTCNT0(u8 TCNT0_value);

void Timer0_SetOCR0(u8 OCR0_Value);

void Timer0_SetCallBackOverFlow( void (*CallBack)(void) );

void Timer0_SetCallBackCTC( void (*CallBack)(void) );




//-----------------------------------------------
void Timer1_Init();

void Timer1_Set_OCR1A(u16 OCR1_value );

void Timer1_Set_ICR(u16 ICR_value);



//------------------------------------
void ICU_Init();
void ICU_EnableNoiseCanceler();
void ICU_DisableNoiseCanceler();
u16  ICU_Value();
void ICU_ChangePinMode(u8 mode);
void ICU_EnableInterrupt();
void ICU_DisableInterrupt();
void ICU_SetCallBack(void (*ICU)(void));
//------------------------------------



#endif /* MCAL_TIMER_INTERFACE_H_ */
