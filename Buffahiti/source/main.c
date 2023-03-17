/**************************
 *​​Copyright​​ (C) ​​2022 ​​by Shrinithi
 *​​Redistribution,​​ modification ​​or ​​use ​​of ​​this ​​software ​​in​​source​ ​or ​​binary
 *​​forms​​ is​​ permitted​​ as​​ long​​ as​​ the​​ files​​ maintain​​ this​​ copyright.​​ Users​​ are
 *​​permitted​​ to ​​modify ​​this ​​and ​​use ​​it ​​to ​​learn ​​about ​​the ​​field​​ of ​​embedded
 *​​software. Shrinithi ​​and​ ​the ​​University ​​of ​​Colorado ​​are ​​not​ ​liable ​​for
 *​​any ​​misuse ​​of ​​this ​​material.
 *
 **************************/
/**
 *
 * @author Shrinithi
 * @date October 3 2022
 * @version 1.1
 *
 *
 Sources of Reference:
 Online Links:
 https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_7/Source/main.c
 https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 i.e. Alexander G Dean's github repository for NXP KL25Z Touch Scan Slider
 Textbook: Embedded Systems Fundamentals with Arm Cortex-M based MicroControllers
 */

/**
 * @file    main.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "states.h"
#include "leds.h"
#include "log.h"
#include "touch.h"
#include "systick.h"
#include "main.h"
#include "switch.h"
/***********************Defining functions**************************************/
/**
 * @function :  Function to initialize PWM
 *
 * @param : NULL
 * @return : NULL
 *
 */
void PWM_Initialization(uint32_t period) {
	//Initializing clocks to ports and TMP0, TPM2
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	//Initializing MUX
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(4);
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(3);
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(3);

	//Enabling TPM clock
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//Initializing Pre-Scaler and setting value to 8
	TPM0->MOD = period - 1;
	TPM0->SC = TPM_SC_PS(3);
	TPM2->MOD = period - 1;
	TPM2->SC = TPM_SC_PS(3);

	//Initializing TPM debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	TPM2->CONF |= TPM_CONF_DBGMODE(3);

	//Initializing TPM low true pulses
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	//Initializing PWM values of three colors
	TPM2->CONTROLS[0].CnV = 0;			//Red
	TPM2->CONTROLS[1].CnV = 0;			//Green
	TPM0->CONTROLS[1].CnV = 0;			//Blue

	//Enabling CMOD
	TPM0->SC |= TPM_SC_CMOD(1);
	TPM2->SC |= TPM_SC_CMOD(1);
}

int main(void) {

	// Initializing board hardware.
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	// Initialize FSL debug console.
	BOARD_InitDebugConsole();
#endif
	//call the initialization functions
	Touch_Initialization();
	SysTick_Initialization();
	PWM_Initialization(PWM_PERIOD);

	//Setting Initial Start Values
	TPM2->CONTROLS[0].CnV = ((0x61) * (PWM_PERIOD)) / 256;
	TPM2->CONTROLS[1].CnV = ((0x1E) * (PWM_PERIOD)) / 256;
	TPM0->CONTROLS[1].CnV = ((0x3C) * (PWM_PERIOD)) / 256;

	LOG("Main loop starting\n");
	LOG("%u STOP \n", time_now());
	while (1) {

		MainLoop();		//state machine loop

	}
	return 0;
}

