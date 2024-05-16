#include <gpio.h>
#include <stdbool.h>
#include <rtthread.h>
#include "main.h"
#include "motor.h"
#include "stm32f1xx_hal_gpio.h"

float round_num=510; // 510 ~ 1 round

static uint8_t motor_step=0;

void GPIO_Control(uint8_t MOTOR_INX ,uint8_t dir)
{
	uint8_t step;
	step = MOTOR_INX;
	if(dir==0){MOTOR_INX = 7-step;}
	switch(MOTOR_INX)
	{
		case 0://A 
		{
			GPIOA->BSRR = GPIO_PIN_9;
			GPIOA->BSRR = (uint32_t)(GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12) << 16u;
			break;
		}
		case 1://AB
		{
			GPIOA->BSRR = (GPIO_PIN_9 | GPIO_PIN_10);
			GPIOA->BSRR = (uint32_t)(GPIO_PIN_11 | GPIO_PIN_12) << 16u;
			break;
		}
		case 2://B
		{
			GPIOA->BSRR = GPIO_PIN_10;
			GPIOA->BSRR = (uint32_t)(GPIO_PIN_9 | GPIO_PIN_11 | GPIO_PIN_12) << 16u;
			break;
		}
		case 3://BC
		{
			GPIOA->BSRR = (GPIO_PIN_10 | GPIO_PIN_11);
			GPIOA->BSRR = (uint32_t)(GPIO_PIN_9 | GPIO_PIN_12) << 16u;
			break;
		}
		case 4://C
		{
			GPIOA->BSRR = GPIO_PIN_11;
			GPIOA->BSRR = (uint32_t)(GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_12) << 16u;
			break;
		}
		case 5://CD
		{
			GPIOA->BSRR = (GPIO_PIN_11 | GPIO_PIN_12);
			GPIOA->BSRR = (uint32_t)(GPIO_PIN_9 | GPIO_PIN_10) << 16u;
			break;
		}
		case 6://D
		{
			GPIOA->BSRR = GPIO_PIN_12;
			GPIOA->BSRR = (uint32_t)(GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11) << 16u;
			break;
		}
		case 7://DA
		{
			GPIOA->BSRR = (GPIO_PIN_9 | GPIO_PIN_12);
			GPIOA->BSRR = (uint32_t)(GPIO_PIN_10 | GPIO_PIN_11) << 16u;
			break;
		}
		
	}
}

/* 	
A>AB>B>BC>C>CD>D>DA>A....
uint32_t motor_time the motor speed  /tick
bool Run_O_Stop 
*/

void motor_run(uint32_t motor_time,uint8_t dir)
{
	for(char i=0;i<8;i++)
	{
		GPIO_Control(i,dir);
		rt_thread_mdelay(motor_time);
	}
}
//minrangle 1   maxranle +00    
//mintime 1     
void motor(float angle,uint8_t time,uint8_t dir)
{
	static float num;
	num = (round_num/360.0)*angle;
	for(int j=0;j<(int)num;j++)
	{
			for(char i=0;i<8;i++)
			{
				GPIO_Control(i,dir);
				rt_thread_mdelay(time);
			}
	}
}

	