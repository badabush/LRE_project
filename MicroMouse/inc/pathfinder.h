#include <moves.h>
#include <maze.h>
#include <stdbool.h>

#define maxl 100

extern int dist_C;
extern int dist_L;
extern int dist_R;

extern void Maze(void);
extern void cmd_shake(void);

bool hasNext;
//function declaration
void permutate(int currCell, int prevCell);
void drive(int currCell, int prevCell);
void cmd_pathfinder(int start, int finish);
