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
