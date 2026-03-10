/*
 * Copyright (c) Gabriel Parmer, 2024.
 * Do not distribute without permission.
 */

 #include <processor.h>
 #include <instructions.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
//TESSSST TESSSST
 
 struct instructions *
 instructions_parse(char *prog, struct configuration *cfg)
 {
     // Setup for output
     struct instructions* ret = (struct instructions*)malloc(sizeof(struct instructions)*1000);
     // Pointer for line count
     int set = 0;
     int* instct = &set;
     // Retrieve lines
     char** bars = lines(prog, instct);
     ret->num_instructions = *instct-1;
     // Mallocate instructions array
     ret->instructions = (struct instruction *)malloc(sizeof(struct instruction)*ret->num_instructions*1000);
 
     // Header setup
     char header[4][10];
     // Scan for headers
     sscanf(bars[0],"%s %s %s %s",header[0],header[1],header[2],header[3]);
     // Convert headers from hex using 'strtoul'
     cfg->instr_lower = strtoul(header[0], NULL, 16);
     cfg->instr_upper = strtoul(header[1], NULL, 16);
     cfg->entry_address = strtoul(header[2], NULL, 16);
     cfg->memory_sz = strtoul(header[3], NULL, 16);
     // Setup vars for instruction check
     char inst[20];
     int x1;
     int x2;
     int x3;
     // For each instruction line
     for(int i = 0; i < *instct-1; i++){
         // Wipe instruction field
         for(int j = 0; j < 20; j++) {
             inst[j] = 0;
         }
         // Scan instruction name
         sscanf(bars[i+1], "%s", inst);
         // Set number and format type
         ret->instructions[i].inst_no = instr_num(inst);
         ret->instructions[i].fmt_type = instr_format(ret->instructions[i].inst_no);
         // If rrr format
         if(ret->instructions[i].fmt_type==FMT_RRR) {
             // Scan vars
             sscanf(bars[i+1], "%s x%d,x%d,x%d", inst, &x1, &x2, &x3);
             // Set format vars
             ret->instructions[i].format.rrr.rd = x1;
             ret->instructions[i].format.rrr.rs1 = x2;
             ret->instructions[i].format.rrr.rs2 = x3;
         }
         // If rri format
         else if(ret->instructions[i].fmt_type==FMT_RRI) {
             // Scan vars
             sscanf(bars[i+1], "%s x%d,x%d,%d", inst, &x1, &x2, &x3);
             // Set format vars
             ret->instructions[i].format.rri.rd = x1;
             ret->instructions[i].format.rri.rs1 = x2;
             ret->instructions[i].format.rri.imm = x3;
         }
         // If ri format
         else if(ret->instructions[i].fmt_type==FMT_RI) {
             // Scan vars
             sscanf(bars[i+1], "%s x%d,%d", inst, &x1, &x2);
             // Set format vars
             ret->instructions[i].format.ri.rd = x1;
             ret->instructions[i].format.ri.imm = x2;
         }
         // If ror format
         else if(ret->instructions[i].fmt_type==FMT_ROR) {
             // Scan vars
             sscanf(bars[i+1], "%s x%d,%d(x%d)", inst, &x1, &x2, &x3);
             // Set format vars
             ret->instructions[i].format.ror.r1 = x3;
             ret->instructions[i].format.ror.offset = x2;
             ret->instructions[i].format.ror.r2 = x1;
         }
         // ecall format (no vars)
         else if(ret->instructions[i].fmt_type==FMT_ECALL) {
             // Vacuous instruciton type set
             ret->instructions[i].inst_addr = 17;
         }
     }
 
     // Testing
 
     // printf("%s\n",stringify_program(ret));
     // cfg->instr_lower
     // printf("ermmmmm... Smello?\n");
     // fflush(stdout);
     /* TODO: Parse the given program, create and populate a struct of instructions with the appropriate instructions types
      * and associated data. In addition, populate the configuration with the relevant information from the header of the program.
      */
     // printf("%s\n",stringify_program(ret));
     // fflush(stdout);
 
     // Return
     return ret;
 }
 
 void instructions_free(struct instructions *instrs)
 {
     if (instrs->instructions)
         free(instrs->instructions);
     free(instrs);
 }