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
#include "receiver.h"
#include "crc.h"

#define F_CPU 16000000UL
#define baud 19200

typedef struct{
	uint8_t dest;
	char buffer[5 + 3 + 256];
	char command[5];
	char address[3];
	char message[256];
	uint8_t index;
} UserInput;

static const char USAGE[] = "Usage:\r\n"
							"<Command> <Address> <Message>\r\n"
							"Example: Send 15 Hello\r\n";
static UserInput* input;

static void printUsage();
static UserInput* getInput();
static char* parseCommand();
static char* parseAddress();
static char* parseMessage();

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

	*input = (UserInput){0,0,0,0,0,0};

	enum STATES currentState = getState();

	while(1){
		currentState = getState();

		UserInput* command = getInput();

		switch(currentState){
			case IDLE:
				if(command){
					transmit(command->address, command->message);
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
		input -> buffer[input -> index] = temp;
		input -> index++;
	}else if(temp != 0 && temp == '\n'){
		input -> buffer[input -> index] = '\0';
		char* command = parseCommand();
		char* address = parseAddress();
		char* message = parseMessage();

		if(!(command && address && message)){
			printUsage();
			input -> index = 0;
			return '\0';
		}

		strncpy(input -> command, command, 5);
		strncpy(input -> address, address, 3);
		strncpy(input -> message, message, 256);
		input -> index = 0;
		return input;
	}
	return '\0';
}

static char* parseCommand(){
	char* temp = malloc(5);
	for(int i = 0; (input -> buffer[i]) != ' '; i++){
		if(i > 3) return '\0';

		temp[i] = input -> buffer[i];
	}
	temp[4] = '\0';
	return temp;
}

static char* parseAddress(){
	char* temp = malloc(3);
	for(int i = 0; (input -> buffer[i]) != ' '; i++){
		if(i > 2) return '\0';

		temp[i] = input -> buffer[i];
	}
	temp[3] = '\0';
	return temp;
}

static char* parseMessage(){
	char* temp = malloc(256);
	int i = 0;
	for(; (input -> buffer[i]) != '\0'; i++){
		if(i > 255) return '\0';

		temp[i] = input -> buffer[i];
	}
	temp[i] = '\0';
	return temp;
}

static void printUsage(){
	for(int i = 0; USAGE[i] != '\0'; i++){
		usart2_putch(USAGE[i]);
	}
}
