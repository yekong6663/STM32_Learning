#include "stm32f10x.h"                  // Device header
#include "PWM.h"
void Servo_Init(void)
{
	PWM_Init();
}
/*
angle=0->CCR=500
angle=180->CCR=2000
*/
void Servo_SetAngle(float angle)
{
	PWM_SetCompare2( angle / 180 *2000 + 500);
}
