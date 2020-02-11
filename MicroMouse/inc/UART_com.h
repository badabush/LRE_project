//#ifndef _UART_com_
//#define _UART_com_

#include "stm32f0xx_gpio.h"
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"
#include <string.h>
#include <wait.h>


#define UART_TX GPIO_Pin_9
#define UART_RX GPIO_Pin_10
#define UART_PinSource_TX GPIO_PinSource9
#define UART_PinSource_RX GPIO_PinSource10
#define UART_AF GPIO_AF_1
#define PORT GPIOA


extern char received_string[];
extern int RX_flag;
extern int TX_flag;
void UARTGPIOInit(void);
void SendString(char *str);
void ReceiveString(void);


#define MAX_LEN 20
void USART1_IRQHandler(void);
void clearRXBuffer(void); //clear reception buffer
