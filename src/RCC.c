
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
			rcc->APB2ENR |= (TIM1_CLK_EN);
			break;
		case 2:
			rcc->APB1ENR |= (TIM2_CLK_EN);
			break;
		case 3:
			rcc->APB1ENR |= (TIM3_CLK_EN);
			break;
		case 4:
			rcc->APB1ENR |= (TIM4_CLK_EN);
			break;
		case 5:
			rcc->APB1ENR |= (TIM5_CLK_EN);
			break;
		case 6:
			rcc->APB1ENR |= (TIM6_CLK_EN);
			break;
		case 7:
			rcc->APB1ENR |= (TIM7_CLK_EN);
			break;
		case 8:
			rcc->APB2ENR |= (TIM8_CLK_EN);
			break;
		case 9:
			rcc->APB2ENR |= (TIM9_CLK_EN);
			break;
		case 10:
			rcc->APB2ENR |= (TIM10_CLK_EN);
			break;
		case 11:
			rcc->APB2ENR |= (TIM11_CLK_EN);
			break;
		case 12:
			rcc->APB1ENR |= (TIM12_CLK_EN);
			break;
		case 13:
			rcc->APB1ENR |= (TIM13_CLK_EN);
			break;
		case 14:
			rcc->APB1ENR |= (TIM14_CLK_EN);
			break;
		default:
			break;
	}
}


void enable_systemconfig_clock()
{
	rcc->APB2ENR |= (SYSCFG_CLK_EN);
}
