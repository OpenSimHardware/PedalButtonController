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
volatile extern uint16_t Rot_Press_Time;

int main(void)

{
	extern volatile struct rots RotaryStore[USEDPINS];
    extern uint8_t Number_Rotaries, Number_Single_Rotaries;
    extern uint8_t Number_Buttons;
    extern uint8_t Number_RotSwitches;
//    extern uint8_t Number_RotSwitches;
//    extern uint8_t buttons_offset;
    extern uint8_t encoders_offset;
    extern volatile uint64_t millis;
    extern struct keypad buttons[MAXBUTTONS];
    uint8_t chk=0, packet_counter=0;
    extern USBD_HandleTypeDef  *hUsbDevice_0;
    extern uint8_t POV_config;


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

	// Null point for Hat Switches
	USBSendBuffer[21] = 8;
	USBSendBuffer[22] = 8;
	USBSendBuffer[23] = 8;
	USBSendBuffer[24] = 8;


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
		//	[1] - 8 buttons / 4 encoders
		//	[2] - 8 buttons / 4 encoders
		//	[3] - 8 buttons / 4 encoders
		//	[4] - 8 buttons / 4 encoders
		//	[5] - 8 buttons / 4 encoders
		//	[6] - 8 buttons / 4 encoders
		//	[7]	- 8 buttons / 4 encoders
		//	[8] - 8 buttons / 4 encoders
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
	  	//	[21]- 1 Hat Switch
	    //  [22]- 2 Hat Switch
	    //	[23]- 3 Hat Switch
	    //	[24]- 4 Hat Switch



	  	 fill_buffer_4_axises();
	  	 CheckRotaries();

	  	 for (uint8_t i=0;i<4;i++) {
	  		 if (POV_config & (0x1<<i)) {
	  			 chk = buttons[i*4].pressed<<3 |
	  					 (buttons[i*4+1].pressed<<2) |
	  					 (buttons[i*4+2].pressed<<1) |
	  					 (buttons[i*4+3].pressed);
	  			 switch (chk) {
	  			 	 case (8)	: USBSendBuffer[21+i]=0; break;
	  			 	 case (12)	: USBSendBuffer[21+i]=1; break;
	  			 	 case (4)	: USBSendBuffer[21+i]=2; break;
	  			 	 case (6)	: USBSendBuffer[21+i]=3; break;
	  			 	 case (2)	: USBSendBuffer[21+i]=4; break;
	  			 	 case (3)	: USBSendBuffer[21+i]=5; break;
	  			 	 case (1)	: USBSendBuffer[21+i]=6; break;
	  			 	 case (9)	: USBSendBuffer[21+i]=7; break;
	  			 	 default	: USBSendBuffer[21+i]=8; break;
	  			 }

	  		 } else {
	  			USBSendBuffer[21+i]=8;
	  		 }
	  	 }

		 for (uint8_t i=0;i<Number_Buttons+Number_RotSwitches;i++) {
			if ((buttons[i].pressed) && !(POV_config & (0x1<<(i/4)))){
				USBSendBuffer[i/8+1] |= ButtonsCodes[i%8];
			 } else {
				 USBSendBuffer[i/8+1] &= ~ButtonsCodes[i%8];
			 }
		}


	  for (uint8_t i=0;i<Number_Rotaries + Number_Single_Rotaries;i++){

				  diff = millis - RotaryStore[i].time_pressed;

				  if (!RotaryStore[i].pressed) {
					  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2];
					  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2+1];
				  }


				  if (RotaryStore[i].pressed == DIR_CW) {
					  if ( diff > Rot_Press_Time){
						  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2];
						  RotaryStore[i].pressed = 0;
					  }
				  		 else
				  			 USBSendBuffer[(i/4)+encoders_offset] |= ButtonsCodes[(i%4)*2];
				  	 }

				  if (RotaryStore[i].pressed == DIR_CCW) {
					  if (diff > Rot_Press_Time){
						  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2+1];
						  RotaryStore[i].pressed = 0;
					  }
				  		  else
				  			  USBSendBuffer[(i/4)+encoders_offset] |= ButtonsCodes[(i%4)*2+1];
				  		}
			  }


	  //We should send report only if some action exist
			  for (uint8_t i=1;i<21;i++) {
				  chk |= USBSendBuffer[i];
			  }
			  for (uint8_t i=21;i<25;i++) {
				  if (USBSendBuffer[i] != 8) chk |= USBSendBuffer[i];
			  }
			  if (chk) {
				 USBD_CUSTOM_HID_SendReport(hUsbDevice_0, USBSendBuffer, USEDPINS+1);
				 packet_counter=0;
			  } else {
				  packet_counter++;
				  if (packet_counter < 6) USBD_CUSTOM_HID_SendReport(hUsbDevice_0, USBSendBuffer, USEDPINS+1);
			  }
  }
}
