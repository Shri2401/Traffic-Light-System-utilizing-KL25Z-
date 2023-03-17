#include "MKL25Z4.h"
#include <stdio.h>
#include "touch.h"

/************************Defining macros***************************/
#define TOUCH_COUNT ((TSI0->DATA)& 0XFFFF)

/************************Defining functions***************************/
/**
 * @function : Function to initialize the TSI
 *
 * @param : NULL
 * @return : NULL
 *
 */
void Touch_Initialization() {
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;
	TSI0->GENCS = TSI_GENCS_MODE(0u) | //operating in non-noise mode
			TSI_GENCS_REFCHRG(0u) | //reference oscillator charge and discharge value 500nA
			TSI_GENCS_DVOLT(0u) | //oscillator voltage rails set to default
			TSI_GENCS_EXTCHRG(0u) | //electrode oscillator charge and discharge value 500nA
			TSI_GENCS_PS(0u) |  // frequency clock divided by one
			TSI_GENCS_NSCN(31u) | //scanning the electrode 32 times
			TSI_GENCS_TSIEN_MASK | //enabling the TSI module
			TSI_GENCS_EOSF_MASK; // writing one to clear the end of scan flag
}
/**
 * @function : Function to scan TSI and get analog values from the touch sensor interrupts.
 *
 * @param : NULL
 * @return : Returns analog values (capacitance) for the touch responses
 *
 */
//Scanning the analog values from the touch sensor
int Touch_Scan(void) {
	unsigned int scan_value = 0;
	TSI0->DATA = TSI_DATA_TSICH(10u);
	TSI0->DATA |= TSI_DATA_SWTS_MASK; //software trigger to start the scan
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK))
		;
	scan_value = TOUCH_COUNT;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK; //writing one to clear the end of scan flag
	return scan_value;
}
