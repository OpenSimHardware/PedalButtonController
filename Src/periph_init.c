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
#include <keypad.h>
#include <rotary.h>
#include "..\common_types\common_structs.h"


const struct pin_conf pins[USEDPINS] = {
		{(uint32_t *)GPIOA_CRL, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 0},		//A0
		{(uint32_t *)GPIOA_CRL, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 1},		//A1
		{(uint32_t *)GPIOA_CRL, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 2}, 		//A2
		{(uint32_t *)GPIOA_CRL, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 3}, 		//A3
		{(uint32_t *)GPIOA_CRL, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 4}, 		//A4
		{(uint32_t *)GPIOA_CRL, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 5}, 		//A5
		{(uint32_t *)GPIOA_CRL, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 6}, 		//A6
		{(uint32_t *)GPIOA_CRL, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 7}, 		//A7
		{(uint32_t *)GPIOA_CRH, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 8},		//A8
		{(uint32_t *)GPIOA_CRH, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 9}, 		//A9
		{(uint32_t *)GPIOA_CRH, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 10},		//A10
		{(uint32_t *)GPIOA_CRH, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 11},		//A11
		{(uint32_t *)GPIOA_CRH, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 12},		//A12
		{(uint32_t *)GPIOA_CRH, (uint32_t *)GPIOA_BSRR, (uint32_t *)GPIOA_IDR, 15},		//A15
		{(uint32_t *)GPIOB_CRL, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 0},		//B0
		{(uint32_t *)GPIOB_CRL, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 1}, 		//B1
		{(uint32_t *)GPIOB_CRL, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 3},		//B3
		{(uint32_t *)GPIOB_CRL, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 4}, 		//B4
		{(uint32_t *)GPIOB_CRL, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 5}, 		//B5
		{(uint32_t *)GPIOB_CRL, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 6}, 		//B6
		{(uint32_t *)GPIOB_CRL, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 7}, 		//B7
		{(uint32_t *)GPIOB_CRH, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 8}, 		//B8
		{(uint32_t *)GPIOB_CRH, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 9}, 		//B9
		{(uint32_t *)GPIOB_CRH, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 10},		//B10
		{(uint32_t *)GPIOB_CRH, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 11},		//B11
		{(uint32_t *)GPIOB_CRH, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 12},		//B12
		{(uint32_t *)GPIOB_CRH, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 13},		//B13
		{(uint32_t *)GPIOB_CRH, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 14},		//B14
		{(uint32_t *)GPIOB_CRH, (uint32_t *)GPIOB_BSRR, (uint32_t *)GPIOB_IDR, 15},		//B15
		{(uint32_t *)GPIOC_CRH, (uint32_t *)GPIOC_BSRR, (uint32_t *)GPIOC_IDR, 13},		//C13
		{(uint32_t *)GPIOC_CRH, (uint32_t *)GPIOC_BSRR, (uint32_t *)GPIOC_IDR, 14},		//C14
		{(uint32_t *)GPIOC_CRH, (uint32_t *)GPIOC_BSRR, (uint32_t *)GPIOC_IDR, 15},		//C15
};

