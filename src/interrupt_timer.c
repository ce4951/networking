/*
 * interrupt_timer.c
 *
 *  Created on: Oct 6, 2018
 *      Author: larsonma
 */

#include "interrupt_timer.h"

void init_interrupt_timer(){
	//enable clock for TIM2
	*(APB1ENR) |= 1;

	//reload set to 1.11 ms
	*(TIM2_ARR) = (17760-1);	// 1/16000000 * 17760 = 1.11ms

	//compare to 1.11 ms
	*(TIM2_CCR2) = (17760-1);

	//select output mode (0b001)
	*(TIM2_CCMR1) &= ~(0b111<<12);
	*(TIM2_CCMR1) |= 0b001<<12;

	//make OC2 signal an output on corresponding pin5
	*(TIM2_CCER) |= 1<<4;

	//enable interrupt
	*(TIM2_DIER) |= 1<<2;

	//enable in NVIC
	*(NVIC_ISER0) |= 1<<28;

	//enable the counter by setting CEN bit in CR1
	*(TIM2_CR1) |= 1;

}
