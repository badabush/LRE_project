#include <cmdFind.h>

// currCell <-> prevCell
void permutate2(int currCell, int prevCell) {
	for (int i = 0; i < 4; i++) { // find where currCell is in prevCell.ini and derive the current orientation of mimo of that
		if (maze[prevCell].ini[i] == currCell && i == 0) { // currCell is on the right of prevCell
			maze[currCell].ini[0] = maze[currCell].perm[3]; // back becomes right
			maze[currCell].ini[1] = maze[currCell].perm[0]; // right becomes front
			maze[currCell].ini[2] = maze[currCell].perm[1];	// etc
			maze[currCell].ini[3] = maze[currCell].perm[2]; // etc
			break;
		} else if (maze[prevCell].ini[i] == currCell && i == 1) { // currCell is on the front of prevCell
			maze[currCell].ini[0] = maze[currCell].perm[0];
			maze[currCell].ini[1] = maze[currCell].perm[1];
			maze[currCell].ini[2] = maze[currCell].perm[2];
			maze[currCell].ini[3] = maze[currCell].perm[3];
			break;
		}
		if (maze[prevCell].ini[i] == currCell && i == 2) { // currCell is on the left of prevCell
			maze[currCell].ini[0] = maze[currCell].perm[1];
			maze[currCell].ini[1] = maze[currCell].perm[2];
			maze[currCell].ini[2] = maze[currCell].perm[3];
			maze[currCell].ini[3] = maze[currCell].perm[0];
			break;
		} else if (maze[prevCell].ini[i] == currCell && i == 3) { // currCell is on the back of prevCell
			maze[currCell].ini[0] = maze[currCell].perm[2];
			maze[currCell].ini[1] = maze[currCell].perm[3];
			maze[currCell].ini[2] = maze[currCell].perm[0];
			maze[currCell].ini[3] = maze[currCell].perm[1];
			break;
		}
	}
	// when currCell=prevCell, that means that mimo is in starting cell the following happens
	if (currCell == prevCell) {
		for (int j = 0; j < 4; j++) {
			maze[currCell].ini[j] = maze[currCell].perm[j]; // no perm
		}
	}
}
void cmd_search(int start, int finish) {
	/* Algorithm to find the center of the maze starting in one of the corners.
	 *
	 * */
	Maze2(finish); //maze without inner borders
	int finishBool = 0; // maxl = max length of path= (number of cells mouse drives through a complete drive through whole maze)+1
	int path[100] = { 0 };
	int currCell = start;
	int prevCell = start;
	path[0] = start;
	// 1.2 pathfinding loop with algorithm
	for (int a = 0; a < maxl; a++) {
		if (finishBool == 0) {
			// 1.2.1 permutate neighbor cells to fit orientation of mouse, drive to neighbour cell

			permutate(currCell, prevCell); //initialisiert perm for drive

			if (wall_L == 1) {
				maze[currCell].perm[2] = 0;
			}
			if (wall_R == 1) {
				maze[currCell].perm[0] = 0;
			}
			if (wall_C == 1) {
				maze[currCell].perm[1] = 0;
			}
//
//			permutate2(prevCell, currCell);
//			permutate(currCell, prevCell); //initialisiert perm for drive

			// 1.2.2 find next cell, update prevCell and currCell
//			for (int k = 0; k < 4; k++) {
//				if (maze[currCell].perm[k] != 0) { // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
//					prevCell = currCell; //
//					currCell = maze[currCell].perm[k];
//					break;
//				} else
//					; // do nothing continue with loop
//			}
//			SendString(printf("curr: %i; prev: %i\n", currCell, prevCell));

			// 1.2.2 go next cell, update prevCell and currCell

			// see cells with flag = 2 as walls
			/* Auswahl der n�chsten Zelle Aufgrund der W�nde, Flags und Value(distance)
			 * Keine Wand
			 * 	Flag (dont need the 1 flag in our maze because there is no
			 * 	 Value(distance)
			 *
			 * */
			//drive nearer to finish when no wall and new cell
			for (int k = 0; k < 4; k++) {
				//   perm[k] ist der Index der n�chsten zelle
				if ((maze[currCell].perm[k] != 0)
						&& (maze[currCell].distance
								> maze[maze[currCell].perm[k]].distance)
						&& (maze[maze[currCell].perm[k]].flag == 0)) {
					clearNodes();
					prevCell = currCell; // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
					currCell = maze[currCell].perm[k];
					hasNext = 1;
					break;
				} else {
					// if distance isnt reducing
					hasNext = 0;
				}
			}
			if (hasNext == 0) {
				//drive when no wall and new cell
				for (int k = 0; k < 4; k++) {
					//   perm[k] ist der Index der n�chsten zelle
					if (maze[currCell].perm[k] != 0
							&& maze[maze[currCell].perm[k]].flag == 0) {
						clearNodes();
						prevCell = currCell; // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
						currCell = maze[currCell].perm[k];
						hasNext = 1;
						break;
					} else
						;
				}
			}
			if (hasNext == 0) {
				//drive where is no wall
				for (int k = 0; k < 4; k++) {
					//   perm[k] ist der Index der n�chsten zelle
					if (maze[currCell].perm[k] != 0) {
						clearNodes();
						prevCell = currCell; // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
						currCell = maze[currCell].perm[k];
						break;
					} else
						; // do nothing continue with loop
				}
			}
			drive(currCell, prevCell);

			//flagg to know where we where before
			if (a != 0) {
				maze[prevCell].flag += 1;
			}
			if (maze[prevCell].flag == 2) {
				maze[currCell].perm[3] = 0;
			}
			// 1.2.3 put next cell in path array
			path[a + 1] = currCell;
			if (currCell == finish) {
				finishBool = 1;
				break; // statt else if (finishBool==1){}; go to 2 short path
			}
//			end of
//			pathfinding loop
		}

		//else if (finishBool==1){}	// reached finish, end pathfinding loop
	}

	// 2. short path; compare first entry of path with rest	of path, if same entry is found set every entry between them to 0
	int iteration = 0;
	while (iteration < 2) {
		for (int j = 0; j < maxl; j++) {
			if (iteration == 0) {
				for (int k = j; k < maxl; k++) {
//					if (path[j] != 0) {
					if (path[j] == path[k + 1] && path[j] != 0) {
						for (int l = j + 1; l <= k + 1; l++) {
							path[l] = 0;
						}
					} else
						;
				}
			} else if (iteration == 1) { // determine length of finalpath by counting every entry != 0
				if (path[j] != 0) {
					counter++;
				} else
					;
			}
		}
		iteration++;
	}
	int cnt = 0;
	for (int j = 0; j < maxl; j++) { // copy every entry != 0 from path to finalpath
		if (path[j] != 0) {
			finalpath[cnt] = path[j];
			cnt++;
		}
	}

	char str[2];
	for (int l = 0; l < 50; l++) {
		if (finalpath[l] != 0) {
			sprintf(str, "%i", finalpath[l]);
			SendString(str);
			SendString("\n");
		}
	}
}

