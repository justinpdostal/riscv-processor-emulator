/*
 * Copyright (c) Gabriel Parmer, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 3
	li a1, 4
	add a2, a0, a1
	li a3, -5
	add a4, a2, a3
	li a4, 0xffffffff
	li a7, 0x2
	ecall
