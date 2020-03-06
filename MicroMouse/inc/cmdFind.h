#include <moves.h>
#include <maze.h>
#include <stdbool.h>

#define maxl 99

int currCell, prevCell;
int path[maxl];

extern int dist_C;
extern int dist_L;
extern int dist_R;

extern int wall_R;
extern int wall_C;
extern int wall_L;
extern int finalpath[50];
extern int counter;

bool hasNext;
extern void Maze(void);
extern void cmd_shake(void);
//function declaration
void cmd_search(int start, int finish);
void cmd_find(int start, int finish, int counter);
void scan(void);
void clearNodes(void);
