# Compiler
CXX = g++

# Target
TARGET = main

# Source files
SRCS = main.cpp

# Default target
all:
	$(CXX) $(SRCS) -o $(TARGET)

# Clean up
clean:
	rm -f $(TARGET)

.PHONY: all clean
