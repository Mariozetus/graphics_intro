#pragma once

class Render {
private:
    int width;
    int height;
    char** buffer;
    
public:
    Render(int ancho, int alto);
    
    ~Render();
    
    void PutPixel(int x, int y);
    
    void resetBuffer();
    
    void Draw();
};
