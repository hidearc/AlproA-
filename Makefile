# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 

# Target executable name
TARGET = program

# Source files
SRCS = main.c link.c

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = link.h boolean.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile .c files into .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything
rebuild: clean all

# Debug build (with debugging symbols)
debug: CFLAGS += -DDEBUG -g
debug: clean all

# For Valgrind memory checking
valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# Help message
help:
	@echo "Available targets:"
	@echo "  all      : Build the program (default)"
	@echo "  clean    : Remove object files and executable"
	@echo "  run      : Build and run the program"
	@echo "  rebuild  : Clean and rebuild from scratch"
	@echo "  debug    : Build with debug symbols and DEBUG flag"
	@echo "  valgrind : Run memory leak check with valgrind"
	@echo "  help     : Show this help message"

# Phony targets (targets that are not actual files)
.PHONY: all clean run rebuild debug valgrind help
