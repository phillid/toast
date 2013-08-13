#ifndef __TOAST_H
#define __TOAST_H

#define KERNEL_VERSION		"0.1"
#define KERNEL_NICKNAME		"Unstable"

#include <stdbool.h>			// Get our booleans defined
#include <stdint.h>				// uint_8 etc

#include <console.h>
#include <lowlevel.h>
#include <string.h>

// KERNEL.C
void kernel_main();

#endif