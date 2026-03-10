/*
 * Copyright (c) Son Nguyen, 2025.
 * Do not copy nor distribute without permission.
 */
 
/* Tests invalid memory address access */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Load from invalid memory */ 
    lui t0, 0xff
    lb t1, 0(t0)

    /* Exit syscall */
    li a7, 0x2
    ecall
