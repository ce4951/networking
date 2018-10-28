/*
 * main.c
 *
 *  Created on: Feb 17, 2017
 *      Author: Mitchell Larson
 * This is the main application for a system that monitors pedestrian
 * traffic using an infared tripwire. The system can be set to one of
 * 3 different modes. A scanning mode, an alarm mode, and an admin mode
 */

#include <stdlib.h>

#include "Manchester_State.h"
#include "gpio.h"
#include "Transmitter.h"
#include "uart_driver.h"
#include "receiver.h"
#include "crc.h"

#define F_CPU 16000000UL
#define baud 19200

typedef struct{
	char buffer[5 + 3 + 256];
	char command[5];
	uint8_t dest;
	char message[256];
	uint8_t messageLength;
	uint8_t location;
} UserInput;

static const char USAGE[] = "Usage:\r\n"
							"<Command> <Address> <Message>\r\n"
							"Example: Send 15 Hello\r\n";
static UserInput input;

static void printUsage();
static UserInput* getInput();

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
	init_CRC();
	init_state();
	init_usart2(baud, F_CPU);
	init_receiver();
	init_transmitter();

	printUsage();

	input.location = 0;

	enum STATES currentState = getState();

	while(1){
		currentState = getState();

		UserInput* command = getInput();

		switch(currentState){
			case IDLE:
				if(command){
					if(transmit(command->dest, command->message, strlen(command->message))){
						printUsage();
					}
				}
				break;
			case BUSY:
				receive();
				break;
			case COLLISION:
				break;
			default:
				break;
		}
	}

	return 0;
}

static UserInput* getInput(){
	char temp = usart2_getch_noblock();
	if(temp != 0 && temp != '\n'){
		//character was typed, add it to the messageToSend
		input.buffer[input.location] = temp;
		input.location++;
	}else if(temp != 0 && temp == '\n'){
		input.buffer[input.location] = '\0';
		char* command = strtok(input.buffer, " ");
		char* address = strtok('\0', " ");
		char* message = strtok('\0', " ");
		char* next_token = strtok('\0', " ");

		if(!(command && address && message) || next_token){
			printUsage();
			input.location = 0;
			return '\0';
		}

		strncpy(input.command, command, 5);
		strncpy(input.message, message, 256);

		char** end;
		input.dest = strtol(address, end, 10);

		input.location = 0;
		return &input;
	}
	return '\0';
}

static void printUsage(){
	for(int i = 0; USAGE[i] != '\0'; i++){
		usart2_putch(USAGE[i]);
	}
}
