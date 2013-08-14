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


// Complain if some pleb's not using a cross-compiler
#if defined(__linux__)
	#error "You're not using a cross-compiler. Good luck with that."
#endif

#include <toast.h>

void kernel_main()
{
	char b[10];
	console_init();
	console_set_colors(COLOR_BRIGHT_GRAY,COLOR_BLACK);
	console_clear();
	console_print("Welcome to Toast "KERNEL_VERSION" (nickname '"KERNEL_NICKNAME"')\n");
	console_set_color(COLOR_RED);
	console_print("Here is kernel_main()\n");
	char test[] = "1234";
	int a = atoi(test);
	itoa(a,b);
}