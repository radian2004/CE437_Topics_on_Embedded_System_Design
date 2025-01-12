
#include "SERVO.h"

void Start_Servo()
{
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	To_Default();
	HAL_Delay(100);		// Allow time for the servo to move to the default position
}
/**
 * @brief Convert an angle in degrees to the corresponding PWM value.
 * @param angle Angle in degrees (0-180).
 * @return PWM value for the specified angle.
 */
uint16_t Angle(double angle)
{
	double temp = 250 + angle * 5.56;		// Conversion formula
	return (int)temp;
}
/**
 * @brief Move the servo to the default position (90 degrees).
 */
void To_Default()
{
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1, Angle(90));		// Set to 90 degrees
}
/**
 * @brief Move the servo to a specified angle with optional speed control.
 * @param CAngle Current angle of the servo.
 * @param DAngle Desired angle to move to.
 * @param mode Movement mode: FAST for direct movement, or SLOW for gradual movement.
 * @param inc Increment for slow movement (in degrees).
 */
void To_Angle(uint16_t CAngle, uint16_t DAngle, uint8_t mode, uint16_t inc)
{
	if (mode == FAST) {
		// Move directly to the desired angle
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1, Angle(DAngle));
	}
	else {
		// Gradual movement with incremental steps
		while (CAngle < DAngle) {
			__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1, Angle(CAngle));
			HAL_Delay(80);		// Delay between increments
			CAngle += inc;
		}
	}
}
/**
 * @brief Turn the servo to the left (48 degrees).
 */
void Turn_Left()
{
	//To_Default();
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1, Angle(48));
}
/**
 * @brief Turn the servo to the right (136 degrees).
 */
void Turn_Right()
{
	//To_Default();
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1, Angle(136));
}
