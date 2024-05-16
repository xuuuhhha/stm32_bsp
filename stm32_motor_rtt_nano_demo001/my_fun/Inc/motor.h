#ifndef __MOTOR_H
#define __MOTOR_H
#include "gpio.h"
#include <stdbool.h>
#include "main.h"
#include "stm32f1xx_hal_gpio.h"

enum 
{
    MOTOR_A=1,
    MOTOR_B,
    MOTOR_C,
    MOTOR_D,
};

enum GPIOA_PIN_X
{
    GPIOA_PIN_0=0x0001,
    GPIOA_PIN_1=0x0002,
    GPIOA_PIN_2,
    GPIOA_PIN_3,
    GPIOA_PIN_4,
    GPIOA_PIN_5,
    GPIOA_PIN_6,
    GPIOA_PIN_7,
    GPIOA_PIN_8,
    GPIOA_PIN_9,
    GPIOA_PIN_10,
    GPIOA_PIN_11,
    GPIOA_PIN_12,
    GPIOA_PIN_13,
    GPIOA_PIN_14,
    GPIOA_PIN_15,
};

#define MOTOR_IN1 GPIOA_PIN_9
#define MOTOR_IN2 GPIOA_PIN_10
#define MOTOR_IN3 GPIOA_PIN_11
#define MOTOR_IN4 GPIOA_PIN_12
#define MOTOR_TIME 1000 //1ms

void GPIO_Control(uint8_t MOTOR_INX ,uint8_t dir);
void motor_run(uint32_t motor_time,uint8_t dir);
void motor(float rangle,uint8_t time,uint8_t dir);


#endif