/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 10
	li a1, 4
	sub a2, a0, a1 /* a2 = 10 - 4 = 6 */
	sub a3, a1, a0 /* a3 = 4 - 10 = -6 */
	sub a4, a3, a1 /* a4 = -6 - 4 = -10 */
	sub a5, a0, a3 /* a5 = 10 - (-6) = 16 */
	li a7, 0x2
	ecall
