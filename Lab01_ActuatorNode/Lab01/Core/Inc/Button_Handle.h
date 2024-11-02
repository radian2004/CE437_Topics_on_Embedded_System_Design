/*
 * Button_Handle.h
 *
 *  Created on: Oct 12, 2023
 *      Author: nhakh
 */

#ifndef INC_BUTTON_HANDLE_H_
#define INC_BUTTON_HANDLE_H_

#include "main.h"
#include "stdio.h"

//#define
//#define PRESS_COUNTER

typedef enum Button_State {
	PRESSED = 0,
	RELEASED = 1,
	LONGPRESSED = 2,
} Button_State_t;

typedef struct Button_HandleStruct {
	uint32_t pin;
	Button_State_t state;
	Button_State_t lastState;
	TIM_HandleTypeDef *htim;
} Button_Handle_t;

void Button_Init(Button_Handle_t* button,uint32_t pin,TIM_HandleTypeDef* htim);

void Button_StartPressedCounter(Button_Handle_t *button);

void Button_StartTimer(Button_Handle_t *button);

void Button_StopTimerCounter(Button_Handle_t *button);

#endif /* INC_BUTTON_HANDLE_H_ */
