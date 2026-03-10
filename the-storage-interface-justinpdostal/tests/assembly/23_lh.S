/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests halfword loading instruction on different values */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Initialize values */
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)
    li t1, 0x7f7f         /* Positive halfword */
    li t2, 6              /* Offset */

    /* Store positive halfword */
    add t3, t0, t2        /* Calculate memory address */
    sh t1, 0(t3)          /* Store halfword (16 bits) */
    /*Fixed Below*/
    lh x8,6(x5)

    /* Store negative halfword */
    li t6, 0xff7f         /* Load a negative value to store (to test sign extension) */
    sh t6, 0(t3)          /* Store the negative halfword */
    
    lh s2, 6(t0)          /* s2 should be 0xffffffffffffff7f (sign-extended to 32-bit) */

    /* Exit syscall */
    li a7, 0x2
    ecall
