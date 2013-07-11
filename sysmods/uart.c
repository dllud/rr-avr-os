/*
 * uart.c
 * Copyright (C) 2011 Mika Tuupola
 * Source: http://www.appelsiini.net/2011/simple-usart-with-avr-libc
 * 
 * Reads and writes chars from/to the UART (serial communication).
 * Directs stdout and stdin to the UART enabling the use of advanced
 * functions such as printf and scanf.
 */

/* Global includes */
#include "node.h"

/* Global inclues for AVR */

 #include <avr/io.h>

#define F_CPU 16000000UL
#define BAUD 9600

/* Includes specific to this module */
#include <util/setbaud.h>
#include "uart.h"

FILE UART_output = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);
FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_getchar, _FDEV_SETUP_READ);

void UART_init(void) {
	stdout = &UART_output;
	stdin  = &UART_input;

	UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

/* TODO: Add a set of buffers for input and output.
 * This way client modules would not block during a read or write.
 * Such would facilitate the fulfillment of time constraints.
 * Later this module would empty the buffers.
 */
void UART_putchar(char c, FILE *stream) {
    if (c == '\n') {
        UART_putchar('\r', stream);
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

char UART_getchar(FILE *stream) {
	/* Wait until data exists. */
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
