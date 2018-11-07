
/** Compiler guard **/
#ifndef RCC_H
#define RCC_H

/** Includes **/
#include <inttypes.h>

/** Defines **/
// Base address
#define RCC_BASE 0x40023800

// AHB1 clocks
#define GPIOA_CLK_EN	(1 << 0)
#define GPIOB_CLK_EN	(1 << 1)
#define GPIOC_CLK_EN	(1 << 2)
#define GPIOD_CLK_EN	(1 << 3)
#define GPIOE_CLK_EN	(1 << 4)
#define GPIOF_CLK_EN	(1 << 5)
#define GPIOG_CLK_EN	(1 << 6)
#define GPIOH_CLK_EN	(1 << 7)
#define CRC_CLK_EN		(1 << 12)
#define DMA1_CLK_EN		(1 << 21)
#define DMA2_CLK_EN		(1 << 22)
#define OTGHS_CLK_EN	(1 << 29)

// AHB2 clocks
#define DMCI_CLK_EN		(1 << 0)
#define OTGFS_CLK_EN	(1 << 7)

// AHB3 clocks
#define FMC_CLK_EN		(1 << 0)
#define QSPE_CLK_EN		(1 << 1)

// APB1 clocks
#define TIM2_CLK_EN		(1 << 0)
#define TIM3_CLK_EN		(1 << 1)
#define TIM4_CLK_EN		(1 << 2)
#define TIM5_CLK_EN		(1 << 3)
#define TIM6_CLK_EN		(1 << 4)
#define TIM7_CLK_EN		(1 << 5)
#define TIM12_CLK_EN	(1 << 6)
#define TIM13_CLK_EN	(1 << 7)
#define TIM14_CLK_EN	(1 << 8)
#define WWDG_CLK_EN		(1 << 11)
#define SPI2_CLK_EN		(1 << 14)
#define SPI3_CLK_EN		(1 << 15)
#define SPDIFRX_CLK_EN	(1 << 16)
#define UART2_CLK_EN	(1 << 17)
#define UART3_CLK_EN	(1 << 18)
#define UART4_CLK_EN	(1 << 19)
#define UART5_CLK_EN	(1 << 20)
#define I2C1_CLK_EN		(1 << 21)
#define I2C2_CLK_EN		(1 << 22)
#define I2C3_CLK_EN		(1 << 23)
#define FMPI2C1_CLK_EN	(1 << 24)
#define CAN1_CLK_EN		(1 << 25)
#define CAN2_CLK_EN		(1 << 26)
#define CEC_CLK_EN		(1 << 27)
#define PWR_CLK_EN		(1 << 28)
#define DAC_CLK_EN		(1 << 29)

// APB2 clocks
#define TIM1_CLK_EN		(1 << 0)
#define TIM8_CLK_EN		(1 << 1)
#define USART1_CLK_EN	(1 << 4)
#define USART2_CLK_EN	(1 << 5)
#define ADC_CLK_EN		(1 << 8)
#define SDIO_CLK_EN		(1 << 11)
#define SPI1_CLK_EN		(1 << 12)
#define SPI4_CLK_EN		(1 << 13)
#define SYSCFG_CLK_EN	(1 << 14)
#define TIM9_CLK_EN		(1 << 16)
#define TIM10_CLK_EN	(1 << 17)
#define TIM11_CLK_EN	(1 << 18)
#define SAI1_CLK_EN		(1 << 22)
#define SAI2_CLK_EN		(1 << 23)

/** structs **/
// RCC memory layout
typedef struct
{
	uint32_t CR;
	uint32_t PLLCFGR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;
	uint32_t AHB3RSTR;
	const uint32_t unused0;
	uint32_t APB1RSTR;
	uint32_t APB2RSTR;
	const uint32_t unused1[((0x30 - 0x24) / 4) - 1];
	uint32_t AHB1ENR;
	uint32_t AHB2ENR;
	uint32_t AHB3ENR;
	const uint32_t unused2;
	uint32_t APB1ENR;
	uint32_t APB2ENR;
	const uint32_t unused3[((0x50 - 0x44) / 4) - 1];
	uint32_t AHB1LPENR;
	uint32_t AHB2LPENR;
	uint32_t AHB3LPENR;
	uint32_t unused4;
	uint32_t APB1LPENR;
	uint32_t APB2LPENR;
	const uint32_t unused5[((0x70 - 0x64) / 4) - 1];
	uint32_t BDCR;
	uint32_t CSR;
	const uint32_t unused6[((0x80 - 0x74) / 4) - 1];
	uint32_t SSCGR;
	uint32_t PLLI2SCFGR;
	uint32_t PLLSAICFGR;
	uint32_t DCKCFGR;
	uint32_t CKGATENR;
	uint32_t DCKCFGR2;
} RCC;


/** Prototypes **/
extern void enable_gpio_clock(char port);
extern void enable_timer_clock(int timer);
extern void enable_systemconfig_clock();

#endif	// End compiler guard
