#pragma once

#include "tmc2590defs.h"

class TMC2590
{
public:
	TMC2590();
	~TMC2590();
	void writeReg(tmc2590 reg);
private:
	DRVCTRL_t DRVCTRL_r;
	CHOPCONF_t CHOPCONF_r;
	SMARTEN_t SMARTEN_r;
	SGCSCONF_t SGCSCONF_r;
	DRVCONF_t DRVCONF_r;
	int* regs[tmc2590::regsLength] = { (int*)&DRVCTRL_r, (int*)&CHOPCONF_r, (int*)&SMARTEN_r, (int*)&SGCSCONF_r, (int*)&DRVCONF_r };
	int addrs[tmc2590::regsLength] = { tmc2590::DRVCTRL, tmc2590::CHOPCONF, tmc2590::SMARTEN, tmc2590::SGCSCONF, tmc2590::DRVCONF };
	void writeConfig();
	void SPI_write(unsigned char addr, int val);
	void dispatcRXbuff(tmc2590_rxBuff_t rxBuff);
};
