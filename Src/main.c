/*
 * ----------------------------------------------------------------------------------
 * @file  		: main.c
 * @brief 		: Main program body
 *
 * ----------------------------------------------------------------------------------
 *	 Copyright (c) 2017 Dmitry Skulkin <dmitry.skulkin@gmail.com>					*
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
/* Includes ------------------------------------------------------------------*/
#include "periph_init.h"
#include "rotary.h"
#include "keypad.h"
#include "usbd_customhid.h"
#include "usb_device.h"
#include "..\common_types\common_structs.h"

DMA_HandleTypeDef hdma_adc1;
//volatile uint8_t USBSendBuffer[USEDPINS+1]={1,0};			//1 report id, 8 bytes buttons, 12 bytes for 6 axes
//volatile extern uint16_t Rot_Press_Time;

int main(void)

{
  /* Configure the system clock, Initializes the Flash interface and the Systick */
  sysclock_init();

  /* Initialize all configured peripherals */
  gpio_init();
//  adc_init();
  MX_USB_DEVICE_Init();


  while (1)
  {
	  	 CheckRotaries();
  }
}
