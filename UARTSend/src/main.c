/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"
#include "lre_gyro.h"
#include "lre_gyro.c"
#include "math.h"
#include "time.h"
#include "stdio.h"

void my_sleep(int secs) {
  #define STEPS_PER_SEC 350000
  unsigned int i,s;
  for (s=0; s < secs; s++) {
    for (i=0; i < STEPS_PER_SEC; i++) {
       // skip CPU cycle or any other statement(s) for making loop
       // untouched by C compiler code optimizations
    }
  }
}


void gpioInit(USART_TypeDef* USARTx){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
	gpioInitStruct.GPIO_OType = GPIO_OType_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpioInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOA, &gpioInitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

	USART_InitTypeDef usartInitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	usartInitStruct.USART_BaudRate = 115200;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usartInitStruct.USART_Parity = USART_Parity_No;
	usartInitStruct.USART_StopBits = USART_StopBits_1;
	usartInitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USARTx, &usartInitStruct);
	USART_Cmd(USARTx, ENABLE);
}


char xyz; // what to receive
char OUT_rate[80];// what to send

void SendString(USART_TypeDef* USARTx, char *str){
	uint8_t i = 0;
	while (str[i] != '\0'){
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
		USART_SendData(USARTx, str[i]);

		i++;
	}
}

int main(void)
{
	gpioInit(USART1);
	my_sleep(2);
	lre_gyro_init();
	SendString(USART1, "Initialization done.\n");
	my_sleep(2);
	while(1){
		my_sleep(1); // wait _ seconds
		lre_gyro_requestRate();
		while (lre_gyro.status != lre_gyro_status_newData);
		sprintf(OUT_rate, "x: %6.2f   y: %6.2f   z: %6.2f\n", lre_gyro.rate.x, lre_gyro.rate.y, lre_gyro.rate.z); // @suppress("Float formatting support")
		SendString(USART1, OUT_rate);
		xyz = USART_ReceiveData(USART1);
		}
}
