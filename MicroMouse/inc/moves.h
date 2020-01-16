
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"

extern int ds;
extern int Lrot_dir;
extern int Rrot_dir;

void cmd_forward(void);
void cmd_back(void);
void cmd_Lturn(void);
void cmd_Rturn(void);
