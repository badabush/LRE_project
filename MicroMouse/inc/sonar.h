#include "stm32f0xx_gpio.h"
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"
#include "gpio_init.h"

#define array_len 50

extern int status_flag;
extern int sonar_flag;

extern int dist_R;
extern int dist_C;
extern int dist_L;

extern int wall_R;
extern int wall_C;
extern int wall_L;

void SonarInit(void);
void EXTI4_15_IRQHandler(void);
