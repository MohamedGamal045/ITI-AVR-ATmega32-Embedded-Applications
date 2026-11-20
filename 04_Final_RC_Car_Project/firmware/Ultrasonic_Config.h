/*
 * Ultrasonic_Config.h
 *
 * Created on: Sep 14, 2025
 * Author: Omar
 */

#ifndef HAL_ULTRASONIC_CONFIG_H_
#define HAL_ULTRASONIC_CONFIG_H_

/*
 * Select port and pin for TRIG
 * Example: _PORTB, PIN0
 */
#define ULTRASONIC_TRIG_PORT   _PORTD
#define ULTRASONIC_TRIG_PIN    PIN2

/*
 * Select port and pin for ECHO
 * Connect to PD3 for INT1
 */
#define ULTRASONIC_ECHO_PORT   _PORTD
#define ULTRASONIC_ECHO_PIN    PIN3

/*
 * Maximum measurable distance (for timeout)
 * HC-SR04 max ≈ 400 cm, but we set safety margin
 */
#define ULTRASONIC_MAX_DISTANCE_CM  400

#endif /* HAL_ULTRASONIC_CONFIG_H_ */
