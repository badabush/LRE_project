#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>

volatile uint32_t extern Milliseconds, Seconds;
void DelayMil(uint32_t MilS);

//Delay function for second delay
void DelaySec(uint32_t S);
