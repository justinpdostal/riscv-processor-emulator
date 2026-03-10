/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests memory override */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)

    /* Initial store */
    li t1, 61
    sw t1, 0(t0)
    lw s2, 0(t0)

    /* Override */
    li t1, 94
    sw t1, 0(t0)
    lw s3, 0(t0)

    /* Store */
    li t1, 125
    sw t1, 4(t0)
    lw s4, 4(t0)

    /* Override */
    li t1, 256
    sw t1, 4(t0)
    lw s5, 4(t0)

    /* Exit syscall */
    li a7, 0x2
    ecall
