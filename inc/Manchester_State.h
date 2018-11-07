/*
 * Manchester_State.h
 *
 *  Created on: Oct 6, 2018
 *      Author: larsonma
 */

#ifndef MANCHESTER_STATE_H_
#define MANCHESTER_STATE_H_

#include "interrupt_timer.h"
#include "RX.h"
#include "gpio.h"
#include "RCC.h"

//#define ISPR0 (volatile uint32_t*) 0xE000E200

enum STATES {IDLE, BUSY, COLLISION};

extern void init_state();
enum STATES getState();
extern uint8_t get_rx();

#endif /* MANCHESTER_STATE_H_ */
