#include <stm32f0xx.h>
#include "nvm.h"

int writeSector(uint32_t Address, void* valuePtr, uint16_t Count);
void eraseSector(uint32_t SectorStartAddress);
void readSector(uint32_t SectorStartAddress, void* valuePtr, uint16_t Count);

uint16_t Params[9] = { 0 };

#define enable_interrupts() asm(" cpsie i ")
#define disable_interrupts() asm(" cpsid i ")

void loadParams(int writeDefault)
{
    disable_interrupts();
    uint32_t lastSector = 0x8000000 + ((*((uint16_t*)(0x1FFFF7CC)) * 4) - 4) * 256;
    readSector(lastSector, Params, sizeof(Params));
    enable_interrupts();
    if (Params[validParams] != 13 && writeDefault)
    {
        loadDefaultParams();
    }
}

void saveParams()
{
    disable_interrupts();
    //RM0360 says Flash size data register Base address: 0x1FFF F7CC
    uint32_t lastSector = 0x8000000 + ((*((uint16_t*)(0x1FFFF7CC)) * 4) - 4) * 256;
    eraseSector(lastSector);
    writeSector(lastSector, Params, sizeof(Params));
    enable_interrupts();
}

void loadDefaultParams()
{
    Params[tmc2590_CHOPCONF] = (uint16_t)0x94557;
    Params[validParams] = 13;
    Params[tmc2590_SGCSCONF] = (uint16_t)0xD0006;
    Params[tmc2590_DRVCONF] = (uint16_t)0xEF013;
    Params[tmc2590_DRVCTRL] = (uint16_t)0x183;
    Params[tmc2590_SMARTEN] = (uint16_t)0xA0222;
    saveParams();
}

int  writeSector(uint32_t Address,void * values, uint16_t size)
{              
    uint16_t *AddressPtr;
    uint16_t *valuePtr;
    AddressPtr = (uint16_t *)Address;
    valuePtr=(uint16_t *)values;
    size = size / 2;  // incoming value is expressed in bytes, not 16 bit words
    while(size) {        
        // unlock the flash 
        // Key 1 : 0x45670123
        // Key 2 : 0xCDEF89AB
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
        FLASH->CR &= ~(1 << 1); // ensure PER is low
        FLASH->CR |= (1 << 0);  // set the PG bit        
        *(AddressPtr) = *(valuePtr);
        while(FLASH->SR & (1 << 0)); // wait while busy
        if (FLASH->SR & (1 << 2))
            return -1; // flash not erased to begin with
        if (FLASH->SR & (1 << 4))
            return -2; // write protect error
        AddressPtr++;
        valuePtr++;
        size--;
    }    
    return 0;    
}
void eraseSector(uint32_t SectorStartAddress)
{
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
    FLASH->CR &= ~(1 << 0);  // Ensure PG bit is low
    FLASH->CR |= (1 << 1); // set the PER bit
    FLASH->AR = SectorStartAddress;
    FLASH->CR |= (1 << 6); // set the start bit 
    while(FLASH->SR & (1 << 0)); // wait while busy
}
void readSector(uint32_t SectorStartAddress, void * values, uint16_t size)
{
    uint16_t *AddressPtr;
    uint16_t *valuePtr;
    AddressPtr = (uint16_t *)SectorStartAddress;
    valuePtr=(uint16_t *)values;
    size = size/2; // incoming value is expressed in bytes, not 16 bit words
    while(size)
    {
        *((uint16_t *)valuePtr)=*((uint16_t *)AddressPtr);
        valuePtr++;
        AddressPtr++;
        size--;
    }
}
