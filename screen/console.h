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

#ifndef __CONSOLE_H
#define __CONSOLE_H

#include <stdarg.h>

#define console_width		80
#define console_height		25
#define console_x_pos		(console_pointer%(2*console_width))
#define console_y_pos		(uint8_t)(console_pointer/(2*console_width))

#define COLOR_BLACK			0x0
#define COLOR_BLUE			0x1
#define COLOR_GREEN			0x2
#define COLOR_TEAL			0x3
#define COLOR_BROWN			0x4
#define COLOR_PURPLE		0x5
#define COLOR_GOLD			0x6
#define COLOR_BRIGHT_GREY	0x7
#define COLOR_GRAY			0x8
#define COLOR_BRIGHT_BLUE	0x9
#define COLOR_BRIGHT_GREEN	0xA
#define COLOR_AQUA			0xB
#define COLOR_RED			0xC
#define COLOR_PINK			0xD
#define COLOR_YELLOW		0xE
#define COLOR_WHITE			0xF

#define COLOR_BRIGHT_GRAY	COLOR_BRIGHT_GREY	// Alias for grey <--> gray
#define COLOR_GREY			COLOR_GRAY			// Alias for grey <--> gray
#define COLOR_LIME			COLOR_BRIGHT_GREEN	// Alias for lime <--> bright green

char* console_buffer;
uint16_t console_pointer;
uint8_t console_color;
uint8_t saved_console_color;

void console_init();
void console_set_cursor_xy(uint8_t x,uint8_t y);
void console_update_cursor();
void console_clear();
void console_set_colors(uint8_t fg, uint8_t bg);
void console_set_color(uint8_t fg);
void console_swap_colors();
void console_print_char(const char c);
void console_print_string(const char *string);
void console_print(const char* format,...);
void console_print_num(uint32_t num, uint8_t base);
void console_scroll();
#endif