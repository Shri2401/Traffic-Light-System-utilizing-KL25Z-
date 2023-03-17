#ifndef MAIN_H_
#define MAIN_H_
#include <stdio.h>
#include <stdint.h>

/***********************Declaring the macros************************************/
#define PWM_PERIOD 60000L

/***********Declaring the functions****************/
void PWM_Initialization(uint32_t period);

#endif /* MAIN_H_ */
