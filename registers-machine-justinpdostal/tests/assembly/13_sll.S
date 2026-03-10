/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 2
	li a1, 8
    li a2, 63
    sll a3, a0, a1 /* a2 = 2 * 2^8 = 512 */
    sll a4, a0, a2 
    li a7, 0x2
	ecall
