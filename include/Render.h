#pragma once
#include "Object3D.h"

class Render {

public:
    typedef struct{
        unsigned int bufferId;
        unsigned int vertexBufferId;
        unsigned int indexBufferId;
    } bufferObject_t;

    vector< Object3D* > objectList;
    map< unsigned int, bufferObject_t > bufferObjectList;

    GLFWwindow* window = nullptr;

    bool exit = false;

    Render();

    void setupObject(Object3D* obj);
    void updateObjects(double timeStep);
    void drawObjects();
    void mainLoop();
};
