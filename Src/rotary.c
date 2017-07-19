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


const uint8_t fulltable[7][4] = {
		{0x0,		0x5,	0x2,	0x0},
		{DIR_CW,	0x1,	0x1,	0x1},
		{0x0,		0x2,	0x2,	0x3},
		{0x0,		0x1,	0x3,	0x3},
		{0x0,		0x4,	0x6,	0x4},
		{0x0,		0x5,	0x5,	0x4},
		{DIR_CCW,	0x6,	0x6,	0x6},
};

const uint8_t halftable[6][4] = {
		{0x0,			0x4,	0x2,	0x3},
		{DIR_CW,		0x1,	0x1,	0x1 },
		{0x2,			0x2,	0x2,	0x3 | DIR_CW},
		{0x0,			0x1,	0x5,	0x3},
		{0x4,			0x4,	0x4,	0x3 | DIR_CCW},
	 	{DIR_CCW,		0x5,	0x5,	0x5	},
	};

const uint8_t quarttable[4][4] = {
		{0x0,			0x1 | DIR_CCW,	0x2 | DIR_CW,	0x3},
		{DIR_CW,		0x1,			0x1,			0x3 | DIR_CCW},
		{DIR_CCW,		0x2,			0x2,			0x3 | DIR_CW},
		{0x0,			0x1 | DIR_CW,	0x2 | DIR_CCW,	0x3},
};




volatile struct rots RotaryStore[USEDPINS];
extern struct pin_conf pins[USEDPINS];

volatile extern uint64_t millis;

volatile 	uint8_t pinstate, rowstateA, rowstateB;

/* Read input pins and process for events. Call this either from a
 * loop or an interrupt (eg pin change or timer).
 *
 * Returns 0 on no event, otherwise 0x80 or 0x40 depending on the direction.
 */
uint8_t rotary_process(uint8_t i, pintype type, uint32_t *PINA_Addr, uint32_t *PINB_Addr, uint16_t PINA, uint16_t PINB) {
//	uint8_t pinstate, rowstateA, rowstateB;


if (((*PINA_Addr) & PINA) != 0)   {
	rowstateA = 1;
  } else {
	rowstateA = 0;
  }

if (((*PINB_Addr) & PINB) != 0) {
	rowstateB = 1;
  } else {
	rowstateB = 0;
  }

	pinstate = (uint8_t)(rowstateA << 1) | rowstateB;

   if ((type == Chain_Rotary_Enc_1) || (type == Single_Rotary_PINA_1))
	   RotaryStore[i].state = fulltable[RotaryStore[i].state & 0xf][pinstate];
   if ((type == Chain_Rotary_Enc_2) || (type == Single_Rotary_PINA_2))
	   RotaryStore[i].state = halftable[RotaryStore[i].state & 0xf][pinstate];
   if ((type == Chain_Rotary_Enc_4) || (type == Single_Rotary_PINA_4))
	   RotaryStore[i].state = quarttable[RotaryStore[i].state & 0xf][pinstate];
  return (RotaryStore[i].state & 0x30);
}

//volatile uint32_t tmp;
//volatile uint8_t tmpi;

void CheckRotaries(void){
	uint8_t res,j=0;
	extern 	uint32_t * Rot_PINA_IDR, * Rot_PINB_IDR;
	extern 	uint16_t Rot_PINA_pin, Rot_PINB_pin;
	extern  uint8_t Number_Rotaries, Number_Single_Rotaries;
	extern  struct rot_conf Single_rotaries[USEDPINS];


	for (uint8_t i=0;i<USEDPINS;i++){
		if ((pins[i].pin_type == Chain_Rotary_Enc_1) || (pins[i].pin_type == Chain_Rotary_Enc_2) || (pins[i].pin_type == Chain_Rotary_Enc_4)) {
			*(pins[i].bsrr_reg_addr) = 0x1<<pins[i].pin_number;
			res = rotary_process(j, pins[i].pin_type, Rot_PINA_IDR, Rot_PINB_IDR, Rot_PINA_pin, Rot_PINB_pin);
			if ((res) && (millis-RotaryStore[j].time_pressed)>ROTDEBOUNCE) {RotaryStore[j].pressed = res; RotaryStore[j].time_pressed=millis;}
			*(pins[i].bsrr_reg_addr) = 0x1<<(pins[i].pin_number+16);
			j++;
		}
	}

	j=Number_Rotaries;
	for (uint8_t i=0; i < Number_Single_Rotaries; i++){
		res = rotary_process(j, Single_rotaries[i].PINA_Type, Single_rotaries[i].PINA_IDR, Single_rotaries[i].PINB_IDR, Single_rotaries[i].PINA, Single_rotaries[i].PINB);
		if ((res) && (millis-RotaryStore[j].time_pressed)>ROTDEBOUNCE) {RotaryStore[j].pressed = res; RotaryStore[j].time_pressed=millis;}
		j++;
	}
}
