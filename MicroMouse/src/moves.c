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
	cmd_forward(1000);
	SendString("*** Starting sequence Parking ***\n\n");
	while (wall_C == 0) {
		ds = 10;
	}

	cmd_Lturn(180);
}

void cmd_shake(void) {
	//start shaking left and right wildly if it has absolutely no idea what to do.
	for (int i; i < 5; i++) {
		cmd_Lturn(10);
		cmd_Rturn(10);
	}
}

void cmd_follow(void) {
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
	int angle = 10;
	int diff = 0;
	int ds_wall = dist_L;
	//init, approach wall to +-10cm diff
	//if wall is further away than 10cm
	if (dist_L > (des_dist + 10)) {
		//routine if false measurement
		while ((ds_wall == 999)) {
			//error handle, let mouse drive 5cm bw
			cmd_backward(1);
			ds_wall = dist_L;
		}
		/*approach wall fast
		 * turn, drive diff, turn back
		 */
		cmd_Lturn(70);
		cmd_forward(abs(ds_wall - des_dist));
		cmd_Rturn(70);

	} else if (dist_L < (des_dist - 10)) {
		//routine if false measurement
		while ((ds_wall == 999)) {
			//error handle, let mouse drive 5cm bw
			cmd_backward(1);
			ds_wall = dist_L;
		}
		cmd_Rturn(70);
		cmd_forward(abs(ds_wall - des_dist));
		cmd_Lturn(70);
	}

	int prior_diff = ds_wall - des_dist;	//to wall
	int add_angle = 0;
	for (i = 0; i < 40; i++) {
		//get diff to des dist
		ds_wall = dist_L;
		diff = ds_wall - des_dist;
		//only correct if divergence>2
		while ((ds_wall == 999) || (ds_wall < 8)) {
			//error handle, let mouse drive 5cm bw
			cmd_backward(1);
			ds_wall = dist_L;

		}
		if (abs(diff) > 1) {
			//increase angle when distance is growing/shrinking
//			if ((diff-prior_diff)>5)
//				angle=angle+5;
			if (ds_wall > des_dist) {
				//got further away from wall

				if (abs(diff) > 8) {
					angle = 15;
					add_angle = add_angle + angle;
				} else if (abs(diff) < 4) {
					angle = 5;
					add_angle = add_angle + angle;
				} else {
					angle = 10;
					add_angle = add_angle + angle;
				}
				cmd_Lturn(angle);
			} else if (ds_wall < des_dist) {
				//got close to the wall

				if (abs(diff) > 8) {
					angle = 15;
					add_angle = add_angle - angle;
				} else if (abs(diff) < 4) {
					angle = 5;
					add_angle = add_angle - angle;
				} else {
					angle = 10;
					add_angle = add_angle - angle;
				}
				cmd_Rturn(angle);
			}
		}
		cmd_forward(cell / 4);

		//if cumulative angle exceeds 45 deg
		if (abs(add_angle) > 45) {
			angle = 60;
			if (add_angle > 0) {
				cmd_Rturn(angle);
			} else {
				cmd_Lturn(angle);
			}
			add_angle = 0;
		}
//		DelaySec(3);
		prior_diff = diff;
	}

}
