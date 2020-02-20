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

void permutate () {
	for(i=0; i<4; i++) { // find where currCell is in prevCell.ini and derive the current orientation of mimo of that
		if (maze[prevCell].ini[i] == currCell && i==0){ // currCell is on the right of prevCell
			maze[currCell].perm[0] = maze[currCell].ini[3]; // back becomes right
			maze[currCell].perm[1] = maze[currCell].ini[0]; // right becomes front
			maze[currCell].perm[2] = maze[currCell].ini[1];	// etc
			maze[currCell].perm[3] = maze[currCell].ini[2]; // etc
		break;
		}
		else if (maze[prevCell].ini[i] == currCell && i==1){ // currCell is on the front of prevCell
			maze[currCell].perm[0] = maze[currCell].ini[0];
			maze[currCell].perm[1] = maze[currCell].ini[1];
			maze[currCell].perm[2] = maze[currCell].ini[2];
			maze[currCell].perm[3] = maze[currCell].ini[3];
		break;
		}
		if (maze[prevCell].ini[i] == currCell && i==2){ // currCell is on the left of prevCell
			maze[currCell].perm[0] = maze[currCell].ini[1];
			maze[currCell].perm[1] = maze[currCell].ini[2];
			maze[currCell].perm[2] = maze[currCell].ini[3];
			maze[currCell].perm[3] = maze[currCell].ini[0];
		break;
		}
		else if (maze[prevCell].ini[i] == currCell && i==3){ // currCell is on the back of prevCell
			maze[currCell].perm[0] = maze[currCell].ini[2];
			maze[currCell].perm[1] = maze[currCell].ini[3];
			maze[currCell].perm[2] = maze[currCell].ini[0];
			maze[currCell].perm[3] = maze[currCell].ini[1];
		break;
		}
	}
	 // when currCell=prevCell, that means that mimo is in starting cell the following happens
	for(j=0; j<4; j++) {
		maze[currCell].perm[j] = maze[currCell].ini[j];// no perm
	}
}


void cmd_pathfinder(int start, int finish) { // everything from 1-3
// 1.1 get starting point and put it in path
	currCell=start;
	prevCell=start;
	path[0]=start;

// 1.2 pathfinding loop
	for(a=0; a<maxl; a++) {
		if (finishBool==0){
// 1.2.1 permutate neighbor cells to fit orientation of mouse
	permutate();

// 1.2.2 find next cell, update prevCell and currCell
			for(k=0; k<4; k++) {
				if (maze[currCell].perm[k] != 0){ // first entry != 0 becomes current cell and therefore the next cell to which mimo will drive
					prevCell=currCell; //
					currCell=maze[currCell].ini[k];
					break;
				}
				else ; // do nothing continue with loop
			}
// 1.2.3 put next cell in path array
			path[a+1]=prevCell;
			if (prevCell==finish)
			{
				finishBool=1;
				break; // statt else if (finishBool==1){}; go to 2 short path
			}
// end of pathfinding loop
		}

		//else if (finishBool==1){}	// reached finish, end pathfinding loop
	}
	char str[2];
	for (l=0;l<maxl;l++) {
		if (path[l]!=0){
			sprintf(str, "%i", path[l]);
			SendString(str);
		}
	}
// 2. short path; compare first entry of path with rest	of path, if same entry is found set every entry between them to 0


		while(iteration<2){
			for(j=0; j<maxl; j++) {
				if (iteration==0){
					for(k=0; k<maxl; k++) {
						if (path[j]	== path[k+1]&& path[j] !=0){
							for(l=0; l<k; l++) {
								path[l]=0;
							}
						}
						else ;
					}
				}
				else if (iteration==1){ // determine length of finalpath by counting every entry != 0
					if (path[j]!=0){
						counter++;
					}
					else ;
				}
			}
			iteration++;
		}
		int finalpath[counter];
		counter=0;

	for(j=0; j<maxl; j++) { // copy every entry != 0 from path to finalpath
		if (path[j]!=0){
			finalpath[counter]=path[j];
				counter++;
		}
		else ;
	}
	char str2[2];
	for (l=0;l<counter;l++) {
			sprintf(str2, "%i", path[l]);
			SendString(str2);
	}
// 3. follow path
	/*
	///nicht fertig ////
	////////////////////
	for (i=1; i<counter; i++){ // goes (x-1) times through finalpath
		currCell=finalpath[i];
		prevCell=finalpath[i-1];

		permutate();

		for(j=0; j<4; j++){
			if(maze[prevCell].perm[j] == currCell && j==0){
				//turn left and drive 1 cell
			break;
			}
			else if(maze[prevCell].perm[j] == currCell && j==1){
				//turn 180 and drive 1 cell
			break;
			}
			if(maze[prevCell].perm[j] == currCell && j==2){
				//turn right and drive 1 cell
			break;
			}
			else if(maze[prevCell].perm[j] == currCell && j==3){
				// no turn and drive 1 cell
			break;
			}
		}

	}
	*/
}//end from fct pathfinder
