
#include "receiver.h"

#define timerOffset 65535
#define halfBitPeriod 8106

uint16_t lastTimestamp;

void init_receiver(){
	//enable clock for TIM3
	*(APB1ENR) |= (1 << 1);

	//select the active input - write CCMR1 CC1S bits
	*(TIM3_CCMR1) &= ~(0b11 << 0);
	*(TIM3_CCMR1) |= (1 << 0);

	//set a input filter to ensure that any jitter does not
	//result in an incorrect reading. Need 4 to trigger
//	*(TIM3_CCMR1) &= ~(0b1111 < 4);
//	*(TIM3_CCMR1) |= (0b0010 < 4);

	//select edge of active transition by writing CC1P and
	//CC1NP bits in CCER register
	*(TIM3_CCER) |= (0b101 << 1);

	//disable the prescalar
	*(TIM3_CCMR1) &= ~(11 << 2);

	//Enable capture from the counter into the capture register
	*(TIM3_CCER) |= (1 << 0);

	//Enable the interrupt
	//*(TIM3_DIER) |= (1 << 1);


	//enable the counter by setting CEN bit in CR1
	*(TIM3_CR1) |= 1;
}

/**
 * This function will run as long as the state of the system is busy and
 * the system is not transmitting its own message. This function will continuously
 * read from the status registers of the TIM3, and compare time stamps when a
 * transition on the RX signal has occured. This function can may be interrupted by
 * the TIM5 timer and RX interrupt handlers.
 */
void receive(){
	//Make sure a message is being received and it's not loopback
	while(getState() == BUSY && !is_transmitting()){
		//Check if a edge transition has occured
		if((*(TIM3_SR) && (1 << 1)) == 0x01){
			uint8_t rx = get_rx();
			uint16_t captureValue = (*(TIM3_CCR1) && 0xFF);

			uint16_t timeElapsed = (captureValue < lastTimestamp) ? captureValue + timerOffset - lastTimestamp : captureValue - lastTimestamp;

			if(timeElapsed <= halfBitPeriod){

			}else{

			}
		}
	}
}

/**
 * This interrupt handler translates clock edges into data following
 * the standard for CE 4951. The timer is set to input capture mode,
 * so timestamps are collected on each transition of the RX signal.
 */
void TIM3_IRQHandler(void){

}
