/*
 * ----------------------------------------------------------------------------------
 * @file  		: rotary.c
 * @brief 		: Rotary Encoders support library
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
 *
 * Based on Ben Buxton code with different state table
 * http://www.buxtronix.net/2011/10/rotary-encoders-done-properly.html
 *
 * */


#include "rotary.h"


const uint8_t ttable[7][4] = {
		{0x0,		0x5,	0x2,	0x0},
		{DIR_CW,	0x1,	0x1,	0x1},
		{0x0,		0x2,	0x2,	0x3},
		{0x0,		0x1,	0x3,	0x3},
		{0x0,		0x4,	0x6,	0x4},
		{0x0,		0x5,	0x5,	0x4},
		{DIR_CCW,	0x6,	0x6,	0x6},
};


volatile struct rots RotaryStore[USEDPINS];
extern struct pin_conf pins[USEDPINS];

volatile extern uint64_t millis;

/* Read input pins and process for events. Call this either from a
 * loop or an interrupt (eg pin change or timer).
 *
 * Returns 0 on no event, otherwise 0x80 or 0x40 depending on the direction.
 */
uint8_t rotary_process(uint8_t i) {
	uint8_t pinstate, rowstateA, rowstateB;

extern 	uint32_t * Rot_PINA_IDR, * Rot_PINB_IDR;
extern 	uint16_t Rot_PINA_pin, Rot_PINB_pin;

if (((*Rot_PINA_IDR) & Rot_PINA_pin) != 0)   {
	rowstateA = 1;
  } else {
	rowstateA = 0;
  }

if (((*Rot_PINB_IDR) & Rot_PINB_pin) != 0) {
	rowstateB = 1;
  } else {
	rowstateB = 0;
  }

	pinstate = (uint8_t)(rowstateA << 1) | rowstateB;

   RotaryStore[i].state = ttable[RotaryStore[i].state & 0xf][pinstate];
  return (RotaryStore[i].state & 0x30);
}

volatile uint32_t tmp;
volatile uint8_t tmpi;

void CheckRotaries(void){
	uint8_t res,j=0;


	for (uint8_t i=0;i<USEDPINS;i++){
		if (pins[i].pin_type == Rotary_Enc) {
			*(pins[i].bsrr_reg_addr) = 0x1<<pins[i].pin_number;
			res = rotary_process(j);
			if (res) {RotaryStore[j].pressed = res; RotaryStore[j].time_pressed=millis;}
			*(pins[i].bsrr_reg_addr) = 0x1<<(pins[i].pin_number+16);
			j++;
		}
	}
}
