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
	    0x95, 0x3F, //0x20,                    //   REPORT_COUNT (32)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)
//	    0x85, 0x06,                    //   REPORT_ID (6)
//	    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
//	    0x95, 0x3F, //0x20,                    //   REPORT_COUNT (32)
//	    0x75, 0x08,                    //   REPORT_SIZE (8)
//	    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)
	    0x85, 0x03,                    //   REPORT_ID (3)
	    0x09, 0x02,                    //   USAGE (Vendor Usage 2)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)
	    0x85, 0x04,                    //   REPORT_ID (4)
	    0x09, 0x03,                    //   USAGE (Vendor Usage 3)
	    0x95, 0x3F, //0x20,                    //   REPORT_COUNT (32)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x81, 0x82,                    //   INPUT (Data,Var,Abs,Vol)
//	    0x85, 0x05,                    // 	REPORT_ID (5)
//	    0x09, 0x03,                    // 	USAGE (Vendor Usage 3)
//	    0x95, 0x3F, //0x20,                    // 	REPORT_COUNT (32)
//	    0x75, 0x08,                    // 	REPORT_SIZE (8)
//	    0x81, 0x82,                    // 	INPUT (Data,Var,Abs,Vol)
	    0xc0                           // END_COLLECTION

}; 
/* USB handler declaration */
/* Handle for USB Full Speed IP */
  USBD_HandleTypeDef  *hUsbDevice_0;

/* USER CODE BEGIN PRIVATE_VARIABLES */
  extern struct pin_conf pins[USEDPINS];
  extern struct axis_conf axises[AXISES];
  extern uint8_t POV_config;
  volatile extern uint16_t Rot_Press_Time;
  volatile extern uint16_t Rot_Debounce_Time;
  volatile extern uint16_t Button_Debounce_Time;
  volatile extern uint16_t Button_Press_time;
  volatile extern uint16_t RotSwitch_Press_Time;
  volatile extern uint8_t USB_Product_String_Unique[10];
  volatile extern uint8_t USB_Serial_Number_Unique[13];
  volatile extern uint8_t USB_polling_interval;
  volatile extern struct rot_conf Single_rotaries[USEDPINS];
  extern uint8_t Number_Single_Rotaries;
  volatile extern uint8_t AxisComb_Percent;
  volatile extern uint8_t AxisComb_pin1;
  volatile extern uint8_t AxisComb_pin2;
  volatile extern uint8_t AxisCombEnabled;
  volatile extern uint16_t AxisCombPin1Min;
  volatile extern uint16_t AxisCombPin1Max;
  volatile extern uint16_t AxisCombPin2Min;
  volatile extern uint16_t AxisCombPin2Max;
  volatile extern uint8_t AxisCombPin1AC;
  volatile extern uint8_t AxisCombPin2AC;
  volatile extern uint8_t AxisCombCoop;
  volatile extern uint8_t AxisCombSep;
  volatile extern uint16_t Analog2ButtonThreshold;

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
	uint8_t send_buffer[USBD_CUSTOMHID_OUTREPORT_BUF_SIZE]={0};
//	uint8_t answer[USBD_CUSTOMHID_OUTREPORT_BUF_SIZE]={0};
	uint8_t index=0;
