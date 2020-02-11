#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f072b_discovery.h"
#include "stdio.h"

#define array_len 600
#define ds_multiplier 177
#define cell 20

int extern ds;
int extern moving;

void substring(char s[], char sub[], int p, int l);

int sonar_filtering(int ds, int dsarray[array_len], int i, int filled);

void Array_sort(int *array, int n);

int Find_median(int array[], int n);

void wait_ds(void);
