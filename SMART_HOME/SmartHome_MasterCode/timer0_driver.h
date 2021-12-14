

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Utilites.h"
#include "STD_Types.h"

void timer0_initializeCTC(void);

void timer0_stop(void);

void timer_initializefastpwm(void);

void change_dutycycle(f64 duty);


#endif /* TIMER_DRIVER_H_ */
