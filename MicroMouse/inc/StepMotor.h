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

#define L4 GPIO_Pin_6
#define L3 GPIO_Pin_7
#define L2 GPIO_Pin_8
#define L1 GPIO_Pin_9

#define stpport GPIOC

extern int R_cmd;
extern int Rrot_dir;
extern int L_cmd;
extern int Lrot_dir;
extern int ds;

void RMotorGPIOInit(void);
void RMotorTIMInit(void);
void RMotorIRT(void);
//void TIM16_IRQHandler(void);
