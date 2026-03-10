# C source files: must have a `main`, should *not* include anything
# (no dependencies)
# Assembly source files: must have a _start function, no dependencies

TEST_DIR = ../tests
ARCHOBJS_DIR   = $(TEST_DIR)/archobjs
ASM_DIR        = $(TEST_DIR)/asm
ASMRAW_DIR     = $(TEST_DIR)/asmraw
ASSEMBLY_DIR   = $(TEST_DIR)/assembly
BINARIES_DIR   = $(TEST_DIR)/binaries
EXAMPLES_DIR   = $(TEST_DIR)/examples
SOLN_DIR       = $(TEST_DIR)/solutions

SRC_DIR = ../src
SOLN  =  $(SRC_DIR)/r5emu

CC = riscv64-unknown-elf-gcc
CFLAGS = -march=rv64i -mabi=lp64 -mcmodel=medlow -fno-pic -fno-PIC -fno-pie -fno-plt -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -static -fno-jump-tables -Wl,--gc-sections -Wl,-T,riscv64-virt.ld
OBJDUMP = riscv64-unknown-elf-objdump
OFLAGS = -Mnumeric --disassembler-options=no-aliases

# Ensure required directories exist
$(shell mkdir -p $(BINARIES_DIR) $(ASM_DIR) $(ASMRAW_DIR) $(ARCHOBJS_DIR) $(SOLN_DIR))

# Assembly source files
SFILES = $(sort $(wildcard $(ASSEMBLY_DIR)/*.S))
# Binary output files
BFILES = $(patsubst $(ASSEMBLY_DIR)/%.S,$(BINARIES_DIR)/%.bin,$(SFILES))
# Assembly output files
AFILES = $(patsubst $(BINARIES_DIR)/%.bin,$(ASM_DIR)/%.asm,$(BFILES))
# Raw, more readable assembly files 
RFILES = $(patsubst $(BINARIES_DIR)/%.bin,$(ASMRAW_DIR)/%.rawasm,$(BFILES))
# The final gwu architecture object format
AOBJS =  $(patsubst $(BINARIES_DIR)/%.bin,$(ARCHOBJS_DIR)/%.archobj,$(BFILES))
# Solution files
SOLNS =  $(patsubst $(BINARIES_DIR)/%.bin,$(SOLN_DIR)/%.soln,$(BFILES))

all: solution $(AOBJS) $(AFILES) $(RFILES) $(BFILES) $(SOLNS)

solution:
	make --no-print-directory -C $(SRC_DIR)

$(BINARIES_DIR)/%.bin: $(ASSEMBLY_DIR)/%.S
	@if ! timeout 2 $(CC) $(CFLAGS) -g $< -o $@; then \
		echo "Warning: $(CC) for $< timed out." >&2; \
		touch $@; \
	fi

$(BINARIES_DIR)/%.bin: %.c _crt0.s
	@if ! timeout 2 $(CC) $(CFLAGS) -g $^ -o $@; then \
		echo "Warning: $(CC) for $< timed out." >&2; \
		touch $@; \
	fi

$(ARCHOBJS_DIR)/%.archobj: $(BINARIES_DIR)/%.bin
	@if ! timeout 2 python3 obj_create.py $< > $@; then \
		echo "Warning: obj_create.py for $< timed out." >&2; \
		touch $@; \
	fi

$(ASM_DIR)/%.asm: $(BINARIES_DIR)/%.bin
	@if ! timeout 2 $(OBJDUMP) $(OFLAGS) -d $< | tail -n +6 | sed "s/<.*>//g" | \
	awk -F' ' '{ if (NF == 3) { print $$1 "\t" $$3; } else if (NF == 4 || NF == 5) { print $$1 "\t" $$3 " " $$4; } }' > $@; then \
		echo "Warning: $(OBJDUMP) for $< timed out." >&2; \
		touch $@; \
	fi

$(ASMRAW_DIR)/%.rawasm: $(BINARIES_DIR)/%.bin
	@if ! timeout 2 $(OBJDUMP) --disassembler-options=no-aliases -Srhp $< | tail -n +7 > $@; then \
		echo "Warning: $(OBJDUMP) for $< timed out." >&2; \
		touch $@; \
	fi

$(SOLN_DIR)/%.soln: $(ARCHOBJS_DIR)/%.archobj
	@if ! timeout 2 $(SOLN) < $< > $@; then \
		echo "Warning: $(SOLN) for $< timed out." >&2; \
		touch $@; \
	fi

clean:
	@rm -rf $(BINARIES_DIR)/* $(ASMRAW_DIR)/* $(ASM_DIR)/* $(ARCHOBJS_DIR)/* $(SOLN_DIR)/*
	make -C $(SRC_DIR) clean