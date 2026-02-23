#pragma once
#include "common.h"
#include "math_lib.h"

using namespace std;
using namespace mathLib;

class Camera{
public:
    Vector4f position;
    Vector4f rotation; // Rotacion respecto en reposo
    
    Vector4f lookAt; // Punto al que mirar
    Vector4f lookAtPrime; // Punto al que mirar en reposo

    Vector4f forward, right, up;

    Camera(Vector4f position, Vector4f lookAt, Vector4f up = {0, 1, 0, 0});

    // Calcula la matriz de vista de la camara en base a posicion, rotacion y orientacion
    Matrix4x4f computeViewMatrix();
    // Calcula la matriz de proyeccion en base a su campo de vision, relacion de aspecto y planos cercanos y lejanos
    Matrix4x4f computeProjectionMatrix(float zNear, float zFar, float fovy, float aspectRatio);

    void moveObject(double timeStep);
};