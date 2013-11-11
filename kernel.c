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

void kernel_main(multiboot_info_t *mbd, unsigned int magic)
{
	console_init();
	console_set_colors(COLOR_BRIGHT_GRAY,COLOR_BLACK);
	console_clear();
	console_print("Welcome to Toast v%d.%d (nickname '%s')\n",KERNEL_VERSION_MAJ,KERNEL_VERSION_MIN,KERNEL_NICKNAME);
	console_set_color(COLOR_RED);

	// Print some stuff about the bootload
	console_print("Here is kernel_main()\n");
	console_print("Bootloader: %s\n",mbd->boot_loader_name);
	console_print("BIOS Memory: %d Bytes\n",mbd->mem_upper - mbd->mem_lower);// find out 100% what this is
	console_print("Kernel: %s\n",mbd->cmdline);
	console_print("Flags: %b\n",mbd->flags);
	console_print("Boot Device: %x\n",mbd->boot_device);

	console_print("--------------------------------\nShowing console_print() off...\n%dd in binary is %b\n%oo = %xh = %dd\n%d is the ASCII code for %c\n--------------------------------\n",100,100,1234,1234,1234,112,112);


	// Show all memory stuff
	uint32_t mmaps = mbd->mmap_length;

	multiboot_memory_map_t* mmap = mbd->mmap_addr;
	while(mmap < mbd->mmap_addr + mbd->mmap_length)
	{
		mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
		console_print("%s: 0x%x to 0x%x = %d bytes\n",
						mmap->type == 1? "AVAILABLE" : "RESERVED ",
						mmap->addr,
						mmap->addr + mmap->len-1,
						mmap->len
		);
	}


	//panic(0x4655434B); // (TEST) testing panic
}