#pragma once
#include "..\stm\Inc\tmc2590defs.h"
#include "tmc2590Converter.h"

void tmc2590Converter::getDRVCTRL_SDOFF_0bits(int regValue, int% MRES, int% DEDGE, int% INTPOL)
{
	DRVCTRL_SDOFF_0_t tmp{};
	tmp.w = regValue;
	MRES = tmp.b.MRES;
	DEDGE = tmp.b.DEDGE;
	INTPOL = tmp.b.INTPOL;
}

int tmc2590Converter::getDRVCTRL_SDOFF_0(int MRES, int DEDGE, int INTPOL)
{
	DRVCTRL_SDOFF_0_t tmp{};
	tmp.b.MRES = MRES;
	tmp.b.DEDGE = DEDGE;
	tmp.b.INTPOL = INTPOL;
	return tmp.w | (int)tmc2590regs_enum::tmc2590_DRVCTRL << 17;
}

void tmc2590Converter::getDRVCTRL_SDOFF_1bits(int regValue, int% CB, int% PHB, int% CA, int% PHA)
{
	DRVCTRL_SDOFF_1_t tmp{};
	tmp.w = regValue;
	CB = tmp.b.CB;
	PHB = tmp.b.PHB;
	CA = tmp.b.CA;
	PHA = tmp.b.PHA;
}

int tmc2590Converter::getDRVCTRL_SDOFF_1(int CB, int PHB, int CA, int PHA)
{
	DRVCTRL_SDOFF_1_t tmp{};
	tmp.b.CB = CB;
	tmp.b.PHB = PHB;
	tmp.b.CA = CA;
	tmp.b.PHA = PHA;
	return tmp.w | (int)tmc2590regs_enum::tmc2590_DRVCTRL << 17;
}

void tmc2590Converter::getCHOPCONFbits(int regValue, int% TOFF, int% HSTRT, int% HEND, int% HDEC, int% RNDTF, int% CHM, int% TBL)
{
	CHOPCONF_t tmp{};
	tmp.w = regValue;
	TOFF = tmp.b.TOFF;
	HSTRT = tmp.b.HSTRT;
	HEND = tmp.b.HEND;
	HDEC = tmp.b.HDEC;
	RNDTF = tmp.b.RNDTF;
	CHM = tmp.b.CHM;
	TBL = tmp.b.TBL;
}

int tmc2590Converter::getCHOPCONF(int TOFF, int HSTRT, int HEND, int HDEC, int RNDTF, int CHM, int TBL)
{
	CHOPCONF_t tmp{};
	tmp.b.TOFF = TOFF;
	tmp.b.HSTRT = HSTRT;
	tmp.b.HEND = HEND;
	tmp.b.HDEC = HDEC;
	tmp.b.RNDTF = RNDTF;
	tmp.b.CHM = CHM;
	tmp.b.TBL = TBL;
	return tmp.w | (int)tmc2590regs_enum::tmc2590_CHOPCONF << 17;
}

void tmc2590Converter::getSMARTENbits(int regValue, int% SEMIN, int% SEUP, int% SEMAX, int% SEDN, int% SEIMIN)
{
	SMARTEN_t tmp{};
	tmp.w = regValue;
	SEMIN = tmp.b.SEMIN;
	SEUP = tmp.b.SEUP;
	SEMAX = tmp.b.SEMAX;
	SEDN = tmp.b.SEDN;
	SEIMIN = tmp.b.SEIMIN;
}

int tmc2590Converter::getSMARTEN(int SEMIN, int SEUP, int SEMAX, int SEDN, int SEIMIN)
{
	SMARTEN_t tmp{};
	tmp.b.SEMIN = SEMIN;
	tmp.b.SEUP = SEUP;
	tmp.b.SEMAX = SEMAX;
	tmp.b.SEDN = SEDN;
	tmp.b.SEIMIN = SEIMIN;
	return tmp.w | (int)tmc2590regs_enum::tmc2590_SMARTEN << 17;
}

void tmc2590Converter::getSGCSCONFbits(int regValue, int% CS, int% SGT, int% SFILT)
{
	SGCSCONF_t tmp{};
	tmp.w = regValue;
	CS = tmp.b.CS;
	SGT = tmp.b.SGT;
	SFILT = tmp.b.SFILT;
}

int tmc2590Converter::getSGCSCONF(int CS, int SGT, int SFILT)
{
	SGCSCONF_t tmp{};
	tmp.b.CS = CS;
	tmp.b.SGT = SGT;
	tmp.b.SFILT = SFILT;
	return tmp.w | (int)tmc2590regs_enum::tmc2590_SGCSCONF << 17;
}

void tmc2590Converter::getDRVCONFbits(int regValue, int% EN_S2VS, int% EN_PFD, int% SHRTSENS, int% OTSENS, int% RDSEL, int% VSENSE, int% SDOFF, int% TS2G, int% DIS_S2G, int% SLP, int% SLPL, int% SLPH, int% TST)
{
	DRVCONF_t tmp{};
	tmp.w = regValue;
	EN_S2VS = tmp.b.EN_S2VS;
	EN_PFD = tmp.b.EN_PFD;
	SHRTSENS = tmp.b.SHRTSENS;
	OTSENS = tmp.b.OTSENS;
	RDSEL = tmp.b.RDSEL;
	VSENSE = tmp.b.VSENSE;
	SDOFF = tmp.b.SDOFF;
	TS2G = tmp.b.TS2G;
	DIS_S2G = tmp.b.DIS_S2G;
	SLP = tmp.b.SLP;
	SLPL = tmp.b.SLPL;
	SLPH = tmp.b.SLPH;
	TST = tmp.b.TST;
}

int tmc2590Converter::getDRVCONF(int EN_S2VS, int EN_PFD, int SHRTSENS, int OTSENS, int RDSEL, int VSENSE, int SDOFF, int TS2G, int DIS_S2G, int SLP, int SLPL, int SLPH, int TST)
{
	DRVCONF_t tmp{};
	tmp.b.EN_S2VS = EN_S2VS;
	tmp.b.EN_PFD = EN_PFD;
	tmp.b.SHRTSENS = SHRTSENS;
	tmp.b.OTSENS = OTSENS;
	tmp.b.RDSEL = RDSEL;
	tmp.b.VSENSE = VSENSE;
	tmp.b.SDOFF = SDOFF;
	tmp.b.TS2G = TS2G;
	tmp.b.DIS_S2G = DIS_S2G;
	tmp.b.SLP = SLP;
	tmp.b.SLPL = SLPL;
	tmp.b.SLPH = SLPH;
	tmp.b.TST = TST;
	return tmp.w | (int)tmc2590regs_enum::tmc2590_DRVCONF << 17;
}
