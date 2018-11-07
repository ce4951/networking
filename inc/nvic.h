/**
****************************************************************
** @author Christopher Piparo <piparocj@msoe.edu>
** @file nvic.h
**
****************************************************************
**
** This file creates structs for registers needed to use
** and initialize the NVIC peripheral.
**
****************************************************************
*/


/** Compiler guard **/
#ifndef NVIC_H
#define NVIC_H

/** Includes **/
#include <inttypes.h>

/** Defines **/

// Peripheral base addresses
#define NVIC_BASE   0xE000E100

/** Variables **/
	//none

/** structs **/
/* NVIC memory layout */
typedef struct
{
	uint32_t ISER0;
	uint32_t ISER1;
	uint32_t ISER2;
	const uint32_t unused0[((0x80 - 0x08) / 4) - 1];
	uint32_t ICER0;
	uint32_t ICER1;
	uint32_t ICER2;
	const uint32_t unused1[((0x100 - 0x88) / 4) - 1];
	uint32_t ISPR0;
	uint32_t ISPR1;
	uint32_t ISPR2;
	const uint32_t unused2[((0x180 - 0x108) / 4) - 1];
	uint32_t ICPR0;
	uint32_t ICPR1;
	uint32_t ICPR2;
	const uint32_t unused3[((0x200 - 0x188) / 4) - 1];
	uint32_t IABR0;
	uint32_t IABR1;
	uint32_t IABR2;
	const uint32_t unused4[((0x300 - 0x208) / 4) - 1];
	uint32_t IPR0;
	uint32_t IPR1;
	uint32_t IPR2;
	uint32_t IPR3;
	uint32_t IPR4;
	uint32_t IPR5;
	uint32_t IPR6;
	uint32_t IPR7;
	uint32_t IPR8;
	uint32_t IPR9;
	uint32_t IPR10;
	uint32_t IPR11;
	uint32_t IPR12;
	uint32_t IPR13;
	uint32_t IPR14;
	uint32_t IPR15;
	uint32_t IPR16;
	uint32_t IPR17;
	uint32_t IPR18;
	uint32_t IPR19;
	uint32_t IPR20;
	const uint32_t unused5[((0xE00 - 0x320) / 4) - 1];
	uint32_t STIR;
} NVIC;

/** Prototypes **/
	//none

#endif // End compiler guard
