/*
 * Transmit.c
 *
 *  Created on: Oct 7, 2018
 *      Author: larsonma
 */

#include "Transmitter.h"
#include "Manchester_State.h"
#include "uart_driver.h"
#include "crc.h"

#define FRAME_SYNC		0x55
#define FRAME_V			0x01
#define FRAME_SOURCE	21
#define CRC_FLAG		0x01

#define MAX_NODES 25
#define SUCCESS 0
#define ERROR 1

static Frame frameToSend;
static bool transferringMessage;
static volatile uint8_t manchesterBit;
static volatile int8_t bitmask;
static volatile GPIOx *GPIOC = (GPIOx *) 0x40020800;

static void package_frame(uint8_t dest, char* message, uint8_t length, uint8_t crc);


void init_transmitter(){
	frameToSend = (Frame){0,0};
	transferringMessage = false;
	manchesterBit = 0;
	bitmask = 7;

	//Setup GPIO pin for sending data
	set_pin_mode('C', 4, OUTPUT);

	//set GPIO pin high
	GPIOC -> ODR |= (1 << 4);

	//setup timer for sending data
	//enable clock for TIM5
	*(APB1ENR) |= (1 << 3);

	//reload set to 500 us
	*(TIM5_ARR) = (8000-1);	// 1/16000000 * 8000 = 500 us

	//compare to 500 us
	*(TIM5_CCR2) = (8000-1);

	//select output mode (0b001)
	*(TIM5_CCMR1) &= ~(0b111<<12);
	*(TIM5_CCMR1) |= 0b001<<12;

	//make OC2 signal an output on corresponding pin5
	*(TIM5_CCER) |= 1<<4;

	//enable interrupt
	*(TIM5_DIER) |= 1<<2;

	//enable in NVIC (50)
	*(NVIC_ISER1) |= 1<<18;

	//set lower interrupt priority
	*(NVIC_IPR12) |= (0xFF << 16);

	//Don't enable the counter. Nothing to Transfer yet
}

bool is_transmitting(){
	return transferringMessage;
}

//Attempt to send the message held in messageToSend. If successful,
//clear messageToSend and load the next message using scanf into
//messageToSend. If state becomes COLLISION, return from transmit
//and do not clear the message in messageToSend
int transmit(int dest, char* message, int length){
	if((dest < 0 || dest > MAX_NODES || length < 0 || length > 256) && message != 0){
		return ERROR;
	}

	uint8_t crc = encode_CRC(message, length);
	package_frame(dest, message, length, crc);

	//start clock
	transferringMessage = true;
	frameToSend.position = 0;
	*(TIM5_CR1) |= 1;

	return SUCCESS;
}

void package_frame(uint8_t dest, char* message, uint8_t length, uint8_t crc){
	int frameLength = length + 7;
	char packedFrame[frameLength];
	frameToSend.length = frameLength;

	packedFrame[0] = FRAME_SYNC;
	packedFrame[1] = FRAME_V;
	packedFrame[2] = FRAME_SOURCE;
	packedFrame[3] = dest;
	packedFrame[4] = length;
	packedFrame[5] = CRC_FLAG;
	strncpy(&packedFrame[6], message, length);
	packedFrame[6 + length] = crc;

	strncpy(frameToSend.message, packedFrame, length + 7);
}

void TIM5_IRQHandler(){
	if(getState() != COLLISION){
		if(frameToSend.position < frameToSend.length){
			//get the character to be sent
			uint8_t byteToSend = (frameToSend.message[frameToSend.position]);

			//move the bit to be sent to position 0
			byteToSend = byteToSend >> bitmask;

			//Bit is now at position 0, apply XNOR
			byteToSend = ~(byteToSend^(manchesterBit));
			byteToSend &= 0x01;

			//toggle the manchester bit
			manchesterBit = ~manchesterBit;

			//Set the GPIO pin according to bit 0
			GPIOC -> BSSR |= (((~byteToSend << 4) << 16) | (byteToSend << 4));

			//if the manchester bit is 0, next bit needed
			if((manchesterBit & 0x01) == 0x00){
				bitmask--;

				//if the bitmask is 8, the character has been sent
				if(bitmask == -1){
					frameToSend.position++;	// Comment out to send infinite stream of data
					bitmask = 7;
				}
			}
		}else{
			//Done receivingMessage the message
			*(TIM5_CR1) &= ~(1 << 0);
			frameToSend.position = 0;
			frameToSend.length = 0;
			transferringMessage = false;
			GPIOC -> ODR |= (1 << 4);
		}

	}else{
		//could not finish message and needs to re-transfer
		frameToSend.position = 0;
		*(TIM5_CR1) &= ~(1 << 0);
		GPIOC -> ODR |= (1 << 4);
	}

	//clear flag
	*(TIM5_SR) &= ~(1<<2);
}

