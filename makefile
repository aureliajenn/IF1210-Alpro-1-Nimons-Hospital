CC = gcc
CFLAGS = -g -Wall -I./src  # Menambahkan path ke folder src untuk mencari file header
TARGET = main
TARGET_DIR = build

# Temukan semua file .c di dalam folder src dan juga file .c di root folder
SRCS = $(wildcard *.c) $(shell find src -name '*.c')

# Buat path object (.o) berdasarkan lokasi source file
OBJS = $(patsubst %.c, $(TARGET_DIR)/%.o, $(SRCS))

# Default target
$(TARGET): $(OBJS)
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
	./$(TARGET) $(ARGS)

# Dependency untuk file header
build/main.o: src/DataParser/dataParser.h src/Model/model.h src/Laman/pasien.h src/Laman/dokter.h src/Laman/manager.h src/Label/label.h src/Utils/load.h src/Utils/save.h 
build/src/DataParser/dataParser.o: src/DataParser/dataParser.h src/Model/model.h
# build/src/penyakit.o: src/penyakit.h
build/src/Utils/utils.o: src/Utils/utils.h
build/src/Laman/pasien.o: src/Model/model.h