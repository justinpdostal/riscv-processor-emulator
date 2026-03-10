/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 5
	addi a1, a0, 3
    li a2, 0x7fffffff
    addi a3, a2, 2
	li a7, 0x2
	ecall
