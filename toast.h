/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#ifndef TOAST_H
#define TOAST_H

#define KERNEL_VERSION_MAJ	0
#define KERNEL_VERSION_MIN	1
#define KERNEL_NICKNAME		"Hydrogen"
#define NULL				0
#define SUCCESS				1

#include <stdint.h>					// uint_8 etc
#include <stdbool.h>				// Get our boolean types defined

#define TRUE true
#define FALSE false

#include <screen/console.h>			// Console output functions
#include <lowlevel.h>				// Low level assembly, eg outb(port,val)
#include <string/common.h>			// Common string functions
#include <panic.h>					// Kernel panic and emergency procedures
#include <multiboot.h>


// KERNEL.C
void kernel_main();

#endif
