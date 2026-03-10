/*
 * Do NOT change this file. This is the "stable API" for the processor
 * emulator, thus should not be changed.
 */

#pragma once

#include <registers.h>
#include <instructions.h>

/*
 * Configuration variables for the program and emulator. This includes:
 *
 * 1. Addresses for the program. These include the lower and upper
 * instruction addresses, the address of the instruction to start
 * execution at (the first instruction of the program), and the size
 * of memory.
 *
 * 2. Binary variables that configure if the emulator should not print
 * out certain state.
 *
 * 3. Cache configuration state for the relevant homework.
 */
struct configuration {
	/*
	 * What is the lowest instruction address, the upper, and what
	 * is the initial entry_address.
	 */
	unsigned long instr_lower, instr_upper, entry_address;
	/* How large is the memory (that is all initially set to zero)? */
	unsigned long memory_sz;
        /*
	 * Variables indicating if we should print out instructions
         * and registers while emulating the processor
	 */
	unsigned long print_instrs, print_regs;

        /* To be used in the cache homeworks */
	unsigned long cache_sets, cache_tot_cachelines;
};

struct processor {
	struct configuration cfg;
	/* Populated and used in the instruction parsing homework */
	struct instructions *instrs;
	/* Populated and used in the register instruction homework */
	struct registers *rs;
};

/*
 * When the processor is asked by an instruction to do something it
 * doesn't know how to process, it "throws an exception". In our
 * emulator, when an exception is thrown, we'll print out an error,
 * and exit the program. In real OSes, these exceptions are what lead
 * to "segmentation faults".
 */
enum exception {
  /*
   * Attempt to execute an instruction outside of the range of
   * addresses holding instructions.
   */
  EXCEPTION_INSTRUCTION,
  /*
   * Attempt to access a memory address outside of the range of
   * addresses holding data.
   */
  EXCEPTION_MEMORY,
  /*
   * Program attempts to exit, thus should be shut down. Normally this
   * isn't a processor exception, and is instead handled by the OS.
   */
  EXCEPTION_EXIT,
  /*
   * Program attempts to make a system call that we don't identify.
   * This should be treated as a fault that will terminate the
   * program.
   */
  EXCEPTION_UNKNOWN_SYSCALL,
};

/*
 * The following functions emulate a single instruction's execution.
 * This execution will make changes in the processor's `registers` and
 * memory.

 * Note that they must progress the program counter, either because of
 * their own logic (i.e. branches or jumps), or my moving on to the
 * next instruction. In this case, the functions will progress the
 * program counter to the next instruction, which is 4 bytes forward
 * (since all RISCV instructions are 4 bytes long.
 */

/*
 * Emulate a single instruction if it only performs register
 * operations. If the instruction at the pc is not an instruction that
 * only performs register operations, then this will make *no
 * changes*.
 *
 * - `@processor` - The processor and register state that has tracked
 *   all execution up until this state.
 * - `@instruction` - the current instruction that should be emulated.
 * - `@e` - the exception we're returning to the call that is populated
 *   in the case that this function's return value is `-1`.
 * - `@return` - return `0` if an instruction is executed, `1` if no
 *   instructions were executed, and `-1` if there is an exception. In
 *   the latter case, `e` holds the exception.
 */
int processor_emulate_regops(struct processor *processor, struct instruction *i, enum exception *e);

/*
 * Emulate a single instruction if it performs memory operations. If
 * the instruction at the pc is not an instruction that only performs
 * memory operations (load or store), then this will make *no
 * changes*.
 *
 * - `@processor` - The processor and register state that has tracked
 *   all execution up until this state.
 * - `@instruction` - the current instruction that should be emulated.
 * - `@e` - the exception we're returning to the call that is populated
 *   in the case that this function's return value is `-1`.
 * - `@return` - return `0` if an instruction is executed, `1` if no
 *   instructions were executed, and `-1` if there is an exception. In
 *   the latter case, `e` holds the exception.
 */
int processor_emulate_memops(struct processor *processor, struct instruction *i, enum exception *e);

/*
 * Emulate a single instruction if it only performs control flow
 * operations including conditionals or jumps. If the instruction at
 * the pc is not an instruction that only performs branch operations,
 * then this will make *no changes*.
 *
 * - `@processor` - The processor and register state that has tracked
 *   all execution up until this state.
 * - `@instruction` - the current instruction that should be emulated.
 * - `@e` - the exception we're returning to the call that is populated
 *   in the case that this function's return value is `-1`.
 * - `@return` - return `0` if an instruction is executed, `1` if no
 *   instructions were executed, and `-1` if there is an exception. In
 *   the latter case, `e` holds the exception.
 */
int processor_emulate_cntlflowops(struct processor *processor, struct instruction *i, enum exception *e);

/*
 * Emulate the processor on the loaded program! This is the main entry
 * point into your emulator's logic!
 *
 * Execution in the processor's `registers`. This will not only
 * execute the instruction (using the register state that has been
 * tracked in the execution so far), but will also progress the
 * program counter to the next instruction. Note that each instruction
 * on RISCV 32 is 4 bytes long, so progressing to the next instruction
 * means progressing the `pc` register by `4` bytes.
 *
 * The implementation of this function will call all of the
 * `processor_emulate_*` functions above to separately emulate
 * different instructions. This function is the core of your
 * implementation.
 *
 * - `@processor` - The processor and register state that has tracked
 *   all execution up until this state.
 */
void processor_emulate(struct processor *p);

struct processor *processor_alloc(struct configuration *cfg, struct instructions *instrs, struct registers *rs);
void processor_free(struct processor *p);

/* Print out processor information */
void processor_registers_print(struct processor *p);
void processor_registers_printall(struct processor *p);

/* Utility function to print out an exception, when it happens */
void processor_print_exception(struct processor *p, enum exception e);
