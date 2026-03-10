/*
 * Copyright (c) Son Nguyen, 2025.
 * Do not copy nor distribute without permission.
 */

/* Test loading instruction using smaller sizes */

.section .bss
.global memory
memory: .zero 64

.section .text
.global _start
_start:
    /* Initialize memory with some values */
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)

    /* Store a byte into memory */
    li t1, 0x7f
    sb t1, 0(t0)

    /* Load it as a word */
    lw t2, 0(t0)      

    # /* Exit syscall */
    li a7, 0x2          
    ecall
