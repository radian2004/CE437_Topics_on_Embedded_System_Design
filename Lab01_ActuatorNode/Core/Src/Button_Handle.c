/*
 * Button_Handle.c
 *
 *  Created on: Oct 12, 2023
 *      Author: nhakh
 */

#include "Button_Handle.h"

void Button_Init(Button_Handle_t* button,uint32_t pin,TIM_HandleTypeDef* htim){
	button->pin = pin;
	button->htim = htim;
	button->state = RELEASED;
	button->lastState = RELEASED;
}

void Button_StartPressedCounter(Button_Handle_t *button) {
//	button->state = PRESSED;
	__HAL_TIM_SET_AUTORELOAD(button->htim,4999);
	HAL_TIM_Base_Start_IT(button->htim);
}

void Button_StartTimer(Button_Handle_t *button) {
//	button->state = LONGPRESSED;
	__HAL_TIM_SET_AUTORELOAD(button->htim,1999);
	HAL_TIM_Base_Start_IT(button->htim);
}

void Button_StopTimerCounter(Button_Handle_t *button){
//	button->state = RELEASED;
	HAL_TIM_Base_Stop_IT(button->htim);

}
