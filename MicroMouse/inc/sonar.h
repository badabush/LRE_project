#include "stm32f0xx_gpio.h"
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"
#include "gpio_init.h"

#define array_len 30

extern int status_flag;
extern int sonar_flag;

extern int dist_R;
extern int dist_C;
extern int dist_L;

extern int filt_R;
extern int filt_C;
extern int filt_L;

/*Sonar flag:
 * flag 0 - check L
 * flag 1 - check R
 * flag 2 - check C
 * */

void SonarInit(void);
void EXTI4_15_IRQHandler(void);
