// Code for moving from a start cell to a finisch cell
// process is divided in 3 steps:
// 1. virtually driving through maze until destination is reached; chain every cell together = path
// 2. short path
// 3. follow path

////////////////////////////////////////////////////
// in main command
//else if (strcmp(received_string, "pf\r\n") == 0) {
//				cmd_pathfinder(s,f);
// }
/////////////////////////////////////////////////
#include <pathfinder.h>
#include <sonar.h>

void permutate(int currCell, int prevCell) {
	for (i = 0; i < 4; i++) { // find where currCell is in prevCell.ini and derive the current orientation of mimo of that
		if (maze[prevCell].ini[i] == currCell && i == 0) { // currCell is on the right of prevCell
			maze[currCell].perm[0] = maze[currCell].ini[3]; // back becomes right
			maze[currCell].perm[1] = maze[currCell].ini[0]; // right becomes front
			maze[currCell].perm[2] = maze[currCell].ini[1];	// etc
			maze[currCell].perm[3] = maze[currCell].ini[2]; // etc
			break;
		} else if (maze[prevCell].ini[i] == currCell && i == 1) { // currCell is on the front of prevCell
			maze[currCell].perm[0] = maze[currCell].ini[0];
			maze[currCell].perm[1] = maze[currCell].ini[1];
			maze[currCell].perm[2] = maze[currCell].ini[2];
			maze[currCell].perm[3] = maze[currCell].ini[3];
			break;
		}
		if (maze[prevCell].ini[i] == currCell && i == 2) { // currCell is on the left of prevCell
			maze[currCell].perm[0] = maze[currCell].ini[1];
			maze[currCell].perm[1] = maze[currCell].ini[2];
			maze[currCell].perm[2] = maze[currCell].ini[3];
			maze[currCell].perm[3] = maze[currCell].ini[0];
			break;
		} else if (maze[prevCell].ini[i] == currCell && i == 3) { // currCell is on the back of prevCell
			maze[currCell].perm[0] = maze[currCell].ini[2];
			maze[currCell].perm[1] = maze[currCell].ini[3];
			maze[currCell].perm[2] = maze[currCell].ini[0];
			maze[currCell].perm[3] = maze[currCell].ini[1];
			break;
		}
	}
	// when currCell=prevCell, that means that mimo is in starting cell the following happens
	if (currCell == prevCell) {
		for (int j = 0; j < 4; j++) {
			maze[currCell].perm[j] = maze[currCell].ini[j]; // no perm
		}
	}
}
void drive(int currCell, int prevCell) {
	for (int j = 0; j < 4; j++) {
		if (maze[prevCell].perm[j] == currCell && j == 0) {
			//turn R and drive 1 cell
			cmd_Rturn(90);
			cmd_forward(20);
			adjust();
			SendString("R turn\n");
			break;
		} else if (maze[prevCell].perm[j] == currCell && j == 1) {
			//drive 1 cell
			cmd_forward(20);
			adjust();
			SendString("Forward\n");
			break;
		}
		if (maze[prevCell].perm[j] == currCell && j == 2) {
			//turn L and drive 1 cell
			cmd_Lturn(90);
			cmd_forward(20);
			adjust();
			SendString("L turn\n");
			break;
		} else if (maze[prevCell].perm[j] == currCell && j == 3) {
			// 180 turn and drive 1 cell
			cmd_Lturn(180);
//			cmd_follow(18);

			cmd_forward(20);
			//maze[prevCell].flag = maze[prevCell].flag +1; //flagging the dead ends
			SendString("180 turn\n");
			break;
		}
	}
}

