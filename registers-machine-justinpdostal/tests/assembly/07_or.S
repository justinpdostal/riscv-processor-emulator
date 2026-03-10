/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 7
    li a1, 0
    or a2, a0, a0 /* 111 | 111 = 111 */
    or a3, a0, a1 /* 111 | 000 = 111 */
    or a4, a1, a1 /* 000 | 000 = 000 */
    li a4, 8
    xor a5, a0, a4 /* 1000 | 111 = 1111 */
	li a7, 0x2
	ecall
