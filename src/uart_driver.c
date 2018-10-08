/*
 * uart_driver.c
 *
 *  Created on: Nov 8, 2016
 *      Author: barnekow
 *  Edited on:  Feb 3, 2017
 *  	Author: Mitchell Larson
 */
#include "uart_driver.h"
#include <stdio.h>

static volatile RingBuffer* sendBuffer;
static volatile RingBuffer* recieveBuffer;

static void enable_buffered_transfer(volatile RingBuffer* in,
									 volatile RingBuffer* out);


char usart2_getch(){
	char c = get(recieveBuffer);

	if (c == '\r'){  // If character is CR
		usart2_putch('\n');  // send it
		c = '\n';   // Return LF. fgets is terminated by LF
	}

	return c;
}

char usart2_getch_noblock(){
	if(hasElement(recieveBuffer)){
		char c = get(recieveBuffer);

		if (c == '\r'){  // If character is CR
			usart2_putch('\n');  // send it
			c = '\n';   // Return LF. fgets is terminated by LF
		}

		return c;
	}

	return 0;
}

void usart2_putch(char c){
		put(sendBuffer,c);
		*(USART_CR1) |= (1<<TXEIE); //enable TXE interrupt
}

void init_usart2(uint32_t baud, uint32_t sysclk){
	// Enable clocks for GPIOA and USART2
	*(RCC_AHB1ENR) |= (1<<GPIOAEN);
	*(RCC_APB1ENR) |= (1<<USART2EN);

	// Function 7 of PORTA pins is USART
	*(GPIOA_AFRL) &= (0xFFFF00FF); // Clear the bits associated with PA3 and PA2
	*(GPIOA_AFRL) |= (0b01110111<<8);  // Choose function 7 for both PA3 and PA2
	*(GPIOA_MODER) &= (0xFFFFFF0F);  // Clear mode bits for PA3 and PA2
	*(GPIOA_MODER) |= (0b1010<<4);  // Both PA3 and PA2 in alt function mode

	// Set up USART2
	//USART2_init();  //8n1 no flow control
	// over8 = 0..oversample by 16
	// M = 0..1 start bit, data size is 8, 1 stop bit
	// PCE= 0..Parity check not enabled
	// no interrupts... using polling
	*(USART_CR1) = (1<<UE)|(1<<TE)|(1<<RE); // Enable UART, Tx and Rx
	*(USART_CR2) = 0;  // This is the default, but do it anyway
	*(USART_CR3) = 0;  // This is the default, but do it anyway
	*(USART_BRR) = sysclk/baud;


	static volatile RingBuffer sendBuffer = {0,0};
	static volatile RingBuffer recieveBuffer = {0,0};
	enable_buffered_transfer(&recieveBuffer, &sendBuffer);

	/* I'm not sure if this is needed for standard IO*/
	 //setvbuf(stderr, NULL, _IONBF, 0);
	 //setvbuf(stdin, NULL, _IONBF, 0);
	 setvbuf(stdout, NULL, _IONBF, 0);
}

static void enable_buffered_transfer(volatile RingBuffer* in,
									 volatile RingBuffer* out){
	//set the in and out buffers
	sendBuffer = out;
	recieveBuffer = in;
	
	//enable interrupts for the RNXE flag
	*(NVIC_ISER1) |= 1<<6;
	*(USART_CR1) |= (1<<RXNEIE);
}

void USART2_IRQHandler(void){
	//check what triggered the interrupt
	if((*(USART_SR)&1<<RXNE)==1<<RXNE){		//read data ready
		char c = (char) *USART_DR;
		if(hasSpace(recieveBuffer)){
			put(recieveBuffer,c);	//put character on the receive buffer
		}

		//echo back to transmit buffer
		if(hasSpace(sendBuffer)){
			if(c==BACK_SPACE){		//In ascii mode, backspace == 177.
				usart2_putch('\b');	//Instead, echo back the \'b'
			}else{
				usart2_putch(c);
			}
		}
	}else{
		if(hasElement(sendBuffer)){
			*(USART_DR) = get(sendBuffer);	//send character to terminal
		}else{
			*(USART_CR1) &= ~(1<<TXEIE);	//disable TXE interrupt
		}
	}
}

