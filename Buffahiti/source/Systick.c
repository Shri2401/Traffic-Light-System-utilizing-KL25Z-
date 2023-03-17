#include <stdio.h>
#include <MKL25Z4.h>
#include <stdint.h>
#include "core_cm0plus.h"
#include "leds.h"
#include "systick.h"

typedef uint32_t ticktime_t;

ticktime_t count = 0;
ticktime_t temp = 0;
/**************************Defining functions*************************************/
/**
 * @function : Function to initialize SysTick Timer
 *
 * @param : NULL
 * @return : NULL
 *
 */
void SysTick_Initialization() {
	SysTick->LOAD = 30000;				//for 10ms res
	NVIC_SetPriority(SysTick_IRQn, 3); //setting interrupt priority to 3
	SysTick->VAL = 0;					//Initial value of counter
	SysTick->CTRL &= ~(SysTick_CTRL_CLKSOURCE_Msk); //frequency = 3Mhz (external clock)
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk; //enable interrupt
}
/**
 * @function : SysTick interrupt handler
 *
 * @param : NULL
 * @return : NULL
 *
 */
void SysTick_Handler() {
	count += 10;
}
/**
 * @function : Function to return the current time
 *
 * @param : NULL
 * @return : Returns current time since startup
 *
 */
ticktime_t time_now() {
	return count;
}
/**
 * @function : Function to reset time
 *
 * @param : NULL
 * @return : Returns current time since startup
 *
 */
void reset_timer() {
	temp = count;
}
/**
 * @function : Function to return the time
 *
 * @param : NULL
 * @return : Returns time
 *
 */
ticktime_t get_timer() {
	return (count - temp);
}
