/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */


/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 2
    slli a1, a0, 3 /* 10 -> 10000 = 0x10 */
    slli a2, a0, 63 
    li a7, 0x2 
	ecall
