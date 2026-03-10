/*
 * Copyright (c) Son Nguyen, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests invalid memory address storage */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Store into invalid memory */ 
    lui t0, 0xff
    sb t1, 0(t0)

    /* Exit syscall */
    li a7, 0x2
    ecall
