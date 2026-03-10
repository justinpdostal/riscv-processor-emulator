/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	li a0, 7
    xori a1, a0, 7   /* 111 v 111 = 000 */
    xori a2, a0, 0   /* 111 v 000 = 111 */
    xori a3, a3, 0   /* 000 v 000 = 000 */
    xori a4, a0, -1  /* all 1s v 7 = 1 with last 3 bits being 0*/
	li a7, 0x2
	ecall
