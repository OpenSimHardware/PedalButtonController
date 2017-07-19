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

// default ports configuration
volatile struct pin_conf pins[USEDPINS] = {
		{AnalogMedSmooth, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 0},		//A0
		{AnalogMedSmooth, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 1},		//A1
		{AnalogMedSmooth, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 2}, 		//A2
		{AnalogMedSmooth, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 3}, 		//A3
		{AnalogMedSmooth, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 4}, 		//A4
		{AnalogMedSmooth, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 5}, 		//A5
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 6}, 		//A6
		{Button_COLUMN, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 7}, //A7
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 8},	//A8
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 9}, 	//A9
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 10},	//A10
		{Not_Used, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 11},	//A11
		{Not_Used, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 12},	//A12
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 15},	//A15
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 0},	//B0
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 1}, 	//B1
		{Button_COLUMN, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 3},	//B3
		{Button_ROW,	(uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 4}, //B4
		{Button_ROW,	(uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 5}, //B5
		{Button_ROW, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 6}, 	//B6
		{Button_ROW, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 7}, 	//B7
		{Button_ROW, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 8}, 	//B8
		{Button_ROW, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 9}, 	//B9
		{Chain_Rotary_PINA, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 10},	//B10
		{Chain_Rotary_PINB, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 11},	//B11
		{Button_COLUMN, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 12},//B12
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 13},	//B13
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 14},	//B14
		{Chain_Rotary_Enc_1, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 15},	//B15
		{Not_Used, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 13},//C13
		{Button_COLUMN, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 14},//C14
		{Button_COLUMN, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 15},//C15
//Config for Beano :)
//		{Button, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 0},		//A0
//		{Button, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 1},		//A1
//		{Button, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 2}, 		//A2
//		{Button, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 3}, 		//A3
//		{Rotary_PINA, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 4}, 		//A4
//		{Rotary_PINB, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 5}, 		//A5
//		{Rotary_Enc, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 6}, 		//A6
//		{Rotary_Enc, (uint32_t *)0x40010800, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 7}, //A7
//		{RotSwWire, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 8},	//A8
//		{RotSwWire, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 9}, 	//A9
//		{RotSwWire, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 10},	//A10
//		{Not_Used, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 11},	//A11
//		{Not_Used, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 12},	//A12
//		{Button, (uint32_t *)0x40010804, (uint32_t *)0x40010810, (uint32_t *)0x40010808, 15},	//A15
//		{RotSwPole, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 0},	//B0
//		{RotSwWire, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 1}, 	//B1
//		{Button, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 3},	//B3
//		{Button,	(uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 4}, //B4
//		{Button,	(uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 5}, //B5
//		{Button, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 6}, 	//B6
//		{Button, (uint32_t *)0x40010c00, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 7}, 	//B7
//		{Button, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 8}, 	//B8
//		{Button, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 9}, 	//B9
//		{RotSwWire, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 10},	//B10
//		{RotSwWire, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 11},	//B11
//		{RotSwWire, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 12},//B12
//		{RotSwWire, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 13},	//B13
//		{RotSwWire, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 14},	//B14
//		{RotSwWire, (uint32_t *)0x40010c04, (uint32_t *)0x40010c10, (uint32_t *)0x40010c08, 15},	//B15
//		{Not_Used, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 13},//C13
//		{Button, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 14},//C14
//		{Button, (uint32_t *)0x40011004, (uint32_t *)0x40011010, (uint32_t *)0x40011008, 15},//C15
};

volatile struct axis_conf axises[AXISES] =
{
		{0,0,0xFF,0x0F,0,0,0xFFF},
		{0,0,0xFF,0x0F,0,0,0xFFF},
		{0,0,0xFF,0x0F,0,0,0xFFF},
		{0,0,0xFF,0x0F,0,0,0xFFF},
		{0,0,0xFF,0x0F,0,0,0xFFF},
		{0,0,0xFF,0x0F,0,0,0xFFF},
};

volatile struct rot_conf Single_rotaries[USEDPINS] = {0};

volatile uint8_t POV_config=0;

uint32_t * Rot_PINA_IDR, * Rot_PINB_IDR;
uint16_t Rot_PINA_pin, Rot_PINB_pin;
uint8_t Number_Rotaries=0,
		Number_Single_Rotaries=0,
		Number_Rows=0,
		Number_Columns=0,
		Number_Buttons=0,
		Number_Simple_Buttons=0,
		Number_Poles=0,
		Number_Wires=0,
		Number_RotSwitches=0;
//uint8_t buttons_offset=0;
uint8_t encoders_offset=0;
volatile uint32_t ADC1Values[ADC_BUFF_SIZE];
uint32_t ADC1Prevs_Values[ADC_BUFF_SIZE]={0};
volatile uint64_t millis;
uint8_t Number_Channels=0;
extern volatile uint8_t USBSendBuffer[USEDPINS+1];


