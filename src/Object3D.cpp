#include "Object3D.h"
#include "eventManager.h"

Object3D::Object3D()
{
    objectId = idCounter++;
    
    vertexList = {
        {{ -0.5,  0.5, 0, 1 }, { 1, 0, 0, 1 }}, // vertice superior izq.
        {{  0.5,  0.5, 0, 1 }, { 1, 0, 0, 1 }}, // vertice superior der.
        {{ -0.5, -0.5, 0, 1 }, { 1, 1, 0, 1 }}, // vertice inferior izq.
        {{  0.5, -0.5, 0, 1},  { 0, 0, 1, 1 }} // verice inferior der.
    };

    // Primer triangulo, esquina arriba izq., esquina arriba der. y esquina inferior abajo izq.
    // Segundo triangulo, esquina arriba der., esquina abajo der. y esquina inferior abajo izq.
    indexList = { 0, 1, 2 , 2, 1, 3 }; // Hay que indicarlos en el mismo sentido (para que las normales miren al mismo lado), 
//                                      en este caso en sentido del reloj
    
}

matrix4x4f Object3D::computeModelMatrix()
{
    matrix4x4f model = makeTraslate(position.x, position.y, position.z);
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
