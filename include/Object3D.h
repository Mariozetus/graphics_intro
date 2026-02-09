#pragma once
#include "mathLib.h"
#include "eventManager.h"
using namespace mathLib;

typedef struct{
    vec4float position;
    vec4float color;
} vertex_t;


class Object3D {  

public:
    vector<vertex_t> vertexList;

    vec4float position = { 0, 0, 0, 1};

    Object3D();

    matrix4x4f computeModelMatrix();
    void moveObject(double timeStep);
};