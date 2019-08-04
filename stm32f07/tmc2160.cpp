#pragma region includes
#include "tmc2160.h"
#include "spi.h"
#pragma endregion

#pragma region regs declaration
GCONF_t GCONF_r = { 0 };
GSTAT_t GSTAT_r = { 0 };
IOIN_t IOIN_r = { 0 };
OTP_PROG_t OTP_PROG_r = { 0 };
OTP_READ_t OTP_READ_r = { 0 };
FACTORY_CONF_t FACTORY_CONF_r = { 0 };
SHORT_CONF_t SHORT_CONF_r = { 0 };
DRV_CONF_t DRV_CONF_r = { 0 };
GLOBAL_SCALER_t GLOBAL_SCALER_r = { 0 };
OFFSET_READ_t OFFSET_READ_r = { 0 };
IHOLD_IRUN_t IHOLD_IRUN_r = { 0 };
TPOWERDOWN_t TPOWERDOWN_r = { 0 };
TSTEP_t TSTEP_r = { 0 };
TPWMTHRS_t TPWMTHRS_r = { 0 };
TCOOLTHRS_t TCOOLTHRS_r = { 0 };
THIGH_t THIGH_r = { 0 };
XDIRECT_t XDIRECT_r = { 0 };
VDCMIN_t VDCMIN_r = { 0 };
MSLUT_t MSLUT_r = { 0 };
MSLUTSEL_t MSLUTSEL_r = { 0 };
MSLUTSTART_t MSLUTSTART_r = { 0 };
MSCNT_t MSCNT_r = { 0 };
MSCURACT_t MSCURACT_r = { 0 };
CHOPCONF_t CHOPCONF_r = { 0 };
COOLCONF_t COOLCONF_r = { 0 };
DCCTRL_t DCCTRL_r = { 0 };
DRV_STATUS_t DRV_STATUS_r = { 0 };
PWMCONF_t PWMCONF_r = { 0 };
PWM_SCALE_t PWM_SCALE_r = { 0 };
PWM_AUTO_t PWM_AUTO_r = { 0 };
LOST_STEPS_t LOST_STEPS_r = { 0 };
#pragma endregion

int* tmc2160regs[31] = { (int*)& GCONF_r, (int*)& GSTAT_r, (int*)& IOIN_r, (int*)& OTP_PROG_r, (int*)& OTP_READ_r, (int*)& FACTORY_CONF_r,
(int*)& SHORT_CONF_r, (int*)& DRV_CONF_r, (int*)& GLOBAL_SCALER_r, (int*)& OFFSET_READ_r, (int*)& IHOLD_IRUN_r, (int*)& TPOWERDOWN_r,
(int*)& TSTEP_r, (int*)& TPWMTHRS_r, (int*)& TCOOLTHRS_r, (int*)& THIGH_r, (int*)& XDIRECT_r, (int*)& VDCMIN_r, (int*)& MSLUT_r, (int*)& MSLUTSEL_r,
(int*)& MSLUTSTART_r, (int*)& MSCNT_r, (int*)& MSCURACT_r, (int*)& CHOPCONF_r, (int*)& COOLCONF_r, (int*)& DCCTRL_r, (int*)& DRV_STATUS_r,
(int*)& PWMCONF_r, (int*)& PWM_SCALE_r, (int*)& PWM_AUTO_r, (int*)& LOST_STEPS_r };

int tmc2160addr[31] = { tmc2160::GCONF, tmc2160::GSTAT, tmc2160::IOIN, tmc2160::OTP_PROG, tmc2160::OTP_READ, tmc2160::FACTORY_CONF,
tmc2160::SHORT_CONF, tmc2160::DRV_CONF, tmc2160::GLOBAL_SCALER, tmc2160::OFFSET_READ, tmc2160::IHOLD_IRUN, tmc2160::TPOWERDOWN,
tmc2160::TSTEP, tmc2160::TPWMTHRS, tmc2160::TCOOLTHRS, tmc2160::THIGH, tmc2160::XDIRECT, tmc2160::VDCMIN, tmc2160::MSLUT, tmc2160::MSLUTSEL,
tmc2160::MSLUTSTART, tmc2160::MSCNT, tmc2160::MSCURACT, tmc2160::CHOPCONF, tmc2160::COOLCONF, tmc2160::DCCTRL, tmc2160::DRV_STATUS,
tmc2160::PWMCONF, tmc2160::PWM_SCALE, tmc2160::PWM_AUTO, tmc2160::LOST_STEPS };

