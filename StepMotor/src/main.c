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


#define blau GPIO_Pin_3
#define gelb GPIO_Pin_4
#define pink GPIO_Pin_5
#define orange GPIO_Pin_6
#define stpport GPIOB

int8_t stp_cnt = 0;
#define step_counter stp_cnt

void gpioInit(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_OUT;
	gpioInitStruct.GPIO_OType = GPIO_OType_PP;
	gpioInitStruct.GPIO_Pin = blau | gelb | pink | orange;
	gpioInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOB, &gpioInitStruct);
}

void TIMInit(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef timerInitStruct;
	timerInitStruct.TIM_ClockDivision = 0;
	timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStruct.TIM_Period = 2 - 1;
	timerInitStruct.TIM_Prescaler =	SystemCoreClock / 2000 - 1;
	timerInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStruct);
	TIM_Cmd(TIM3, ENABLE);

}

//Function for interrupt
void intrpt(){
	//set interrupt
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//setup nvic for interrupt
	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void) {
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// increase or decrease step counter, depending on the // rotation direction
	switch (step_counter) {
		case 0:
			GPIO_SetBits(stpport, blau);
			GPIO_ResetBits(stpport, pink | gelb | orange);
			step_counter++;
			break;
		case 1:
			GPIO_SetBits(stpport, blau | pink);
			GPIO_ResetBits(stpport, gelb | orange);
			step_counter++;
			break;
		case 2:
			GPIO_SetBits(stpport, pink);
			GPIO_ResetBits(stpport, blau | gelb | orange);
			step_counter++;
			break;
		case 3:
			GPIO_SetBits(stpport, pink | gelb);
			GPIO_ResetBits(stpport, blau | orange);
			step_counter++;
			break;
		case 4:
			GPIO_SetBits(stpport, gelb);
			GPIO_ResetBits(stpport, pink | blau | orange);
			step_counter++;
			break;
		case 5:
			GPIO_SetBits(stpport, gelb | orange);
			GPIO_ResetBits(stpport, pink | blau);
			step_counter++;
			break;
		case 6:
			GPIO_SetBits(stpport, orange);
			GPIO_ResetBits(stpport, pink | gelb | blau);
			step_counter++;
			break;
		case 7:
			GPIO_SetBits(stpport, blau | orange);
			GPIO_ResetBits(stpport, pink | gelb);
			step_counter++;
			break;
		default:
			step_counter = 0;
	}
}


int main(void){
	gpioInit();
	TIMInit();
	intrpt();
	while(1);

}
