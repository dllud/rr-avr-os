/*
 * uart.h
 * Copyright (C) 2011 Mika Tuupola
 * Source: http://www.appelsiini.net/2011/simple-usart-with-avr-libc
 * 
 * Reads and writes chars from/to the UART (serial communication).
 * Directs stdout and stdin to the UART enabling the use of advanced
 * functions such as printf and scanf.
 */

#ifndef UART_H_
#define UART_H_

#include <stdio.h>

void UART_init(void);
void UART_putchar(char c, FILE *stream);
char UART_getchar(FILE *stream);

extern FILE UART_output;
extern FILE UART_input;

#endif /* UART_H_ */
