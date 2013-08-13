#ifndef LOWLEVEL_C
#define LOWLEVEL_C

#include <toast.h>

void outb(uint16_t p,uint8_t val)
{
   asm("outb %%al,%%dx;"
		   :
		   :"d"(p),"a"(val)
   );
}

void disable_ints()
{
	asm("cli");
}

void enable_ints()
{
	asm("sti");
}

#endif