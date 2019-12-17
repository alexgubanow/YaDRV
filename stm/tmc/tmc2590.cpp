#include "tmc2590.h"
#include "spi.h"

TMC2590::TMC2590()
{
	/*DRVCTRL_r;
	CHOPCONF_r;
	SMARTEN_r;
	SGCSCONF_r;
	DRVCONF_r;*/
	writeConfig();
}

TMC2590::~TMC2590()
{
}

void TMC2590::writeConfig()
{
	for (size_t i = 0; i < tmc2590::regsLength; i++)
	{
		SPI_write(addrs[i], *regs[i]);
	}
}

void TMC2590::writeReg(tmc2590 reg)
{
	for (size_t i = 0; i < tmc2590::regsLength; i++)
	{
		if (reg == addrs[i]) { SPI_write(reg, *regs[i]); break; }
	}
}

void TMC2590::SPI_write(unsigned char addr, int val)
{
	HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDGRN_Pin, GPIO_PIN_SET);
	tmc2590_txBuff_t txBuff;
	tmc2590_rxBuff_t rxBuff;
	txBuff.addr = addr;
	txBuff.data = val;
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)&txBuff, (uint8_t*)&rxBuff, 2, 1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	dispatcRXbuff(rxBuff);
	HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_RESET);
}

void TMC2590::dispatcRXbuff(tmc2590_rxBuff_t rxBuff)
{
}
