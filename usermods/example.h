 /*
 * example.h
 * Copyright (C) 2013 David Ludovino david.ludovino@gmail.com
 * 
 * Uses various of the hardware abstraction functions provided by rr-avr-os.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 3 as
 * published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef EXAMPLE_H_
#define EXAMPLE_H_

/* Global includes for AVR */
#include <avr/io.h>

#define EXAMPLE_PWM_PIN OCR0A

extern uint16_t EXAMPLE_timer_pwm;  /* 1 s */
extern uint16_t EXAMPLE_timer_adc;  /* 1 s */

/* public functions **/
void EXAMPLE_init(void);
void EXAMPLE_task(void);

#endif /* EXAMPLE_H_ */
