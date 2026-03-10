MODE = P

# Get a list of all .c files in the current directory
CFILES_ALL = $(wildcard *.c)

# Set the C files to compile based on the mode
ifeq ($(MODE), S)
	CFILES = $(CFILES_ALL)
else ifeq ($(MODE), P)
    CFILES = $(filter-out $(foreach file, $(CFILES_ALL), $(if $(wildcard objects/$(basename $(file)).o)$(wildcard objects/$(basename $(file)).d),$(file))), $(CFILES_ALL))
else 
	MESSAGE = ($(error Invalid mode specified. Use F for full or T for test.))
endif

CFILES_EXCLUDE_MAIN = $(filter-out main.c, $(CFILES))
OFILES = $(patsubst %.c,%.o,$(CFILES_ALL))
DFILES = $(patsubst %.c,%.d,$(CFILES_ALL))
BINARY = r5emu
CC = gcc
CFLAGS = -O3 -I. -Wall -Werror -Wextra 

all:
ifeq ($(MODE), P)
	@echo "Using provided object files"
	cp $(wildcard objects/*.o) .
	make $(BINARY) 
else ifeq ($(MODE), S)
	@echo "Using student's object files"
	make $(BINARY) 
else
	@echo "\nInvalid mode specified. Use P for provided file or S for student.\n"
endif

$(BINARY): $(OFILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DFILES)


clean:
	rm -rf $(BINARY) $(OFILES) $(DFILES) tests/test
	

