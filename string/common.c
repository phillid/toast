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

#ifndef STRING_COMMON_C
#define STRING_COMMON_C

#include <toast.h>

uint64_t strlen(char *string)
{
	uint64_t l = 0;
	while (string[l] != 0)
		l++;
	return l;
}

void itoa(uint32_t num,char *buffer)
{
	uint8_t i;
	uint8_t remainder;

	for(i = 10; i > 0; i--)
	{
		remainder = num % 10;
		num = (uint32_t)(num /10);
		buffer[i-1] = remainder+48;
		console_print(buffer);
	}
	buffer[10] = 0;

}

uint32_t atoi(char *string)
{
	uint32_t i;
	uint32_t multiplier = 1;
	uint32_t total = 0;
	for (i = 0; i < strlen(string); i++)
	{
		total += (string[strlen(string)-1-i] - 48) * multiplier;
		multiplier*=10;
	}
	return total;
}

#endif
