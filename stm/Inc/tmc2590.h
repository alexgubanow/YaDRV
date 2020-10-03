#pragma once

#include "tmc2590defs.h"

//extern DRVCTRL_SDOFF_0_t DRVCTRL_r;
//extern CHOPCONF_t CHOPCONF_r;
//extern SMARTEN_t SMARTEN_r;
//extern SGCSCONF_t SGCSCONF_r;
//extern DRVCONF_t DRVCONF_r;

extern unsigned int TMC2590readResponse;
extern unsigned int motorVel;

void TMC2590_WriteConfig();
void TMC2590_writeReg(tmc2590regs_enum reg, unsigned int val);