/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2019
 * @brief   Default main function.
 ******************************************************************************
 */

#include <StepMotorR.h>

uint8_t step_counterR = 0;

void RMotorGPIOInit() {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioInitStruct.GPIO_OType = GPIO_OType_PP;
	gpioInitStruct.GPIO_Pin = R1 | R2 | R3 | R4;
	gpioInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOC, &gpioInitStruct);
}

void RMotorTIMInit() {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);

	//enable tim16 GPIOB
	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_8;
	gpioInitStruct.GPIO_OType = GPIO_OType_PP;
	gpioInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOB, &gpioInitStruct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_2);

	TIM_TimeBaseInitTypeDef timerInitStruct;
	timerInitStruct.TIM_ClockDivision = 0;
	timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStruct.TIM_Period = 10 - 1;
	timerInitStruct.TIM_Prescaler = SystemCoreClock / 10000 - 1;
	timerInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM16, &timerInitStruct);
}

//Function for interrupt
void RMotorIRT() {
	//set interrupt
	TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);
	//setup nvic for interrupt
	NVIC_EnableIRQ(TIM16_IRQn);
	TIM_Cmd(TIM16, ENABLE);
}

void TIM16_IRQHandler(void) {
	TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
	// increase or decrease step counter, depending on the // rotation direction
	while (R_cmd != 0) {
		SendString("R moving.\n");
		switch (step_counterR) {
		case 0:
			GPIO_SetBits(stpport, R1);
			GPIO_ResetBits(stpport, R2 | R3 | R4);

			if (Rrot_dir == 0) {
				step_counterR++;
			} else {
				step_counterR--;
			}
			break;
		case 1:
			GPIO_SetBits(stpport, R1 | R2);
			GPIO_ResetBits(stpport, R3 | R4);

			if (Rrot_dir == 0) {
				step_counterR++;
			} else {
				step_counterR--;
			}
			break;
		case 2:
			GPIO_SetBits(stpport, R2);
			GPIO_ResetBits(stpport, R1 | R3 | R4);

			if (Rrot_dir == 0) {
				step_counterR++;
			} else {
				step_counterR--;
			}
			break;
		case 3:
			GPIO_SetBits(stpport, R2 | R3);
			GPIO_ResetBits(stpport, R1 | R4);
			step_counterR++;
			break;
		case 4:
			GPIO_SetBits(stpport, R3);
			GPIO_ResetBits(stpport, R2 | R1 | R4);

			if (Rrot_dir == 0) {
				step_counterR++;
			} else {
				step_counterR--;
			}
			break;
		case 5:
			GPIO_SetBits(stpport, R3 | R4);
			GPIO_ResetBits(stpport, R2 | R1);

			if (Rrot_dir == 0) {
				step_counterR++;
			} else {
				step_counterR--;
			}
			break;
		case 6:
			GPIO_SetBits(stpport, R4);
			GPIO_ResetBits(stpport, R2 | R3 | R1);

			if (Rrot_dir == 0) {
				step_counterR++;
			} else {
				step_counterR--;
			}
			break;
		case 7:
			GPIO_SetBits(stpport, R1 | R4);
			GPIO_ResetBits(stpport, R2 | R3);

			if (Rrot_dir == 0) {
				step_counterR++;
			} else {
				step_counterR--;
			}
			break;
		default:
			if (step_counterR == -1) {
				step_counterR = 7;
			} else {
				step_counterR = 0;
			}
			break;
		}
		R_cmd--;
	}
}

