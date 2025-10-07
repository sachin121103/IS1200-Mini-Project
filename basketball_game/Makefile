CC = riscv32-unknown-elf-gcc
CFLAGS = -march=rv32im -mabi=ilp32 -O0 -g -Wall -Wextra

all: test

test:
	$(CC) $(CFLAGS) -c src/main.c -o main.o
	@echo "Build successful!"

clean:
	rm -f *.o *.elf *.bin