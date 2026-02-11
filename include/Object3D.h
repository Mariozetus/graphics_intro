#pragma once
#include "mathLib.h"
using namespace mathLib;

typedef struct{
    vec4float position;
    vec4float color;
} vertex_t;


class Object3D {  

public:
    static inline unsigned int idCounter;

    unsigned int objectId;

    vector<vertex_t> vertexList;
    vector<unsigned int> indexList;

    vec4float position = { 0, 0, 0, 1};

    Object3D();

    matrix4x4f computeModelMatrix();
    void moveObject(double timeStep);
};