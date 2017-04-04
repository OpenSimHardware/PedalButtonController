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

DMA_HandleTypeDef hdma_adc1;
volatile uint8_t USBSendBuffer[USEDPINS+1]={1,0};			//1 report id, 8 bytes buttons, 12 bytes for 6 axes


int main(void)

{
	extern volatile struct rots RotaryStore[USEDPINS];
    extern uint8_t Number_Rotaries;
    extern uint8_t Number_Buttons;
    extern uint8_t Number_RotSwitches;
//    extern uint8_t Number_RotSwitches;
    extern uint8_t buttons_offset;
    extern volatile uint64_t millis;
    extern struct keypad buttons[MAXBUTTONS];
    uint8_t chk=0;
    extern USBD_HandleTypeDef  *hUsbDevice_0;

	const uint8_t ButtonsCodes[8] = {
			0x01,	//b00000001,
			0x02,	//b00000010,
			0x04,	//b00000100,
			0x08,	//b00001000,
			0x10,	//b00010000,
			0x20,	//b00100000,
			0x40,	//b01000000,
			0x80,	//b10000000,
	};

	uint64_t diff;

  /* Configure the system clock, Initializes the Flash interface and the Systick */
  sysclock_init();

  /* Initialize all configured peripherals */
  gpio_init();
//  adc_init();
  MX_USB_DEVICE_Init();

  while (1)
  {


		//	USBSendBuffer structure:
		//	[0] - report id (1)
		//	[1] - 4 encoders (8 buttons)
		//	[2] - 4 encoders (8 buttons)
		//	[3] - 3 encoders (6 buttons) + 2 not used buttons
		//	[4] - 8 buttons
		//	[5] - 8 buttons
		//	[6] - 8 buttons
		//	[7]	- 8 buttons
		//	[8] - 8 buttons
		//	[9] - LOWBYTE from 1st axis
		//	[10]- HIGHBYTE from 1st axis
		//	[11]- LOWBYTE from 2nd axis
		//	[12]- HIGHBYTE from 2nd axis
		//	[13]- LOWBYTE from 3rd axis
		//	[14]- HIGHBYTE from 3rd axis
		//	[15]- LOWBYTE from 4th axis
		//	[16]- HIGHBYTE from 4th axis
		//	[17]- LOWBYTE from 5th axis
		//	[18]- HIGHBYTE from 5th axis
		//	[19]- LOWBYTE from 6th axis
		//	[20]- HIGHBYTE from 6th axis



	  	 fill_buffer_4_axises();
	  	 CheckRotaries();


		 for (uint8_t i=0;i<Number_Buttons+Number_RotSwitches;i++) {
			if (buttons[i].pressed) {
			 USBSendBuffer[buttons_offset+i/8] |= ButtonsCodes[i%8];
			 } else {
			 USBSendBuffer[buttons_offset+i/8] &= ~ButtonsCodes[i%8];
			 }
		}


	  for (uint8_t i=0;i<Number_Rotaries;i++){

				  diff = millis - RotaryStore[i].time_pressed;

				  if (RotaryStore[i].pressed == DIR_CW) {
						  if ( diff > ROTTIME){
						  USBSendBuffer[(uint8_t)(i/4)+1] &= ~ButtonsCodes[(i%4)*2];
						  RotaryStore[i].pressed = 0;
					  }
				  		 else
				  			 USBSendBuffer[(uint8_t)(i/4)+1] |= ButtonsCodes[(i%4)*2];
				  	 }

				  if (RotaryStore[i].pressed == DIR_CCW) {
					  if (diff > ROTTIME){
						  USBSendBuffer[(uint8_t)(i/4)+1] &= ~ButtonsCodes[(i%4)*2+1];
						  RotaryStore[i].pressed = 0;
					  }
				  		  else
				  			  USBSendBuffer[(uint8_t)(i/4)+1] |= ButtonsCodes[(i%4)*2+1];
				  		}
			  }


			  for (uint8_t i=1;i<USEDPINS+1;i++) {
				  chk |= USBSendBuffer[i];
			  }

			  if (chk) {
				  USBD_CUSTOM_HID_SendReport(hUsbDevice_0, USBSendBuffer, USEDPINS+1);
			  }


  }
}
