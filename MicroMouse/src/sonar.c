/**
 ******************************************************************************
 * @file    main.c
 * @author  Ga Man Liang
 * @version V1.0
 * @date    13-December-2019
 * @brief   Script for distance measurement with HC-SR04 using interrupt handlers.
 ******************************************************************************
 */

/* Ports on STM32:
 * CENTER SONAR
 * HCSR04 ECHO: PC11
 * HCSR04 TRIG: PC12
 * UART SERIAL PORT config:
 * Baudrate: 115200, Databits: 8, Parity: none, Stop Bits: 1
 * */

#include <sonar.h>

void SonarCInit(void) {
	/*Enable Port for Timer*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	/*Enable Port for Timer*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	/*SYSCFG clock enable*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	/*TIM clock enable*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/*GPIO inits for echo and trigger*/

	//Echo
	GPIO_InitTypeDef gpioEchoStruct;
	gpioEchoStruct.GPIO_Mode = GPIO_Mode_IN;
	gpioEchoStruct.GPIO_OType = GPIO_OType_PP;
	gpioEchoStruct.GPIO_Pin = GPIO_Pin_11;
	gpioEchoStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioEchoStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOC, &gpioEchoStruct);

	//tigger GPIO
	GPIO_InitTypeDef gpioTrigStruct;
	gpioTrigStruct.GPIO_Mode = GPIO_Mode_AF;
	gpioTrigStruct.GPIO_OType = GPIO_OType_PP;
	gpioTrigStruct.GPIO_Pin = GPIO_Pin_3;
	gpioTrigStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioTrigStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOB, &gpioTrigStruct);
	//configure AF for b-pin4
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_2);
	/* trigger function not on TIM
	 * solution:
	 * */

	TIM_TimeBaseInitTypeDef timerInitStruct;
	timerInitStruct.TIM_ClockDivision = 0;
	timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStruct.TIM_Period = 50000 - 1;
	timerInitStruct.TIM_Prescaler = SystemCoreClock / 500000 - 1;
	timerInitStruct.TIM_RepetitionCounter = 0;

	/*EXTI configurations*/
	EXTI_InitTypeDef extiInitStruct;
	extiInitStruct.EXTI_Line = EXTI_Line11;
	extiInitStruct.EXTI_LineCmd = ENABLE;
	extiInitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	extiInitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&extiInitStruct);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource11);
	//activate EXTI interrupt handler via NVIC
	NVIC_EnableIRQ(EXTI4_15_IRQn);
	/*Initialize PWM*/
	TIM_OCInitTypeDef ocInitStruct;
	ocInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
	ocInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Set;
	ocInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	ocInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	ocInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	ocInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	ocInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
	ocInitStruct.TIM_Pulse = 5;
	TIM_OC1Init(TIM2, &ocInitStruct);

	TIM_TimeBaseInit(TIM2, &timerInitStruct);

	TIM_Cmd(TIM2, ENABLE);
}

void EXTI4_15_IRQHandler(void) {
	/*Interrupt handler for EXTI 4-15*/
	uint16_t t_echo;
	uint16_t dist;
//	if (status_flag == 4) {
		SendString("EXTI C flag 4.\n");
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11) == SET) {
			//rising trigger
			t0 = TIM_GetCounter(TIM2);
		} else {
			t9 = TIM_GetCounter(TIM2);
			t_echo = t9 - t0;
			dist = t_echo * 0.034;
			OUT_dist = itoa(dist);
			SendString(OUT_dist);
		}
//	}
	EXTI_ClearITPendingBit(EXTI_Line11);
}
