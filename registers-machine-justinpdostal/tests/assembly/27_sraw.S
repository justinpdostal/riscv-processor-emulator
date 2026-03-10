/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	addi x10,x0,1
    slli x10,x10, 0x20
    addi x10,x10,-1
	li a7, 0x2
	ecall


 