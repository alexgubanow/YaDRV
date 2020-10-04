#include "tmc2590.h"
#include "spi.h"
#include "nvm.h"

//DRVCTRL_SDOFF_0_t DRVCTRL_r;
//CHOPCONF_t CHOPCONF_r;
//SMARTEN_t SMARTEN_r;
//SGCSCONF_t SGCSCONF_r;
//DRVCONF_t DRVCONF_r;
unsigned int motorVel;
unsigned int TMC2590readResponse;

void TMC2590_dispatcRXbuff(unsigned int val);

void TMC2590_WriteConfig()
{
	TMC2590_writeReg(tmc2590_CHOPCONF, Params.CHOPCONF_r.w);
	TMC2590_writeReg(tmc2590_SGCSCONF, Params.SGCSCONF_r.w);
	TMC2590_writeReg(tmc2590_DRVCONF, Params.DRVCONF_r.w);
	TMC2590_writeReg(tmc2590_DRVCTRL, Params.DRVCTRL_r.w);
	TMC2590_writeReg(tmc2590_SMARTEN, Params.SMARTEN_r.w);
	/*//tmc2590_CHOPCONF
	TMC2590_SPI_write(0x94557);
	SGCSCONF_r.b.CS = 0xf;
	SGCSCONF_r.b.SGT = 15;
	SGCSCONF_r.b.SFILT = 1;
	TMC2590_writeReg(tmc2590_SGCSCONF, SGCSCONF_r.w);
	//TMC2590_SPI_write(0xD0006);
	DRVCONF_r.b.SLPH = 0b11;
	DRVCONF_r.b.SLPL = 0b11;
	DRVCONF_r.b.RDSEL = 0b01;
	DRVCONF_r.b.EN_PFD = 1;
	DRVCONF_r.b.EN_S2VS = 1;
	TMC2590_writeReg(tmc2590_DRVCONF, DRVCONF_r.w);
	//TMC2590_SPI_write(0xEF013);
	DRVCTRL_r.b.INTPOL = 0;
	DRVCTRL_r.b.DEDGE = 0;
	DRVCTRL_r.b.MRES = 0b1000;
	TMC2590_writeReg(tmc2590_DRVCTRL, DRVCTRL_r.w);
	//TMC2590_SPI_write(0x183);
	SMARTEN_r.b.SEMIN = 2;
	SMARTEN_r.b.SEUP = 1;
	SMARTEN_r.b.SEMAX = 2;
	TMC2590_writeReg(tmc2590_SMARTEN, SMARTEN_r.w);
	//TMC2590_SPI_write(0xA0222);*/
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


void TMC2590_writeReg(tmc2590regs_enum addr, unsigned int val)
{
	TMC2590_SPI_write(addr << 17 | val);
}

void TMC2590_dispatcRXbuff(unsigned int val)
{
	TMC2590readResponse = val;
	//tmc2590_rxBuff_t rxBuff;
	//rxBuff.w = val;
	//if (rxBuff.b.SG)
	//{
	//	/*LL_TIM_SetAutoReload(TIM14, 0);
	//	LL_TIM_OC_SetCompareCH1(TIM14, 0);*/
	//}
}
