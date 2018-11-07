/*
 * interrupt_timer.h
 *
 *  Created on: Oct 6, 2018
 *      Author: larsonma
 */

#ifndef INTERRUPT_TIMER_H_
#define INTERRUPT_TIMER_H_

#include <inttypes.h>
#include "RCC.h"
#include "nvic.h"

//NVIC constants
#define NVIC_ISER0 (volatile uint32_t*)		0xE000E100

//TIM2 constants
#define TIM2_PSC 	(volatile uint32_t*)	0x40000028
#define TIM2_ARR	(volatile uint32_t*)	0x4000002C
#define TIM2_CCR1	(volatile uint32_t*)	0x40000034
#define TIM2_CCR2	(volatile uint32_t*)	0x40000038
#define TIM2_CCMR1	(volatile uint32_t*)	0x40000018
#define TIM2_CCER	(volatile uint32_t*)	0x40000020
#define TIM2_CR1	(volatile uint32_t*)	0x40000000
#define TIM2_EGR	(volatile uint32_t*)	0x40000014
#define TIM2_DIER	(volatile uint32_t*)	0x4000000C
#define TIM2_SR		(volatile uint32_t*)	0x40000010
#define TIM2_CNT	(volatile uint32_t*)	0x40000024

//RCC constants
//#define RCC_BASE	(volatile uint32_t*)	0x40023800
//#define APB2ENR		(volatile uint32_t*)	0x40023844
//#define APB1ENR		(volatile uint32_t*)	0x40023840

extern void init_interrupt_timer();

#endif /* INTERRUPT_TIMER_H_ */
