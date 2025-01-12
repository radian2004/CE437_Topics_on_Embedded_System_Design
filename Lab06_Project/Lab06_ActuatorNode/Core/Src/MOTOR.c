
#include "MOTOR.h"

void Start_Motor()
{
	// Start PWM channels
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	// Set motor control pins to high
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
}

void run(uint8_t speed, uint8_t mode)
{
	if (mode == SFORWARD) {
		genPwm(&htim1,TIM_CHANNEL_4, speed);	// Forward channel
		genPwm(&htim1,TIM_CHANNEL_1, 0);		// Stop backward channel
	}
	else {	// SBACKWARD
		genPwm(&htim1,TIM_CHANNEL_4, 0);		// Stop forward channel
		genPwm(&htim1,TIM_CHANNEL_1, speed);	// Backward channel
	}
}

void genPwm(TIM_HandleTypeDef *htim, uint32_t channel, float duty_cycle)
{
	// Calculate load value based on duty cycle
	float load_value = (duty_cycle / 100) * htim->Instance->ARR;
	// Set compare register value to generate PWM
	__HAL_TIM_SET_COMPARE(htim, channel, (uint16_t)load_value);
}

void stop()
{
	// Stop PWM signals
	genPwm(&htim1,TIM_CHANNEL_4, 0);
	genPwm(&htim1,TIM_CHANNEL_1, 0);
	// Short delay to ensure the motor stops completely
	HAL_Delay(200);
}
