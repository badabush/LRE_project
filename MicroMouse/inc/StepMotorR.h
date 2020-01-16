/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2019
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"
#include "stdio.h"
#include <lre_wait.h>

#define R4 GPIO_Pin_3
#define R3 GPIO_Pin_15
#define R2 GPIO_Pin_14
#define R1 GPIO_Pin_13
#define stpport GPIOC

void RMotorGPIOInit(void);
void RMotorTIMInit(void);
void RMotorIRT(void);
void TIM16_IRQHandler(void);
