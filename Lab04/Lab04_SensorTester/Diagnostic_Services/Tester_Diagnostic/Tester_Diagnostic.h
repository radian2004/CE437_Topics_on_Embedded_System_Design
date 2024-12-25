/*
 * Tester_Diagnostic.h
 *
 *  Created on: Dec 2, 2023
 *      Author: nhakh
 */

#ifndef TESTER_DIAGNOSTIC_TESTER_DIAGNOSTIC_H_
#define TESTER_DIAGNOSTIC_TESTER_DIAGNOSTIC_H_

#include "stdint.h"

//uint8_t Send_ReqServiceByRID(uint8_t RID,,uint8_t* DR);
uint8_t Tester_Init();

uint8_t Tester_ReadDataByID_RequestService(uint16_t DID);
uint8_t Tester_WriteDataByID_RequestService(uint16_t DID,uint8_t *Data,uint8_t Len);
uint8_t Tester_SecurityAccess_RequestService();


#endif /* TESTER_DIAGNOSTIC_TESTER_DIAGNOSTIC_H_ */
