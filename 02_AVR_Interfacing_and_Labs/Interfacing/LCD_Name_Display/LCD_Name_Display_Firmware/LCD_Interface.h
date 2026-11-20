/*
 * LCD_Interface.h
 *
 *  Created on: Aug 26, 2025
 *      Author: Mohammed Gamal
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_voidInit(void);
void LCD_voidSendCharacter(u8 Copy_u8char );
void LCD_voidSendString(u8* pu8_String);
void LCD_voidSendNumber(u32 Copy_u32Number);
void LCD_voidClearDisplay(void);
void LCD_voidGotoXY(u8 Copy_u8Colume ,u8 Copy_u8Row);

#endif /* LCD_INTERFACE_H_ */
