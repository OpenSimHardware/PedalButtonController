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


/* USER CODE BEGIN Includes */
//#include "usbd_hid.h"
#include "periph_init.h"
#include "rotary.h"
#include "keypad.h"
#include "usbd_customhid.h"
#include "usb_device.h"

#include "usb_device.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
volatile uint8_t USBSendBuffer[USEDPINS+1]={1,0};			//1 report id, 8 bytes buttons, 12 bytes for 6 axes

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

//uint8_t TM_KEYPAD_INT_Read(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


int main(void)
{

  /* USER CODE BEGIN 1 */

	extern volatile struct rots RotaryStore[USEDPINS];
    extern uint8_t Number_Rotaries;
    extern uint8_t Number_Buttons;
    extern uint8_t buttons_offset;
    extern volatile uint64_t millis;
    extern struct keypad buttons[MAXBUTTONS];
    uint8_t chk=0;
//    extern volatile uint32_t ADC1Values[ADC_BUFF_SIZE];
//    extern volatile uint32_t ADC1Prevs_Values[ADC_BUFF_SIZE];
    extern USBD_HandleTypeDef  *hUsbDevice_0;
//    extern uint8_t Number_Channels;

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
//	uint32_t a,b;
//  uint8_t chk=0;



  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  sysclock_init();

  /* Initialize all configured peripherals */
  gpio_init();
  adc_init();
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  CheckRotaries();

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

//			  a = ADC1Values[0];
//			  USBSendBuffer[9] = LOBYTE(a);
//			  USBSendBuffer[10] = HIBYTE(a);
//			  a = ADC1Values[1];
//			  USBSendBuffer[11] = LOBYTE(a);
//			  USBSendBuffer[12] = HIBYTE(a);
//			  a = ADC1Values[2];
//			  USBSendBuffer[13] = LOBYTE(a);
//			  USBSendBuffer[14] = HIBYTE(a);

//			  a = ADC1Values[3];
//			  USBSendBuffer[15] = LOBYTE(a);
//			  USBSendBuffer[16] = HIBYTE(a);
//			  a = ADC1Values[4];
//			  USBSendBuffer[17] = LOBYTE(a);
//			  USBSendBuffer[18] = HIBYTE(a);

//			  a = ADC1Values[5];
//			  b = ADC1Values[6];
//			  a = (a > b) ? a : b;
//			  USBSendBuffer[19] = LOBYTE(a);
//			  USBSendBuffer[20] = HIBYTE(a);


	  	 fill_buffer_4_axises();

		 for (uint8_t i=0;i<Number_Buttons;i++) {
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
  /* USER CODE END 3 */
}
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
  while(1)
  {
  }
//	ITM_SendChar('E');
  /* USER CODE END Error_Handler */
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
