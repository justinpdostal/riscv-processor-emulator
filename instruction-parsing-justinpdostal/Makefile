CFILES = $(wildcard *.c)
OFILES = $(patsubst %.c,%.o,$(CFILES))
DFILES = $(patsubst %.c,%.d,$(CFILES))
BINARY = r5emu
CC = gcc
UTIL = util
# note: no -g or anything similar, and using -O3: these will make it
# hard to disassemble the assembly and reverse to C
CFLAGS = -O3 -I. -Wall -Werror -Wextra

OUTPUT_DIR="./output"

all: $(BINARY)

$(BINARY): $(OFILES)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(UTIL):
	@echo "Downloading utils..."
	wget https://github.com/gwu-cs-sysprog/utils/raw/main/util.tgz
	tar zxvf util.tgz
	rm util.tgz

-include $(DFILES)

test:
	sh tests/run_tests.sh

clean:
	rm -rf $(BINARY) $(OFILES) $(DFILES) $(UTIL) $(OUTPUT_DIR)
