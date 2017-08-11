/*
 * ----------------------------------------------------------------------------------
 * @file  		: keypad.h
 * @author 		: Dmitry Skulkin <dmitry.skulkin@gmail.com>
 * @version		: 0.1
 * @brief 		: Keypad/buttons support library
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

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdint.h>
#include "periph_init.h"

//#define DEBOUNCETIME 50
//#define PRESSTIME 500
#define MAXBUTTONS 64
//#define ROTSWITCHTIME 100


struct keypad {
	uint8_t pressed;
	uint8_t prev_state;
	uint8_t current_state;
	uint64_t time_pressed;
};


void CheckRows(uint8_t column);
void CheckButtons(void);
void SetButtonState(uint8_t i, GPIO_PinState rowstate);
void CheckWires(uint8_t pole);

#endif /* KEYPAD_H_ */
