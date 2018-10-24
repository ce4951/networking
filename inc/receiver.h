/*
 * receiver.h
 *
 *  Created on: Oct 10, 2018
 *      Author: piparocj
 */

#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Manchester_State.h"
#include "Transmitter.h"
#include "uart_driver.h"

// TIM3 constants 0x4000 0400
#define TIM3_PSC 	(volatile uint32_t*)	0x40000428
#define TIM3_ARR	(volatile uint32_t*)	0x4000042C
#define TIM3_CCR1	(volatile uint32_t*)	0x40000434
#define TIM3_CCR2	(volatile uint32_t*)	0x40000438
#define TIM3_CCMR1	(volatile uint32_t*)	0x40000418
#define TIM3_CCER	(volatile uint32_t*)	0x40000420
#define TIM3_CR1	(volatile uint32_t*)	0x40000400
#define TIM3_EGR	(volatile uint32_t*)	0x40000414
#define TIM3_DIER	(volatile uint32_t*)	0x4000040C
#define TIM3_SR		(volatile uint32_t*)	0x40000410
#define TIM3_CNT	(volatile uint32_t*)	0x40000424

// RCC constants
#define RCC_BASE	(volatile uint32_t*)	0x40023800
#define APB2ENR		(volatile uint32_t*)	0x40023844
#define APB1ENR		(volatile uint32_t*)	0x40023840

extern void init_receiver();
extern void receive();

#endif
