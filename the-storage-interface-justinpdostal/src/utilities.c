#include <processor.h>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
 * A helpful function that you can use to input the program, and
 * output an array of strings, one per line in the intput program.
 * This function will change the program string (adding \0s), and the
 * returned array will point to the resulting substrings in `prog`.
 * This means that if you don't want `prog` to be modified when you
 * call this function (or if you're passing in static strings that
 * cannot be modifed as they are read-only), you should call `strdup`
 * first, and pass in the duplicate.
 *
 * - `@prog` - The input program.
 * - `@nlines` - we return the number of lines found in this variable.
 * - `@return` - The array of strings, with each string being a line.
 *   The last entry in the array is always `NULL`, so you know that
 *   there are no more strings when you hit the `NULL`. An example: If
 *   you input "" as the `program`, then the return array will include
 *   a single pointer to `NULL`.
 */
char **
lines(char *program, int *nlines)
{
	int count = 0, offset = 0;
	char *last_newline, *str;
	/*
	 * Allocate a new string that will hold the lines. We're going
	 * to change the string, to turn it into multiple strings, so
	 * we want to duplicate the original program (allocating the
	 * new string that is a copy) so that we don't surprise the
	 * user of this function with updates to their original
	 * program.
	 */
	char *prog = strdup(program);
	char *pos = NULL;
	char **lines;

	/* Lets go through and count the number of newline characters */
	str = prog;
	while ((last_newline = strchr(str, '\n')) != NULL) {
		count++;
		str = last_newline + 1;
	}

	if (*str != '\0') {
		count++;
	}

	/* Allocate the array of pointers, one-per-line */
	lines = malloc((count + 1) * sizeof(char *));
	assert(lines);
	/* The last entry is NULL */
	lines[count] = NULL;
	if (nlines != NULL) *nlines = count;

	for (offset = 0; offset != count; offset++) {
		/* all but the first iteration, strtok_r wants NULL */
		char *p = offset == 0? prog: NULL;
		lines[offset] = strtok_r(p, "\n\0", &pos);
		assert(lines[offset]);
	}

	return lines;
}

/*
 * The helper function paired with `lines` that enables you to free
 * all of the lines that were allocated and returned by `lines`.
 */
void
free_lines(char **lines)
{
	/* Free the string of all of the lines */
	if (lines[0] != NULL) free(lines[0]);
	/* Then free the array pointing to each line */
	free(lines);
}

#include <stdio.h>

/*
 * We just want to store the collection of the instruction number,
 * string (operation), and format, so that we can look up any of these
 * from the other.
 */
struct instr_meta {
	enum instruction_num n;
	enum instr_fmt f;
	char *s;
};

/*
 * This table associates one of our instruction enums, with both its
 * format, and its actual string instruction representation. Below
 * this table are a few accessor functions for your convenience.
 */
