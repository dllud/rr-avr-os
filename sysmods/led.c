 /*
 * led.c
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

/* Global includes */
#include "node.h"

/* Global includes for AVR */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Specific inlucdes for this module */
#include "led.h"

/* ::define **/
#define LED_PORT  PORTB
#define LED_PIN_MASK  0x20  /* PIN5 : 0010 0000 */
/* Arduino has no internal watchdog. */

/* Internal LED in Arduino lights on HIGH. */
#define LED_TURN_ON    LED_PORT |= LED_PIN_MASK
#define LED_TURN_OFF   LED_PORT &= ~LED_PIN_MASK
#define LED_TOGGLE     LED_PORT ^= LED_PIN_MASK

#define LED_PULSE_TIME   20  /* 200 ms */
#define LED_PAUSE_TIME   50  /* 500 ms */

/* Global variables */
uint8_t LED_timer = 0;  /* 10 ms */

/* Local variables */
static uint8_t led_num_toggles, led_toggle_n;

/* Assigns the adequate value to led_num_toggles which defines the
 * number of impulses the "alive" LED will emmit.
 * led_num_toggles = ("num_pulses" * 2) - 1. */
void LED_num_pulses(uint8_t num_pulses)
{
  led_num_toggles = (num_pulses << 1) - 1;
}

/* Initialization of this task.*/
void LED_init(uint8_t num_pulses)
{
  /* PIN of the internal LED was already initialized. 
   * Check avr_init() in main.c */
  /* led_timer = 0; unnecessary */
  LED_num_pulses(num_pulses);
  /* led_toggle_n = 0; unnecessary */
}

/* LED task. Controls the "alive" LED. The LED emmits a sequence of blinks
 * separated by a pause. Timmings are defined in LED_[PULSE/PAUSE]_TIME.
 * The number of sequential blinks depends on led_num_toggles. For N
 * blinks this variable must contain the value 2*N-1. Check led_num_pulses().*/
void LED_task(void)
{
  if(led_toggle_n == 0)
  {
    if(LED_timer >= LED_PAUSE_TIME)
    {
      LED_TOGGLE;
      LED_timer = 0;
      led_toggle_n = led_num_toggles;
    }
  }
  else
  {
    if(LED_timer >= LED_PULSE_TIME)
    {
      LED_TOGGLE;
      LED_timer = 0;
      --led_toggle_n;
    }
  }
}
