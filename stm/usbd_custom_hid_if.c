/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include <tmc\tmc2590.h>
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

	  /* USER CODE END PRIVATE_TYPES */

	  /**
		* @}
		*/

		/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
		  * @brief Private defines.
		  * @{
		  */

		  /* USER CODE BEGIN PRIVATE_DEFINES */
#define HID_FEATURE_REPORT_BYTES     1				/* size of report in Bytes */
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
		HID_ReportID(IOctl),
		HID_Usage(HID_USAGE_GENERIC_UNDEFINED),
		HID_Feature(HID_Data | HID_Variable | HID_Absolute),

		HID_ReportCount(USBD_CUSTOMHID_OUTREPORT_BUF_SIZE),
		HID_ReportID(tmcRegisterCtl),
		HID_Usage(HID_USAGE_GENERIC_UNDEFINED),
		HID_Feature(HID_Data | HID_Variable | HID_Absolute),
	HID_EndCollection
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

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
static int8_t CUSTOM_HID_InEvent_FS(uint8_t event_idx, uint8_t* buffer, uint16_t* length);  /* An extra interface func. */
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t* report, uint16_t len);
static void setIO_Handler(uint8_t setIOcomm);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS,
  CUSTOM_HID_InEvent_FS
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
		setIO_Handler(hhid->Report_buf[1]);
		break;
	case  IOctl:
		setIO_Handler(hhid->Report_buf[1]);
		break;
	}
	return (USBD_OK);
	/* USER CODE END 6 */
}
static int8_t CUSTOM_HID_InEvent_FS(uint8_t event_idx, uint8_t* buffer, uint16_t* length)
{
	memset(buffer, 0x00, *length);
	switch ((usbReports)event_idx)
	{
	case tmcRegisterCtl:
	{
		buffer[0] = 1;
		buffer[1] = 2;
		buffer[2] = 3;
	}
	break;
	case  getVer:
	{
		buffer[0] = firmwareVersion;
		buffer[1] = 0;
		buffer[2] = 0;
	}
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
void setIO_Handler(uint8_t setIOcomm)
{
	switch (setIOcomm)
	{
	case 0b00:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		break;
	case 0b01:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		break;
	case 0b10:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		break;
	case 0b11:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		break;
	}
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */

static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t* report, uint16_t len)
{
	return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}

/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

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

