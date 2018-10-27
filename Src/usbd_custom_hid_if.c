/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  * 1. Redistributions of source code must retain the above copyright notice,
  * this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation
  * and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of its contributors
  * may be used to endorse or promote products derived from this software
  * without specific prior written permission.
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
#include "usbd_custom_hid_if.h"
/* USER CODE BEGIN INCLUDE */
#include "..\common_types\common_structs.h"
#include "periph_init.h"
/* USER CODE END INCLUDE */
/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_CUSTOM_HID 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_TYPES */
/* USER CODE END PRIVATE_TYPES */ 
/**
  * @}
  */ 

/** @defgroup USBD_CUSTOM_HID_Private_Defines
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */
  
/**
  * @}
  */ 

/** @defgroup USBD_CUSTOM_HID_Private_Macros
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_MACRO */
/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */ 

/** @defgroup USBD_AUDIO_IF_Private_Variables
 * @{
 */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
	    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	    0x09, 0x05,                    // USAGE (Game Pad)
	    0xa1, 0x01,                    // COLLECTION (Application)
	    0x85, 0x01,                    //   REPORT_ID (1)
	    0x05, 0x09,                    //     USAGE_PAGE (Button)
	    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	    0x75, 0x01,                    //     REPORT_SIZE (1)
	    0x95, 0x40,                    //     REPORT_COUNT (64)
	    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
	    0x29, 0x40,                    //     USAGE_MAXIMUM (Button 64)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	    0x09, 0x33,                    //     USAGE (Rx)
	    0x09, 0x34,                    //     USAGE (Ry)
	    0x09, 0x35,                    //     USAGE (Rz)
	    0x09, 0x36,                    //     USAGE (Slider1)
	    0x09, 0x36,                    //     USAGE (Slider2)
	    0x09, 0x32,                    //     USAGE (Z)
	    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x0f,              //     LOGICAL_MAXIMUM (4095)
	    0x75, 0x10,                    //     REPORT_SIZE (16)
	    0x95, 0x06,                    //     REPORT_COUNT (6)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0x09, 0x39,                    //   USAGE (Hat switch)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x07,                    //   LOGICAL_MAXIMUM (7)
	    0x35, 0x00,                    //   PHYSICAL_MINIMUM (0)
	    0x46, 0x3b, 0x01,              //   PHYSICAL_MAXIMUM (315)
	    0x65, 0x12,                    //   UNIT (SI Rot:Angular Pos)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x09, 0x39,                    //   USAGE (Hat switch)
	    0x65, 0x12,                    //   UNIT (SI Rot:Angular Pos)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x09, 0x39,                    //   USAGE (Hat switch)
	    0x65, 0x12,                    //   UNIT (SI Rot:Angular Pos)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x09, 0x39,                    //   USAGE (Hat switch)
	    0x65, 0x12,                    //   UNIT (SI Rot:Angular Pos)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x85, 0x02,                    //   REPORT_ID (2)
	    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	    0x95, 0x3F,                     //   REPORT_COUNT (63)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)
	    0x85, 0x03,                    //   REPORT_ID (3)
	    0x09, 0x02,                    //   USAGE (Vendor Usage 2)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)
	    0x85, 0x04,                    //   REPORT_ID (4)
	    0x09, 0x03,                    //   USAGE (Vendor Usage 3)
	    0x95, 0x3F,                     //   REPORT_COUNT (63)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x81, 0x82,                    //   INPUT (Data,Var,Abs,Vol)
	    0x85, 0x05,                    //   REPORT_ID (5)
	    0x09, 0x03,                    //   USAGE (Vendor Usage 3)
	    0x95, 0x3F,                     //   REPORT_COUNT (63)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x81, 0x82,                    //   INPUT (Data,Var,Abs,Vol)
	    0xc0                           // END_COLLECTION

}; 
/* USB handler declaration */
/* Handle for USB Full Speed IP */
  USBD_HandleTypeDef  *hUsbDevice_0;

/* USER CODE BEGIN PRIVATE_VARIABLES */
  extern struct pin_conf pins[USEDPINS];
  volatile extern uint8_t USB_Serial_Number_Unique[13];
  volatile extern uint8_t send_buffer[USBD_CUSTOMHID_OUTREPORT_BUF_SIZE];
  volatile extern uint8_t config_flag;
  volatile extern struct total_config_ config;
  extern volatile uint8_t USBSendBuffer[USEDPINS+1];
