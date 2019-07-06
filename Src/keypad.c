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
#include "..\common_types\common_structs.h"

extern struct pin_conf pins[USEDPINS];
extern uint8_t Number_Rows, Number_Columns;
uint64_t millis;
struct keypad buttons[MAX_BUTTONS];
volatile extern struct total_config_ config;
extern volatile uint8_t SBstore[MAX_BUTTONS];

volatile extern struct mouse_report_ mouse_report;
volatile extern struct keyboard_report_ keyboard_report;
volatile extern struct gamepad_report_ gamepad_report;
volatile extern struct multimedia_report_ multimedia_report;



void CheckButtons(void) {

	uint8_t column=0, rowstate=0, button=0, pole=0;

	button = Number_Rows*Number_Columns;

	for (uint8_t i=0;i<USEDPINS;i++){
		if ((config.pin[i] == Button_COLUMN) || (config.pin[i] == RotSwPole)) {
			*(pins[i].bsrr_reg_addr) = 0x1<<pins[i].pin_number;
			if (config.pin[i] == Button_COLUMN) CheckRows(column++,smpl_button);
			if (config.pin[i] == RotSwPole) CheckRows(pole++,rotswitch);
			*(pins[i].bsrr_reg_addr) = 0x1<<(pins[i].pin_number+16);
		}
		if (config.pin[i] == Button) {
			if (((*pins[i].idr_reg_addr) & 0x1<<(pins[i].pin_number)) != 0)   {
				rowstate = 1;
			  } else {
				rowstate = 0;
			  };
			SetButtonState(button++,rowstate, smpl_button);
		}
		if (config.pin[i] == Button_GND) {
			if (((*pins[i].idr_reg_addr) & 0x1<<(pins[i].pin_number)) != 0)   {
				rowstate = 0;
			  } else {
				rowstate = 1;
			  };
			SetButtonState(button++,rowstate, smpl_button);
		}
	}
}

void CheckRows(uint8_t column, uint8_t type) {
	volatile uint8_t row=0,rowstate=0,button=0,wire=0;
	extern uint8_t Number_Columns;
	extern uint8_t Number_Wires;
	extern uint8_t Number_Buttons;
//	extern uint8_t Number_Simple_Buttons;

	for (uint8_t i=0;i<USEDPINS;i++){
		if ((config.pin[i] == Button_ROW) || (config.pin[i] == RotSwWire)) {
			if (((*pins[i].idr_reg_addr) & 0x1<<(pins[i].pin_number)) != 0)   {
				rowstate = 1;
			  } else {
				rowstate = 0;
			  };
			if ((config.pin[i] == Button_ROW) && (type == smpl_button)) {
				button = row*Number_Columns + column;// + Number_Simple_Buttons;
				SetButtonState(button,rowstate,smpl_button);
				row++;
			}
			if ((config.pin[i] == RotSwWire) && (type == rotswitch)) {
				button = column*Number_Wires + wire + Number_Buttons; //Number_Simple_Buttons;
				SetButtonState(button,rowstate,rotswitch);
				wire++;
			}
		}
	}
}

