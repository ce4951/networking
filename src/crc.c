/*
 * crc.c
 *
 *  Created on: Oct 24, 2018
 *      Author: piparocj
 */

#include "crc.h"

#define	CRC8_ELEMENTS		255					// Number of elements in a CRC8 lookup table
#define CRC8_MASK			0x80				// CRC8 mask to test if it is the MSB
#define NUM_BITS_PER_BYTE	8


static const uint16_t polynomial = 0x107; 		// x^8 + x^2 + x + 1 = 100000111 = 0x107
static uint8_t crc_table[CRC8_ELEMENTS + 1];	// CRC8 lookup table

// Helper function to calculate CRC
static uint8_t calculate_CRC(const char *data, uint8_t size);

// Set up CRC lookup table
void init_CRC()
{
	// Iterate to set a value in every lookup table index
	for(uint8_t i = 0; i <= CRC8_ELEMENTS; i++)
	{
		uint8_t byte = (uint8_t)i;	// Byte to add to lookup table

		// Iterate over every bit in a byte to calculate byte value to insert
		for(uint8_t j = 0; j < NUM_BITS_PER_BYTE; j++)
		{
			byte <<= 1;
		}

		// Only XOR if it is the MSB is set
		if(byte & CRC8_MASK)
		{
			byte ^= polynomial;
		}

		// Insert byte to lookup table
		crc_table[i] = byte;
	}
}

// Calculate CRC to send
uint8_t encode_CRC(const char *data, uint8_t size)
{
	return calculate_CRC(data, size);
}

// Use CRC to detect if there were errors in received data
bool decode_CRC(const char *data, uint8_t size)
{
	// Calculated CRC will return 0 if no errors
	return !calculate_CRC(data, size);
}

// Helper function to calculate CRC
uint8_t calculate_CRC(const char *data, uint8_t size)
{
	uint8_t crc = 0;

	// Calculate CRC
	for(uint8_t i = 0; i < size; i++)
	{
		uint8_t value = (uint8_t)(data[i] ^ crc);
		crc = crc_table[value];
	}

	return crc;
}
