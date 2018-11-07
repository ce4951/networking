/*
 * RX.h
 *
 *  Created on: Oct 6, 2018
 *      Author: larsonma
 */

#ifndef RX_H_
#define RX_H_

#include <inttypes.h>

#include "gpio.h"
#include "RCC.h"
#include "nvic.h"

#define NVIC_ISER0 (volatile uint32_t*)		0xE000E100
//#define APB2ENR		(volatile uint32_t*)	0x40023844
#define EXTICR2		(volatile uint32_t*)	0x4001380C
#define NVIC_IPR5		(volatile uint32_t*)	0xE000E414

typedef struct{
	uint32_t IMR;
	uint32_t EMR;
	uint32_t RTSR;
	uint32_t FTSR;
	uint32_t SWIER;
	uint32_t PR;
} EXTI;


extern void init_RX_channel();

#endif /* RX_H_ */
