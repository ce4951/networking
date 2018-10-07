/*
 * Transmit.c
 *
 *  Created on: Oct 7, 2018
 *      Author: larsonma
 */

#include <Transmitter.h>

static char messageToSend[50];

void init_transmit(){

}

//Attempt to send the message held in messageToSend. If successful,
//clear messageToSend and load the next message using scanf into
//messageToSend. If state becomes COLLISION, return from transmit
//and do not clear the message in messageToSend
void transmit(){
	//scanf reads input, but blocks - need to figure this out
}

