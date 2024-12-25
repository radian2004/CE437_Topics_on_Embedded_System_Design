
#include "DiagnosticDefine.h"
#include "CanTP.h"

void KeyCalculate(uint8_t *Keys, uint8_t *Seeds) {
	Keys[0] = Seeds[0] ^ Seeds[1];
	Keys[1] = Seeds[1] + Seeds[2];
	Keys[2] = Seeds[2] ^ Seeds[3];
	Keys[3] = Seeds[3] + Seeds[0];

	Keys[4] = Seeds[0] | Seeds[1];
	Keys[5] = Seeds[1] + Seeds[2];
	Keys[6] = Seeds[2] | Seeds[3];
	Keys[7] = Seeds[3] + Seeds[0];

	Keys[8] = Seeds[0] & Seeds[1];
	Keys[9] = Seeds[1] + Seeds[2];
	Keys[10] = Seeds[2] & Seeds[3];
	Keys[11] = Seeds[3] + Seeds[0];

	Keys[12] = Seeds[0] - Seeds[1];
	Keys[13] = Seeds[1] + Seeds[2];
	Keys[14] = Seeds[2] - Seeds[3];
	Keys[15] = Seeds[3] + Seeds[0];
}

uint8_t DiagnosticService_Init() {
#ifdef TesterNode
	return Tester_Init();
#elif ECUNode
	return ECU_Init();
#endif
}


uint8_t RecvData[20] = { 0 };
uint16_t RecvLen = 20;
void Diagnostic_Handler() {
	uint8_t Recv_State = CanTP_Receive(RecvData, RecvLen, 500);

	if (Recv_State == HAL_OK) {
		int ReqSID = RecvData[0];
		switch (ReqSID) {
		case ReadData_ByID_ReqSID:
//			HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_SET);
			ECU_ReadDataByID_RequestService(RecvData, RecvLen);
			break;
		case WriteData_ByID_ReqSID:
//			HAL_GPIO_WritePin(LEDG_GPIO_Port, LEDG_Pin, GPIO_PIN_SET);
			ECU_WriteDataByID_RequestService(RecvData, RecvLen);
			break;
		case SecurityAccess_ReqSID:
			ECU_SecurityAccess_RequestService(RecvData, RecvLen);
		default:
			break;
		}
	}
}