void cmd_pathfinder(int start, int finish) { // everything from 1-3

// 1.1 get starting point and put it in path
	Maze();
	currCell = start;
	prevCell = start;
	path[0] = start;

// 1.2 pathfinding loop
	for (int a = 0; a < maxl; a++) {
		if (finishBool == 0) {
// 1.2.1 permutate neighbor cells to fit orientation of mouse
			permutate(currCell, prevCell);

// 1.2.2 find next cell, update prevCell and currCell
			for (int k = 0; k < 4; k++) {
				if (maze[currCell].perm[k] != 0) { // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
					prevCell = currCell; //
					currCell = maze[currCell].perm[k];
					break;
				} else
					; // do nothing continue with loop
			}
// 1.2.3 put next cell in path array
			path[a + 1] = currCell;
			if (currCell == finish) {
				finishBool = 1;
				break; // statt else if (finishBool==1){}; go to 2 short path
			}
// end of pathfinding loop
		}

		//else if (finishBool==1){}	// reached finish, end pathfinding loop
	}
	char str[2];
	for (int l = 0; l < maxl; l++) {
		if (path[l] != 0) {
			sprintf(str, "%i", path[l]);
			SendString(str);
			SendString("\n");
		}
	}
// 2. short path; compare first entry of path with rest	of path, if same entry is found set every entry between them to 0

	while (iteration < 2) {
		for (int j = 0; j < maxl; j++) {
			if (iteration == 0) {
				for (int k = j; k < maxl; k++) {
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
	int finalpath[counter];
	counter = 0;

	for (int j = 0; j < maxl; j++) { // copy every entry != 0 from path to finalpath
		if (path[j] != 0) {
			finalpath[counter] = path[j];
			counter++;
		} else
			;
	}
//	char str2[2];
//	for (l = 0; l < counter; l++) {
//		sprintf(str2, "%i", path[l]);
//		SendString(str2);
//	}
// 3. follow path

	///nicht fertig ////
	////////////////////
	for (int i = 1; i < counter; i++) { // goes (x-1) times through finalpath
		currCell = finalpath[i];
		prevCell = finalpath[i - 1];

		if (i == 1) {
			drive(currCell, prevCell);
		} else {
			permutate(currCell, prevCell);
			drive(currCell, prevCell);
		}
	}
	cmd_shake();
} //end from fct pathfinder
void cmd_search(int start, int finish) {
	/* Algorithm to find the center of the maze starting in one of the corners.
	 *
	 * */
	Maze2(finish); //maze without inner borders
	currCell = start;
	prevCell = start;
	path[0] = start;
	// 1.2 pathfinding loop with algorithm
	for (int a = 0; a < maxl; a++) {
		if (finishBool == 0) {
			// 1.2.1 permutate neighbor cells to fit orientation of mouse, drive to neighbour cell

			permutate(currCell, prevCell); //initialisiert perm for drive
			scan(); //set to 0 for walls
			drive(currCell, prevCell);
			//flaggen to know where we where before
			maze[prevCell].flag = maze[prevCell].flag +1;

		// 1.2.2 go next cell, update prevCell and currCell
//

			// see cells with flag = 2 as walls
			if(maze[prevCell].flag ==2){maze[currCell].perm[3]=0;}

			/* Auswahl der nächsten Zelle Aufgrund der Wände, Flags und Value(distance)
			 * Keine Wand
			 * 	Flag (dont need the 1 flag in our maze because there is no
			 * 	 Value(distance)
			 *
			 * */
			//drive nearer to finish when no wall and new cell
			for (int k = 0; k < 4; k++) {
							//   perm[k] ist der Index der nächsten zelle
							if (maze[currCell].perm[k] != 0 && maze[currCell].distance > maze[maze[currCell].perm[k]].distance && maze[maze[currCell].perm[k]].flag == 0 ) {
								clearNodes();
								prevCell = currCell; // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
								currCell = maze[currCell].perm[k];
								hasNext = 1 ;
								break;
							} else 	;
						}
			if(hasNext != 1){
			//drive when no wall and new cell
			for (int k = 0; k < 4; k++) {
							//   perm[k] ist der Index der nächsten zelle
							if (maze[currCell].perm[k] != 0 && maze[maze[currCell].perm[k]].flag == 0 ) {
								clearNodes();
								prevCell = currCell; // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
								currCell = maze[currCell].perm[k];
								hasNext = 1 ;
								break;
							} else 	;
									}
			}
			if(hasNext != 1){
			//drive where is no wall
			for (int k = 0; k < 4; k++) {
							//   perm[k] ist der Index der nächsten zelle
							if (maze[currCell].perm[k] != 0 ) {
								clearNodes();
								prevCell = currCell; // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
								currCell = maze[currCell].perm[k];
								hasNext = 0;   //for the next run
								break;
							} else
								; // do nothing continue with loop
						}
			}


			// 1.2.3 put next cell in path array
			path[a + 1] = currCell;
			if (currCell == finish) {
				finishBool = 1;
				break; // statt else if (finishBool==1){}; go to 2 short path
			}
			// end of pathfinding loop
		}

		//else if (finishBool==1){}	// reached finish, end pathfinding loop
	}
	char str[2];
	for (int l = 0; l < maxl; l++) {
		if (path[l] != 0) {
			sprintf(str, "%i", path[l]);
			SendString(str);
			SendString("\n");
		}
	}
	// 2. short path; compare first entry of path with rest	of path, if same entry is found set every entry between them to 0

	while (iteration < 2) {
		for (int j = 0; j < maxl; j++) {
			if (iteration == 0) {
				for (int k = j; k < maxl; k++) {
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
	int finalpath[counter];
	counter = 0;

	for (int j = 0; j < maxl; j++) { // copy every entry != 0 from path to finalpath
		if (path[j] != 0) {
			finalpath[counter] = path[j];
			counter++;
		} else
			;
	}
	/*TODO: this wont work, you have to assign one value to a specific element
	 * findpath[i] = finalpath[i]
	 * should look like as follows
	 */
	int findpath[50];
	for (int i; i < maxl; i++) {
		findpath[i] = finalpath[i];
	}
}
void cmd_find(int start, int finish, int findpath[]) {
	/* some comment*/
	for (int i = 1; i < counter; i++) { // goes (x-1) times through finalpath
		currCell = findpath[i];
		prevCell = findpath[i - 1];

		if (i == 1) {
			drive(currCell, prevCell);
		} else {
			permutate(currCell, prevCell);
			drive(currCell, prevCell);
		}
	}
}
void scan(void) {
	/* some comment*/
	if (dist_L < 6) {
		maze[currCell].perm[2] = 0;
	}
	if (dist_R < 6) {
		maze[currCell].perm[0] = 0;
	}
	if (dist_C < 6) {
		maze[currCell].perm[3] = 0;
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
								if(maze[prevCell].flag == 1){
								maze[prevCell].flag = maze[prevCell].flag -1;
								break;
								}
							}else;
						}else;
					}else;
				}
}

