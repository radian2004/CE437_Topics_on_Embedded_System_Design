
#include "ECU_Diagnostic/ECU_Diagnostic.h"
#include "DiagnosticDefine.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "CanTP.h"

#define Security_Lock			1
#define Security_Unlock			0

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
	} else {
		// off led
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
		printf("Read data DID not support\r\n");
		return HAL_OK;
	}
	uint8_t RespBuff[5] = { Get_Positive_RespID(ReadData_ByID_ReqSID), pData[1],
			pData[2], 0, 0 };
	RespBuff[3] = RECV_ID >> 8;
	RespBuff[4] = RECV_ID & 0xFF;
	HAL_ERR(CanTP_Transmit(RespBuff, 5));
	HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_SET);
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
		printf("Security Access DID not support\r\n");
		return HAL_OK;
	}
	uint8_t ReqDID = pData[1];
	if (ReqDID != WriteData_CanID_DID) {
		uint8_t NegResp[3] = { 0x7F, WriteData_ByID_ReqSID,
				NegResp_DID_notSupport };
		HAL_ERR(CanTP_Transmit(NegResp, 3));
		printf("Security Access DID not support\r\n");
		return HAL_OK;
	}
	uint8_t PosResp = Get_Positive_RespID(WriteData_ByID_ReqSID);
	HAL_ERR(CanTP_Transmit(&PosResp, 1));
	return HAL_OK;
}
uint8_t ECU_SecurityAccess_RequestService(uint8_t *pData, uint16_t Len) {
	uint8_t ReqSF = pData[1];
	if (ReqSF != SecurityAccess_ReqSeedID) {
//		uint8_t RespPacket[3] = { 0x7F, SecurityAccess_ReqSID,
//		NegResp_ReadData_Service };
//		HAL_ERR(CanTP_Transmit(RespPacket, 3));
//		printf("Security Access SF invalid\r\n");
		return HAL_OK;
	}
	uint8_t RespBuff[6] = { Get_Positive_RespID(SecurityAccess_ReqSID), ReqSF,
			0, 0, 0, 0 };
	uint8_t Seeds[4];
	ECU_SeedsGen(Seeds);
	memcpy(RespBuff + 2, Seeds, 4);

	HAL_ERR(CanTP_Transmit(RespBuff, 6));
	uint8_t Keys[16] = { 0 };
	uint8_t RecvKey[16] = { 0 };
	KeyCalculate(Keys, Seeds);
	uint8_t RecvKeyBuff[18] = { 0 };
	uint16_t RecvKeyLen = 18;
	HAL_ERR(CanTP_Receive((uint8_t *)RecvKeyBuff, &RecvKeyLen, 500));
	uint8_t ReqSID = pData[0];
	ReqSF = pData[1];
	if (ReqSID != SecurityAccess_ReqSID) {
		printf("Security Access wrong SID\r\n");
		return HAL_OK;
	} else if (ReqSF != SecurityAccess_SendKeyID) {
		printf("Security Access wrong SF\r\n");
		return HAL_OK;
	}
	memcpy(RecvKey, RecvKeyBuff + 2, 16);
	if (!ECU_CheckKey(RecvKey, Keys)) {
		uint8_t RespPacket[3] = { 0x7F, SecurityAccess_ReqSID,
		NegResp_SecurityAccess_InvalidKey };
		HAL_ERR(CanTP_Transmit(RespPacket, 3));
		printf("Security Access Key invalid\r\n");
		return HAL_OK;
	}
	Security_ChangeState(Security_Unlock);
	uint8_t RespKey[2] = { Get_Positive_RespID(SecurityAccess_ReqSID),
	SecurityAccess_SendKeyID };
	HAL_ERR(CanTP_Transmit(RespKey, 2));
	printf("Security Access success\r\n");
	return HAL_OK;
}
