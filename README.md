# PES_Assignment-4

### Developed a new traffic light for export to the little-known tropical island of Buffahiti.

- Platform used: MCUXpresso environment. <br />
- Language Used: C language. <br />
The code consists of multiple .c and .h files – main.c, systick.c, touch.c, leds.c, states.c, switch.c, main.h, leds.h, touch.h, states.h, log.h, systick.h, switch.h 

## .c Files:

main.c : <br />

Initializes the PWM function and contains main(). Following function are present: <br />

## leds.c: <br />

Iinitializes three leds (RGB) and function to turn the led on and off. <br />

## SysTick.c: <br />

Initializes and sets resolution of the systick timer (with interrupt handler) which has been used for timing throughout the program. Contains functions to reset the timer, return time after startup, get time. <br />

## touch.c: <br />

Initializes the TSI sensor and also has a function to scan (poll) for touch. <br />

##switch.c: <br />

Initializes the gpio switch and also has a functions for interrupt handler and detecting switch operation. <br />

## states.c: <br />

Contains the main state machine being used. The file contains an enum for declaring states and two structures for led color values (for RGB) and machine’s events for current and next state. The function Loop() is contained inside this file which contains the main working of the state machine described below.  It also defines two modes – DEBUG and PRODUCTION – for different timing configurations.

The States: <br />

The state machine contains 4 states – stop, go, warning, and crosswalk. Stop, go, and warning states are run in main loop one after the other with each active for 5 or 20 seconds depending on the mode choice whether in DEBUG ot PRODUCTION mode. Each state starts with a particular code values of colors RGB and stays with that for respective time. Transition of one state to other takes 1 seconds with each led changing its code value according to a specifies formula. When the button is pressed (TSI touch), the transition happens (in its normal way) to the crosswalk state. Then after blinking the led for 10 seconds, the transition to GO state takes place.


##PEER REVIEW COMMENTS
- Reviewer: Mrunal Yadav
- Date : 11.10.2022
### Comments:
- Use defines in appropriate .c and .h files. Common defines used in more than one file must be included and .h file and others in .c file.
- First LOG is not printing from STOP state. 
- Polling time in states.c file is given wrong for 100ms. 
- Correct Indentation throughout.
- Add appropriate comments according to guidelines.
- Empty READme File. Make changes.
- Statemachines Flowchart missing.

POST REVIEW CHANGES MADE:
- Have included defines in appropriate files.
- Added STOP LOG to print first.
- Polling time corrected.
- Readme file edited.
- Added State-machine Flowchart
- Added comments and Intendation.
- Added Switch file for extra credits. 
