 /*
 * adc.c
 * Copyright (C) 2011 David Ludovino david.ludovino@gmail.com
 * 
 * Reads the Analog-to-Digital converter.
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
	ADMUX = (1 << REFS0);
	/* Set Prescalar = Fcpu/128 = 16 MHz / 128 = 125 KHz which belongs to [50,200] KHz */
	ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_read(uint8_t pin) {
	/* ADC channel must be 0-11. */
	if(pin > 10)
		return USHRT_MAX;
	/* Enable ADC */
	ADCSRA |= (1 << ADEN);
	/* Clear previous pin from multiplexer */
	ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
	ADMUX |= pin;
	/* Start Single Conversion */
	ADCSRA |= (1 << ADSC);
	/* Wait for conversion to complete */
	while(ADCSRA & (1 << ADSC));
	/* Clear ADIF by writing 1 to it
	 * This is standard way of clearing bits in IO as said in datasheets.
	 * The code writes '1' but it results in setting bit to '0' !!!
	 * ADCSRA |= (1<<ADIF); No need to clear in Single Conversion Mode
	 * Disable ADC */
	ADCSRA &= ~(1 << ADEN);
	return ADC;
}
