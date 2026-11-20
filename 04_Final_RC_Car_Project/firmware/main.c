#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

// MCAL Includes
#include "DIO_interface.h"

// HAL Includes
#include "DCMOTOR_Interface.h"
#include "Ultrasonic_Interface.h"
#include "Bluetooth_Interface.h"

void main(void)
{
    u8 receivedCommand;

    // Initialization
    // Initialize motor driver pins, Bluetooth module, and Ultrasonic sensor
    DCMOTOR_voidInit();
    Bluetooth_voidInit();
    Ultrasonic_voidInit();

    // Configure LED and Buzzer pins as output
    DIO_SetPinDirection(_PORTD, PIN6, OUTPUT); // LED pin
    DIO_SetPinDirection(_PORTD, PIN7, OUTPUT); // Buzzer pin

    // Configure selector switch pins as input with internal pull-up enabled
    DIO_SetPinDirection(_PORTB, PIN0, INPUT); // Bluetooth mode switch
    DIO_SetPinDirection(_PORTB, PIN1, INPUT); // Autonomous mode switch
    DIO_SetPinValue(_PORTB, PIN0, HIGH);      // Enable pull-up for PIN0
    DIO_SetPinValue(_PORTB, PIN1, HIGH);      // Enable pull-up for PIN1


    while (1)
    {
        // Check for Autonomous Mode (Pin 1 on Port B connected to GND)
        if (DIO_GetPinValue(_PORTB, PIN1) == LOW)
        {
            f32 distance = Ultrasonic_f32GetDistanceCM();

            if (distance > 20)
            {
                // Move Forward
                DCMOTOR_voidRotateMotorA(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CCW);
            }
            else
            {
                // Stop and check for empty space
                DCMOTOR_voidRotateMotorA(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorB(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorC(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorD(DCMOTOR_STOP);
                _delay_ms(500); // Wait for a moment

                // Check distance to the right
                // Turn right by rotating left motors forward and right motors backward
                DCMOTOR_voidRotateMotorA(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CW);
                _delay_ms(700); // Turn for a short period
                f32 rightDistance = Ultrasonic_f32GetDistanceCM();

                // Return to facing forward
                DCMOTOR_voidRotateMotorA(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorB(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorC(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorD(DCMOTOR_STOP);
                _delay_ms(500);

                // Check distance to the left
                // Turn left by rotating left motors backward and right motors forward
                DCMOTOR_voidRotateMotorA(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CCW);
                _delay_ms(700); // Turn for a short period
                f32 leftDistance = Ultrasonic_f32GetDistanceCM();

                // Stop before deciding
                DCMOTOR_voidRotateMotorA(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorB(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorC(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorD(DCMOTOR_STOP);
                _delay_ms(500);

                // Choose the path with more space
                if (rightDistance > leftDistance)
                {
                    // Turn right to align with the clear path and move forward
                    DCMOTOR_voidRotateMotorA(DCMOTOR_CCW);
                    DCMOTOR_voidRotateMotorB(DCMOTOR_CCW);
                    DCMOTOR_voidRotateMotorC(DCMOTOR_CW);
                    DCMOTOR_voidRotateMotorD(DCMOTOR_CW);
                    _delay_ms(700);
                }
                else
                {
                    // Turn left to align with the clear path and move forward
                    DCMOTOR_voidRotateMotorA(DCMOTOR_CW);
                    DCMOTOR_voidRotateMotorB(DCMOTOR_CW);
                    DCMOTOR_voidRotateMotorC(DCMOTOR_CCW);
                    DCMOTOR_voidRotateMotorD(DCMOTOR_CCW);
                    _delay_ms(700);
                }
            }
        }
        // Check for Bluetooth Mode (Pin 0 on Port B connected to GND)
        else if (DIO_GetPinValue(_PORTB, PIN0) == LOW)
        {
            receivedCommand = Bluetooth_u8ReceiveChar();

            switch (receivedCommand)
            {
            case 'F':
                // Move Forward
                DCMOTOR_voidRotateMotorA(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CCW);
                break;
            case 'B':
                // Move Backward
                DCMOTOR_voidRotateMotorA(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CW);
                break;
            case 'L':
                // Turn Left ==> Side Way
                DCMOTOR_voidRotateMotorA(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CW);
                break;
            case 'R':
                // Turn Right ==> Side Way
                DCMOTOR_voidRotateMotorA(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CCW);
                break;
            case 'G':
                // Move Forward Left(On Mobile) ==> Turn Round Left
                DCMOTOR_voidRotateMotorA(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CCW);
                break;
            case 'I':
                // Move Forward Right(On Mobile) ==> Turn Round Right
                DCMOTOR_voidRotateMotorA(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorD(DCMOTOR_CW);
                break;
            case 'H':
                // Move Backward Left(On Mobile) ==> Turn Rear Left
                DCMOTOR_voidRotateMotorA(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorD(DCMOTOR_STOP);
                break;
            case 'J':
                // Move Backward Right(On Mobile) ==> Turn Rear Right
                DCMOTOR_voidRotateMotorA(DCMOTOR_CCW);
                DCMOTOR_voidRotateMotorB(DCMOTOR_CW);
                DCMOTOR_voidRotateMotorC(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorD(DCMOTOR_STOP);
                break;
            case 'S':

                // Stop All Motors
                DCMOTOR_voidRotateMotorA(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorB(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorC(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorD(DCMOTOR_STOP);
                break;
            case 'w':
                // Turn LED Off
                DIO_SetPinValue(_PORTD, PIN6, LOW);
                break;
            case 'v':
                    // Turn Buzzer Off
                DIO_SetPinValue(_PORTD, PIN7, LOW);
                break;
            case 'W':
                // Turn LED On
                DIO_SetPinValue(_PORTD, PIN6, HIGH);
                break;
            case 'V':
                // Turn Buzzer On
                DIO_SetPinValue(_PORTD, PIN7, HIGH);
                break;
            default:
                // Stop All Motors
                DCMOTOR_voidRotateMotorA(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorB(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorC(DCMOTOR_STOP);
                DCMOTOR_voidRotateMotorD(DCMOTOR_STOP);
                break;
            }
        }
        else
        {
            // Stop all motors if neither switch is active
            DCMOTOR_voidRotateMotorA(DCMOTOR_STOP);
            DCMOTOR_voidRotateMotorB(DCMOTOR_STOP);
            DCMOTOR_voidRotateMotorC(DCMOTOR_STOP);
            DCMOTOR_voidRotateMotorD(DCMOTOR_STOP);
        }
    }
}
