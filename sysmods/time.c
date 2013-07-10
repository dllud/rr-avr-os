 /*
 * time.c
 * Copyright (C) 2002-2011 Renato Jorge Caleira Nunes renato.nunes@ist.utl.pt
 * Copyright (C) 2013 David Ludovino david.ludovino@gmail.com
 * 
 * System task which keeps track of time with the minimum granularity of 200 us.
 * Allows the tracking of periods of 200 us, 1 ms, 10 ms, 50 ms, 100 ms, 1 s, 1 min, etc.
 * In order to insert a timer one should declare it in the appropriate module header
 * as an extern variable (check :cfg00) and then place it in the desired timing
 * section (:cfg02), enabling the if macro. One must also activate the variable(s)
 * needed to keep track of the period of time in use (:cfg01).
 * 
 * This module uses Timer/Counter1 leaving 0 and 2 free for the pwm module.
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

/* Global includes for AVR */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Specific inlucdes for this module */
#include "time.h"

/* Includes of the modules that use timers :cfg00 */
#include "led.h"
#include "digitalrw.h"
#include "pwm.h"

/* Local variables */
static uint8_t TIME_curr_time; /* incremented at each 200 us interruption */
static uint8_t TIME_last_time;

/* Initializes the timer. */
void TIME_init(void)
{
	/* Timer/Counter Control Register (p. 139)
	 * clock select: CLK/64 (16MHz/64=250KHZ -> 4us) */
	TCCR1B = _BV(CS11) | _BV(CS10);
 
	OCR1A = 50; /* 50 units of 4us (check above) = 200us */
	
	/* Timer/Counter Interrupt Mask Register (p. 141)
	 * enable "Timer/Counter0 Compare Match A" interrupt */
	TIMSK1 = _BV(OCIE1A);
}

/* Interruption "Compare Match A" handling routine (IHR) for timer 1.
 * The declaration follows the directives for WinAVR and avr-gcc.
 * An interruption is risen every 200 us (for a 16 MHz crystal). */
ISR(TIMER1_COMPA_vect)
{
	OCR1A += 50;
	++TIME_curr_time;
}

#define TIME_1MS_N200US    5  /* 1 ms = 5 * 200 us */
#define TIME_10MS_N200US  50  /* 10 ms = 50 * 200 us */
#define TIME_50MS_N10MS    5  /* 50 ms = 5 * 10 ms */
#define TIME_100MS_N10MS  10  /* 100 ms = 10 * 10 ms */
#define TIME_1S_N10MS    100  /* 1 s = 100 * 10 ms */
#define TIME_1M_N1S       60  /* 1 min = 60 * 1 s */

/* Task which updates the variables from external modules which count time.
 * These variables are called timers.
 * 
 * Note that timers are updated in task time and not during interruption handling.
 * If there is a need to count time in a piece of code which is in (infinite) cycle,
 * for instance an active wait, the corresponding variable must be updated directly in the IHR.
 * 
 * The base unit of time counting is 200 us. This modules also allows to count 1 ms,
 * 10 ms, 50 ms, 100 ms, 1 s, and 1 min depending on the chosen configuration. */
void TIME_task(void)
{
	uint8_t elapsed_time; /* N * 200us */
	static uint8_t t1ms_n200us = 0;
	static uint8_t t10ms_n200us = 0;

#if 0  
/* Copy to above the necessary variables according to the time units you want
 * to count. Notice that in order to have, for instace, 100 ms you need first 
 * the 10 ms variable. The 200 us unit is always available. :cfg01 */
	static uint8_t t1ms_n200us = 0;
	static uint8_t t10ms_n200us = 0;
	static uint8_t t50ms_n10ms = 0;
	static uint8_t t100ms_n10ms = 0;
	static uint8_t t1s_n10ms = 0;
	static uint8_t t1m_n1s = 0;
#endif

	disable_interrupts; /* Check node.h */

	elapsed_time = TIME_curr_time - TIME_last_time;
	TIME_last_time = TIME_curr_time;

	enable_interrupts; /* Check node.h */
	
/* Enable the needed sections bellow according to the time units you are tracking. */

/* 200 us timers
 * var char:  1-255 => 0.2ms - 51.0ms (~0.05s)
 * var int: 1-65535 => 0.2ms - 13107ms (~13s) */
#if 0
	/*++MODULEXXX_timer; :cfg02*/
#endif

/* 1 ms timers
 * var char:  1-255 => 1ms - 255ms (~0.25s)
 * var int: 1-65535 => 1ms - 65535ms (~65.5s) */
#if 1
	t1ms_n200us += elapsed_time;
	if(t1ms_n200us >= TIME_1MS_N200US)
	{
		t1ms_n200us -= TIME_1MS_N200US; /* 1 ms = 5 * 200 us */
		++DIGITALRW_timer;
		++PWM_timer;
		/*++MODULEXXX_timer; :cfg02*/
	}
#endif

/* 10 ms timers
 * var char:  1-255 => 0.01s - 2.55s
 * var int: 1-65535 => 0.01s - 655.35s (~10.9m) */
#if 1
	t10ms_n200us += elapsed_time;
	if(t10ms_n200us >= TIME_10MS_N200US)
	{
		t10ms_n200us -= TIME_10MS_N200US; /* 10 ms = 50 * 200 us */
		++LED_timer;
		/*++MODULEXXX_timer; :cfg02*/
	}
#endif

/* 50 ms timers (needs 10 ms)
 * var char:  1-255 => 0.05s - 12.75s
 * var int: 1-65535 => 0.05s - 3276.75s (~54.6m) */
#if 0
	++t50ms_n10ms;
	if(t50ms_n10ms >= TIME_50MS_N10MS)
	{
		t50ms_n10ms = 0; /* 50 ms =  5 * 10 ms */
		/*++MODULEXXX_timer; :cfg02*/
	}
#endif

/* 100 ms timers (needs 10 ms)
 * var char:  1-255 => 0.1s - 25.5s
 * var int: 1-65535 => 0.1s - 6553.5s (~109m, ~1.8h) */
#if 0
	++t100ms_n10ms;
	if(t100ms_n10ms >= TIME_100MS_N10MS)
	{
		t100ms_n10ms = 0; /* 100 ms = 10 * 10 ms */
		/*++MODULEXXX_timer; :cfg02*/
	}
#endif

/* 1s timers (needs 10 ms)
 * var char:  1-255 => 1s - 255s (~4.2m)
 * var int: 1-65535 => 1s - 65535s (~1092m, ~18.2h) */
#if 0
	++t1s_n10ms;
	if(t1s_n10ms >= TIME_1S_N10MS)
	{
		t1s_n10ms = 0; /* 1 s = 100 * 10 ms */
		/*++MODULEXXX_timer; :cfg02*/
	}
#endif

/* 1 min timers (needs 1 s)
 * var char:  1-255 => 1m - 255m (~4.2h)
 * var int: 1-65535 => 1m - 65535m (~1092h, ~45.5d) */
#if 0
	++t1m_n1s;
	if(t1m_n1s >= TIME_1M_N1S)
	{
		t1m_n1s = 0; /* 1 min = 60 * 1 s */
		/*++MODULEXXX_timer; :cfg02*/
	}
#endif
}
