/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2019
 * @brief   Default main function.
 ******************************************************************************
 */

#include <StepMotorL.h>

uint8_t step_counterL = 0;

void LMotorGPIOInit() {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioInitStruct.GPIO_OType = GPIO_OType_PP;
	gpioInitStruct.GPIO_Pin = L1 | L3 | L2 | L4;
	gpioInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOC, &gpioInitStruct);
}

void LMotorTIMInit() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStruct;
	timerInitStruct.TIM_ClockDivision = 0;
	timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStruct.TIM_Period = 10 - 1;
	timerInitStruct.TIM_Prescaler = SystemCoreClock / 10000 - 1;
	timerInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM14, &timerInitStruct);
}

//Function for interrupt
void LMotorIRT() {
	//set interrupt
	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
	//setup nvic for interrupt
	NVIC_EnableIRQ(TIM14_IRQn);
	TIM_Cmd(TIM14, ENABLE);
}

void TIM14_IRQHandler(void) {
	TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
	// increase or decrease step counter, depending on the // rotation direction
	//check for rotation direction within switch cases

	while (L_cmd != 0) {
		SendString("L moving.\n");
		switch (step_counterL) {
		case 0:
			GPIO_SetBits(stpport, L1);
			GPIO_ResetBits(stpport, L2 | L3 | L4);

			if (Lrot_dir == 0) {
				step_counterL++;
			} else {
				step_counterL--;
			}
			break;
		case 1:
			GPIO_SetBits(stpport, L1 | L2);
			GPIO_ResetBits(stpport, L3 | L4);

			if (Lrot_dir == 0) {
				step_counterL++;
			} else {
				step_counterL--;
			}
			break;
		case 2:
			GPIO_SetBits(stpport, L2);
			GPIO_ResetBits(stpport, L1 | L3 | L4);

			if (Lrot_dir == 0) {
				step_counterL++;
			} else {
				step_counterL--;
			}
			break;
		case 3:
			GPIO_SetBits(stpport, L2 | L3);
			GPIO_ResetBits(stpport, L1 | L4);
			step_counterL++;
			break;
		case 4:
			GPIO_SetBits(stpport, L3);
			GPIO_ResetBits(stpport, L2 | L1 | L4);

			if (Lrot_dir == 0) {
				step_counterL++;
			} else {
				step_counterL--;
			}
			break;
		case 5:
			GPIO_SetBits(stpport, L3 | L4);
			GPIO_ResetBits(stpport, L2 | L1);

			if (Lrot_dir == 0) {
				step_counterL++;
			} else {
				step_counterL--;
			}
			break;
		case 6:
			GPIO_SetBits(stpport, L4);
			GPIO_ResetBits(stpport, L2 | L3 | L1);

			if (Lrot_dir == 0) {
				step_counterL++;
			} else {
				step_counterL--;
			}
			break;
		case 7:
			GPIO_SetBits(stpport, L1 | L4);
			GPIO_ResetBits(stpport, L2 | L3);

			if (Lrot_dir == 0) {
				step_counterL++;
			} else {
				step_counterL--;
			}
			break;
		default:
			if (step_counterL == -1) {
				step_counterL = 7;
			} else {
				step_counterL = 0;
			}
			break;
		}
		L_cmd--;
	}
}
