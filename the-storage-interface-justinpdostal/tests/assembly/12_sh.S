/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests halfword storage instruction sh */

.section .bss
.global memory
memory: .zero 48

.section .text
.global _start
_start:
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)

    li t1, 0x789a
    sh t1, 4(t0)

    li a7, 0x2
    ecall