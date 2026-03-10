/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 0x1
	li a1, 0x1f
	sllw a2, a0, 0x1f /* Left shit 1 by 31 bits */
	li a7, 0x2
	ecall


 