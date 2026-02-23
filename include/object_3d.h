#pragma once
#include "math_lib.h"
using namespace mathLib;

typedef struct{
    Vector4f position;
    Vector4f color;
} vertex_t;


class Object3D {  

public:
    static inline unsigned int idCounter;

    unsigned int objectId;

    vector<vertex_t> vertexList;
    vector<unsigned int> indexList;

    Vector4f position = { 0, 0, 0, 1};

    Object3D();

    Matrix4x4f computeModelMatrix();
    void moveObject(double timeStep);
};