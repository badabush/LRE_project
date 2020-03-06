#include <maze.h>

//Here the maze will be defined by building a struct for every cell, which contains all necessary information
//in code every cell gets combination of a number and a letter; see google docs for clarification

void Maze(void){

	maze[1].ini[0] = 2; maze[1].ini[1] = 0; maze[1].ini[2] = 0; maze[1].ini[3] = 0; //a1
    maze[2].ini[0] = 3; maze[2].ini[1] = 0; maze[2].ini[2] = 1; maze[2].ini[3] = 0; //b1
	maze[3].ini[0] = 4; maze[3].ini[1] = 0; maze[3].ini[2] = 2; maze[3].ini[3] = 0; //c1
    maze[4].ini[0] = 0; maze[4].ini[1] = 0; maze[4].ini[2] = 3; maze[4].ini[3] = 11; //d1
	maze[5].ini[0] = 6; maze[5].ini[1] = 0; maze[5].ini[2] = 0; maze[5].ini[3] = 12; //e1
    maze[6].ini[0] = 7; maze[6].ini[1] = 0; maze[6].ini[2] = 5; maze[6].ini[3] = 0; //f1
    maze[7].ini[0] = 0; maze[7].ini[1] = 0; maze[7].ini[2] = 6; maze[7].ini[3] = 14; //g1

	maze[8].ini[0] = 0; maze[8].ini[1] = 0; maze[8].ini[2] = 0; maze[8].ini[3] = 15; //a2
    maze[9].ini[0] = 10; maze[9].ini[1] = 0; maze[9].ini[2] = 0; maze[9].ini[3] = 16; //b2
	maze[10].ini[0] = 11; maze[10].ini[1] = 0; maze[10].ini[2] = 9; maze[10].ini[3] = 0; //c2
    maze[11].ini[0] = 12; maze[11].ini[1] = 4; maze[11].ini[2] = 10; maze[11].ini[3] = 0; //d2
	maze[12].ini[0] = 13; maze[12].ini[1] = 5; maze[12].ini[2] = 11; maze[12].ini[3] = 0; //e2
    maze[13].ini[0] = 0; maze[13].ini[1] = 0; maze[13].ini[2] = 12; maze[13].ini[3] = 20; //f2
    maze[14].ini[0] = 0; maze[14].ini[1] = 7; maze[14].ini[2] = 0; maze[14].ini[3] = 21; //g2

	maze[15].ini[0] = 16; maze[15].ini[1] = 8; maze[15].ini[2] = 0; maze[15].ini[3] = 22; //a3
    maze[16].ini[0] = 17; maze[16].ini[1] = 9; maze[16].ini[2] = 15; maze[16].ini[3] = 0; //b3
	maze[17].ini[0] = 0; maze[17].ini[1] = 0; maze[17].ini[2] = 16; maze[17].ini[3] = 0; //c3
    maze[18].ini[0] = 19; maze[18].ini[1] = 0; maze[18].ini[2] = 0; maze[18].ini[3] = 25; //d3
	maze[19].ini[0] = 0; maze[19].ini[1] = 0; maze[19].ini[2] = 18; maze[19].ini[3] = 26; //e3
    maze[20].ini[0] = 0; maze[20].ini[1] = 13; maze[20].ini[2] = 0; maze[20].ini[3] = 27; //f3
    maze[21].ini[0] = 0; maze[21].ini[1] = 14; maze[21].ini[2] = 0; maze[21].ini[3] = 28; //g3

	maze[22].ini[0] = 23; maze[22].ini[1] = 15; maze[22].ini[2] = 0; maze[22].ini[3] = 29; //a4
    maze[23].ini[0] = 24; maze[23].ini[1] = 0; maze[23].ini[2] = 22; maze[23].ini[3] = 0; //b4
	maze[24].ini[0] = 0; maze[24].ini[1] = 0; maze[24].ini[2] = 23; maze[24].ini[3] = 31; //c4
    maze[25].ini[0] = 0; maze[25].ini[1] = 18; maze[25].ini[2] = 0; maze[25].ini[3] = 0; //d4
	maze[26].ini[0] = 0; maze[26].ini[1] = 19; maze[26].ini[2] = 0; maze[26].ini[3] = 33; //e4
    maze[27].ini[0] = 0; maze[27].ini[1] = 20; maze[27].ini[2] = 0; maze[27].ini[3] = 0; //f4
    maze[28].ini[0] = 0; maze[28].ini[1] = 21; maze[28].ini[2] = 0; maze[28].ini[3] = 0; //g4

	maze[29].ini[0] = 0; maze[29].ini[1] = 22; maze[29].ini[2] = 0; maze[29].ini[3] = 36; //a5
    maze[30].ini[0] = 0; maze[30].ini[1] = 0; maze[30].ini[2] = 0; maze[30].ini[3] = 37; //b5
	maze[31].ini[0] = 0; maze[31].ini[1] = 24; maze[31].ini[2] = 0; maze[31].ini[3] = 38; //c5
    maze[32].ini[0] = 33; maze[32].ini[1] = 0; maze[32].ini[2] = 0; maze[32].ini[3] = 0; //d5
	maze[33].ini[0] = 34; maze[33].ini[1] = 26; maze[33].ini[2] = 32; maze[33].ini[3] = 0; //e5
    maze[34].ini[0] = 35; maze[34].ini[1] = 0; maze[34].ini[2] = 33; maze[34].ini[3] = 41; //f5
    maze[35].ini[0] = 0; maze[35].ini[1] = 0; maze[35].ini[2] = 34; maze[35].ini[3] = 0; //g5

	maze[36].ini[0] = 0; maze[36].ini[1] = 29; maze[36].ini[2] = 0; maze[36].ini[3] = 43; //a6
    maze[37].ini[0] = 0; maze[37].ini[1] = 30; maze[37].ini[2] = 0; maze[37].ini[3] = 44; //b6
	maze[38].ini[0] = 39; maze[38].ini[1] = 31; maze[38].ini[2] = 0; maze[38].ini[3] = 0; //c6
    maze[39].ini[0] = 0; maze[39].ini[1] = 0; maze[39].ini[2] = 38; maze[39].ini[3] = 46; //d6
	maze[40].ini[0] = 41; maze[40].ini[1] = 0; maze[40].ini[2] = 0; maze[40].ini[3] = 47; //e6
    maze[41].ini[0] = 0; maze[41].ini[1] = 34; maze[41].ini[2] = 40; maze[41].ini[3] = 48; //f6
    maze[42].ini[0] = 0; maze[42].ini[1] = 0; maze[42].ini[2] = 0; maze[42].ini[3] = 49; //g6

	maze[43].ini[0] = 44; maze[43].ini[1] = 36; maze[43].ini[2] = 0; maze[43].ini[3] = 0; //a7
    maze[44].ini[0] = 45; maze[44].ini[1] = 37; maze[44].ini[2] = 43; maze[44].ini[3] = 0; //b7
	maze[45].ini[0] = 0; maze[45].ini[1] = 0; maze[45].ini[2] = 44; maze[45].ini[3] = 0; //c7
    maze[46].ini[0] = 47; maze[46].ini[1] = 39; maze[46].ini[2] = 0; maze[46].ini[3] = 0; //d7
	maze[47].ini[0] = 0; maze[47].ini[1] = 40; maze[47].ini[2] = 46; maze[47].ini[3] = 0; //e7
    maze[48].ini[0] = 49; maze[48].ini[1] = 41; maze[48].ini[2] = 0; maze[48].ini[3] = 0; //f7
    maze[49].ini[0] = 0; maze[49].ini[1] = 42; maze[49].ini[2] = 48; maze[49].ini[3] = 0; //g7
}


