#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"
#include <tmc\tmc2590.h>

void delayUS(uint32_t us) {
	volatile uint32_t counter = us;
	while (counter--);
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* MCU Configuration--------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	//MX_SPI1_Init();
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PinState::GPIO_PIN_SET);
	HAL_GPIO_WritePin(DRV_EN_GPIO_Port, DRV_EN_Pin, GPIO_PinState::GPIO_PIN_SET);
	HAL_Delay(200);
	sendSPI(0x94557);
	sendSPI(0xD0006);
	sendSPI(0xEF013);
	sendSPI(0x183);
	sendSPI(0xA0222);
	//to limit current for 1.6A with 0.075R sense resistor SGCSCONF_r.CS=31 and DRVCONF_r.VSENSE=1
	/*DRVCONF_r.b.SDOFF = 0;
	DRVCONF_r.b.VSENSE = 1;
	DRVCONF_r.b.RDSEL = 0b11;
	DRVCONF_r.b.SLPH = 0b11;
	DRVCONF_r.b.SLPL = 0b11;
	DRVCONF_r.b.SLP = 0;
	DRVCONF_r.b.OTSENS = 1;
	DRVCONF_r.b.EN_S2VS = 1;
	TMC2590_writeReg(tmc2590::DRVCONF);
	SGCSCONF_r.b.CS = 31;
	TMC2590_writeReg(tmc2590::SGCSCONF);
	DRVCTRL_r.b.INTPOL = 1;
	TMC2590_writeReg(tmc2590::DRVCTRL);*/
	HAL_GPIO_WritePin(DRV_EN_GPIO_Port, DRV_EN_Pin, GPIO_PinState::GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PinState::GPIO_PIN_RESET);
	
	/*HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PinState::GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, GPIO_PIN_5, GPIO_PinState::GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, GPIO_PIN_7, GPIO_PinState::GPIO_PIN_SET);*/
	//MX_TIM14_Init();
	//MX_USB_DEVICE_Init(); 
	/* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(STEP_GPIO_Port, STEP_Pin, GPIO_PinState::GPIO_PIN_SET);
	HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PinState::GPIO_PIN_SET);
	/* USER CODE END 2 */
	//HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	//TIM14->CCR1 = 1024;
	/* Infinite loop */
	while (1)
	{/*
		DIR_GPIO_Port->BSRR = (uint32_t)DIR_Pin;
		DIR_GPIO_Port->BRR = (uint32_t)DIR_Pin;*/
		/*HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PinState::GPIO_PIN_SET);
		delayUS(10);
		HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PinState::GPIO_PIN_RESET);
		delayUS(10);*/
		//HAL_Delay(100);
		////sendSPI(0xEF013);
		//TMC2590_writeReg(tmc2590::DRVCONF);

		/*HAL_GPIO_WritePin(GRN_LED_GPIO_Port, GRN_LED_Pin, GPIO_PinState::GPIO_PIN_RESET);
		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PinState::GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GRN_LED_GPIO_Port, GRN_LED_Pin, GPIO_PinState::GPIO_PIN_SET);
		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PinState::GPIO_PIN_RESET);
		HAL_Delay(500);*/
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;

	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	   /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */