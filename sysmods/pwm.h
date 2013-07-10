 /*
 * pwm.h
 * Copyright (C) 2013 David Ludovino david.ludovino@gmail.com
 * 
 * Writes PWM signals.
 * Only 8-bit Timer/Counters are supported: Timer/Counter0 and Timer/Counter2 in ATmegax8
 * Reason: this way we can keep the variable pin as a uint8_t and use the functions in list.c
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

#ifndef PWM_H_
#define PWM_H_

extern uint32_t PWM_timer;  /* 1 ms */

/* public functions **/

void PWM_init(uint8_t pin);
void PWM_write(uint8_t pin, uint8_t value);
void PWM_write_timed(uint8_t pin, uint8_t value, uint32_t duration);
void PWM_task(void);

#endif /* PWM_H_ */