//default parameters
volatile struct total_config_ config = {
			.packet_id1 = 4,
			.packet_id2 = 4,
			.packet_id3 = 4,
			.operation_code1 = 1,
			.operation_code2 = 2,
			.operation_code3 = 3,
			.rotary_press_time = 100,
			.rotary_debounce_time = 50,
			.button_debounce_time = 50,
			.rotswitch_press_time = 100,
			.rotswitch_min_time = 0,
			.usb_exchange_rate = 16,
			.combined_axis1_mincalib_value = 0,
			.combined_axis1_maxcalib_value = 4095,
			.combined_axis2_mincalib_value = 0,
			.combined_axis2_maxcalib_value = 4095,
			.combined_axis_percent = 50,
			.combined_axis_pin1 = 4,
			.combined_axis_pin2 = 5,
			.combined_axis_enabled = 0,
			.total_single_encoders = 0,
			.combined_axis_cooperate = 1,
			.combined_axis_separate = 0,
			.combined_axis_pin1_autocalib = 0,
			.combined_axis_pin2_autocalib = 0,
			.analog_2_button_threshold = 600, //for DimSim
			.POV_config = 0,
			.axes[0].axis_min_calib_value = 0x1E, //for DimSim
			.axes[0].axis_max_calib_value = 0x3A3, //for DimSim
			.axes[0].axis_special = 0,
			.axes[1].axis_min_calib_value = 0,
			.axes[1].axis_max_calib_value = 4095,
			.axes[1].axis_special = 0,
			.axes[2].axis_min_calib_value = 0,
			.axes[2].axis_max_calib_value = 4095,
			.axes[2].axis_special = 0,
			.axes[3].axis_min_calib_value = 0,
			.axes[3].axis_max_calib_value = 4095,
			.axes[3].axis_special = 0,
			.axes[4].axis_min_calib_value = 0,
			.axes[4].axis_max_calib_value = 4095,
			.axes[4].axis_special = 0,
			.axes[5].axis_min_calib_value = 0,
			.axes[5].axis_max_calib_value = 4095,
			.axes[5].axis_special = 0,
			.pin[0] = Button_GND,		//A0	//AnalogMedSmooth	//AnalogMedSmooth
			.pin[1] = Button_GND,		//A1	//Analog2Button	//AnalogMedSmooth
			.pin[2] = Button_GND, 		//A2	//Not_Used		//AnalogMedSmooth
			.pin[3] = Button_GND, 		//A3	//Not_Used		//AnalogMedSmooth
			.pin[4] = Button_GND, 		//A4	//Not_Used		//AnalogMedSmooth
			.pin[5] = Button_GND, 		//A5	//Not_Used		//AnalogMedSmooth
			.pin[6] = Button_GND, 		//A6	//Not_Used		//Chain_Rotary_Enc_1
			.pin[7] = Button_GND, 		//A7	//Not_Used		//Button_COLUMN
			.pin[8] = Button_GND, 		//A8	//Not_Used		//Chain_Rotary_Enc_1
			.pin[9] = Button_GND, 	 	//A9	//Not_Used		//Chain_Rotary_Enc_1
			.pin[10] = Button_GND, 		//A10	//Not_Used		//Chain_Rotary_Enc_1
			.pin[11] = Not_Used, 		//A11	//Not_Used		//Not_Used
			.pin[12] = Not_Used, 		//A12	//Not_Used		//Not_Used
			.pin[13] = Button_GND, 		//A15	//Not_Used		//Chain_Rotary_Enc_1
			.pin[14] = Button_GND, 		//B0	//Not_Used		//Chain_Rotary_Enc_1
			.pin[15] = Button_GND, 	 	//B1	//Not_Used		//Chain_Rotary_Enc_1
			.pin[16] = Button_GND, 		//B3	//Not_Used		//Button_COLUMN
			.pin[17] = Button_GND,		//B4	//Not_Used		//Button_ROW
			.pin[18] = Button_GND,		//B5	//Not_Used		//Button_ROW
			.pin[19] = Button_GND, 		//B6	//Not_Used		//Button_ROW
			.pin[20] = Button_GND, 	 	//B7	//Not_Used		//Button_ROW
			.pin[21] = Button_GND, 	 	//B8	//Not_Used		//Button_ROW
			.pin[22] = Button_GND, 	 	//B9	//Not_Used		//Button_ROW
			.pin[23] = Button_GND, 		//B10	//Not_Used		//Chain_Rotary_PINA
			.pin[24] = Button_GND, 		//B11	//Not_Used		//Chain_Rotary_PINB
			.pin[25] = Button_GND, 		//B12	//Not_Used		//Button_COLUMN
			.pin[26] = Button_GND, 		//B13	//Not_Used		//Chain_Rotary_Enc_1
			.pin[27] = Button_GND, 		//B14	//Not_Used		//Chain_Rotary_Enc_1
			.pin[28] = Button_GND, 		//B15	//Not_Used		//Chain_Rotary_Enc_1
			.pin[29] = Button_GND, 		//C13	//Not_Used		//Button_COLUMN
			.pin[30] = Button_GND, 		//C14	//Not_Used		//Button_COLUMN
			.pin[31] = Button_GND, 		//C15	//Not_Used		//Button_COLUMN
};

