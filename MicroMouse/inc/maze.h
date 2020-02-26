//Here the maze will be defined by building a struct for every cell, which contains all necessary information
//in code every cell gets combination of a number and a letter; see google docs for clarification

#include "stdio.h"
#include <stdlib.h>

#define cells 50 // number of cells

//extern void SendString(char *str);


void Maze(void);
void Maze2(int finish);


struct zelle {
	int ini[4]; //={2,0,0,0}; // every entry a neighbour; r front l back; 0 = wall; 1,2,...,49 possible cell (see gdocs); init state as seen in gdocs
	int perm[4]; //={0,0,0,0}; // permutated entries from ini, eg if mouse comes from left to cell 1 (a1), perm for a1 becomes {0,0,0,2}
//	int prevCell[4];//={0,0,0,0}; // ini from previous cell to determ orientation of mouse
	//for better algorithm
	int X;
	int Y;	//Position by x and y
	int distance; //=abs[ZielX- X]+abs[ZielY-Y]; //value from the Target by X and Y, doesnt think of walls
	int flag; //Anzeigen ob Feld besucht wurde =1, Wenn Feld zweimal besucht oder Sackgasse =2
};

//struct zelle maze[cells]; // a struct maze which contains a list, on first place: cell 1 (a1)

//structur ini        1
//				    2	0
//					  3
struct zelle maze[cells]; // a struct maze which contains a list, on first place: cell 1 (a1)
