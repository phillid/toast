; Cheers to wiki.osdev.org for this quick starter. It really helped me
; get a prototype off the ground quickly without pissing around

; Declare constants used for creating a multiboot header.
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot

; Declare a header as in the Multiboot Standard. We put this into a special
; section so we can force the header to be in the start of the final program.
; You don't need to understand all these details as it is just magic values that
; is documented in the multiboot standard. The bootloader will search for this
; magic sequence and recognize us as a multiboot kernel.
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; Currently the stack pointer register (esp) points at anything and using it may
; cause massive harm. Instead, we'll provide our own stack. We will allocate
; room for a small temporary stack by creating a symbol at the bottom of it,
; then allocating 16384 bytes for it, and finally creating a symbol at the top.
section .bootstrap_stack
align 4
stack_bottom:
times 16384 db 0
stack_top:

; The linker script specifies _start as the entry point to the kernel and the
; bootloader will jump to this position once the kernel has been loaded. It
; doesn't make sense to return from this function as the bootloader is gone.
section .text
global _start
_start:
	extern	kernel_main
	extern	console_print
	extern	console_set_colors

	mov		esp, stack_top
	call	kernel_main

	; Let the user know that kernel_main() exited
	push	word 0x0007
	call	console_set_colors
	push	mainexit
	call	console_print
	cli
.hang:
	hlt
	jmp .hang

mainexit	db	10,"asm: kernel_main() exited",0
