/*
 * DCMOTOR_Program.c
 *
 *  Created on: Sep 15, 2025
 *      Author: Omar
 */

// LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_interface.h"
// HAL
#include "DCMOTOR_Config.h"
#include "DCMOTOR_Private.h"
#include "DCMOTOR_Interface.h"

void DCMOTOR_voidInit(void)
{
    /* Set direction pins as output */
    DIO_SetPinDirection(DCMOTOR_A_PORT, DCMOTOR_A_IN1, OUTPUT);
    DIO_SetPinDirection(DCMOTOR_A_PORT, DCMOTOR_A_IN2, OUTPUT);
    DIO_SetPinDirection(DCMOTOR_B_PORT, DCMOTOR_B_IN1, OUTPUT);
    DIO_SetPinDirection(DCMOTOR_B_PORT, DCMOTOR_B_IN2, OUTPUT);
    DIO_SetPinDirection(DCMOTOR_C_PORT, DCMOTOR_C_IN1, OUTPUT);
    DIO_SetPinDirection(DCMOTOR_C_PORT, DCMOTOR_C_IN2, OUTPUT);
    DIO_SetPinDirection(DCMOTOR_D_PORT, DCMOTOR_D_IN1, OUTPUT);
    DIO_SetPinDirection(DCMOTOR_D_PORT, DCMOTOR_D_IN2, OUTPUT);

}

void DCMOTOR_voidRotateMotorA(u8 Copy_u8Direction)
{
    switch (Copy_u8Direction)
    {
    case DCMOTOR_CW:
        DIO_SetPinValue(DCMOTOR_A_PORT, DCMOTOR_A_IN1, LOW);
        DIO_SetPinValue(DCMOTOR_A_PORT, DCMOTOR_A_IN2, HIGH);
        break;
    case DCMOTOR_CCW:
        DIO_SetPinValue(DCMOTOR_A_PORT, DCMOTOR_A_IN1, HIGH);
        DIO_SetPinValue(DCMOTOR_A_PORT, DCMOTOR_A_IN2, LOW);
        break;
    case DCMOTOR_STOP:
    default:
        DIO_SetPinValue(DCMOTOR_A_PORT, DCMOTOR_A_IN1, LOW);
        DIO_SetPinValue(DCMOTOR_A_PORT, DCMOTOR_A_IN2, LOW);
        break;
    }
}

void DCMOTOR_voidRotateMotorB(u8 Copy_u8Direction)
{
    switch (Copy_u8Direction)
    {
    case DCMOTOR_CW:
        DIO_SetPinValue(DCMOTOR_B_PORT, DCMOTOR_B_IN1, HIGH);
        DIO_SetPinValue(DCMOTOR_B_PORT, DCMOTOR_B_IN2, LOW);
        break;
    case DCMOTOR_CCW:
        DIO_SetPinValue(DCMOTOR_B_PORT, DCMOTOR_B_IN1, LOW);
        DIO_SetPinValue(DCMOTOR_B_PORT, DCMOTOR_B_IN2, HIGH);
        break;
    case DCMOTOR_STOP:
    default:
        DIO_SetPinValue(DCMOTOR_B_PORT, DCMOTOR_B_IN1, LOW);
        DIO_SetPinValue(DCMOTOR_B_PORT, DCMOTOR_B_IN2, LOW);
        break;
    }
}

void DCMOTOR_voidRotateMotorC(u8 Copy_u8Direction)
{
    switch (Copy_u8Direction)
    {
    case DCMOTOR_CW:
        DIO_SetPinValue(DCMOTOR_C_PORT, DCMOTOR_C_IN1, LOW);
        DIO_SetPinValue(DCMOTOR_C_PORT, DCMOTOR_C_IN2, HIGH);
        break;
    case DCMOTOR_CCW:
        DIO_SetPinValue(DCMOTOR_C_PORT, DCMOTOR_C_IN1, HIGH);
        DIO_SetPinValue(DCMOTOR_C_PORT, DCMOTOR_C_IN2, LOW);
        break;
    case DCMOTOR_STOP:
    default:
        DIO_SetPinValue(DCMOTOR_C_PORT, DCMOTOR_C_IN1, LOW);
        DIO_SetPinValue(DCMOTOR_C_PORT, DCMOTOR_C_IN2, LOW);
        break;
    }
}

void DCMOTOR_voidRotateMotorD(u8 Copy_u8Direction)
{
    switch (Copy_u8Direction)
    {
    case DCMOTOR_CW:
        DIO_SetPinValue(DCMOTOR_D_PORT, DCMOTOR_D_IN1, HIGH);
        DIO_SetPinValue(DCMOTOR_D_PORT, DCMOTOR_D_IN2, LOW);
        break;
    case DCMOTOR_CCW:
        DIO_SetPinValue(DCMOTOR_D_PORT, DCMOTOR_D_IN1, LOW);
        DIO_SetPinValue(DCMOTOR_D_PORT, DCMOTOR_D_IN2, HIGH);
        break;
    case DCMOTOR_STOP:
    default:
        DIO_SetPinValue(DCMOTOR_D_PORT, DCMOTOR_D_IN1, LOW);
        DIO_SetPinValue(DCMOTOR_D_PORT, DCMOTOR_D_IN2, LOW);
        break;
    }
}
