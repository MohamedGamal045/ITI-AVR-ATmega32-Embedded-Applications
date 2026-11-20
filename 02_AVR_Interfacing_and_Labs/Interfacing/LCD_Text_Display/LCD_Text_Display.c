#include "util/delay.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "LCD_Interface.h"

int main()
{
    // Initialize LCD
    LCD_voidInit();

    LCD_voidClearDisplay();
    LCD_voidGotoXY(0, 0);
    LCD_voidSendString("MG SOLIMAN");
    LCD_voidGotoXY(0, 1);
    LCD_voidSendString("mg soliman");


    while(1)
    {
    }

    return 0;
}
