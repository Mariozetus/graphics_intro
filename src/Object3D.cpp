#include "Object3D.h"

Object3D::Object3D()
{
    vertexList = {
        {{ 0, 0.5, 0, 1 }, { 1, 0, 0, 1 }}, // vertice superior
        {{ -0.5, -0.5, 0, 1 }, { 1, 1, 0, 1 }}, // vertice inferior izq.
        {{ 0.5, -0.5, 0, 1}, { 0, 0, 1, 1 }} // verice inferior der.
    };
    
}

matrix4x4f Object3D::computeModelMatrix()
{
    matrix4x4f model = makeTranslate(position.x, position.y, position.z);
    return model;
}

void Object3D::moveObject(double timeStep)
{
    float speed = 1;
    if(EventManager::keymap[GLFW_KEY_A])
        position.x -= speed * timeStep;
    if(EventManager::keymap[GLFW_KEY_D])
        position.x += speed * timeStep;
    if(EventManager::keymap[GLFW_KEY_W])
        position.y += speed * timeStep;
    if(EventManager::keymap[GLFW_KEY_S])
        position.y -= speed * timeStep;
}