uint8_t * USBD_PRODUCT_STRING_FS;
uint8_t * USBD_SERIALNUMBER_STRING_FS;
uint8_t USB_Serial_Number_Unique[15] = {0};

volatile uint8_t Number_AnalogButtons=0;
uint8_t Number_DigiButtons=0;
volatile uint8_t send_buffer[USBD_CUSTOMHID_OUTREPORT_BUF_SIZE]={0};
volatile uint8_t config_flag=0;

volatile struct rot_conf Single_rotaries[USEDPINS] = {0};


//TODO not sure why it needs to be global
uint8_t USB_Product_String[31] = {
		79, // O
		83, // S
		72, // H
		32, // Space
		80, // P
		66, // B
		32, // Space
		67, // C
		111, // o
		110, // n
		116, // t
		114, // r
		111, // o
		108, // l
		108, // l
		101, // e
		114, // r
};

uint32_t * Rot_PINA_IDR, * Rot_PINB_IDR;
uint16_t Rot_PINA_pin, Rot_PINB_pin;
uint8_t Number_Rotaries=0,
		//Number_Single_Rotaries=0,
		Number_Rows=0,
		Number_Columns=0,
		Number_Buttons=0,
		Number_Simple_Buttons=0,
		Number_Wires=0,
		Number_RotSwitches=0;
//uint8_t buttons_offset=0;
uint8_t encoders_offset=0;
volatile uint32_t ADC1Values[ADC_BUFF_SIZE];
uint32_t ADC1Prevs_Values[ADC_BUFF_SIZE]={0};
volatile uint64_t millis;
uint8_t Number_Channels=0;
extern volatile uint8_t USBSendBuffer[USEDPINS+1];

extern uint8_t USBD_CUSTOM_HID_CfgDesc[41];


void gpio_init(void) {

	// GPIO Ports Clock for GPIOA/B/C/D
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
	// Disable JTAG and SWD
//	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_DISABLE;

	if (*(get_lastpage_addr((uint16_t *)FLASHSIZEREG)) == 0xFFFF) {
		write_flash();
	} else {
		get_config();
	}


	gpio_ports_config();

	custom_usb_config();

}


