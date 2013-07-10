 /*
 * list.h
 * Copyright (C) 2012 David Ludovino david.ludovino@gmail.com
 * 
 * Creates a list to support the timed write function of digital_write.c
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

#ifndef LIST_H_
#define LIST_H_

#include <stdint.h>
#include <stdlib.h>

struct node {
   uint8_t port;
   uint8_t pin;
   uint32_t end_time;
   struct node * next;
};

typedef struct node list_el;

int LIST_insert(list_el **head, uint8_t port, uint8_t pin, uint32_t end_time);
int LIST_remove_expired(list_el **head, uint32_t current_time, void (*reset_func)(uint8_t, uint8_t));

#endif /* LIST_H_ */
