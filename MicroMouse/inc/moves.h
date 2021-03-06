#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"
#include "tools.h"
#include "wait.h"
#include "math.h"

#define std_steps 2000
#define std_turn 15.9

#define adjust_ds 5

#define ds_cell 20
#define ds_multiplier 155;
extern int ds;
extern int Lrot_dir;
extern int Rrot_dir;

extern int R_cmd;
extern int L_cmd;

extern int wall_C;
extern int wall_R;
extern int wall_L;

extern int side;
//distances from sensors
extern int dist_R;
extern int dist_C;
extern int dist_L;

extern int des_dist;

void cmd_forward(int dist);
void cmd_backward(int dist);
void cmd_Lturn(int deg);
void cmd_Rturn(int deg);

void cmd_park(void);
void cmd_follow(int tot_dist);
void adjust(void);
