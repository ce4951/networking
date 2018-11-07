
/** Includes **/
#include "gpio.h"

/** Helper function prototypes **/
static volatile GPIO* assign_port(char port);

/** Variables **/
// Peripheral addresses
static volatile GPIO *gpioa = (GPIO *)GPIOA_BASE;
static volatile GPIO *gpiob = (GPIO *)GPIOB_BASE;
static volatile GPIO *gpioc = (GPIO *)GPIOC_BASE;
//static volatile RCC  *rcc   = (RCC  *)RCC_BASE;

/** Functions **/
// Set GPIO pin mode
void set_pin_mode(char port, uint8_t pin, GPIO_MODE mode)
{
	// Get the port address to access
	volatile GPIO *selected_port = assign_port(port);

	// Clear pins associated with pin mode
	selected_port->MODER &= ~(0b11 << (pin*2));

	// Set the desired mode
	selected_port->MODER |= (mode << (pin * 2));
}

// Set GPIO pin output type
void set_pin_output_type(char port, uint8_t pin, GPIO_TYPE type)
{
	// Get the port address to access
	volatile GPIO *selected_port = assign_port(port);

	// Clear pin specified
	selected_port->OTYPER &= ~(1<<pin);

	// Set the desired type
	selected_port->OTYPER |= (type << pin);
}

// Set GPIO pin output speed
void set_output_speed(char port, uint8_t pin, GPIO_SPEED speed)
{
	// Get the port address to access
	volatile GPIO *selected_port = assign_port(port);

	// Clear speed set at specified pin
	selected_port->OSPEEDR &= ~(0b11<<(pin*2));

	// Set the desired speed
	selected_port->OSPEEDR |= (speed << (pin * 2));
}

// Set GPIO pin pull-up/pull-down resistors
void set_pin_PUPDR(char port, uint8_t pin, GPIO_PUPDR pupdr)
{
	// Get the port address to access
	volatile GPIO *selected_port = assign_port(port);

	// Clear pull type set at specified pin
	selected_port->PUPDR &= ~(0b11<<(pin*2));

	// Set the desired resistor
	selected_port->PUPDR |= (pupdr << (pin * 2));
}

// Set GPIO pin to alternate function
void set_alt_func(char port, uint8_t pin, uint8_t func)
{
	// Get the port address to access
	volatile GPIO *selected_port = assign_port(port);

	// If the pin is 0-7, use the alternate function low register. If it is 8-15,
	// use the alternate function high register
	if(pin >= 0 && pin <=7)
	{
		selected_port->AFRL &= ~(0b1111 << (pin * 4));
		selected_port->AFRL |=  (func   << (pin * 4));
	}
	else if(pin >=8 && pin <= 15)
	{
		selected_port->AFRH &= ~(0b1111 << (pin * 4));
		selected_port->AFRH |=  (func   << (pin * 4));
	}
}

// Set pin output
void set_output_value(char port, uint8_t pin, GPIO_VALUE value)
{
	// Get the port address to access
	volatile GPIO *selected_port = assign_port(port);

	// Set the output value
	if(value)
	{
		selected_port->ODR |= (value << pin);
	}
	else
	{
		selected_port->ODR &= ~(value << pin);
	}
}

// Get pin input
GPIO_VALUE get_input_value(char port, uint8_t pin)
{
	// Get the port address to access
	volatile GPIO *selected_port = assign_port(port);

	return ((selected_port->IDR & (1 << pin)) >> pin);
}

void clear_and_set_output(char port, uint16_t clear, uint16_t set)
{
	// Get the port address to access
	volatile GPIO *selected_port = assign_port(port);

	selected_port->BSRR |= ((clear << 16) | set);
}

/** Helper functions **/
static volatile GPIO* assign_port(char port)
{
	switch(port)
	{
		case 'A': case 'a':
			return gpioa;
		case 'B':case 'b':
			return gpiob;
		case 'C':case 'c':
			return gpioc;
		default:
			return 0;
	}
}

