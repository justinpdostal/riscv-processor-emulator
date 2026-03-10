/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests double word loading instruction on different values (unsigned) */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Initialize values */
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)
    li t1, 0x123456789abcdef0 /* Positive double word */
    li t2, 8                  /* Offset */

    /* Store positive double word */
    add t3, t0, t2            /* Calculate memory address */
    sd t1, 0(t3)              /* Store double word (64 bits) */

    ld s1, 8(t0)              /* s1 should be 0x123456789abcdef0 (no sign extension) */

    /* Store negative double word */
    li t6, -0x123456789abcdef0 /* Negative double word */
    sd t6, 0(t3)              /* Store the negative double word */
    
    ld s3, 8(t0)              /* s3 should be 0xedcba98765432110 (no sign extension) */

    /* Exit syscall */
    li a7, 0x2
    ecall
