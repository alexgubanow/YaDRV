#include "comPort.h"
#include "usart.h"
#include <stm32f0xx_hal.h>

enum accessType { RD = 0, WR = 1 };
enum commType { tmc = 0xA5, pc = 0x13 };

typedef struct rqPacket_t
{
	unsigned int addr : 7;
	accessType access : 1;
	unsigned int val;
}rqPacket;

constexpr int MAX_RX = 64;

//rqType rq;

uint8_t rxBuff[MAX_RX] = { 0 };

rqPacket rq = { 0 };

int topOfStack = 0;
int rxIdx = 0;
int knownRQ = 0;

void comPortStart()
{
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&rxBuff[topOfStack], 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	topOfStack++;
	if (topOfStack > MAX_RX - 1)
	{
		topOfStack = 0;
	}
	HAL_UART_Receive_IT(&huart1, &rxBuff[topOfStack], 1);
	if (!knownRQ)
	{
		parseRX(topOfStack - 1);
	}
	else
	{
		if (topOfStack - rxIdx == 6)
		{
			parseRQ(rxIdx);
		}
	}
}

void parseRX(int idx)
{
	switch (rxBuff[idx])
	{
	case tmc:
		knownRQ = 1;
		rxIdx = idx;
		break;
	case pc:
		knownRQ = 1;
		rxIdx = idx;
		break;
	}
}

void parseRQ(int idx)
{
	knownRQ = 0;
	switch (rxBuff[idx])
	{
	case tmc:
		//
		talkToTMC();
		//HAL_UART_Transmit_DMA(&huart1, (uint8_t*)& rq, 1);
		break;
	case pc:
		break;
	}
	HAL_UART_Receive_IT(&huart1, (uint8_t*)& rq, 1);
}

int talkToTMC()
{

}