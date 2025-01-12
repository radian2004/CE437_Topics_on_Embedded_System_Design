

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "tim.h"
#include "main.h"

#define FAST 1
#define SLOW 0

void Start_Servo();
uint16_t Angle(double angle);
void To_Default();
void To_Angle(uint16_t CAngle, uint16_t DAngle, uint8_t mode, uint16_t inc);
void Turn_Left();
void Turn_Right();
#endif /* INC_SERVO_H_ */
