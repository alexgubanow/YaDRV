#include "comPort.h"
#include "usart.h"
#include <stm32f0xx_hal.h>
#include <string.h>
#include "tmc2160.h"

extern SPI_STATUS tmc2160status;

enum accessType { RD = 0, WR = 1 };

typedef struct DRV_STAT_t
{
	unsigned int reset_flag : 1;
	unsigned int driver_error : 1;
	unsigned int sg2 : 1;
	unsigned int standstill : 1;
	unsigned int errorDrvCode : 4;
}DRV_STAT;

typedef struct rqPacket_t
{
	unsigned int addr : 7;
	accessType access : 1;
	int val;
}rqPacket;

typedef struct answerPacket_t
{
	SPI_STATUS status;
	int val;
}answerPacket;

uint8_t rxBuff[5] = { 0 };
rqPacket rq = { 0 };
int gotRQ = 0;
DRV_STAT drvStatus = { 0 };
answerPacket txBuff = { 0 };

void comPortStart()
{
	HAL_UART_Receive_IT(&huart1, rxBuff, 5);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	memcpy((uint8_t*)& rq, rxBuff, 5);
	HAL_UART_Receive_IT(&huart1, rxBuff, 5);
	gotRQ = 1;
}

void parseComPortRQ()
{
	int val = 0;
	if (rq.addr < 0x73)
	{
		if (rq.access == RD)
		{
			val = tmc2160_SPI_read(rq.addr);
		}
		else
		{
			val = tmc2160_SPI_write(rq.addr, rq.val);
		}
	}
	txBuff.status = tmc2160status;
	txBuff.val = val;
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*)& txBuff, 5);
	gotRQ = 0;
}
