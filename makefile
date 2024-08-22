# Compiler
CXX := clang++

# Compiler flags
CXXFLAGS := -std=c++23 -Wall -Wextra -pedantic -O2

# Linker flags
LDFLAGS :=

# Source directory
SRC_DIR := toy.cpp

# Build directory
BUILD_DIR := build

# Include directory
INCLUDE_DIR := include

# Source files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable name
TARGET := myprogram

# Default target
all: $(BUILD_DIR) $(TARGET)

# Rule to create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c -o $@ $

# Clean rule
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
