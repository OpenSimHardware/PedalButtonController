/*
 * keypad.h
 *
 *  Created on: Jun 30, 2016
 *      Author: John
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include <stm32f1xx_hal_gpio.h>

#define NUMCOLS 6
#define NUMROWS 6


#define ROW_1_PORT 	GPIOB
#define ROW_1_PIN 	GPIO_PIN_4
#define ROW_2_PORT 	GPIOB
#define ROW_2_PIN 	GPIO_PIN_5
#define ROW_3_PORT 	GPIOB
#define ROW_3_PIN 	GPIO_PIN_6
#define ROW_4_PORT 	GPIOB
#define ROW_4_PIN 	GPIO_PIN_7
#define ROW_5_PORT 	GPIOB
#define ROW_5_PIN 	GPIO_PIN_8
#define ROW_6_PORT 	GPIOB
#define ROW_6_PIN 	GPIO_PIN_9

#define COL_1_PORT 	GPIOC
#define COL_1_PIN 	GPIO_PIN_13
#define COL_2_PORT 	GPIOC
#define COL_2_PIN 	GPIO_PIN_14
#define COL_3_PORT	GPIOC
#define COL_3_PIN 	GPIO_PIN_15
#define COL_4_PORT	GPIOB
#define COL_4_PIN 	GPIO_PIN_12
#define COL_5_PORT 	GPIOB
#define COL_5_PIN 	GPIO_PIN_3
#define COL_6_PORT 	GPIOA
#define COL_6_PIN 	GPIO_PIN_7

#define DEBOUNCETIME 50
#define PRESSTIME 500


void CheckRows(uint8_t column);
void CheckButtons(void);
void SetButtonState(uint8_t row, uint8_t column, GPIO_PinState rowstate);

#endif /* KEYPAD_H_ */
