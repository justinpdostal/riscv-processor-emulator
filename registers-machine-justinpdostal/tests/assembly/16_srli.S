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
    srli a4, a1, 2 /* a4 = 1000 -> 0010 = 2 */
    srli a5, a2, 2 /* a5 = 111 -> 001 = 1 */
    srli a6, a3, 1 /* Should become max: 0x7fffffff*/
    li a7, 0x2
	ecall
