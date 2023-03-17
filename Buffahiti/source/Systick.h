#ifndef SYSTICK_H_
#define SYSTICK_H_

/***********Declaring the functions****************/
typedef uint32_t ticktime_t;
void SysTick_Initialization();
void SysTick_Handler();
ticktime_t time_now();
void reset_timer();
ticktime_t get_timer();

#endif /* SYSTICK_H_ */
