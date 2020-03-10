#include <moves.h>
/* Orchastrates move patterns */

void cmd_forward(int dist) {
	Lrot_dir = 0;
	Rrot_dir = 0;
	R_cmd = 1;
	L_cmd = 1;
	ds = dist * ds_multiplier
	;
	DelayMil(157 * dist);
}

void cmd_backward(int dist) {
	Lrot_dir = 1;
	Rrot_dir = 1;
	R_cmd = 1;
	L_cmd = 1;
	ds = dist * ds_multiplier
	;
	DelayMil(157 * dist);
}

void cmd_Lturn(int deg) {

	Lrot_dir = 0;
	Rrot_dir = 1;
	R_cmd = 1;
	L_cmd = 1;
	ds = deg * std_turn;
	DelayMil(17 * deg);
}

void cmd_Rturn(int deg) {

	Lrot_dir = 1;
	Rrot_dir = 0;
	R_cmd = 1;
	L_cmd = 1;
	ds = deg * std_turn;
	DelayMil(17 * deg);
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

void adjust(void) {
	int adjusted = 0;
	double GK;
	double angle;
	int corr = 2; //correction for angle
	//adjust to the sides
	//walls on both sides
	if (wall_R) {
		if (dist_R < 4) {
			GK = 4.0 - dist_R;
			angle = atan(GK/adjust_ds) ;
			cmd_backward(adjust_ds);
			cmd_Lturn((angle * (180/3.14)) + corr);
			cmd_forward((adjust_ds / cos(angle)));
			cmd_Rturn(angle * (180/3.14));
		} else if (dist_R > 4) {
			GK = dist_R - 4.0;
			angle = atan(GK/adjust_ds);
			cmd_backward(adjust_ds);
			cmd_Rturn((angle*(180/3.14)) + corr);
			cmd_forward((adjust_ds / cos(angle)));
			cmd_Lturn(angle*(180/3.14));
		}
		adjusted = 1;
	} else if (wall_L) {
		//prevents double adjustments L+R
		if (adjusted == 0) {
			if (dist_L < 4) {
				GK = 4.0 - dist_L;
				angle = atan(GK/adjust_ds);
				cmd_backward(adjust_ds);
				cmd_Rturn((angle*(180/3.14)) + corr);
				cmd_forward(adjust_ds / cos(angle));
				cmd_Lturn(angle*(180/3.14));
			} else if (dist_L > 4) {
				GK = dist_L - 4.0;
				angle = atan(GK/adjust_ds);
				cmd_backward(adjust_ds);
				cmd_Lturn((angle*(180/3.14)) + corr);
				cmd_forward(adjust_ds / cos(angle));
				cmd_Rturn(angle*(180/3.14));
			}
		}
	}

	//adjust to front wall to exact 4 cm
	if ((dist_C > 1) && (dist_C < 10)) {
		if (dist_C < 4) {
			cmd_backward(4 - dist_C);
		} else if (dist_C > 4) {
			cmd_forward(dist_C - 4);
		}
	}
}
