
#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"
#include "tools.h"
#include "wait.h"

#define std_steps 2000
#define std_turn 15.5
#define ds_cell 20

extern int ds;
extern int Lrot_dir;
extern int Rrot_dir;

extern int R_cmd;
extern int L_cmd;

extern int wall_C;

//distances from sensors
extern int dist_R;
extern int dist_C;
extern int dist_L;

extern int des_dist;

void cmd_forward(void);
void cmd_backward(void);
void cmd_Lturn(void);
void cmd_Rturn(void);
void cmd_park(void);
void cmd_follow(void);
