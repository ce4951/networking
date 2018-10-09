/*
 * main.c
 *
 *  Created on: Feb 17, 2017
 *      Author: Mitchell Larson
 * This is the main application for a system that monitors pedestrian
 * traffic using an infared tripwire. The system can be set to one of
 * 3 different modes. A scanning mode, an alarm mode, and an admin mode
 */

#include "Manchester_State.h"
#include "gpio.h"
#include "Transmitter.h"
#include "uart_driver.h"

#define F_CPU 16000000UL
#define baud 19200

/**
 * The main function for this application runs a state machine, while
 * periodically checking for a user entering the admin password. In
 * order to perform tasks, many of the tasks are accomplished by
 * calling static functions within this file
 * Inputs:
 * 		none
 * Outputs:
 * 		none
 */
int main(void){
	init_state();
	init_usart2(baud, F_CPU);
	init_transmitter();

	enum STATES currentState = getState();

	while(1){
		currentState = getState();

		switch(currentState){
			case IDLE:
				transmit();
				break;
			case BUSY:
				break;
			case COLLISION:
				break;
			default:
				break;
		}
	}

	return 0;
}
