
#ifndef INC_SIGNAL_H_
#define INC_SIGNAL_H_

#include "main.h"

#define LEFT_STATE 		1
#define RIGHT_STATE 	2
#define FORWARD_STATE 	3
#define BACKWARD_STATE	4
#define TEST_SENSORS 	5

extern uint8_t LEFT[8];
extern uint8_t RIGHT[8];
extern uint8_t FORWARD[8];
extern uint8_t BACKWARD[8];

uint8_t Get_State(int d1, int d2);
uint8_t Get_CounterState(uint8_t state);
#endif /* INC_SIGNAL_H_ */
