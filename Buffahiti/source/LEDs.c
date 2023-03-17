#include <stdio.h>
#include "MKL25Z4.h"
#include "leds.h"

/***************************Defining macros**********************************/
#define MASK(x) (1UL << (x))

/*************************Defining functions*********************************/
/**
 * @function :  Function to initialize LEDs on KL25Z
 *
 * @param : NULL
 * @return : NULL
 *
 */
void LED_Initialization(void) {
	//Initializing the clocks for ports B and D to configure LEDs
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//Initializing the pins 18, 16 of port B and 1 of port D to configure LEDs
	GPIOB->PDOR |= MASK(RED_LED_PIN) | MASK(GREEN_LED_PIN);
	GPIOD->PDOR |= MASK(BLUE_LED_PIN);
	GPIOB->PDDR |= MASK(RED_LED_PIN) | MASK(GREEN_LED_PIN);
	GPIOD->PDDR |= MASK(BLUE_LED_PIN);

	//Initializing MUX for the respective LEDs
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);
}
/**
 * @function :  Function to turns on the appropriate led
 *
 * @param : NULL
 * @return : NULL
 *
 */
void LED_on(int rgb) {
	switch (rgb) {
	case (1): //turns on red led
		GPIOB->PSOR |= MASK(GREEN_LED_PIN);  //turning green led off
		GPIOD->PSOR |= MASK(BLUE_LED_PIN);	//turning blue led off
		GPIOB->PCOR |= MASK(RED_LED_PIN);	//turning red led on
		break;
	case (2): //turns on Green led
		GPIOD->PSOR |= MASK(BLUE_LED_PIN);	//turning blue led off
		GPIOB->PSOR |= MASK(RED_LED_PIN);	//turning red led off
		GPIOB->PCOR |= MASK(GREEN_LED_PIN);	//turning green led on
		break;
	case (3): //turns on Blue led
		GPIOB->PSOR |= MASK(GREEN_LED_PIN);	//turning green led off
		GPIOB->PSOR |= MASK(RED_LED_PIN);	//turning red led off
		GPIOD->PCOR |= MASK(BLUE_LED_PIN);	//turning blue led on
		break;
	}
}
/**
 * @function : Function to turn the led off
 *
 * @param : NULL
 * @return : NULL
 *
 */
void LED_off() {
	GPIOB->PSOR |= MASK(RED_LED_PIN) | MASK(GREEN_LED_PIN); //turns off red and green led
	GPIOD->PSOR |= MASK(BLUE_LED_PIN); //turns off blue led
}

