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
int cnt_R = 0;
//
int t0_L = 0;
int t9_L = 0;
int cnt_L = 0;

int t0_C = 0;
int t9_C = 0;
int cnt_C = 0;
//distance arrays for filtering
int dsarrayR[array_len];
int dsarrayL[array_len];
int dsarrayC[array_len];
//flag if first array is filled
int filled_R = 0;
int filled_C = 0;
int filled_L = 0;

uint16_t t_echo_R;
uint16_t t_echo_L;
uint16_t t_echo_C;

void SonarInit(void) {

	//Sonar R
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

	//Sonar L
	gpio_pinSetup(GPIOC, GPIO_Pin_4, GPIO_Mode_IN, GPIO_OType_PP,
			GPIO_PuPd_NOPULL, GPIO_Speed_Level_1);
	gpio_pinSetup_AF(GPIOB, GPIO_Pin_9, GPIO_AF_2, GPIO_OType_PP,
			GPIO_PuPd_NOPULL, GPIO_Speed_Level_1);
	gpio_pinSetup_interrupt(GPIOC, GPIO_Pin_4, EXTI_Trigger_Rising_Falling, 0);
	TIM_init(TIM17);

	//activate EXTI interrupt handler via NVIC
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM17, ENABLE);

}

void EXTI4_15_IRQHandler(void) {
	if (EXTI_GetFlagStatus(EXTI_Line6)) {

		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == SET) {
			//rising trigger
			t0_R = TIM_GetCounter(TIM3);

		} else {
			t9_R = TIM_GetCounter(TIM3);

			t_echo_R = t9_R - t0_R;
			dist_R = t_echo_R * 0.034;

			//filter distance
			dist_R, cnt_R, filled_R = sonar_filtering(dist_R, dsarrayR, cnt_R,
					filled_R);
			if (dist_R > 30)
				dist_R = 999;
			//wall flag
			if (dist_R < 10)
				wall_R = 1;
			else
				wall_R = 0;
//			char sonar_dist[10];
//			sprintf(sonar_dist, "R: %2i cm;\n", dist_R);
//			SendString(sonar_dist);
		}
		EXTI_ClearITPendingBit(EXTI_Line6);
	} //getflagstatus_line6
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
			//wall flag
			if (dist_C < 10) {
				wall_C = 1;
			} else
				wall_C = 0;
//			char sonar_dist[10];
//			sprintf(sonar_dist, "C: %5i cm", dist_C);
//			SendString(sonar_dist);
		}
		EXTI_ClearITPendingBit(EXTI_Line11);
	} //getflagstatus_line4
	if (EXTI_GetFlagStatus(EXTI_Line4)) {
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == SET) {
			//rising trigger
			t0_L = TIM_GetCounter(TIM17);

		} else {
			t9_L = TIM_GetCounter(TIM17);

			t_echo_L = t9_L - t0_L;
			dist_L = t_echo_L * 0.034;
			dist_L, cnt_L, filled_L = sonar_filtering(dist_L, dsarrayL, cnt_L,
					filled_L);
			if (dist_L > 30)
				dist_L = 999;
			//wall flag
			if (dist_L > 30) {
				dist_L = 999;
			}
			if (dist_L < 10)
				wall_L = 1;
			else
				wall_L = 0;
//			char sonar_dist[10];
//			sprintf(sonar_dist, "L: %2i cm\r\n", dist_L);
//			SendString(sonar_dist);
		} //getflagstatus_line4
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
} //EXTI4_15

