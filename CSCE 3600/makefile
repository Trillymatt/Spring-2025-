# Makefile for newshell project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Executable name
TARGET = newshell

# Source files
SRCS = main.c builtins.c execution.c parser.c shell_core.c

# Object files (same as SRCS but with .o)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = shell.h

# Default build target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)