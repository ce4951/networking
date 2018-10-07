/*
 * RX.c
 *
 *  Created on: Oct 6, 2018
 *      Author: larsonma
 */

#include "RX.h"

static volatile EXTI *EXTI0 = (EXTI *) 0x40013C00;


void init_RX_channel(){
	//Setup PC0 on the GPIO ports

	//Enable GPIO clock
	enable_clock('C');

	//Set to input mode
	set_pin_mode('C', 0, INPUT);

	//Enable SYSCFGEN
	(*APB2ENR) |= 1<<14;

	//Set port A for SYSCFG
	(*EXTICR1) &= ~(0b1111);
	(*EXTICR1) |= 0b0010;

	//Enable EXTI interrupt
	EXTI0->IMR |= 1<<0;

	//Enable interrupt on rising edge
	EXTI0->RTSR |= 1<<0;

	//Enable interrupt on falling edge
	EXTI0->FTSR |= 1<<0;

	//PC0 is connected to EXTI0
	//enable in NVIC
	*(NVIC_ISER0) |= 1<<6;

	//Set the pin to a lower priority
	*(NVIC_IPR1) |= (0xFF << 16);
}

