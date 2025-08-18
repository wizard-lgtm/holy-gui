# Compiler
CC = clang

# Directories
SRC_DIR = src
INC_DIR = src/lib
BUILD_DIR = build
TARGET = holy-gui

# Detect platform
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS
    CFLAGS = -Wall -Wextra -O2 $(shell pkg-config --cflags sdl3)
    LDFLAGS = $(shell pkg-config --libs sdl3)
else
    # Linux
    CFLAGS = -Wall -Wextra -O2 $(shell pkg-config --cflags sdl3)
    LDFLAGS = $(shell pkg-config --libs sdl3)
endif

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Create build directory if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run the program
run: all
	./$(TARGET)

# Clean build
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean run