void SetButtonState(uint8_t i, uint8_t rowstate, button_type type) {

	extern uint64_t millis;

	uint16_t press_time_limit = 0;
	uint16_t min_time_limit = 0;

	if (type == a2b_button) {
		press_time_limit = config.analog_2_button_press_time;
		min_time_limit = config.analog_2_button_min_time;
	}
	if (type == rotswitch) {
		press_time_limit = config.rotswitch_press_time;
		min_time_limit = config.rotswitch_min_time;
	}

	if (rowstate == 1) {

		if (buttons[i].prev_state == 0) { //if previous state is 0, then just remember push time
			buttons[i].time_pressed = millis;
		}

		if (press_time_limit) {
			if ((buttons[i].pressed == 1) &&  //if already pressed and longer then presstime
					 (millis - buttons[i].time_pressed  > press_time_limit)) { //then reset
				buttons[i].pressed = 0;
			}
		}

		if ((buttons[i].prev_state == 1) &&			//if previous state is HIGH and time since 1st push is
				(!(buttons[i].current_state)) && 	//more than debounce time then button is pressed
			 (millis - buttons[i].time_pressed  > config.button_debounce_time) &&
			 (millis - buttons[i].time_pressed  > min_time_limit)) {
				buttons[i].pressed = 1;
				buttons[i].current_state = 1;
				buttons[i].time_pressed = millis;
		}

		// for one-time-press buttons
		if ((SBstore[i] == player_button) ||
				(SBstore[i] == play_button) ||
				(SBstore[i] == stop_button) ||
				(SBstore[i] == eject_button) ||
				(SBstore[i] == next_button) ||
				(SBstore[i] == prev_button) ||
				(SBstore[i] == calc_button) ||
				(SBstore[i] == cpanel_button) ||
				(SBstore[i] == taskman_button) ||
				(SBstore[i] == browser_button) ||
				(SBstore[i] == browserhome_button) ||
				(SBstore[i] == browserback_button) ||
				(SBstore[i] == browserforward_button)){
			if ((buttons[i].pressed) && (millis - (buttons[i].time_pressed) > (3*config.usb_exchange_rate))) {
				buttons[i].pressed = 0;
			}
		}

		buttons[i].prev_state = 1; //set previous state to 1
	}


	if (rowstate == 0) {
		buttons[i].current_state = 0;
		buttons[i].pressed = 0;
		buttons[i].prev_state = 0; //set previous state to 0
	}
}

void fill_packets_4_buttons(void){
    uint8_t pov[4] = {0};
    extern uint8_t total_buttons;

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
		if (SBstore[i] == player_button) {
			if (buttons[i].pressed){
				multimedia_report.audio_player = 1;
			} else {
				multimedia_report.audio_player = 0;
			}
		}
		if (SBstore[i] == play_button) {
			if (buttons[i].pressed){
				multimedia_report.play = 1;
			} else {
				multimedia_report.play = 0;
			}
		}
		if (SBstore[i] == stop_button) {
			if (buttons[i].pressed){
				multimedia_report.stop = 1;
			} else {
				multimedia_report.stop = 0;
			}
		}
		if (SBstore[i] == eject_button) {
			if (buttons[i].pressed){
				multimedia_report.eject = 1;
			} else {
				multimedia_report.eject = 0;
			}
		}
		if (SBstore[i] == next_button) {
			if (buttons[i].pressed){
				multimedia_report.scan_next = 1;
			} else {
				multimedia_report.scan_next = 0;
			}
		}
		if (SBstore[i] == prev_button) {
			if (buttons[i].pressed){
				multimedia_report.scan_prev = 1;
			} else {
				multimedia_report.scan_prev = 0;
			}
		}
		if (SBstore[i] == calc_button) {
			if (buttons[i].pressed){
				multimedia_report.calculator = 1;
			} else {
				multimedia_report.calculator = 0;
			}
		}
		if (SBstore[i] == cpanel_button) {
			if (buttons[i].pressed){
				multimedia_report.control_panel = 1;
			} else {
				multimedia_report.control_panel = 0;
			}
		}
		if (SBstore[i] == taskman_button) {
			if (buttons[i].pressed){
				multimedia_report.task_manager = 1;
			} else {
				multimedia_report.task_manager = 0;
			}
		}
		if (SBstore[i] == explorer_button) {
			if (buttons[i].pressed){
				multimedia_report.browser = 1;
			} else {
				multimedia_report.browser = 0;
			}
		}
		if (SBstore[i] == browserhome_button) {
			if (buttons[i].pressed){
				multimedia_report.home = 1;
			} else {
				multimedia_report.home = 0;
			}
		}
		if (SBstore[i] == browserback_button) {
			if (buttons[i].pressed){
				multimedia_report.back = 1;
			} else {
				multimedia_report.back = 0;
			}
		}
		if (SBstore[i] == browserforward_button) {
			if (buttons[i].pressed){
				multimedia_report.forward = 1;
			} else {
				multimedia_report.forward = 0;
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


}
