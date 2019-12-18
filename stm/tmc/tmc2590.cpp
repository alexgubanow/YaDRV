#include "tmc2590.h"
#include "spi.h"

DRVCTRL_SDOFF_0_t DRVCTRL_r;
CHOPCONF_t CHOPCONF_r;
SMARTEN_t SMARTEN_r;
SGCSCONF_t SGCSCONF_r;
DRVCONF_t DRVCONF_r;

int* regs[tmc2590::regsLength] = { (int*)&DRVCTRL_r, (int*)&CHOPCONF_r, (int*)&SMARTEN_r, (int*)&SGCSCONF_r, (int*)&DRVCONF_r };
int addrs[tmc2590::regsLength] = { tmc2590::DRVCTRL, tmc2590::CHOPCONF, tmc2590::SMARTEN, tmc2590::SGCSCONF, tmc2590::DRVCONF };

void TMC2590_SPI_write(tmc2590 addr, int val);
void TMC2590_dispatcRXbuff(tmc2590_rxBuff_t rxBuff);

void TMC2590_writeConfig()
{
	for (size_t i = 0; i < tmc2590::regsLength; i++)
	{
		TMC2590_SPI_write((tmc2590)addrs[i], *regs[i]);
	}
}

void TMC2590_writeReg(tmc2590 addr)
{
	for (size_t i = 0; i < tmc2590::regsLength; i++)
	{
		if ((int)addr == addrs[i])
		{
			TMC2590_SPI_write(addr, *regs[i]);
			break;
		}
	}
}

void TMC2590_SPI_write(tmc2590 addr, int val)
{
	HAL_GPIO_WritePin(GRN_LED_GPIO_Port, GRN_LED_Pin, GPIO_PIN_SET);
	tmc2590_txBuff_t txData;
	tmc2590_rxBuff_t rxData;
	txData.b.addr = addr;
	txData.b.data = val;

	spiBuff txBuff;
	txBuff.w1 = txData.w >> 12;
	txBuff.w2 = txData.w & 0x3FF;

	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PinState::GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&txBuff, (uint8_t*)&rxData, 2, 1);
	HAL_GPIO_WritePin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin, GPIO_PinState::GPIO_PIN_SET);
	TMC2590_dispatcRXbuff(rxData);
	HAL_GPIO_WritePin(GRN_LED_GPIO_Port, GRN_LED_Pin, GPIO_PIN_RESET);
}

void TMC2590_dispatcRXbuff(tmc2590_rxBuff_t rxBuff)
{
}
