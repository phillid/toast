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
 * Update cursor position to x,y co-ord for next char
 ********************************************************/
void console_set_cursor_xy(uint8_t x,uint8_t y)
{
	console_pointer = (160*y) + (2*x);
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
	for (console_pointer = 0; console_pointer < 4000; console_pointer+=2)
	{
		console_buffer[console_pointer] = 0;
		console_buffer[console_pointer+1] = console_color;
	}
	console_pointer = 0;
	console_update_cursor();
}


/*********************************************************
 * Set the console foreground AND background colours
 ********************************************************/
void console_set_colors(uint8_t fg, uint8_t bg)
{
	console_color = (bg << 4) | fg;
}

/*********************************************************
 * Swap the current console colours out
 ********************************************************/
void console_swap_colors()
{
	uint32_t t = console_color;
	console_color = saved_console_color;
	saved_console_color = t;
}

/*********************************************************
 * Set ONLY the console foreground colour
 ********************************************************/
void console_set_color(uint8_t fg)
{
	console_color &= 0xF0;				// Zero-out foreground color
	console_color |= fg;				// Apply foreground color
}


/*********************************************************
 * Print a single character
 ********************************************************/
void console_print_char(const char c)
{
	// Scroll the screen up a line if the pointer is out of bounds
	if (console_pointer >= 4000)
		console_scroll();
	switch (c)
	{
		case 8:
			console_buffer[console_pointer-=2] = 0;
			break;

		case 10:
			console_pointer += 160-(console_pointer%160);
			break;

		default:
			console_buffer[console_pointer++] = c;
			console_buffer[console_pointer++] = console_color;
	}
}


/*********************************************************
 * Print an integer of a certain base
 ********************************************************/
void console_print_num(const uint32_t num, const uint8_t base)
{
	char buffer[32];
	uint32_t i = 0;
	if (num == 0)
	{
		console_print_char('0');
	} else {
		itoa(num,buffer,base);
		// Find the first digit which isn't a trailing digit
		while(buffer[i++] == '0');
		console_print_string(buffer+i-1);
	}
}

/*********************************************************
 * Print a single null-terminated string
 ********************************************************/
void console_print_string(const char *string)
{
	uint16_t i = 0;
	while(string[i] != 0)
		console_print_char(string[i++]);
	console_update_cursor();
}

/*********************************************************
 * Print a single null-terminated string
 ********************************************************/
void console_scroll(/*uint8_t lines*/)
{
	//memcpy(console_buffer, console_buffer+160, 3840);
	memcpy(console_buffer, console_buffer+160, 3840);
	memset(console_buffer+3840, 0, 160);
	console_pointer = 3840;
}


/*********************************************************
 * Print a formatted string
 ********************************************************/
void console_print(const char* format, ...)
{
	va_list strings;
	va_start(strings,format);
	uint16_t i;
	uint64_t length = strlen(format);

	for (i = 0; i < length; i++)
	{
		if (format[i] == '%')
		{
			switch (format[++i])
			{
				case 's':
					console_print_string(va_arg(strings, char*));
					break;
				case 'c':
					console_print_char(va_arg(strings, int));
					break;
				case 'd':
					console_print_num(va_arg(strings, int),10);
					break;
				case 'x':
					console_print_num(va_arg(strings, int),16);
					break;
				case 'o':
					console_print_num(va_arg(strings, int),8);
					break;
				case 'b':
					console_print_num(va_arg(strings, int),2);
					break;
			}
		} else {
			console_print_char(format[i]);
		}
	}
	va_end(strings);
}

#endif