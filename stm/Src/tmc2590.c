#include "tmc2590.h"
#include "spi.h"

DRVCTRL_SDOFF_0_t DRVCTRL_r;
CHOPCONF_t CHOPCONF_r;
SMARTEN_t SMARTEN_r;
SGCSCONF_t SGCSCONF_r;
DRVCONF_t DRVCONF_r;
unsigned int motorVel;

void TMC2590_dispatcRXbuff(unsigned int val);

void TMC2590_writeReg(tmc2590 addr, unsigned int val)
{
	tmc2590_txBuff_t txData;
	txData.b.addr = addr;
	txData.b.data = val;
	TMC2590_SPI_write(txData.w);
}
void TMC2590_SPI_write(unsigned int val)
{
	unsigned int dataToSend = __RBIT(val & 0xFFFFF);
	LL_SPI_Enable(SPI1);
	while (!LL_SPI_IsActiveFlag_TXE(SPI1) && !LL_SPI_IsActiveFlag_RXNE(SPI1)) {}
	LL_GPIO_ResetOutputPin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin);
	LL_SPI_TransmitData16(SPI1, dataToSend >> 12);
	LL_SPI_TransmitData16(SPI1, dataToSend >> 22);
	unsigned int rx1 = LL_SPI_ReceiveData16(SPI1);
	unsigned int rx2 = LL_SPI_ReceiveData16(SPI1);
	while (LL_SPI_IsActiveFlag_BSY(SPI1)) {}
	LL_GPIO_SetOutputPin(SPI1_CSN_GPIO_Port, SPI1_CSN_Pin);
	LL_SPI_Disable(SPI1);
	TMC2590_dispatcRXbuff((__RBIT(rx1) >> 22) << 10 | __RBIT(rx2) >> 22);
}

int counter = 0;
void TMC2590_dispatcRXbuff(unsigned int val)
{
	tmc2590_rxBuff_t rxBuff;
	rxBuff.w = val;
	if (rxBuff.b.SG)
	{
		/*LL_TIM_SetAutoReload(TIM14, 0);
		LL_TIM_OC_SetCompareCH1(TIM14, 0);*/
	}
}
