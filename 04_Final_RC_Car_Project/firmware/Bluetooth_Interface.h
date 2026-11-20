

/*
 * Bluetooth_Interface.h
 *
 *  Created on: Sep 14, 2025
 *      Author: Omar
 */

#ifndef HAL_BLUETOOTH_INTERFACE_H_
#define HAL_BLUETOOTH_INTERFACE_H_

#include "STD_TYPES.h"

/**
 * @brief Initialize Bluetooth module (uses USART)
 */
void Bluetooth_voidInit(void);

/**
 * @brief Send a single character
 */
void Bluetooth_voidSendChar(u8 data);

/**
 * @brief Send a null-terminated string
 */
void Bluetooth_voidSendString(u8* str);

/**
 * @brief Receive one character (polling)
 */
u8 Bluetooth_u8ReceiveChar(void);

/**
 * @brief Receive string until terminator (blocking)
 * @param buffer Pointer to buffer
 * @param terminator Character that ends reception (e.g. '\n')
 */
void Bluetooth_voidReceiveString(u8* buffer, u8 terminator);

#endif /* HAL_BLUETOOTH_INTERFACE_H_ */
