/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests interleaved load and store instructions */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Initialize array */
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)
    li t1, 100
    sw t1, 0(t0)

    /* Interleaved operations */
    lw s2, 0(t0)
    addi s2, s2, 10
    sw s2, 4(t0)

    lw s3, 4(t0)
    addi s3, s3, 20
    sw s3, 8(t0)

    lw s4, 8(t0)
    addi s4, s4, 30
    sw s4, 12(t0)

    lw s5, 12(t0)

    /* Exit syscall */
    li a7, 0x2
    ecall
