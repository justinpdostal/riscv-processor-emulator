/*
 * Copyright (c) Oliver Krisetya, 2025.
 * Do not copy nor distribute without permission.
 */

/* Tests loading and storing with negative offsets */

.section .bss
.global memory
memory: .zero 16

.section .text
.global _start
_start:
    lui t0, %hi(memory)
    addi t0, t0, %lo(memory)
    addi t0, t0, 16 /* Add offset of 16 */

    li t1, 42
    sw t1, -8(t0)
    lw s2, -8(t0)

    li t1, -999
    sw t1, -12(t0)
    lw s3, -12(t0)

    lwu t4, -12(t0) /* Should be 0xfffffC19 */

    /* Exit syscall */
    li a7, 0x2
    ecall
