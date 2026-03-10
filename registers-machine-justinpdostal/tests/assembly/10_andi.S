/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 7
    andi a1, a0, 7   /* 111 & 111 = 111 */
    andi a2, a0, 0   /* 111 & 000 = 000 */
    andi a3, a3, 0   /* 000 & 000 = 000 */
    andi a4, a0, -1  /* all 1s & 7 = 7 */
    li a7, 0x2
	ecall
