/*
 * RX.c
 *
 *  Created on: Oct 6, 2018
 *      Author: larsonma
 */

#include "RX.h"

static volatile EXTI *EXTI6 = (EXTI *) 0x40013C00;

void init_RX_channel(){
	//Setup PC6 on the GPIO ports

	//Enable GPIO clock
	enable_clock('C');

	//Set to alternate function mode
	set_pin_mode('C', 6, ALTFUNC);

	//set alternative function to use - TIM3, Channel 1
	set_alt_func('C', 6, 2)

	//Enable SYSCFGEN
	(*APB2ENR) |= 1<<14;

	//Set port A for SYSCFG
	(*EXTICR2) &= ~((0b1111) << 8);
	(*EXTICR2) |= (0b0010 << 8);

	//Enable EXTI interrupt
	EXTI6->IMR |= 1<<6;

	//Enable interrupt on rising edge
	EXTI6->RTSR |= 1<<6;

	//Enable interrupt on falling edge
	EXTI6->FTSR |= 1<<6;

	//PC6 is connected to EXTI6
	//enable in NVIC
	*(NVIC_ISER0) |= 1<<23;

	//Set the pin to a lower priority
	*(NVIC_IPR5) |= (0xF0 << 24);
}

