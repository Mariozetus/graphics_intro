# Variables
CC = g++
CFLAGS = -Wall -g
INCLUDES = -Iinclude -Iexternal/glad/inc -Iexternal # Includes del proyecto
LIBS = -lglfw -lX11 -lpthread -ldl # Librerias del sistema

# Directorios
SRCDIR = src
OBJDIR = build
BINDIR = bin

# Nombre ejecutable
TARGET = $(BINDIR)/graphics_intro

# Archivos fuente y objeto
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/mathLib.cpp $(SRCDIR)/Object3D.cpp $(SRCDIR)/eventManager.cpp $(SRCDIR)/Render.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Regla principal
all: $(OBJDIR) $(BINDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ ${INCLUDES} ${LIBS}

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ ${INCLUDES}

# Regla de limpieza
clean:
	rm -rf $(OBJDIR) $(BINDIR)