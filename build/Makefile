PREFIX = aarch64-none-elf

CFLAGS = -Wall -Wno-unknown-pragmas -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
LFLAGS = -nostdlib -nostartfiles

SRC_DIR = ../src
HEAD_DIR = ../include
OBJ_DIR = objects
SRCS = $(shell find $(SRC_DIR) -name *.c)
ASM_SRCS = $(shell find $(SRC_DIR) -name *.S)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJECTS += $(patsubst $(SRC_DIR)/%.S, $(OBJ_DIR)/%.o, $(ASM_SRCS))
HEADERS = $(wildcard $(HEAD_DIR)/*.h)

IMG_NAME=kernel8

build: clean $(OBJECTS) $(HEADERS)
	$(PREFIX)-ld $(LFLAGS) $(OBJECTS) -T linker.ld -o $(IMG_NAME).elf
	$(PREFIX)-objcopy -O binary $(IMG_NAME).elf $(IMG_NAME).img

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(PREFIX)-gcc $(CFLAGS) -I$(SRC_DIR) -I$(HEAD_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(PREFIX)-gcc $(CFLAGS) -I$(SRC_DIR) -I$(HEAD_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) || true
	rm $(IMG_NAME).elf $(IMG_NAME).img || true