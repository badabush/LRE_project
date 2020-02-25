/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include <gpio_init.h>
#include <stdio.h>
#include <stdlib.h>
#include <stm32f0xx.h>
#include <stm32f072b_discovery.h>
#include <assert.h>
#include <tools.h>
#include <UART_com.h>
#include <moves.h>
#include <StepMotor.h>

#include <sonar.h>
#include <wait.h>

#define std_steps 2000
//#define std_turn 15.5
#define MillisecondsIT 1e3

/* STATUS FLAG DEFINITION
 * 0 - do nothing
 * 1 - drive forward
 * 2 - pattern XX
 * 3 - pattern XX
 * 4 - Sonar output
 * 5 - pattern XX
 * */

int status_flag = 0;
int sonar_flag = 0;
volatile int RX_flag = 0;
int TX_flag = 0;

int R_cmd = 0;
int L_cmd = 0;

// global variable for rotating direction of motor; 0 = forward, 1 = backward
int Lrot_dir = 0; // left motor
int Rrot_dir = 0; // right motor
int ds = 0; // distance to move forward [cm]
int cycle = 4096; //cycles required for moving one distance
char received_string[30];
char rt_dir[1];

int r_angle = 0; // right angle
int l_angle = 0; // left angle

//distances from sonar

int dist_L = 0;
int dist_C = 0;
int dist_R = 0;

int filt_L = 0;
int filt_C = 0;
int filt_R = 0;
char sonar_dist[30];

//flags for wall L/C/R
int wall_L = 0;
int wall_C = 0;
int wall_R = 0;

//design distance for follow wall
int des_dist = 4; //CHANGE THIS FOR DISTANCE TO WALL!!!!

//which side got detected
int side = 0; // 0=unknown, 1=R, 2=L

//Define time keeping variables
volatile uint32_t Milliseconds = 0, Seconds = 0;

//declarations for filtering
struct filter {
	int L, C, R;
};

int main(void) {

	/* ******************************************** */
	/* ********** Initialization process ********** */
	/* ******************************************** */

	//init Motor
	MotorGPIOInit();
	MotorTIMInit();
	MotorIRT();

	// init UART
	UARTGPIOInit();

	//init Sonar
	SonarInit();

	//init wait timer
	SystemInit(); //Ensure CPU is running at correctly set clock speed
	SystemCoreClockUpdate(); //Update SystemCoreClock variable to current clock speed
	SysTick_Config(SystemCoreClock / MillisecondsIT); //Set up a systick interrupt every millisecond
	/* ******************************************** */
	/* **************** Main Logic **************** */
	/* ******************************************** */
	while (1) {
		if (RX_flag == 1) {
			RX_flag = 0;
//			SendString("Main loop\n");
//			//declarations for substring operations
			char angle[3];
			char str1[2];
			char str2[2];
			char str3[5];
			char str4[6];
			substring(received_string, str1, 0, 2);
			substring(received_string, str4, 0, 6);
			if (strcmp(received_string, "mv fw\r\n") == 0) {

				SendString("Moving forwards.\n");
				cmd_forward(std_steps);
			} else if (strcmp(received_string, "mv bw\r\n") == 0) {
				SendString("Moving backwards.\n");
				cmd_backward(std_steps);

			} else if (strcmp(str1, "mv") == 0) {
				substring(received_string, str2, 3, 2);
				if (strcmp(str2, "ds") == 0) {
					substring(received_string, str3, 6, 5);
					cmd_forward(atoi(str3));
					SendString(printf("Moving Distance: %i", ds));

				} else if (strcmp(str2, "rr") == 0) {
					substring(received_string, angle, 6, 3);
					cmd_Rturn(atoi(angle));
					SendString(printf("Rotate CW: %i\r\n", ds));

				} else if (strcmp(str2, "lr") == 0) {
					substring(received_string, angle, 6, 3);
					cmd_Lturn(atoi(angle));
					SendString(printf("Rotate CCW: %i\r\n", ds));
				}
				//routine for cmds
			} else if (strcmp(received_string, "cmd park\r\n") == 0) {
				cmd_park();
			} else if (strcmp(received_string, "cmd follow\r\n") == 0) {
				cmd_follow(200);
			} else if (strcmp(received_string, "cmd corner\r\n") == 0) {
				cmd_corner();

			} else if (strcmp(received_string, "tm us\r\n") == 0) {

				sprintf(sonar_dist, "R: %5i cm, C: %5i cm, L: %5i cm\n", dist_R,
						dist_C, dist_L);
				SendString(sonar_dist);

			} else if (strcmp(received_string, "stop\r\n") == 0) {

				SendString("stop motors.\n");

			} else if (strcmp(received_string, "sandbox\r\n") == 0) {

				adjust();
			} else if (strcmp(str4, "cmd pf")==0) {
				char pf_start[2];
				char pf_end[2];
				substring(received_string, pf_start, 7, 2);
				substring(received_string, pf_end, 10, 2);
				int pf0;
				int pf9;
				pf0 = atoi(pf_start);
				pf9 = atoi(pf_end);
				assert(pf0>=0);
				assert(pf0<=48);
				assert(pf9>=0);
				assert(pf9<=48);
				cmd_pathfinder(pf0, pf9);

			} else if (strcmp(str4, "cmd se")==0) {
				char pf_start[2];
				char pf_end[2];
				substring(received_string, pf_start, 7, 2);
				substring(received_string, pf_end, 10, 2);
				int pf0;
				int pf9;
				pf0 = atoi(pf_start);
				pf9 = atoi(pf_end);
				assert(pf0>=0);
				assert(pf0<=48);
				assert(pf9>=0);
				assert(pf9<=48);
				cmd_search(pf0, pf9);

			} else if (strcmp(str4, "cmd fi")==0) {
				char pf_start[2];
				char pf_end[2];
				substring(received_string, pf_start, 7, 2);
				substring(received_string, pf_end, 10, 2);
				int pf0;
				int pf9;
				pf0 = atoi(pf_start);
				pf9 = atoi(pf_end);
				assert(pf0>=0);
				assert(pf0<=48);
				assert(pf9>=0);
				assert(pf9<=48);
				cmd_find(pf0, pf9);

			} else if (strcmp(received_string, "help\r\n") == 0) {

				SendString("*** <Help Window> ***\nUsage of commands:\n"
						"mv - Move forward\n"
						"mv ds X - Move for X distance.\n"
						"mv rr X - Rotate clockwise X°.\n"
						"mv lr X - Rotate counter clockwise X°.\n"
						"tm us - ultrasonic\n"
						"cmd follow - follow left wall.\n"
						"cmd park - drive until wall, do 180."
						"*** </Help Window> ***\n\n");

			} else {
				SendString("Instruction not known.\n");
			}
			clearRXBuffer();
			RX_flag = 0;
		}
	} //while(1)
}