void gpio_init(void) {

	// GPIO Ports Clock for GPIOA/B/C/D
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN;
	// Disable JTAG and SWD
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_DISABLE;

	if (*(get_lastpage_addr((uint16_t *)FLASHSIZEREG)) == 0xFFFF) {
		write_flash();
	} else {
		get_config();
	}


	gpio_ports_config();

}

void gpio_ports_config(void) {

	uint32_t tmpregmask;
	uint8_t tmpconfvalue=0x4,
			tmpbsrrvalue=0,
			i,
			tmp=0;
	uint8_t Number_Single_Rotaries_PINA=0,
			Number_Single_Rotaries_PINB=0;

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
		switch (pins[i].pin_type) {
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
							Single_rotaries[Number_Single_Rotaries_PINA].PINA=(0x1<<pins[i].pin_number);
							Single_rotaries[Number_Single_Rotaries_PINA].PINA_IDR=pins[i].idr_reg_addr;
							Single_rotaries[Number_Single_Rotaries_PINA].PINA_Type=pins[i].pin_type;
							Number_Single_Rotaries_PINA++;
							tmpconfvalue=0x02;
							tmpbsrrvalue=0x10;
							break;
		case Single_Rotary_PINB_1:
		case Single_Rotary_PINB_2:
		case Single_Rotary_PINB_4:
							Single_rotaries[Number_Single_Rotaries_PINB].PINB=(0x1<<pins[i].pin_number);
							Single_rotaries[Number_Single_Rotaries_PINB].PINB_IDR=pins[i].idr_reg_addr;
							Single_rotaries[Number_Single_Rotaries_PINB].PINB_Type=pins[i].pin_type;
							Number_Single_Rotaries_PINB++;
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

//		if (pins[i].pin_type == Rotary_PINA) {
//			Rot_PINA_IDR=pins[i].idr_reg_addr;
//			Rot_PINA_pin=0x1<<pins[i].pin_number;
//		};
//		if (pins[i].pin_type == Rotary_PINB) {
//			Rot_PINB_IDR=pins[i].idr_reg_addr;
//			Rot_PINB_pin=0x1<<pins[i].pin_number;
//		};

		if (pins[i].pin_number>7) {
			tmp=pins[i].pin_number-8;
		} else {
			tmp=pins[i].pin_number;
		};

//		buttons_offset=Number_Rotaries*2/8 + 2;
		Number_Single_Rotaries = Number_Single_Rotaries_PINA;
		Number_Buttons = Number_Columns*Number_Rows + Number_Simple_Buttons;
		Number_RotSwitches = Number_Poles * Number_Wires;
		encoders_offset = (Number_Buttons + Number_RotSwitches)/8;// + 2;
		if (((Number_Buttons + Number_RotSwitches)%8) == 0) encoders_offset++; else encoders_offset=encoders_offset+2;

		tmpregmask = (uint32_t)(0b1111 << (tmp*4));
		*pins[i].conf_reg_addr = (*(pins[i].conf_reg_addr) & (~tmpregmask)) | (tmpconfvalue << (tmp*4));
		*pins[i].bsrr_reg_addr 	= 1 << (pins[i].pin_number+tmpbsrrvalue);
	}

	adc_init();
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
		if ((pins[i].pin_type == AnalogNoSmooth) || (pins[i].pin_type == AnalogLowSmooth) ||
				(pins[i].pin_type == AnalogMedSmooth) || (pins[i].pin_type == AnalogHighSmooth)) {
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
	  uint8_t axis=0;

	  for (uint8_t i=0;i<USEDPINS;i++) {
		  switch (pins[i].pin_type) {
		  	  case AnalogNoSmooth:		  processing_axises(axis++, 100); break;
		  	  case AnalogLowSmooth:	  	  processing_axises(axis++, 60); break;
		  	  case AnalogMedSmooth:		  processing_axises(axis++, 30); break;
		  	  case AnalogHighSmooth:	  processing_axises(axis++, 1); break;
		  	  default:					  break;
		  }
	  }
}


void processing_axises(uint8_t axis, uint8_t Kstab) {

	uint32_t curr = 0;
	uint32_t optvalue =0;
	uint32_t mapvalue=0;


	curr = ADC1Values[axis];

	optvalue = (Kstab *(int32_t)(curr - ADC1Prevs_Values[axis]))/100 + ADC1Prevs_Values[axis];

	if (optvalue < axises[axis].calib_min) optvalue = axises[axis].calib_min;
	if (optvalue > axises[axis].calib_max) optvalue = axises[axis].calib_max;

	mapvalue = map(optvalue, axises[axis].calib_min, axises[axis].calib_max, 0, 4095);

	ADC1Prevs_Values[axis] = optvalue;
	USBSendBuffer[9+(2*axis)] = LOBYTE(mapvalue);
	USBSendBuffer[10+(2*axis)] = HIBYTE(mapvalue);

}


uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