#define IM(num, fmt, str) {.n = num, .f = fmt, .s = str}
const struct instr_meta imeta[INSTRCNT] = {
	IM(AUIPC, FMT_RI, "auipc"),
	IM(ADD, FMT_RRR, "add"),
	IM(ADDW, FMT_RRR, "addw"),
	IM(ADDI, FMT_RRI, "addi"),
	IM(ADDIW, FMT_RRI, "addiw"),
	IM(SUB, FMT_RRR, "sub"),
	IM(SUBW, FMT_RRR, "subw"),
	IM(SLL, FMT_RRR, "sll"),
	IM(SLLW, FMT_RRR, "sllw"),
	IM(SRL, FMT_RRR, "srl"),
	IM(SRLW, FMT_RRR, "srlw"),
	IM(SRA, FMT_RRR, "sra"),
	IM(SRAW, FMT_RRR, "sraw"),
	IM(SLLI, FMT_RRI, "slli"),
	IM(SLLIW, FMT_RRI, "slliw"),
	IM(SRLI, FMT_RRI, "srli"),
	IM(SRLIW, FMT_RRI, "srliw"),
	IM(SRAI, FMT_RRI, "srai"),
	IM(SRAIW, FMT_RRI, "sraiw"),
	IM(OR, FMT_RRR, "or"),
	IM(ORI, FMT_RRI, "ori"),
	IM(AND, FMT_RRR, "and"),
	IM(ANDI, FMT_RRI, "andi"),
	IM(XOR, FMT_RRR, "xor"),
	IM(XORI, FMT_RRI, "xori"),
	IM(LUI, FMT_RI, "lui"),
	IM(SB, FMT_ROR, "sb"),
	IM(SH, FMT_ROR, "sh"),
	IM(SW, FMT_ROR, "sw"),
	IM(SD, FMT_ROR, "sd"),
	IM(LB, FMT_ROR, "lb"),
	IM(LH, FMT_ROR, "lh"),
	IM(LW, FMT_ROR, "lw"),
	IM(LWU, FMT_ROR, "lwu"),
	IM(LD, FMT_ROR, "ld"),
	IM(LBU, FMT_ROR, "lbu"),
	IM(LHU, FMT_ROR, "lhu"),
	IM(SLT, FMT_RRR, "slt"),
	IM(SLTU, FMT_RRR, "sltu"),
	IM(SLTI, FMT_RRI, "slti"),
	IM(SLTIU, FMT_RRI, "sltiu"),
	IM(BEQ, FMT_RRI, "beq"),
	IM(BNE, FMT_RRI, "bne"),
	IM(BLT, FMT_RRI, "blt"),
	IM(BGE, FMT_RRI, "bge"),
	IM(BLTU, FMT_RRI, "bltu"),
	IM(BGEU, FMT_RRI, "bgeu"),
	IM(JAL, FMT_RI, "jal"),
	IM(JALR, FMT_ROR, "jalr"),
	IM(ECALL, FMT_ECALL, "ecall"),
};
#undef IM

/*
 * Return the format of a given instruction, use the lookup table
 * above.
 */
enum instr_fmt
instr_format(enum instruction_num n)
{
	int i;

	for (i = 0; i < INSTRCNT; i++) {
		if (imeta[i].n == n) return imeta[i].f;
	}

	return FMT_ERROR;
}

char *
instr_name(enum instruction_num n)
{
	int i;

	for (i = 0; i < INSTRCNT; i++) {
		if (imeta[i].n == n) return imeta[i].s;
	}

	return NULL;
}

/*
 * Another useful function to return the instruction number (or
 * `INSTRINVALID` on error) from the string of its instruction name.
 */
enum instruction_num
instr_num(char *instr)
{
	int i;

	for (i = 0; i < INSTRCNT; i++) {
		if (strcmp(instr, imeta[i].s) == 0) return imeta[i].n;
	}
	return INSTRINVALID;
}

void
instruction_print(struct instruction *i)
{
	char *name = instr_name(i->inst_no);

	switch (i->fmt_type) {
	case FMT_RRR: {
		struct instfmt_rrr *rrr = &i->format.rrr;
		printf("0x%lx\t%s x%d,x%d,x%d\n", i->inst_addr, name, rrr->rd, rrr->rs1, rrr->rs2);
		break;
	}
	case FMT_RRI: {
		struct instfmt_rri *rri = &i->format.rri;
		printf("0x%lx\t%s x%d,x%d,%ld\n", i->inst_addr, name, rri->rd, rri->rs1, rri->imm);
		break;
	}
	case FMT_ROR: {
		struct instfmt_ror *ror = &i->format.ror;
		printf("0x%lx\t%s x%d,%ld(x%d)\n", i->inst_addr, name, ror->r2, ror->offset, ror->r1);
		break;
	}
	case FMT_RI: {
		struct instfmt_ri *ri = &i->format.ri;
		printf("0x%lx\t%s x%d,%ld\n", i->inst_addr, name, ri->rd, ri->imm);
		break;
	}
	case FMT_ECALL: {
		printf("0x%lx\tecall\n", i->inst_addr);
		break;
	}
	case FMT_ERROR: {
		fprintf(stderr, "stringify: instructions include an error.\n");
		exit(-1);
		break;
	}}
}

