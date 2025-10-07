# Makefile for Atari 800XL LLVM-MOS Project

# Add llvm-mos to PATH
export PATH := /opt/llvm-mos/bin:$(PATH)

# Project name
PROJECT = atari-test

# Directories
SRC_DIR = src
BUILD_DIR = build
DIST_DIR = dist

# Compiler and tools
CC = mos-atari8-dos-clang
LD = mos-atari8-dos-clang
OBJCOPY = llvm-objcopy

# Compiler flags
CFLAGS = -Os -Wall -Wextra
LDFLAGS = 

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Output files
XEX = $(DIST_DIR)/$(PROJECT).xex
ATR = $(DIST_DIR)/$(PROJECT).atr

# Default target
all: directories $(XEX) $(ATR)

# Create necessary directories
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(DIST_DIR)

# Compile C files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create XEX executable (mos-atari8-dos outputs XEX directly)
$(XEX): $(OBJECTS)
	@echo "Linking and creating Atari XEX executable..."
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@
	@echo "Built: $@"

# Create ATR disk image
$(ATR): $(XEX)
	@echo "Creating ATR disk image..."
	@if command -v atr >/dev/null 2>&1 || command -v dir2atr >/dev/null 2>&1; then \
		if command -v dir2atr >/dev/null 2>&1; then \
			dir2atr -d -b Dos25 720 $(ATR) $(DIST_DIR); \
		else \
			echo "Warning: dir2atr not found. Please install atr-tools or create ATR manually."; \
			echo "XEX file is available at: $(XEX)"; \
		fi \
	else \
		echo "Warning: ATR creation tools not found."; \
		echo "Install dir2atr from: https://github.com/jhallen/dir2atr"; \
		echo "Or use online tools to create ATR from XEX."; \
		echo "XEX file is available at: $(XEX)"; \
	fi

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR) $(DIST_DIR)

# Clean and rebuild
rebuild: clean all

# Display build information
info:
	@echo "Project: $(PROJECT)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Output: $(XEX)"
	@echo "ATR Image: $(ATR)"

# Run in emulator (requires atari800 emulator)
run: $(XEX)
	@if command -v atari800 >/dev/null 2>&1; then \
		atari800 -xl -nobasic $(XEX); \
	else \
		echo "Atari800 emulator not found."; \
		echo "Install from: https://atari800.github.io/"; \
		echo "Or load $(XEX) in your preferred Atari emulator."; \
	fi

.PHONY: all directories clean rebuild info run
