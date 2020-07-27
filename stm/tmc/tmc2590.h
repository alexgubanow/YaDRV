#pragma once

#include <tmc\tmc2590defs.h>

extern DRVCTRL_SDOFF_0_t DRVCTRL_r;
extern CHOPCONF_t CHOPCONF_r;
extern SMARTEN_t SMARTEN_r;
extern SGCSCONF_t SGCSCONF_r;
extern DRVCONF_t DRVCONF_r;

void TMC2590_writeConfig(void);
void TMC2590_writeReg(tmc2590 reg);
void TMC2590_SPI_write(tmc2590 addr, int val);
extern void sendSPI(unsigned int val);