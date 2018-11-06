/*
 * crc.c
 *
 *  Created on: Oct 24, 2018
 *      Author: piparocj
 */

#include "crc.h"

static const uint8_t polynomial = 0x07; 	// x^8 + x^2 + x + 1 = 100000111 = 0x107 = 0x07
static uint8_t crc_table[CRC8_ELEMENTS];	// CRC8 lookup table

// Helper function to calculate CRC
static uint8_t calculate_CRC(const char *data, uint8_t size);

// Set up CRC lookup table
void init_CRC()
{
    // Iterate over all elements to fill lookup table
    for (uint32_t i = 0; i < CRC8_ELEMENTS; i++)
    {
        uint8_t byte = (uint8_t)i;

        // Calculate the CRC value of the current byte to add it to the lookup table
        for(uint8_t j = 0; j < BITS_PER_BYTE; j++)
        {
        	// Only should XOR if MSB is set
            if(byte & CRC8_MASK)
            {
                byte <<= 1;
                byte ^= polynomial;
            }
            else
            {
                byte <<= 1;
            }
        }

        // Add CRC to lookup table
        crc_table[i] = byte;
    }
}

// Calculate CRC to send
uint8_t encode_CRC(const char *data, uint8_t size)
{
	return calculate_CRC(data, size);
}

// Use CRC to detect if there were errors in received data
bool decode_CRC(const char *data, uint8_t size, uint8_t fcs)
{
	// Calculated CRC will return 0 (false) if no errors
	return !(calculate_CRC(data, size) ^ fcs);
}

// Helper function to calculate CRC
uint8_t calculate_CRC(const char *data, uint8_t size)
{
	  uint8_t crc = 0;

	  // Calculate cumulative CRC for each byte in data
	  for(int i = 0; i < size; i++)
	  {
	    crc = crc_table[crc ^ data[i]];
	  }

	  return crc;
}
