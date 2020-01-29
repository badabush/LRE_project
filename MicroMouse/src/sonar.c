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

#include "sonar.h"
char center_dist[50];
char right_dist[50];
char left_dist[50];

int t0_R = 0;
int t9_R = 0;
int dist_R = 0;
//
int t0_L = 0;
int t9_L = 0;
int dist_L = 0;

int t0_C = 0;
int t9_C = 0;
int dist_C = 0;

uint16_t t_echo_R;
uint16_t t_echo_L;
uint16_t t_echo_C;

void SonarInit(void) {

	//Sonar L
	gpio_pinSetup(GPIOB, GPIO_Pin_6, GPIO_Mode_IN, GPIO_OType_PP,
			GPIO_PuPd_NOPULL, GPIO_Speed_Level_1);
	gpio_pinSetup_AF(GPIOB, GPIO_Pin_4, GPIO_AF_1, GPIO_OType_PP,
			GPIO_PuPd_NOPULL, GPIO_Speed_Level_1);
	gpio_pinSetup_interrupt(GPIOB, GPIO_Pin_6, EXTI_Trigger_Rising_Falling, 0);
	TIM_init(TIM3);

	//Sonar C
	gpio_pinSetup(GPIOC, GPIO_Pin_11, GPIO_Mode_IN, GPIO_OType_PP,
			GPIO_PuPd_NOPULL, GPIO_Speed_Level_1);
	gpio_pinSetup_AF(GPIOB, GPIO_Pin_3, GPIO_AF_2, GPIO_OType_PP,
			GPIO_PuPd_NOPULL, GPIO_Speed_Level_1);
	gpio_pinSetup_interrupt(GPIOC, GPIO_Pin_11, EXTI_Trigger_Rising_Falling, 0);
	TIM_init(TIM2);

	//Sonar R
	gpio_pinSetup(GPIOC, GPIO_Pin_4, GPIO_Mode_IN, GPIO_OType_PP,
			GPIO_PuPd_NOPULL, GPIO_Speed_Level_1);
	gpio_pinSetup_AF(GPIOB, GPIO_Pin_9, GPIO_AF_2, GPIO_OType_PP,
			GPIO_PuPd_NOPULL, GPIO_Speed_Level_1);
	gpio_pinSetup_interrupt(GPIOC, GPIO_Pin_4, EXTI_Trigger_Rising_Falling, 0);
	TIM_init(TIM17);

}

void EXTI4_15_IRQHandler(void) {
	if (status_flag == 4) {
		if (sonar_flag == 1) {
			if (EXTI_GetFlagStatus(EXTI_Line6)) {

				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == SET) {
					//rising trigger
					t0_L = TIM_GetCounter(TIM3);

				} else {
					t9_L = TIM_GetCounter(TIM3);

					t_echo_L = t9_L - t0_L;
					dist_L = t_echo_L * 0.034;
					if (dist_L > 400)
						dist_L = 0;
					sonar_flag = 2;
					sprintf(left_dist, "distance L %5i cm;", dist_L);
					SendString(left_dist);
					TIM_Cmd(TIM3, DISABLE);
					TIM_Cmd(TIM2, ENABLE);
				}
			} //getflagstatus_line6
		}
		if (sonar_flag == 2) {
			if (EXTI_GetFlagStatus(EXTI_Line11)) {
				if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11) == SET) {
					//rising trigger
					t0_C = TIM_GetCounter(TIM2);

				} else {
					t9_C = TIM_GetCounter(TIM2);

					t_echo_C = t9_C - t0_C;
					dist_C = t_echo_C * 0.034;
					if (dist_C > 400)
						dist_C = 0;
					sonar_flag = 3;
					sprintf(center_dist, "C %5i cm;", dist_C);
					SendString(center_dist);
					TIM_Cmd(TIM2, DISABLE);
					TIM_Cmd(TIM17, ENABLE);
				}
			} //getflagstatus_line4
		}
		if (sonar_flag == 3) {
			if (EXTI_GetFlagStatus(EXTI_Line4)) {
				if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == SET) {
					//rising trigger
					t0_R = TIM_GetCounter(TIM17);

				} else {
					t9_R = TIM_GetCounter(TIM17);

					t_echo_R = t9_R - t0_R;
					dist_R = t_echo_R * 0.034;
					if (dist_R > 400)
						dist_R = 0;
					sonar_flag = 0;
					sprintf(right_dist, "R %5i cm\n", dist_R);
					SendString(right_dist);
					status_flag = 0;
					TIM_Cmd(TIM17, DISABLE);
//			TIM_Cmd(TIM3, ENABLE);
				}
			} //getflagstatus_line4
		}
		EXTI_ClearITPendingBit(EXTI_Line4);
		EXTI_ClearITPendingBit(EXTI_Line11);
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
} //EXTI4_15

