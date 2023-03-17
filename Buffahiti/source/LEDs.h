#ifndef LEDS_H_
#define LEDS_H_

/*************Defining macros***********************/
#define RED_LED_PIN 18
#define GREEN_LED_PIN 19
#define BLUE_LED_PIN 1

/***********Declaring the functions****************/
void LED_Initialization(void);
void LED_on(int rgb);
void LED_off();

#endif /* LEDS_H_ */