void custom_usb_config(void) {
	uint8_t i=0;
	uint32_t * curradr;
	uint32_t id1,id2,id3;
	uint8_t mod;

	USB_Product_String[0] = 79; // O
	USB_Product_String[1] = 83; // S
	USB_Product_String[2] = 72; // H
	USB_Product_String[3] = 32; // Space
	USB_Product_String[4] = 80; // P
	USB_Product_String[5] = 66; // B
	USB_Product_String[6] = 32; // Space
	USB_Product_String[7] = 67; // C
	USB_Product_String[8] = 111; // o
	USB_Product_String[9] = 110; // n
	USB_Product_String[10] = 116; // t
	USB_Product_String[11] = 114; // r
	USB_Product_String[12] = 111; // o
	USB_Product_String[13] = 108; // l
	USB_Product_String[14] = 108; // l
	USB_Product_String[15] = 101; // e
	USB_Product_String[16] = 114; // r
	USB_Product_String[17] = 0;


	if (config.usb_ps_uniq[0]) {
		USB_Product_String[17] = 32; // Space
		USB_Product_String[18] = 40; // (
		while ((config.usb_ps_uniq[i]) && (i < 10)) {
			USB_Product_String[19+i] = config.usb_ps_uniq[i];
			i++;
		}

		USB_Product_String[19+i] = 41; // )
		USB_Product_String[19+i+1] = 0;
	}

	USBD_PRODUCT_STRING_FS = USB_Product_String;

	USB_Serial_Number_Unique[14]=0;
	curradr = (uint32_t *)UNIQUEIDREG;
	id1 = *curradr++;
	id2 = *curradr++;
	id3 = *curradr;

	id2^=id1;
	id3^=id1;

		for (uint8_t i=0; i<6; i++) {
			mod = id2 % 32;
			USB_Serial_Number_Unique[13-i]=uint8_to_32(mod);
			id2 = id2/32;
		}
		USB_Serial_Number_Unique[7]=uint8_to_32(id2);
		for (uint8_t i=0; i<6; i++) {
			mod = id3 % 32;
			USB_Serial_Number_Unique[6-i]=uint8_to_32(mod);
			id3 = id3/32;
		}
		USB_Serial_Number_Unique[0]=uint8_to_32(id3);

 	USBD_SERIALNUMBER_STRING_FS = USB_Serial_Number_Unique;


 	USBD_CUSTOM_HID_CfgDesc[33]=config.usb_exchange_rate;
}

uint8_t uint8_to_32(uint8_t value) {
	if (value > 9) return (value+55);
	else return (value+48);
}

