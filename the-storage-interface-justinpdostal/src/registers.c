#include <processor.h>
#include <registers.h>
#include <stdlib.h>
#include <stdio.h>

struct registers {
    unsigned long pc; // Program counter
    unsigned long x[32]; // General-purpose registers
};

// Allocate memory for registers and initialize
struct registers *registers_alloc(unsigned long init_pc_value) {
    struct registers *regs = malloc(sizeof(struct registers));
    if (!regs) return NULL;
    
    regs->pc = init_pc_value;
    for (int i = 0; i < 32; i++) regs->x[i] = 0;
    
    return regs;
}

// Free allocated memory for registers
void registers_free(struct registers *regs) {
    free(regs);
}

// Get the value of a specific register
unsigned long registers_getreg(struct registers *state, unsigned int regno) {
    return (state && regno < 32) ? state->x[regno] : 0;
}

// Set the value of a specific register (excluding register 0)
void registers_setreg(struct registers *state, unsigned int regno, unsigned long value) {
    if (state && regno > 0 && regno < 32) state->x[regno] = value;
}

// Get the current program counter value
unsigned int registers_getpc(struct registers *state) {
    return state ? state->pc : 0;
}

// Set the program counter to a new value
void registers_setpc(struct registers *state, unsigned long value) {
    if (state) state->pc = value;
}

// Helper function to get a register value from a processor structure
static long get_register_value(struct processor *processor, unsigned int regno) {
    return registers_getreg(processor->rs, regno);
}

// Helper function to set a register value in a processor structure
static void set_register_value(struct processor *processor, unsigned int regno, long value) {
    registers_setreg(processor->rs, regno, value);
}

// Emulate register operations for a given instruction
int processor_emulate_regops(struct processor *processor, struct instruction *inst, enum exception *e) {
    //Null Checks
    if (!processor || !inst || !e) return -1;
    
    //Declaring registers/immediates and final destination
    unsigned int rs1 = 0, rs2 = 0, rd = 0;
    long imm = 0, result = 0;

    // Decode instruction format
    switch (inst->fmt_type) {
        case FMT_RRR:
            rs1 = inst->format.rrr.rs1;
            rs2 = inst->format.rrr.rs2;
            rd = inst->format.rrr.rd;
            break;
        case FMT_RRI:
            rs1 = inst->format.rri.rs1;
            imm = inst->format.rri.imm;
            rd = inst->format.rri.rd;
            break;
        case FMT_RI:
            imm = inst->format.ri.imm;
            rd = inst->format.ri.rd;
            break;
        case FMT_ROR:
            rs1 = inst->format.ror.r1;
            imm = inst->format.ror.offset;
            rd = inst->format.ror.r2;
            break;
        case FMT_ECALL:
            // Handle system call exceptions
            switch (get_register_value(processor, 17)) {
                case 2:
                    *e = EXCEPTION_EXIT;
                    break;
                case 23:
                    registers_setpc(processor->rs, registers_getpc(processor->rs) + 4);
                    return 0;
                default:
                    *e = EXCEPTION_UNKNOWN_SYSCALL;
                    return -1;
            }
            break;
        case FMT_ERROR:
            *e = EXCEPTION_INSTRUCTION;
            return -1;
    }
    
    // Execute the instruction based on its operation code
    switch (inst->inst_no) {
        case LUI:   
            result = imm << 12; break;
        case ADD:   
            result = get_register_value(processor, rs1) + get_register_value(processor, rs2); break;
        case ADDI:  
            result = get_register_value(processor, rs1) + imm; break;
        case SUB:   
            result = get_register_value(processor, rs1) - get_register_value(processor, rs2); break;
        case OR:    
            result = get_register_value(processor, rs1) | get_register_value(processor, rs2); break;
        case ORI:   
            result = get_register_value(processor, rs1) | imm; break;
        case AND:   
            result = get_register_value(processor, rs1) & get_register_value(processor, rs2); break;
        case ANDI:      
            result = get_register_value(processor, rs1) & imm; break;
        case XOR:   
            result = get_register_value(processor, rs1) ^ get_register_value(processor, rs2); break;
        case XORI:  
            result = get_register_value(processor, rs1) ^ imm; break;
        case SLL:   
            result = get_register_value(processor, rs1) << get_register_value(processor, rs2); break;
        case SLLI:  
            result = get_register_value(processor, rs1) << imm; break;
        case SRL:   
            result = get_register_value(processor, rs1) >> get_register_value(processor, rs2); break;
        case SRLI:  
            result = get_register_value(processor, rs1) >> imm; break;
        case SRA:   
            result = (long)get_register_value(processor, rs1) >> get_register_value(processor, rs2); break;
        case SRAI:  
            result = (long)get_register_value(processor, rs1) >> imm; break;
        default:
            *e = EXCEPTION_INSTRUCTION;
            return -1;
    }
    
    // Update program counter and set destination register
    registers_setpc(processor->rs, registers_getpc(processor->rs) + 4);
    if (inst->inst_no != ECALL) set_register_value(processor, rd, result);
    
    return 0;
}