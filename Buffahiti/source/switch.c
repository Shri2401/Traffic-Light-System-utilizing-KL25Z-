#include "MKL25Z4.h"
#include "touch.h"
#include <stdio.h>
#include <stdlib.h>
#include <switch.h>
/***************************Defining macros***************************************/
#define GPIOPIN (6)

extern int flag;
/**************************Defining functions*************************************/
/**
 * @function :  Function to initialize GPIO pin to use it as a switch
 *
 * @param : NULL
 * @return : NULL
 *
 */
void Switch_Initialization() {
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[GPIOPIN] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
	PORTD->PCR[GPIOPIN] |= PORT_PCR_IRQC(10); // configuring falling edge interrupt
	GPIOD->PDDR &= ~(1 << GPIOPIN);
	NVIC_SetPriority(PORTD_IRQn, 4);  // SET priority of interrupt
	NVIC_ClearPendingIRQ(PORTD_IRQn); // clear pending IRQ
	NVIC_EnableIRQ(PORTD_IRQn);  // enable IRQ
}
/**
 * @function :  GPIO Interrupt Handler
 *
 * @param : NULL
 * @return : NULL
 *
 */
void IRQHandler() {
	// Clears pending IRQ
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	// Setting switch_pressed
	flag = 1;
	// Clears Interrupt flag
	PORTD->ISFR |= (1 << GPIOPIN);
}
/**
 * @function :  Function to return GPIO flag
 *
 * @param : NULL
 * @return : Returns flag value
 *
 */
int switch_press() {
	return flag;
}

