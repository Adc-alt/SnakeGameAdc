# Ruta donde está instalada la librería Raylib
RAYLIB_DIR = C:/raylib/w64devkit

# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(RAYLIB_DIR)/include -I$(RAYLIB_DIR)/../raylib/src -I./include
LDFLAGS = -L$(RAYLIB_DIR)/lib -lraylib -lopengl32 -lgdi32 -lwinmm

# Archivos fuente
SRC = src/main.cpp \
      src/core/game.cpp \
      src/entities/snake.cpp \
      src/entities/food.cpp

TARGET = game.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	del /F /Q $(TARGET)