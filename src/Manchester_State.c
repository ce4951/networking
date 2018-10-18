/*
 * Manchester_State.c
 *
 *  Created on: Oct 6, 2018
 *      Author: larsonma
 */

#include "../inc/Manchester_State.h"
#include "../inc/gpio.h"

static uint8_t RX;
static volatile EXTI *EXTI0 = (EXTI *) 0x40013C00;
static volatile GPIOx *GPIOC = (GPIOx *) 0x40020800;

static volatile enum STATES state;

static void initLEDs();
static void setLED(enum STATES state);

void init_state(){
	state = IDLE;
	RX = 1;
	initLEDs();

	setLED(state);

	//start channel interrupt and timer interrupt
	init_RX_channel();
	init_interrupt_timer();
}

enum STATES getState(){
	return state;
}

static void initLEDs(){
	//enable GPIOC clock
	enable_clock('C');

	//GPIOC clock already selected
	//set GPIOC pin 1,2,3 to output for LEDs
	set_pin_mode('C', 1, OUTPUT);
	set_pin_mode('C', 2, OUTPUT);
	set_pin_mode('C', 3, OUTPUT);
}

static void setLED(enum STATES state){
	switch(state){
		case IDLE:
			GPIOC -> BSSR |= (((0b110 << 1) << 16) | (0b001 << 1));
			break;
		case BUSY:
			GPIOC -> BSSR |= (((0b101 << 1) << 16) | (0b010 << 1));
			break;
		case COLLISION:
			GPIOC -> BSSR |= (((0b011 << 1) << 16) | (0b100 << 1));
			break;
		default:
			break;
	}
}

//Timer has expired
void TIM2_IRQHandler(void){
	//Set state according to what was previously captured
	if(RX == 0){
		state = COLLISION;
	}else{
		state = IDLE;
	}

	// Obtain the most recent RX value
	RX = (GPIOC -> IDR) & (1 << 0);

	// Set LEDs to match state
	setLED(state);

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

	// Set LEDs to match state
	setLED(state);

	//clear the status bits for the timer and RX
	*(TIM2_SR) &= ~(1<<2);
	EXTI0 -> PR |= 1<<0;
}

