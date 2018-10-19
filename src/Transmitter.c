/*
 * Transmit.c
 *
 *  Created on: Oct 7, 2018
 *      Author: larsonma
 */

#include "Transmitter.h"
#include <stdbool.h>
#include "Manchester_State.h"
#include "uart_driver.h"

typedef struct {
	unsigned int position;
	unsigned int length;
	char buffer[50];
} Message;

static Message messageToSend;
static bool transferringMessage;
static volatile uint8_t manchesterBit;
static volatile int8_t bitmask;
static volatile GPIOx *GPIOC = (GPIOx *) 0x40020800;

void init_transmitter(){
	messageToSend = (Message){0,0};
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

//Attempt to send the message held in messageToSend. If successful,
//clear messageToSend and load the next message using scanf into
//messageToSend. If state becomes COLLISION, return from transmit
//and do not clear the message in messageToSend
void transmit(){
	//Make sure not in collision state
	while(getState() == IDLE && !transferringMessage){
		char temp = usart2_getch_noblock();
		if(temp != 0 && temp != '\n'){
			//character was typed, add it to the messageToSend

			messageToSend.buffer[messageToSend.position] = temp;
			messageToSend.position++;
			messageToSend.length++;

		}else if(temp != 0 && temp == '\n'){
			//end message - start clock
			messageToSend.position = 0;
			transferringMessage = true;
			*(TIM5_CR1) |= 1;
		}
	}
}

void TIM5_IRQHandler(){
	if(getState() != COLLISION){
		if(messageToSend.position < messageToSend.length){
			//get the character to be sent
			uint8_t byteToSend = (messageToSend.buffer[messageToSend.position]);

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
					messageToSend.position++;	// Comment out to send infinite stream of data
					bitmask = 7;
				}
			}
		}else{
			//Done receivingMessage the message
			*(TIM5_CR1) &= ~(1 << 0);
			messageToSend.position = 0;
			messageToSend.length = 0;
			transferringMessage = false;
			GPIOC -> ODR |= (1 << 4);
		}

	}else{
		//could not finish message and needs to re-transfer
		messageToSend.position = 0;
		*(TIM5_CR1) &= ~(1 << 0);
		GPIOC -> ODR |= (1 << 4);
	}

	//clear flag
	*(TIM5_SR) &= ~(1<<2);
}

