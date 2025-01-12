

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "tim.h"
#include "gpio.h"

#define SFORWARD 	1
#define SBACKWARD 	0

void Start_Motor();
void genPwm(TIM_HandleTypeDef *htim, uint32_t channel, float duty_cycle);
void run(uint8_t speed, uint8_t mode);
void stop();

#endif /* INC_MOTOR_H_ */
