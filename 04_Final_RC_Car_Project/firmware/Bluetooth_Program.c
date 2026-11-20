/*
 * Bluetooth_Program.c
 *
 *  Created on: Sep 14, 2025
 *      Author: omar
 */


/*
 * Bluetooth_Program.c
 *
 *  Created on: Sep 14, 2025
 *      Author: Omar
 */

// LIB
#include "STD_TYPES.h"

// MCAL
#include "USART_Interface.h"

// HAL
#include "Bluetooth_Config.h"
#include "Bluetooth_Private.h"
#include "Bluetooth_Interface.h"

void Bluetooth_voidInit(void)
{
    /* Initialize USART with default settings (9600 baud, 8N1) */
    USART_Init();
}

void Bluetooth_voidSendChar(u8 data)
{
    USART_Poll_voidSendData(data);
}

void Bluetooth_voidSendString(u8* str)
{
    while(*str != NULL_CHAR)
    {
        USART_Poll_voidSendData(*str);
        str++;
    }
}

u8 Bluetooth_u8ReceiveChar(void)
{
    return USART_Poll_u8RecieveData();
}

void Bluetooth_voidReceiveString(u8* buffer, u8 terminator)
{
    u8 index = 0;
    u8 data;
    do
    {
        data = USART_Poll_u8RecieveData();
        buffer[index++] = data;
    } while(data != terminator);

    buffer[index] = NULL_CHAR;
}
