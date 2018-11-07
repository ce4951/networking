
#include "RCC.h"

static volatile RCC *rcc = (RCC *)RCC_BASE;

void enable_gpio_clock(char port)
{
	switch(port)
	{
		case 'A': case 'a':
			rcc->AHB1ENR |= (GPIOA_CLK_EN);
			break;
		case 'B': case 'b':
			rcc->AHB1ENR |= (GPIOB_CLK_EN);
			break;
		case 'C': case 'c':
			rcc->AHB1ENR |= (GPIOC_CLK_EN);
			break;
		case 'D': case 'd':
			rcc->AHB1ENR |= (GPIOD_CLK_EN);
			break;
		case 'E': case 'e':
			rcc->AHB1ENR |= (GPIOE_CLK_EN);
			break;
		case 'F': case 'f':
			rcc->AHB1ENR |= (GPIOF_CLK_EN);
			break;
		case 'G': case 'g':
			rcc->AHB1ENR |= (GPIOG_CLK_EN);
			break;
		case 'H': case 'h':
			rcc->AHB1ENR |= (GPIOH_CLK_EN);
			break;
		default:
			break;
	}
}

void enable_timer_clock(int timer)
{
	switch(timer)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		default:
			break;
	}
}


void enable_systemconfig_clock()
{

}
