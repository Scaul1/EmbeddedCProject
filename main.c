#include "stm32f0xx.h"

void delay(int time);

void flashPin6(int numFlashes, int pin);

int main(void){
	RCC ->AHBENR |= RCC_AHBENR_GPIOCEN;
	//Specifies registers being used?
	GPIOC ->MODER |= GPIO_MODER_MODER6_0;
	//GPIOC Specifies port C
	//MODER is 32-bit register controlling 'mode'
		//00 input mode (reset state)
			//meaning MODER starts as
			//00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
		//01 general purpose output mode
		//11 analog input mode
		//10 alternate function mode
			//peripherals control mode
	//GPIO_MODER_MODER6_0 is 0000 0000 0000 0000 0001 0000 0000 0000
			//meaning MODER is now
			// 00,00,00,00,00,00,00,00,00,01,00,00,00,00,00,00
	GPIOC ->MODER &= ~(GPIO_MODER_MODER6_1);
	//GPIO_MODER_MODER6_1 is 0000 0000 0000 0000 0010 0000 0000 0000
			//meaning MODER is now
			// 00,00,00,00,00,00,00,00,00,11,00,00,00,00,00,00
	GPIOC ->OTYPER &= ~(GPIO_OTPER_OT_6);
	//OTYPER is a 16-bit register controlling 'type'
		//0 ouput push-pull (reset state)
			//meaning OTYPER starts as
			//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		//1 output open-drain
	//GPIO_OTYPER_OT_6 is 0000 0000 0000 0000 0000 0000 0100 0000
			//meaning OTYPER is now
			// 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0
	GPIOC ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDER6;
	//OSPEEDR is register controlling input or output current
		//'xo' 2MHz (Low Speed)
		//'01' 10MHz (Medium Speed)
		//'11' 50 MHz (High Speed)
	//GPIO_OSPEEDR_OSPEEDR6 is 
			//meaning OSPEEDR is now
			//????
	GPIOC ->PUPDR &= (GPIO_PUPDR_PUPDR6);
	//PUPDR is a 32-bit register controlling pull-up or pull-down resistance
	//pull-up or pull-down resistance can be set on input or output pins
	//pull-up 
	//pull-down 
		//00 no pull-up or pull-down
			//PUPDR starts as  00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
		//01 pull-up
		//10 pull-down
		//11 reserved
	//GPIO_PUPDR_PUPDR6 is ????
		//meaning PUPDR is now
		//????
	GPIOC -> MODER |= 0000 0000 0000 0000 0000 0000 0000 0000
  while (1){
	  flashPin6(10);
  }
}

void delay(int mSeconds){
	int goal = mSeconds + clock();
	while(goal > clock()){}
}

void flashPin6(int numFlashes, int pin){
	int i;
	int mod = 0000 0000 0000 0000 0000 0000 0000 0001;
	mod += 2exp(pin);
	for(i = 0; i < numFlashes; i++){
	GPIOC -> BSRR |= GPIO_BSRR_BS_6;
	//BSRR Bit set/reset register is 32-bits and allows specific pins to be set without
	//changing other pins in the same register
	//BSRR changes...
		//allows registers to be changed very quickly
		//GPIO_BSRR_BS_6 is 0000 0000 0000 0000 0000 0000 0100 0000
		//this sets pin 6
		//WHY DOES THIS USE THE OR (|) FUNCTION?
	delay(1000);
	GPIOC ->BRR |= GPIO_BRR_BR_6;
	//BRR Bit reset register is 32-bit
		//second (lower 16) bits will reset (turn off pins) and first 16 bits will set (turn on pins)
	//Reverses actions done by the BSRR register
		//GPIO_BRR_BR_6 is 0000 0000 0000 0000 0000 0000 0100 0000
		//this resets pin 6
	delay(1000);
  }
}
