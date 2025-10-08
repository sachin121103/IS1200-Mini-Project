# =========================================================
# RISC-V Basketball Game Build System
# =========================================================

# Toolchain
CC       := riscv32-unknown-elf-gcc
AS       := riscv32-unknown-elf-as
LD       := riscv32-unknown-elf-ld
OBJCOPY  := riscv32-unknown-elf-objcopy
OBJDUMP  := riscv32-unknown-elf-objdump
SIZE     := riscv32-unknown-elf-size

# Directories
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
ASM_DIR   := asm

# Output files
TARGET := basketball_game.elf
BINARY := basketball_game.bin
HEX    := basketball_game.hex
LST    := basketball_game.lst
MAP    := $(BUILD_DIR)/basketball_game.map

# Architecture flags (shared between C and ASM)
ARCH_FLAGS := -march=rv32i -mabi=ilp32

# Compiler flags
CFLAGS := $(ARCH_FLAGS) \
          -O2 \
          -Wall \
          -Wextra \
          -I$(INC_DIR) \
          -ffunction-sections \
          -fdata-sections

# Assembler flags
ASFLAGS := -march=rv32i_zicsr -mabi=ilp32

# Linker flags
LDFLAGS := $(ARCH_FLAGS) \
           -T linker-script.ld \
           -nostartfiles \
           -Wl,--gc-sections \
           -Wl,-Map=$(MAP)

# Source files
C_SOURCES   := $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES := $(wildcard $(ASM_DIR)/*.s)

# Header files (for dependency tracking)
HEADERS := $(wildcard $(INC_DIR)/*.h)

# Object files
C_OBJECTS   := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst $(ASM_DIR)/%.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJECTS     := $(ASM_OBJECTS) $(C_OBJECTS)

# =========================================================
# Default target
# =========================================================
.DEFAULT_GOAL := all

all: $(BUILD_DIR) $(TARGET) $(BINARY) $(HEX) size

# =========================================================
# Create build directory
# =========================================================
$(BUILD_DIR):
<<<<<<< HEAD
=======
	@echo "Creating build directory..."
>>>>>>> 1e3aaa6a6546cea74414e956fc2eaaf9d9b6f432
	@mkdir -p $(BUILD_DIR)

# =========================================================
# Compile C files (with dependency tracking)
# =========================================================
<<<<<<< HEAD
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
=======
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "CC    $<"
	@$(CC) $(CFLAGS) -c $< -o $@
>>>>>>> 1e3aaa6a6546cea74414e956fc2eaaf9d9b6f432

# =========================================================
# Assemble assembly files
# =========================================================
$(BUILD_DIR)/%.o: $(ASM_DIR)/%.s
<<<<<<< HEAD
	@echo "Assembling $<..."
	@$(AS) $(CFLAGS) -c $< -o $@
=======
	@echo "AS    $<"
	@$(AS) $(ASFLAGS) -c $< -o $@
>>>>>>> 1e3aaa6a6546cea74414e956fc2eaaf9d9b6f432

# =========================================================
# Link all objects
# =========================================================
<<<<<<< HEAD
$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@
=======
$(TARGET): $(OBJECTS) linker-script.ld
	@echo "LD    $@"
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@
>>>>>>> 1e3aaa6a6546cea74414e956fc2eaaf9d9b6f432

# =========================================================
# Create binary image
# =========================================================
$(BINARY): $(TARGET)
<<<<<<< HEAD
	@echo "Creating binary..."
	@$(OBJCOPY) -O binary $< $@
=======
	@echo "BIN   $@"
	@$(OBJCOPY) -O binary $< $@

# =========================================================
# Create Intel HEX file
# =========================================================
$(HEX): $(TARGET)
	@echo "HEX   $@"
	@$(OBJCOPY) -O ihex $< $@

# =========================================================
# Create disassembly listing
# =========================================================
$(LST): $(TARGET)
	@echo "LST   $@"
	@$(OBJDUMP) -D $< > $@

# =========================================================
# Show binary size
# =========================================================
.PHONY: size
size: $(TARGET)
	@echo ""
	@echo "===== Binary Size ====="
	@$(SIZE) basketball_game.elf
	@echo ""
>>>>>>> 1e3aaa6a6546cea74414e956fc2eaaf9d9b6f432

# =========================================================
# Clean up build artifacts
# =========================================================
.PHONY: clean
clean:
<<<<<<< HEAD
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(TARGET) $(BINARY)
=======
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR) $(TARGET) $(BINARY) $(HEX) $(LST)
>>>>>>> 1e3aaa6a6546cea74414e956fc2eaaf9d9b6f432

# =========================================================
# Deep clean (also remove backups, etc.)
# =========================================================
.PHONY: distclean
distclean: clean
	@echo "Deep cleaning..."
	@find . -name "*~" -delete
	@find . -name "*.swp" -delete

# =========================================================
# Developer-specific partial builds
# =========================================================
.PHONY: person_a person_b

person_a: $(BUILD_DIR) \
          $(BUILD_DIR)/game_state.o \
          $(BUILD_DIR)/physics.o \
          $(BUILD_DIR)/collision.o \
          $(BUILD_DIR)/input.o \
          $(BUILD_DIR)/utils.o
	@echo "Person A modules built successfully!"

person_b: $(BUILD_DIR) \
          $(BUILD_DIR)/vga.o \
          $(BUILD_DIR)/graphics.o \
          $(BUILD_DIR)/sprites.o \
          $(BUILD_DIR)/hardware.o
	@echo "Person B modules built successfully!"

# =========================================================
# Debugging targets
# =========================================================
.PHONY: dump symbols headers map

# Disassemble the ELF file
dump: $(LST)
	@less $(LST)

# Show all symbols
symbols: $(TARGET)
	@$(OBJDUMP) -t $< | less

# Show section headers
headers: $(TARGET)
	@$(OBJDUMP) -h $

# Show memory map
map: $(TARGET)
	@cat $(MAP) | less

# =========================================================
# Help target
# =========================================================
.PHONY: help
help:
	@echo "Basketball Game Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all       - Build everything (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  distclean - Remove all generated files"
	@echo "  person_a  - Build Person A modules only"
	@echo "  person_b  - Build Person B modules only"
	@echo "  size      - Show binary size"
	@echo "  dump      - Disassemble binary"
	@echo "  symbols   - Show symbol table"
	@echo "  headers   - Show section headers"
	@echo "  map       - Show memory map"
	@echo "  help      - Show this help"
	@echo ""
	@echo "Variables:"
	@echo "  DEBUG=1   - Build with debug symbols (e.g., make DEBUG=1)"

# =========================================================
# Optional: Debug build variant
# =========================================================
ifdef DEBUG
CFLAGS += -g -Og -DDEBUG
LDFLAGS += -Wl,--print-memory-usage
$(info Building in DEBUG mode)
endif

# =========================================================
# Optional: Verbose build
# =========================================================
ifdef VERBOSE
.SILENT:
endif

# =========================================================
# Prevent deletion of intermediate files
# =========================================================
.PRECIOUS: $(BUILD_DIR)/%.o