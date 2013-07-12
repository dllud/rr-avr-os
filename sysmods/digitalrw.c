 /*
 * digitalrw.c
 * Copyright (C) 2012-2013 David Ludovino david.ludovino@gmail.com
 * 
 * Reads and writes from digital ports.
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
#include "digitalrw.h"
#include "list.h"
#include <stdio.h>

/* Global varibales **/

uint32_t DIGITALRW_timer = 0;

/* Local variables **/
list_el *DIGITALRW_head = NULL;

void DIGITALRW_init(void) { }

char DIGITALRW_read(uint8_t port, uint8_t pin) {
	return port & _BV(pin);
}

void DIGITALRW_write(uint8_t port, uint8_t pin, uint8_t value) {
	if(value) // Write 1
		port |= _BV(pin);
	else // Write 0
		port &= ~_BV(pin);
}

void DIGITALRW_toggle(uint8_t port, uint8_t pin) {
	port ^= _BV(pin);
}

/* Using a list with dynamically allocated memory in an embedded system
 * is usually wrong.
 * Though here the number of elements is small.
*/
void DIGITALRW_write_timed(uint8_t port, uint8_t pin, uint8_t value, uint32_t duration) {
	DIGITALRW_write(port, pin, value);
	LIST_insert(&DIGITALRW_head, port, pin, DIGITALRW_timer + duration);
}


void DIGITALRW_task(void) {
	LIST_remove_expired(&DIGITALRW_head, DIGITALRW_timer, &DIGITALRW_toggle);
}
