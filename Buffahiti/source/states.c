#include <main.h>
#include <stdint.h>
#include <stdio.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "log.h"
#include "touch.h"
#include "leds.h"
#include "systick.h"
#include "switch.h"

/***************************Defining macros**********************************/
#define CROSSWALK_TIME 10000
#define TRANSITION_TIME 1000

#ifdef DEBUG

#define STOP_TIME 5000
#define GO_TIME 5000
#define WARN_TIME 3000

#else

#define STOP_TIME 20000
#define GO_TIME 20000
#define WARN_TIME 5000

#endif

int flag;
/**************************Defining Structures**********************************/
//Declaring color codes
typedef struct {
	int Red;
	int Green;
	int Blue;
} colors;

//Declaring states and transition
typedef enum {
	STOP, GO, WARN, CROSSWALK, TRANSITION
} signalState;

//Color codes (values of RGB) in each state
const colors STOP_CODE = { .Red = 0x61, .Green = 0x1E, .Blue = 0x3C }; // 0x611E3C
const colors GO_CODE = { .Red = 0x22, .Green = 0x96, .Blue = 0x22 }; // 0x229622
const colors WARN_CODE = { .Red = 0xFF, .Green = 0xB2, .Blue = 0x00 }; // 0xFFB200
const colors CROSSWALK_CODE = { .Red = 0x00, .Green = 0x10, .Blue = 0x30 }; // 0x001030

//Defining Events
signalState state = STOP;
signalState next_state = TRANSITION;
colors startCol = STOP_CODE;
colors endCol = STOP_CODE;

/**************************Defining functions*************************************/
/**
 * @function : Function to call for transition
 *
 * @param : NULL
 * @return : NULL
 *
 */
void transition(int currentTime) {

	TPM2->CONTROLS[0].CnV = (uint32_t) ((uint8_t) ((((endCol.Red - startCol.Red)
			* (int16_t) currentTime) / 1000) + (int16_t) startCol.Red)
			* (PWM_PERIOD)) / 256;
	TPM2->CONTROLS[1].CnV = (uint32_t) ((uint8_t) ((((endCol.Green
			- startCol.Green) * (int16_t) currentTime) / 1000)
			+ (int16_t) startCol.Green) * (PWM_PERIOD)) / 256;
	TPM0->CONTROLS[1].CnV = (uint32_t) ((uint8_t) ((((endCol.Blue
			- startCol.Blue) * (int16_t) currentTime) / 1000)
			+ (int16_t) startCol.Blue) * (PWM_PERIOD)) / 256;

}
/**
 * @function : Function to setting states
 *
 * @param : NULL
 * @return : NULL
 *
 */
void setStates(signalState lState, signalState lNextState, colors lEndCol) {
	state = lState;
	endCol = lEndCol;
	next_state = lNextState;
}

//The state machine functions
uint32_t scan_time;
uint32_t blink_time;

void MainLoop() {
	//Get the touch interrupt through scanning for transition to CROSSWALK state
	if ((state != CROSSWALK) && (next_state != CROSSWALK)) {
		if (!(((time_now()) - (scan_time)) < 10)) //polling to occur within 100ms
		{
			uint32_t touch_interrupt = Touch_Scan();
			if ((touch_interrupt > 600)||flag == 1) {
				//transition to Cross-walk state
				setStates(TRANSITION, CROSSWALK, CROSSWALK_CODE);
				LOG("touch value = %u \n", scan_time);
				LOG("%u CROSSWALK \n", time_now());
				reset_timer();
			}
			scan_time = time_now();
		}
	}

	//states with their start and end color values as well as information for next state to be called
	if (state == STOP) {
		startCol = STOP_CODE;
		if (get_timer() >= STOP_TIME) {
			setStates(TRANSITION, GO, GO_CODE);
			LOG("%u GO \n", time_now());
			reset_timer();
		}
	}

	else if (state == GO) {
		startCol = GO_CODE;
		if (get_timer() >= GO_TIME) {
			setStates(TRANSITION, WARN, WARN_CODE);
			LOG("%u WARN \n", time_now());
			reset_timer();
		}
	}

	else if (state == WARN) {
		startCol = WARN_CODE;
		if (get_timer() >= WARN_TIME) {
			setStates(TRANSITION, STOP, STOP_CODE);
			LOG("%u STOP \n", time_now());
			reset_timer();
		}
	}

	else if (state == TRANSITION) {
		if (get_timer() < TRANSITION_TIME) {
			transition(get_timer());
		} else {
			state = next_state;
			reset_timer();
			if (state == CROSSWALK)
				blink_time = time_now();
		}
	}

	else if (state == CROSSWALK) {
		startCol = CROSSWALK_CODE;
		if (get_timer() <= CROSSWALK_TIME) {
			if (((time_now()) - (blink_time)) <= 250) {
				TPM2->CONTROLS[0].CnV = 0;
				TPM2->CONTROLS[1].CnV = 0;
				TPM0->CONTROLS[1].CnV = 0;
			} else if (((time_now()) - (blink_time)) <= 1000) {
				TPM2->CONTROLS[0].CnV = ((startCol.Red) * (PWM_PERIOD)) / 256;
				TPM2->CONTROLS[1].CnV = ((startCol.Green) * (PWM_PERIOD)) / 256;
				TPM0->CONTROLS[1].CnV = ((startCol.Blue) * (PWM_PERIOD)) / 256;
			} else {
				blink_time = time_now();
			}
		}

		else {
			setStates(TRANSITION, GO, GO_CODE);
			LOG("%u GO \n", time_now());
			reset_timer();
		}
	}

}
