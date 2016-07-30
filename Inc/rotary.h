/*
 * ----------------------------------------------------------------------------------
 * @file  		: rotary.h
 * @author 		: Dmitry Skulkin <dmitry.skulkin@gmail.com>
 * @version		: 0.1
 * @brief 		: Rotary Encoders support library
 *
 *
 * ----------------------------------------------------------------------------------
 *	 Copyright (c) 2016 Dmitry Skulkin <dmitry.skulkin@gmail.com>					*
 *																					*
 *	Permission is hereby granted, free of charge, to any person obtaining a copy	*
 *	of this software and associated documentation files (the "Software"), to deal	*
 *	in the Software without restriction, including without limitation the rights	*
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell		*
 *	copies of the Software, and to permit persons to whom the Software is			*
 *	furnished to do so, subject to the following conditions:						*
 *																					*
 *	The above copyright notice and this permission notice shall be included in all	*
 *	copies or substantial portions of the Software.									*
 *																					*
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR		*
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,		*
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE		*
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER			*
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	*
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	*
 *	SOFTWARE.																		*
 * ----------------------------------------------------------------------------------
 * */


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
