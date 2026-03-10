/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests large storage offsets */

.section .bss
.global memory
memory: .zero 64

.section .text
.global _start
_start:
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)

    li t1, 0x12345678 
    sw t1, 40(t0)

    li t1, 0x87654321
    sw t1, -20(t0)

    lw s2, 40(t0)
    lw s3, -20(t0)

    /* Exit syscall */
    li a7, 0x2
    ecall
