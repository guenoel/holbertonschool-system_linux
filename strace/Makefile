# C Compiler
CC = gcc

# Compiler Flags
CFLAGS = -std=c90 -Wall -Werror -Wextra -pedantic
FILES_0 = strace_0.c
FILES_1 = strace_1.c

# Linker Flags (empty in this case)
LDFLAGS =

# Default Target: Build the strace_0 executable
all: strace_0 strace_1

# Rule to build strace_0 from strace_0.c
strace_0: strace_0.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(FILES_0) -o $@ $<
strace_1: strace_1.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(FILES_1) -o $@

# Target to clean generated files
clean:
	rm -f strace_0 strace_1

# Declaration of phony targets
.PHONY: all clean
