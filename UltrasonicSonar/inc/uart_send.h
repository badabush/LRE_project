#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"

void UARTGPIOInit(USART_TypeDef* USARTx){
	//gpio for usart, port A pins 9 and 10
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
