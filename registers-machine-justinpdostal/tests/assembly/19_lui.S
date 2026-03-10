/*
 * Copyright (c) Son Nguyen, 2024.
 * Do not copy nor distribute without permission.
 */

/* The starting instructions that call main */
.section .text
.global _start
_start:
	lui x0, 0x1 /* No change */ 
    lui a1, 0x1 /* 1 << 12 = 0x1000 */
    lui a2, 0xFFFFF /* Highest possible should get: 0xFF000 */
    li a7, 0x2 
	ecall
