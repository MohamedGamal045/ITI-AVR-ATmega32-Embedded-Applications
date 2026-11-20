#include "util/delay.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_register.h"
#include "Dio_private.h"
#include "DIO_interface.h"
#include "DIO_config.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_Interface.h"

int main()
{
    u8 name[] = "Mohamed Gamal So";
    u8 i;

    LCD_voidInit();

    while(1)
    {
        for (i = 0; name[i] != '\0'; i++)
        {
            if (i % 2 == 0)
            {
                LCD_voidGotoXY(i, 0);
            }
            else
            {
                LCD_voidGotoXY(i, 1);
            }
            LCD_voidSendCharacter(name[i]);
            _delay_ms(200);
        }
    }

    return 0;
}
