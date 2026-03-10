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
	addiw a4, a0, 1 /* Lower 32 bits => 0 + 0x1 = 0x1 */
	addiw a5, a0, -1 /* 0 - 1 = -1 */
	addiw a6, a1, 1 /* Lower 32 bits output = 0 */
	li a7, 0x2
	ecall
