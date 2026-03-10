/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests word storage instruction sw */

.section .bss
.global memory
memory: .zero 48

.section .text
.global _start
_start:
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)
    /*Fixed Below*/     
    sw x6,12(x5)

    li a7, 0x2
    ecall