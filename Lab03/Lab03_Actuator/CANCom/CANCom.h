
#ifndef CANCOM_H_
#define CANCOM_H_


#define SENSOR_NODE			0
#define ACTUATOR_NODE		1

#define SENSOR_ID			0x0A2
#define ACTUATOR_ID			0x012


#if SENSOR_NODE
#define TX_ID				ACTUATOR_ID
#define	RX_ID				SENSOR_ID
#elif	ACTUATOR_NODE
#define TX_ID				SENSOR_ID
#define	RX_ID				ACTUATOR_ID
#endif

void CANCom_Init();

void CANCom_Transmit(uint8_t * pData,uint8_t len);

void CANCom_ReceiveCallback();


#endif /* CANCOM_H_ */
