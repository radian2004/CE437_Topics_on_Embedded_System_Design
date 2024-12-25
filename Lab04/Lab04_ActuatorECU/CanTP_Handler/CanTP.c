/*
 * CanTP.c
 *
 *  Created on: Dec 2, 2023
 *      Author: nhakh
 */

#include "CanTP.h"
#include "main.h"
#include "isotp.h"

extern CAN_HandleTypeDef hcan;
extern UART_HandleTypeDef huart1;
IsoTpLink isoTP;
#define CANTP_BUFF_SIZE			100

uint8_t SendBuffer[CANTP_BUFF_SIZE];
uint8_t RecvBuffer[CANTP_BUFF_SIZE];

uint8_t CanTP_Init(uint16_t SendId, uint16_t RecvId) {
	CAN_FilterTypeDef Can_Filter;
	Can_Filter.FilterActivation = CAN_FILTER_ENABLE;
	Can_Filter.FilterBank = 0;
	Can_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	Can_Filter.FilterMode = CAN_FILTERMODE_IDLIST;
	Can_Filter.FilterScale = CAN_FILTERSCALE_16BIT;
	Can_Filter.FilterIdHigh = RecvId << 5;
	HAL_ERR(HAL_CAN_ConfigFilter(&hcan, &Can_Filter));

	HAL_ERR(HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING));

	HAL_ERR(HAL_CAN_Start(&hcan));
//	uint8_t status = 0;
	isotp_init_link(&isoTP, SendId, SendBuffer, CANTP_BUFF_SIZE, RecvBuffer,
	CANTP_BUFF_SIZE);
	return HAL_OK;
}

uint8_t CanTP_Transmit(uint8_t *pData, uint16_t len) {
	HAL_ERR(isotp_send(&isoTP, pData, len));
	while (isoTP.send_status == ISOTP_SEND_STATUS_INPROGRESS) {
		isotp_poll(&isoTP);
	}
	if (ISOTP_SEND_STATUS_IDLE != isoTP.send_status) {
		HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, 1);
		return HAL_ERROR;
	}
	return HAL_OK;
}

uint8_t CanTP_Receive(uint8_t *pData, uint16_t *len, uint32_t timeout) {
	uint32_t startTime = HAL_GetTick();
	while ((HAL_GetTick() - startTime) < timeout) {
		isotp_poll(&isoTP);
		if (isoTP.receive_status == ISOTP_RECEIVE_STATUS_FULL) {
//			HAL_GPIO_WritePin(LEDIn_GPIO_Port, LEDIn_Pin,0);
			break;
		}
	}
	uint8_t status = 0;
	if (ISOTP_RECEIVE_STATUS_FULL == isoTP.receive_status) {
//		char PrintBuf[20] = "";
//		uint16_t printSize = 0;
//		printSize = sprintf(PrintBuf, "%x %x %x\r\n", isoTP.receive_buffer[0],
//				isoTP.receive_buffer[1], isoTP.receive_buffer[2]);
//		HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
		status = isotp_receive(&isoTP, pData, *len, len);
		uint16_t copylen = isoTP.receive_size;
		if (copylen > *len) {
			copylen = *len;
		}
		for (int i = 0;i < copylen;i++) {
			pData[i] = isoTP.receive_buffer[i];
		}
//		memcpy(pData, isoTP.receive_buffer, copylen);
//		if (status != ISOTP_RET_OK) {
//			HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, 1);
//			return HAL_ERROR;
//		}
//		char PrintBuf[20] = "";
//		uint16_t printSize = 0;
//		printSize = sprintf(PrintBuf, "Rsuccessful\r\n");
//		HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
		return HAL_OK;
	}
	HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, 1);
//	char PrintBuf[20] = "";
//	uint16_t printSize = 0;
//	printSize = sprintf(PrintBuf, "Rtimeout\r\n");
//	HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
	return HAL_TIMEOUT;
}

void CanTP_RcvCallback() {
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData[8] = { 0 };
	HAL_CAN_GetRxMessage(&hcan, CAN_FILTER_FIFO0, &RxHeader, RxData);
	isotp_on_can_message(&isoTP, RxData, RxHeader.DLC);
}
