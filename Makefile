CC = gcc
ENABLE_ASSERT = -DENABLE_ASSERT=1
CFLAGS = -Wall -Werror -Wextra -std=c99 $(ENABLE_ASSERT)
SANITIZE = -fsanitize=address,undefined -fno-omit-frame-pointer
TARGET_DIR = bin
BUILD_DIR = build
TARGET = $(TARGET_DIR)/main
SRC = ./src/main.c
OBJ = $(SRC:./src/%.c=$(BUILD_DIR)/%.o)
DEBUGFLAGS = -DDEBUG -g -O0
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

TEST_PATH ?= test

test:
	@if [ -d "$(TEST_PATH)" ]; then \
		echo "Running tests in directory $(TEST_PATH)..."; \
		mkdir -p $(BUILD_DIR); \
		for f in $(TEST_PATH)/*.c; do \
			[ -f "$$f" ] || continue; \
			$(CC) $(CFLAGS) -o $(BUILD_DIR)/$$(basename $$f .c) $$f && $(BUILD_DIR)/$$(basename $$f .c); \
		done; \
	elif [ -f "$(TEST_PATH)" ]; then \
		echo "Running test file $(TEST_PATH)..."; \
		mkdir -p $(BUILD_DIR); \
		$(CC) $(CFLAGS) -o $(BUILD_DIR)/$$(basename $(TEST_PATH) .c) $(TEST_PATH) && $(BUILD_DIR)/$$(basename $(TEST_PATH) .c); \
	else \
		echo "Test file or directory '$(TEST_PATH)' not found."; exit 1; \
	fi
