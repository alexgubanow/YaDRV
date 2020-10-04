#pragma once
#include "..\stm\Inc\usbReports_t.h"

public ref class tmc2590Converter
{
public:
	static void getDRVCTRL_SDOFF_0bits(int regValue, int% MRES, int% DEDGE, int% INTPOL);
	static int getDRVCTRL_SDOFF_0(int MRES, int DEDGE, int INTPOL);
	static void getDRVCTRL_SDOFF_1bits(int regValue, int% CB, int% PHB, int% CA, int% PHA);
	static int getDRVCTRL_SDOFF_1(int CB, int PHB, int CA, int PHA);
	static void getCHOPCONFbits(int regValue, int% TOFF, int% HSTRT, int% HEND, int% HDEC, int% RNDTF, int% CHM, int% TBL);
	static int getCHOPCONF(int TOFF, int HSTRT, int HEND, int HDEC, int RNDTF, int CHM, int TBL);
	static void getSMARTENbits(int regValue, int% SEMIN, int% SEUP, int% SEMAX, int% SEDN, int% SEIMIN);
	static int getSMARTEN(int SEMIN, int SEUP, int SEMAX, int SEDN, int SEIMIN);
	static void getSGCSCONFbits(int regValue, int% CS, int% SGT, int% SFILT);
	static int getSGCSCONF(int CS, int SGT, int SFILT);
	static void getDRVCONFbits(int regValue, int% EN_S2VS, int% EN_PFD, int% SHRTSENS, int% OTSENS, int% RDSEL, int% VSENSE,
		int% SDOFF, int% TS2G, int% DIS_S2G, int% SLP, int% SLPL, int% SLPH, int% TST);
	static int getDRVCONF(int EN_S2VS, int EN_PFD, int SHRTSENS, int OTSENS, int RDSEL, int VSENSE, int SDOFF,
		int TS2G, int DIS_S2G, int SLP, int SLPL, int SLPH, int TST);
};

