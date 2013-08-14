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

#ifndef CONSOLE_C
#define CONSOLE_C

#include <toast.h>

/*********************************************************
 * Set up the console buffer and pointer
 ********************************************************/
void console_init()
{
	console_buffer = (char*)0xB8000;
	console_pointer = 0;
}

/*********************************************************
 * Update flashing cursor to match console_position
 * Note: Does _NOT_ dictate the pos for next printed byte
 ********************************************************/
void console_update_cursor()
{
	outb(0x3D4, 0x0F);
	outb(0x3D5, ((console_pointer/2) & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (((console_pointer/2)>>8)&0xFF));
}

/*********************************************************
 * Clear the console with the current colour scheme
 ********************************************************/
void console_clear()
{
	int console_pointer;
	for (console_pointer = 0; console_pointer < 4000; console_pointer++)
	{
		console_buffer[console_pointer] = console_color;
		console_buffer[console_pointer++] = 0;
	}
	//console_update_cursor();
}


/*********************************************************
 * Set the console foreground and background colours
 ********************************************************/
void console_set_colors(uint8_t fg, uint8_t bg)
{
	console_color = (bg << 4) | fg;
}


/*********************************************************
 * Set the console foreground colour
 ********************************************************/
void console_set_color(uint8_t fg)
{
	console_color &= 0xF0;				// Zero-out foreground color
	console_color |= fg;				// Apply foreground color
}

/*********************************************************
 * Print a null-terminated string to the text screen
 ********************************************************/
void console_print(char *string, ...)
{
	uint16_t i;
	for (i = 0; i < strlen(string); i++)
	{
		// If special char, handle appropriately
		if (string[i] < 32)
		{
			switch (string[i])
				case 10:
					console_pointer = 160 + (console_pointer / 160) * 160;
		} else {
			console_buffer[console_pointer++] = string[i];
			console_buffer[console_pointer++] = console_color;
		}
	}
	console_update_cursor();
}

#endif