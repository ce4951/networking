/*
 * Transmit.h
 *
 *  Created on: Oct 7, 2018
 *      Author: larsonma
 */

#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

//NVIC constants
#define NVIC_ISER1 (volatile uint32_t*)		0xE000E104
#define NVIC_IPR12 (volatile uint32_t*)		0xE000E430

//TIM5 constants0x4000 0C00
#define TIM5_PSC 	(volatile uint32_t*)	0x40000C28
#define TIM5_ARR	(volatile uint32_t*)	0x40000C2C
#define TIM5_CCR1	(volatile uint32_t*)	0x40000C34
#define TIM5_CCR2	(volatile uint32_t*)	0x40000C38
#define TIM5_CCMR1	(volatile uint32_t*)	0x40000C18
#define TIM5_CCER	(volatile uint32_t*)	0x40000C20
#define TIM5_CR1	(volatile uint32_t*)	0x40000C00
#define TIM5_EGR	(volatile uint32_t*)	0x40000C14
#define TIM5_DIER	(volatile uint32_t*)	0x40000C0C
#define TIM5_SR		(volatile uint32_t*)	0x40000C10
#define TIM5_CNT	(volatile uint32_t*)	0x40000C24

//RCC constants
#define RCC_BASE	(volatile uint32_t*)	0x40023800
#define APB2ENR		(volatile uint32_t*)	0x40023844
#define APB1ENR		(volatile uint32_t*)	0x40023840

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
	uint8_t position;
	uint8_t length;
	char message[255 + 7];
} Frame;

extern void init_transmitter();
extern bool is_transmitting();
extern int transmit(int dest, char* message, int length);

#endif /* TRANSMITTER_H_ */
