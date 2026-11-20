#include "util/delay.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"

int main(void)
{
    DIO_SetPortDirection(_PORTA, 0xFF);
    DIO_SetPinDirection(_PORTB, PIN0, 1);
    DIO_SetPinDirection(_PORTB, PIN1, 1);

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

    while(1)
    {
        for(int num = 1; num < 100; num++)
        {
            int units = num % 10;
            int tens  = num / 10;

            for(int k = 0; k < 100; k++)
            {

                DIO_SetPortvalue(_PORTA, Seven_Seg_Anode[units]);
                DIO_SetPinValue(_PORTB, PIN0, 0);
                DIO_SetPinValue(_PORTB, PIN1, 1);
                _delay_ms(10);


                DIO_SetPortvalue(_PORTA, Seven_Seg_Anode[tens]);
                DIO_SetPinValue(_PORTB, PIN0, 1);
                DIO_SetPinValue(_PORTB, PIN1, 0);
                _delay_ms(10);
            }
        }
    }

    return 0;
}