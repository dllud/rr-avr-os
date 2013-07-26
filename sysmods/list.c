 /*
 * list.c
 * Copyright (C) 2012-2013 David Ludovino david.ludovino@gmail.com
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

#include "list.h"

int LIST_insert(list_el **head, volatile uint8_t *port, uint8_t pin, uint32_t end_time) {
    list_el *new_el;
    new_el = malloc(sizeof(struct node));
    if(new_el == NULL)
    	return -1; // Out of space
    new_el->port = port;
    new_el->pin = pin;
    new_el->end_time = end_time;
    new_el->next = *head;
    *head = new_el;
    return 0;
}

static inline int LIST_remove(list_el **head, list_el *prev, list_el *to_remove) {
	if(to_remove == *head) // The element is the head of the list.
		*head = to_remove->next;
	else // It's not the head.
		prev->next = to_remove->next;
	free(to_remove);
	return 0;
}

int LIST_remove_expired(list_el **head, uint32_t current_time, void (*reset_func)(volatile uint8_t *, uint8_t)) {
	list_el *prev, *current, *old_current;
	prev = current = *head;
	while(current != NULL) {
		if(current_time >= current->end_time) {
			(*reset_func)(current->port, current->pin);
			old_current = current;
			current = current->next;
			LIST_remove(head, prev, old_current); //Removes current
		}
		else {
			prev = current;
			current = current->next;
		}
	}
	return 0;
}
