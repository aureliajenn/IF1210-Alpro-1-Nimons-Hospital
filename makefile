# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -I./src  # Menambahkan path ke folder src untuk mencari file header
TARGET = main
TARGET_DIR = build

# Temukan semua file .c di dalam folder src dan juga file .c di root folder
SRCS = $(wildcard *.c) $(shell find src -name '*.c')

# Buat path object (.o) berdasarkan lokasi source file
OBJS = $(SRCS:%.c=$(TARGET_DIR)/%.o)

# Default target untuk kompilasi dan linking
$(TARGET): $(OBJS)
	@echo "Linking object files..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build complete."

# Rule umum untuk kompilasi file .c menjadi file .o
$(TARGET_DIR)/%.o: %.c
	@mkdir -p $(dir $@)  # Membuat direktori build untuk file objek
	$(CC) $(CFLAGS) -c $< -o $@  # Kompilasi file sumber menjadi file objek

# Clean target untuk menghapus file build sebelumnya
clean:
	rm -rf $(TARGET_DIR)
	rm -f $(TARGET)

# Menjalankan program setelah build
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Dependency untuk file header
$(TARGET_DIR)/main.o: src/DataParser/dataParser.h src/Model/model.h src/Laman/pasien.h src/Laman/dokter.h src/Laman/manager.h src/Label/label.h src/Utils/load.h src/Utils/saveload.h
$(TARGET_DIR)/src/DataParser/dataParser.o: src/DataParser/dataParser.h src/Model/model.h
$(TARGET_DIR)/src/Utils/utils.o: src/Utils/utils.h
$(TARGET_DIR)/src/Laman/pasien.o: src/Model/model.h
$(TARGET_DIR)/src/Utils/map.o: src/Utils/map.h
$(TARGET_DIR)/src/Laman/AntrianSaya/antriansaya.o: src/Model/model.h src/Utils/saveload.h
