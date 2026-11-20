/*
 * Ultrasonic_Program.c
 *
 * Created on: Sep 14, 2025
 * Author: Omar
 */

// LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

// MCAL
#include "DIO_interface.h"
#include "Timer_Interface.h"

// HAL
#include "Ultrasonic_Config.h"
#include "Ultrasonic_Private.h"
#include "Ultrasonic_Interface.h"

static volatile u16 g_u16RisingTime = 0;
static volatile u16 g_u16FallingTime = 0;
static volatile u8  g_u8ICUState = ULTRASONIC_WAITING_FOR_RISING;

void Ultrasonic_ICU_ISR(void)
{
    if (g_u8ICUState == ULTRASONIC_WAITING_FOR_RISING)
    {
        g_u16RisingTime = ICU_Value();
        ICU_ChangePinMode(Falling_Edge);
        g_u8ICUState = ULTRASONIC_WAITING_FOR_FALLING;
    }
    else if (g_u8ICUState == ULTRASONIC_WAITING_FOR_FALLING)
    {
        g_u16FallingTime = ICU_Value();
        ICU_ChangePinMode(Rising_Edge);
        g_u8ICUState = ULTRASONIC_WAITING_FOR_RISING;
    }
}

void Ultrasonic_voidInit(void)
{
    /* Configure TRIG pin as output */
    DIO_SetPinDirection(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, OUTPUT);
    DIO_SetPinValue(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, LOW);

    /* Initialize the ICU (Timer_program.c already contains implementation) */
    ICU_Init();
    ICU_ChangePinMode(Rising_Edge);
    ICU_SetCallBack(Ultrasonic_ICU_ISR);
    ICU_EnableInterrupt();
}

void Ultrasonic_voidTrigger(void)
{
    /* send 10us pulse */
    DIO_SetPinValue(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, HIGH);
    _delay_us(10);
    DIO_SetPinValue(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, LOW);
}

u16 Ultrasonic_u16GetLastPulseUS(void)
{
    /* Timer1 ticks are 1us in your Timer setup (Timer1 prescaler = 8 and Timer1 TICK commented in Timer_program),
       but verify your Timer1 prescaler and F_CPU. */
    if (g_u16FallingTime >= g_u16RisingTime)
    {
        return (g_u16FallingTime - g_u16RisingTime);
    }
    else
    {
        return ((0xFFFF - g_u16RisingTime) + g_u16FallingTime);
    }
}

f32 Ultrasonic_f32GetDistanceCM(void)
{
    u16 pulseTime = Ultrasonic_u16GetLastPulseUS();
    f32 distance = (f32)pulseTime / 58.0;  // Speed of sound = 340 m/s = 0.034 cm/us
    return distance;
}
