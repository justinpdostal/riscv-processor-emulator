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

    /* Store a half-word using sb */
    li t1, 0x8001
    sb t1, 0(t0)

    /* End of tests */
    li a7, 0x2
    ecall