static	uint8_t packet1=0, packet2=0, packet3=0;

	report_id = hhid->Report_buf[0];
	code = hhid->Report_buf[1];

	if (report_id == 3) {
		if (code == 1) {
			send_buffer[0] = 4;
			send_buffer[1] = 1;
			for (uint8_t i=1;i<USEDPINS+1;i++){
				send_buffer[i+1] = pins[i-1].pin_type;
			}
			index=USEDPINS+2;
			for (uint8_t i=0;i<AXISES;i++) {
				send_buffer[index++] = axises[i].calib_min_lowbyte;
				send_buffer[index++] = axises[i].calib_min_hibyte;
				send_buffer[index++] = axises[i].calib_max_lowbyte;
				send_buffer[index++] = axises[i].calib_max_hibyte;
				send_buffer[index++] = axises[i].special;
			}
			USBD_CUSTOM_HID_SendReport(hUsbDevice_0, send_buffer, USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
		}
		if (code == 2) {
			send_buffer[0] = 4;
			send_buffer[1] = 2;
			send_buffer[2]=LOBYTE(Rot_Press_Time);
			send_buffer[3]=HIBYTE(Rot_Press_Time);
			send_buffer[4]=LOBYTE(Rot_Debounce_Time);
			send_buffer[5]=HIBYTE(Rot_Debounce_Time);
			send_buffer[6]=LOBYTE(Button_Debounce_Time);
			send_buffer[7]=HIBYTE(Button_Debounce_Time);
			send_buffer[8]=USB_polling_interval;
			send_buffer[9]=LOBYTE(RotSwitch_Press_Time);
			send_buffer[10]=HIBYTE(RotSwitch_Press_Time);

			for (uint8_t i=0; i<10; i++) {
				send_buffer[11+i]=USB_Product_String_Unique[i];
			}
			send_buffer[21]=AxisCombEnabled;
			send_buffer[22]=LOBYTE(AxisCombPin1Min);
			send_buffer[23]=HIBYTE(AxisCombPin1Min);
			send_buffer[24]=LOBYTE(AxisCombPin1Max);
			send_buffer[25]=HIBYTE(AxisCombPin1Max);
			send_buffer[26]=LOBYTE(AxisCombPin2Min);
			send_buffer[27]=HIBYTE(AxisCombPin2Min);
			send_buffer[28]=LOBYTE(AxisCombPin2Max);
			send_buffer[29]=HIBYTE(AxisCombPin2Max);
			send_buffer[30]=0;
			if (AxisCombSep) send_buffer[30]|=0x8;
			if (AxisCombCoop) send_buffer[30]|=0x4;
			if (AxisCombPin2AC) send_buffer[30]|=0x2;
			if (AxisCombPin1AC) send_buffer[30]|=0x1;

			send_buffer[31]=Number_Single_Rotaries;
			for (uint8_t i=0; i<14; i++) {
				send_buffer[32+(i*2)]=Single_rotaries[i].PINA;
				send_buffer[33+(i*2)]=Single_rotaries[i].PINB;
			}
			send_buffer[60] = POV_config;
			send_buffer[61] = AxisComb_Percent;
			send_buffer[62] = AxisComb_pin1;
			send_buffer[63] = AxisComb_pin2;
			USBD_CUSTOM_HID_SendReport(hUsbDevice_0, send_buffer, USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);

			for (uint8_t i=0;i<USBD_CUSTOMHID_OUTREPORT_BUF_SIZE;i++) {
				send_buffer[i]=0;
			}
		}
		if (code == 3) {
			send_buffer[0] = 4;
			send_buffer[1] = 3;
			send_buffer[2] = LOBYTE(Analog2ButtonThreshold);
			send_buffer[3] = HIBYTE(Analog2ButtonThreshold);
			USBD_CUSTOM_HID_SendReport(hUsbDevice_0, send_buffer, USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
		}


	}

	if (report_id == 2) {
		send_buffer[0]=4;
		send_buffer[1]=255; //OK code
		if (hhid->Report_buf[1] == 1){
			packet1++;
			for (uint8_t i=0;i<USEDPINS;i++) {
				pins[i].pin_type = hhid->Report_buf[i+2];
			}
			for (uint8_t i=0;i<AXISES;i++) {
				axises[i].calib_min_lowbyte = hhid->Report_buf[USEDPINS+2+i*5];
				axises[i].calib_min_hibyte = hhid->Report_buf[USEDPINS+3+i*5];
				axises[i].calib_max_lowbyte = hhid->Report_buf[USEDPINS+4+i*5];
				axises[i].calib_max_hibyte = hhid->Report_buf[USEDPINS+5+i*5];
				axises[i].special = hhid->Report_buf[USEDPINS+6+i*5];
			}
		//	USBD_CUSTOM_HID_SendReport(hUsbDevice_0, send_buffer, USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
		//	POV_config = hhid->Report_buf[63];
		}
		if (hhid->Report_buf[1] == 2) {
			packet2++;
			Rot_Press_Time=(hhid->Report_buf[3]<<8)+hhid->Report_buf[2];
			Rot_Debounce_Time=(hhid->Report_buf[5]<<8)+hhid->Report_buf[4] ;
			Button_Debounce_Time=(hhid->Report_buf[7]<<8)+hhid->Report_buf[6];
//			Button_Press_time=(hhid->Report_buf[8]<<8)+hhid->Report_buf[7];
			USB_polling_interval=hhid->Report_buf[8];
			RotSwitch_Press_Time=(hhid->Report_buf[10]<<8)+hhid->Report_buf[9];

			for (uint8_t i=0; i<10; i++) {
				USB_Product_String_Unique[i]=hhid->Report_buf[11+i];
			}


		        AxisCombEnabled=hhid->Report_buf[21];
		        AxisCombPin1Min=(hhid->Report_buf[23]<<8)+hhid->Report_buf[22];
		        AxisCombPin1Max=(hhid->Report_buf[25]<<8)+hhid->Report_buf[24];
		        AxisCombPin2Min=(hhid->Report_buf[27]<<8)+hhid->Report_buf[26];
		        AxisCombPin2Max=(hhid->Report_buf[29]<<8)+hhid->Report_buf[28];
		        AxisCombPin1AC=hhid->Report_buf[30]&0b0001;
		        AxisCombPin2AC=(hhid->Report_buf[30]&0b0010)>>1;
		        AxisCombCoop=(hhid->Report_buf[30]&0b0100)>>2;
		        AxisCombSep=(hhid->Report_buf[30]&0b1000)>>3;

//			for (uint8_t i=0; i<10; i++) {
//				USB_Serial_Number_Unique[i+2]=hhid->Report_buf[21+i];
//			}

			Number_Single_Rotaries=hhid->Report_buf[31];
			for (uint8_t i=0; i<14; i++) {
				Single_rotaries[i].PINA=hhid->Report_buf[32+(i*2)];
				Single_rotaries[i].PINB=hhid->Report_buf[33+(i*2)];
			}
			POV_config = hhid->Report_buf[60];
			AxisComb_Percent = hhid->Report_buf[61];
			AxisComb_pin1 = hhid->Report_buf[62];
			AxisComb_pin2 = hhid->Report_buf[63];

		//	USBD_CUSTOM_HID_SendReport(hUsbDevice_0, send_buffer, USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
		}

		if (hhid->Report_buf[1] == 3) {
			packet3++;
			Analog2ButtonThreshold = (hhid->Report_buf[3]<<8)+hhid->Report_buf[2];
		}


		if ((packet1) && (packet2) && (packet3)) {
			packet1=0; packet2=0; packet3=0;
			erase_flash();
			write_flash();
			NVIC_SystemReset();
		}
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
