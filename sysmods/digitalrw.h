 /*
 * digitalrw.h
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

#ifndef DIGITALRW_H_
#define DIGITALRW_H_

extern uint32_t DIGITALRW_timer;  /* 1 ms */

/* public functions **/

void DIGITALRW_init(void);
char DIGITALRW_read(uint8_t port, uint8_t pin);
void DIGITALRW_write(uint8_t port, uint8_t pin, uint8_t value);
void DIGITALRW_write_timed(uint8_t port, uint8_t pin, uint8_t value, uint32_t duration);
void DIGITALRW_task(void);

#endif /* DIGITALRW_H_ */
