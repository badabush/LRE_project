#include <moves.h>
/* Orchastrates move patterns */

void cmd_forward(void) {
	Lrot_dir = 0;
	Rrot_dir = 0;
	R_cmd = 1;
	L_cmd = 1;
}

void cmd_backward(void) {
	Lrot_dir = 1;
	Rrot_dir = 1;
	R_cmd = 1;
	L_cmd = 1;
}

void cmd_Lturn(void) {

	Lrot_dir = 0;
	Rrot_dir = 1;
	R_cmd = 1;
	L_cmd = 1;
}

void cmd_Rturn(void) {

	Lrot_dir = 1;
	Rrot_dir = 0;
	R_cmd = 1;
	L_cmd = 1;
}

void cmd_park(void) {
	//parking algorithm. Move forward towards wall and do 180 if gotten close.
	ds = ds_true(1000);
	cmd_forward();
	SendString("*** Starting sequence Parking ***\n\n");
	while (wall_C == 0) {
		ds = 10;
	}

	cmd_Lturn();
	ds = 180 * std_turn;
}

void cmd_shake(void) {
	//start shaking left and right wildly if it has absolutely no idea what to do.
	for (int i; i < 5; i++) {
		cmd_Lturn();
		ds = ds_true(10);
		DelaySec(1);
		cmd_Rturn();
		ds = ds_true(10);
		DelaySec(1);
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
			cmd_backward();
			ds = ds_true(1);
			DelayMil(1000);
			ds_wall = dist_L;
		}
		//approach wall fast
		cmd_Lturn();
		ds = (70 * std_turn);
		DelaySec(2);

		cmd_forward();
		ds = ds_true(abs(ds_wall - des_dist));
		DelaySec(5);

		cmd_Rturn();
		ds = (70 * std_turn);
		DelaySec(2);

	} else if (dist_L < (des_dist - 10)) {
		//routine if false measurement
		while ((ds_wall == 999)) {
			//error handle, let mouse drive 5cm bw
			cmd_backward();
			ds = ds_true(1);
			DelayMil(1000);
			ds_wall = dist_L;
		}
		//approach wall fast
		cmd_Rturn();
		ds = (70 * std_turn);
		DelaySec(2);

		cmd_forward();
		ds = ds_true(abs(ds_wall - des_dist));
		DelaySec(5);

		cmd_Lturn();
		ds = (70 * std_turn);
		DelaySec(2);
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
			cmd_backward();
			ds = ds_true(1);
			DelayMil(1000);
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
				cmd_Lturn();
				ds = angle * std_turn;
				DelaySec(1);
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
				cmd_Rturn();
				ds = angle * std_turn;
				DelaySec(1);
			}
		}
		cmd_forward();
		ds = ds_true(cell / 4);
		DelayMil(1100);

		//if cumulative angle exceeds 45 deg
		if (abs(add_angle) > 45) {
			angle = 60;
			if (add_angle > 0) {
				cmd_Rturn();
				ds = angle * std_turn;
				DelaySec(1);
			} else {
				cmd_Lturn();
				ds = angle * std_turn;
				DelaySec(1);
			}
			add_angle = 0;
		}
//		DelaySec(3);
		prior_diff = diff;
	}

}
