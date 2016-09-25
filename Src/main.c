/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */
#include "keypad.h"
#include "rotary.h"
#include "periph_init.h"
#include "usbd_customhid.h"
//#include "usbd_hid.h"



/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//static void MX_DMA_Init(void);
//static void MX_ADC1_Init(void);
void Error_Handler(void);

//uint8_t TM_KEYPAD_INT_Read(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void SWV_printnum(long number);

volatile uint32_t ADC1Values[ADC_BUFF_SIZE];
uint32_t a,b;//,c,d,e;
extern uint8_t Keypad_Buttons[USEDPINS][USEDPINS][3];
uint8_t USBSendBuffer[21];			//1 report id, 8 bytes buttons, 12 bytes for 6 axes
uint8_t ButtonsCodes[8] = {
		0x01,	//b00000001,
		0x02,	//b00000010,
		0x04,	//b00000100,
		0x08,	//b00001000,
		0x10,	//b00010000,
		0x20,	//b00100000,
		0x40,	//b01000000,
		0x80,	//b10000000,
};



extern volatile struct rots RotaryStore[USEDPINS];
extern uint8_t Number_Rotaries;
extern uint8_t Number_Rows, Number_Columns;
extern volatile uint64_t millis;
extern struct keypad buttons[USEDPINS];

//extern __IO uint8_t PrevXferComplete;

//extern uint32_t gpioa_l,gpioa_h,gpiob_l,gpiob_h,gpioc_l,gpioc_h;

//uint32_t loc_gpioa_l,loc_gpioa_h,loc_gpiob_l,loc_gpiob_h,loc_gpioc_l,loc_gpioc_h;


extern USBD_HandleTypeDef  *hUsbDevice_0;

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


