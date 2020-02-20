#include <moves.h>
#include <maze.h>

#define maxl 50
int a,counter=0,finishBool=0,iteration=0,i,j,k,l,newl;// maxl = max length of path= (number of cells mouse drives through a complete drive through whole maze)+1
int currCell,prevCell;
int path[maxl];
