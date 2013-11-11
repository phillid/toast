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

#ifndef STRING_COMMON_H
#define STRING_COMMON_H

uint64_t strlen(const char *string);
bool itoa(uint32_t num, char *buffer, uint8_t base);
uint32_t atoi(const char *string);
void memcpy(void *to, const void *from, uint32_t size);
void memset(void *to, uint8_t value, uint32_t size);

#endif