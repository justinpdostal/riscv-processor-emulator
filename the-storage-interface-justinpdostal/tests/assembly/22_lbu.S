/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests byte loading instruction on different values (unsigned) */

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

    lbu s1, 4(t0)         /* s1 should also be 0x7f (unsigned, so no sign extension) */

    /* Store negative byte */
    li t1, 0xff           /* Negative byte (-1 in signed 8-bit) */
    sb t1, 0(t3)          /* Store byte */

    lbu s3, 4(t0)         /* s3 should be 0xff (no sign extension, zero-padded) */

    /* Exit syscall */
    li a7, 0x2
    ecall
