/*
 * advancedMoves.h
 *
 *  Created on: 09.02.2020
 *      Author: Willi
 */

extern int dist_L;
extern int dist_C;
extern int dist_R;

int dummy;
int cellDist; // length of a cell

int xCmin= 4; // min distance Center
int xRmin= 15; // min distance R
int xLmin= 15; // min distance L
int xClive; // live dist C
int xRlive; // live dist R
int xLlive; // live dist L
int xCold; // old dist C
int xRold; // old dist R
int xLold; // old dist L
int xLdiff; // difference between current dist to lWall and dist to lWall in previous state

float reqTurn; // required turning angle


int desiredDist; // dist that mouse has to move forward
int movedDist; // dist that mouse has moved forward
