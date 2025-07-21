NASM = nasm
CC = gcc
LD = ld
OBJCOPY = objcopy

CFLAGS = -m32 -ffreestanding -c
LDFLAGS = -m elf_i386 -T src/linker.ld -nostdlib

SRC_DIR = src
BUILD_DIR = build

C_SRCS = $(wildcard $(SRC_DIR)/*.c)
C_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))

BOOT_BIN = $(BUILD_DIR)/boot.bin
PM_OBJ = $(BUILD_DIR)/pm.o
KERNEL_ELF = $(BUILD_DIR)/kernel.elf
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
OS_IMAGE_BIN = $(BUILD_DIR)/os-image.bin
OS_IMAGE_IMG = $(BUILD_DIR)/os-image.img

all: $(OS_IMAGE_BIN) $(OS_IMAGE_IMG)
	@rm -f $(BUILD_DIR)/*.o $(PM_OBJ) $(KERNEL_ELF) $(KERNEL_BIN) $(BOOT_BIN) >/dev/null 2>&1
	@echo "Images successfully built in build directory"

$(BOOT_BIN): $(SRC_DIR)/boot.asm | $(BUILD_DIR)
	@$(NASM) -f bin $< -o $@ >/dev/null 2>&1

$(PM_OBJ): $(SRC_DIR)/pm.asm | $(BUILD_DIR)
	@$(NASM) -f elf $< -o $@ >/dev/null 2>&1

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $< -o $@ >/dev/null 2>&1

$(KERNEL_ELF): $(PM_OBJ) $(C_OBJS)
	@$(LD) $(LDFLAGS) $^ -o $@ >/dev/null 2>&1

$(KERNEL_BIN): $(KERNEL_ELF)
	@$(OBJCOPY) -O binary $< $@ >/dev/null 2>&1

$(OS_IMAGE_BIN): $(BOOT_BIN) $(KERNEL_BIN)
	@cat $^ > $@

$(OS_IMAGE_IMG): $(BOOT_BIN) $(KERNEL_BIN)
	@cat $^ > $@

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all clean