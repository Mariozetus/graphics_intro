# Variables
CC = g++
CFLAGS = -Wall -g
INCLUDES = -Iinclude -Iexternal/glad/inc -Iexternal # Includes del proyecto
LIBS = -lglfw -lX11 -lpthread -ldl # Librerias del sistema

# Directorios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Nombre ejecutable
TARGET = $(BIN_DIR)/graphics_intro

# Archivos fuente y objetos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Regla principal
all: $(TARGET)

# Crear ejecutable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

# Compilar archivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Crear directorios si no existen
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regla de limpieza
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)