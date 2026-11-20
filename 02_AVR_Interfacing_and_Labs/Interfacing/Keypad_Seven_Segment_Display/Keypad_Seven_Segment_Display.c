
//include first library
#include "util/delay.h"

#include "BIT_MATH.h"
#include "STD_TYPES.h"

//include drivers;
#include "DIO_interface.h"
#include "Keypad_interface.h"

void main()
{

	u8 SevenSegmentCaTh[10] = {
	 0b01111111,//0
	 0b00000110,//1
	 0b01011011,//2
	 0b01001111,//3
	 0b01100110,//4
	 0b01101101,//5
	 0b01111101,//6
	 0b00000111,//7
	 0b01111111,//8
	 0b01101111,//9
	};

	u8 SevenSegmentanode[10] = {
	 ~0b01111111,//0
	 ~0b00000110,//1
	 ~0b01011011,//2
	 ~0b01001111,//3
	 ~0b01100110,//4
	 ~0b01101101,//5
	 ~0b01111101,//6
	 ~0b00000111,//7
	 ~0b01111111,//8
	 ~0b01101111,//9
	};



    DIO_SetPortDirection(_PORTA,0xFF); // seven segment port output
    Keypad_voidInit();  //Initialize Keypad

    u8 key;
	while(1)
	{
     key = Keypad_u8GetPressedKey();
     if(key!= NO_PRESSED_KEY)
     {
    	 DIO_SetPortvalue(_PORTA,SevenSegmentCaTh[key]);
     }

	}


}

