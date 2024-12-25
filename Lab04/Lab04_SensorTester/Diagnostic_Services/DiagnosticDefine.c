
#include "DiagnosticDefine.h"

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

void DiagnosticService_Init() {
#ifdef TesterNode
	Tester_Init();
#elif ECUNode
	ECU_Init();
#endif
}

void Diagnostic_Handler() {

}
