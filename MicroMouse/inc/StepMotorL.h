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


#define L1 GPIO_Pin_6
#define L2 GPIO_Pin_7
#define L3 GPIO_Pin_8
#define L4 GPIO_Pin_9
#define stpport GPIOC

extern int ds;
extern int Lrot_dir;

int cycle = 4096; //cycles required for moving one distance

void LMotorGPIOInit(void);
void LMotorTIMInit(void);
void LMotorIRT(void);
void TIM14_IRQHandler(void);