int main(void)
{

  /* USER CODE BEGIN 1 */
//	TM_KEYPAD_Button_t Keypad_Button;

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */

//  MX_GPIO_Init();
  gpio_init();
//   MX_DMA_Init();
//  MX_ADC1_Init();
   adc_init();
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN 2 */
// -- Enables ADC and starts conversion of the regular channels.
//   if( HAL_ADC_Start(&hadc1) != HAL_OK)
//	   Error_Handler();
// -- Enables ADC DMA request
//   if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1Values, 7) != HAL_OK)
//	   Error_Handler();

   USBSendBuffer[0] = 4;
   uint64_t diff;
   uint8_t chk=0;

   uint8_t buttons_offset=Number_Rotaries*2/8 + 1;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
  /* USER CODE BEGIN 3 */
//	  a = ADC1Values[0];
//	  b = ADC1Values[1];
//	  c = ADC1Values[2];
//	  d = ADC1Values[3];
//	  e = ADC1Values[4];
	 // c++;

	  CheckRotaries();

//	USBSendBuffer structure:
//	[0] - report id (4)
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

	  a = ADC1Values[0];
	  USBSendBuffer[9] = LOBYTE(a);
	  USBSendBuffer[10] = HIBYTE(a);
	  a = ADC1Values[1];
	  USBSendBuffer[11] = LOBYTE(a);
	  USBSendBuffer[12] = HIBYTE(a);
	  a = ADC1Values[2];
	  USBSendBuffer[13] = LOBYTE(a);
	  USBSendBuffer[14] = HIBYTE(a);

	  a = ADC1Values[3];
	  USBSendBuffer[15] = LOBYTE(a);
	  USBSendBuffer[16] = HIBYTE(a);
	  a = ADC1Values[4];
	  USBSendBuffer[17] = LOBYTE(a);
	  USBSendBuffer[18] = HIBYTE(a);

	  a = ADC1Values[5];
	  b = ADC1Values[6];
	  a = (a > b) ? a : b;
	  USBSendBuffer[19] = LOBYTE(a);
	  USBSendBuffer[20] = HIBYTE(a);


//	  buttons_offset=1;
	  for (uint8_t i=0;i<Number_Columns*Number_Rows;i++) {
		  if (buttons[i].pressed) {
			  USBSendBuffer[buttons_offset+i/8] |= ButtonsCodes[i%8];
		  } else {
			  USBSendBuffer[buttons_offset+i/8] &= ~ButtonsCodes[i%8];
		  }
	  }

//	  for (uint8_t i=0;i<Number_Columns;i++)
//		  for (uint8_t j=0;j<Number_Rows;j++){
//			  if (Keypad_Buttons[i][j][0] == 1) {
//				  USBSendBuffer[4+i] |= ButtonsCodes[j];
//			//	  SWV_printnum((long)Keypad_Buttons[i][j][0]);
//			  } else {
//				  USBSendBuffer[4+i] &= ~ButtonsCodes[j];
//			  }
//		  }

	  //CW: Byte[i/4] = mass[(i%4) *2]
//	  CCW: bytes[i/4] = mass[(i%4) *2 + 1]

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


	  for (uint8_t i=1;i<21;i++) {
		  chk |= USBSendBuffer[i];
	  }

	  if (chk) {
		  USBD_CUSTOM_HID_SendReport(hUsbDevice_0, USBSendBuffer, 21);
	  }



	//  HAL_Delay(1000);


  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
//  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
//static void MX_ADC1_Init(void)
//{
//
//  ADC_ChannelConfTypeDef sConfig;
//
//    /**Common config
//    */
//  hadc1.Instance = ADC1;
//  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
//  hadc1.Init.ContinuousConvMode = ENABLE;
//  hadc1.Init.DiscontinuousConvMode = DISABLE;
//  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
//  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
//  hadc1.Init.NbrOfConversion = 7;
//  if (HAL_ADC_Init(&hadc1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//   /**Configure Regular Channel
//    */
//  sConfig.Channel = ADC_CHANNEL_0;
//  sConfig.Rank = 1;
////  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
//  sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
////  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }

//    /**Configure Regular Channel
//    */
//  sConfig.Channel = ADC_CHANNEL_1;
//  sConfig.Rank = 2;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }

//  sConfig.Channel = ADC_CHANNEL_2;
//  sConfig.Rank = 3;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }

//  sConfig.Channel = ADC_CHANNEL_3;
//  sConfig.Rank = 4;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }

//  sConfig.Channel = ADC_CHANNEL_4;
//  sConfig.Rank = 5;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }

//  sConfig.Channel = ADC_CHANNEL_5;
//   sConfig.Rank = 6;
//   if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   sConfig.Channel = ADC_CHANNEL_6;
//    sConfig.Rank = 7;
//    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//    {
//      Error_Handler();
//    }



//}

/** 
  * Enable DMA controller clock
  */
//void MX_DMA_Init(void)
//{
//  /* DMA controller clock enable */
//  __HAL_RCC_DMA1_CLK_ENABLE();
//
  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

//}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
//void MX_GPIO_Init(void)
//{

//  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOC_CLK_ENABLE();
//  __HAL_RCC_GPIOD_CLK_ENABLE();
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();

////  gpio_init();

  /*Configure GPIO pin : PC13 */
//  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 PA4 PA7 
                           PA15 */
//  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 PA8 PA9 
                           PA10 */
  /*GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);*/

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 
                           PB12 PB13 PB14 PB3 
                           PB4 PB6 PB7 PB8 
                           PB9 */
//  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB15 PB5 */
//  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|
//		  	  	  	  	  GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

//  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

//}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
//  while(1)
//  {
//  }
	ITM_SendChar('E');
  /* USER CODE END Error_Handler */
}

void SWV_printnum(long number)
{
 unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
 unsigned int i = 0;

 //if number is 0
 if (number == 0)
 {
  ITM_SendChar('0'); //if number is zero
     return;
 }
 //account for negative numbers
 if (number < 0)
 {
  ITM_SendChar('-');
  number = number * -1;
 }
 while(number > 0)
 {
  buf[i++] = number % 10; //display in base 10
  number = number / 10;
  //NOTE: the effect of i++ means that the i variable will be at number of digits + 1
 }
 for(; i > 0; i--)
 {
  ITM_SendChar((char)('0' + buf[i-1]));
 }
}


#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
