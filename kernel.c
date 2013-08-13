// Complain if some pleb's not using a cross-compiler
#ifdef __linux__
	#error "You're not using a cross-compiler. Good luck with that."
#endif

#include <toast.h>

void kernel_main()
{
	console_init();
	console_set_colors(COLOR_BRIGHT_GRAY,COLOR_BLACK);
	console_clear();
	console_print("Welcome to Toast "KERNEL_VERSION" (nickname '"KERNEL_NICKNAME"')\n");
	console_set_color(COLOR_RED);
	console_print("Here is kernel_main()\n");
}