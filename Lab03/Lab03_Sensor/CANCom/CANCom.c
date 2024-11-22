
#include "main.h"
#include "CANCom.h"

extern CAN_HandleTypeDef hcan;
extern uint8_t SendBuf[8];
extern uint8_t MsgCounter;

void CANCom_Init() {
	CAN_FilterTypeDef RxFilter = {0 };
	RxFilter.FilterActivation = CAN_FILTER_ENABLE;
	RxFilter.FilterBank = 0;
	RxFilter.FilterFIFOAssignment = CAN_RX_FIFO0;
	RxFilter.FilterIdHigh = RX_ID << 5;
	RxFilter.FilterMode = CAN_FILTERMODE_IDLIST;
	RxFilter.FilterScale = CAN_FILTERSCALE_16BIT;
	HAL_CAN_ConfigFilter(&hcan, &RxFilter);
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_Start(&hcan);
}

void CANCom_Transmit(uint8_t *pData, uint8_t len) {
	CAN_TxHeaderTypeDef TxHeader;
	TxHeader.DLC = len;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = TX_ID;
	uint8_t Mailbox;
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, pData, &Mailbox);
}

void Sensor_RecvHandle(uint8_t *Buf,uint8_t Len) {
	int crc_check = calc_SAE_J1850(Buf, 7);
	if (crc_check == (int)Buf[7]) {
		uint8_t RespBuf[8] = {0};
		RespBuf[0] = Buf[0];
		RespBuf[1] = Buf[1];
		RespBuf[7] = MsgCounter++;
		CANCom_Transmit(RespBuf, 8);

	}
}

void Actuator_RecvHandle(uint8_t *Buf,uint8_t Len) {
	if (Buf[0] == SendBuf[0] && Buf[1] == SendBuf[1] && MsgCounter == Buf[7]) {
		HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_RESET);
	}
	else {
		HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_RESET);
	}
}

void CANCom_ReceiveCallback() {
	uint8_t RcvBuf[8];
	CAN_RxHeaderTypeDef RxHeader;
	HAL_CAN_GetRxMessage(&hcan, CAN_FILTER_FIFO0, &RxHeader, RcvBuf);
#if SENSOR_NODE
	Sensor_RecvHandle(RcvBuf,RxHeader.DLC);
#elif ACTUATOR_NODE
	Actuator_RecvHandle(RcvBuf,RxHeader.DLC);
#endif
}
