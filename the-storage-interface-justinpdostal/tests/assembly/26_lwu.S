/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests word loading instruction on different values (unsigned) */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    /* Initialize values */
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)
    li t1, 0x12345678       /* Positive word */
    li t2, 8                /* Offset */

    /* Store positive word */
    add t3, t0, t2          /* Calculate memory address */
    sw t1, 0(t3)            /* Store word (32 bits) */

    lwu s1, 8(t0)           /* s1 should be 0x12345678 (no sign extension) */

    /* Store negative word */
    lui t6, 0xfffff         /* Load upper 20 bits (0xfffff) into t6 */
    addi t6, t6, 0x678      /* Add lower 12 bits (0x678) to t6 */
    sw t6, 0(t3)            /* Store the negative word */
    
    lwu s3, 8(t0)           /* s3 should be 0xfffff678 (no sign extension) */

    /* Exit syscall */
    li a7, 0x2
    ecall