/* USER CODE END PRIVATE_VARIABLES */
/**
  * @}
  */ 
  
/** @defgroup USBD_CUSTOM_HID_IF_Exported_Variables
  * @{
  */ 
  extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE BEGIN EXPORTED_VARIABLES */
/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */ 
  
/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @{
  */
static int8_t CUSTOM_HID_Init_FS     (void);
static int8_t CUSTOM_HID_DeInit_FS   (void);
static int8_t CUSTOM_HID_OutEvent_FS (uint8_t event_idx, uint8_t state);
 

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS = 
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS,
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  CUSTOM_HID_Init_FS
  *         Initializes the CUSTOM HID media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  hUsbDevice_0 = &hUsbDeviceFS;
  /* USER CODE BEGIN 4 */ 
  return (0);
  /* USER CODE END 4 */ 
}

/**
  * @brief  CUSTOM_HID_DeInit_FS
  *         DeInitializes the CUSTOM HID media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */ 
  return (0);
  /* USER CODE END 5 */ 
}

/**
  * @brief  CUSTOM_HID_OutEvent_FS
  *         Manage the CUSTOM HID class events       
  * @param  event_idx: event index
  * @param  state: event state
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS  (uint8_t event_idx, uint8_t state)
{ 
  /* USER CODE BEGIN 6 */ 

	USBD_CUSTOM_HID_HandleTypeDef     *hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDevice_0->pClassData;
	uint8_t report_id=0;
	uint8_t code=0;

	report_id = hhid->Report_buf[0];
	code = hhid->Report_buf[1];

	if (report_id == 3) {
		config.packet_id1 = 4;
		config.packet_id2 = 4;
		config.packet_id3 = 4;
		config.packet_id4 = 4;
		if (code == 1) {
			config_flag = 1;
			memcpy(send_buffer, &(config.packet_id1), BUFFSIZE);
		}
		if (code == 2) {
			memcpy(send_buffer, &(config.packet_id2), BUFFSIZE);
		}
		if (code == 3) {
			memcpy(send_buffer, &(config.packet_id3), BUFFSIZE);
		}
		if (code == 4) {
			memcpy(send_buffer, &(config.packet_id4), BUFFSIZE);
		}
		if (code == 0xFF) config_flag=0;


	}

	if (report_id == 2) {
		send_buffer[0]=5;
		if (hhid->Report_buf[1] == 1){
			send_buffer[1]=1;
			config_flag = 1;
			memcpy(&(config.packet_id1), hhid->Report_buf, BUFFSIZE);
		}
		if (hhid->Report_buf[1] == 2) {
			send_buffer[1]=2;
			memcpy(&(config.packet_id2), hhid->Report_buf, BUFFSIZE);
		}
		if (hhid->Report_buf[1] == 3) {
			send_buffer[1]=3;
			memcpy(&(config.packet_id3), hhid->Report_buf, BUFFSIZE);
		}
		if (hhid->Report_buf[1] == 4) {
			send_buffer[1]=4;
			memcpy(&(config.packet_id4), hhid->Report_buf, BUFFSIZE);
			erase_flash();
			write_flash();
		}
		if (hhid->Report_buf[1] == 255) {
			config_flag = 0;

			USBSendBuffer[0] = 1;
			for (uint8_t i=1; i<USEDPINS+1; i++){
				USBSendBuffer[i]=0;
			}
			// Null point for Hat Switches
			USBSendBuffer[21] = 8;
			USBSendBuffer[22] = 8;
			USBSendBuffer[23] = 8;
			USBSendBuffer[24] = 8;
			USBD_CUSTOM_HID_SendReport(hUsbDevice_0, USBSendBuffer, USEDPINS+1);

			//periph_deinit();
			//sysclock_init();
			//gpio_init();
			gpio_ports_config();
			//HAL_Delay(100);
			//__disable_irq();
			//NVIC_SystemReset();
			//__enable_irq();
		}
	}


  return (0);
  /* USER CODE END 6 */ 
}

/* USER CODE BEGIN 7 */ 
/**
  * @brief  USBD_CUSTOM_HID_SendReport_FS
  *         Send the report to the Host       
  * @param  report: the report to be sent
  * @param  len: the report length
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
/*  
static int8_t USBD_CUSTOM_HID_SendReport_FS ( uint8_t *report,uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(hUsbDevice_0, report, len); 
}
*/
/* USER CODE END 7 */ 

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */ 

/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
