/*
 * Collision_Delay.h
 *
 *  Created on: Oct 29, 2018
 *      Author: larsonma
 */

#ifndef COLLISION_DELAY_H_
#define COLLISION_DELAY_H_

#include <inttypes.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Manchester_State.h"

//SysTic constants
#define APB2ENR (volatile uint32_t*) 0x40023844
#define TIM9_PSK (volatile uint32_t*) 0x40014028
#define TIM9_CCMR1 (volatile uint32_t*) 0x40014018
#define TIM9_CCER (volatile uint32_t*) 0x40014020
#define TIM9_ARR (volatile uint32_t*) 0x4001402C
#define TIM9_CCR1 (volatile uint32_t*) 0x40014034
#define TIM9_CR1 (volatile uint32_t*) 0x40014000
#define TIM9_SR (volatile uint32_t*) 0x40014010
#define TIM9_CNT (volatile uint32_t*) 0x40014024

extern void init_collision_delay();
extern void setDelayTimeout();
extern bool collisionTimeExpired();

#endif /* COLLISION_DELAY_H_ */
