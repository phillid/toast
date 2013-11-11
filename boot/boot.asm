; Cheers to wiki.osdev.org for this quick starter. It really helped me
; get a prototype off the ground quickly without pissing around

; Declare constants used for creating a multiboot header.
MBALIGN     equ  1<<0					; align loaded modules on page boundaries
MEMINFO     equ  1<<1					; Ask for memory map
FLAGS       equ  MBALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

; Standard mutliboot header so GRUB and other bootloaders can boot the kernel
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; Init our very own 16K stack
section .bootstrap_stack
align 4
stack_bottom:
times 16384 db 0
stack_top:

section .text
global _start
global _kernel_exit

_start:
	; Functions in external objects
	extern	kernel_main
	extern	console_print_string
	extern	console_set_color

	; Set stack up ready for C
	mov		esp, stack_top
	push	eax
	push	ebx
	call	kernel_main

	; Let the user know that kernel_main() exited
	push	0x0A
	call	console_set_color		; Reset text colour
	push	exitmain
	call	console_print_string

	; Wake us not from our slumber
	cli
_kernel_exit:
.hang:
	hlt
	jmp .hang

exitmain	db	10,"boot: kernel_main() exited",0