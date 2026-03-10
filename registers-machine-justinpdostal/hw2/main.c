/*
 * Copyright (c) Gabriel Parmer, 2024.
 * Do not distribute without permission.
 */

#include <processor.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static void
err(char *msg) {
	printf("%s", msg);
	exit(-1);
}

static char *
find_instructions(char *prog)
{
	char *s = strstr(prog, "\n");
	assert(s);

	return s + 1;
}

#define PROG_SZ_MAX (1024 * 16)

int
main(int argc, char *argv[])
{
	char program[PROG_SZ_MAX];
	int ret, read_amnt = 0;
	struct instructions *instrs;
	struct processor *p;
	struct configuration cfg;
	int i;

	/* Default configuration values */
	cfg = (struct configuration) {
		.print_instrs = 1,
		.print_regs   = 1,
		.cache_tot_cachelines = 1,
		.cache_sets = 1
	};

	/* Parse the command-line arguments */
        for (i = 1; i < argc; i++) {
		unsigned long cache_num_lines, cache_sets;

		if (strcmp(argv[i], "--no-print-instr") == 0) cfg.print_instrs = 0;
		if (strcmp(argv[i], "--no-print-regs") == 0)  cfg.print_regs   = 0;
		if (sscanf(argv[i], "--cache-values=%ld,%ld", &cache_num_lines, &cache_sets) == 2) {
			cfg.cache_sets = cache_sets;
			cfg.cache_tot_cachelines = cache_num_lines;
		}
	}

	/* Read in the program */
	while ((ret = read(STDIN_FILENO, program + read_amnt, PROG_SZ_MAX - read_amnt)) != 0) {
		if (ret < 0) err("Cannot read program from stdin.\n");
		read_amnt += ret;
	}

	/* Parse the instructions */
	instrs = instructions_parse(program, &cfg);
	if (!instrs) err("Cannot parse program.\n");
	/* Validate that we parsed it correctly (not expected of students) */
	if (strcmp(find_instructions(program), stringify_program(instrs)) != 0) {
		char **p, **s;
		int p_lines, s_lines, i;

		p = lines(find_instructions(program), &p_lines);
		s = lines(stringify_program(instrs), &s_lines);
		assert(p_lines == s_lines);
		fprintf(stderr, "Instruction parse failed. Differences:\n");
		for (i = 0; i < s_lines; i++) {
			if (strcmp(p[i], s[i]) != 0) {
				fprintf(stderr, "line %d, input program:\n%s\nprocessed instructions:\n%s\n",
					i, p[i], s[i]);
			}
		}
		exit(-1);
	}

	/* Allocate a processor with the configuration and instructions */
	p = processor_alloc(&cfg, instrs, registers_alloc(cfg.entry_address));
	/* Emulate the processor and execute the program! */
	processor_emulate(p);

	return 0;
}