void Maze2(int finish){

	maze[1].ini[0] = 2; maze[1].ini[1] = 0; maze[1].ini[2] = 0; maze[1].ini[3] = 8; //a1
	maze[2].ini[0] = 3; maze[2].ini[1] = 0; maze[2].ini[2] = 1; maze[2].ini[3] = 9; //b1
	maze[3].ini[0] = 4; maze[3].ini[1] = 0; maze[3].ini[2] = 2; maze[3].ini[3] = 10; //c1
	maze[4].ini[0] = 5; maze[4].ini[1] = 0; maze[4].ini[2] = 3; maze[4].ini[3] = 11; //d1
	maze[5].ini[0] = 6; maze[5].ini[1] = 0; maze[5].ini[2] = 4; maze[5].ini[3] = 12; //e1
	maze[6].ini[0] = 7; maze[6].ini[1] = 0; maze[6].ini[2] = 5; maze[6].ini[3] = 13; //f1
	maze[7].ini[0] = 0; maze[7].ini[1] = 0; maze[7].ini[2] = 6; maze[7].ini[3] = 14; //g1

	maze[8].ini[0] = 9; maze[8].ini[1] = 1; maze[8].ini[2] = 0; maze[8].ini[3] = 15; //a2
	maze[9].ini[0] = 10; maze[9].ini[1] = 2; maze[9].ini[2] = 8; maze[9].ini[3] = 16; //b2
	maze[10].ini[0] = 11; maze[10].ini[1] = 3; maze[10].ini[2] = 9; maze[10].ini[3] = 17; //c2
	maze[11].ini[0] = 12; maze[11].ini[1] = 4; maze[11].ini[2] = 10; maze[11].ini[3] = 18; //d2
	maze[12].ini[0] = 13; maze[12].ini[1] = 5; maze[12].ini[2] = 11; maze[12].ini[3] = 19; //e2
	maze[13].ini[0] = 14; maze[13].ini[1] = 6; maze[13].ini[2] = 12; maze[13].ini[3] = 20; //f2
	maze[14].ini[0] = 0; maze[14].ini[1] = 7; maze[14].ini[2] = 13; maze[14].ini[3] = 21; //g2

	maze[15].ini[0] = 16; maze[15].ini[1] = 8; maze[15].ini[2] = 0; maze[15].ini[3] = 22; //a3
	maze[16].ini[0] = 17; maze[16].ini[1] = 9; maze[16].ini[2] = 15; maze[16].ini[3] = 23; //b3
	maze[17].ini[0] = 18; maze[17].ini[1] = 10; maze[17].ini[2] = 16; maze[17].ini[3] = 24; //c3
	maze[18].ini[0] = 19; maze[18].ini[1] = 11; maze[18].ini[2] = 17; maze[18].ini[3] = 25; //d3
	maze[19].ini[0] = 20; maze[19].ini[1] = 12; maze[19].ini[2] = 18; maze[19].ini[3] = 26; //e3
	maze[20].ini[0] = 21; maze[20].ini[1] = 13; maze[20].ini[2] = 19; maze[20].ini[3] = 27; //f3
	maze[21].ini[0] = 0; maze[21].ini[1] = 14; maze[21].ini[2] = 20; maze[21].ini[3] = 28; //g3

	maze[22].ini[0] = 23; maze[22].ini[1] = 15; maze[22].ini[2] = 0; maze[22].ini[3] = 29; //a4
	maze[23].ini[0] = 24; maze[23].ini[1] = 16; maze[23].ini[2] = 22; maze[23].ini[3] = 30; //b4
	maze[24].ini[0] = 25; maze[24].ini[1] = 17; maze[24].ini[2] = 23; maze[24].ini[3] = 31; //c4
	maze[25].ini[0] = 26; maze[25].ini[1] = 18; maze[25].ini[2] = 24; maze[25].ini[3] = 32; //d4
	maze[26].ini[0] = 27; maze[26].ini[1] = 19; maze[26].ini[2] = 25; maze[26].ini[3] = 33; //e4
	maze[27].ini[0] = 28; maze[27].ini[1] = 20; maze[27].ini[2] = 26; maze[27].ini[3] = 34; //f4
	maze[28].ini[0] = 0; maze[28].ini[1] = 21; maze[28].ini[2] = 27; maze[28].ini[3] = 35; //g4

	maze[29].ini[0] = 30; maze[29].ini[1] = 22; maze[29].ini[2] = 0; maze[29].ini[3] = 36; //a5
	maze[30].ini[0] = 31; maze[30].ini[1] = 23; maze[30].ini[2] = 29; maze[30].ini[3] = 37; //b5
	maze[31].ini[0] = 32; maze[31].ini[1] = 24; maze[31].ini[2] = 30; maze[31].ini[3] = 38; //c5
	maze[32].ini[0] = 33; maze[32].ini[1] = 25; maze[32].ini[2] = 31; maze[32].ini[3] = 39; //d5
	maze[33].ini[0] = 34; maze[33].ini[1] = 26; maze[33].ini[2] = 32; maze[33].ini[3] = 40; //e5
	maze[34].ini[0] = 35; maze[34].ini[1] = 27; maze[34].ini[2] = 33; maze[34].ini[3] = 41; //f5
	maze[35].ini[0] = 0; maze[35].ini[1] = 28; maze[35].ini[2] = 34; maze[35].ini[3] = 42; //g5

	maze[36].ini[0] = 37; maze[36].ini[1] = 29; maze[36].ini[2] = 0; maze[36].ini[3] = 43; //a6
	maze[37].ini[0] = 38; maze[37].ini[1] = 30; maze[37].ini[2] = 36; maze[37].ini[3] = 44; //b6
	maze[38].ini[0] = 39; maze[38].ini[1] = 31; maze[38].ini[2] = 37; maze[38].ini[3] = 45; //c6
	maze[39].ini[0] = 40; maze[39].ini[1] = 32; maze[39].ini[2] = 38; maze[39].ini[3] = 46; //d6
	maze[40].ini[0] = 41; maze[40].ini[1] = 33; maze[40].ini[2] = 39; maze[40].ini[3] = 47; //e6
	maze[41].ini[0] = 42; maze[41].ini[1] = 34; maze[41].ini[2] = 40; maze[41].ini[3] = 48; //f6
	maze[42].ini[0] = 0; maze[42].ini[1] = 35; maze[42].ini[2] = 41; maze[42].ini[3] = 49; //g6

	maze[43].ini[0] = 44; maze[43].ini[1] = 36; maze[43].ini[2] = 0; maze[43].ini[3] = 0; //a7
	maze[44].ini[0] = 45; maze[44].ini[1] = 37; maze[44].ini[2] = 43; maze[44].ini[3] = 0; //b7
	maze[45].ini[0] = 46; maze[45].ini[1] = 38; maze[45].ini[2] = 44; maze[45].ini[3] = 0; //c7
	maze[46].ini[0] = 47; maze[46].ini[1] = 39; maze[46].ini[2] = 45; maze[46].ini[3] = 0; //d7
	maze[47].ini[0] = 48; maze[47].ini[1] = 40; maze[47].ini[2] = 46; maze[47].ini[3] = 0; //e7
	maze[48].ini[0] = 49; maze[48].ini[1] = 41; maze[48].ini[2] = 47; maze[48].ini[3] = 0; //f7
	maze[49].ini[0] = 0; maze[49].ini[1] = 42; maze[49].ini[2] = 48; maze[49].ini[3] = 0; //g7

	//initialize X & Y values
	int k = 1;
	for (int y = 1; y <= 7; y++) {
		for (int x = 1; x <= 7; x++) {
			maze[k].X = x;
			maze[k].Y = y;
			k += 1;
		}
	}

	//distance basierend auf Ziel und XY values
	for (int n = 1; n < 50; n++) {
		maze[n].distance = abs(maze[finish].X - maze[n].X)
				+ abs(maze[finish].Y - maze[n].Y);

	}
	for (int i = 1; i < 50; i++) {
		maze[i].flag = 0;
	}
}
