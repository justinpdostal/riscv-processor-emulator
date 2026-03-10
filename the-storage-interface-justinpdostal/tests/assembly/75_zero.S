/*
 * Copyright (c) Son Nguyen, 2025.
 * Do not copy nor distribute without permission.
 */
 

/* Tests loading from memory into x0 register */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Loading values into x0 should remain unchanged */
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)

    /* Store 0x7f into memory */
    li t1, 0x7f
    sb t1, 0(t0)
    /*Fixed Below*/
    lb x0, 0(x5)
    
    /* Load the value from memory into x0 */

    /* Exit syscall */
    li a7, 0x2
    ecall
