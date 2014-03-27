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

// Complain if some pleb's using a linux toolchain and not cross-compiling
#if defined(__linux__)
	#error "You're not using a cross-compiler. Good luck with that."
#endif

#include <toast.h>

// vv-- Put me somewhere --vv
uint32_t TOTAL_MEMORY = 0;			// Total memory. Typically set by k_tally_available_memory().
									// It must be initialised to 0 so that if it's not set otherwise, nothing will think there's memory available
bool KERNEL_OPTION_QUIET	= FALSE;
bool KERNEL_OPTION_SILENT	= FALSE;
bool KERNEL_OPTION_ESHELL	= FALSE;
// ^^-- put me somewhere --^

void kernel_main(multiboot_info_t *mbd, uint32_t magic)
{
	//*********************************************************
	// First things first. Parse the command line. Quick guide:
	//
	//  o quiet  - Don't print so much stuff to the screen during boot
	//  o silent - Don't print anything at all during boot (implies quiet)
	//  o eshell - (RESERVED) Will be used to enter emergency shell
	//
	if (string_contains( (char*)(mbd->cmdline) , "quiet"))
		KERNEL_OPTION_QUIET = TRUE;

	if (string_contains( (char*)(mbd->cmdline) , "silent"))
	{
		KERNEL_OPTION_QUIET = TRUE;
		KERNEL_OPTION_SILENT = TRUE;
	}
	if (string_contains( (char*)(mbd->cmdline) , "eshell"))
		KERNEL_OPTION_ESHELL = TRUE;
	//*********************************************************

	//*********************************************************
	// Do some important things before we forget
	k_tally_available_memory(mbd);

	// Init the text console and colours
	console_init();
	console_set_colors(COLOR_BRIGHT_GRAY, COLOR_BLACK);
	console_swap_colors();
	console_set_colors(COLOR_BRIGHT_GRAY, COLOR_BLACK);
	console_clear();
	//*********************************************************

	if (!KERNEL_OPTION_QUIET)
	{
		// Print some stuff about the environment
		console_print("Here is kernel_main()\n");
		console_print("Bootloader: %s\n",mbd->boot_loader_name);
		console_print("Kernel: %s\n",mbd->cmdline);
		console_print("Flags: %b\n",mbd->flags);
		console_print("Boot Device: %x\n",mbd->boot_device);

		// Dump some info about the memory blocks/regions available/reserved
		k_dump_memory_blocks(mbd);
	}
	if (!KERNEL_OPTION_SILENT)
	{
		console_print("Welcome to Toast v%d.%d (nickname '%s')\nMemory: %dMiB",
						KERNEL_VERSION_MAJ,
						KERNEL_VERSION_MIN,
						KERNEL_NICKNAME,
						TOTAL_MEMORY/1048576);
	}
	//panic(0x4655434B); // (TEST) testing panic
}

/*********************************************************
 * Tally/total the amount of available memory and store
 * it for later use. Returns pointer to total mem figure
 ********************************************************/
uint32_t *k_tally_available_memory(multiboot_info_t *mbd)
{
	multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbd->mmap_addr;
	TOTAL_MEMORY = 0;

	while((uint32_t)mmap < mbd->mmap_addr + mbd->mmap_length)
	{
		mmap = (multiboot_memory_map_t*)( (uint32_t)mmap + mmap->size + sizeof(uint32_t) );

		if (mmap->type == 1) // available
			TOTAL_MEMORY += (uint32_t)mmap->len;
	}
	return &TOTAL_MEMORY;
}

/*********************************************************
 * Dump information about the blocks of memory. What
 * starts and finishes where and available/reserved
 ********************************************************/
void k_dump_memory_blocks(multiboot_info_t *mbd)
{
	multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbd->mmap_addr;

	// While we're pointing to a mem map struct within the supplied range...
	while((uint32_t)mmap < mbd->mmap_addr + mbd->mmap_length)
	{
		mmap = (multiboot_memory_map_t*)( (uint32_t)mmap + mmap->size + sizeof(uint32_t) );
		console_print("[");

		// Save current console colours
		console_swap_colors();

		if (mmap->type == 1)
		{
			console_set_colors(COLOR_GREEN, COLOR_BLACK);
			console_print("   FREE   ");
		} else {
			console_set_colors(COLOR_RED, COLOR_BLACK);
			console_print(" RESERVED ");
		}
		// Restore old console colours
		console_swap_colors();

		console_print("] 0x%x to 0x%x = %d bytes\n",
						(uint32_t)mmap->addr,
						(uint32_t)mmap->addr + (uint32_t)mmap->len-1,
						(uint32_t)mmap->len
		);
	}
}