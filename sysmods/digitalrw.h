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

/* It is preferable to use inline functions instead of function-like macros.
 * Though if DIGITALRW_write was written as a function (even if inline) it would
 * generate larger code. Read: http://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_port_pass
 * read and toggle are written as macros in order to keep consistency.
*/
 
/*
 * On port read receives a PINx, where x = { A, B, C, D }
*/
#define DIGITALRW_read(port, pin) ((port) & (_BV(pin)))
/*
 * On port write and toggle receive a PORTx, where x = { A, B, C, D }
*/
#define DIGITALRW_write(port, pin, value) ((value) ? ((port) |= (_BV(pin))) : ((port) &= (~_BV(pin))))
#define DIGITALRW_toggle(port, pin) ((port) ^= (_BV(pin)))

extern uint32_t DIGITALRW_timer;  /* 1 ms */

/* public functions **/

void DIGITALRW_init(void);
void DIGITALRW_write_timed(volatile uint8_t *port, uint8_t pin, uint8_t value, uint32_t duration);
void DIGITALRW_task(void);

#endif /* DIGITALRW_H_ */
