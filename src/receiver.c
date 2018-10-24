
#include "receiver.h"

#define timerOffset 65535
#define halfBitMax 10000

static const char INVALID[] = "[INFO] Message outside specification received and discarded.\r\n";


unsigned int bitCount;
unsigned int bytes;
uint8_t data[100];

bool messageReceived;
bool invalidMessage;

uint16_t lastTimestamp;

void init_receiver(){
	bitCount = 0;
	bytes = 0;
	messageReceived = false;
	invalidMessage = false;
	memset(data, 0, 100*sizeof(char));

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
		if((*(TIM3_SR) & (1 << 1)) == 0x02){
			uint8_t rx = ((get_rx() >> 6) & 0x01);
			uint16_t captureValue = (*(TIM3_CCR1) & 0xFFFF);

			uint16_t timeElapsed = (captureValue < lastTimestamp) ?
					captureValue + timerOffset - lastTimestamp : captureValue - lastTimestamp;

			if(bitCount != 0){
				data[bytes] = data[bytes] << 1;

				if(rx == 0){
					data[bytes] |= 0b01;
				}
				bitCount++;
				if(bitCount % 8 == 0) bytes++;

				if(timeElapsed > halfBitMax){
					data[bytes] = data[bytes] << 1;

					if(rx == 0){
						data[bytes] |= 0b01;
					}
					bitCount++;
					if(bitCount % 8 == 0) bytes++;
				}
			}else{
				data[bytes] = 0x01;
				bitCount++;
			}

			lastTimestamp = captureValue;
			//clear interrupt flag
			*(TIM3_SR) &= ~(1 << 1);
		}
		messageReceived = true;
	}

	//Once full message has been received, translate, print, and return
	if(getState() == IDLE && messageReceived){

		if(!invalidMessage){
			//First we need to get the last bit if it wasn't captured.
			//This can happen if the last bit is a 1 and the line goes
			//IDLE. We should have filled bytes.
			if((bitCount % 8) != 0){
				data[bytes] = data[bytes] << 1;
				data[bytes] |= 1;
				bitCount++;
			}


			//create a temporary buffer of bytes/2
			char temp[bytes/2];
			uint8_t data1_xx;
			uint8_t data2_xx;

			for(int i = 0; i < bytes; i += 2){
				char asciiChar = 0x00;
				uint8_t data1 = data[i];
				uint8_t data2 = data[i+1];

				//four bits of data are contained in each Manchester byte
				for(int j = 3; j >= 0; j--){
					asciiChar = asciiChar << 1;

					//shift two bits to position 1 and 0, starting with msb
					data1_xx = (data1 >> ((j*2) ));
					data2_xx = (data2 >> ((j*2) ));

					 //Fill the upper nibble
					 if((data1_xx & 0b11) == 0b01){
						 asciiChar |= (0b1 << 4);
					 }

					 //Fill the lower nibble
					 if((data2_xx & 0b11) == 0b01){
						 asciiChar |= 0b1;
					 }
				}

				//place decoded byte into temporary buffer
				temp[i/2] = asciiChar;
			}

			//send characters to console out
			for(int i = 0; i < bytes/2; i++){
				char toConsole = temp[i];

				if(toConsole >= ' ' && toConsole <= '~'){
					usart2_putch(temp[i]);
				}else{
					usart2_putch('*');
				}
			}
			usart2_putch('\r');
			usart2_putch('\n');
		}else{
			for(int i = 0; i < 64; i++){
				usart2_putch(INVALID[i]);
			}
		}

		//reset all data
		bitCount = 0;
		bytes = 0;
		memset(data, 0, 100*sizeof(char));
		messageReceived = false;
		invalidMessage = false;
	}
}
