/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 7
    xor a1, a0, a0 /* 111 v 111 = 0 */
    xor a2, a1, a0 /* 000 v 111 = 111 */
    xor a3, a1, a1 /* 000 v 000 = 000 */
    li a3, 8
    xor a4, a3, a0 /* 0111 v 1000 = 1111 */
	li a7, 0x2
	ecall
