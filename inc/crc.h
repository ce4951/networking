/*
 * crc.h
 *
 *  Created on: Oct 24, 2018
 *      Author: piparocj
 */

// Compiler guard
#ifndef CRC_H
#define CRC_H

#include <inttypes.h>
#include <stdbool.h>

#define CRC8_ELEMENTS 256					// Number of elements in a CRC8 lookup table
#define CRC8_MASK     0x80				// CRC8 mask to test if it is the MSB
#define BITS_PER_BYTE 8

/*
 * Initialize the CRC by computing the CRC8 lookup table
 */
extern void init_CRC();

/*
 * Take a message to transmit and calculate the CRC value to send
 *
 * @param data - The data of the message to transmit
 * @param size - The number of bytes in 'data'
 *
 * @return - The value of the calculated CRC
 */
extern uint8_t encode_CRC(const char *data, uint8_t size);

/*
 * Take received data and determine if there were any errors through CRC
 *
 * @param data - The data that was received
 * @param size - The number of bytes in 'data'
 *
 * @return - True if no errors, false if errors
 */
extern bool decode_CRC(const char *data, uint8_t size);

#endif	// End compiler guard
