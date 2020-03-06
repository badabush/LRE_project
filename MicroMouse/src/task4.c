#include <task4.h>

void t4_follow(int cell1) {
	/*
	 * function for task 4
	 * */
	//pt1: drive a given number of cells
	for (int i = 1; i <= cell1; i++) {
		cmd_forward(20);
		adjust();
		scan();
	}

	//pt2: turn right and drive until wall
	cmd_Rturn(90);
	scan();
	int cells2 = 0;
	while (wall_C == 0) {
		cmd_forward(20);
		adjust();
		scan();
		cells2 += 1;
	}

	//pt3:U-turn and drive back cells2
	cmd_Rturn(180);
	scan();
	for (int i = 1; i <= cells2; i++) {
		cmd_forward(20);
		adjust();
		scan();
	}

	//pt4: L-turn and drive back cells
	cmd_Lturn(90);
	scan();
	for (int i = 1; i <= cell1; i++) {
		cmd_forward(20);
		adjust();
		scan();
	}
	DelaySec(2);
	cmd_shake();
}

void scan(void) {
	if (wall_C == 1) {
		SendString("Wall C  ");
	}

	if (wall_R == 1) {
		SendString("Wall R  ");
	}

	if (wall_L == 1) {
		SendString("Wall L  ");
	}
	if ((wall_C == 0) && (wall_R == 0) && (wall_L == 0)) {
		SendString("no walls detected");
	}
	SendString("\n\n");

}

