
#include "Tester_Diagnostic.h"
#include "DiagnosticDefine.h"
#include "main.h"
#include "CanTP.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;

uint8_t Tester_Init() {
	HAL_ERR(CanTP_Init(SEND_ID, RECV_ID));
	return HAL_OK;
}

uint8_t Tester_ReadDataByID_RequestService(uint16_t DID) {
	uint8_t ReqSID = ReadData_ByID_ReqSID;
	uint8_t SendBuff[3];
	uint16_t RecvLen = 20;
	uint8_t RecvBuff[RecvLen];
	SendBuff[0] = ReqSID;
	SendBuff[1] = DID >> 8;
	SendBuff[2] = DID & 0xFF;
//	isotp_send(&CanTP, SendBuff, 3);
	HAL_ERR(CanTP_Transmit(SendBuff, 3));

	HAL_ERR(CanTP_Receive(RecvBuff, &RecvLen, 500));
	//uint16_t RespDID = RecvBuff[1] << 8 | (Rec)
	uint8_t RespSID = RecvBuff[0];
	if (RespSID == Get_Positive_RespID(ReadData_ByID_ReqSID)
			&& DID == Get_Resp_DID(RecvBuff[1], RecvBuff[2])) {
		uint16_t RD_len = RecvLen - 3;
		uint8_t RDBuff[RD_len];
		memcpy(RDBuff, RecvBuff + 3, RD_len);
		HAL_GPIO_TogglePin(LEDG_GPIO_Port, LEDG_Pin);
		printf("Read Data Success\r\n");
		return HAL_OK;
	}
	printf("Read Data Failed\r\n");
	HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_SET);
	return HAL_ERROR;

}
uint8_t Tester_WriteDataByID_RequestService(uint16_t DID, uint8_t *Data,
		uint8_t Len) {
	uint8_t ReqSID = WriteData_ByID_ReqSID;
	uint8_t SendBuff[Len + 3];
	uint16_t RecvLen = 20;
	uint8_t RecvBuff[RecvLen];
	SendBuff[0] = ReqSID;
	SendBuff[1] = DID >> 8;
	SendBuff[2] = DID & 0xFF;
	memcpy(SendBuff + 3, Data, Len);
	//	isotp_send(&CanTP, SendBuff, 3);
	HAL_ERR(CanTP_Transmit(SendBuff, Len + 3));

	HAL_ERR(CanTP_Receive(RecvBuff, &RecvLen, 500));
	uint8_t RespSID = RecvBuff[0];
	if (RespSID == Get_Positive_RespID(WriteData_ByID_ReqSID)) {
		printf("Write Data Success\r\n");
		HAL_GPIO_TogglePin(LEDG_GPIO_Port, LEDG_Pin);
		return HAL_OK;
	}
	HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
	printf("Write Data Failed\r\n");
	return HAL_ERROR;
}
uint8_t Tester_SecurityAccess_RequestService() {
	uint8_t ReqSeedsBuff[2] =
			{ SecurityAccess_ReqSID, SecurityAccess_ReqSeedID };
	uint8_t RespSeedsBuff[6];
	uint8_t RespSeedsLen = 6;
	HAL_ERR(CanTP_Transmit(ReqSeedsBuff, 2));

	HAL_ERR(CanTP_Receive(RespSeedsBuff, RespSeedsLen, 1000));
	uint8_t RespSID = RespSeedsBuff[0];
	uint8_t RespSF = RespSeedsBuff[1];
	if (RespSID != Get_Positive_RespID(SecurityAccess_ReqSID)
			|| RespSF != SecurityAccess_ReqSeedID) {
		printf("Security Access request Seeds error: %d", RespSeedsBuff[2]);
//		HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, 1);
		HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
		return HAL_ERROR;
	}
	uint8_t Seeds[4];
	memcpy(Seeds, RespSeedsBuff + 2, 4);
	uint8_t Keys[16];
	KeyCalculate(Keys, Seeds);

	uint8_t SendKeysBuff[18];
	SendKeysBuff[0] = SecurityAccess_ReqSID;
	SendKeysBuff[1] = SecurityAccess_SendKeyID;
	memcpy(SendKeysBuff + 2, Keys, 16);

	HAL_ERR(CanTP_Transmit(SendKeysBuff, 18));
	char PrintBuf[20] = "";
	uint16_t printSize = 0;
//	printSize = sprintf(PrintBuf, "SSS\r\n");
//	HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);

	uint8_t RespCheckKeysBuff[3];
	uint8_t RespCheckKeyLen = 3;
	HAL_ERR(CanTP_Receive(RespCheckKeysBuff, RespCheckKeyLen, 1500));
//	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, 1);
//	char PrintBuf[20] = "";
//	uint16_t printSize = 0;
	printSize = sprintf(PrintBuf, "SAS\r\n");
	HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
//	printf("Security Access Success\r\n");
//	HAL_GPIO_TogglePin(LEDG_GPIO_Port, LEDG_Pin);
	RespSID = RespCheckKeysBuff[0];
	RespSF = RespCheckKeysBuff[1];
	if (RespSID == Get_Positive_RespID(SecurityAccess_ReqSID)
			&& RespSF == SecurityAccess_SendKeyID) {
//		HAL_GPIO_TogglePin(LEDG_GPIO_Port, LEDG_Pin);
//		char PrintBuf[20] = "";
//		uint16_t printSize = 0;
//		printSize = sprintf(PrintBuf, "SAS\r\n");
//		HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
		printf("Security Access Success\r\n");
		HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, 1);
		return HAL_OK;
	}
	HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
	printf("Security Access Failed\r\n");
	return HAL_ERROR;
}
