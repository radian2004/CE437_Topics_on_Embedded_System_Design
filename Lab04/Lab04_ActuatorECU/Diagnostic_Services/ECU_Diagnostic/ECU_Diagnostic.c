
#include "ECU_Diagnostic/ECU_Diagnostic.h"
#include "DiagnosticDefine.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "CanTP.h"

#define Security_Lock			1
#define Security_Unlock			0

extern UART_HandleTypeDef huart1;

//static uint8_t Security_Access = 0;
static uint8_t Security_State = Security_Lock;

static void ECU_SeedsGen(uint8_t Seeds[]) {
	Seeds[0] = rand() % 256;
	Seeds[1] = rand() % 256;
	Seeds[2] = rand() % 256;
	Seeds[3] = rand() % 256;
}

static uint8_t ECU_CheckKey(uint8_t RecvKey[], uint8_t CalKey[]) {
	for (int i = 0; i < 16; i++) {
		if (RecvKey[i] != CalKey[i])
			return 0;
	}
	return 1;
}

void Security_ChangeState(uint8_t State) {
	if (Security_State == Security_Unlock)
		return;
	if (State == Security_Lock) {
		// on LEd
		HAL_GPIO_WritePin(LEDIn_GPIO_Port, LEDIn_Pin, GPIO_PIN_SET);
	} else {
		// off led
		HAL_GPIO_WritePin(LEDIn_GPIO_Port, LEDIn_Pin, GPIO_PIN_RESET);
	}
	Security_State = State;
}

uint8_t ECU_Init() {
	HAL_ERR(CanTP_Init(SEND_ID, RECV_ID));
	return HAL_OK;
}

uint8_t ECU_ReadDataByID_RequestService(uint8_t pData[], uint16_t Len) {
	uint16_t ReqDID = Get_Resp_DID(pData[1], pData[2]);
	if (ReqDID != ReadData_CanID_DID) {
		uint8_t RespPacket[3] = { 0x7F, ReadData_ByID_ReqSID,
		NegResp_InvalidLen };
		HAL_ERR(CanTP_Transmit(RespPacket, 3));
		HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_SET);
		printf("Read data DID not support\r\n");
		return HAL_OK;
	}
	uint8_t RespBuff[5] = { Get_Positive_RespID(ReadData_ByID_ReqSID), pData[1],
			pData[2], 0, 0 };
	RespBuff[3] = RECV_ID >> 8;
	RespBuff[4] = RECV_ID & 0xFF;
	HAL_ERR(CanTP_Transmit(RespBuff, 5));
	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_RESET);
	return HAL_OK;
}
uint8_t ECU_WriteDataByID_RequestService(uint8_t *pData, uint16_t Len) {
//	if (Security_State == Security_Lock) {
//		uint8_t NegResp[3] = { 0x7F, WriteData_ByID_ReqSID, 0x33 };
//		HAL_ERR(CanTP_Transmit(NegResp, 3));
//		printf("Security Access denied\r\n");
//		return HAL_OK;
//	}
	if (Len < 4) {
		uint8_t NegResp[3] = { 0x7F, WriteData_ByID_ReqSID,
		NegResp_InvalidLen };
		HAL_ERR(CanTP_Transmit(NegResp, 3));
		printf("Write Data len not vaild\r\n");
		HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
		return HAL_OK;
	}
	uint16_t ReqDID = Get_Resp_DID(pData[1], pData[2]);
	if (ReqDID != WriteData_CanID_DID) {
		uint8_t NegResp[3] = { 0x7F, WriteData_ByID_ReqSID,
		NegResp_DID_notSupport };
		HAL_ERR(CanTP_Transmit(NegResp, 3));
		printf("Write Data DID not support\r\n");
		HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
		return HAL_OK;
	}
	if (pData[3] == 0x12 && pData[4] == 0x13) {
		HAL_GPIO_TogglePin(LEDG_GPIO_Port, LEDG_Pin);
	}
	uint8_t PosResp[] = { Get_Positive_RespID(WriteData_ByID_ReqSID) };
	HAL_ERR(CanTP_Transmit(PosResp, 1));
	return HAL_OK;
}
uint8_t ECU_SecurityAccess_RequestService(uint8_t *pData, uint16_t Len) {
	uint8_t ReqSF = pData[1];
	if (ReqSF != SecurityAccess_ReqSeedID) {
//		uint8_t RespPacket[3] = { 0x7F, SecurityAccess_ReqSID,
//		NegResp_ReadData_Service };
//		HAL_ERR(CanTP_Transmit(RespPacket, 3));
//		printf("Security Access SF invalid\r\n");
//		HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
		return HAL_OK;
	}
	uint8_t RespBuff[6] = { Get_Positive_RespID(SecurityAccess_ReqSID),
	SecurityAccess_ReqSeedID, 0, 0, 0, 0 };
	uint8_t Seeds[4];
	ECU_SeedsGen(Seeds);
	memcpy(RespBuff + 2, Seeds, 4);

	HAL_ERR(CanTP_Transmit(RespBuff, 6));
	uint8_t RecvKeyBuff[18] = { 0 };
	memset(RecvKeyBuff,0,18);
	uint8_t RecvKeyLen = 18;
	char PrintBuf[20] = "";
	uint16_t printSize = 0;
//	printSize = sprintf(PrintBuf, "SSS\r\n");
//	HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, 1);
	uint8_t Keys[16] = { 0 };
	uint8_t RecvKey[16] = { 0 };
	KeyCalculate(Keys, Seeds);

	HAL_ERR(CanTP_Receive(RecvKeyBuff, &RecvKeyLen, 1500));
	printSize = sprintf(PrintBuf, "RKS\r\n");
	HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, 1);
	uint8_t ReqSID = RecvKeyBuff[0];
	ReqSF = RecvKeyBuff[1];
	if (ReqSID != SecurityAccess_ReqSID) {
		HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
		printSize = sprintf(PrintBuf, "WSID: %x,%x,%x\r\n",RecvKeyBuff[0],RecvKeyBuff[1],RecvKeyBuff[2]);
		HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
//		printf("Security Access wrong SID\r\n");
		HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, 1);
		return HAL_OK;
	} else if (ReqSF != SecurityAccess_SendKeyID) {
		HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
		printSize = sprintf(PrintBuf, "WSF\r\n");
		HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
//		printf("Security Access wrong SF\r\n");
		HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, 1);
		return HAL_OK;
	}
	memcpy(RecvKey, RecvKeyBuff + 2, 16);
	if (!ECU_CheckKey(RecvKey, Keys)) {
		uint8_t RespPacket[3] = { 0x7F, SecurityAccess_ReqSID,
		NegResp_SecurityAccess_InvalidKey };
		HAL_ERR(CanTP_Transmit(RespPacket, 3));
		printf("Security Access Key invalid\r\n");
		HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
		printSize = sprintf(PrintBuf, "WK\r\n");
		HAL_UART_Transmit(&huart1, PrintBuf, printSize, 200);
		return HAL_OK;
	}

	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, 1);
	Security_ChangeState(Security_Unlock);
	uint8_t RespKey[2] = { Get_Positive_RespID(SecurityAccess_ReqSID),
	SecurityAccess_SendKeyID };
	HAL_ERR(CanTP_Transmit(RespKey, 2));
	printf("Security Access success\r\n");
	return HAL_OK;
}
