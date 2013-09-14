 /*
 * adc.c
 * Copyright (C) 2011-2013 David Ludovino david.ludovino@gmail.com
 * 
 * Reads the Analog-to-Digital converter in Single Conversion Mode.
 * Can use 10 bit or 8 bit resolution to offer a compromise between
 * accuracy and sampling rate.
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

/* Global varibales */

/* Local variables */

void ADC_init_10bit(void) {
	/* Reference voltage = Vcc (5V) */
	ADMUX = _BV(REFS0);
	/* Set Prescalar = Fcpu/128 = 16 MHz / 128 = 125 kHz
	 * [50,200] kHz is required to get maximum resolution (p. 255)
	 * First conversion takes 25 ADC cycles = 25 * (1 / 125 kHz) = 0.2 ms 
	 * Normal conversion takes 13 ADC cycles = 13 * (1 / 125 kHz) = 0.104 ms
	 * f ~= 9.6 kHz */
	ADCSRA = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	/* Enable ADC */
	ADCSRA |= _BV(ADEN);
}

void ADC_init_8bit(void) {
	ADMUX = _BV(REFS0) | _BV(ADLAR);
	/* Set Prescalar = Fcpu/32 = 16 MHz / 32 = 500 kHz
	 * First conversion takes 25 ADC cycles = 25 * (1 / 500 kHz) = 0.05 ms 
	 * Normal conversion takes 13 ADC cycles = 13 * (1 / 500 kHz) = 0.026 ms
	 * f ~= 38 kHz 
	 * We may go even further, check: http://www.marulaberry.co.za/index.php/tutorials/code/arduino-adc */
	ADCSRA = _BV(ADPS2) | _BV(ADPS0);
	ADCSRA |= _BV(ADEN);
}

static void ADC_read_aux(uint8_t pin) {
	/* ADC pin must be 0-15.
	 * Verification disabled for performance improvement.
	if(pin > 15)
		return;
	*/
	/* Clear previous pin from multiplexer */
	ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));
	ADMUX |= pin;
	/* Start Single Conversion */
	ADCSRA |= _BV(ADSC);
	/* Wait for conversion to complete */
	loop_until_bit_is_clear(ADCSRA, ADSC);
	/* Clear ADIF by writing 1 to it
	 * This is standard way of clearing bits in IO as said in datasheets.
	 * The code writes '1' but it results in setting bit to '0' !!!
	 * ADCSRA |= _BV(ADIF); No need to clear in Single Conversion Mode */
 }

uint16_t ADC_read_10bit(uint8_t pin) {
	ADC_read_aux(pin);
	return ADC;
}

uint8_t ADC_read_8bit(uint8_t pin) {
	ADC_read_aux(pin);
	return ADCH;
}

/* Disable ADC */
inline void ADC_off(void) {
	ADCSRA &= ~_BV(ADEN);
}

inline void ADC_ref_AVCC(void) {
	ADMUX |= _BV(REFS0);
	ADMUX &= ~_BV(REFS1);
}

inline void ADC_ref_1V(void) {	
	ADMUX |= _BV(REFS1) | _BV(REFS0);
}
