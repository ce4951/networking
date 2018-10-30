/*
 * Collision_Delay.c
 *
 *  Created on: Oct 29, 2018
 *      Author: larsonma
 */

#include "Collision_Delay.h"

#define N_MAX 1000

static bool timeoutObserved;
static bool timeoutSet;

void init_collision_delay(){
	//enable clock for TIM2
	*(APB2ENR) |= (1 << 16);

	//load 16000 into STK_LOAD
	*(TIM9_PSK) = 16000;//1ms

	//select output mode (0b001)
	*(TIM9_CCMR1) &= ~(0b111<<4);
	*(TIM9_CCMR1) |= 0b001<<4;

	//make OC2 signal an output on corresponding pin5
	*(TIM9_CCER) |= 1<<0;

	*(TIM9_ARR) = (955);

	//compare to radnom milliseconds
	*(TIM9_CCR1) = (955);

	// *** Need to bypass weird behavior where prescalar is ignored at first***

	//enable the counter by setting CEN bit in CR1
	*(TIM9_CR1) |= 1;

	while((*(TIM9_SR) & (1 << 1)) != (0b10)){}

	*(TIM9_CR1) &= ~(1 << 0);
	*(TIM9_SR) &= ~(1 << 1);
	*(TIM9_CNT) = 0;

	// ***Bypassed***

	//initialize random number generator
	srand(234523089);

	timeoutObserved = true;
	timeoutSet = false;
}

void setDelayTimeout(){
	if(timeoutObserved){
		uint16_t n = (((float)(rand() % N_MAX)) / ((float)N_MAX)) * 1000;

		//reload set to random amount of milliseconds
		*(TIM9_ARR) = (n);

		//compare to radnom milliseconds
		*(TIM9_CCR1) = (n);

		//enable the counter by setting CEN bit in CR1
		*(TIM9_CR1) |= 1;

		timeoutObserved = false;
		timeoutSet = true;
	}
}

bool collisionTimeExpired(){
	bool timeExpired = (*(TIM9_SR) & (1 << 1)) == (0b10);

	if(timeoutSet && timeExpired){
		//disable the counter by setting CEN bit in CR1
		*(TIM9_CR1) &= ~(1 << 0);
		*(TIM9_SR) &= ~(1 << 1);
		*(TIM9_CNT) = 0;
		timeoutObserved = true;
		timeoutSet = false;
		return true;
	}else if(!timeoutSet){
		return true;
	}

	return false;
}