/*
 * Another utility function that might help debug. `stringify_program`
 * takes the instructions returned from `parse_program` (and the
 * number of instructions in `ninstr`, and converts the instructions
 * into a string for the program. It is the inverse function of
 * `parse_program`!
 */
char *
stringify_program(struct instructions *p)
{
	/*
	 * Maximum instruction size (in bytes) as a string:
	 *
	 * 5 (= max isntrlen) +
	 * 3 spaces +
	 * 2 commas +
	 * 6 (= 2 reg at 3 char each) +
	 * 9 (= 32 bit immediate) +
	 * 1 \n
	 */
	const int max_instr_str_sz = 5 + 3 + 2 + 6 + 9 + 1;
	/* The output string */
	char *o = malloc(p->num_instructions * max_instr_str_sz);
	int off = 0, i;
	struct instruction *is = p->instructions;

	assert(o);
	for (i = 0; i < p->num_instructions; i++) {
		char *name = instr_name(is[i].inst_no);
		switch (is[i].fmt_type) {
		case FMT_RRR: {
			struct instfmt_rrr *rrr = &is[i].format.rrr;
			off += sprintf(o + off, "%s x%d,x%d,x%d\n", name, rrr->rd, rrr->rs1, rrr->rs2);
			break;
		}
		case FMT_RRI: {
			struct instfmt_rri *rri = &is[i].format.rri;
			off += sprintf(o + off, "%s x%d,x%d,%ld\n", name, rri->rd, rri->rs1, rri->imm);
			break;
		}
		case FMT_ROR: {
			struct instfmt_ror *ror = &is[i].format.ror;
			off += sprintf(o + off, "%s x%d,%ld(x%d)\n", name, ror->r2, ror->offset, ror->r1);
			break;
		}
		case FMT_RI: {
			struct instfmt_ri *ri = &is[i].format.ri;
			off += sprintf(o + off, "%s x%d,%ld\n", name, ri->rd, ri->imm);
			break;
		}
		case FMT_ECALL: {
			off += sprintf(o + off, "ecall\n");
			break;
		}
		case FMT_ERROR: {
			fprintf(stderr, "stringify: instructions include an error.\n");
			exit(-1);
			break;
		}}
	}
	o[off - 1] = '\0'; 	/* get rid of the last newline */

	return o;
}

void
processor_registers_print(struct processor *p)
{
	/*
	 * This will store the registers from the previous time this
	 * was called. Recall that `static` variables in a function
	 * are effectively global (thus persist across calls to this
	 * function), without being accessible from other functions.
	 */
	static unsigned long prev_rs[32] = { 0 };
	int i;

	printf("pc: 0x%x, ", registers_getpc(p->rs));
	for (i = 0; i < 32; i++) {
		unsigned long r = registers_getreg(p->rs, i);

		if (r != prev_rs[i]) {
			printf("modified x%u: 0x%lx\n", i, registers_getreg(p->rs, i));
			prev_rs[i] = r;

			return;
		}
	}
	printf("no registers modified.\n");
}

void
processor_registers_printall(struct processor *p)
{
	unsigned int i;

	printf("pc: 0x%x, ", registers_getpc(p->rs));
	for (i = 0; i < 32; i++) {
		printf("x%u: 0x%lx", i, registers_getreg(p->rs, i));
		if (i != 31) printf(", ");
	}
	printf("\n");
}

void
processor_print_exception(struct processor *p, enum exception e)
{
	char *exception_name[] = {
		"Instruction exception",
		"Memory access exception",
		"Process exit",
		"Unknown syscall exception",
	};

	assert(e <= EXCEPTION_UNKNOWN_SYSCALL);
	printf("%s, register state:\n", exception_name[e]);
	processor_registers_printall(p);

	return;
}

void processor_memory_print(struct processor *p)
{
	unsigned long addr, sz, empty;
	
	sz = memory_getsize(p->mem);
	empty = 0;
	printf("Memory: ");
	for (addr = 0; addr < sz; addr++) {
		unsigned char byte = memory_getbyte(p->mem, addr);
		if (byte == 0)
			continue;
		printf("%x ", byte);
		empty = 1;
	}
	if (!empty) printf("No memops performed so far.");
	printf("\n");
}
