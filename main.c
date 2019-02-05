#include "stm32f0xx.h"

void delay(int time);

int main(void){
	RCC ->AHBENR |= RCC_AHBENR_GPIOCEN;
	//Specifies registers being used?
	GPIOC ->MODER |= GPIO_MODER_MODER6_0;
	//GPIOC Specifies port C
	//MODER is register controlling...
	//GPIO_MODER_MODER6_0 sets MODER's pin 6 to...
	GPIOC ->MODER &= ~(GPIO_MODER_MODER6_1);
	//GPIO_MODER_MODER6_1 sets MODER's pin 6 to...
	GPIOC ->OTYPER &= ~(GPIO_OTPER_OT_6);
	//OTYPER is register controlling...
	//GPIO_OTYPER_OT_6 sets OTYPER's pin 6 to...
	GPIOC ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDER6;
	//OSPEEDR is register controlling current rate to a specific pin
	//GPIO_OSPEEDR_OSPEEDR6 sets OSPEEDR's pin 6 to...
	GPIOC ->PUPDR &= (GPIO_PUPDR_PUPDR6);
	//PUPDR is register controlling pull-up or pull-down resistance
	//GPIO_PUPDR_PUPDR6 sets PUPDR's pin 6 to...
  while (1){
	GPIOC -> BSRR |= GPIO_BSRR_BS_6;
	//BSRR Bit set register (sets pin 6 to high voltage output)
	delay(200000);
	GPIOC ->BRR |= GPIO_BRR_BR_6;
	//BRR Bit reset register (sets pin 6 to low voltage/ground)
	delay(200000);
  }
}

void delay(int time){

}

