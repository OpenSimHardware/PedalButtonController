/*
 * ----------------------------------------------------------------------------------
 * @file  		: keypad.c
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

#include "keypad.h"

extern struct pin_conf pins[USEDPINS];
extern uint8_t Number_Rows, Number_Columns;
uint64_t millis;
struct keypad buttons[MAXBUTTONS];


void CheckButtons(void) {

	uint8_t column=0;

	for (uint8_t i=0;i<USEDPINS;i++){
		if (pins[i].pin_type == Button_COLUMN) {
			*(pins[i].bsrr_reg_addr) = 0x1<<pins[i].pin_number;
			CheckRows(column);
			*(pins[i].bsrr_reg_addr) = 0x1<<(pins[i].pin_number+16);
			column++;
		}
	}
}

void CheckRows(uint8_t column) {
	uint8_t row=0,rowstate;

	for (uint8_t i=0;i<USEDPINS;i++){
		if (pins[i].pin_type == Button_ROW) {
			if (((*pins[i].idr_reg_addr) & 0x1<<(pins[i].pin_number)) != 0)   {
				rowstate = 1;
			  } else {
				rowstate = 0;
			  }
			SetButtonState(row,column,rowstate);
			row++;
		}
	}
}


void SetButtonState(uint8_t row, uint8_t column, uint8_t rowstate) {

	extern uint64_t millis;
	extern uint8_t Number_Columns;


	uint8_t i = row*Number_Columns + column;

	if (rowstate == 1) {

		if (buttons[i].prev_state == 0) { //if previous state is 0, then just remember push time
			buttons[i].time_pressed = millis;
		}

//		if ((buttons[i].pressed == 1) &&  //if already pressed and longer then presstime
//				 (millis - buttons[i].time_pressed  > PRESSTIME)) { //then reset
//			buttons[i].pressed = 0;
//		}

		if ((buttons[i].prev_state == 1) &&			//if previous state is HIGH and time since 1st push is
				(!(buttons[i].current_state)) && 	//more than debounce time then button is pressed
			 (millis - buttons[i].time_pressed  > DEBOUNCETIME)) {
				buttons[i].pressed = 1;
				buttons[i].current_state = 1;
				buttons[i].time_pressed = millis;
		}

		buttons[i].prev_state = 1; //set previous state to 1
	}


	if (rowstate == 0) {
		buttons[i].current_state = 0;
		buttons[i].pressed = 0;
		buttons[i].prev_state = 0; //set previous state to 0
	}
}
