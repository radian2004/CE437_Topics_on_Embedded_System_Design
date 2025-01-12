
#include "CAN_Handler.h"
CAN_TxHeaderTypeDef TxHeader;
uint32_t Mailbox;
uint8_t TxBuffer[] = { 1, 2, 3, 4, 5, 6, 0, 9 };

CAN_RxHeaderTypeDef RxHeader;
CAN_FilterTypeDef canfilterconfig;
uint8_t RxData[8];

void CAN_ComInit_Std(CAN_TxHeaderTypeDef *Tx_Header, CAN_HandleTypeDef *hcan, uint32_t id, uint8_t dlc)
{
	Tx_Header->IDE = CAN_ID_STD;	// Use Standard ID
	Tx_Header->DLC = dlc;			// Set data length
	Tx_Header->StdId = id;			// Set Standard ID
	Tx_Header->RTR = CAN_RTR_DATA;	// Data Frame
	HAL_CAN_Start(hcan);			// Start the CAN peripheral
}

void CAN_FilterInit_SingleFF0(CAN_HandleTypeDef *hcan, CAN_FilterTypeDef *canfilterconfig, uint32_t addr)
{
	canfilterconfig->FilterActivation = CAN_FILTER_ENABLE;		// Enable filter
	canfilterconfig->FilterBank = 0;							// Use filter bank 0
	canfilterconfig->FilterFIFOAssignment = CAN_FILTER_FIFO0;	// Assign to FIFO0
	canfilterconfig->FilterIdHigh = addr << 5;					// Set filter ID (high part)
	canfilterconfig->FilterIdLow = 0x0000;						// No additional bits
	canfilterconfig->FilterMaskIdHigh = addr << 5;				// Set mask ID (high part)
	canfilterconfig->FilterMaskIdLow = 0x0000;					// No additional bits
	canfilterconfig->FilterMode = CAN_FILTERMODE_IDMASK;		// Use ID masking
	canfilterconfig->FilterScale = CAN_FILTERSCALE_32BIT;		// 32-bit filter scale

	HAL_CAN_ConfigFilter(hcan, canfilterconfig);					// Configure the filter
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);// Enable RX FIFO0 interrupt
}

uint32_t CAN_Transmit(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *Tx_Header, uint8_t* buffer)
{
	HAL_CAN_AddTxMessage(hcan, Tx_Header, buffer, &Mailbox);
	return Mailbox;		// Return mailbox if transmission is successful
}
