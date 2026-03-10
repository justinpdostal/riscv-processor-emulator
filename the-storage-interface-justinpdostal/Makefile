OBJCRT_DIR = object_create
STUDENT_DIR = src
SOLN_BIN = $(STUDENT_DIR)/r5emu
SOLN_SRC = $(wildcard $(STUDENT_DIR)/*.c) $(wildcard $(STUDENT_DIR)/*.h) $(STUDENT_DIR)/Makefile
TEST_DIR = tests
TEST_SRCOBJS = $(sort $(wildcard $(TEST_DIR)/assembly/*.S))

all: test_objects

rebuild: clean all

test: 
	@make rebuild
	@echo Running Tests....
	./run_tests.sh

# Create all of the test objects
test_objects: $(wildcard $(OBJCRT_DIR)/*) $(TEST_SRCOBJS)
	$(info <<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>)
	$(info <<< Creating solution and all of the test objects  >>>)
	$(info <<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>)
	@make --no-print-directory -C $(OBJCRT_DIR)
	@echo ""
	@echo "Compilation complete"
	

clean:
	make --no-print-directory -C $(STUDENT_DIR) clean
	make --no-print-directory -C $(OBJCRT_DIR) clean


.PHONY: all clean rebuild test test_objects

