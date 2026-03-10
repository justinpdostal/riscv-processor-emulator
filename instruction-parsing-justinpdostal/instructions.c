#include <processor.h>
#include <instructions.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#define MAX_TOKENS 4
//CHECK IF THIS UPDATED
//Taken From Main.c
static char *find_header(const char *prog) {
    char * line = strchr(prog, '\n'); 
	assert(line);
	int length = line - prog;
	char * header = malloc(length + 1);
	assert(header);
	strncpy(header, prog, length);
	header[length] = '\0';
	return header;
}

/* Get the instruction section */
static char *find_instructions(char *prog) {
   char *s = strstr(prog, "\n");
   assert(s);
   return s + 1;
}

/* Parse the instruction set */
struct instructions *instructions_parse(char *prog, struct configuration *cfg) {
    //Null check
    if (!prog || !cfg) return NULL;

    //Create memory
    struct instructions *instrs = malloc(sizeof(struct instructions));
    if (!instrs) return NULL;
    instrs->num_instructions = 0;
    instrs->instructions = NULL;

    //printf("PARSE START.\n");

    // Parse header
    char *header = find_header(prog);
    //printf("HEADER FOUND: %s\n", header);

    char *tokens[MAX_TOKENS];
    tokens[0] = strtok(header, " ");
    for (int i = 1; i < MAX_TOKENS; i++) {tokens[i] = strtok(NULL, " ");}

    cfg->instr_lower = strtoul(tokens[0], NULL, 16);
    cfg->instr_upper = strtoul(tokens[1], NULL, 16);
    cfg->entry_address = strtoul(tokens[2], NULL, 16);
    cfg->memory_sz = strtoul(tokens[3], NULL, 16);


    free(header);

    // Get instruction lines
    char *instr_text = find_instructions(prog);

    //printf("INSTRUCT FOUND.\n");
    int num_lines = 0;
    char **lines_arr = lines(instr_text, &num_lines);
    if (!lines_arr) {
        //printf("WHYYYYYYYYYYYYYY.\n");
        free(instrs);
        return NULL;
    }
    instrs->num_instructions = num_lines;

    //printf("NUMLINESCHECK: %d\n", num_lines);

    instrs->instructions = calloc(num_lines, sizeof(struct instruction));

    // Parse each instruction
    for (int i = 0; i < num_lines; i++) {
        struct instruction *inst = &instrs->instructions[i];
        char *line = lines_arr[i];
        char instr_str[16];
        int rd, rs1, rs2, imm;
        if (sscanf(line, "%s x%d, x%d, x%d", instr_str, &rd, &rs1, &rs2) == 4) {
            // RRR format (add x1, x2, x3)
            inst->inst_no = instr_num(instr_str);
            inst->inst_addr = cfg->instr_lower + (i * 4);
            inst->fmt_type = FMT_RRR;
            inst->format.rrr.rd = rd;
            inst->format.rrr.rs1 = rs1;
            inst->format.rrr.rs2 = rs2;
        } 
        else if (sscanf(line, "%s x%d, x%d, %d", instr_str, &rd, &rs1, &imm) == 4) {
            // RRI format (addi x1, x2, 10)
            inst->inst_no = instr_num(instr_str);
            inst->inst_addr = cfg->instr_lower + (i * 4);
            inst->fmt_type = FMT_RRI;
            inst->format.rri.rd = rd;
            inst->format.rri.rs1 = rs1;
            inst->format.rri.imm = imm;
        } 
        else if (sscanf(line, "%s x%d,%d(x%d)", instr_str, &rd, &imm, &rs1) == 4) {
                // ROR format ( ld x11, 0(x11) or sd x12, 5(x12))
                inst->inst_no = instr_num(instr_str);
                inst->inst_addr = cfg->instr_lower + (i * 4);
                inst->fmt_type = FMT_ROR;
                inst->format.ror.r2 = rd;     // Destination register (x11, x12)
                inst->format.ror.r1 = rs1;    // Base register (x11, x12)
                inst->format.ror.offset = imm; // Offset value (0, 5)
        }
        else if (sscanf(line, "%s x%d,%d", instr_str, &rd, &imm) == 3) {
            printf("HEEEERE\n");
            // RI format (lui x10, 1)
            inst->inst_no = instr_num(instr_str);
            inst->inst_addr = cfg->instr_lower + (i * 4);
            inst->fmt_type = FMT_RI;
            inst->format.ri.rd = rd;
            inst->format.ri.imm = imm; 
        }
        else if (strcmp(line, "ecall") == 0) {
            // ECALL instruction
            inst->inst_no = instr_num("ecall");
            inst->inst_addr = cfg->instr_lower + (i * 4);
            inst->fmt_type = FMT_ECALL;
        }
        
    }
    free_lines(lines_arr);
    printf("FINISHED.\n");
    return instrs;

}
    



