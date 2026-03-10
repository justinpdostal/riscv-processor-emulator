/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests byte loading instruction on different values */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Initialize values */
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)
    li t1, 0x7f           /* Positive byte */
    li t2, 4              /* Offset */

    /* Store positive byte */
    add t3, t0, t2        /* Calculates the memory address given the offset */
    sb t1, 0(t3)          /* Stores byte in new address */

    lb s0, 4(t0)          /* s0 should be 0x7f (unchanged as sign bit is 0) */

    /* Store negative byte */
    li t1, 0xff           /* Negative byte (-1 in signed 8-bit) */
    sb t1, 0(t3)          /* Store byte */

    lb s2, 4(t0)          /* s2 should be 0xffffffff (-1 with sign extension to 32-bit) */

    /* Exit syscall */
    li a7, 0x2
    ecall
