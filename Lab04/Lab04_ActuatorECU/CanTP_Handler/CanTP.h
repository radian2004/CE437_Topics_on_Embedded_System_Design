/*
 * CanTP.h
 *
 *  Created on: Dec 2, 2023
 *      Author: nhakh
 */

#ifndef CANTP_H_
#define CANTP_H_

#include <stdint.h>

uint8_t CanTP_Init(uint16_t SendId,uint16_t RecvID);

uint8_t CanTP_Transmit(uint8_t *pData,uint16_t len);

uint8_t CanTP_Receive(uint8_t *pData,uint16_t *len,uint32_t timeout);

void CanTP_RcvCallback();

#endif /* CANTP_H_ */
