#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

	/* USER CODE BEGIN EFP */

	/* USER CODE END EFP */

	/* Private defines -----------------------------------------------------------*/
#define DIAG1_Pin GPIO_PIN_0
#define DIAG1_GPIO_Port GPIOA
#define DIAG1_EXTI_IRQn EXTI0_1_IRQn
#define DIAG0_Pin GPIO_PIN_1
#define DIAG0_GPIO_Port GPIOA
#define DIAG0_EXTI_IRQn EXTI0_1_IRQn
#define LEDR_Pin GPIO_PIN_2
#define LEDR_GPIO_Port GPIOA
#define LEDY_Pin GPIO_PIN_3
#define LEDY_GPIO_Port GPIOA
#define LEDG_Pin GPIO_PIN_4
#define LEDG_GPIO_Port GPIOA
#define SPI1_NSS_Pin GPIO_PIN_1
#define SPI1_NSS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif
