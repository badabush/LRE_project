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
#include <tools.h>
#include <UART_com.h>
#include <lre_wait.h>

#include <moves.h>
#include <StepMotor.h>

#include <sonar.h>

#define std_steps 2000
#define std_turn 1400

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
int RX_flag = 0;
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

//distances from sonar

int dist_L = 0;
int dist_C = 0;
int dist_R = 0;
char sonar_dist[30];
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


	/* ******************************************** */
	/* **************** Main Logic **************** */
	/* ******************************************** */
	while (1) {
		if (RX_flag == 1) {
//			SendString("Main loop\n");
//			//declarations for substring operations
			char str1[2];
			char str2[2];
			char str3[5];
			substring(received_string, str1, 0, 2);
			if (strcmp(received_string, "mv fw\r\n") == 0) {

				SendString("Moving forwards.\n");
				//TODO:implement reading "mv ds *val*": read value from string to get distance.
				ds = std_steps;
				cmd_forward();
				//call pattern to drive
			} else if (strcmp(received_string, "mv bw\r\n") == 0) {
				SendString("Moving backwards.\n");
				ds = std_steps;
				cmd_backward();

			} else if (strcmp(str1, "mv") == 0) {
				substring(received_string, str2, 3, 2);
				if (strcmp(str2, "ds") == 0) {
					substring(received_string, str3, 6, 5);
					ds = atoi(str3) * 177;
					cmd_forward();
					SendString(printf("Moving Distance: %i", ds));
				} else if (strcmp(str2, "rt") == 0) {
					substring(received_string, rt_dir, 6, 1);
					if (strcmp(rt_dir, "0") == 0) {
						SendString("Rotating (+)\n");
						cmd_Rturn();
						ds = std_turn;
					} else if (strcmp(rt_dir, "1") == 0) {
						SendString("Rotating (-)\n");
						cmd_Lturn();
						ds = std_turn;
					}
				} else {
					SendString("Unknown command.\n");
				}

			} else if (strcmp(received_string, "tm ps\r\n") == 0) {

				SendString("Position: xyz\n");

			} else if (strcmp(received_string, "tm od\r\n") == 0) {

				SendString("Traveled Distance\n");

			} else if (strcmp(received_string, "tm hd\r\n") == 0) {

				SendString("Heading\n");

			} else if (strcmp(received_string, "tm cu\r\n") == 0) {

				SendString("Current usage: ? mA\n");

			} else if (strcmp(received_string, "tm us\r\n") == 0) {

				sprintf(sonar_dist, "R: %5i cm, C: %5i cm, L: %5i cm\n", dist_R,
						dist_C, dist_L);
				SendString(sonar_dist);

			} else if (strcmp(received_string, "stop\r\n") == 0) {

				SendString("stop motors.\n");

			} else if (strcmp(received_string, "help\r\n") == 0) {

				SendString("*** <Help Window> ***\nUsage of commands:\n"
						"mv - Move forward\n"
						"mv ds X - Move for X distance.\n"
						"mv rt 0 - Rotate right.\n"
						"mv rt 1 - Rotate left.\n"
						"tm ps - position\n"
						"tm od - odometry\n"
						"tm hd - heading\n"
						"tm cu - current\n"
						"tm us - ultrasonic\n"
						"*** </Help Window> ***\n\n");

			} else {
				SendString("Instruction not known, type help for commands.\n");
			}

			clearRXBuffer();
			RX_flag = 0;
		}
//		//set **global_flag** from USART IRQHandler, do something *here* (asking for flags, doing commands from here)
	}
}
