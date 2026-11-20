/*
 * Timer_program.c
 *
 *  Created on: Sep 3, 2025
 *      Author: Dell
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "Timer_Register.h"
#include "Timer_Private.h"
#include "Timer_Config.h"
#include "Timer_Interface.h"

static void (*ISR_overflow)(void);
static void (*ISR_CTC)(void);
static void (*ISR_ICU)(void);


void Timer0_Init(u8 Mode, u8 Flag, u8 CLK_SRC)
{
	//SET Mode
	if(Mode == Normal_Mode)
	{
		CLR_BIT(Timer0_TCCR0,Timer0_TCCR0_WGM01);
		CLR_BIT(Timer0_TCCR0,Timer0_TCCR0_WGM00);
	}
	else if (Mode == CTC)
	{
		SET_BIT(Timer0_TCCR0,Timer0_TCCR0_WGM01);
		CLR_BIT(Timer0_TCCR0,Timer0_TCCR0_WGM00);
	}
	else if (Mode == Fast_PWM)
	{
		SET_BIT(Timer0_TCCR0,Timer0_TCCR0_WGM01);
		SET_BIT(Timer0_TCCR0,Timer0_TCCR0_WGM00);
	}
	else
	{
		CLR_BIT(Timer0_TCCR0,Timer0_TCCR0_WGM01);
		SET_BIT(Timer0_TCCR0,Timer0_TCCR0_WGM00);
	}


	//ENABLE OVER FLOW INTERRUPT
    if(Flag == TIMER0_OVF)
    {
    	SET_BIT(TIMSK, TIMSK_TOIE0);
    }

    else if(Flag == TIMER0_CTCF)
    {
    	SET_BIT(TIMSK, TIMSK_OCIE0);
    }

	//SET CLK
    Timer0_TCCR0 &= TIMER_CLK_CLEAR_BITS;
    Timer0_TCCR0 |= CLK_SRC;


}






void Timer0_EnableOverFlowInterrupt()
{
	SET_BIT(TIMSK,TIMSK_TOIE0);
}

void Timer0_DisableOverFlowInterrupt()
{
	CLR_BIT(TIMSK,TIMSK_TOIE0);

}

void Timer0_EnableCompareMatchInterrupt()
{
	SET_BIT(TIMSK,TIMSK_OCIE0);

}

void Timer0_DisableCompareMatchInterrupt()
{
	CLR_BIT(TIMSK,TIMSK_OCIE0);
}

void Timer0_SetTCNT0(u8 TCNT0_value)
{
      Timer0_TCNT0 = TCNT0_value;
}

void Timer0_SetOCR0(u8 OCR0_Value)
{
	Timer0_OCR0 = OCR0_Value;
}


void Timer0_SetCallBackOverFlow( void (*CallBack)(void) )
{
       ISR_overflow = CallBack;

}

void Timer0_SetCallBackCTC( void (*CallBack)(void) )
{

	ISR_CTC = CallBack;

}

void Timer0_SetFastPWM_Mode(u8 Mode)
{
	if( Mode == CLEAR_ON_COMPARE_SET_ON_TOP )
	{
          SET_BIT(Timer0_TCCR0,Timer0_TCCR0_COM01);
          CLR_BIT(Timer0_TCCR0,Timer0_TCCR0_COM00);
	}

	else if (Mode == SET_ON_COMPARE_CLEAR_ON_TOP)
	{
        SET_BIT(Timer0_TCCR0,Timer0_TCCR0_COM01);
        SET_BIT(Timer0_TCCR0,Timer0_TCCR0_COM00);
	}

}




//--------------------------------------------
void Timer1_Init()
{

	//Set Mode Fast PWM   Top ICR Register   (ICR Value is Top)
    CLR_BIT(Timer1_TCCR1A,Timer1_TCCR1A_WGM10);
    SET_BIT(Timer1_TCCR1A,Timer1_TCCR1A_WGM11);
    SET_BIT(Timer1_TCCR1B,Timer1_TCCR1B_WGM12);
    SET_BIT(Timer1_TCCR1B,Timer1_TCCR1B_WGM13);


    // CLear OC1A Pin At OCR1A Value set at ICR Value
    CLR_BIT(Timer1_TCCR1A,Timer1_TCCR1A_COM1A0);
    SET_BIT(Timer1_TCCR1A,Timer1_TCCR1A_COM1A1);



    Timer1_TCCR1B &= TIMER_CLK_CLEAR_BITS;
    Timer1_TCCR1B |= TIMER_CLK_8;   // Tick Time 1 MicroSecond



}

void Timer1_Set_OCR1A(u16 OCR1_value )
{

	Timer1_OCR1A = OCR1_value;
}

void Timer1_Set_ICR(u16 ICR_value)
{
	Timer1_ICR = ICR_value;

}

//--------------------------------------------

void ICU_Init()
{
  //Set Timer1 Mode as Normal mode
    CLR_BIT(Timer1_TCCR1A,Timer1_TCCR1A_WGM10);
    CLR_BIT(Timer1_TCCR1A,Timer1_TCCR1A_WGM11);
    CLR_BIT(Timer1_TCCR1B,Timer1_TCCR1B_WGM12);
    CLR_BIT(Timer1_TCCR1B,Timer1_TCCR1B_WGM13);


    Timer1_TCCR1B &= TIMER_CLK_CLEAR_BITS;
    Timer1_TCCR1B |= TIMER_CLK_8;   // Tick Time 1 MicroSecond


 ///-------------------------------------------

    //Disable Noise Canceler
    CLR_BIT(Timer1_TCCR1B,Timer1_TCCR1B_ICNC1);

    //Set ICU Pin to make Interrupt at Rising Edge
    SET_BIT(Timer1_TCCR1B,Timer1_TCCR1B_ICES1);

    // Make ICU to be able to make Interrupt
    SET_BIT(TIMSK,TIMSK_TICIE1);

}


u16  ICU_Value()
{
	return Timer1_ICR;
}
void ICU_EnableNoiseCanceler()
{
	SET_BIT(Timer1_TCCR1B,Timer1_TCCR1B_ICNC1);
}
void ICU_DisableNoiseCanceler()
{
	CLR_BIT(Timer1_TCCR1B,Timer1_TCCR1B_ICNC1);
}
void ICU_EnableInterrupt()
{
    SET_BIT(TIMSK,TIMSK_TICIE1);
}
void ICU_DisableInterrupt()
{
    CLR_BIT(TIMSK,TIMSK_TICIE1);
}
void ICU_SetCallBack(void (*ICU)(void))
{
     ISR_ICU = ICU;

}


void ICU_ChangePinMode(u8 mode)
{

	if(mode == Falling_Edge)
	{
	    //Set ICU Pin to make Interrupt at Falling Edge
	    CLR_BIT(Timer1_TCCR1B,Timer1_TCCR1B_ICES1);
	}

	else if ( mode == Rising_Edge)
	{
	    //Set ICU Pin to make Interrupt at Rising Edge
	    SET_BIT(Timer1_TCCR1B,Timer1_TCCR1B_ICES1);

	}
}


//---------------------------------------


//ISR overflow
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{

	ISR_overflow();

}


//ISR CTC
void __vector_10(void)  __attribute__((signal));
void __vector_10(void)
{

    ISR_CTC();

}


void __vector_6(void)  __attribute__((signal));
void __vector_6(void)
{
    ISR_ICU();

}

