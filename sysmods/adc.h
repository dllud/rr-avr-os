 /*
 * adc.h
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

#ifndef ADC_H_
#define ADC_H_

/* public functions **/
void ADC_init(void);
uint16_t ADC_read(uint8_t pin);

#endif /* ADC_H_ */
