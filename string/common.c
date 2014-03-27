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

uint64_t strlen(const char *string)
{
	uint64_t l = 0;
	while (string[l++]);
	return l-1;
}

bool itoa(uint32_t num, char *buffer, uint8_t base)
{
	// Lookup table is valid up to heptadecimal (it's an inside joke)
	char lookup[] = "0123456789ABCDEFG";
	if (base > 17)
		return FALSE;
	uint8_t i;
	/// (Buffer size is 32 bytes)
	for(i = 31; i > 0; i--)
	{
		buffer[i-1] = lookup[(num % base)];
		num = (uint32_t)(num/base);
	}
	buffer[31] = 0;
	return TRUE;
}

uint32_t atoi(const char *string)
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

//strcmp()
// UNFINISHED

// HAYSTACK:
// foo bar hello woo

// NEEDLE:
// hello
bool string_contains(char *haystack, char *needle)
{
	uint32_t i;
	uint32_t j;
	uint32_t hlen = strlen(haystack);
	uint32_t nlen = strlen(needle);

	// If needle is longer than haystack, it can't be in there!
	if (strlen(needle) > strlen(haystack))
		return FALSE;

	for (i = 0; i < hlen; i++)
	{
		for (j = 0; j < nlen; j++)
		{
			if (haystack[j+i] != needle[j])
				break;
		}
		// Reached end of haystack without mismatch, we've found the needle!
		if (j == nlen)
			return TRUE;
	}
	return FALSE;
}

void memcpy(void *to, const void *from, uint32_t size)
{
	// TO DO: copy more than one byte at a time
	char *t = to;
	const char *f = from;
	uint32_t i;
	for (i = 0; i < size; i++)
		t[i] = f[i];
}


void memset(void *to, uint8_t value, uint32_t size)
{
	// TO DO: copy more than one byte at a time
	char *t = to;
	uint32_t i;
	for (i = 0; i < size; i++)
		t[i] = value;

}
#endif