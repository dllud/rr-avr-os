 /*
 * pwm.c
 * Copyright (C) 2013 David Ludovino david.ludovino@gmail.com
 * 
 * Writes PWM signals.
 * Only 8-bit Timer/Counters are supported: Timer/Counter0 and Timer/Counter2 in ATmegax8
 * Reason: this way we can keep the variable port as a uint8_t and use the functions in list.c
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

/* Global includes */
#include "node.h"

/* Global inclues for AVR */
#include <avr/io.h>

/* Includes specific to this module */
#include "pwm.h"
#include "list.h"
#include <stdio.h>

/* Global varibales **/

uint32_t PWM_timer;

/* Local variables **/
list_el *PWM_head; /* = NULL */

/*
 * Initializes a given PWM port to mode Fast PWM, 8-bit with Fcpu speed.
 * Check the AVR ATmega manual, for instance page 108.
*/
void PWM_init(volatile uint8_t *port) {
	switch((uint16_t) port) {
		case (uint16_t) &OCR0A:
			TCCR0A = _BV(COM0A1) | _BV(COM0A0) | _BV(WGM01) | _BV(WGM00);
			TCCR0B = _BV(CS00);
			break;
		case (uint16_t) &OCR0B:
			TCCR0A = _BV(COM0B1) | _BV(COM0B0) | _BV(WGM01) | _BV(WGM00);
			TCCR0B = _BV(CS00);
			break;
		case (uint16_t) &OCR2A:
			TCCR2A = _BV(COM2A1) | _BV(COM2A0) | _BV(WGM21) | _BV(WGM20);
			TCCR2B = _BV(CS20);
			break;
		case (uint16_t) &OCR2B:
			TCCR2A = _BV(COM2B1) | _BV(COM2B0) | _BV(WGM21) | _BV(WGM20);
			TCCR2B = _BV(CS20);
			break;
	}
}

void PWM_write_timed(volatile uint8_t *port, uint8_t value, uint32_t duration){
	PWM_write(*port, value);
	LIST_insert(&PWM_head, port, 0, PWM_timer + duration);
}

void PWM_reset_expired(volatile uint8_t *port, uint8_t pin) {
	PWM_reset(*port);
}

void PWM_task(void) {
	LIST_remove_expired(&PWM_head, PWM_timer, &PWM_reset_expired);
}
