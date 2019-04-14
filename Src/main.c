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
volatile uint8_t USBSendBuffer[USEDPINS+1]={1,0};			//1 report id, 8 bytes buttons, 12 bytes for 6 axes
//volatile extern uint16_t Rot_Press_Time;
volatile extern struct total_config_ config;
volatile extern struct mouse_report_ mouse_report;
volatile extern struct keyboard_report_ keyboard_report;
volatile extern struct gamepad_report_ gamepad_report;
volatile extern struct multimedia_report_ multimedia_report;

int main(void)

{
    extern struct keypad buttons[MAX_BUTTONS];
    extern volatile uint8_t SBstore[MAX_BUTTONS];
    extern uint8_t total_buttons;
    uint8_t pov[4] = {0};


  /* Configure the system clock, Initializes the Flash interface and the Systick */
  sysclock_init();

  /* Initialize all configured peripherals */
  gpio_init();
//  adc_init();
  MX_USB_DEVICE_Init();


  while (1)
  {
	  	 fill_buffer_4_axises();
	  	 CheckRotaries();

	  	 for (uint8_t i=0;i<MAX_POVS;i++) {
	  		pov[i]=0;
	  	 }

		 for (uint8_t i=0;i<total_buttons;i++) {
				if (SBstore[i] == pov1up_button){
					if (buttons[i].pressed)
						pov[0] |= 1<<3;
				}
				if (SBstore[i] == pov1right_button){
					if (buttons[i].pressed)
						pov[0] |= 1<<2;
				}
				if (SBstore[i] == pov1down_button){
					if (buttons[i].pressed)
						pov[0] |= 1<<1;
				}
				if (SBstore[i] == pov1left_button){
					if (buttons[i].pressed)
						pov[0] |= 1;
				}
				if (SBstore[i] == pov2up_button){
					if (buttons[i].pressed)
						pov[1] |= 1<<3;
				}
				if (SBstore[i] == pov2right_button){
					if (buttons[i].pressed)
						pov[1] |= 1<<2;
				}
				if (SBstore[i] == pov2down_button){
					if (buttons[i].pressed)
						pov[1] |= 1<<1;
				}
				if (SBstore[i] == pov2left_button){
					if (buttons[i].pressed)
						pov[1] |= 1;
				}
				if (SBstore[i] == pov3up_button){
					if (buttons[i].pressed)
						pov[2] |= 1<<3;
				}
				if (SBstore[i] == pov3right_button){
					if (buttons[i].pressed)
						pov[2] |= 1<<2;
				}
				if (SBstore[i] == pov3down_button){
					if (buttons[i].pressed)
						pov[2] |= 1<<1;
				}
				if (SBstore[i] == pov3left_button){
					if (buttons[i].pressed)
						pov[2] |= 1;
				}
				if (SBstore[i] == pov4up_button){
					if (buttons[i].pressed)
						pov[3] |= 1<<3;
				}
				if (SBstore[i] == pov4right_button){
					if (buttons[i].pressed)
						pov[3] |= 1<<2;
				}
				if (SBstore[i] == pov4down_button){
					if (buttons[i].pressed)
						pov[3] |= 1<<1;
				}
				if (SBstore[i] == pov4left_button){
					if (buttons[i].pressed)
						pov[3] |= 1;
				}
			 if (SBstore[i] == joystick_button) {
				 if (buttons[i].pressed){
					 //USBSendBuffer[i/8+1] |= ButtonsCodes[i%8];
					 gamepad_report.buttons |= 1ULL<<i;
				 } else {
					 //USBSendBuffer[i/8+1] &= ~ButtonsCodes[i%8];
					 gamepad_report.buttons &= ~(1ULL<<i);
				 }
			 }
			if (SBstore[i] == mouseleft_button){
				if (buttons[i].pressed){
					mouse_report.left_button = 1;
				} else {
					mouse_report.left_button = 0;
				}
			}
			if (SBstore[i] == mousemiddle_button){
				if (buttons[i].pressed){
					mouse_report.middle_button = 1;
				} else {
					mouse_report.middle_button = 0;
				}
			}
			if (SBstore[i] == mouseright_button){
				if (buttons[i].pressed){
					mouse_report.right_button = 1;
				} else {
					mouse_report.right_button = 0;
				}
			}
			if (SBstore[i] == leftcontrol_button){
				if (buttons[i].pressed){
					keyboard_report.left_ctrl = 1;
				} else {
					keyboard_report.left_ctrl = 0;
				}
			}
			if (SBstore[i] == leftshift_button){
				if (buttons[i].pressed){
					keyboard_report.left_shft = 1;
				} else {
					keyboard_report.left_shft = 0;
				}
			}
			if (SBstore[i] == leftalt_button){
				if (buttons[i].pressed){
					keyboard_report.left_alt = 1;
				} else {
					keyboard_report.left_alt = 0;
				}
			}
			if (SBstore[i] == leftgui_button){
				if (buttons[i].pressed){
					keyboard_report.left_gui = 1;
				} else {
					keyboard_report.left_gui = 0;
				}
			}
			if (SBstore[i] == rightcontrol_button){
				if (buttons[i].pressed){
					keyboard_report.right_ctrl = 1;
				} else {
					keyboard_report.right_ctrl = 0;
				}
			}
			if (SBstore[i] == rightshift_button){
				if (buttons[i].pressed){
					keyboard_report.right_shft = 1;
				} else {
					keyboard_report.right_shft = 0;
				}
			}
			if (SBstore[i] == rightalt_button){
				if (buttons[i].pressed){
					keyboard_report.right_alt = 1;
				} else {
					keyboard_report.right_alt = 0;
				}
			}
			if (SBstore[i] == rightgui_button){
				if (buttons[i].pressed){
					keyboard_report.right_gui = 1;
				} else {
					keyboard_report.right_gui = 0;
				}
			}
			if 		(((SBstore[i] >= a_button) && (SBstore[i] <= space_button)) ||
					((SBstore[i] >= f1_button) && (SBstore[i] <= f12_button)) ||
					((SBstore[i] >= insert_button) && (SBstore[i] <= uparrow_button))) {
				if (buttons[i].pressed){
					keyboard_report.key1 = SBstore[i];
				} else {
					keyboard_report.key1 = 0;
				}
			}
			if (SBstore[i] == volumemute_button) {
				if (buttons[i].pressed){
					multimedia_report.volume_mute = 1;
				} else {
					multimedia_report.volume_mute = 0;
				}
			}
			if (SBstore[i] == volumeup_button) {
				if (buttons[i].pressed){
					multimedia_report.volume_up = 1;
				} else {
					multimedia_report.volume_up = 0;
				}
			}
			if (SBstore[i] == volumedown_button) {
				if (buttons[i].pressed){
					multimedia_report.volume_down = 1;
				} else {
					multimedia_report.volume_down = 0;
				}
			}
		 }

		 for (uint8_t i=0;i<MAX_POVS;i++) {
		 	  			 switch (pov[i]) {
		 	  			 	 case (8)	: gamepad_report.pov[i] = 0; break;
		 	  			 	 case (12)	: gamepad_report.pov[i] = 1; break;
		 	  			 	 case (4)	: gamepad_report.pov[i] = 2; break;
		 	  			 	 case (6)	: gamepad_report.pov[i] = 3; break;
		 	  			 	 case (2)	: gamepad_report.pov[i] = 4; break;
		 	  			 	 case (3)	: gamepad_report.pov[i] = 5; break;
		 	  			 	 case (1)	: gamepad_report.pov[i] = 6; break;
		 	  			 	 case (9)	: gamepad_report.pov[i] = 7; break;
		 	  			 	 default	: gamepad_report.pov[i] = 8; break;
		 	  			 }
		 	  		 }

/*
	  for (uint8_t i=0;i<Number_Rotaries + config.total_single_encoders;i++){

				  diff = millis - RotaryStore[i].time_pressed;

				  if (diff > config.rotary_press_time) {
					  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2];
					  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2+1];
					  RotaryStore[i].pressed = 0;
					  RotaryStore[i].previous_state = 0;
				  } else {
					  if (!RotaryStore[i].previous_state){
						  if (RotaryStore[i].pressed == DIR_CW) {
							  USBSendBuffer[(i/4)+encoders_offset] |= ButtonsCodes[(i%4)*2];
						  }
						  if (RotaryStore[i].pressed == DIR_CCW) {
							  USBSendBuffer[(i/4)+encoders_offset] |= ButtonsCodes[(i%4)*2+1];
						  }
						  RotaryStore[i].previous_state = RotaryStore[i].pressed;
					  }
				  }
	  }

				  if (!RotaryStore[i].pressed) {
					  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2];
					  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2+1];
				  }


				  if (RotaryStore[i].pressed == DIR_CW) {
					  if ( diff > config.rotary_press_time){
						  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2];
						  RotaryStore[i].pressed = 0;
					  }
				  		 else
				  			 USBSendBuffer[(i/4)+encoders_offset] |= ButtonsCodes[(i%4)*2];
				  	 }

				  if (RotaryStore[i].pressed == DIR_CCW) {
					  if (diff > config.rotary_press_time){
						  USBSendBuffer[(i/4)+encoders_offset] &= ~ButtonsCodes[(i%4)*2+1];
						  RotaryStore[i].pressed = 0;
					  }
				  		  else
				  			  USBSendBuffer[(i/4)+encoders_offset] |= ButtonsCodes[(i%4)*2+1];
				  		}
			  }
*/

	  //We should send report only if some action exist
			/*  for (uint8_t i=1;i<21;i++) {
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
			  }*/
  }
}
