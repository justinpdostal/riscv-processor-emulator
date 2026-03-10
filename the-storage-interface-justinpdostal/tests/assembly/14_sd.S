/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests doubleword storage instruction sd */

.section .bss
.global memory
memory: .zero 64

.section .text
.global _start
_start:
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)

    li t1, 0x3456789abcdef012
    sd t1, 8(t0)
    
    li a7, 0x2
    ecall