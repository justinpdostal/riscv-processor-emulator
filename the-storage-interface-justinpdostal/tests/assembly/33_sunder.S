/*
 * Copyright (c) Son Nguyen, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests store instructions with inappropriate input sizes */

.section .bss
.global memory
memory: .zero 64

.section .text
.global _start
_start:
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)

    /* Store a byte using a sd */
    li t1, 0x7f
    sd t1, 0(t0)
    
    /* Exit System Call */
    li a7, 0x2
    ecall