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
err(char *msg)
{
	printf("%s", msg);
	exit(-1);
}

static char * find_header(const char *prog) 
{
   	char * line = strchr(prog, '\n'); // Find first newline
	assert(line);
	int length = line - prog;

	char * header = malloc(length + 1);
	assert(header);
	strncpy(header, prog, length);
	header[length] = '\0';
	return header;
}

static char *
find_instructions(char *prog)
{
	char *s = strstr(prog, "\n");
	assert(s);

	return s + 1;
}

#define PROG_SZ_MAX (1024 * 16)

int main()
{
	char program[PROG_SZ_MAX];
	int ret, read_amnt = 0;
	struct instructions *instrs;
	// struct processor *p;
	struct configuration cfg;
	// int i;

	/* Default configuration values */
	cfg = (struct configuration){
		.print_instrs = 1,
		.print_regs = 1,
		.cache_tot_cachelines = 1,
		.cache_sets = 1};

	/* Read in the program from the standard input */
	while ((ret = read(STDIN_FILENO, program + read_amnt, PROG_SZ_MAX - read_amnt)) != 0)
	{
		if (ret < 0)
			err("Cannot read program from stdin.\n");
		read_amnt += ret;
	}

	/* Parse the instructions, and return some configuration information about the program! */
	instrs = instructions_parse(program, &cfg);
	if (!instrs)
		err("Cannot parse program.\n");

	/* Validate that the configurations are parsed correctly */
	char * header = find_header(program);
	char * tokens[4];
	long unsigned values[16];
	int i;
	tokens[0] = strtok(header, " ");
	tokens[1] = strtok(NULL, " ");
	tokens[2] = strtok(NULL, " ");
	tokens[3] = strtok(NULL, " ");

	// Convert hex string tokens to integers
    for (i = 0; i < 4; i++) {
        values[i] = strtoul(tokens[i], NULL, 16); 
    }

	if(values[0] != cfg.instr_lower || values[1] != cfg.instr_upper || values[2] != cfg.entry_address || values[3] != cfg.memory_sz)
		err("Header parsing failed.\n");


	/*
	 * Validate that we parsed it correctly (not expected of
	 * students). Note that the `stringify_program` function is
	 * provided for you in the `utiliites.c` file
	 */
	if (strcmp(find_instructions(program), stringify_program(instrs)) != 0)
	{
		char **p, **s;
		int p_lines, s_lines, i;

		/*
		 * If we got here, the program is not the same as the
		 * parsed representation, so there's an error in
		 * parsing! What follows is just some code to output a
		 * useful error.
		 */

		/*
		 * `lines` is in `utilities.c`, and breaks the output
		 * into different strings, one per line.
		 */
		p = lines(find_instructions(program), &p_lines);
		s = lines(stringify_program(instrs), &s_lines);
		assert(p_lines == s_lines);
		fprintf(stderr, "Instruction parse failed. Differences:\n");
		/* Lets output the differences in the program, and what we parsed */
		for (i = 0; i < s_lines; i++)
		{
			if (strcmp(p[i], s[i]) != 0)
			{
				fprintf(stderr, "line %d, input program:\n%s\nprocessed instructions:\n%s\n",
						i, p[i], s[i]);
			}
		}
		exit(-1);
	}

	fprintf(stdout, "PASSED\n");
	/* More to come later, once we have our instructions!!! */

	return 0;
}
