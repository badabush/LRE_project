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
	ds = ds_true(1000);
	cmd_forward();
	SendString("*** Starting sequence Parking ***\n\n");
	while (wall_C == 0) {
		ds = 10;
	}

	cmd_Lturn();
	ds = 180 * std_turn;
}

void cmd_follow(void){
	/* Follow right wall
	 * seperate between init and routine
	 * init:
	 * - find wall
	 * - get distance
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

	//init


}