/* ********************************************************
 * ********************************************************
 * ********************  CMD FIND  ************************
 * ********************************************************
 * *********************************************************/

void cmd_find(int start, int finish, int counter) {
	Maze2(finish); //added
	//reset perm before driving
	int finpath[counter];

	for (int j = 0; j < counter; j++) { // copy every entry != 0 from path to finalpath
		finpath[j] = finalpath[j];
	}
	//<debug print>
	char str[2];
	for (int l = 0; l < counter; l++) {
		if (finpath[l] != 0) {
			sprintf(str, "%i", finpath[l]);
			SendString(str);
			SendString("\n");
		}
	}
	//</debug print>
	for (int i = 0; i < 50; i++) {
		maze[i].perm[0] = maze[i].ini[0];
		maze[i].perm[1] = maze[i].ini[1];
		maze[i].perm[2] = maze[i].ini[2];
		maze[i].perm[3] = maze[i].ini[3];
	}
	for (int i = 1; i < counter; i++) { // goes (x-1) times through finalpath
		currCell = finpath[i];
		prevCell = finpath[i - 1];

		if (i == 1) {
			drive(currCell, prevCell);
			permutate(currCell, prevCell);
		} else {
			permutate(currCell, prevCell);
			drive(currCell, prevCell);
		}
	}
}

void clearNodes(void) {
	// setting nodes to 0; nessasary for Nodes because in a Node we are driving sometimes more then two times
	for (int k = 0; k < 4; k++) {
		if (maze[prevCell].perm[k] != 0) {
			k++;
			if (maze[prevCell].perm[k] != 0) {
				k++;
				if (maze[prevCell].perm[k] != 0) {
					if (maze[prevCell].flag == 1) {
						maze[prevCell].flag = maze[prevCell].flag - 1;
						break;
					}
				} else
					;
			} else
				;
		} else
			;
	}

}

