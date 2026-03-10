/*
 * Copyright (c) Gabriel Parmer, 2024.
 * Do not copy nor distribute without permission.
 */

/* Allocate 4096 bytes for the execution stack */
.section .bss
.global __stack_bottom
.align 8
__stack_bottom:	.zero 4096
__stack_top:

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a7, 5 /* invalid value! */
	ecall
	li a7, 2
	ecall
	nop
