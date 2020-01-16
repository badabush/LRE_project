#include "stm32f0xx.h"
#include "stm32f072b_discovery.h"

extern int status_flag;
uint16_t t0;
uint16_t t9;

void RCCInit(void);
void GPIOInit(void);
void TIMInit(void);
void EXTI4_15_IRQHandler(void);

