OBJCRT_DIR = object_create
STUDENT_DIR = hw2
SOLN_BIN = $(STUDENT_DIR)/r5emu
SOLN_SRC = $(wildcard $(STUDENT_DIR)/*.c) $(wildcard $(STUDENT_DIR)/*.h) $(STUDENT_DIR)/Makefile

TEST_DIR = tests
ARCHOBJS_DIR = $(TEST_DIR)/archobjs
ASM_DIR = $(TEST_DIR)/asm
ASMRAW_DIR = $(TEST_DIR)/asmraw
ASSEMBLY_DIR = $(TEST_DIR)/assembly
BINARIES_DIR = $(TEST_DIR)/binaries
EXAMPLES_DIR = $(TEST_DIR)/examples
SOLN_DIR = $(TEST_DIR)/solutions

TEST_SRCOBJS = $(wildcard $(ASSEMBLY_DIR)/*.S) 
TEST_ARCHOBJS = $(patsubst %.S,%.archobj,$(TEST_SRCOBJS)) $(patsubst %.c,%.archobj,$(TEST_SRCOBJS))
TEST_SOLNOBJS = $(patsubst %.archobj,%.soln,$(TEST_ARCHOBJS))


all: test_objects

test: test_objects
	@echo Running Tests....
	./run_tests.sh


# Create all of the test objects
test_objects: $(wildcard $(OBJCRT_DIR)/*) $(wildcard $(TEST_SRCOBJS))
	$(info <<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>)
	$(info <<< Creating solution and all of the test objects  >>>)
	$(info <<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>)
	make --no-print-directory -C $(OBJCRT_DIR)
	make --no-print-directory move_files
	@echo ""
	@echo "Compilation complete"
	

move_files:
	$(info <<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>)
	$(info <<< Moving files to the appropriate directories      >>>)
	$(info <<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>)
	mkdir -p $(ARCHOBJS_DIR) $(ASM_DIR) $(ASMRAW_DIR) $(BINARIES_DIR) $(SOLN_DIR)
	mv $(ASSEMBLY_DIR)/*.archobj $(ARCHOBJS_DIR)/
	mv $(ASSEMBLY_DIR)/*.asm $(ASM_DIR)/
	mv $(ASSEMBLY_DIR)/*.rawasm $(ASMRAW_DIR)/
	mv $(ASSEMBLY_DIR)/*.bin $(BINARIES_DIR)/
	mv $(ASSEMBLY_DIR)/*.soln $(SOLN_DIR)/

clean:
	make --no-print-directory -C $(STUDENT_DIR) clean
	make --no-print-directory -C $(OBJCRT_DIR) clean
	$(foreach D,$(ARCHOBJS_DIR),rm -rf $(D)/*.archobj;)
	$(foreach D,$(ASM_DIR),rm -rf $(D)/*.asm;)
	$(foreach D,$(ASMRAW_DIR),rm -rf $(D)/*.rawasm;)
	$(foreach D,$(BINARIES_DIR),rm -rf $(D)/*.bin;)
	$(foreach D,$(SOLN_DIR),rm -rf $(D)/*.soln;)
