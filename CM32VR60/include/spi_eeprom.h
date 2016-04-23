#ifndef __SPI_EEPROM_H
#define __SPI_EEPROM_H

#include "stm32f1xx_hal.h"

/*Change this*/
#define MEM_SIZE 0x8000
#define PAGE_SIZE 0x0040

enum eepromCMD 
{ 
	cmdREAD = 0x03, 
	cmdWRITE = 0x02,
	cmdWREN = 0x06, 
	cmdWRDI = 0x04,
	cmdRDSR = 0x05, 
	cmdWRSR = 0x01 
};

void eepromInit(SPI_HandleTypeDef *spiHandle);
uint8_t eepromReadStatus(SPI_HandleTypeDef *spiHandle); 
int eepromRead(SPI_HandleTypeDef *spiHandle, uint8_t *buf, unsigned int cnt, uint16_t address);
int eepromWrite(SPI_HandleTypeDef *spiHandle, uint8_t *buf, unsigned int cnt, uint16_t address);
void eepromWriteEnable(SPI_HandleTypeDef *spiHandle) ;

#endif /* __SPI_EEPROM_H */
