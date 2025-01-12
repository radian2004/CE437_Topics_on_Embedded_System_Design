
#include "CAN_Handler.h"
// Global Variables
CAN_TxHeaderTypeDef TxHeader;		// Transmit header for CAN
uint32_t Mailbox;					// Mailbox for transmitting CAN messages
uint8_t TxBuffer[] = { 4, 5, 6, 7, 0, 0, 0, 8 };	// Transmit buffer data


CAN_RxHeaderTypeDef RxHeader;		// Receive header for CAN
CAN_FilterTypeDef canfilterconfig;	// Filter configuration for CAN
uint8_t RxData[8];					// Receive buffer data

void CAN_ComInit_Std(CAN_TxHeaderTypeDef *Tx_Header, CAN_HandleTypeDef *hcan, uint32_t id, uint8_t dlc)
{
	Tx_Header->IDE = CAN_ID_STD;	// Use standard ID
	Tx_Header->DLC = dlc;			// Set data length code
	Tx_Header->StdId = id;			// Set standard identifier
	Tx_Header->RTR = CAN_RTR_DATA;	// Set remote transmission request to data frame
	HAL_CAN_Start(hcan);			// Start CAN communication
}

void CAN_FilterInit_SingleFF0(CAN_HandleTypeDef *hcan, CAN_FilterTypeDef *canfilterconfig, uint32_t addr)
{
	canfilterconfig->FilterActivation = CAN_FILTER_ENABLE;
	canfilterconfig->FilterBank = 0;							// Use filter bank 0
	canfilterconfig->FilterFIFOAssignment = CAN_FILTER_FIFO0;	// Assign to FIFO 0
	canfilterconfig->FilterIdHigh = addr << 5;					// Set filter ID high (left-aligned 11-bit ID)
	canfilterconfig->FilterIdLow = 0x0000;						// Set filter ID low
	canfilterconfig->FilterMaskIdHigh = addr << 5;				// Set mask ID high
	canfilterconfig->FilterMaskIdLow = 0x0000;					// Set mask ID low
	canfilterconfig->FilterMode = CAN_FILTERMODE_IDMASK;		// Use ID-mask mode
	canfilterconfig->FilterScale = CAN_FILTERSCALE_32BIT;		// Use 32-bit filter scale

	HAL_CAN_ConfigFilter(hcan, canfilterconfig);				// Configure CAN filter
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);	// Enable RX interrupt
}

uint32_t CAN_Transmit(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *Tx_Header, uint8_t* buffer)
{
	HAL_CAN_AddTxMessage(hcan, Tx_Header, buffer, &Mailbox);
	return Mailbox;
}
