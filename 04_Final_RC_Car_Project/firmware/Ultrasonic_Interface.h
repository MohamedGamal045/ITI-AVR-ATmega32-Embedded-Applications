/*
 * Ultrasonic_Interface.h
 *
 *  Created on: Sep 14, 2025
 *      Author: Omar
 */

#ifndef HAL_ULTRASONIC_INTERFACE_H_
#define HAL_ULTRASONIC_INTERFACE_H_

#include "STD_TYPES.h"

/**
 * @brief Initialize ultrasonic module (configures TRIG pin + ICU)
 */
void Ultrasonic_voidInit(void);

/**
 * @brief Trigger measurement and return distance (blocking)
 * @return Distance in centimeters
 */
f32 Ultrasonic_f32GetDistanceCM(void);

/**
 * @brief Non-blocking trigger (start pulse)
 */
void Ultrasonic_voidTrigger(void);

/**
 * @brief Returns last measured pulse width in microseconds
 */
u16 Ultrasonic_u16GetLastPulseUS(void);

#endif /* HAL_ULTRASONIC_INTERFACE_H_ */
