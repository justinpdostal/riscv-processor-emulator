/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 0x100000000
	li a1, 0xffffffff
	li a2, -1
	li a3, 1
	subw a3, a0, a2 /* Lower 32 bits => 0 - -1 = 0+1 = 1 */
	subw a4, a0, a3 /* 0 - 1 = -1 */
	subw a5, a1, a2 
	li a7, 0x2
	ecall
