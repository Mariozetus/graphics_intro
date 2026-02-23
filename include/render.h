#pragma once
#include "object_3d.h"
#include "camera.h"

class Render {

public:
    typedef struct{
        unsigned int bufferId;
        unsigned int vertexBufferId;
        unsigned int indexBufferId;
    } bufferObject_t;

    Camera* camera = new Camera({ 0, 0, 3, 1}, { 0, 0, 0, 1 });    


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
