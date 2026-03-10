#include "memory.h"
#include "processor.h"
#include "registers.h"
#include "instructions.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h" 

// Memory 
struct memory {
    unsigned char *buffer;  
    unsigned long size;     
};

// Allocate memory structure 
struct memory *memory_alloc(unsigned long memory_sz) {
    struct memory *m = malloc(sizeof(struct memory));
    if (!m) return NULL;

    m->buffer = malloc(memory_sz);
    if (!m->buffer) {
        free(m);
        return NULL;
    }

    memset(m->buffer, 0, memory_sz); 
    m->size = memory_sz;
    return m;
}

// Free allocated memory
void memory_free(struct memory *m) {
    if (m) {
        free(m->buffer);
        free(m);
    }
}

// Get memory size
unsigned long memory_getsize(struct memory *m) {
    return m ? m->size : 0;
}

// Read a byte from memory
char memory_getbyte(struct memory *m, unsigned long addr) {
    if (!m || addr >= m->size) return 0;
    return (char)m->buffer[addr];
}

// Write a byte to memory
void memory_setbyte(struct memory *m, unsigned long addr, char value) {
    if (m && addr < m->size) {
        m->buffer[addr] = (unsigned char)value;
    }
}

int processor_emulate_memops(struct processor *processor, 
    struct instruction *i,
    enum exception *e) {
    
    *e = EXCEPTION_INSTRUCTION;
    if (!processor || !i || !e) return -1;
    if (i->fmt_type != FMT_ROR) return 1;

    const unsigned r1 = i->format.ror.r1;
    const unsigned r2 = i->format.ror.r2;
    const int offset = i->format.ror.offset;
    const bool skip_write = (r2 == 0);

    // No x0 bas register
    if (r1 == 0) {
        *e = EXCEPTION_MEMORY;
        return -1;
    }

    int size;
    bool store = false, load = false, sign_ext = false;

    // Determin op and size
    switch (i->inst_no) {
        case SB:  size = 1; store = true; break;
        case SH:  size = 2; store = true; break;
        case SW:  size = 4; store = true; break;
        case SD:  size = 8; store = true; break;
        case LB:  size = 1; load = true; sign_ext = true; break;
        case LBU: size = 1; load = true; break;
        case LH:  size = 2; load = true; sign_ext = true; break;
        case LHU: size = 2; load = true; break;
        case LW:  size = 4; load = true; sign_ext = true; break;
        case LWU: size = 4; load = true; break;
        case LD:  size = 8; load = true; break;
        default: return 1;  
    }

    // Get base address from register
    const u64_t base = registers_getreg(processor->rs, r1);

    // Extract and sign-extend 12-bit offset
    const s64_t signed_offset = (offset & 0x800) 
        ? (s64_t)(offset | 0xFFFFFFFFFFFFF000ULL) 
        : (s64_t)(offset & 0xFFF);

    // Compute target memory address
    const u64_t address = base + signed_offset;

    // Check for memory access violation
    if (address + size - 1 >= processor->mem->size) {
        *e = EXCEPTION_MEMORY;
        return -1;
    }

    if (store) {
        // Store value in memory
        const u64_t value = registers_getreg(processor->rs, r2);
        for (int i = 0; i < size; i++) {
            const u8_t byte = (value >> (i * 8)) & 0xFF;
            memory_setbyte(processor->mem, address + i, byte);
        }
    } 
    else if (load) {
        // Load value from memory
        u64_t value = 0;
        for (int i = 0; i < size; i++) {
            const u8_t byte = memory_getbyte(processor->mem, address + i);
            value |= (u64_t)byte << (i * 8);
        }

        // Sign-extend if needed
        if (sign_ext) {
            switch (size) {
                case 1: value = (u64_t)(s64_t)(s8_t)value; break;
                case 2: value = (u64_t)(s64_t)(s16_t)value; break;
                case 4: value = (u64_t)(s64_t)(s32_t)value; break;
            }
        }

        // Store if valid
        if (!skip_write) {
            registers_setreg(processor->rs, r2, value);
        }
    }

    // PC update
    registers_setpc(processor->rs, registers_getpc(processor->rs) + 4);
    return 0;
}
