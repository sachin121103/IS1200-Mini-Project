# =========================================================
# RISC-V Basketball Game Build System
# =========================================================

# Compiler and tools
CC       := riscv32-unknown-elf-gcc
AS       := riscv32-unknown-elf-as
LD       := riscv32-unknown-elf-ld
OBJCOPY  := riscv32-unknown-elf-objcopy

# Compiler and linker flags
CFLAGS   := -march=rv32i -mabi=ilp32 -O2 -Wall -Wextra
LDFLAGS  := -T linker_script.ld

# Directories
SRC_DIR  := src
INC_DIR  := include
BUILD_DIR := build
ASM_DIR  := asm

# Source files
C_SOURCES   := $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES := $(wildcard $(ASM_DIR)/*.s)

# Object files
C_OBJECTS   := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst $(ASM_DIR)/%.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJECTS     := $(C_OBJECTS) $(ASM_OBJECTS)

# Targets
TARGET := basketball_game.elf
BINARY := basketball_game.bin

# =========================================================
# Default target
# =========================================================
all: $(BUILD_DIR) $(TARGET) $(BINARY)

# =========================================================
# Create build directory
# =========================================================
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# =========================================================
# Compile C files
# =========================================================
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# =========================================================
# Assemble assembly files
# =========================================================
$(BUILD_DIR)/%.o: $(ASM_DIR)/%.s
	@echo "Assembling $<..."
	@$(AS) $(CFLAGS) -c $< -o $@

# =========================================================
# Link all objects
# =========================================================
$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@

# =========================================================
# Create binary image
# =========================================================
$(BINARY): $(TARGET)
	@echo "Creating binary..."
	@$(OBJCOPY) -O binary $< $@

# =========================================================
# Clean up build artifacts
# =========================================================
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(TARGET) $(BINARY)

# =========================================================
# Phony targets
# =========================================================
.PHONY: all clean person_a person_b

# =========================================================
# Developer-specific partial builds
# =========================================================
person_a: $(BUILD_DIR) $(BUILD_DIR)/game_state.o $(BUILD_DIR)/physics.o $(BUILD_DIR)/collision.o $(BUILD_DIR)/input.o

person_b: $(BUILD_DIR) $(BUILD_DIR)/vga.o $(BUILD_DIR)/graphics.o $(BUILD_DIR)/sprites.o $(BUILD_DIR)/hardware.o
