#include <moves.h>
/* Orchastrates move patterns */

void cmd_forward(int dist) {
	Lrot_dir = 0;
	Rrot_dir = 0;
	R_cmd = 1;
	L_cmd = 1;
	ds = dist * ds_multiplier
	;
	DelayMil(250 * dist);
}

void cmd_backward(int dist) {
	Lrot_dir = 1;
	Rrot_dir = 1;
	R_cmd = 1;
	L_cmd = 1;
	ds = dist * ds_multiplier
	;
	DelayMil(250 * dist);
}

void cmd_Lturn(int deg) {

	Lrot_dir = 0;
	Rrot_dir = 1;
	R_cmd = 1;
	L_cmd = 1;
	ds = deg * std_turn;
	DelayMil(25 * deg);
}

void cmd_Rturn(int deg) {

	Lrot_dir = 1;
	Rrot_dir = 0;
	R_cmd = 1;
	L_cmd = 1;
	ds = deg * std_turn;
	DelayMil(25 * deg);
}

void cmd_park(void) {
	//parking algorithm. Move forward towards wall and do 180 if gotten close.
	SendString("*** Starting sequence Parking ***\n\n");
	while (dist_C > 10) {
		Lrot_dir = 0;
		Rrot_dir = 0;
		R_cmd = 1;
		L_cmd = 1;
		ds = 2 * 177;
	}

	cmd_Lturn(180);
	cmd_backward(3);
}

void cmd_shake(void) {
	//start shaking left and right wildly if it has absolutely no idea what to do.
	for (int i; i < 5; i++) {
		cmd_Lturn(10);
		cmd_Rturn(10);
	}
}

void cmd_follow(int tot_dist) {
	/* Follow right wall
	 * seperate between init and routine
	 * init:
	 * - get distance to wall
	 * - approach to a defined distance (5cm)
	 * - adjust so moving direction is parallel to wall
	 * routine:
	 * - drive half a cell
	 * - get distance
	 * - adjust so after the next 1/2 cell distance the defined
	 * distance to wall will be reached
	 *
	 * TODO: find wall to follow (L/R), default to follow R if
	 * side unclear
	 * */
	int i;
	int driven_dist = 0;
	int prior_dist = 0;
	int abs_dist = 0;
	int side_dist = 0;
	//determine which side to follow
	int pre_R, pre_L, j = 0;
	while (j < 5) {
		if (j > 0) {
			if ((pre_R == dist_R) && (dist_R != 999)) {
				if (pre_R < pre_L) {
					side = 1;
					j = 5;
				}
			} else if ((pre_L == dist_L) && (dist_L != 999)) {
				if (pre_L < pre_R) {
					side = 2;
					j = 5;
				}
			}
		}
		pre_R = dist_R;
		pre_L = dist_L;
		cmd_forward(1);
		j++;
	}
	if (side == 1) {
		SendString("Side R detected.\n");
	} else if (side == 2) {
		SendString("Side L detected.\n");
	}
	char str[20];
	sprintf(str, "L: %i, R:%i", dist_L, dist_R);
	SendString(str);
	while (driven_dist <= tot_dist) {

		if (side == 1) {
			side_dist = dist_R;
		} else {
			side_dist = dist_L;
		}
		abs_dist = abs(des_dist - side_dist);
		if (side == 1) {
			if (abs_dist > 1) {
				if (side_dist < des_dist) {
					cmd_Lturn(10);
				} else {
					cmd_Rturn(10);
				}
			}
		} else {
			if (abs_dist > 1) {
				if (side_dist < des_dist) {
					cmd_Rturn(10);
				} else {
					cmd_Lturn(10);
				}
			}
		}
		cmd_forward(9);
		driven_dist += 9;
		if (side == 1) {
			prior_dist = dist_R;
		} else {
			prior_dist = dist_L;
		}
	}
}

void cmd_corner(void) {
//parking algorithm. Move forward towards wall and do 180 if gotten close.

	SendString("*** Starting corner sequence ***\n\n");
	while (wall_C == 0) {

		cmd_follow(5);

	}
	/*
	 if ( dist_L < des_dist) {
	 cmd_Rturn(90);
	 }
	 else {
	 cmd_Lturn(90);
	 }
	 */
	cmd_Rturn(90);
	cmd_follow(100);

	if (side == 2) {
		cmd_Rturn(90);
		cmd_follow(100);
	} else {
		cmd_Lturn(90);
		cmd_follow(100);
	}
}