void gpio_ports_config(void) {

	uint32_t tmpregmask;
	uint8_t tmpconfvalue=0x4,
			tmpbsrrvalue=0,
			i,
			tmp=0;
	uint8_t Number_Poles = 0;
	//TODO make it as struct & pass ptr to it to functions
	Number_Channels = 0;
	Number_AnalogButtons = 0;
	Number_DigiButtons = 0;
	extern volatile struct rots RotaryStore[USEDPINS];
	extern struct keypad buttons[MAXBUTTONS];

	for (uint8_t i=0; i<USEDPINS; i++) {
			Single_rotaries[i].PINA_IDR = 0;
			Single_rotaries[i].PINA_Type = 0;
			Single_rotaries[i].PINAmask = 0;
			Single_rotaries[i].PINB_IDR = 0;
			Single_rotaries[i].PINB_Type = 0;
			Single_rotaries[i].PINBmask = 0;
			RotaryStore[i].pressed = 0;
			RotaryStore[i].state = 0;
			RotaryStore[i].time_pressed = 0;
			RotaryStore[i].previous_state = 0;
		}
	Rot_PINA_IDR = 0;
	Rot_PINB_IDR = 0;
	Rot_PINA_pin = 0;
	Rot_PINB_pin = 0;
	Number_Rotaries = 0;
	Number_Rows = 0;
	Number_Columns = 0;
	Number_Buttons = 0;
	Number_Simple_Buttons = 0;
	Number_Wires = 0;
	Number_RotSwitches = 0;
	encoders_offset = 0;

	for (uint8_t i=0; i<ADC_BUFF_SIZE; i++) {
		ADC1Values[i] = 0;
		ADC1Prevs_Values[i] = 0;
	}

	for (uint8_t i=0; i<MAXBUTTONS; i++){
		buttons[i].current_state = 0;
		buttons[i].pressed = 0;
		buttons[i].prev_state = 0;
		buttons[i].time_pressed = 0;
	}


//	uint8_t Number_Single_Rotaries_PINA=0,
//			Number_Single_Rotaries_PINB=0;

	// Reset all prevs states
	GPIOA->CRL=0x44444444;
	GPIOA->CRH=0x44444444;
	GPIOA->ODR=0x0;
	GPIOB->CRL=0x44444444;
	GPIOB->CRH=0x44444444;
	GPIOB->ODR=0x0;
	GPIOC->CRL=0x44444444;
	GPIOC->CRH=0x44444444;
	GPIOC->ODR=0x0;



	// making registers configuration;

	for (i=0;i<USEDPINS;i++){
		switch (config.pin[i]) {
		case Not_Used:		tmpconfvalue=0x4;
							tmpbsrrvalue=0x10;
							break;
		case AnalogLowSmooth:
		case AnalogMedSmooth:
		case AnalogHighSmooth:
		case AnalogNoSmooth:Number_Channels++;
							tmpconfvalue=0x0;
							tmpbsrrvalue=0x10;
							break;
		case Analog2Button: Number_Channels++;
							Number_AnalogButtons++;
							tmpconfvalue=0x0;
							tmpbsrrvalue=0x10;
							break;
		case Chain_Rotary_PINA:
							tmpconfvalue=0x8;
							tmpbsrrvalue=0x10;
							Rot_PINA_IDR=pins[i].idr_reg_addr;
							Rot_PINA_pin=0x1<<pins[i].pin_number;
							break;
		case Chain_Rotary_PINB:
							tmpconfvalue=0x8;
							tmpbsrrvalue=0x10;
							Rot_PINB_IDR=pins[i].idr_reg_addr;
							Rot_PINB_pin=0x1<<pins[i].pin_number;
							break;
		case Button_ROW: 	Number_Rows++;
							tmpconfvalue=0x8;
							tmpbsrrvalue=0x10;
							break;
		case Button:		Number_Simple_Buttons++;
							tmpconfvalue=0x8;
							tmpbsrrvalue=0x10;
							break;
		case Button_GND:	Number_Simple_Buttons++;
							tmpconfvalue=0x8;
							tmpbsrrvalue=0x00;
							break;
		case Chain_Rotary_Enc_1:
		case Chain_Rotary_Enc_2:
		case Chain_Rotary_Enc_4:
							Number_Rotaries++;
							tmpconfvalue=0x02;
							tmpbsrrvalue=0x10;
							break;
		case Single_Rotary_PINA_1:
		case Single_Rotary_PINA_2:
		case Single_Rotary_PINA_4:
//							Single_rotaries[Number_Single_Rotaries_PINA].PINA=(0x1<<pins[i].pin_number);
//							Single_rotaries[Number_Single_Rotaries_PINA].PINA_IDR=pins[i].idr_reg_addr;
//							Single_rotaries[Number_Single_Rotaries_PINA].PINA_Type=pins[i].pin_type;
//							Number_Single_Rotaries_PINA++;
							tmpconfvalue=0x02;
							tmpbsrrvalue=0x10;
							break;
		case Single_Rotary_PINB_1:
		case Single_Rotary_PINB_2:
		case Single_Rotary_PINB_4:
//							Single_rotaries[Number_Single_Rotaries_PINB].PINB=(0x1<<pins[i].pin_number);
//							Single_rotaries[Number_Single_Rotaries_PINB].PINB_IDR=pins[i].idr_reg_addr;
//							Single_rotaries[Number_Single_Rotaries_PINB].PINB_Type=pins[i].pin_type;
//							Number_Single_Rotaries_PINB++;
							tmpconfvalue=0x02;
							tmpbsrrvalue=0x10;
							break;
		case Button_COLUMN: Number_Columns++;
							tmpconfvalue=0x02;
							tmpbsrrvalue=0x10;
							break;
		case RotSwPole:		Number_Poles++;
							tmpconfvalue=0x02;
							tmpbsrrvalue=0x10;
							break;
		case RotSwWire:		Number_Wires++;
							tmpconfvalue=0x8;
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
		*pins[i].bsrr_reg_addr 	= 1 << (pins[i].pin_number+tmpbsrrvalue);
	}

	for (uint8_t i=0; i<config.total_single_encoders; i++) {
		Single_rotaries[i].PINA_IDR=pins[config.single_encoder_pinA[i]].idr_reg_addr;
		Single_rotaries[i].PINA_Type=config.pin[config.single_encoder_pinA[i]];
		Single_rotaries[i].PINAmask=(0x1<<pins[config.single_encoder_pinA[i]].pin_number);
		Single_rotaries[i].PINB_IDR=pins[config.single_encoder_pinB[i]].idr_reg_addr;
		Single_rotaries[i].PINB_Type=config.pin[config.single_encoder_pinB[i]];
		Single_rotaries[i].PINBmask=(0x1<<pins[config.single_encoder_pinB[i]].pin_number);
	}

	Number_DigiButtons = Number_Columns*Number_Rows + Number_Simple_Buttons;
	Number_Buttons = Number_DigiButtons + Number_AnalogButtons;
	Number_RotSwitches = Number_Poles * Number_Wires;
	encoders_offset = (Number_Buttons + Number_RotSwitches)/8;// + 2;
	if (((Number_Buttons + Number_RotSwitches)%8) == 0) encoders_offset++; else encoders_offset=encoders_offset+2;


	adc_init();

	for (uint8_t i=0;i<MAX_AXES;i++) {
			  if (config.axes[i].axis_special == 1) {
				  config.axes[i].axis_min_calib_value = 4095;
				  config.axes[i].axis_max_calib_value = 1;
			  }
		  }

	if (config.combined_axis_enabled) {
		uint8_t lastaxis=0;
		if (Number_Channels-Number_AnalogButtons > MAX_AXES) lastaxis=5; else lastaxis=Number_Channels-Number_AnalogButtons;
		config.axes[lastaxis].axis_min_calib_value = config.combined_axis1_mincalib_value;
		config.axes[lastaxis].axis_max_calib_value = config.combined_axis1_maxcalib_value;
	}
}

void periph_deinit(void){
	//ADC deinit
	ADC1->CR2 |= (uint32_t)0x0;
	//clock disable
	//RCC->APB2ENR = 0;
	//RCC->AHBENR = 0;
	//RCC->APB1ENR = 0;
}

void adc_init(void) {


	//ADC clock enable
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN ;
	//DMA clock enable
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	//reset ADC prev config
	ADC1->CR1=(uint32_t)0x0;
	ADC1->CR2=(uint32_t)0x0;
	ADC1->SMPR1=(uint32_t)0x0;
	ADC1->SMPR2=(uint32_t)0x0;
	ADC1->SQR3=(uint32_t)0x0;
	ADC1->SQR2=(uint32_t)0x0;
	ADC1->SQR1=(uint32_t)0x0;
	//reset DMA prev config
	DMA1_Channel1->CPAR = 0x0;
	DMA1_Channel1->CMAR = 0x0;
	DMA1_Channel1->CCR = 0x0;
	DMA1_Channel1->CNDTR =0x0;


	//Set ADC DR Register as peripheral
	DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
	//Set Memory address
	DMA1_Channel1->CMAR = (uint32_t)ADC1Values;
	//Total number of data transfered
	DMA1_Channel1->CNDTR = Number_Channels;//ADC_BUFF_SIZE;
	//Channel priority very high
	DMA1_Channel1->CCR |= DMA_CCR_PL;
	//Memory size 32bit
	DMA1_Channel1->CCR |= DMA_CCR_MSIZE;
	//Peripheral size 32bit
	DMA1_Channel1->CCR |= DMA_CCR_PSIZE;
	//Circular mode
	DMA1_Channel1->CCR |= DMA_CCR_CIRC;
	//Memory inc
	DMA1_Channel1->CCR |= DMA_CCR_MINC;
	//DMA Channel1 enable
	DMA1_Channel1->CCR |= DMA_CCR_EN;

	//Calibration
	ADC1->CR2 |= ADC_CR2_CAL;
	while (!(ADC1->CR2 & ADC_CR2_CAL));

	//DMA + Continious Conversion
	ADC1->CR2 |= ADC_CR2_DMA;
	ADC1->CR2 |= ADC_CR2_CONT;
	//Scan mode
	ADC1->CR1 |= ADC_CR1_SCAN ;
	//13.5 cycles for all channels
	ADC1->SMPR1 = (uint32_t)0x492492;
	ADC1->SMPR2 = (uint32_t)0x12492492;
	//Wakeup ADC
	ADC1->CR2 |= ADC_CR2_ADON;

	uint8_t channel=0;

	for (uint8_t i=0;i<USEDPINS;i++){
		if ((config.pin[i] == AnalogNoSmooth) || (config.pin[i] == AnalogLowSmooth) ||
				(config.pin[i] == AnalogMedSmooth) || (config.pin[i] == AnalogHighSmooth) ||
				(config.pin[i] == Analog2Button)) {
			if (channel < 6) {
				//ADC1->SQR3 |= channel << (5*channel);
				ADC1->SQR3 |= pins[i].pin_number << (5*channel);
			} else {
				//ADC1->SQR2 |= channel << (5*(channel-6));
				ADC1->SQR2 |= pins[i].pin_number << (5*(channel-6));
			}
			channel++;
		}
	}
	ADC1->SQR1 |= (--channel) << 20;

	//Start ADC
	ADC1->CR2 |= ADC_CR2_ADON;
}

void sysclock_init(void) {
	//HSE on
	RCC->CR |= RCC_CR_HSEON;
	//Wait for HSE is ready
	while (!(RCC->CR & RCC_CR_HSERDY)) {};
	//Turn on prefetch flash buffer
	FLASH->ACR |= FLASH_ACR_PRFTBE;
	//Config for 2 cycles
	FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
	FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
	//PLL as system clock
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	//AHB not divided
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	//APB1 divided by 2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	//APB2 not divided
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	//ADC divided by 8
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8;
	//HSE for PLL source
	RCC->CFGR |= RCC_CFGR_PLLSRC;
	//PLL multiplicator factor
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	//PLL on
	RCC->CR |= RCC_CR_PLLON;
	//Wait until PLL is on
	while(!(RCC->CR & RCC_CR_PLLRDY)) {};


	//USB clock enable
	RCC->APB1ENR |= RCC_APB1ENR_USBEN;

	//SysTick
	SysTick_Config(72000);
	SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;

	NVIC_init();

}


void NVIC_init(void){
	   NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	  /* System interrupt init*/
	  /* MemoryManagement_IRQn interrupt configuration */
	  NVIC_SetPriority(MemoryManagement_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	  /* BusFault_IRQn interrupt configuration */
	  NVIC_SetPriority(BusFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	  /* UsageFault_IRQn interrupt configuration */
	  NVIC_SetPriority(UsageFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	  /* DebugMonitor_IRQn interrupt configuration */
	  NVIC_SetPriority(DebugMonitor_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	  /* SysTick_IRQn interrupt configuration */
	  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
}


void fill_buffer_4_axises(void) {
	  uint8_t Ainput=0;
	  uint8_t AnalogButton=0;

	  for (uint8_t i=0;i<USEDPINS;i++) {
		  switch (config.pin[i]) {
		  	  case AnalogNoSmooth:		  processing_axises(Ainput++, 100, i); break;
		  	  case AnalogLowSmooth:	  	  processing_axises(Ainput++, 60, i); break;
		  	  case AnalogMedSmooth:		  processing_axises(Ainput++, 30, i); break;
		  	  case AnalogHighSmooth:	  processing_axises(Ainput++, 1, i); break;
		  	  case Analog2Button:		  processing_axises(Ainput++, 200+AnalogButton++, i); break;
		  	  default:					  break;
		  }
	  }
}


void processing_axises(uint8_t Ainput, uint8_t Kstab, uint8_t i) {

	uint32_t curr = 0;
	uint32_t optvalue =0;
	uint32_t mapvalue=0;
	uint8_t endvalue;
	uint8_t Number_Axes=0;
static	uint32_t AxisComboValue=0;
static uint8_t pincount=0;
static uint8_t Axis=0;

	Number_Axes=Number_Channels-Number_AnalogButtons-1; //Number of axes not more than analog inputs

	curr = ADC1Values[Ainput];

	if (Kstab > 199) {
		optvalue = (80 *(int32_t)(curr - ADC1Prevs_Values[Ainput]))/100 + ADC1Prevs_Values[Ainput];
		ADC1Prevs_Values[Ainput] = optvalue;
		if (curr > config.analog_2_button_threshold) {
			SetButtonState(Kstab-200 + Number_DigiButtons, 1);
		} else {
			SetButtonState(Kstab-200 + Number_DigiButtons, 0);
		}
		return;
	}

	optvalue = (Kstab *(int32_t)(curr - ADC1Prevs_Values[Ainput]))/100 + ADC1Prevs_Values[Ainput];


	if (config.axes[Axis].axis_special == 1) {
		if (curr < config.axes[Axis].axis_min_calib_value) config.axes[Axis].axis_min_calib_value = curr;
		if (curr > config.axes[Axis].axis_max_calib_value) config.axes[Axis].axis_max_calib_value = curr;
	} else {
		if (optvalue < config.axes[Axis].axis_min_calib_value) optvalue = config.axes[Axis].axis_min_calib_value;
		if (optvalue > config.axes[Axis].axis_max_calib_value) optvalue = config.axes[Axis].axis_max_calib_value;
	}

	ADC1Prevs_Values[Ainput] = optvalue;

	if (config.combined_axis_enabled) {
		Number_Axes-=2;
	if ((i == config.combined_axis_pin1) || (i == config.combined_axis_pin2)){
		pincount++;
		if (i == config.combined_axis_pin1) optvalue = map(optvalue, config.combined_axis1_mincalib_value, config.combined_axis1_maxcalib_value, 0, 4095);
			else optvalue = map(optvalue, config.combined_axis2_mincalib_value, config.combined_axis2_maxcalib_value, 0, 4095);
		if (config.combined_axis_cooperate) {
			if (i == config.combined_axis_pin1) endvalue=config.combined_axis_percent;
				else endvalue=100-config.combined_axis_percent;
			optvalue=(optvalue*endvalue)/100;
			if (pincount==1)  {
				AxisComboValue=optvalue;
//				ADC1Prevs_Values[Ainput] = optvalue;
				return; //not going to send axis value if not processed both inputs
			}
				else optvalue+=AxisComboValue;
		} else {
			if (pincount==1)  {
							AxisComboValue=optvalue;
//							ADC1Prevs_Values[Ainput] = optvalue;
							return; //not going to send axis value if not processed both inputs
						}
							else {
								if (AxisComboValue > optvalue) optvalue=AxisComboValue;
							}
		}
		//Axis=5;
		if (pincount==2) pincount=0;
		//Combined axis will be always on AXIS6
		mapvalue = map(optvalue, config.axes[5].axis_min_calib_value, config.axes[5].axis_max_calib_value, 0, 4095);
//		ADC1Prevs_Values[Ainput] = optvalue;
		USBSendBuffer[9+(10)] = LOBYTE(mapvalue);
		USBSendBuffer[10+(10)] = HIBYTE(mapvalue);
		return;
	}
	}


	mapvalue = map(optvalue, config.axes[Axis].axis_min_calib_value, config.axes[Axis].axis_max_calib_value, 0, 4095);

	USBSendBuffer[9+(2*Axis)] = LOBYTE(mapvalue);
	USBSendBuffer[10+(2*Axis)] = HIBYTE(mapvalue);
	Axis++;

	if ((Axis > MAX_AXES-1) || (Axis > Number_Axes)) Axis=0;
}


uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

