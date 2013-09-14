 /*
 * adc.h
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

#ifndef ADC_H_
#define ADC_H_

/* public functions **/
void ADC_init_10bit(void);
void ADC_init_8bit(void);
/* ADC pin must be 0-15. */
uint16_t ADC_read_10bit(uint8_t pin);
uint8_t ADC_read_8bit(uint8_t pin);
void ADC_off(void);
void ADC_ref_AVCC(void);
void ADC_ref_1V(void);

#endif /* ADC_H_ */
