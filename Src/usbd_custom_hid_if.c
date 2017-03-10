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
	    0x29, 0x3f,                    //     USAGE_MAXIMUM (Button 63)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	    0x09, 0x33,                    //     USAGE (Rx)
	    0x09, 0x34,                    //     USAGE (Ry)
	    0x09, 0x35,                    //     USAGE (Rz)
	    0x09, /*0x30*/ 0x43,                    //     USAGE /*(X)*/ Vx
	    0x09, /*0x31*/ 0x44,                    //     USAGE /*(Y)*/ Vy
	    0x09, /*0x32*/ 0x45,                    //     USAGE /*(Z)*/ Vz
	    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x0f,              //     LOGICAL_MAXIMUM (4095)
	    0x75, 0x10,                    //     REPORT_SIZE (16)
	    0x95, 0x06,                    //     REPORT_COUNT (6)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0x85, 0x02,                    //   REPORT_ID (2)
	    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	    0x95, 0x3E, //0x20,                    //   REPORT_COUNT (32)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)
	    0x85, 0x03,                    //   REPORT_ID (3)
	    0x09, 0x02,                    //   USAGE (Vendor Usage 2)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)
	    0x85, 0x04,                    //   REPORT_ID (4)
	    0x09, 0x03,                    //   USAGE (Vendor Usage 3)
	    0x95, 0x3E, //0x20,                    //   REPORT_COUNT (32)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x81, 0x82,                    //   INPUT (Data,Var,Abs,Vol)
	    0xc0                           // END_COLLECTION

}; 
/* USB handler declaration */
/* Handle for USB Full Speed IP */
  USBD_HandleTypeDef  *hUsbDevice_0;

/* USER CODE BEGIN PRIVATE_VARIABLES */
  extern struct pin_conf pins[USEDPINS];
  extern struct axis_conf axises[AXISES];
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
	uint8_t send_buffer[63]={0};
	uint8_t index=0;

	report_id = hhid->Report_buf[0];
	code = hhid->Report_buf[1];

	if (report_id == 3) {
		if (code == 1) {
			send_buffer[0] = 4;
			for (uint8_t i=1;i<USEDPINS+1;i++){
				send_buffer[i] = pins[i-1].pin_type;
			}
			index=USEDPINS+1;
			for (uint8_t i=0;i<AXISES;i++) {
				send_buffer[index++] = axises[i].calib_min_lowbyte;
				send_buffer[index++] = axises[i].calib_min_hibyte;
				send_buffer[index++] = axises[i].calib_max_lowbyte;
				send_buffer[index++] = axises[i].calib_max_hibyte;
				send_buffer[index++] = axises[i].special;
			}

			USBD_CUSTOM_HID_SendReport(hUsbDevice_0, send_buffer, 63);
		}
	}

	if (report_id == 2) {
		for (uint8_t i=0;i<USEDPINS;i++) {
				pins[i].pin_type = hhid->Report_buf[i+1];
			}
		for (uint8_t i=0;i<AXISES;i++) {
			axises[i].calib_min_lowbyte = hhid->Report_buf[USEDPINS+1+i*5];
			axises[i].calib_min_hibyte = hhid->Report_buf[USEDPINS+2+i*5];
			axises[i].calib_max_lowbyte = hhid->Report_buf[USEDPINS+3+i*5];
			axises[i].calib_max_hibyte = hhid->Report_buf[USEDPINS+4+i*5];
			axises[i].special = hhid->Report_buf[USEDPINS+5+i*5];
		}
		erase_flash();
		write_flash();
		NVIC_SystemReset();
	//	get_config();
	//	gpio_ports_config();
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