enum accessType { RD = 0, WR = 1 };

typedef struct txPacket_t
{
	unsigned int addr : 7;
	accessType access : 1;
	int val;
}txPacket;

SPI_STATUS tmc2160status;

void tmc_2160_ReadRegMap();
void tmc2160_WriteReg(tmc2160 reg);

void tmc2160_init(void)
{
	//has to be 0x30000040 or 0x30000050
	int tmp = tmc2160_SPI_read(IOIN);
	IOIN_r = *(IOIN_t*)& tmp;
	while (IOIN_r.hasTObeONE != 1 && IOIN_r.VERSION < 0x30 )
	{
		HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_SET);
		tmp = tmc2160_SPI_read(IOIN);
		IOIN_r = *(IOIN_t*)& tmp;
	}
	HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_RESET);
	tmc_2160_ReadRegMap();
	CHOPCONF_r.toff = 3;
	CHOPCONF_r.HSTRT_TFD = 4;
	CHOPCONF_r.HEND_OFFSET = 1;
	CHOPCONF_r.tbl = 2;
	CHOPCONF_r.chm = 0;
	//CHOPCONF_r.MRES = 4;
	tmc2160_WriteReg(CHOPCONF);
	IHOLD_IRUN_r.IHOLD = 10;
	IHOLD_IRUN_r.IRUN = 31;
	IHOLD_IRUN_r.IHOLDDELAY = 6;
	tmc2160_WriteReg(IHOLD_IRUN);
	TPOWERDOWN_r.value = 10;
	tmc2160_WriteReg(TPOWERDOWN);
	GCONF_r.en_pwm_mode = 1;
	tmc2160_WriteReg(GCONF);
	TPWMTHRS_r.value = 200;
	tmc2160_WriteReg(TPWMTHRS);
	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_SET);
}

void tmc2160_WriteReg(tmc2160 reg)
{
	for (size_t i = 0; i < 31; i++)
	{
		if (reg == tmc2160addr[i]) { tmc2160_SPI_write(reg, *tmc2160regs[i]); break; }
	}
}
void tmc_2160_ReadRegMap()
{
	for (size_t i = 0; i < 31; i++)
	{
		*tmc2160regs[i] = tmc2160_SPI_read(tmc2160addr[i]);
	}
}

int tmc2160_SPI_read(unsigned int addr)
{
	HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_SET);
	txPacket txBuff = { RD };
	uint8_t rxBuff[5] = { 0 };
	txBuff.access = RD;
	txBuff.addr = addr;
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)& txBuff, 5, 1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Receive(&hspi1, (uint8_t*)& rxBuff, 5, 1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	tmc2160status = *(SPI_STATUS_t*)& rxBuff[0];
	HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_RESET);
	return __REV(rxBuff[1] | (rxBuff[2] << 8) | (rxBuff[3] << 16) | (rxBuff[4] << 24));
}

int tmc2160_SPI_write(unsigned int addr, int val)
{
	HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_SET);
	txPacket txBuff = { RD };
	uint8_t rxBuff[5] = { 0 };
	txBuff.access = WR;
	txBuff.addr = addr;
	txBuff.val = val;
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)& txBuff, 5, 1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Receive(&hspi1, (uint8_t*)& rxBuff, 5, 1);
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
	tmc2160status = *(SPI_STATUS_t*)& rxBuff[0];
	HAL_GPIO_WritePin(LEDY_GPIO_Port, LEDY_Pin, GPIO_PIN_RESET);
	return __REV(rxBuff[1] | (rxBuff[2] << 8) | (rxBuff[3] << 16) | (rxBuff[4] << 24));
}