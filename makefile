CC = gcc
CFLAGS = -g -Wall
TARGET = main
TARGET_DIR = build

# Temukan semua file .c di dalam folder src dan juga file .c di root folder
SRCS = $(wildcard *.c) $(shell find src -name '*.c')

# Buat path object (.o) berdasarkan lokasi source file
OBJS = $(patsubst %.c, $(TARGET_DIR)/%.o, $(SRCS))

# Default target
main: $(OBJS)
	@echo "Linking object files..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build complete."

# Rule umum untuk kompilasi: src/abc/def.c → build/src/abc/def.o
$(TARGET_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf $(TARGET_DIR)
	rm -f $(TARGET)


###########################
CC = gcc
CFLAGS = -g -Wall
TARGET = main
TARGET_DIR = build

# Temukan semua file .c di dalam folder src dan juga file .c di root folder
SRCS = $(wildcard *.c) $(shell find src -name '*.c')

# Buat path object (.o) berdasarkan lokasi source file
OBJS = $(patsubst %.c, $(TARGET_DIR)/%.o, $(SRCS))

# Default target
main: $(OBJS)
	@echo "Linking object files..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build complete."

# Rule umum untuk kompilasi: src/abc/def.c → build/src/abc/def.o
$(TARGET_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf $(TARGET_DIR)
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
