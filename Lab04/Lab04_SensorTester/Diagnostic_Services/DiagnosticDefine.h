
#ifndef DIAGNOSTICDEFINE_H_
#define DIAGNOSTICDEFINE_H_

#include <stdint.h>
#include "ECU_Diagnostic/ECU_Diagnostic.h"
#include "Tester_Diagnostic/Tester_Diagnostic.h"
#include "CanTP.h"

#define TesterNode

#define ECU_ID						0x7A2
#define TESTER_ID					0x712
#ifdef TesterNode
#define	SEND_ID 						ECU_ID
#define RECV_ID 						TESTER_ID
#else
#define	SEND_ID 						TESTER_ID
#define RECV_ID 						ECU_ID
#endif

#define ReadData_ByID_ReqSID 		0x22
#define WriteData_ByID_ReqSID		0x2E
#define SecurityAccess_ReqSID		0x27

#define ReadData_CanID_DID			0x0123
#define WriteData_CanID_DID			0x0123
//#define ReadData_ByID_RespSID 		0x62
//#define WriteData_ByID_RespSID		0x6E
//#define SecurityAccess_RespSID		0x67

#define SecurityAccess_ReqSeedID	0x01
#define SecurityAccess_SendKeyID	0x02


#define NegResp_InvalidLen			0x13
#define NegResp_SecurityAccess_InvalidKey	0x35
#define NegResp_DID_notSupport				0x31

#define Get_Positive_RespID(ReqID)			((uint16_t)ReqID + 0x40)
#define Get_Resp_DID(DID_H,DID_L)		((uint16_t)DID_H << 8 | (DID_L & 0xFF))

void KeyCalculate(uint8_t *Keys, uint8_t *Seeds);
void DiagnosticService_Init();
void Diagnostic_Handler();
#endif /* DIAGNOSTICDEFINE_H_ */
