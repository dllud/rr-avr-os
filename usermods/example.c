 /*
 * example.c
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

/* Global includes */
#include "sysmods/node.h"

/* Global inclues for AVR */

/* Includes specific to this module */
#include "example.h"
#include "sysmods/pwm.h"

#define CHANGE_INTERVAL 2 // seconds

/* Global varibales ::vars **/
uint16_t EXAMPLE_timer = 0;  /* 1 s*/

/* Local variables **/
uint8_t pwm_value = 0;

void EXAMPLE_init(void) { }

void EXAMPLE_task(void) {
	if(EXAMPLE_timer >= CHANGE_INTERVAL) {
		EXAMPLE_timer = 0;
		printf("----------- Example module -----------\n");
		printf("Writing %d to the PWM pin\n", pwm_value);
		printf("------------------------------\n");
		PWM_write(EXAMPLE_PWM_PIN, pwm_value);
		pwm_value++;
	}
}
