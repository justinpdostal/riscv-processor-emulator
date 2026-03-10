/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 1
	li a1, 8
    li a2, 7
    li a3, -2
    srl a4, a1, a0 /* a4 = 1000 -> 0100 = 4 */
    srl a5, a2, a0 /* a5 = 111 -> 011 = 3 */
    srl a6, a3, a0 /* Should become max: 0x7fffffff*/
    li a7, 0x2
	ecall
