#ifndef _SERVO_H_
#define _SERVO_H_

/* Module to initialize and cleanup the PWMLED thread.
Supports controlling the LED with the potentiometer. Repeatedly writes the period and duty_cycle parameters of the LED
based on the voltage read from the potentiometer. 
*/

#include <stdbool.h>

void initializeServo();
void createServoThread();
void joinServoThread();
void shutdownServo();

void unlockServo();
void lockServo();
bool isLocked();

#endif