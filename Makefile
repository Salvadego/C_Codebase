CC = gcc
ENABLE_ASSERT = -DENABLE_ASSERT=1
CFLAGS = -Wall -Werror -Wextra -std=c99 $(ENABLE_ASSERT)
SANITIZE = -fsanitize=address,undefined -fno-omit-frame-pointer
TARGET_DIR = bin
BUILD_DIR = build
TARGET = $(TARGET_DIR)/main
SRC = ./src/main.c
OBJ = $(SRC:./src/%.c=$(BUILD_DIR)/%.o)
DEBUGFLAGS = -DDEBUG -ggdb -O0
RELEASEFLAGS = -O2

.PHONY: all clean run test

all: $(TARGET_DIR) $(TARGET)

$(TARGET_DIR):
	@mkdir -p $(TARGET_DIR)

$(TARGET): $(OBJ)
	@$(CC) -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.o: ./src/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

run: all
	@$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
	rm -rf $(TARGET_DIR)
	rm -rf $(BUILD_DIR)

debug: CFLAGS += $(DEBUGFLAGS) $(SANITIZE)
debug: clean all

release: CFLAGS += $(RELEASEFLAGS)
release: clean all
