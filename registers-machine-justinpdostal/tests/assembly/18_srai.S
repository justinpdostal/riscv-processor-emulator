/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a1, 8
    li a2, 7
    li a3, -2
    srai a4, a1, 2 /* a4 = 1000 -> 0010 = 2 */
    srai a5, a2, 2 /* a5 = 111 -> 001 = 1 */
    srai a6, a3, 1 /* Arithmetic shift = 0xFFFFFFFF  */
    li a7, 0x2
	ecall
