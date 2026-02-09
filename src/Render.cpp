#include "Render.h"
#include <iostream>

Render::Render(int ancho, int alto) : width(ancho), height(alto) {
    buffer = new char*[height];
    for (int i = 0; i < height; i++) {
        buffer[i] = new char[width];
    }
    
    resetBuffer();
}

Render::~Render() {
    for (int i = 0; i < height; i++) {
        delete[] buffer[i];
    }
    delete[] buffer;
}

void Render::PutPixel(int x, int y) {
    
    int col = x + (width / 2);
    int row = y + (height / 2);
    
    int maxCoord = width / 2;
    int minCoord = -(width / 2);
    
    // Si es invalida la ignoramos
    if (x > maxCoord || x < minCoord || y > maxCoord || y < minCoord) {
        return;
    }
    
    // Verificar límites del array
    if (row >= 0 && row < height && col >= 0 && col < width) {
        buffer[row][col] = 1;
    }
}

void Render::resetBuffer() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            buffer[i][j] = 0;
        }
    }
}

void Render::Draw() {
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            if (buffer[i][j] == 0) {
                std::cout << " ";
            } else {
                std::cout << "·";
            }
        }
        std::cout << std::endl;
    }
}
