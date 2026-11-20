#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "Timer_Interface.h"
#include "Timer_Private.h"
#include "GIE_interface.h"

// Define motor control pins
#define MOTOR_CW_PIN   PIN0
#define MOTOR_CCW_PIN  PIN1
#define MOTOR_PORT     _PORTA

// Global variables to track the state and time
volatile u16 counter = 0;
volatile u8 motor_state = 0; // 0: CW, 1: CCW, 2: Stop

// Function prototypes for interrupt handlers
void Timer0_OVF_Handler(void);

// Timer0 CTC Interrupt Service Routine (ISR)
void Timer0_CTC_Handler(void) {
    // Increment the counter on each CTC interrupt (every 1ms)
    counter++;

    // State 0: Clockwise (CW) rotation
    if (motor_state == 0) {
        // After 5000 interrupts (5 seconds), transition to the next state
        if (counter >= 5000) {
            counter = 0;
            motor_state = 1; // Transition to CCW State

            // Stop the motor by setting both pins to LOW
            DIO_SetPinValue(MOTOR_PORT, MOTOR_CW_PIN, LOW);
            DIO_SetPinValue(MOTOR_PORT, MOTOR_CCW_PIN, HIGH);

            // Reconfigure Timer to OVF mode for CCW timing
            Timer0_DisableCompareMatchInterrupt();
            Timer0_Init(Normal_Mode, TIMER0_OVF, TIMER_CLK_1024);
            Timer0_SetCallBackOverFlow(Timer0_OVF_Handler);
        }
    }
    // State 2: Motor Stop
    else if (motor_state == 2) {
        // After 5000 interrupts (5 seconds), transition back to CW state
        if (counter >= 5000) {
            counter = 0;
            motor_state = 0; // Transition to CW State

            // Set motor to CW
            DIO_SetPinValue(MOTOR_PORT, MOTOR_CW_PIN, HIGH);
            DIO_SetPinValue(MOTOR_PORT, MOTOR_CCW_PIN, LOW);
        }
    }
}

// Timer0 Overflow Interrupt Service Routine (ISR)
void Timer0_OVF_Handler(void) {
    // Increment the counter on each OVF interrupt
    counter++;

    // An overflow occurs every ~32.768ms with an 8MHz clock and 1024 prescaler
    // We need approximately 92 overflows for 3 seconds (3000ms / 32.768ms)
    if (counter >= 92) {
        counter = 0;
        motor_state = 2; // Transition to Stop State

        // Stop the motor
        DIO_SetPinValue(MOTOR_PORT, MOTOR_CW_PIN, LOW);
        DIO_SetPinValue(MOTOR_PORT, MOTOR_CCW_PIN, LOW);

        // Reconfigure Timer to CTC mode for Stop timing
        Timer0_DisableOverFlowInterrupt();
        Timer0_Init(CTC, TIMER0_CTCF, TIMER_CLK_64);
        Timer0_SetOCR0(124); // OCR0 value for a 1ms interrupt with 8MHz clock and prescaler 64
        Timer0_SetCallBackCTC(Timer0_CTC_Handler);
    }
}

int main(void) {
    // Configure motor pins as outputs
    DIO_SetPinDirection(MOTOR_PORT, MOTOR_CW_PIN, PIN_OUTPUT);
    DIO_SetPinDirection(MOTOR_PORT, MOTOR_CCW_PIN, PIN_OUTPUT);

    // Set initial motor state to Clockwise (CW)
    DIO_SetPinValue(MOTOR_PORT, MOTOR_CW_PIN, HIGH);
    DIO_SetPinValue(MOTOR_PORT, MOTOR_CCW_PIN, LOW);

    // Enable Global Interrupts
    GIE_voidEnable();

    // Initial Timer Configuration for CW state (CTC mode, 1ms interrupt)
    Timer0_Init(CTC, TIMER0_CTCF, TIMER_CLK_64);
    Timer0_SetOCR0(124);
    Timer0_SetCallBackCTC(Timer0_CTC_Handler);

    while (1) {
        // The main loop is empty because all timing and state changes are handled by the interrupts.
    }

    return 0;
}
