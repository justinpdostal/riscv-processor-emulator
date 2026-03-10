#pragma once

#include <instructions.h>

//
struct processor;
enum exception;
/*
 * This is the main structure that stores the registers state. In this
 * homework, this focuses on the registers. You'll need to modify this
 * structure to track whatever you find necessary to be able to
 * complete the assignment.
 *
 * Do not change the name of this structure as we'll use it in our
 * code.
 */
struct registers {
    unsigned long pc;
    struct reg *regs;
};

struct reg {
    int index;
    unsigned long value;
};

/*
 * Allocate a new registers state. This should initialize the
 * registers assuming that the initial instruction to execute is the
 * first in the instruction array. This should not be called with
 * `num_instr < 1`. All registers should be initialized to `0`.
 *
 * - `@init_pc_value` - The value to initialize the `pc` to.
 * - `@return` - The new registers state.
 */
struct registers *registers_alloc(unsigned long init_pc_value);

/*
 * Free the previously allocated registers.
 *
 * - `@regs` - the registers to be freed.
 */
void registers_free(struct registers *regs);

/*
 * This function will dump out the state of a single register within a
 * registers state.
 *
 * - `@state` -the current state of all registers
 * - `@regno` - which register's value to return, `0 = x0`, through
 *   `31 = x31`. This value must be between 0 and 31.
 * - `@return` - The value at the register corresponding to regno
 */
unsigned long registers_getreg(struct registers *state, unsigned int regno);

/*
 * This function will update the state of a single register to a given
 * value.
 *
 * - `@state` - Same as above.
 * - `@regno` - which register's value to return, `0 = x0`, through
 *   `31 = x31`. This value must be between 0 and 31.
 * - `@value` - the value to set the register to.
 */
void registers_setreg(struct registers *state, unsigned int regno, unsigned long value);

/*
 * Similar to `registers_getreg`, but simply return the program
 * counter (`pc`).
 *
 * - `@state` - same as above.
 * - `@return` - the current program counter.
 */
unsigned int registers_getpc(struct registers *state);

/*
 * Similar to `registers_setreg`, but simply initialize the program
 * counter (`pc`).
 *
 * - `@state` - same as above.
 */
void registers_setpc(struct registers *state, unsigned long value);


/* Some useful types */
typedef unsigned long      u64_t;
typedef signed long        s64_t;
typedef unsigned int       u32_t;
typedef signed int         s32_t;
typedef unsigned short int u16_t;
typedef signed short int   s16_t;
typedef unsigned char      u8_t;
typedef signed char        s8_t;

// Helper functions:
u64_t rrr(struct processor *processor, struct instruction *inst, enum exception *e);
u64_t ror(struct processor *processor, struct instruction *inst, enum exception *e);
u64_t rri(struct processor *processor, struct instruction *inst, enum exception *e);
u64_t ri(struct processor *processor, struct instruction *inst, enum exception *e);
u64_t ecall(struct processor *processor, struct instruction *inst, enum exception *e);

u64_t dec(int* bits, int place);
void copy(int* bits, int* cbits);