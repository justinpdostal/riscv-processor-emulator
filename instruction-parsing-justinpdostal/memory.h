#pragma once

/* Define this structure in your code in your .c file */
struct memory;

/*
 * Allocate and free the memory struct. You can store whatever you
 * need in the memory structure (you define it yourself). The
 * `memory_sz` is the total amount of memory required in the program.
 */
struct memory *memory_alloc(unsigned long memory_sz);
void memory_free(struct memory *m);
