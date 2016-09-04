/*
 * ----------------------------------------------------------------------------------
 * @file  		: periph_init.c
 * @brief 		: Periphery initialization  library
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

#include <periph_init.h>


struct pin_conf {
		uint8_t pin_type;
		uint32_t * conf_reg_addr;
		uint32_t * bsrr_reg_addr;
		uint32_t * idr_reg_addr;
		uint8_t pin_number;
	};

// default ports configuration

// pin_type:
// 0 - Not Used
// 1 - Analog
// 2 - Rotary Enc PINA
// 3 - Rotary Enc PINB
// 4 - Rotary Enc
// 5 - Button Matrix ROW
// 6 - Button Matrix COLUMN

// GPIOA
// A0 - A6 - analog
// A7 - A10 - output PP lowspeed
// GPIOB
// B4 - B9, B10 - B11 - input pulldown
// B0, B1, B3, B12 - B15 - output PP lowspeed
// GPIOC
// C13 - C15 output PP lowspeed

volatile struct pin_conf pins[USEDPINS] = {
		{1, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 0},	//A0
		{1, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 1},	//A1
		{1, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 2}, //A2
		{1, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 3}, //A3
		{1, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 4}, //A4
		{1, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 5}, //A5
		{1, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 6}, //A6
		{6, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 7}, //A7
		{4, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 8},	//A8
		{4, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 9}, //A9
		{4, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 10},//A10
		{4, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 0},	//B0
		{4, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 1}, //B1
		{5,	(uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 5}, //B5
		{5, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 6}, //B6
		{5, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 7}, //B7
		{5, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 8}, //B8
		{5, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 9}, //B9
		{2, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 10},//B10
		{3, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 11},//B11
		{6, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 12},//B12
		{4, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 13},//B13
		{4, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 14},//B14
		{4, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 15},//B15
		{6, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 13},//C13
		{6, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 14},//C14
		{6, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 15},//C15}
};

volatile uint16_t * tmp;
void gpio_init(void) {

	// GPIO Ports Clock for GPIOA/B/C/D
	RCC->APB2ENR |= (uint32_t)0x3C;


	if (*(get_lastpage_addr((uint16_t *)FLASHSIZEREG)) == 0xFFFF) {
		write_flash();
	} else {
		get_config();
	}


	gpio_ports_config();

	// Reset all output pins
	GPIOA->ODR &= 0b1111100001111111;
	GPIOB->ODR &= 0b0001111111111100;
	GPIOC->ODR &= 0b0001111111111111;

}

void gpio_ports_config(void) {

	uint32_t tmpregmask;
	uint8_t tmpconfvalue=0x4,tmpbsrrvalue,i,tmp=0;


	// making registers configuration;

	for (i=0;i<USEDPINS;i++){
		switch (pins[i].pin_type) {
		case 0:	tmpconfvalue=0x4;
				tmpbsrrvalue=0x10;
				break;
		case 1: tmpconfvalue=0x0;
				tmpbsrrvalue=0x10;
				break;
		case 2:
		case 3:
		case 5: tmpconfvalue=0x8;
				tmpbsrrvalue=0x10;
				break;
		case 4:
		case 6: tmpconfvalue=0x2;
				tmpbsrrvalue=0x10;
				break;
		}
		if (pins[i].pin_number>7) {
			tmp=pins[i].pin_number-8;
		} else {
			tmp=pins[i].pin_number;
		};
		tmpregmask = (uint32_t)(0b1111 << (tmp*4));
		*pins[i].conf_reg_addr = (*(pins[i].conf_reg_addr) & (~tmpregmask)) | (tmpconfvalue << (tmp*4));
		*pins[i].bsrr_reg_addr &= 1 << (pins[i].pin_number+tmpbsrrvalue);
	}
}
