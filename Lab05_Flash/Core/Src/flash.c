#include "flash.h"

/* PUBLIC FUNCTION DEFINITION BEGIN */
HAL_StatusTypeDef Flash_writeData(uint32_t *addr, uint32_t *write_data){
	ERROR_HANDLER(HAL_FLASH_Unlock());
	FLASH_EraseInitTypeDef erase_handler;
	erase_handler.TypeErase = FLASH_TYPEERASE_PAGES;
	erase_handler.PageAddress = *addr;
	erase_handler.NbPages = 1;

	uint32_t error_page;
	ERROR_HANDLER(HAL_FLASHEx_Erase(&erase_handler, &error_page));
	ERROR_HANDLER(
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, *addr, *write_data)
	);
	return HAL_FLASH_Lock();
}

uint32_t Flash_readData(uint32_t read_addr){
	return *(__IO uint32_t *)(read_addr);
}
/* PUBLIC FUNCTION DEFINITION END */
