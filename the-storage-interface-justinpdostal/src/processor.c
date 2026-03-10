/*
 * Copyright (c) Gabriel Parmer, 2024.
 * Do not distribute without permission.
 */

#include <processor.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void
processor_emulate(struct processor *p)
{
	unsigned long pc, offset;
	struct instruction *i;
	enum exception e;

	processor_registers_printall(p);
	while (1) {
		pc = registers_getpc(p->rs);
		if (p->cfg.instr_lower > pc || p->cfg.instr_upper <= pc) {
			processor_print_exception(p, EXCEPTION_INSTRUCTION);
		}
		offset = (pc - p->cfg.instr_lower) / 4; /* each instruction is 4 bytes */
		i = &p->instrs->instructions[offset];

		if (p->cfg.print_instrs) instruction_print(i);

		if (processor_emulate_regops(p, i, &e) < 0 ||
		    processor_emulate_memops(p, i, &e) < 0) {
			processor_print_exception(p, e);
			return;
		}
		processor_memory_print(p);
		if (p->cfg.print_regs)   processor_registers_print(p);
		printf("-------------------------------------------------------------------------------------------------------------------\n");
	}
}

struct processor *
processor_alloc(struct configuration *cfg, struct instructions *instrs, struct registers *rs, struct memory *mem)
{
	struct processor *p = malloc(sizeof(struct processor));
	assert(p);
	*p = (struct processor) {
		.cfg = *cfg,
		.instrs = instrs,
		.rs = rs,
		.mem = mem,
	};

	return p;
}

void
processor_free(struct processor *p)
{
	if (p->rs)     registers_free(p->rs);
	if (p->mem)    memory_free(p->mem);
	if (p->instrs) instructions_free(p->instrs);
	free(p);
}
