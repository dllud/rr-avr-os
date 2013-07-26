 /*
 * led.h
 * Copyright (C) 2011 Renato Jorge Caleira Nunes renato.nunes@ist.utl.pt
 * Copyright (C) 2013 David Ludovino david.ludovino@gmail.com
 * 
 * System task which is responsible for blinking the "alive" LED.
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

#ifndef _LED_TASK_
#define _LED_TASK_

extern uint8_t LED_timer;  /* 10 ms */

void LED_init(uint8_t num_pulses);
void LED_task(void);

#endif
