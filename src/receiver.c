
#include "receiver.h"

void init_receiver(){

}

/**
 * This interrupt handler translates clock edges into data following
 * the standard for CE 4951. The timer is set to input capture mode,
 * so timestamps are collected on each transition of the RX signal.
 */
void TIM3_IRQHandler(void){

}
