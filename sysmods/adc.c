 /*
 * adc.c
 * Copyright (C) 2011-2013 David Ludovino david.ludovino@gmail.com
 * 
 * Reads the Analog-to-Digital converter in Single Conversion Mode.
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
#include "adc.h"
#include <limits.h>
#include <stdio.h>

/* Global varibales */

/* Local variables */

void ADC_init(void) {
	/* Reference voltage = Vcc (5V) */
	ADMUX = _BV(REFS0);
	/* Set Prescalar = Fcpu/128 = 16 MHz / 128 = 125 kHz
	 * [50,200] kHz is required to get maximum resolution (p. 255)
	 * First conversion takes 25 ADC cycles = 25 * (1 / 125) = 0.2 s 
	 * Normal conversion takes 13 ADC cycles = 13 * (1 / 125) = 0.104 s*/
	ADCSRA = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	/* Enable ADC */
	ADCSRA |= _BV(ADEN);
}

uint16_t ADC_read(uint8_t pin) {
	/* ADC channel must be 0-15. */
	if(pin > 15)
		return USHRT_MAX;
	/* Clear previous pin from multiplexer */
	ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
	ADMUX |= pin;
	/* Start Single Conversion */
	ADCSRA |= _BV(ADSC);
	/* Wait for conversion to complete */
	loop_until_bit_is_set(ADCSRA, ADSC);
	/* Clear ADIF by writing 1 to it
	 * This is standard way of clearing bits in IO as said in datasheets.
	 * The code writes '1' but it results in setting bit to '0' !!!
	 * ADCSRA |= _BV(ADIF); No need to clear in Single Conversion Mode */
	return ADC;
}

/* Disable ADC */
void ADC_off() {
	ADCSRA &= ~_BV(ADEN);
}
