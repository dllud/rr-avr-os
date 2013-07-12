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
#include "sysmods/digitalrw.h"
#include "sysmods/adc.h"

#define CHANGE_PWM_INTERVAL 2 // seconds
#define READ_ADC_INTERVAL 20 // seconds
#define BUTTON_PORT PIND
#define BUTTON_PIN PIND4
#define LED_PORT PORTD
#define LED_PIN PORTD2
#define VOLTAGE_DIVIDER_PIN PINC0

/* Global varibales ::vars **/
uint16_t EXAMPLE_timer_pwm = 0;  /* 1 s*/
uint16_t EXAMPLE_timer_adc = 0;  /* 1 s*/

/* Local variables **/
uint8_t pwm_value = 0;

void EXAMPLE_init(void) { }

void EXAMPLE_task(void) {
	if(DIGITALRW_read(BUTTON_PORT, BUTTON_PIN)) {
		//printf("Push button pressed.\n");
		DIGITALRW_write(LED_PORT, LED_PIN, 1);
	}
	else
		DIGITALRW_write(LED_PORT, LED_PIN, 0);
	
	if(EXAMPLE_timer_pwm >= CHANGE_PWM_INTERVAL) {
		EXAMPLE_timer_pwm = 0;
		printf("Writing %u to the PWM pin.\n", pwm_value);
		PWM_write(EXAMPLE_PWM_PIN, pwm_value);
		pwm_value++;
	}
	
	if(EXAMPLE_timer_adc >= READ_ADC_INTERVAL) {
		EXAMPLE_timer_adc = 0;
		printf("\t\t\t\tVoltage divider reads: %u\n", ADC_read(VOLTAGE_DIVIDER_PIN));
	}
}
