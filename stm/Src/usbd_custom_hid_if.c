/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */
#include "tmc2590.h"
#include "tim.h"
#include "main.h"
#include "hid_macros.h"
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */
typedef enum usbReports_t
{
	getVer = 1,
	IOctl,
	tmcRegisterCtl,
	velocity,
	ReportMCUtemp
}usbReports;
/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
void setIO_Handler(uint8_t setIOcomm);
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
  HID_UsagePage(HID_USAGE_PAGE_GENERIC),
	HID_Usage(HID_USAGE_GENERIC_UNDEFINED),
	HID_Collection(HID_Application),
		HID_LogicalMin(0),
		HID_LogicalMax(0xFF),

		HID_ReportSize(8),	// 8 bits

		HID_ReportCount(USBD_CUSTOMHID_OUTREPORT_BUF_SIZE),
		HID_ReportID(getVer),
		HID_Usage(HID_USAGE_GENERIC_UNDEFINED),
		HID_Input(HID_Data | HID_Variable | HID_Absolute),

		HID_ReportCount(USBD_CUSTOMHID_OUTREPORT_BUF_SIZE),
		HID_ReportID(velocity),
		HID_Usage(HID_USAGE_GENERIC_UNDEFINED),
		HID_Output(HID_Data | HID_Variable | HID_Absolute),

		HID_ReportCount(USBD_CUSTOMHID_OUTREPORT_BUF_SIZE),
		HID_ReportID(IOctl),
		HID_Usage(HID_USAGE_GENERIC_UNDEFINED),
		HID_Feature(HID_Data | HID_Variable | HID_Absolute),
		//ReportMCUtemp
		HID_ReportCount(USBD_CUSTOMHID_OUTREPORT_BUF_SIZE),
		HID_ReportID(ReportMCUtemp),
		HID_Usage(HID_USAGE_GENERIC_UNDEFINED),
		HID_Feature(HID_Data | HID_Variable | HID_Absolute),

		HID_ReportCount(USBD_CUSTOMHID_OUTREPORT_BUF_SIZE),
		HID_ReportID(tmcRegisterCtl),
		HID_Usage(HID_USAGE_GENERIC_UNDEFINED),
		HID_Feature(HID_Data | HID_Variable | HID_Absolute),
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */
#define myUSBcustom 1
static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);
static int8_t CUSTOM_HID_InEvent_FS(uint8_t event_idx, uint8_t* buffer, uint16_t* length);

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS,
  CUSTOM_HID_InEvent_FS
};
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
	/* USER CODE BEGIN 4 */
	return (USBD_OK);
	/* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
	/* USER CODE BEGIN 5 */
	return (USBD_OK);
	/* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
	/* USER CODE BEGIN 6 */
	USBD_CUSTOM_HID_HandleTypeDef* hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;
	switch ((usbReports)event_idx)
	{
	case  tmcRegisterCtl:
		TMC2590_writeReg(tmc2590_SGCSCONF, hhid->Report_buf[1]);
		break;
	case  IOctl:
		setIO_Handler(hhid->Report_buf[1]);
		break;
	case  velocity:
		motorVel = hhid->Report_buf[1] << 8 | hhid->Report_buf[2];
		if (motorVel == 0)
		{
			LL_TIM_CC_DisableChannel(TIM14, 1);
		}
		else
		{
			LL_TIM_SetAutoReload(TIM14, motorVel);
			LL_TIM_OC_SetCompareCH1(TIM14, motorVel / 2);
			if (!LL_TIM_IsEnabledCounter(TIM14))
			{
				LL_TIM_EnableCounter(TIM14);
			}
			if (!LL_TIM_CC_IsEnabledChannel(TIM14, 1))
			{
				LL_TIM_CC_EnableChannel(TIM14, 1);
			}
		}
		break;
	}
	return (USBD_OK);
	/* USER CODE END 6 */
}
#ifndef myUSBcustom


/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
	return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
	return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
	USBD_CUSTOM_HID_HandleTypeDef* hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;
	switch ((usbReports)event_idx)
	{
	case  tmcRegisterCtl:
		TMC2590_writeReg(tmc2590_SGCSCONF, hhid->Report_buf[1]);
		break;
	case  IOctl:
		setIO_Handler(hhid->Report_buf[1]);
		break;
	case  velocity:
		motorVel = hhid->Report_buf[1] << 8 | hhid->Report_buf[2];
		if (motorVel == 0)
		{
			LL_TIM_CC_DisableChannel(TIM14, 1);
		}
		else
		{
			LL_TIM_SetAutoReload(TIM14, motorVel);
			LL_TIM_OC_SetCompareCH1(TIM14, motorVel / 2);
			if (!LL_TIM_IsEnabledCounter(TIM14))
			{
				LL_TIM_EnableCounter(TIM14);
			}
			if (!LL_TIM_CC_IsEnabledChannel(TIM14, 1))
			{
				LL_TIM_CC_EnableChannel(TIM14, 1);
			}
		}
		break;
	}
	return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
#endif // !myUSBcustom
/**
  * @brief  Send the report to the Host
  * @param  event_idx: Event index
  * @param  buffer: The report to be sent
  * @param  length: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_InEvent_FS(uint8_t event_idx, uint8_t* buffer, uint16_t* length)
{
	memset(buffer, 0x00, *length);
	switch ((usbReports)event_idx)
	{
	case tmcRegisterCtl:
		buffer[0] = 1;
		buffer[1] = 2;
		buffer[2] = 3;
		break;
	case  getVer:
		buffer[0] = 13;
		buffer[1] = 0;
		buffer[2] = 0;
		break;
	case ReportMCUtemp:
		buffer[0] = MCUtemp;
		break;
	case IOctl:
	{
		uint8_t IOstatus = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) << 1;
		IOstatus |= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
		buffer[0] = IOstatus;
		buffer[1] = 0;
		buffer[2] = 0;
	}
	break;
	}
	return (USBD_OK);
}
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
void setIO_Handler(uint8_t setIOcomm)
{
	switch (setIOcomm)
	{
	case 0b00:
		LL_GPIO_ResetOutputPin(GPIOA, GPIO_PIN_0);
		LL_GPIO_ResetOutputPin(GPIOA, GPIO_PIN_1);
		break;
	case 0b01:
		LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_0);
		LL_GPIO_ResetOutputPin(GPIOA, GPIO_PIN_1);
		break;
	case 0b10:
		LL_GPIO_ResetOutputPin(GPIOA, GPIO_PIN_0);
		LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_1);
		break;
	case 0b11:
		LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_0);
		LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_1);
		break;
	}
}
/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

