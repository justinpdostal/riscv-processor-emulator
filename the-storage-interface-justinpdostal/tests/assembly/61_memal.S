/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests memory aliasing */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Share reference to same memory */
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)
    lui t1, %hi(memory)
    addi t1, t1, %lo(memory)

    /* Store */
    li t2, 64
    sw t2, 0(t0)

    lw s2, 0(t1) /* Should be x40 if addresses match */

    li t2, 32
    sw t2, 0(t1)

    lw s3, 0(t0) /* Should be x20 */

    /* Exit syscall */
    li a7, 0x2
    ecall
