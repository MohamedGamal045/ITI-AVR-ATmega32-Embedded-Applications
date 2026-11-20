#include "util/delay.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"

int main()
{
    // Set PORTA as output for the Seven-Segment Display
    DIO_SetPortDirection(_PORTA, PORT_OUTPUT);

    // Set PIN0 on PORTC as input for the Increment Button
    DIO_SetPinDirection(_PORTC, PIN0, PIN_INPUT);

    // Set PIN1 on PORTC as input for the Decrement Button
    DIO_SetPinDirection(_PORTC, PIN1, PIN_INPUT);

    // Enable internal pull-up resistors for the buttons on PORTC
    DIO_SetPinValue(_PORTC, PIN0, PIN_HIGH);
    DIO_SetPinValue(_PORTC, PIN1, PIN_HIGH);

    // Array to store the segment values for a Common Anode Seven-Segment Display
    u8 Seven_Seg_Anode[10] = {
        0b01000000, // 0
        0b01111001, // 1
        0b00100100, // 2
        0b00110000, // 3
        0b00011001, // 4
        0b00010010, // 5
        0b00000010, // 6
        0b01111000, // 7
        0b00000000, // 8
        0b00010000  // 9
    };

    u8 count = 0;
    DIO_SetPortvalue(_PORTA, Seven_Seg_Anode[count]);

    while(1)
    {
        // Check if the increment button is pressed (LOW due to pull-up resistor)
        if(DIO_GetPinValue(_PORTC, PIN0) == HIGH)
        {
            // Increment counter and wrap around from 9 to 0
            count = (count + 1) % 10;
            DIO_SetPortvalue(_PORTA, Seven_Seg_Anode[count]);

            // Wait until button is released to prevent multiple counts from a single press
            while(DIO_GetPinValue(_PORTC, PIN0) == HIGH);
            _delay_ms(20); // Add a small delay for debouncing
        }

        // Check if the decrement button is pressed (LOW due to pull-up resistor)
        if(DIO_GetPinValue(_PORTC, PIN1) == HIGH)
        {
            // Decrement counter and wrap around from 0 to 9
            count = (count == 0) ? 9 : count - 1;
            DIO_SetPortvalue(_PORTA, Seven_Seg_Anode[count]);

            // Wait until button is released
            while(DIO_GetPinValue(_PORTC, PIN1) == HIGH);
            _delay_ms(20); // Add a small delay for debouncing
        }
    }

    return 0;
}
