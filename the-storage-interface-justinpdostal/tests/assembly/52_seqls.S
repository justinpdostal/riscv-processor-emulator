/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests sequential load and store instructions */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)

    /* Sequential stores */
    li t1, 10
    sw t1, 0(t0)
    li t1, 20
    sw t1, 4(t0)
    li t1, 30
    sw t1, 8(t0)
    li t1, 40
    sw t1, 12(t0)

    /* Sequential loads */
    lw s2, 0(t0)            /* Load word from memory[0] into s2 (should be 10) */
    lw s3, 4(t0)            /* Load word from memory[1] into s3 (should be 20) */
    lw s4, 8(t0)            /* Load word from memory[2] into s4 (should be 30) */
    lw s5, 12(t0)           /* Load word from memory[3] into s5 (should be 40) */

    /* Exit syscall */
    li a7, 0x2
    ecall
