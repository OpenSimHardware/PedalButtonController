/*
 * rotary.h
 *
 *  Created on: Jul 4, 2016
 *      Author: John
 */

#ifndef ROTARY_H_
#define ROTARY_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include <stm32f1xx_hal_gpio.h>


#define NUMROTARIES 11
#define ROTTIME 50

#define ROTARY_1_PORT 		GPIOB
#define ROTARY_1_PIN 		GPIO_PIN_0
#define ROTARY_2_PORT 		GPIOB
#define ROTARY_2_PIN 		GPIO_PIN_1
#define ROTARY_3_PORT 		GPIOB
#define ROTARY_3_PIN 		GPIO_PIN_13
#define ROTARY_4_PORT 		GPIOB
#define ROTARY_4_PIN 		GPIO_PIN_14
#define ROTARY_5_PORT 		GPIOB
#define ROTARY_5_PIN 		GPIO_PIN_15
#define ROTARY_6_PORT 		GPIOA
#define ROTARY_6_PIN 		GPIO_PIN_8
#define ROTARY_7_PORT 		GPIOA
#define ROTARY_7_PIN 		GPIO_PIN_9
#define ROTARY_8_PORT 		GPIOA
#define ROTARY_8_PIN 		GPIO_PIN_10
#define ROTARY_9_PORT 		GPIOA
#define ROTARY_9_PIN 		GPIO_PIN_11
#define ROTARY_10_PORT 		GPIOA
#define ROTARY_10_PIN 		GPIO_PIN_12
#define ROTARY_11_PORT 		GPIOA
#define ROTARY_11_PIN 		GPIO_PIN_15

#define ROTARY_A_PORT 		GPIOB
#define ROTARY_A_PIN 		GPIO_PIN_10
#define ROTARY_B_PORT 		GPIOB
#define ROTARY_B_PIN 		GPIO_PIN_11


unsigned char rotary_process(uint8_t _i);
void CheckRotaries(void);

struct rots {
	volatile uint8_t pressed;
	volatile uint64_t time_pressed;
	volatile uint8_t state;
};


#endif /* ROTARY_H_ */
