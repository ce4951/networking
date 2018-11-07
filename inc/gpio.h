
/** Compiler guard **/
#ifndef GPIO_H
#define GPIO_H
 
/** Includes **/
#include <inttypes.h>

#include "RCC.h"

/** Defines **/
// Base addresses
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOD_BASE 0x40020C00
#define GPIOE_BASE 0x40021000
#define GPIOF_BASE 0x40021400
#define GPIOG_BASE 0x40021800
#define GPIOH_BASE 0x40021C00

/** structs **/
// GPIO memory layout
typedef struct
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
} GPIO;

/** Enumerated types **/
// GPIO MODER
typedef enum
{
	INPUT,
	OUTPUT,
	ALTFUNC,
	ANALOG
} GPIO_MODE;

// GPIO OTYPER
typedef enum
{
	PUSH_PULL,
	OPEN_DRAIN
} GPIO_TYPE;

// GPIO OSPEEDER
typedef enum
{
	LOW,
	MED,
	FAST,
	HIGH
} GPIO_SPEED;

// GPIO PUPDR
typedef enum
{
	NOPULL,
	PULLUP,
	PULLDOWN
} GPIO_PUPDR;

// GPIO pin values
typedef enum
{
	OFF,
	ON
} GPIO_VALUE;

/** Prototypes **/
///**
// * Enables the clock for a given GPIO port
// *
// * @param port - The port letter to enable
// */
//void enable_clock(char port);
/**
 * Sets the mode of a pin for a desired port
 *
 * @param port - The port letter to set the pin mode of
 * @param pin - The pin number to set the mode of
 * @param mode - The mode to set the pin to
 */
void set_pin_mode(char port, uint8_t pin, GPIO_MODE mode);

/*
 * Sets the type of a port
 *
 * @param port - The port letter to set the output type of
 * @param pin - the pin number to set the output type of
 * @param type - The type to set the pin to
 */
void set_pin_output_type(char port, uint8_t pin, GPIO_TYPE type);

/**
 * Sets the speed of the output
 *
 * @param port - The port letter to set the output speed of
 * @param pin - The pin number to set the output speed of
 * @param speed - The speed which to set the output to
 */
void set_output_speed(char port, uint8_t pin, GPIO_SPEED speed);

/**
 * Set the pull-up/pull-down resistors of a port
 *
 * @param port - The port letter to set the resistors of
 * @param pin - The pin number to set the resistors of
 * @param pupdr - The direction to set the resistors to
 */
void set_pin_PUPDR(char port, uint8_t pin, GPIO_PUPDR pupdr);

/**
 * Sets an alternate function of a pin
 *
 * @param port - The port letter to set the alternate function of
 * @param pin - The pin number to set the alternate function of
 * @param func - The alternate function to set the pin to
 */
void set_alt_func(char port, uint8_t pin, uint8_t func);

/**
 * Sets a pin to specified output value
 *
 * @param port - The port letter to set the alternate function of
 * @param pin - The pin number to set the alternate function of
 * @param value - The value to set the pin to
 */
void set_output_value(char port, uint8_t pin, GPIO_VALUE value);

/**
 * Gets the value of a specified pin
 *
 * @param port - The port letter to get the value of
 * @param pin - The pin to get the value of
 *
 * @return - The value of 'pin' on 'port'
 */
GPIO_VALUE get_input_value(char port, uint8_t pin);

/**
 * Clears and sets given pins
 */
void clear_and_set_output(char port, uint16_t clear, uint16_t set);

#endif // End compiler guard
