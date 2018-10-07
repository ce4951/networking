/*
 * Manchester_State.c
 *
 *  Created on: Oct 6, 2018
 *      Author: larsonma
 */

#include "Manchester_State.h"

static uint8_t RX;
static volatile EXTI *EXTI0 = (EXTI *) 0x40013C00;
static volatile GPIOx *GPIOC = (GPIOx *) 0x40020800;

static volatile enum STATES state;

void init_state(){
	state = IDLE;
	RX = 1;

	//start channel interrupt and timer interrupt
	init_RX_channel();
	init_interrupt_timer();
}

enum STATES getState(){
	return state;
}

//Timer has expired
void TIM2_IRQHandler(void){
	//Set state according to what was previously captured
	if(RX == 0){
		state = COLLISION;
	}else{
		state = IDLE;
	}

	RX = (GPIOC -> IDR) & (1 << 0);

	//clear flag
	*(TIM2_SR) &= ~(1<<2);
}

//Edge Has Occured
void EXTI0_IRQHandler(void){
	//Set the Timer count to original value
	*(TIM2_CNT) = 0;

	//set the state to BUSY
	state = BUSY;

	//capture RX
	RX = (GPIOC -> IDR) & (1 << 0);

	//clear the status bits for the timer and RX
	*(TIM2_SR) &= ~(1<<2);
	EXTI0 -> PR |= 1<<0;
}

