/*
 * Copyright (c) Gabriel Parmer, 2024.
 * Do not distribute without permission.
 */

#pragma once

enum instruction_num {
	/* register operations homework */
	ECALL,		/* System call, with the "command" in x17 (or a7) */
	ADD,
	ADDW,
	ADDI,
	ADDIW,
	SUB,
	SUBW,
	SLL,
	SLLW,
	SRL,
	SRLW,
	SRA,
	SRAW,
	SLLI,
	SLLIW,
	SRLI,
	SRLIW,
	SRAI,
	SRAIW,
	OR,
	ORI,
	AND,
	ANDI,
	XOR,
	XORI,
	LUI,
	SLT,
	SLTU,
	SLTI,
	SLTIU,

	/* memory operations homework */
	SB,
	SH,
	SW,
	LB,
	LH,
	LW,
	LBU,
	LHU,
	LWU,
	LD,
	SD,

	/* control flow operations homework */
	BEQ,
	BNE,
	BLT,
	BGE,
	BLTU,
	BGEU,
	AUIPC,
	JAL,
	JALR,

	/* metadata values, not actual instructions */
	INSTRCNT,		/* This is an integer that contains the number of instruction types */
	INSTRINVALID,		/* Used as the return value for invalid instructions */
};

enum instr_fmt {
	FMT_RRR,
	FMT_RRI,
	FMT_RI,
	FMT_ROR,
	FMT_ECALL,
	FMT_ERROR, 		/* Can't find the format */
};

/* Instructions with `rd, rs1, rs2` format. */
struct instfmt_rrr {
	unsigned int rd, rs1, rs2;
};

/* Instructions with `rd, rs1, imm` or `rs1, rs2, offset` formats. */
struct instfmt_rri {
	unsigned int rd, rs1;
	long imm;
};

/* Instructions with `rd, imm` or `rd, offset` formats. */
struct instfmt_ri {
	unsigned int rd;
	long imm;
};

/*
 * Instructions with `r2, offset(r1)` or `rd, offset(r1)`
 * formats.
 */
struct instfmt_ror {
	unsigned int r2, r1;
	long offset;
};

/*
 * The `ecall` instruction!
 *
 * This has no arguments, but it assumes that the "system call number"
 * is in `a7` or `x17`. We'll only support two "system calls": `exit`
 * with a system call number of `2` (we'll see this in xv6 in CSCI
 * 3411), and `23` which we'll take to be "print out processor state".
 */
struct instfmt_ecall {
};

struct instruction {
	/* Which type of instruction is this? */
	enum instruction_num inst_no;
	/* What is the address of this instruction? */
	unsigned long inst_addr;
	/*
	 * What format is the data for the instruction? This variable
	 * tells us which of the `instfmt_*` formats to use in the
	 * `enum` below.
	 */
	enum instr_fmt fmt_type;
	/*
	 * The `format` field contains exactly one, and only one, of
	 * the structures within. You know which one is within
	 * `format` based on the `inst_no.
	 */
	union {
		struct instfmt_rrr rrr;
		struct instfmt_rri rri;
		struct instfmt_ri  ri;
		struct instfmt_ror ror;
		struct instfmt_ecall ecall;
	} format;
};

/*
 * The instructions, their addresses, and the size of memory.
 */
struct instructions {
	int num_instructions;
	/* a pointer to an array of instructions */
	struct instruction *instructions;
};

struct configuration;

/*
 * Take a program as input, and output an array of instructions. Note
 * that you cannot predict the number of instructions, so the array
 * must be dynamically allocated.
 *
 * - `@program_text` - the NULL-terminated string that is the
 *   meta-data and instructions of the program.
 * - `@cfg` - A structure to be populated with the addresses in the header for
 *   the program. This is effectively used as a return value.
 * - `@return` - the instructions structure on success, or `NULL` on error.
 */
struct instructions *instructions_parse(char *program_text, struct configuration *cfg);

/*
 * Free all the instructions that were created with the `parse_program`
 * function.
 */
void instructions_free(struct instructions *instructions);

/*
 * Utility functions defined and documented in instructions.c which
 * might be useful to you.
 */

char **lines(char *program, int *nlines);
void free_lines(char **lines);

/* Some conversion functions, should they be useful to you */
enum instr_fmt instr_format(enum instruction_num n);
enum instruction_num instr_num(char *instr);
char *instr_name(enum instruction_num n);
/* Print out a single instruction */
void instruction_print(struct instruction *i);
/* Print out all of the instructions */
char *stringify_program(struct instructions *prog);
