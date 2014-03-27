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

#ifndef LOWLEVEL_C
#define LOWLEVEL_C

#include <toast.h>

void outb(uint16_t port, uint8_t data)
{
   asm("outb %%al,%%dx;"
		   :
		   :"d"(port),"a"(data)
   );
}

void disable_ints()
{
	asm("cli");
}

void enable_ints()
{
	asm("sti");
}

#endif