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
	li a2, 0x1
	li a3, -1
  	addw a4, a0, a2 /* Lower 32 bits => 0 + 0x1 = 0x1 */
	addw a5, a0, a3 /* 0 - 1 = -1 */
	addw a6, a1, a2 /* a6 = 0 since lower 32 bits are output */
	li a7, 0x2
	ecall
