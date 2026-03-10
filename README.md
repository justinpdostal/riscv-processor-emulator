# RISC-V Processor Emulator

**Author:** Justin Dostal  
**Technologies:** C · GCC · Make · Bash

---

## Overview

A fully functional RISC-V (RV64I) processor emulator built from scratch in C across three incremental phases. The emulator parses real RISC-V assembly programs, executes them instruction by instruction, and simulates the full processor pipeline including a register file, program counter, and byte-addressable memory subsystem.

---

## Project Structure

    riscv-processor-emulator/
    │
    ├── instruction-parsing-justinpdostal/    # Phase 1 — Instruction parser
    ├── registers-machine-justinpdostal/      # Phase 2 — Register file & execution engine
    └── the-storage-interface-justinpdostal/  # Phase 3 — Memory subsystem & load/store

---

## Phase 1 — Instruction Parsing

Parses a custom binary program format (`archobj`) from stdin into structured C data.

- Extracts a program header containing instruction bounds, entry point address, and total memory size into a `configuration` struct
- Dynamically allocates an array of `instruction` structs, one per line of assembly
- Handles five instruction formats using `sscanf` pattern matching:
  - **RRR** — three register operands (e.g. `add x1,x2,x3`)
  - **RRI** — two registers and an immediate (e.g. `addi x1,x2,10`)
  - **RI** — one register and an immediate (e.g. `lui x10,1`)
  - **ROR** — register, offset, and base register (e.g. `ld x11,0(x11)`)
  - **ECALL** — zero-argument system call
- Validates correctness by round-tripping parsed instructions through a stringify function and comparing against the original input

---

## Phase 2 — Register File & Execution Engine

Brings parsed instructions to life with a full processor execution loop.

- Implements a 32-register file with a 64-bit program counter
- Enforces RISC-V hardware constraint that register `x0` is hardwired to zero
- Main execution loop reads the PC, bounds-checks it, indexes into the instruction array, dispatches to emulation functions, and advances PC by 4 bytes per instruction
- Emulates 20+ instructions including:
  - Integer arithmetic: `ADD`, `ADDI`, `SUB`, `ADDW`, `SUBW`
  - Bitwise logic: `OR`, `ORI`, `AND`, `ANDI`, `XOR`, `XORI`
  - Shifts: `SLL`, `SLLI`, `SRL`, `SRLI`, `SRA`, `SRAI`
  - Upper immediate: `LUI`
  - System calls via `ECALL`: exit (syscall 2) and print register state (syscall 23)
- Full exception handling for out-of-bounds instructions, unknown syscalls, and process exit

---

## Phase 3 — Memory Subsystem & Load/Store

Adds a byte-addressable memory subsystem and emulates all RISC-V load/store instructions.

- Implements `memory_alloc` as a flat dynamic byte array representing the full addressable data space
- Emulates all 11 RISC-V load/store instructions across four access widths:
  - **Stores:** `SB`, `SH`, `SW`, `SD`
  - **Signed loads:** `LB`, `LH`, `LW`, `LD` — with C sign extension via typed pointer casts
  - **Unsigned loads:** `LBU`, `LHU`, `LWU` — zero-extended using unsigned types
- Address calculation: `base_register + offset` for every access
- Bounds checking on every memory operation — out-of-range addresses raise `EXCEPTION_MEMORY`
- Handles edge cases: negative offsets, large offsets, memory aliasing, and sequential interleaved loads/stores

---

## Building & Running

Each phase has its own Makefile. To build and run any phase:

    cd instruction-parsing-justinpdostal
    make
    ./r5emu < tests/01_header_test.archobj

To run all tests:

    ./run_tests.sh

---

## Key Concepts Demonstrated

- Instruction Set Architecture (ISA) design and encoding
- Processor pipeline: fetch, decode, execute
- Register file design and program counter management
- Byte-addressable memory and memory hierarchy
- Sign extension and integer width handling in C
- Dynamic memory management — `malloc`, `free`, manual ownership
- Pointer arithmetic and typed memory access
- Exception and fault handling in emulated hardware
- Parsing techniques in C — `sscanf`, `strtok`, `strtoul`
- Systems programming — fixed APIs, modular compilation, Makefile builds
