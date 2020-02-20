//Here the maze will be defined by building a struct for every cell, which contains all necessary information
//in code every cell gets combination of a number and a letter; see google docs for clarification

#include "stdio.h"

#define cells 49 // Zellenanzahl

struct zelle {
	int ini[4];//={2,0,0,0}; // every entry a neighbour; r front l back; 0 = wall; 1,2,...,49 possible cell (see gdocs); init state as seen in gdocs
	int perm[4];//={0,0,0,0}; // permutated entries from ini, eg if mouse comes from left to cell 1 (a1), perm for a1 becomes {0,0,0,2}
	int prevCell[4];//={0,0,0,0}; // ini from previous cell to determ orientation of mouse
};

struct zelle maze[cells]; // a struct maze which contains a list, on first place: cell 1 (a1)

void Maze(){
	maze[0].ini[0] = 2; maze[0].ini[1] = 0; maze[0].ini[2] = 0; maze[0].ini[3] = 0; //a1
    maze[1].ini[0] = 3; maze[1].ini[1] = 0; maze[1].ini[2] = 1; maze[1].ini[3] = 0; //b1
	maze[2].ini[0] = 4; maze[2].ini[1] = 0; maze[2].ini[2] = 2; maze[2].ini[3] = 0; //c1
    maze[3].ini[0] = 0; maze[3].ini[1] = 0; maze[3].ini[2] = 3; maze[3].ini[3] = 11; //d1
	maze[4].ini[0] = 6; maze[4].ini[1] = 0; maze[4].ini[2] = 0; maze[4].ini[3] = 12; //e1
    maze[5].ini[0] = 7; maze[5].ini[1] = 0; maze[5].ini[2] = 5; maze[5].ini[3] = 0; //f1
    maze[6].ini[0] = 3; maze[6].ini[1] = 0; maze[6].ini[2] = 6; maze[6].ini[3] = 14; //g1

	maze[7].ini[0] = 0; maze[7].ini[1] = 0; maze[7].ini[2] = 0; maze[7].ini[3] = 15; //a2
    maze[8].ini[0] = 10; maze[8].ini[1] = 0; maze[8].ini[2] = 0; maze[8].ini[3] = 16; //b2
	maze[9].ini[0] = 11; maze[9].ini[1] = 0; maze[9].ini[2] = 9; maze[9].ini[3] = 0; //c2
    maze[10].ini[0] = 12; maze[10].ini[1] = 4; maze[10].ini[2] = 10; maze[10].ini[3] = 0; //d2
	maze[11].ini[0] = 13; maze[11].ini[1] = 5; maze[11].ini[2] = 11; maze[11].ini[3] = 0; //e2
    maze[12].ini[0] = 0; maze[12].ini[1] = 0; maze[12].ini[2] = 12; maze[12].ini[3] = 20; //f2
    maze[13].ini[0] = 0; maze[13].ini[1] = 7; maze[13].ini[2] = 0; maze[13].ini[3] = 21; //g2

	maze[14].ini[0] = 16; maze[14].ini[1] = 8; maze[14].ini[2] = 0; maze[14].ini[3] = 22; //a3
    maze[15].ini[0] = 17; maze[15].ini[1] = 9; maze[15].ini[2] = 15; maze[15].ini[3] = 0; //b3
	maze[16].ini[0] = 0; maze[16].ini[1] = 0; maze[16].ini[2] = 16; maze[16].ini[3] = 0; //c3
    maze[17].ini[0] = 19; maze[17].ini[1] = 0; maze[17].ini[2] = 0; maze[17].ini[3] = 25; //d3
	maze[18].ini[0] = 0; maze[18].ini[1] = 0; maze[18].ini[2] = 18; maze[18].ini[3] = 26; //e3
    maze[19].ini[0] = 0; maze[19].ini[1] = 13; maze[19].ini[2] = 0; maze[19].ini[3] = 27; //f3
    maze[20].ini[0] = 0; maze[20].ini[1] = 14; maze[20].ini[2] = 0; maze[20].ini[3] = 28; //g3

	maze[21].ini[0] = 23; maze[21].ini[1] = 15; maze[21].ini[2] = 0; maze[21].ini[3] = 29; //a4
    maze[22].ini[0] = 24; maze[22].ini[1] = 0; maze[22].ini[2] = 22; maze[22].ini[3] = 0; //b4
	maze[23].ini[0] = 0; maze[23].ini[1] = 0; maze[23].ini[2] = 21; maze[23].ini[3] = 31; //c4
    maze[24].ini[0] = 0; maze[24].ini[1] = 18; maze[24].ini[2] = 0; maze[24].ini[3] = 0; //d4
	maze[25].ini[0] = 0; maze[25].ini[1] = 19; maze[25].ini[2] = 0; maze[25].ini[3] = 33; //e4
    maze[26].ini[0] = 0; maze[26].ini[1] = 20; maze[26].ini[2] = 0; maze[26].ini[3] = 0; //f4
    maze[27].ini[0] = 0; maze[27].ini[1] = 21; maze[27].ini[2] = 0; maze[27].ini[3] = 0; //g4

	maze[28].ini[0] = 0; maze[28].ini[1] = 22; maze[28].ini[2] = 0; maze[28].ini[3] = 36; //a5
    maze[29].ini[0] = 0; maze[29].ini[1] = 0; maze[29].ini[2] = 0; maze[29].ini[3] = 37; //b5
	maze[30].ini[0] = 0; maze[30].ini[1] = 24; maze[30].ini[2] = 0; maze[30].ini[3] = 38; //c5
    maze[31].ini[0] = 33; maze[31].ini[1] = 0; maze[31].ini[2] = 0; maze[31].ini[3] = 0; //d5
	maze[32].ini[0] = 34; maze[32].ini[1] = 26; maze[32].ini[2] = 32; maze[32].ini[3] = 0; //e5
    maze[33].ini[0] = 35; maze[33].ini[1] = 0; maze[33].ini[2] = 33; maze[33].ini[3] = 41; //f5
    maze[34].ini[0] = 0; maze[34].ini[1] = 0; maze[34].ini[2] = 34; maze[34].ini[3] = 0; //g5

	maze[35].ini[0] = 0; maze[35].ini[1] = 29; maze[35].ini[2] = 0; maze[35].ini[3] = 43; //a6
    maze[36].ini[0] = 0; maze[36].ini[1] = 30; maze[36].ini[2] = 0; maze[36].ini[3] = 44; //b6
	maze[37].ini[0] = 39; maze[37].ini[1] = 31; maze[37].ini[2] = 0; maze[37].ini[3] = 0; //c6
    maze[38].ini[0] = 0; maze[38].ini[1] = 0; maze[38].ini[2] = 38; maze[38].ini[3] = 46; //d6
	maze[39].ini[0] = 41; maze[39].ini[1] = 0; maze[39].ini[2] = 0; maze[39].ini[3] = 47; //e6
    maze[40].ini[0] = 0; maze[40].ini[1] = 34; maze[40].ini[2] = 40; maze[40].ini[3] = 48; //f6
    maze[41].ini[0] = 0; maze[41].ini[1] = 0; maze[41].ini[2] = 0; maze[41].ini[3] = 49; //g6

	maze[42].ini[0] = 44; maze[42].ini[1] = 36; maze[42].ini[2] = 0; maze[42].ini[3] = 0; //a7
    maze[43].ini[0] = 45; maze[43].ini[1] = 37; maze[43].ini[2] = 43; maze[43].ini[3] = 0; //b7
	maze[44].ini[0] = 0; maze[44].ini[1] = 0; maze[44].ini[2] = 44; maze[44].ini[3] = 0; //c7
    maze[45].ini[0] = 47; maze[45].ini[1] = 39; maze[45].ini[2] = 0; maze[45].ini[3] = 0; //d7
	maze[46].ini[0] = 0; maze[46].ini[1] = 40; maze[46].ini[2] = 46; maze[46].ini[3] = 0; //e7
    maze[47].ini[0] = 49; maze[47].ini[1] = 41; maze[47].ini[2] = 0; maze[47].ini[3] = 0; //f7
    maze[48].ini[0] = 0; maze[48].ini[1] = 42; maze[48].ini[2] = 48; maze[48].ini[3] = 0; //g7
}
