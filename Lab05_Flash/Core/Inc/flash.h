#ifndef _FLASH_H_
#define _FLASH_H_

#include "stm32f1xx_hal.h"

#define	ERROR_HANDLER(STATUS)					\
	do{											\
		uint8_t _status = STATUS; 				\
		if(_status != HAL_OK){					\
			return _status;						\
		}										\
	}while(0);

uint32_t Flash_readData(uint32_t);
HAL_StatusTypeDef Flash_writeData(uint32_t *, uint32_t *);

#endif


