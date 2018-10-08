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

static volatile GPIOx *GPIOC = (GPIOx *) 0x40020800;
static void setLED(enum STATES state);

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

	//GPIOC clock already selected
	//set GPIOC pin 1,2,3 to output for LEDs
	set_pin_mode('C', 1, OUTPUT);
	set_pin_mode('C', 2, OUTPUT);
	set_pin_mode('C', 3, OUTPUT);

	enum STATES lastState = getState();
	enum STATES currentState = getState();

	char message[50];

	setLED(currentState);

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

static void setLED(enum STATES state){
	GPIOC -> ODR &= ~(0b111 << 1);

	switch(state){
		case IDLE:
			GPIOC -> ODR |= (0b001 << 1);
			break;
		case BUSY:
			GPIOC -> ODR |= (0b010 << 1);
			break;
		case COLLISION:
			GPIOC -> ODR |= (0b100 << 1);
			break;
		default:
			break;
	}
}
