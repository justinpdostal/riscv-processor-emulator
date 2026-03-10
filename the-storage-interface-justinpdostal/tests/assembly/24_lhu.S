/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests halfword loading instruction on different values (unsigned) */

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

    lhu s1, 6(t0)         /* s1 should be 0x7f7f (no sign extension) */

    /* Store negative halfword */
    li t6, 0xff7f         /* Load a negative value to store (to test sign extension) */
    sh t6, 0(t3)          /* Store the negative halfword */
    
    lhu s3, 6(t0)         /* s3 should be 0xff7f (no sign extension) */

    /* Exit syscall */
    li a7, 0x2
    ecall
