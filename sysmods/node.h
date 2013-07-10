 /*
 * node.h
 * Copyright (C) 2008-2011 Renato Jorge Caleira Nunes renato.nunes@ist.utl.pt
 * 
 * Contains the global defenitions of a node (computing platform in use).
 * This file needs to be configured according to the specific characteristics
 * of each node.
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

#include <stdio.h>
#include <stdint.h>

#define disable_interrupts cli()
#define enable_interrupts  sei()
