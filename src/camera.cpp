#include "camera.h"
#include "event_manager.h"

Camera::Camera(Vector4f position, Vector4f lookAt, Vector4f up){
    this->position = position;
    this->rotation = { 0, 0, 0, 0 };
    
    this->lookAt = lookAt;
    this->lookAtPrime = lookAt - position;
    
    this->up = up;
    // Vector direccion desde la camara a posicion a mirar
    this->forward = normalize(lookAt - position); 
}

Matrix4x4f Camera::computeViewMatrix(){
    Matrix4x4f viewMatrix = makeIdentityf();
    
    this->forward = normalize(this->lookAt - this->position);
    this->right = normalize(forward * up);

    Vector4f upCamera = normalize(right * forward);
    Vector4f position = makeVector4(
        - dotProduct (this->right, this->position),
        - dotProduct(this->up, this->position),
        dotProduct(this->forward, this->position),
        1
    );

    // Matriz vista (es definicion)
    viewMatrix.matrixVec[0] = this->right;
    viewMatrix.matrixVec[1] = upCamera;
    viewMatrix.matrixVec[2] = -1.f * this->forward;
    viewMatrix.matrixVec[3] = { 0,0,0,1 };

    viewMatrix.matrix2D[0][3] = position.x;
    viewMatrix.matrix2D[1][3] = position.y;
    viewMatrix.matrix2D[2][3] = position.z;
    
    return viewMatrix;
}

Matrix4x4f Camera::computeProjectionMatrix(float zNear, float zFar, float fovy, float aspectRatio){
    Matrix4x4f projectionMatrix = makeIdentityf();

    // Matriz proyeccion (es definicion)
    projectionMatrix.matrix2D[0][0] =  1.0f / (aspectRatio * tan(fovy * 0.5));
    projectionMatrix.matrix2D[1][1] =  1.0f / tan(fovy * 0.5f);
    projectionMatrix.matrix2D[2][2] = -(zFar + zNear) / (zFar - zNear);
    projectionMatrix.matrix2D[2][3] =  2.0f * zFar * zNear / (zFar - zNear);
    projectionMatrix.matrix2D[3][2] = -1.0f;
    
    return projectionMatrix;
}

void Camera::moveObject(double timeStep)
{
    float speed = 0.5f;
    float rotationSpeed =50.0f;


    if (EventManager::keymap[GLFW_KEY_LEFT])
    {
        position.x -= speed * timeStep;
    }

    if (EventManager::keymap[GLFW_KEY_RIGHT])
    {
        position.x += speed * timeStep;
    }

    if (EventManager::keymap[GLFW_KEY_H])
    {
        rotation.y += rotationSpeed * timeStep;
    }

    if (EventManager::keymap[GLFW_KEY_F])
    {
        rotation.y -= rotationSpeed * timeStep;
    }

    Matrix4x4f rotationMatrix = makeRotate(rotation.x, rotation.y, rotation.z);
    lookAt = rotationMatrix * lookAtPrime;
    Matrix4x4f traslateMatrix = makeTraslate(position.x, position.y, position.z);
    lookAt = traslateMatrix * lookAt;
}