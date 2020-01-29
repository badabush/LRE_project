#include <UART_com.h>


void UARTGPIOInit(void) {
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;

	//gpio for usart, port A pins 9 and 10
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//configure USART1 Pins for RX and TX
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
	gpioInitStruct.GPIO_OType = GPIO_OType_PP;
	gpioInitStruct.GPIO_Pin = UART_TX | UART_RX;
	gpioInitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_Init(GPIOA, &gpioInitStruct);
	GPIO_PinAFConfig(PORT, UART_PinSource_RX, UART_AF);
	GPIO_PinAFConfig(PORT, UART_PinSource_TX, UART_AF);

	/*Enable USART1 IRQ*/
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;
	nvicInitStruct.NVIC_IRQChannelPriority = 0;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInitStruct);

	usartInitStruct.USART_BaudRate = 115200;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usartInitStruct.USART_Parity = USART_Parity_No;
	usartInitStruct.USART_StopBits = USART_StopBits_1;
	usartInitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART1, &usartInitStruct);
	USART_Cmd(USART1, ENABLE);
	/* Enable RXNE interrupt */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/* Enable TXNE interrupt */
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	/* Enable USART1 global interrupt */
//	NVIC_EnableIRQ(USART1_IRQn);
}

char OUT_rate[80]; // what to send

void SendString(char *str) {
//	USART_ClearITPendingBit(USART1, USART_IT_TXE);
	uint8_t i = 0;
	while (str[i] != '\0') {
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
			;
		USART_SendData(USART1, str[i]);
		i++;
	}
	USART_ClearITPendingBit(USART1, USART_IT_TC);
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);

}

unsigned char cnt = 0;
void USART1_IRQHandler(void) {

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		if (RX_flag == 0) {
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			char t = USART1->RDR;
			received_string[cnt++] = t;
			if (t == '\n') {
//			/*clean up \n when in first position*/
//			if (received_string[0] == '\n') {
//				memmove(received_string, received_string + 1,
//						strlen(received_string));
//			}
				RX_flag = 1;
				SendString(received_string);
//				clearRXBuffer();
				//TODO:replace \r\n with \0
//			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
			}
		}

	}
}

void clearRXBuffer(void) {
	int i;
	for (i = 0; i < cnt; i++)
		received_string[i] = 0;
	cnt = 0;
}

